//<File !Start!>
// FILE: [Budzik_GSLC.h]
// Created by GUIslice Builder version: [0.17.b18]
//
// GUIslice Builder Generated GUI Framework File
//
// For the latest guides, updates and support view:
// https://github.com/ImpulseAdventure/GUIslice
//
//<File !End!>

#ifndef _GUISLICE_GEN_H
#define _GUISLICE_GEN_H

// ------------------------------------------------
// Headers to include
// ------------------------------------------------
#include "GUIslice.h"
#include "GUIslice_drv.h"

// Include any extended elements
//<Includes !Start!>
// Include extended elements
#include "elem/XCheckbox.h"
#include "elem/XKeyPad_Alpha.h"
#include "elem/XKeyPad_Num.h"
#include "elem/XListbox.h"
#include "elem/XSlider.h"
#include "elem/XTogglebtn.h"

// Ensure optional features are enabled in the configuration
//<Includes !End!>

// ------------------------------------------------
// Headers and Defines for fonts
// Note that font files are located within the Adafruit-GFX library folder:
// ------------------------------------------------
//<Fonts !Start!>
#if !defined(DRV_DISP_TFT_ESPI)
  #error E_PROJECT_OPTIONS tab->Graphics Library should be Adafruit_GFX
#endif
#include <TFT_eSPI.h>
#include "NotoLatin1_10pt.h"
#include "NotoLatin1_12pt.h"
#include "NotoLatin1_36pt.h"
//<Fonts !End!>

// ------------------------------------------------
// Defines for resources
// ------------------------------------------------
//<Resources !Start!>
//<Resources !End!>

// ------------------------------------------------
// Enumerations for pages, elements, fonts, images
// ------------------------------------------------
//<Enum !Start!>
enum {E_PG_MAIN,E_PG_SETTINGS,E_PG_WIFI,E_ALARMS,E_PG_PASSWORD
      ,E_PG_WIFI_STATUS,E_PG_EDIT_ALARM,E_POP_KEYPAD_NUM
      ,E_POP_KEYPAD_ALPHA};
enum {E_BT_WIFI_REFRESH,E_Conn_Status,E_DATE,E_DAY,E_DRAW_LINE1
      ,E_EDIT_ALARM,E_ELEM_AIRQ,E_ELEM_BOX1,E_ELEM_BOX10,E_ELEM_BOX12
      ,E_ELEM_BOX2,E_ELEM_BOX3,E_ELEM_BOX4,E_ELEM_BOX5,E_ELEM_BOX6
      ,E_ELEM_BOX8,E_ELEM_BOX9,E_ELEM_BTN1,E_ELEM_BTN15,E_ELEM_BTN16
      ,E_ELEM_BTN17,E_ELEM_BTN19,E_ELEM_BTN2,E_ELEM_BTN24,E_ELEM_BTN25
      ,E_ELEM_BTN3,E_ELEM_BTN4,E_ELEM_BTN5,E_ELEM_CHECK16
      ,E_ELEM_CHECK17,E_ELEM_CHECK18,E_ELEM_CHECK19,E_ELEM_CHECK20
      ,E_ELEM_CHECK21,E_ELEM_CHECK9,E_ELEM_DOWN,E_ELEM_HUM
      ,E_ELEM_LISTBOX1,E_ELEM_NUMINPUT3,E_ELEM_NUMINPUT4
      ,E_ELEM_PRESSURE,E_ELEM_SUNRISE,E_ELEM_SUNSET,E_ELEM_TEMP
      ,E_ELEM_TEXT18,E_ELEM_TEXT19,E_ELEM_TEXT20,E_ELEM_TEXT28
      ,E_ELEM_TEXT29,E_ELEM_TEXT30,E_ELEM_TEXT31,E_ELEM_TEXT32
      ,E_ELEM_TEXT33,E_ELEM_TEXT34,E_ELEM_TEXT35,E_ELEM_TEXT36
      ,E_ELEM_TEXT4,E_ELEM_TEXT5,E_ELEM_TEXT6,E_ELEM_TEXTINPUT1
      ,E_ELEM_TOGGLE2,E_ELEM_UP,E_ELEM_WIFI1,E_ELEM_WIFI2,E_ELEM_WIFI3
      ,E_ELEM_WIFI4,E_ELEM_WIFI5,E_LISTSCROLL1,E_SECONDS,E_TIME
      ,E_ELEM_KEYPAD_NUM,E_ELEM_KEYPAD_ALPHA};
// Must use separate enum for fonts with MAX_FONT at end to use gslc_FontSet.
enum {E_BUILTIN10X16,E_BUILTIN15X24,E_BUILTIN20X32,E_BUILTIN5X8
      ,E_NOTOLATIN1_10PT,E_NOTOLATIN1_12PT,E_NOTOLATIN1_36PT,MAX_FONT};
//<Enum !End!>

// ------------------------------------------------
// Instantiate the GUI
// ------------------------------------------------

// ------------------------------------------------
// Define the maximum number of elements and pages
// ------------------------------------------------
//<ElementDefines !Start!>
#define MAX_PAGE                9

#define MAX_ELEM_PG_MAIN 17 // # Elems total on page
#define MAX_ELEM_PG_MAIN_RAM MAX_ELEM_PG_MAIN // # Elems in RAM

