#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Dusk2Dawn.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <DHT.h>
#include <DHT_U.h>
#include <MQ135.h>
#include <ESP_EEPROM.h>

#include <ESP8266RTTTLPlus.h>
#include <ArduinoJson.h>

const char* client_id = "393565403730-48p5e5maa5smu4q3cvr9e4f97nd0og4n.apps.googleusercontent.com";
const char* client_secret = "AIzaSyBryBsZbT9zqhHfEtQvIHNkQ_oNtwT5myo";
const char* calendar_id = "8202aa352ff05a668aee4a36e941ecefd7c23a5c8c057f2de7550ffcbf093f76@group.calendar.google.com";

Adafruit_BMP280 bmp;

unsigned long startTime = 0;

String* days = new String[7]{ "Niedziela", "Poniedzialek", "Wtorek", "Sroda", "Czwartek", "Piatek", "Sobota" };

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 60000);
Dusk2Dawn ks(51.8283, 15.5594, 1);
Dusk2Dawn zg(51.9373, 15.5082, 1);

#define DHTPIN 0
#define DHTTYPE    DHT22
DHT dht(DHTPIN, DHTTYPE);

#define PIN_MQ135 A0
MQ135 mq135_sensor = MQ135(PIN_MQ135);

#define BUZZER_PIN D4



char SunriseText[] = "00:00";
char SunsetText[] = "00:00";
char TimeText[] = "00:00";
char DateText[] = "00.00.0000";
char DayText[] = "Poniedzialek";
char SecondsText[] = "00";
char TemperatureText[] = "00.0*C";
char PressureText[] = "0000hpa";
char DHTtemperatureText[] = "00.0*C";
char HumidityText[] = "00.0%";
char MQ135Text[] = "0000ppm";

float temperature = 0, humidity = 0;
int hour = 0, minute = 0, weekday = 0;

void updateMQ135() {
    float mq135 = mq135_sensor.getPPM();
    float mq135_corrected = mq135_sensor.getCorrectedPPM(temperature, humidity);
    sprintf(MQ135Text, "%4.0f%S", mq135, "ppm");
    // Serial.print("MQ135: ");
    // Serial.print(mq135);
    // Serial.print(" ppm, ");
    // Serial.print(mq135_corrected);
    // Serial.println(" ppm (corrected)");

}

void updateDHT22() {
    temperature = dht.readTemperature();
    humidity = dht.readHumidity();
    sprintf(DHTtemperatureText, "%2.1f%S", temperature, "*C");
    sprintf(HumidityText, "%3f%S", humidity, "%");
    // Serial.print("DHT22: ");
    // Serial.print(temperature);
    // Serial.print(" *C, ");
    // Serial.print(humidity);
    // Serial.println(" %");
}

void updateBMP280() {
    temperature = bmp.readTemperature();
    float pressure = bmp.readPressure() / 100;
    sprintf(TemperatureText, "%2.1f%S", temperature, "*C");
    sprintf(PressureText, "%4.0f%S", pressure, "hpa");
    //     Serial.print("BMP280: ");
    //     Serial.print(temperature);
    //     Serial.print(" *C, ");
    //     Serial.print(pressure);
    //     Serial.println(" hpa");
}


void updateTexts(struct tm* ptm) {
    hour = ptm->tm_hour;
    minute = ptm->tm_min;
    weekday = ptm->tm_wday;

    sprintf(TimeText, "%02d:%02d", ptm->tm_hour, ptm->tm_min);
    sprintf(SecondsText, "%02d", ptm->tm_sec);
    sprintf(DateText, "%02d.%02d.%04d", ptm->tm_mday, ptm->tm_mon + 1, ptm->tm_year + 1900);
    sprintf(DayText, "%s", days[ptm->tm_wday].c_str());
    int Sunrise = ks.sunrise(ptm->tm_year + 1900, ptm->tm_mon + 1, ptm->tm_mday, false);
    int Sunset = ks.sunset(ptm->tm_year + 1900, ptm->tm_mon + 1, ptm->tm_mday, false);
    sprintf(SunriseText, "%02d:%02d", Sunrise / 60, Sunrise % 60);
    sprintf(SunsetText, "%02d:%02d", Sunset / 60, Sunset % 60);

}

