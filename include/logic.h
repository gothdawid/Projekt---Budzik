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
            Serial.println("Nie udało się połączyć z siecią WiFi");
        }
    }
    Serial.println("Połączono z siecią WiFi");
    Serial.println(WiFi.localIP());
    Serial.println(WiFi.gatewayIP());
    Serial.println(WiFi.subnetMask());
    Serial.println(WiFi.dnsIP());
    Serial.println(WiFi.macAddress());
    Serial.println(WiFi.RSSI());
    Serial.println(WiFi.SSID());
    Serial.println(WiFi.BSSIDstr());
    Serial.println(WiFi.channel());
    Serial.println(WiFi.softAPIP());
    Serial.println(WiFi.softAPmacAddress());
    Serial.println(WiFi.softAPgetStationNum());;
    connectedWiFi = "ssid";
    WiFiPassword = "password";
    return true;
}