#define MAX_ELEM_PG_SETTINGS 3 // # Elems total on page
#define MAX_ELEM_PG_SETTINGS_RAM MAX_ELEM_PG_SETTINGS // # Elems in RAM

#define MAX_ELEM_PG_WIFI 10 // # Elems total on page
#define MAX_ELEM_PG_WIFI_RAM MAX_ELEM_PG_WIFI // # Elems in RAM

#define MAX_ELEM_ALARMS 7 // # Elems total on page
#define MAX_ELEM_ALARMS_RAM MAX_ELEM_ALARMS // # Elems in RAM

#define MAX_ELEM_PG_PASSWORD 9 // # Elems total on page
#define MAX_ELEM_PG_PASSWORD_RAM MAX_ELEM_PG_PASSWORD // # Elems in RAM

#define MAX_ELEM_PG_WIFI_STATUS 3 // # Elems total on page
#define MAX_ELEM_PG_WIFI_STATUS_RAM MAX_ELEM_PG_WIFI_STATUS // # Elems in RAM

#define MAX_ELEM_PG_EDIT_ALARM 22 // # Elems total on page
#define MAX_ELEM_PG_EDIT_ALARM_RAM MAX_ELEM_PG_EDIT_ALARM // # Elems in RAM
//<ElementDefines !End!>

// ------------------------------------------------
// Create element storage
// ------------------------------------------------
gslc_tsGui                      m_gui;
gslc_tsDriver                   m_drv;
gslc_tsFont                     m_asFont[MAX_FONT];
gslc_tsPage                     m_asPage[MAX_PAGE];

//<GUI_Extra_Elements !Start!>
gslc_tsElem                     m_asPage1Elem[MAX_ELEM_PG_MAIN_RAM];
gslc_tsElemRef                  m_asPage1ElemRef[MAX_ELEM_PG_MAIN];
gslc_tsElem                     m_asPage2Elem[MAX_ELEM_PG_SETTINGS_RAM];
gslc_tsElemRef                  m_asPage2ElemRef[MAX_ELEM_PG_SETTINGS];
gslc_tsElem                     m_asPage3Elem[MAX_ELEM_PG_WIFI_RAM];
gslc_tsElemRef                  m_asPage3ElemRef[MAX_ELEM_PG_WIFI];
gslc_tsElem                     m_asPage4Elem[MAX_ELEM_ALARMS_RAM];
gslc_tsElemRef                  m_asPage4ElemRef[MAX_ELEM_ALARMS];
gslc_tsElem                     m_asPage5Elem[MAX_ELEM_PG_PASSWORD_RAM];
gslc_tsElemRef                  m_asPage5ElemRef[MAX_ELEM_PG_PASSWORD];
gslc_tsElem                     m_asPopup1Elem[MAX_ELEM_PG_WIFI_STATUS_RAM];
gslc_tsElemRef                  m_asPopup1ElemRef[MAX_ELEM_PG_WIFI_STATUS];
gslc_tsElem                     m_asPage6Elem[MAX_ELEM_PG_EDIT_ALARM_RAM];
gslc_tsElemRef                  m_asPage6ElemRef[MAX_ELEM_PG_EDIT_ALARM];
gslc_tsElem                     m_asKeypadNumElem[1];
gslc_tsElemRef                  m_asKeypadNumElemRef[1];
gslc_tsElem                     m_asKeypadAlphaElem[1];
gslc_tsElemRef                  m_asKeypadAlphaElemRef[1];
gslc_tsXKeyPad                  m_sKeyPadNum;
gslc_tsXKeyPad                  m_sKeyPadAlpha;
gslc_tsXListbox                 m_sListbox1;
// - Note that XLISTBOX_BUF_OH_R is extra required per item
char                            m_acListboxBuf1[465 + XLISTBOX_BUF_OH_R];
gslc_tsXSlider                  m_sListScroll1;
gslc_tsXTogglebtn               m_asXToggle2;
gslc_tsXCheckbox                m_asXCheck9;
gslc_tsXCheckbox                m_asXCheck16;
gslc_tsXCheckbox                m_asXCheck17;
gslc_tsXCheckbox                m_asXCheck18;
gslc_tsXCheckbox                m_asXCheck19;
gslc_tsXCheckbox                m_asXCheck20;
gslc_tsXCheckbox                m_asXCheck21;

#define MAX_STR                 100

//<GUI_Extra_Elements !End!>

// ------------------------------------------------
// Program Globals
// ------------------------------------------------

// Element References for direct access
//<Extern_References !Start!>
extern gslc_tsElemRef* WIFI1;
extern gslc_tsElemRef* WIFI2;
extern gslc_tsElemRef* WIFI3;
extern gslc_tsElemRef* WIFI4;
extern gslc_tsElemRef* WIFI5;
extern gslc_tsElemRef* m_AIRQ;
extern gslc_tsElemRef* m_ALARM_HOUR;
extern gslc_tsElemRef* m_ALARM_MIN;
extern gslc_tsElemRef* m_ALARM_TOGGLE;
extern gslc_tsElemRef* m_CHECK_CZW;
extern gslc_tsElemRef* m_CHECK_ND;
extern gslc_tsElemRef* m_CHECK_PON;
extern gslc_tsElemRef* m_CHECK_PT;
extern gslc_tsElemRef* m_CHECK_SB;
extern gslc_tsElemRef* m_CHECK_SR;
extern gslc_tsElemRef* m_CHECK_WT;
extern gslc_tsElemRef* m_Conn_Status;
extern gslc_tsElemRef* m_DATE;
extern gslc_tsElemRef* m_DAY;
extern gslc_tsElemRef* m_HUM;
extern gslc_tsElemRef* m_IP;
extern gslc_tsElemRef* m_PRESSURE;
extern gslc_tsElemRef* m_SECONDS;
extern gslc_tsElemRef* m_SSID_TO_CONNECT;
extern gslc_tsElemRef* m_SUNRISE;
extern gslc_tsElemRef* m_SUNSET;
extern gslc_tsElemRef* m_TEMP;
extern gslc_tsElemRef* m_TIME;
extern gslc_tsElemRef* m_alarmList;
extern gslc_tsElemRef* m_pElemInTxt1;
extern gslc_tsElemRef* m_pListSlider1;
extern gslc_tsElemRef* m_pElemKeyPadNum;
extern gslc_tsElemRef* m_pElemKeyPadAlpha;
//<Extern_References !End!>