bool syncTime() {
    //if wifi is connected
    time_t epochTime = timeClient.getEpochTime();
    struct tm* ptm = gmtime(&epochTime);
    updateTexts(ptm);
    if (WiFi.status() == WL_CONNECTED) {
        if (timeClient.update()) {
            return true;
        }
    }
    return false;
}


String* scanWiFi() {
    int numberOfNetworks = WiFi.scanNetworks();
    gslc_ElemXListboxReset(&m_gui, m_pElemListbox2);
    if (numberOfNetworks == 0) {
        return new String[1]{ "Brak dostępnych sieci WiFi" };
    }
    else {
        String* availableNetworks = new String[numberOfNetworks];
        // zapisanie nazw sieci i ich sił do tablicy w formacie "Nazwa (siła)"
        for (int i = 0; i < numberOfNetworks; i++) {
            availableNetworks[i] = WiFi.SSID(i) + " (" + WiFi.RSSI(i) + ")";
        }


        for (int i = 0; i < numberOfNetworks; i++) {
            gslc_ElemXListboxAddItem(&m_gui, m_pElemListbox2, availableNetworks[i].c_str());
        }


        return availableNetworks;
    }
}


struct s_appSettings {
    char ssid[16];
    char password[32];
};

struct s_alarm {
    int hour;
    int minute;
    bool enabled;
    bool poniedzialek;
    bool wtorek;
    bool sroda;
    bool czwartek;
    bool piatek;
    bool sobota;
    bool niedziela;
};

s_appSettings appSettings = { "ssid", "password" };

//Lista domyślnych alarmów
s_alarm alarms[15] = {
    {7, 0, true, true, true, true, true, true, true, true},
    {7, 30, false, true, true, true, false, false, false, false},
    {8, 0, true, true, true, false, false, false, false, false},
    {8, 30, false, true, false, false, false, false, false, false},
    {9, 0, true, false, false, false, false, true, true, true},
    {9, 30, false, false, false, false, false, false, false, false},
    {10, 0, true, false, false, false, false, false, false, false},
    {10, 30, false, false, false, false, false, false, false, false},
    {11, 0, true, false, false, false, false, false, false, false},
    {11, 30, false, false, false, false, false, false, false, false},
    {12, 0, true, false, false, false, false, false, false, false},
    {12, 30, false, false, false, false, false, false, false, false},
    {13, 0, true, false, false, false, false, false, false, false},
    {13, 30, false, false, false, false, false, false, false, false},
    {14, 0, true, false, false, false, false, false, false, false}
};



void eepromOperation(bool save) {
    int address = 0;
    EEPROM.begin(sizeof(s_appSettings) + sizeof(s_alarm) * 15);
    if (save) {
        EEPROM.put(address, appSettings);
        address += sizeof(s_appSettings);
        for (int i = 0; i < 15; i++) {
            EEPROM.put(address, alarms[i]);
            address += sizeof(s_alarm);
        }
        EEPROM.commit();

    }
    else {
        EEPROM.get(address, appSettings);
        address += sizeof(s_appSettings);
        for (int i = 0; i < 15; i++) {
            EEPROM.get(address, alarms[i]);
            address += sizeof(s_alarm);
        }
    }
    EEPROM.end();



}

char* alarmtoString(s_alarm alarm) {
    // format: ON 07:00 PN, WT, SR, CZ, PT, SB, ND
    char* alarmString = new char[31];
    if (alarm.enabled) {
        sprintf(alarmString, "ON %02d:%02d ", alarm.hour, alarm.minute);
    }
    else {
        sprintf(alarmString, "OFF %02d:%02d ", alarm.hour, alarm.minute);
    }
    if (alarm.poniedzialek) {
        //strcat(alarmString, " PN");
        strcat(alarmString, "1");
    }
    if (alarm.wtorek) {
        //strcat(alarmString, " WT");
        strcat(alarmString, "2");
    }
    if (alarm.sroda) {
        //strcat(alarmString, " SR");
        strcat(alarmString, "3");
    }
    if (alarm.czwartek) {
        //strcat(alarmString, " CZ");
        strcat(alarmString, "4");
    }
    if (alarm.piatek) {
        //strcat(alarmString, " PT");
        strcat(alarmString, "5");
    }
    if (alarm.sobota) {
        //strcat(alarmString, " SB");
        strcat(alarmString, "6");
    }
    if (alarm.niedziela) {
        //strcat(alarmString, " ND");
        strcat(alarmString, "7");
    }
    return alarmString;
}

