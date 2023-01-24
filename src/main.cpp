//<App !Start!>
// FILE: [main.cpp]
// Created by GUIslice Builder version: [0.17.b18]
//
// GUIslice Builder Generated File
//
// For the latest guides, updates and support view:
// https://github.com/ImpulseAdventure/GUIslice
//
//<App !End!>

// ------------------------------------------------
// Headers to include
// ------------------------------------------------
#include "Budzik_GSLC.h"
#include "logic.h"

// ------------------------------------------------
// Program Globals
// ------------------------------------------------
//last sync time
unsigned long lastSyncTime = 0, lastBMPTime = 0, lastDHTTime = 0, lastMQ135Time = 0;
int selectedWiFi = 0;

// Save some element references for direct access
//<Save_References !Start!>
gslc_tsElemRef* WIFI1 = NULL;
gslc_tsElemRef* WIFI2 = NULL;
gslc_tsElemRef* WIFI3 = NULL;
gslc_tsElemRef* WIFI4 = NULL;
gslc_tsElemRef* WIFI5 = NULL;
gslc_tsElemRef* m_AIRQ = NULL;
gslc_tsElemRef* m_DATE = NULL;
gslc_tsElemRef* m_DAY = NULL;
gslc_tsElemRef* m_HUM = NULL;
gslc_tsElemRef* m_PRESSURE = NULL;
gslc_tsElemRef* m_SECONDS = NULL;
gslc_tsElemRef* m_SUNRISE = NULL;
gslc_tsElemRef* m_SUNSET = NULL;
gslc_tsElemRef* m_TEMP = NULL;
gslc_tsElemRef* m_TIME = NULL;
gslc_tsElemRef* m_pElemInTxt1 = NULL;
gslc_tsElemRef* m_pElemKeyPadAlpha = NULL;
//<Save_References !End!>

// Define debug message function
static int16_t DebugOut(char ch) { if (ch == (char)'\n') Serial.println(""); else Serial.write(ch); return 0; }

// ------------------------------------------------
// Callback Methods
// ------------------------------------------------
// Common Button callback
bool CbBtnCommon(void* pvGui, void* pvElemRef, gslc_teTouch eTouch, int16_t nX, int16_t nY)
{
  // Typecast the parameters to match the GUI and element types
  gslc_tsGui* pGui = (gslc_tsGui*)(pvGui);
  gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem* pElem = gslc_GetElemFromRef(pGui, pElemRef);
  char           acTxt[20];

  if (eTouch == GSLC_TOUCH_UP_IN) {
    // From the element's ID we can determine which button was pressed.
    switch (pElem->nId) {
      //<Button Enums !Start!>
    case E_ELEM_BTN1:
      gslc_SetPageCur(&m_gui, E_ALARMS);
      break;
    case E_ELEM_BTN2:
      gslc_SetPageCur(&m_gui, E_PG_SETTINGS);
      break;
    case E_ELEM_BTN3:
      gslc_SetPageCur(&m_gui, E_PG_WIFI);
      break;
    case E_ELEM_BTN4:
      gslc_SetPageCur(&m_gui, E_PG_MAIN);
      break;
    case E_ELEM_BTN5:
      gslc_SetPageCur(&m_gui, E_PG_SETTINGS);
      break;
    case E_ELEM_UP:
      break;
    case E_ELEM_DOWN:
      break;
    case E_ELEM_WIFI1:
      selectedWiFi = 0;
      gslc_SetPageCur(&m_gui, E_PG_PASSWORD);
      break;
    case E_ELEM_WIFI2:
      selectedWiFi = 1;
      gslc_SetPageCur(&m_gui, E_PG_PASSWORD);
      break;
    case E_ELEM_WIFI3:
      selectedWiFi = 2;
      gslc_SetPageCur(&m_gui, E_PG_PASSWORD);
      break;
    case E_ELEM_WIFI4:
      selectedWiFi = 3;
      gslc_SetPageCur(&m_gui, E_PG_PASSWORD);
      break;
    case E_ELEM_WIFI5:
      selectedWiFi = 4;
      gslc_SetPageCur(&m_gui, E_PG_PASSWORD);
      break;
    case E_BT_WIFI_REFRESH:
      scanWiFi();
      break;
    case E_ELEM_BTN15:
      gslc_SetPageCur(&m_gui, E_PG_MAIN);
      break;
    case E_ELEM_BTN16:
      connectToWiFi(selectedWiFi);
      break;
    case E_ELEM_BTN17:
      gslc_SetPageCur(&m_gui, E_PG_WIFI);
      break;
    case E_ELEM_TEXTINPUT1:
      // Clicked on edit field, so show popup box and associate with this text field
      gslc_ElemXKeyPadInputAsk(&m_gui, m_pElemKeyPadAlpha, E_POP_KEYPAD_ALPHA, m_pElemInTxt1);
      break;
      //<Button Enums !End!>
    default:
      break;
    }
  }
  return true;
}
//<Checkbox Callback !Start!>
//<Checkbox Callback !End!>
// KeyPad Input Ready callback
bool CbKeypad(void* pvGui, void* pvElemRef, int16_t nState, void* pvData)
{
  gslc_tsGui* pGui = (gslc_tsGui*)pvGui;
  gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem* pElem = gslc_GetElemFromRef(pGui, pElemRef);

  // From the pvData we can get the ID element that is ready.
  int16_t nTargetElemId = gslc_ElemXKeyPadDataTargetIdGet(pGui, pvData);
  if (nState == XKEYPAD_CB_STATE_DONE) {
    // User clicked on Enter to leave popup
    // - If we have a popup active, pass the return value directly to
    //   the corresponding value field
    switch (nTargetElemId) {
      //<Keypad Enums !Start!>
    case E_ELEM_TEXTINPUT1:
      gslc_ElemXKeyPadInputGet(pGui, m_pElemInTxt1, pvData);
      gslc_PopupHide(&m_gui);
      break;

      //<Keypad Enums !End!>
    default:
      break;
    }
  }
  else if (nState == XKEYPAD_CB_STATE_CANCEL) {
    // User escaped from popup, so don't update values
    gslc_PopupHide(&m_gui);
  }
  return true;
}
//<Spinner Callback !Start!>
//<Spinner Callback !End!>
//<Listbox Callback !Start!>
//<Listbox Callback !End!>
//<Draw Callback !Start!>
//<Draw Callback !End!>
//<Slider Callback !Start!>
//<Slider Callback !End!>
//<Tick Callback !Start!>
//<Tick Callback !End!>