// Define debug message function
static int16_t DebugOut(char ch);

// ------------------------------------------------
// Callback Methods
// ------------------------------------------------
bool CbBtnCommon(void* pvGui,void *pvElemRef,gslc_teTouch eTouch,int16_t nX,int16_t nY);
bool CbCheckbox(void* pvGui, void* pvElemRef, int16_t nSelId, bool bState);
bool CbDrawScanner(void* pvGui,void* pvElemRef,gslc_teRedrawType eRedraw);
bool CbKeypad(void* pvGui, void *pvElemRef, int16_t nState, void* pvData);
bool CbListbox(void* pvGui, void* pvElemRef, int16_t nSelId);
bool CbSlidePos(void* pvGui,void* pvElemRef,int16_t nPos);
bool CbSpinner(void* pvGui, void *pvElemRef, int16_t nState, void* pvData);
bool CbTickScanner(void* pvGui,void* pvScope);

// ------------------------------------------------
// Create page elements
// ------------------------------------------------
void InitGUIslice_gen()
{
  gslc_tsElemRef* pElemRef = NULL;

  if (!gslc_Init(&m_gui,&m_drv,m_asPage,MAX_PAGE,m_asFont,MAX_FONT)) { return; }

  // ------------------------------------------------
  // Load Fonts
  // ------------------------------------------------
//<Load_Fonts !Start!>
    if (!gslc_FontSet(&m_gui,E_BUILTIN10X16,GSLC_FONTREF_PTR,NULL,2)) { return; }
    if (!gslc_FontSet(&m_gui,E_BUILTIN15X24,GSLC_FONTREF_PTR,NULL,3)) { return; }
    if (!gslc_FontSet(&m_gui,E_BUILTIN20X32,GSLC_FONTREF_PTR,NULL,4)) { return; }
    if (!gslc_FontSet(&m_gui,E_BUILTIN5X8,GSLC_FONTREF_PTR,NULL,1)) { return; }
    if (!gslc_FontSet(&m_gui,E_NOTOLATIN1_10PT,GSLC_FONTREF_PTR,&NotoLatin1_10pt,1)) { return; }
    if (!gslc_FontSet(&m_gui,E_NOTOLATIN1_12PT,GSLC_FONTREF_PTR,&NotoLatin1_12pt,1)) { return; }
    if (!gslc_FontSet(&m_gui,E_NOTOLATIN1_36PT,GSLC_FONTREF_PTR,&NotoLatin1_36pt,1)) { return; }
//<Load_Fonts !End!>

//<InitGUI !Start!>
  gslc_PageAdd(&m_gui,E_PG_MAIN,m_asPage1Elem,MAX_ELEM_PG_MAIN_RAM,m_asPage1ElemRef,MAX_ELEM_PG_MAIN);
  gslc_PageAdd(&m_gui,E_PG_SETTINGS,m_asPage2Elem,MAX_ELEM_PG_SETTINGS_RAM,m_asPage2ElemRef,MAX_ELEM_PG_SETTINGS);
  gslc_PageAdd(&m_gui,E_PG_WIFI,m_asPage3Elem,MAX_ELEM_PG_WIFI_RAM,m_asPage3ElemRef,MAX_ELEM_PG_WIFI);
  gslc_PageAdd(&m_gui,E_ALARMS,m_asPage4Elem,MAX_ELEM_ALARMS_RAM,m_asPage4ElemRef,MAX_ELEM_ALARMS);
  gslc_PageAdd(&m_gui,E_PG_PASSWORD,m_asPage5Elem,MAX_ELEM_PG_PASSWORD_RAM,m_asPage5ElemRef,MAX_ELEM_PG_PASSWORD);
  gslc_PageAdd(&m_gui,E_PG_WIFI_STATUS,m_asPopup1Elem,MAX_ELEM_PG_WIFI_STATUS_RAM,m_asPopup1ElemRef,MAX_ELEM_PG_WIFI_STATUS);
  gslc_PageAdd(&m_gui,E_PG_EDIT_ALARM,m_asPage6Elem,MAX_ELEM_PG_EDIT_ALARM_RAM,m_asPage6ElemRef,MAX_ELEM_PG_EDIT_ALARM);
  gslc_PageAdd(&m_gui,E_POP_KEYPAD_NUM,m_asKeypadNumElem,1,m_asKeypadNumElemRef,1);  // KeyPad
  gslc_PageAdd(&m_gui,E_POP_KEYPAD_ALPHA,m_asKeypadAlphaElem,1,m_asKeypadAlphaElemRef,1);  // KeyPad

  // NOTE: The current page defaults to the first page added. Here we explicitly
  //       ensure that the main page is the correct page no matter the add order.
  gslc_SetPageCur(&m_gui,E_PG_MAIN);
  
  // Set Background to a flat color
  gslc_SetBkgndColor(&m_gui,GSLC_COL_BLACK);

  // -----------------------------------
  // PAGE: E_PG_MAIN
  
   
  // Create E_ELEM_BOX1 box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_BOX1,E_PG_MAIN,(gslc_tsRect){0,140,80,100});
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  gslc_ElemSetCol(&m_gui,pElemRef,((gslc_tsColor){0,0,32}),((gslc_tsColor){0,0,32}),((gslc_tsColor){0,0,32}));
   
  // Create E_ELEM_BOX2 box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_BOX2,E_PG_MAIN,(gslc_tsRect){80,140,80,100});
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  gslc_ElemSetCol(&m_gui,pElemRef,((gslc_tsColor){0,32,0}),((gslc_tsColor){0,32,0}),((gslc_tsColor){0,32,0}));
   
  // Create E_ELEM_BOX3 box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_BOX3,E_PG_MAIN,(gslc_tsRect){160,140,80,100});
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  gslc_ElemSetCol(&m_gui,pElemRef,((gslc_tsColor){32,0,0}),((gslc_tsColor){32,0,0}),((gslc_tsColor){32,0,0}));
   
  // Create E_ELEM_BOX4 box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_BOX4,E_PG_MAIN,(gslc_tsRect){240,140,80,100});
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  gslc_ElemSetCol(&m_gui,pElemRef,((gslc_tsColor){20,20,0}),((gslc_tsColor){20,20,0}),((gslc_tsColor){20,20,0}));
  
  // create E_ELEM_BTN1 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN1,E_PG_MAIN,
    (gslc_tsRect){245,145,70,40},(char*)"Alarmy",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // create E_ELEM_BTN2 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN2,E_PG_MAIN,
    (gslc_tsRect){245,195,70,40},(char*)"Ustawienia",0,E_BUILTIN5X8,&CbBtnCommon);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  
  // Create E_DAY text label
  static char m_sDAY[15] = "PONIEDZIALEK";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_DAY,E_PG_MAIN,(gslc_tsRect){124,10,71,15},
    m_sDAY,15,E_NOTOLATIN1_10PT);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  m_DAY = pElemRef;
  
  // Create E_SECONDS text label
  static char m_sSECONDS[3] = "58";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_SECONDS,E_PG_MAIN,(gslc_tsRect){251,75,22,15},
    m_sSECONDS,3,E_NOTOLATIN1_10PT);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_GREEN_DK4);
  m_SECONDS = pElemRef;
  
  // Create E_TIME text label
  static char m_sTIME[6] = "20:30";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_TIME,E_PG_MAIN,(gslc_tsRect){70,30,176,55},
    m_sTIME,6,E_NOTOLATIN1_36PT);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_GREEN_LT1);
  m_TIME = pElemRef;
  
  // Create E_DATE text label
  static char m_sDATE[11] = "07.02.2023";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_DATE,E_PG_MAIN,(gslc_tsRect){99,98,123,18},
    m_sDATE,11,E_NOTOLATIN1_12PT);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_GRAY_LT2);
  m_DATE = pElemRef;
  
  // Create E_ELEM_SUNRISE text label
  static char m_sSUNRISE[6] = "06:50";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_SUNRISE,E_PG_MAIN,(gslc_tsRect){105,160,31,10},
    m_sSUNRISE,6,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  m_SUNRISE = pElemRef;
  
  // Create E_ELEM_SUNSET text label
  static char m_sSUNSET[6] = "17:56";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_SUNSET,E_PG_MAIN,(gslc_tsRect){105,209,31,10},
    m_sSUNSET,6,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  m_SUNSET = pElemRef;
  
  // Create E_ELEM_TEMP text label
  static char m_sTEMP[7] = "20.1*C";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEMP,E_PG_MAIN,(gslc_tsRect){30,160,7,10},
    m_sTEMP,7,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  m_TEMP = pElemRef;
  
  // Create E_ELEM_HUM text label
  static char m_sHUM[6] = "50.2%";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_HUM,E_PG_MAIN,(gslc_tsRect){30,209,7,10},
    m_sHUM,6,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  m_HUM = pElemRef;
  
  // Create E_ELEM_PRESSURE text label
  static char m_sPRESSURE[8] = "1000hpa";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_PRESSURE,E_PG_MAIN,(gslc_tsRect){190,160,19,10},
    m_sPRESSURE,8,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  m_PRESSURE = pElemRef;
  
  // Create E_ELEM_AIRQ text label
  static char m_sAIRQ[9] = "10000ppm";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_AIRQ,E_PG_MAIN,(gslc_tsRect){190,209,19,10},
    m_sAIRQ,9,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  m_AIRQ = pElemRef;

  // Create E_DRAW_LINE1 line 
  pElemRef = gslc_ElemCreateLine(&m_gui,E_DRAW_LINE1,E_PG_MAIN,0,190,320,190);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLACK,GSLC_COL_BLACK,GSLC_COL_BLACK);

  // -----------------------------------
  // PAGE: E_PG_SETTINGS
  
   
  // Create E_ELEM_BOX5 box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_BOX5,E_PG_SETTINGS,(gslc_tsRect){9,9,302,222});
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY_DK2,GSLC_COL_GRAY_DK3,GSLC_COL_GRAY_DK3);
  
  // create E_ELEM_BTN3 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN3,E_PG_SETTINGS,
    (gslc_tsRect){20,20,280,40},(char*)"WIFI",0,E_BUILTIN5X8,&CbBtnCommon);
  
  // create E_ELEM_BTN4 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN4,E_PG_SETTINGS,
    (gslc_tsRect){240,185,60,40},(char*)"Cofnij",0,E_BUILTIN5X8,&CbBtnCommon);

  // -----------------------------------
  // PAGE: E_PG_WIFI
  
   
  // Create E_ELEM_BOX6 box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_BOX6,E_PG_WIFI,(gslc_tsRect){9,9,302,222});
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY_DK2,GSLC_COL_GRAY_DK3,GSLC_COL_GRAY_DK3);
  
  // create E_ELEM_BTN5 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN5,E_PG_WIFI,
    (gslc_tsRect){240,185,60,40},(char*)"Cofnij",0,E_BUILTIN5X8,&CbBtnCommon);
  
  // create E_ELEM_UP button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_UP,E_PG_WIFI,
    (gslc_tsRect){190,185,40,40},(char*)"/\\",0,E_BUILTIN5X8,&CbBtnCommon);
  
  // create E_ELEM_DOWN button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_DOWN,E_PG_WIFI,
    (gslc_tsRect){140,185,40,40},(char*)"\\/",0,E_BUILTIN5X8,&CbBtnCommon);
  
  // create E_ELEM_WIFI1 button with text label
  static char m_sWIFI1[30] = "";
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_WIFI1,E_PG_WIFI,
    (gslc_tsRect){20,15,280,24},m_sWIFI1,30,E_BUILTIN5X8,&CbBtnCommon);
  WIFI1 = pElemRef;
  
  // create E_ELEM_WIFI2 button with text label
  static char m_sWIFI2[30] = "";
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_WIFI2,E_PG_WIFI,
    (gslc_tsRect){20,49,280,24},m_sWIFI2,30,E_BUILTIN5X8,&CbBtnCommon);
  WIFI2 = pElemRef;
  
  // create E_ELEM_WIFI3 button with text label
  static char m_sWIFI3[30] = "";
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_WIFI3,E_PG_WIFI,
    (gslc_tsRect){20,83,280,24},m_sWIFI3,30,E_BUILTIN5X8,&CbBtnCommon);
  WIFI3 = pElemRef;
  
  // create E_ELEM_WIFI4 button with text label
  static char m_sWIFI4[30] = "";
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_WIFI4,E_PG_WIFI,
    (gslc_tsRect){20,117,280,24},m_sWIFI4,30,E_BUILTIN5X8,&CbBtnCommon);
  WIFI4 = pElemRef;
  
  // create E_ELEM_WIFI5 button with text label
  static char m_sWIFI5[30] = "";
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_WIFI5,E_PG_WIFI,
    (gslc_tsRect){20,151,280,24},m_sWIFI5,30,E_BUILTIN5X8,&CbBtnCommon);
  WIFI5 = pElemRef;
  
  // create E_BT_WIFI_REFRESH button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_BT_WIFI_REFRESH,E_PG_WIFI,
    (gslc_tsRect){20,185,110,40},(char*)"Odswiez",0,E_BUILTIN5X8,&CbBtnCommon);

  // -----------------------------------
  // PAGE: E_ALARMS
  
   
  // Create E_ELEM_BOX8 box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_BOX8,E_ALARMS,(gslc_tsRect){9,9,302,222});
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY_DK2,GSLC_COL_GRAY_DK3,GSLC_COL_GRAY_DK3);
  
  // create E_ELEM_BTN15 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN15,E_ALARMS,
    (gslc_tsRect){240,185,60,40},(char*)"Cofnij",0,E_BUILTIN5X8,&CbBtnCommon);
   
  // Create wrapping box for listbox E_ELEM_LISTBOX1 and scrollbar
  pElemRef = gslc_ElemCreateBox(&m_gui,GSLC_ID_AUTO,E_ALARMS,(gslc_tsRect){20,40,280,135});
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE,GSLC_COL_BLUE_DK4,GSLC_COL_TEAL);
  
  // Create listbox
  pElemRef = gslc_ElemXListboxCreate(&m_gui,E_ELEM_LISTBOX1,E_ALARMS,&m_sListbox1,
    (gslc_tsRect){20+2,40+4,280-4-30,135-7},E_BUILTIN5X8,
    (uint8_t*)&m_acListboxBuf1,sizeof(m_acListboxBuf1),0);
  gslc_ElemXListboxSetSize(&m_gui, pElemRef, 5, 1); // 5 rows, 1 columns
  gslc_ElemXListboxItemsSetSize(&m_gui, pElemRef, -1, 21);
  gslc_ElemSetTxtMarginXY(&m_gui, pElemRef, 5, 5);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE,GSLC_COL_BLUE_DK4,GSLC_COL_TEAL);
  gslc_ElemXListboxSetSelFunc(&m_gui, pElemRef, &CbListbox);
  gslc_ElemXListboxItemsSetGap(&m_gui, pElemRef, 5,GSLC_COL_BLACK);
  gslc_ElemXListboxAddItem(&m_gui, pElemRef, "OFF 10:00 PN WT SR CZ PT SB ND");
  gslc_ElemXListboxAddItem(&m_gui, pElemRef, "11f 10:00 PN WT SR CZ PT SB ND");
  gslc_ElemXListboxAddItem(&m_gui, pElemRef, "10f 10:00 PN WT SR CZ PT SB ND");
  gslc_ElemXListboxAddItem(&m_gui, pElemRef, "9FF 10:00 PN WT SR CZ PT SB ND");
  gslc_ElemXListboxAddItem(&m_gui, pElemRef, "8FF 10:00 PN WT SR CZ PT SB ND");
  gslc_ElemXListboxAddItem(&m_gui, pElemRef, "7FF 10:00 PN WT SR CZ PT SB ND");
  gslc_ElemXListboxAddItem(&m_gui, pElemRef, "6FF 10:00 PN WT SR CZ PT SB ND");
  gslc_ElemXListboxAddItem(&m_gui, pElemRef, "5FF 10:00 PN WT SR CZ PT SB ND");
  gslc_ElemXListboxAddItem(&m_gui, pElemRef, "4FF 10:00 PN WT SR CZ PT SB ND");
  gslc_ElemXListboxAddItem(&m_gui, pElemRef, "1FF 10:00 PN WT SR CZ PT SB ND");
  gslc_ElemXListboxAddItem(&m_gui, pElemRef, "aFF 10:00 PN WT SR CZ PT SB ND");
  gslc_ElemXListboxAddItem(&m_gui, pElemRef, "55F 10:00 PN WT SR CZ PT SB ND");
  gslc_ElemXListboxAddItem(&m_gui, pElemRef, "44F 10:00 PN WT SR CZ PT SB ND");
  gslc_ElemXListboxAddItem(&m_gui, pElemRef, "O3F 10:00 PN WT SR CZ PT SB ND");
  gslc_ElemXListboxAddItem(&m_gui, pElemRef, "OF2 10:00 PN WT SR CZ PT SB ND");
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  m_alarmList = pElemRef;

  // Create vertical scrollbar for listbox
  pElemRef = gslc_ElemXSliderCreate(&m_gui,E_LISTSCROLL1,E_ALARMS,&m_sListScroll1,
          (gslc_tsRect){20+280-2-30,40+4,30,135-8},0,20,0,7,true);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE,GSLC_COL_BLACK,GSLC_COL_BLUE);
  gslc_ElemXSliderSetPosFunc(&m_gui,pElemRef,&CbSlidePos);
  m_pListSlider1 = pElemRef;
  
  // create E_EDIT_ALARM button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_EDIT_ALARM,E_ALARMS,
    (gslc_tsRect){170,185,60,40},(char*)"Edytuj",0,E_BUILTIN5X8,&CbBtnCommon);
  
  // Create E_ELEM_TEXT36 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT36,E_ALARMS,(gslc_tsRect){33,13,253,26},
    (char*)"Lista Budzikow",0,E_BUILTIN15X24);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);

  // -----------------------------------
  // PAGE: E_PG_PASSWORD
  
   
  // Create E_ELEM_BOX9 box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_BOX9,E_PG_PASSWORD,(gslc_tsRect){20,20,280,200});
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_GRAY_DK1,GSLC_COL_GRAY_DK1);
  
  // create E_ELEM_BTN16 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN16,E_PG_PASSWORD,
    (gslc_tsRect){160,175,60,40},(char*)"Polacz",0,E_BUILTIN5X8,&CbBtnCommon);
  
  // create E_ELEM_BTN17 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN17,E_PG_PASSWORD,
    (gslc_tsRect){230,175,60,40},(char*)"Cofnij",0,E_BUILTIN5X8,&CbBtnCommon);
  
  // Create E_ELEM_TEXT4 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT4,E_PG_PASSWORD,(gslc_tsRect){40,40,61,18},
    (char*)"SSID:",0,E_BUILTIN10X16);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  
  // Create E_ELEM_TEXT5 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT5,E_PG_PASSWORD,(gslc_tsRect){40,65,109,18},
    (char*)"PASSWORD:",0,E_BUILTIN10X16);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  
  // Create E_ELEM_TEXT6 text label
  static char m_sSSID[30] = "";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT6,E_PG_PASSWORD,(gslc_tsRect){100,40,85,18},
    m_sSSID,30,E_BUILTIN10X16);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  m_SSID_TO_CONNECT = pElemRef;
  
  // Create E_ELEM_TEXTINPUT1 text input field
  static char m_sInputText1[12] = "";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXTINPUT1,E_PG_PASSWORD,(gslc_tsRect){150,65,140,18},
    (char*)m_sInputText1,12,E_BUILTIN10X16);
  gslc_ElemSetTxtMargin(&m_gui,pElemRef,5);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  gslc_ElemSetClickEn(&m_gui, pElemRef, true);
  gslc_ElemSetTouchFunc(&m_gui, pElemRef, &CbBtnCommon);
  m_pElemInTxt1 = pElemRef;
  
  // Create E_ELEM_TEXT18 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT18,E_PG_PASSWORD,(gslc_tsRect){40,90,37,18},
    (char*)"IP:",0,E_BUILTIN10X16);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  
  // Create E_ELEM_TEXT19 text label
  static char m_sIP[14] = "";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT19,E_PG_PASSWORD,(gslc_tsRect){80,90,49,18},
    m_sIP,14,E_BUILTIN10X16);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  m_IP = pElemRef;

  // -----------------------------------
  // PAGE: E_PG_WIFI_STATUS
  
   
  // Create E_ELEM_BOX10 box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_BOX10,E_PG_WIFI_STATUS,(gslc_tsRect){40,40,240,160});
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_GRAY_DK1,GSLC_COL_GRAY_DK1);
  
  // Create E_Conn_Status text label
  static char m_sWIFI_STATUS[30] = "";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_Conn_Status,E_PG_WIFI_STATUS,(gslc_tsRect){40,110,240,18},
    m_sWIFI_STATUS,30,E_NOTOLATIN1_12PT);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  m_Conn_Status = pElemRef;
  
  // create E_ELEM_BTN19 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN19,E_PG_WIFI_STATUS,
    (gslc_tsRect){210,150,60,40},(char*)"Cofnij",0,E_BUILTIN5X8,&CbBtnCommon);

  // -----------------------------------
  // PAGE: E_PG_EDIT_ALARM
  
   
  // Create E_ELEM_BOX12 box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_BOX12,E_PG_EDIT_ALARM,(gslc_tsRect){24,24,272,192});
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_GRAY_DK1,GSLC_COL_GRAY_DK1);
  
  // create E_ELEM_BTN24 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN24,E_PG_EDIT_ALARM,
    (gslc_tsRect){230,170,60,40},(char*)"Cofnij",0,E_BUILTIN5X8,&CbBtnCommon);
  
  // create E_ELEM_BTN25 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN25,E_PG_EDIT_ALARM,
    (gslc_tsRect){160,170,60,40},(char*)"Zapisz",0,E_BUILTIN5X8,&CbBtnCommon);
  
  // Create E_ELEM_NUMINPUT3 numeric input field
  static char m_sInputNumber3[3] = "";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_NUMINPUT3,E_PG_EDIT_ALARM,(gslc_tsRect){102,50,47,26},
    (char*)m_sInputNumber3,3,E_BUILTIN15X24);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtMargin(&m_gui,pElemRef,5);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  gslc_ElemSetClickEn(&m_gui, pElemRef, true);
  gslc_ElemSetTouchFunc(&m_gui, pElemRef, &CbBtnCommon);
  m_ALARM_HOUR = pElemRef;
  
  // Create E_ELEM_NUMINPUT4 numeric input field
  static char m_sInputNumber4[3] = "";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_NUMINPUT4,E_PG_EDIT_ALARM,(gslc_tsRect){167,50,47,26},
    (char*)m_sInputNumber4,3,E_BUILTIN15X24);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtMargin(&m_gui,pElemRef,5);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  gslc_ElemSetClickEn(&m_gui, pElemRef, true);
  gslc_ElemSetTouchFunc(&m_gui, pElemRef, &CbBtnCommon);
  m_ALARM_MIN = pElemRef;
  
  // Create toggle button E_ELEM_TOGGLE2
  pElemRef = gslc_ElemXTogglebtnCreate(&m_gui,E_ELEM_TOGGLE2,E_PG_EDIT_ALARM,&m_asXToggle2,
    (gslc_tsRect){230,50,40,26},GSLC_COL_GRAY_DK2,GSLC_COL_GREEN_DK3,GSLC_COL_GRAY_LT3,
    true,false,&CbBtnCommon);
  m_ALARM_TOGGLE = pElemRef;
   
  // create checkbox E_ELEM_CHECK9
  pElemRef = gslc_ElemXCheckboxCreate(&m_gui,E_ELEM_CHECK9,E_PG_EDIT_ALARM,&m_asXCheck9,
    (gslc_tsRect){110,80,20,20},false,GSLCX_CHECKBOX_STYLE_X,GSLC_COL_ORANGE,false);
  gslc_ElemXCheckboxSetStateFunc(&m_gui, pElemRef, &CbCheckbox);
  m_CHECK_PON = pElemRef;
  
  // Create E_ELEM_TEXT20 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT20,E_PG_EDIT_ALARM,(gslc_tsRect){30,80,73,20},
    (char*)"Poniedzialek",0,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_RIGHT);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
   
  // create checkbox E_ELEM_CHECK16
  pElemRef = gslc_ElemXCheckboxCreate(&m_gui,E_ELEM_CHECK16,E_PG_EDIT_ALARM,&m_asXCheck16,
    (gslc_tsRect){110,105,20,20},false,GSLCX_CHECKBOX_STYLE_X,GSLC_COL_ORANGE,false);
  gslc_ElemXCheckboxSetStateFunc(&m_gui, pElemRef, &CbCheckbox);
  m_CHECK_WT = pElemRef;
  
  // Create E_ELEM_TEXT28 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT28,E_PG_EDIT_ALARM,(gslc_tsRect){30,105,73,20},
    (char*)"Wtorek",0,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_RIGHT);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
   
  // create checkbox E_ELEM_CHECK17
  pElemRef = gslc_ElemXCheckboxCreate(&m_gui,E_ELEM_CHECK17,E_PG_EDIT_ALARM,&m_asXCheck17,
    (gslc_tsRect){110,130,20,20},false,GSLCX_CHECKBOX_STYLE_X,GSLC_COL_ORANGE,false);
  gslc_ElemXCheckboxSetStateFunc(&m_gui, pElemRef, &CbCheckbox);
  m_CHECK_SR = pElemRef;
  
  // Create E_ELEM_TEXT29 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT29,E_PG_EDIT_ALARM,(gslc_tsRect){30,130,73,20},
    (char*)"Sroda",0,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_RIGHT);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
   
  // create checkbox E_ELEM_CHECK18
  pElemRef = gslc_ElemXCheckboxCreate(&m_gui,E_ELEM_CHECK18,E_PG_EDIT_ALARM,&m_asXCheck18,
    (gslc_tsRect){218,81,20,20},false,GSLCX_CHECKBOX_STYLE_X,GSLC_COL_ORANGE,false);
  gslc_ElemXCheckboxSetStateFunc(&m_gui, pElemRef, &CbCheckbox);
  m_CHECK_PT = pElemRef;
  
  // Create E_ELEM_TEXT30 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT30,E_PG_EDIT_ALARM,(gslc_tsRect){138,81,73,20},
    (char*)"Piatek",0,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_RIGHT);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
   
  // create checkbox E_ELEM_CHECK19
  pElemRef = gslc_ElemXCheckboxCreate(&m_gui,E_ELEM_CHECK19,E_PG_EDIT_ALARM,&m_asXCheck19,
    (gslc_tsRect){217,106,20,20},false,GSLCX_CHECKBOX_STYLE_X,GSLC_COL_ORANGE,false);
  gslc_ElemXCheckboxSetStateFunc(&m_gui, pElemRef, &CbCheckbox);
  m_CHECK_SB = pElemRef;
  
  // Create E_ELEM_TEXT31 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT31,E_PG_EDIT_ALARM,(gslc_tsRect){137,106,73,20},
    (char*)"Sobota",0,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_RIGHT);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_ORANGE);
   
  // create checkbox E_ELEM_CHECK20
  pElemRef = gslc_ElemXCheckboxCreate(&m_gui,E_ELEM_CHECK20,E_PG_EDIT_ALARM,&m_asXCheck20,
    (gslc_tsRect){217,133,20,20},false,GSLCX_CHECKBOX_STYLE_X,GSLC_COL_ORANGE,false);
  gslc_ElemXCheckboxSetStateFunc(&m_gui, pElemRef, &CbCheckbox);
  m_CHECK_ND = pElemRef;
  
  // Create E_ELEM_TEXT32 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT32,E_PG_EDIT_ALARM,(gslc_tsRect){137,133,73,20},
    (char*)"Niedziela",0,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_RIGHT);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_ORANGE);
   
  // create checkbox E_ELEM_CHECK21
  pElemRef = gslc_ElemXCheckboxCreate(&m_gui,E_ELEM_CHECK21,E_PG_EDIT_ALARM,&m_asXCheck21,
    (gslc_tsRect){111,156,20,20},false,GSLCX_CHECKBOX_STYLE_X,GSLC_COL_ORANGE,false);
  gslc_ElemXCheckboxSetStateFunc(&m_gui, pElemRef, &CbCheckbox);
  m_CHECK_CZW = pElemRef;
  
  // Create E_ELEM_TEXT33 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT33,E_PG_EDIT_ALARM,(gslc_tsRect){31,156,73,20},
    (char*)"Czwartek",0,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_RIGHT);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  
  // Create E_ELEM_TEXT34 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT34,E_PG_EDIT_ALARM,(gslc_tsRect){117,28,85,18},
    (char*)"GODZINA",0,E_BUILTIN10X16);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_GREEN_LT1);
  
  // Create E_ELEM_TEXT35 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT35,E_PG_EDIT_ALARM,(gslc_tsRect){147,48,25,34},
    (char*)":",0,E_BUILTIN20X32);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);

  // -----------------------------------
  // PAGE: E_POP_KEYPAD_NUM
  
  static gslc_tsXKeyPadCfg_Num sCfg;
  sCfg = gslc_ElemXKeyPadCfgInit_Num();
  gslc_ElemXKeyPadCfgSetFloatEn_Num(&sCfg, true);
  gslc_ElemXKeyPadCfgSetSignEn_Num(&sCfg, true);
  m_pElemKeyPadNum = gslc_ElemXKeyPadCreate_Num(&m_gui, E_ELEM_KEYPAD_NUM, E_POP_KEYPAD_NUM,
    &m_sKeyPadNum, 65, 80, E_BUILTIN5X8, &sCfg);
  gslc_ElemXKeyPadValSetCb(&m_gui, m_pElemKeyPadNum, &CbKeypad);

  // -----------------------------------
  // PAGE: E_POP_KEYPAD_ALPHA
  
  static gslc_tsXKeyPadCfg_Alpha sCfgTx;
  sCfgTx = gslc_ElemXKeyPadCfgInit_Alpha();
  m_pElemKeyPadAlpha = gslc_ElemXKeyPadCreate_Alpha(&m_gui, E_ELEM_KEYPAD_ALPHA, E_POP_KEYPAD_ALPHA,
    &m_sKeyPadAlpha, 65, 80, E_BUILTIN5X8, &sCfgTx);
  gslc_ElemXKeyPadValSetCb(&m_gui, m_pElemKeyPadAlpha, &CbKeypad);
//<InitGUI !End!>

//<Startup !Start!>
//<Startup !End!>

}

#endif // end _GUISLICE_GEN_H