void AlarmListboxLoad() {
    gslc_ElemXListboxReset(&m_gui, m_alarmList);
    for (int i = 0; i < 15; i++) {
        Serial.println(alarmtoString(alarms[i]));
        char* test = alarmtoString(alarms[i]);
        gslc_ElemXListboxAddItem(&m_gui, m_alarmList, test);
    }

    //test = "qwertyuiopasdfghjklzxcvbnm123456790";
}

static int selectedAlarm = 0;

void getAlarm() {
    int16_t m_nSelected = gslc_ElemXListboxGetSel(&m_gui, m_alarmList);
    Serial.println(m_nSelected);
    if (m_nSelected >= 0) {
        selectedAlarm = m_nSelected;
        gslc_ElemSetTxtStr(&m_gui, m_ALARM_HOUR, String(alarms[m_nSelected].hour).c_str());
        gslc_ElemSetTxtStr(&m_gui, m_ALARM_MIN, String(alarms[m_nSelected].minute).c_str());

        gslc_ElemXTogglebtnSetState(&m_gui, m_ALARM_TOGGLE, alarms[m_nSelected].enabled);

        gslc_ElemXCheckboxSetState(&m_gui, m_CHECK_PON, alarms[m_nSelected].poniedzialek);
        gslc_ElemXCheckboxSetState(&m_gui, m_CHECK_WT, alarms[m_nSelected].wtorek);
        gslc_ElemXCheckboxSetState(&m_gui, m_CHECK_SR, alarms[m_nSelected].sroda);
        gslc_ElemXCheckboxSetState(&m_gui, m_CHECK_CZW, alarms[m_nSelected].czwartek);
        gslc_ElemXCheckboxSetState(&m_gui, m_CHECK_PT, alarms[m_nSelected].piatek);
        gslc_ElemXCheckboxSetState(&m_gui, m_CHECK_SB, alarms[m_nSelected].sobota);
        gslc_ElemXCheckboxSetState(&m_gui, m_CHECK_ND, alarms[m_nSelected].niedziela);

    }
}

void updateAlarm() {
    int hour = atoi(gslc_ElemGetTxtStr(&m_gui, m_ALARM_HOUR));
    int minute = atoi(gslc_ElemGetTxtStr(&m_gui, m_ALARM_MIN));
    if (hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59) {
        alarms[selectedAlarm].hour = hour;
        alarms[selectedAlarm].minute = minute;
    }
    alarms[selectedAlarm].enabled = gslc_ElemXTogglebtnGetState(&m_gui, m_ALARM_TOGGLE);
    alarms[selectedAlarm].poniedzialek = gslc_ElemXCheckboxGetState(&m_gui, m_CHECK_PON);
    alarms[selectedAlarm].wtorek = gslc_ElemXCheckboxGetState(&m_gui, m_CHECK_WT);
    alarms[selectedAlarm].sroda = gslc_ElemXCheckboxGetState(&m_gui, m_CHECK_SR);
    alarms[selectedAlarm].czwartek = gslc_ElemXCheckboxGetState(&m_gui, m_CHECK_CZW);
    alarms[selectedAlarm].piatek = gslc_ElemXCheckboxGetState(&m_gui, m_CHECK_PT);
    alarms[selectedAlarm].sobota = gslc_ElemXCheckboxGetState(&m_gui, m_CHECK_SB);
    alarms[selectedAlarm].niedziela = gslc_ElemXCheckboxGetState(&m_gui, m_CHECK_ND);
    AlarmListboxLoad();
}

void tryConnectToSavedWiFi() {
    Serial.println(F("Sprawdzanie połączenia z siecią WiFi"));
    const char* ssid = appSettings.ssid;
    const char* password = appSettings.password;
    Serial.print(F("Laczenie z siecia WiFi: "));
    Serial.print(ssid);
    Serial.print(F(" Haslo: "));
    Serial.println(password);

    WiFi.begin(ssid, password);
    int timeout = 0;
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        timeout++;
        if (timeout == 5) {
            Serial.println(F("Nie udało się połączyć z siecią WiFi"));
            return;
        }
    }
    Serial.println(F("Połączono z siecią WiFi"));
    gslc_ElemSetTxtStr(&m_gui, m_SSID_TO_CONNECT, ssid);

}