void setup()
{
  // ------------------------------------------------
  // Initialize
  // ------------------------------------------------
  pinMode(PIN_MQ135, INPUT);
  pinMode(DHTPIN, INPUT);

  Serial.begin(115200);
  timeClient.begin();
  Wire.begin();
  if (!bmp.begin(0x76)) { // Sprawdzenie połączenia z czujnikiem
    Serial.println("Nie udało się połączyć z BMP280");
    while (1);
  }
  dht.begin();
  // Wait for USB Serial 
  //delay(1000);  // NOTE: Some devices require a delay after Serial.begin() before serial port can be used

  gslc_InitDebug(&DebugOut);

  // ------------------------------------------------
  // Create graphic elements
  // ------------------------------------------------
  InitGUIslice_gen();
}

// -----------------------------------
// Main event loop
// -----------------------------------
void loop()
{

  // ------------------------------------------------
  // Update GUI Elements
  // ------------------------------------------------

  //TODO - Add update code for any text, gauges, or sliders

  // ------------------------------------------------
  // Periodically call GUIslice update function
  // ------------------------------------------------
  if (millis() - lastSyncTime > 500) {
    lastSyncTime = millis();
    syncTime();
    gslc_ElemSetTxtStr(&m_gui, m_SUNRISE, SunriseText);
    gslc_ElemSetTxtStr(&m_gui, m_SUNSET, SunsetText);
    gslc_ElemSetTxtStr(&m_gui, m_TIME, TimeText);
    gslc_ElemSetTxtStr(&m_gui, m_DATE, DateText);
    gslc_ElemSetTxtStr(&m_gui, m_SECONDS, SecondsText);
    gslc_ElemSetTxtStr(&m_gui, m_DAY, DayText);
  }
  if (millis() - lastBMPTime > 5000) {
    lastBMPTime = millis();
    updateBMP280();
    gslc_ElemSetTxtStr(&m_gui, m_TEMP, TemperatureText);
    gslc_ElemSetTxtStr(&m_gui, m_PRESSURE, PressureText);
  }
  if (millis() - lastDHTTime > 10000) {
    lastDHTTime = millis();
    updateDHT22();
    gslc_ElemSetTxtStr(&m_gui, m_TEMP, DHTtemperatureText);
    gslc_ElemSetTxtStr(&m_gui, m_HUM, HumidityText);
  }
  if (millis() - lastMQ135Time > 3000) {
    lastMQ135Time = millis();
    updateMQ135();
    gslc_ElemSetTxtStr(&m_gui, m_AIRQ, MQ135Text);
  }
  gslc_Update(&m_gui);

}

