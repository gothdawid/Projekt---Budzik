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
gslc_tsElemRef* m_AIRQ = NULL;
gslc_tsElemRef* m_ALARM_HOUR = NULL;
gslc_tsElemRef* m_ALARM_MIN = NULL;
gslc_tsElemRef* m_ALARM_TOGGLE = NULL;
gslc_tsElemRef* m_CHECK_CZW = NULL;
gslc_tsElemRef* m_CHECK_ND = NULL;
gslc_tsElemRef* m_CHECK_PON = NULL;
gslc_tsElemRef* m_CHECK_PT = NULL;
gslc_tsElemRef* m_CHECK_SB = NULL;
gslc_tsElemRef* m_CHECK_SR = NULL;
gslc_tsElemRef* m_CHECK_WT = NULL;
gslc_tsElemRef* m_Conn_Status = NULL;
gslc_tsElemRef* m_DATE = NULL;
gslc_tsElemRef* m_DAY = NULL;
gslc_tsElemRef* m_HUM = NULL;
gslc_tsElemRef* m_IP = NULL;
gslc_tsElemRef* m_PRESSURE = NULL;
gslc_tsElemRef* m_SECONDS = NULL;
gslc_tsElemRef* m_SSID_TO_CONNECT = NULL;
gslc_tsElemRef* m_SUNRISE = NULL;
gslc_tsElemRef* m_SUNSET = NULL;
gslc_tsElemRef* m_TEMP = NULL;
gslc_tsElemRef* m_TIME = NULL;
gslc_tsElemRef* m_alarmList = NULL;
gslc_tsElemRef* m_pElemInTxt1 = NULL;
gslc_tsElemRef* m_pElemListbox2 = NULL;
gslc_tsElemRef* m_pListSlider1 = NULL;
gslc_tsElemRef* m_pListSlider2 = NULL;
gslc_tsElemRef* m_pElemKeyPadNum = NULL;
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
      AlarmListboxLoad();
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
    case E_BT_WIFI_REFRESH:
      scanWiFi();
      break;
    case E_ELEM_BTN15:
      eepromOperation(true);
      gslc_SetPageCur(&m_gui, E_PG_MAIN);
      break;
    case E_EDIT_ALARM:
      getAlarm();
      gslc_SetPageCur(&m_gui, E_PG_EDIT_ALARM);
      break;
    case E_ELEM_BTN16:
      connectToWiFi(selectedWiFi);
      gslc_PopupShow(&m_gui, E_PG_WIFI_STATUS, true);
      break;
    case E_ELEM_BTN17:
      gslc_SetPageCur(&m_gui, E_PG_WIFI);
      break;
    case E_ELEM_TEXTINPUT1:
      // Clicked on edit field, so show popup box and associate with this text field
      gslc_ElemXKeyPadInputAsk(&m_gui, m_pElemKeyPadAlpha, E_POP_KEYPAD_ALPHA, m_pElemInTxt1);
      break;
    case E_ELEM_BTN19:
      gslc_PopupHide(&m_gui);
      break;
    case E_ELEM_BTN24:
      gslc_SetPageCur(&m_gui, E_ALARMS);
      break;
    case E_ELEM_BTN25:
      updateAlarm();
      gslc_SetPageCur(&m_gui, E_ALARMS);
      break;
    case E_ELEM_NUMINPUT3:
      // Clicked on edit field, so show popup box and associate with this text field
      gslc_ElemXKeyPadInputAsk(&m_gui, m_pElemKeyPadNum, E_POP_KEYPAD_NUM, m_ALARM_HOUR);
      break;
    case E_ELEM_NUMINPUT4:
      // Clicked on edit field, so show popup box and associate with this text field
      gslc_ElemXKeyPadInputAsk(&m_gui, m_pElemKeyPadNum, E_POP_KEYPAD_NUM, m_ALARM_MIN);
      break;
    case E_ELEM_TOGGLE2:
      // TODO Add code for Toggle button ON/OFF state
      if (gslc_ElemXTogglebtnGetState(&m_gui, m_ALARM_TOGGLE)) {
        ;
      }
      break;
      //<Button Enums !End!>
    default:
      break;
    }
  }
  return true;
}
// Checkbox / radio callbacks
// - Creating a callback function is optional, but doing so enables you to
//   detect changes in the state of the elements.
bool CbCheckbox(void* pvGui, void* pvElemRef, int16_t nSelId, bool bState)
{
  gslc_tsGui* pGui = (gslc_tsGui*)(pvGui);
  gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem* pElem = gslc_GetElemFromRef(pGui, pElemRef);
  if (pElemRef == NULL) {
    return false;
  }

  boolean bChecked = gslc_ElemXCheckboxGetState(pGui, pElemRef);

  // Determine which element issued the callback
  switch (pElem->nId) {
    //<Checkbox Enums !Start!>
  case E_ELEM_CHECK9:
    break;
  case E_ELEM_CHECK16:
    break;
  case E_ELEM_CHECK17:
    break;
  case E_ELEM_CHECK18:
    break;
  case E_ELEM_CHECK19:
    break;
  case E_ELEM_CHECK20:
    break;
  case E_ELEM_CHECK21:
    break;

    //<Checkbox Enums !End!>
  default:
    break;
  } // switch
  return true;
}
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

    case E_ELEM_NUMINPUT3:
      gslc_ElemXKeyPadInputGet(pGui, m_ALARM_HOUR, pvData);
      gslc_PopupHide(&m_gui);
      break;
    case E_ELEM_NUMINPUT4:
      gslc_ElemXKeyPadInputGet(pGui, m_ALARM_MIN, pvData);
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
bool CbListbox(void* pvGui, void* pvElemRef, int16_t nSelId)
{
  gslc_tsGui* pGui = (gslc_tsGui*)(pvGui);
  gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem* pElem = gslc_GetElemFromRef(pGui, pElemRef);
  char            acTxt[MAX_STR + 1];

  if (pElemRef == NULL) {
    return false;
  }

  // From the element's ID we can determine which listbox was active.
  switch (pElem->nId) {
    //<Listbox Enums !Start!>
  case E_ELEM_LISTBOX1:
    if (nSelId != XLISTBOX_SEL_NONE) {
      gslc_ElemXListboxGetItem(&m_gui, pElemRef, nSelId, acTxt, MAX_STR);
    }
    break;

  case E_ELEM_LISTBOX2:
    if (nSelId != XLISTBOX_SEL_NONE) {
      gslc_ElemXListboxGetItem(&m_gui, pElemRef, nSelId, acTxt, MAX_STR);
      Serial.println(acTxt);
      Serial.println(nSelId);
      Serial.println(WiFi.SSID(nSelId));
      selectedWiFi = nSelId;
      gslc_ElemSetTxtStr(&m_gui, m_SSID_TO_CONNECT, WiFi.SSID(selectedWiFi).c_str());
      gslc_ElemSetTxtStr(&m_gui, m_pElemInTxt1, "");
      gslc_ElemSetTxtStr(&m_gui, m_IP, "");

      gslc_SetPageCur(&m_gui, E_PG_PASSWORD);
    }
    break;
    //<Listbox Enums !End!>
  default:
    break;
  }
  return true;
}
//<Draw Callback !Start!>
//<Draw Callback !End!>

