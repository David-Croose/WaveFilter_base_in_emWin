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
File        : BASIC_DrawingRects.c
Purpose     : Filling screen with random rectangles
Requirements: WindowManager - ( )
              MemoryDevices - ( )
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )
----------------------------------------------------------------------
*/

#include <stdlib.h>
#include "GUI.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
//
// Recommended memory to run the sample with adequate performance
//
#define RECOMMENDED_MEMORY (1024L * 5)

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       MainTask
*/
void MainTask(void) {
  const U32 aColor[] = {
    GUI_BLUE        ,    GUI_GREEN       ,    GUI_RED         ,    GUI_CYAN        ,    GUI_MAGENTA     ,    GUI_YELLOW      ,
    GUI_LIGHTBLUE   ,    GUI_LIGHTGREEN  ,    GUI_LIGHTRED    ,    GUI_LIGHTCYAN   ,    GUI_LIGHTMAGENTA,    GUI_LIGHTYELLOW ,
    GUI_DARKBLUE    ,    GUI_DARKGREEN   ,    GUI_DARKRED     ,    GUI_DARKCYAN    ,    GUI_DARKMAGENTA ,    GUI_DARKYELLOW  ,
  };
  int x0;
  int y0;
  int Index;
  int xSize;
  int ySize;
  int xSizeRect;
  int ySizeRect;

  GUI_Init();
  //
  // Check if recommended memory for the sample is available
  //
  if (GUI_ALLOC_GetNumFreeBytes() < RECOMMENDED_MEMORY) {
    GUI_ErrorOut("Not enough memory available."); 
    return;
  }
  xSize = LCD_GetXSize();
  ySize = LCD_GetYSize();
  while (1) {
    x0 = rand() % xSize;
    y0 = rand() % ySize;
    xSizeRect = rand() % (xSize - x0);
    ySizeRect = rand() % (ySize - y0);
    Index = (unsigned)rand() % GUI_COUNTOF(aColor);
    GUI_SetColor(aColor[Index]);
    GUI_FillRect(x0, y0, x0 + xSizeRect - 1, y0 + ySizeRect - 1);
  }
}

/*************************** End of file ****************************/
