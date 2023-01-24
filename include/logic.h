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

String connectedWiFi = "";
String WiFiPassword = "";
Adafruit_BMP280 bmp;

unsigned long startTime = 0;

String* days = new String[7] {"Niedziela", "Poniedzialek", "Wtorek", "Sroda", "Czwartek", "Piatek", "Sobota"};

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 60000);
Dusk2Dawn ks(51.8283, 15.5594, 1);
Dusk2Dawn zg(51.9373, 15.5082, 1);

#define DHTPIN 0
#define DHTTYPE    DHT22
DHT dht(DHTPIN, DHTTYPE);

#define PIN_MQ135 A0
MQ135 mq135_sensor = MQ135(PIN_MQ135);

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

void updateTexts(struct tm *ptm) {
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
    struct tm *ptm = gmtime (&epochTime); 
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
    if (numberOfNetworks == 0) {
        return new String[1] {"Brak dostępnych sieci WiFi"};
    }
    else {
        String* availableNetworks = new String[numberOfNetworks];
        int rssi[numberOfNetworks];
        for (int i = 0; i < numberOfNetworks; i++) {
            availableNetworks[i] = WiFi.SSID(i);
            rssi[i] = WiFi.RSSI(i);
        }

        //sortowanie
        for(int i = 0; i < numberOfNetworks; i++) {
            for(int j = i + 1; j < numberOfNetworks; j++) {
                if(rssi[i] < rssi[j]) {
                    int tempRSSI = rssi[i];
                    rssi[i] = rssi[j];
                    rssi[j] = tempRSSI;
                    String tempSSID = availableNetworks[i];
                    availableNetworks[i] = availableNetworks[j];
                    availableNetworks[j] = tempSSID;
                }
            }
        }
        //gslc_ElemSetTxtStr(&m_gui, WIFI1, availableNetworks[0].c_str());
        for (int i = 0; i < numberOfNetworks; i++) {
            switch (i) {
                case 0:
                    gslc_ElemSetTxtStr(&m_gui, WIFI1, availableNetworks[i].c_str());
                    break;
                case 1:
                    gslc_ElemSetTxtStr(&m_gui, WIFI2, availableNetworks[i].c_str());
                    break;
                case 2:
                    gslc_ElemSetTxtStr(&m_gui, WIFI3, availableNetworks[i].c_str());
                    break;
                case 3:
                    gslc_ElemSetTxtStr(&m_gui, WIFI4, availableNetworks[i].c_str());
                    break;
                case 4:
                    gslc_ElemSetTxtStr(&m_gui, WIFI5, availableNetworks[i].c_str());
                    break;
            }
        }
        
        // Wyświetlanie dostępnych sieci na terminalu
        Serial.println("Dostępne sieci WiFi:");
        for (int i = 0; i < numberOfNetworks; i++) {
            Serial.print(i + 1);
            Serial.print(". ");
            Serial.print(availableNetworks[i]);
            Serial.print(" (");
            Serial.print(rssi[i]);
            Serial.println(")");
        }
        return availableNetworks;
    }
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
            Serial.println("Nie udało się połączyć z siecią WiFi");
        }
    }
    Serial.println("Połączono z siecią WiFi");
    gslc_ElemSetTxtStr(&m_gui, m_Conn_Status, "Połączono");
    gslc_ElemSetTxtStr(&m_gui, m_SSID_TO_CONNECT, WiFi.SSID().c_str());
    gslc_ElemSetTxtStr(&m_gui, m_IP, WiFi.localIP().toString().c_str());
    connectedWiFi = "ssid";
    WiFiPassword = "password";
    return true;
}

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

//Lista domyślnych alarmów
s_alarm alarms[13] = {
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
    {13, 0, true, false, false, false, false, false, false, false}
};

char* alarmtoString(s_alarm alarm) {
    // format: ON 07:00 PN, WT, SR, CZ, PT, SB, ND
    char* alarmString = new char[35];
    if (alarm.enabled) {
        sprintf(alarmString, "ON %02d:%02d", alarm.hour, alarm.minute);
    }
    else {
        sprintf(alarmString, "OFF %02d:%02d", alarm.hour, alarm.minute);
    }
    if (alarm.poniedzialek) {
        strcat(alarmString, " PN");
    }
    if (alarm.wtorek) {
        strcat(alarmString, " WT");
    }
    if (alarm.sroda) {
        strcat(alarmString, " SR");
    }
    if (alarm.czwartek) {
        strcat(alarmString, " CZ");
    }
    if (alarm.piatek) {
        strcat(alarmString, " PT");
    }
    if (alarm.sobota) {
        strcat(alarmString, " SB");
    }
    if (alarm.niedziela) {
        strcat(alarmString, " ND");
    }
    return alarmString;
}

void AlarmListboxLoad() {
    gslc_ElemXListboxReset(&m_gui, m_alarmList);
    for (int i = 0; i < 15; i++) {
        gslc_ElemXListboxAddItem(&m_gui, m_alarmList, alarmtoString(alarms[i]));
        Serial.println(alarmtoString(alarms[i]));
    }
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