// Callback function for when a slider's position has been updated
bool CbSlidePos(void* pvGui, void* pvElemRef, int16_t nPos)
{
  gslc_tsGui* pGui = (gslc_tsGui*)(pvGui);
  gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem* pElem = gslc_GetElemFromRef(pGui, pElemRef);
  int16_t         nVal;
  gslc_tsElemRef* pElemRefTmp = NULL;

  // From the element's ID we can determine which slider was updated.
  switch (pElem->nId) {
    //<Slider Enums !Start!>
  case E_LISTSCROLL1:
    // Fetch the slider position
    nVal = gslc_ElemXSliderGetPos(pGui, m_pListSlider1);
    // Update the listbox to match the slider position
    pElemRefTmp = gslc_PageFindElemById(&m_gui, E_ALARMS, E_ELEM_LISTBOX1);
    gslc_ElemXListboxSetScrollPos(pGui, pElemRefTmp, nVal);
    break;

  case E_LISTSCROLL2:
    // Fetch the slider position
    nVal = gslc_ElemXSliderGetPos(pGui, m_pListSlider2);
    // Update the listbox to match the slider position
    pElemRefTmp = gslc_PageFindElemById(&m_gui, E_PG_WIFI, E_ELEM_LISTBOX2);
    gslc_ElemXListboxSetScrollPos(pGui, pElemRefTmp, nVal);
    break;
    //<Slider Enums !End!>
  default:
    break;
  }

  return true;
}
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
  delay(1000);  // NOTE: Some devices require a delay after Serial.begin() before serial port can be used
  eepromOperation(false);
  if (appSettings.ssid != "" && appSettings.password != "") {
    tryConnectToSavedWiFi();
  }

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