bool connectToWiFi(int index) {
    WiFi.begin(WiFi.SSID(index).c_str(), gslc_ElemGetTxtStr(&m_gui, m_pElemInTxt1));
    int timeout = 0;
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        timeout++;
        if (timeout == 5) {
            return false;
            gslc_ElemSetTxtStr(&m_gui, m_Conn_Status, "Error");
            Serial.println(F("Nie udało się połączyć z siecią WiFi"));
        }
    }
    Serial.println(F("Połączono z siecią WiFi"));
    gslc_ElemSetTxtStr(&m_gui, m_Conn_Status, "Polaczono");
    gslc_ElemSetTxtStr(&m_gui, m_SSID_TO_CONNECT, WiFi.SSID().c_str());
    gslc_ElemSetTxtStr(&m_gui, m_IP, WiFi.localIP().toString().c_str());
    const char* ssid = gslc_ElemGetTxtStr(&m_gui, m_SSID_TO_CONNECT);
    Serial.println(ssid);
    const char* password = gslc_ElemGetTxtStr(&m_gui, m_pElemInTxt1);
    Serial.println(password);
    for (int i = 0; i < sizeof(appSettings.ssid); i++) {
        appSettings.ssid[i] = ssid[i];
        if (ssid[i] == '\0') {
            break;
        }
    }
    for (int i = 0; i < sizeof(appSettings.password); i++) {
        appSettings.password[i] = password[i];
        if (password[i] == '\0') {
            break;
        }
    }
    // save alarm settings to eeprom

    eepromOperation(true);

    return true;
}


bool checkAlarms() {
    for (int i = 0; i < 15; i++) {
        if (alarms[i].enabled) {
            if (alarms[i].hour == hour && alarms[i].minute == minute) {
                if (alarms[i].poniedzialek && weekday == 1) {
                    alarms[i].enabled = false;
                    e8rtp::start();
                    return true;
                }
                if (alarms[i].wtorek && weekday == 2) {
                    alarms[i].enabled = false;
                    e8rtp::start();
                    return true;
                }
                if (alarms[i].sroda && weekday == 3) {
                    alarms[i].enabled = false;
                    e8rtp::start();
                    return true;
                }
                if (alarms[i].czwartek && weekday == 4) {
                    alarms[i].enabled = false;
                    e8rtp::start();
                    return true;
                }
                if (alarms[i].piatek && weekday == 5) {
                    alarms[i].enabled = false;
                    e8rtp::start();
                    return true;
                }
                if (alarms[i].sobota && weekday == 6) {
                    alarms[i].enabled = false;
                    e8rtp::start();
                    return true;
                }
                if (alarms[i].niedziela && weekday == 7) {
                    alarms[i].enabled = false;
                    e8rtp::start();
                    return true;
                }
            }
        }
    }
    return false;
}

WiFiClient client;

//https/ssl wifi client
BearSSL::WiFiClientSecure clientSecure;
BearSSL::Session tlsSession;


String now() {
    time_t epochTime = timeClient.getEpochTime();
    // epochTime minus 30 minutes
    epochTime -= 1800;
    struct tm* ptm = gmtime(&epochTime);
    char buffer[80];
    strftime(buffer, 80, "%Y-%m-%dT%H:%M:%S.000Z", ptm);
    Serial.println(buffer);
    return String(buffer);
}


