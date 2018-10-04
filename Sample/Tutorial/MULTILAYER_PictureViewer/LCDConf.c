/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2015  SEGGER Microcontroller GmbH & Co. KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.30 - Graphical user interface for embedded applications **
emWin is protected by international copyright laws.   Knowledge of the
source code may not be used to write a similar product.  This file may
only  be used  in accordance  with  a license  and should  not be  re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : LCDConf.c
Purpose     : Sample configuration for picture viewer sample
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI.h"

/*********************************************************************
*
*       Supported color modes (not to be changed)
*/
//      Color mode       Conversion     Driver (default orientation)
//      ---------------------------------------------
#define CM_ARGB8888 1 // GUICC_M8888I - GUIDRV_LIN_32
#define CM_RGB888   2 // GUICC_M888   - GUIDRV_LIN_24
#define CM_RGB565   3 // GUICC_M565   - GUIDRV_LIN_16
#define CM_ARGB1555 4 // GUICC_M1555I - GUIDRV_LIN_16
#define CM_ARGB4444 5 // GUICC_M4444I - GUIDRV_LIN_16
#define CM_L8       6 // GUICC_8666   - GUIDRV_LIN_8
#define CM_AL44     7 // GUICC_1616I  - GUIDRV_LIN_8
#define CM_AL88     8 // GUICC_88666I - GUIDRV_LIN_16

/*********************************************************************
**********************************************************************
*
*       DISPLAY CONFIGURATION START (TO BE MODIFIED)
*
**********************************************************************
**********************************************************************
*/
/*********************************************************************
*
*       Common
*/
//
// Physical display size
//
#define XSIZE_PHYS 480
#define YSIZE_PHYS 272

//
// Buffers / VScreens
//
#define NUM_BUFFERS  3 // Number of multiple buffers to be used (at least 1 buffer)
#define NUM_VSCREENS 1 // Number of virtual  screens to be used (at least 1 screen)

//
// Redefine number of layers for this configuration file. Must be equal or less than in GUIConf.h!
//
#undef  GUI_NUM_LAYERS
#define GUI_NUM_LAYERS 2

/*********************************************************************
*
*       Layer 0
*/
//
// Color mode layer 0. Should be one of the above defined color modes
//
#define COLOR_MODE_0 CM_ARGB8888

//
// Size of layer 0. Ignored and replaced by XSIZE_PHYS and YSIZE_PHYS if GUI_NUM_LAYERS == 1
//
#define XSIZE_0 480
#define YSIZE_0 272

/*********************************************************************
*
*       Layer 1
*/
//
// Color mode layer 1. Should be one of the above defined color modes
//
#define COLOR_MODE_1 CM_ARGB8888

//
// Size of layer 1
//
#define XSIZE_1 480
#define YSIZE_1 272

/*********************************************************************
**********************************************************************
*
*       DISPLAY CONFIGURATION END
*
**********************************************************************
**********************************************************************
*/
/*********************************************************************
*
*       Automatic selection of color conversion
*/
#if   (COLOR_MODE_0 == CM_ARGB8888)
  #define COLOR_CONVERSION_0 GUICC_M8888I
#elif (COLOR_MODE_0 == CM_RGB888)
  #define COLOR_CONVERSION_0 GUICC_M888
#elif (COLOR_MODE_0 == CM_RGB565)
  #define COLOR_CONVERSION_0 GUICC_M565
#elif (COLOR_MODE_0 == CM_ARGB1555)
  #define COLOR_CONVERSION_0 GUICC_M1555I
#elif (COLOR_MODE_0 == CM_ARGB4444)
  #define COLOR_CONVERSION_0 GUICC_M4444I
#elif (COLOR_MODE_0 == CM_L8)
  #define COLOR_CONVERSION_0 GUICC_8666
#elif (COLOR_MODE_0 == CM_AL44)
  #define COLOR_CONVERSION_0 GUICC_1616I
#elif (COLOR_MODE_0 == CM_AL88)
  #define COLOR_CONVERSION_0 GUICC_88666I
#else
  #error Illegal color mode 0!
#endif

#if (GUI_NUM_LAYERS > 1)

#if   (COLOR_MODE_1 == CM_ARGB8888)
  #define COLOR_CONVERSION_1 GUICC_M8888I
#elif (COLOR_MODE_1 == CM_RGB888)
  #define COLOR_CONVERSION_1 GUICC_M888
#elif (COLOR_MODE_1 == CM_RGB565)
  #define COLOR_CONVERSION_1 GUICC_M565
#elif (COLOR_MODE_1 == CM_ARGB1555)
  #define COLOR_CONVERSION_1 GUICC_M1555I
#elif (COLOR_MODE_1 == CM_ARGB4444)
  #define COLOR_CONVERSION_1 GUICC_M4444I