void getAlarmsFromGoogleCalendarSecure() {

    if (WiFi.status() == WL_CONNECTED) {
        // Build the request URL
        String url = "https://www.googleapis.com/calendar/v3/calendars/";
        url += calendar_id;
        url += "/events?&key=";
        url += client_secret;
        url += "&alwaysIncludeEmail=false";
        url += "&prettyPrint=false";
        url += "&alt=json";
        url += "&timeMin=";
        url += now();
        url += "&fields=items(start(dateTime),%20summary,%20recurrence)";
        //url += "&maxResults=5";
        //url += "&orderBy=startTime";

        Serial.println(url);
        clientSecure.setInsecure();
        clientSecure.setBufferSizes(1024, 1024);
        clientSecure.setTimeout(5000);
        
        Serial.println("Connecting to server");
        if (clientSecure.connect("www.googleapis.com", 443)) {
            Serial.println("Connected to server");
            clientSecure.println("GET " + url + " HTTP/1.1");
            clientSecure.println("Host: www.googleapis.com");
            clientSecure.println("Accept: application/json");
            clientSecure.println("Connection: close");
            clientSecure.println();
            Serial.println("Request sent");
            delay(10);


            unsigned long timeout = millis();
            while (clientSecure.available() == 0) {
                if (millis() - timeout > 5000) {
                    Serial.println(F(">>> Client Timeout !"));
                    clientSecure.stop();
                    return;
                }
            }

            bool headers = true;
            char* response = (char*)malloc(1024);
            long i = 0;
            while (clientSecure.available()) {
                char c = clientSecure.read();
                //response += c;
                if (headers) {
                    if (c == '{') {
                        headers = false;
                        response[i] = c;
                    }
                }
                else {
                    i++;
                    response[i] = c;
                }
            }
            response[i + 1] = '\0';

            Serial.println("I:");
            Serial.println(i);

            Serial.println("Response:");
            Serial.println(response);

            // Parse JSON response 
            const size_t capacity = 1024;
            DynamicJsonDocument doc(capacity);



            Serial.println("Deserializing JSON");
            DeserializationError error = deserializeJson(doc, response);
            Serial.println("Deserialized");
            Serial.println("Freeing memory");
            free(response);
            Serial.println("Memory freed");

            if (error) {
                Serial.print(F("deserializeJson() failed: "));
                Serial.println(error.f_str());

                return;
            }

            int error_code = doc["error"]["code"];
            Serial.print(F("Error code: "));
            Serial.println(error_code);


            // Get the number of events
            int events = doc["items"].size();
            Serial.print("Number of events: ");
            Serial.println(events);

            for (int i = 0; i < events; i++) {
                Serial.print("Event ");
                Serial.print(i);
                Serial.println(":");
                Serial.print("Summary: ");
                Serial.println(String(doc["items"][i]["summary"]));
                Serial.print("Start: ");
                Serial.println(String(doc["items"][i]["start"]["dateTime"]));
                Serial.print("Weekday: "); // from recurrence
                Serial.println(String(doc["items"][i]["recurrence"][0]));

                // Get the start time
                String start = String(doc["items"][i]["start"]["dateTime"]);
                // get the hour and minute
                int hour2 = start.substring(11, 13).toInt();
                int minute2 = start.substring(14, 16).toInt();
                int day2 = start.substring(8, 10).toInt();
                int month2 = start.substring(5, 7).toInt();
                int year2 = start.substring(0, 4).toInt();

                // Print the start time
                Serial.print("Start time: ");
                Serial.print(hour2);
                Serial.print(":");
                Serial.println(minute2);
                Serial.print("Day: ");
                Serial.println(day2);
                Serial.print("Month: ");
                Serial.println(month2);
                Serial.print("Year: ");
                Serial.println(year2);

                // Save the first alarm in the array of alarms

                alarms[i].hour = hour2;
                alarms[i].minute = minute2;
                alarms[i].enabled = true;

                // Parse weekday from day of month and year
                // https://stackoverflow.com/questions/21242011/calculate-day-of-week-from-date
                int weekday2 = (day2 += month2 < 3 ? year2-- : year2 - 2, 23 * month2 / 9 + day2 + 4 + year2 / 4 - year2 / 100 + year2 / 400) % 7;
                Serial.print("Weekday: ");
                Serial.println(weekday2);
                Serial.println(days[weekday2]);

                // Save the weekday
                alarms[i].poniedzialek = false;
                alarms[i].wtorek = false;
                alarms[i].sroda = false;
                alarms[i].czwartek = false;
                alarms[i].piatek = false;
                alarms[i].sobota = false;
                alarms[i].niedziela = false;

                if (weekday2 == 0) {
                    alarms[i].poniedzialek = true;
                }
                else if (weekday2 == 1) {
                    alarms[i].wtorek = true;
                }
                else if (weekday2 == 2) {
                    alarms[i].sroda = true;
                }
                else if (weekday2 == 3) {
                    alarms[i].czwartek = true;
                }
                else if (weekday2 == 4) {
                    alarms[i].piatek = true;
                }
                else if (weekday2 == 5) {
                    alarms[i].sobota = true;
                }
                else if (weekday2 == 6) {
                    alarms[i].niedziela = true;
                }
            }

            // Serial.println();
            // Serial.println("closing connection");
        }
        else {
            // if you didn't get a connection to the server:
            Serial.println("connection failed");
            clientSecure.stop();
            Serial.println(F("connection failed"));
        }
        Serial.println(F("closing connection2"));
    }
    Serial.println(F("closing connection"));
    clientSecure.stop();
}