#elif (COLOR_MODE_1 == CM_L8)
  #define COLOR_CONVERSION_1 GUICC_8666
#elif (COLOR_MODE_1 == CM_AL44)
  #define COLOR_CONVERSION_1 GUICC_1616I
#elif (COLOR_MODE_1 == CM_AL88)
  #define COLOR_CONVERSION_1 GUICC_88666I
#else
  #error Illegal color mode 0!
#endif

#else

/*********************************************************************
*
*       Use complete display automatically in case of only one layer
*/
#undef XSIZE_0
#undef YSIZE_0
#define XSIZE_0 XSIZE_PHYS
#define YSIZE_0 YSIZE_PHYS

#endif

/*********************************************************************
*
*       Configuration checking
*/
#if NUM_BUFFERS > 3
  #error More than 3 buffers make no sense and are not supported in this configuration file!
#endif
#ifndef   XSIZE_PHYS
  #error Physical X size of display is not defined!
#endif
#ifndef   YSIZE_PHYS
  #error Physical Y size of display is not defined!
#endif
#ifndef   NUM_BUFFERS
  #define NUM_BUFFERS 1
#else
  #if (NUM_BUFFERS <= 0)
    #error At least one buffer needs to be defined!
  #endif
#endif
#ifndef   NUM_VSCREENS
  #define NUM_VSCREENS 1
#else
  #if (NUM_VSCREENS <= 0)
    #error At least one screeen needs to be defined!
  #endif
#endif
#if (NUM_VSCREENS > 1) && (NUM_BUFFERS > 1)
  #error Virtual screens together with multiple buffers are not allowed!
#endif

#define DISPLAY_DRIVER_0 GUIDRV_WIN32
#define DISPLAY_DRIVER_1 GUIDRV_WIN32

/*********************************************************************
*
*       Public code (WIN32)
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_X_DisplayDriver
*
* Purpose:
*   This function is called by the display driver for several purposes.
*   To support the according task the routine needs to be adapted to
*   the display controller. Please note that the commands marked with
*   'optional' are not cogently required and should only be adapted if
*   the display controller supports these features.
*
* Parameter:
*   LayerIndex - Index of layer to be configured
*   Cmd        - Please refer to the details in the switch statement below
*   pData      - Pointer to a LCD_X_DATA structure
*
* Return Value:
*   < -1 - Error
*     -1 - Command not handled
*      0 - Ok
*/
int LCD_X_DisplayDriver(unsigned LayerIndex, unsigned Cmd, void * pData) {
  int r;
  switch (Cmd) {
  case LCD_X_INITCONTROLLER:
    r = 0;
  default:
    r = -1;
  }
  return r;
}

/*********************************************************************
*
*       LCD_X_Config
*
* Purpose:
*   Called during the initialization process in order to set up the
*   display driver configuration.
*
*/
void LCD_X_Config(void) {
  #if (NUM_BUFFERS > 1)
  int i;

  for (i = 0; i < GUI_NUM_LAYERS; i++) {
    GUI_MULTIBUF_ConfigEx(i, NUM_BUFFERS);
  }
  #endif
  //
  // Set display driver and color conversion for 1st layer
  //
  GUI_DEVICE_CreateAndLink(DISPLAY_DRIVER_0, COLOR_CONVERSION_0, 0, 0);
  //
  // Set size of 1st layer
  //
  if (LCD_GetSwapXYEx(0)) {
    LCD_SetSizeEx (0, YSIZE_0, XSIZE_0);
    LCD_SetVSizeEx(0, YSIZE_0 * NUM_VSCREENS, XSIZE_0);
  } else {
    LCD_SetSizeEx (0, XSIZE_0, YSIZE_0);
    LCD_SetVSizeEx(0, XSIZE_0, YSIZE_0 * NUM_VSCREENS);
  }
  LCD_SetVisEx(0, 1);
  #if (GUI_NUM_LAYERS > 1)
    //
    // Set display driver and color conversion for 2nd layer
    //
    GUI_DEVICE_CreateAndLink(DISPLAY_DRIVER_1, COLOR_CONVERSION_1, 0, 1);
    //
    // Set size of 2nd layer
    //
    if (LCD_GetSwapXYEx(1)) {
      LCD_SetSizeEx (1, YSIZE_0, XSIZE_1);
      LCD_SetVSizeEx(1, YSIZE_1 * NUM_VSCREENS, XSIZE_1);
    } else {
      LCD_SetSizeEx (1, XSIZE_1, YSIZE_1);
      LCD_SetVSizeEx(1, XSIZE_1, YSIZE_1 * NUM_VSCREENS);
    }
    LCD_SetVisEx(1, 1);
  #endif
}

/*************************** End of file ****************************/
