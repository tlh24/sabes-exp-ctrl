// CP_OptoTrack.cpp : Implementation of WinMain


#define _WIN32_DCOM

#include <windows.h>
#include <wingdi.h>
#include <objbase.h>
#include <initguid.h>

#include "OptoTrackGlob.h"
#include "CP_printf.h"


#include "resource.h"  // Generated on every build


#define TIMER_ID 1
#define TIMER_PERIOD_MS 100    // 10 Hz rate

#define INVALID_FLOAT  ((float)-3.0E28)   // from the NDI include
#define DIST_LEVEL_MAX   2  // don't print coords if distortion is high (>=2)
// in mm
#define RAW_MIN_X -400.0f
#define RAW_MAX_X 400.0f

#define RAW_MIN_Y -300.0f
#define RAW_MAX_Y 300.0f

// in pix
#define WIN_SIZE_X 400
#define WIN_SIZE_Y 300

char * g_szVersion = "CP_OptoTrack: Ver 0.01 July 29th, 2008";

char * x_szTitle = "CP_OptoTrack";
char * x_szMutexName = "CP_OptoTrack_Application_Mutex";

HINSTANCE x_hInstance;

COLORREF x_atMarkerColors[N_DISPL_SENSORS] = { 
    RGB( 0xff,    0,    0),    // Red
    RGB(    0, 0xff,    0),    // green
    RGB( 0xff, 0xff,    0),    // yellow
    RGB(    0, 0xff, 0xff)     // cyan
};

COLORREF x_atDistortionColors[4] = { 
    RGB(    0, 0xff,    0),    // green
    RGB( 0xff, 0xff,    0),    // yellow
    RGB( 0xff,    0,    0),    // Red
    RGB(    0,    0,    0)     // black
};


//---------------------------------------------
// for command-line processing
LPCTSTR FindOneOf(LPCTSTR p1, LPCTSTR p2){  
    while (p1 != NULL && *p1 != NULL)
    {
        LPCTSTR p = p2;
        while (p != NULL && *p != NULL)
        {
            if (*p1 == *p)
                return CharNext(p1);
            p = CharNext(p);
        }
        p1 = CharNext(p1);
    }
    return NULL;
}

//----------------------------------------------
void PrintCoord( HWND hDlgWnd, double dCoord, int iLabelID ){
  char szTmp[100];
              
  sprintf(szTmp, "%.1f", dCoord );
  SetWindowText(GetDlgItem(hDlgWnd, iLabelID ), szTmp);
}


//----------------------------------------------
void DrawDistortionBox( HWND hDlgWnd, COLORREF tColor, int iPicID ){
  HWND hPic;
  HDC hDC;
  HBRUSH hBrush; 
  RECT recClnt;

  hPic = GetDlgItem(hDlgWnd, iPicID);
  GetClientRect( hPic, &recClnt );

  hDC = GetDC(hPic);
  hBrush = CreateSolidBrush( tColor );
  SelectObject(hDC, hBrush);
  Rectangle( hDC, recClnt.left, recClnt.top, 
                  recClnt.right , recClnt.bottom );
  DeleteObject(hBrush);
  ReleaseDC(hPic, hDC); 


}
//----------------------------------------------
void DrawCross( HDC hDC, COLORREF color, int iCentX, int iCentY ){
  HPEN hPen;

  hPen = CreatePen( PS_SOLID, 1, color );
  SelectObject(hDC, hPen);
  MoveToEx( hDC, iCentX - 10, iCentY, NULL);
  LineTo( hDC, iCentX + 10, iCentY);
  MoveToEx( hDC, iCentX, iCentY-10, NULL);
  LineTo( hDC, iCentX, iCentY + 10);
  DeleteObject( hPen );

}

//----------------------------------------------
// Display current sensor position
void OnTimer( HWND hDlgWnd ){
  static int iRectIsClean = 0;
  int iFrame;
  double dT_ms;
  double adXYZ[N_DISPL_SENSORS][N_DISPL_COORD];
  int aiDistortion[N_DISPL_SENSORS];
  HWND hPic;
  HDC hDC, hBitmapDC;
  HBITMAP hBitmap;
  RECT recClnt;
  int iSensor;
  int iOffsetX, iOffsetY;
  int iW, iH;
  int nSensors;
  double dSensX, dSensY;
  double dX, dY;
  char szTmp[100];

  ZeroMemory(adXYZ, sizeof(adXYZ));
  hPic = GetDlgItem(hDlgWnd, IDC_PICTURE);
  GetClientRect( hPic, &recClnt );
  if( g_GetLatestCoordinates( N_DISPL_SENSORS, &nSensors, &iFrame, &dT_ms, (double *)adXYZ ) ) {
    if( !iRectIsClean ) {
      // No valid coordinates - not running
      InvalidateRect( hDlgWnd, &recClnt, TRUE );
      // Print timestamp
      SetWindowText(GetDlgItem(hDlgWnd, IDC_LBL_TIME ), "N/A");
      // Print frame
      SetWindowText(GetDlgItem(hDlgWnd, IDC_LBL_IFRAME ), "N/A");
      iRectIsClean = 1;
    }
  }
  else {
    iRectIsClean = 0;
    iW = (recClnt.right - recClnt.left);
    iH = (recClnt.bottom - recClnt.top);
    iOffsetX = (iW - WIN_SIZE_X)/2;
    iOffsetY = (iH - WIN_SIZE_Y)/2;
    hDC = GetDC(hPic);

    // to avoid flicker we draw on the off-screen bitmap and then copy it to the screen
    hBitmapDC = CreateCompatibleDC ( hDC );
    hBitmap = CreateCompatibleBitmap ( hDC, iW, iH );
    SelectObject ( hBitmapDC, hBitmap ); // map DC to the off-screen bitmap
    // Black backgound
    SelectObject( hBitmapDC, GetStockObject( BLACK_BRUSH ));
    Rectangle( hBitmapDC, recClnt.left, recClnt.top, 
                          recClnt.right, recClnt.bottom);
    // White box
    SelectObject( hBitmapDC, GetStockObject( WHITE_PEN ));
    Rectangle( hBitmapDC, iOffsetX, iOffsetY, 
                          WIN_SIZE_X+iOffsetX, WIN_SIZE_Y+iOffsetY );

    for( iSensor = 0; iSensor < nSensors; iSensor++){
      dSensX = adXYZ[iSensor][0];
      dSensY = adXYZ[iSensor][1];
      // normalize coordinates to 0-1 
      dX = (dSensX - RAW_MIN_X)/ (RAW_MAX_X - RAW_MIN_X);  
      dY = (RAW_MAX_Y - dSensY)/ (RAW_MAX_Y - RAW_MIN_Y);  // make Y axis bottom->top

      // clip coordinates
      if(dX < 0) dX = 0;
      if(dX > 1) dX = 1;
      if(dY < 0) dY = 0;
      if(dY > 1) dY = 1;

      DrawCross( hBitmapDC, x_atMarkerColors[iSensor],
                (int)(dX*WIN_SIZE_X) + iOffsetX,  
                (int)(dY*WIN_SIZE_Y) + iOffsetY  );
    } // for all sensors

    // Draw bitmap
    BitBlt(hDC, recClnt.left, recClnt.top, iW, iH, 
           hBitmapDC, 0, 0, SRCCOPY);

    DeleteObject(hBitmap);
    DeleteDC(hBitmapDC);
    ReleaseDC(hPic, hDC); 

    // Print timestamp
    sprintf(szTmp, "%.2f", dT_ms/1000.0);
    SetWindowText(GetDlgItem(hDlgWnd, IDC_LBL_TIME ), szTmp);
    // Print frame
    sprintf(szTmp, "%d", iFrame);
    SetWindowText(GetDlgItem(hDlgWnd, IDC_LBL_IFRAME ), szTmp);
  }

  // Draw distortion LEDs and print coordinates
  g_GetSignalDistortion( aiDistortion );

  DrawDistortionBox( hDlgWnd, x_atDistortionColors[aiDistortion[0]],  IDC_PIC_SENS1);
  DrawDistortionBox( hDlgWnd, x_atDistortionColors[aiDistortion[1]],  IDC_PIC_SENS2);
  DrawDistortionBox( hDlgWnd, x_atDistortionColors[aiDistortion[2]],  IDC_PIC_SENS3);
  DrawDistortionBox( hDlgWnd, x_atDistortionColors[aiDistortion[3]],  IDC_PIC_SENS4);

  // Print coordinates
  if(aiDistortion[0] < DIST_LEVEL_MAX ){
    PrintCoord(hDlgWnd, adXYZ[0][0], IDC_LBL_X1);
    PrintCoord(hDlgWnd, adXYZ[0][1], IDC_LBL_Y1);
    PrintCoord(hDlgWnd, adXYZ[0][2], IDC_LBL_Z1);
  }
  else{
    SetWindowText(GetDlgItem(hDlgWnd, IDC_LBL_X1 ), "N/A");
    SetWindowText(GetDlgItem(hDlgWnd, IDC_LBL_Y1 ), "N/A");
    SetWindowText(GetDlgItem(hDlgWnd, IDC_LBL_Z1 ), "N/A");
  }

  if(aiDistortion[1] < DIST_LEVEL_MAX ){
    PrintCoord(hDlgWnd, adXYZ[1][0], IDC_LBL_X2);
    PrintCoord(hDlgWnd, adXYZ[1][1], IDC_LBL_Y2);
    PrintCoord(hDlgWnd, adXYZ[1][2], IDC_LBL_Z2);
  }
  else{
    SetWindowText(GetDlgItem(hDlgWnd, IDC_LBL_X2 ), "N/A");
    SetWindowText(GetDlgItem(hDlgWnd, IDC_LBL_Y2 ), "N/A");
    SetWindowText(GetDlgItem(hDlgWnd, IDC_LBL_Z2 ), "N/A");
  }

  if(aiDistortion[2] < DIST_LEVEL_MAX ){
    PrintCoord(hDlgWnd, adXYZ[2][0], IDC_LBL_X3);
    PrintCoord(hDlgWnd, adXYZ[2][1], IDC_LBL_Y3);
    PrintCoord(hDlgWnd, adXYZ[2][2], IDC_LBL_Z3);
  }
  else{
    SetWindowText(GetDlgItem(hDlgWnd, IDC_LBL_X3 ), "N/A");
    SetWindowText(GetDlgItem(hDlgWnd, IDC_LBL_Y3 ), "N/A");
    SetWindowText(GetDlgItem(hDlgWnd, IDC_LBL_Z3 ), "N/A");
  }

  if(aiDistortion[3] < DIST_LEVEL_MAX ){
    PrintCoord(hDlgWnd, adXYZ[3][0], IDC_LBL_X4);
    PrintCoord(hDlgWnd, adXYZ[3][1], IDC_LBL_Y4);
    PrintCoord(hDlgWnd, adXYZ[3][2], IDC_LBL_Z4);
  }
  else{
    SetWindowText(GetDlgItem(hDlgWnd, IDC_LBL_X4 ), "N/A");
    SetWindowText(GetDlgItem(hDlgWnd, IDC_LBL_Y4 ), "N/A");
    SetWindowText(GetDlgItem(hDlgWnd, IDC_LBL_Z4 ), "N/A");
  }


}

//----------------------------------------------------------------------
BOOL CALLBACK x_DialogProc(HWND hDlgWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam) { 
  UINT uiTimerID; 
  int iRes;
 
  switch (uiMsg) {

    case WM_COMMAND: 
      if (HIWORD(wParam) == BN_CLICKED) { 
        switch (LOWORD(wParam)) { 
          case IDC_CMD_EXIT:  // Exit button
            PostMessage( hDlgWnd, WM_CLOSE, 0, 0);
            return TRUE;
          case IDC_CMD_START:  // Start button
            g_CmdStart();
            return TRUE;
          case IDC_CMD_STOP:  // Stop button
            g_CmdStop();
            return TRUE;

          // Hide/show log window
          case IDC_CHK_SHOWLOG: 
            // Retrieve the state of the check box. 
            iRes = SendDlgItemMessage( hDlgWnd, IDC_CHK_SHOWLOG, BM_GETCHECK, 0, 0); 
            if( iRes == BST_CHECKED ) CP_printfShow();
            if( iRes == BST_UNCHECKED ) CP_printfHide();
            return TRUE; 

        } // switch
      }  // if BN_CLICKED
      break;

    case WM_TIMER:
      OnTimer( hDlgWnd );
      return TRUE;

    case WM_DESTROY:
      PostQuitMessage(0);
      return TRUE;

    case WM_CLOSE:
      KillTimer( hDlgWnd, TIMER_ID);
      g_Release_OptoTrack();
      DestroyWindow (hDlgWnd);
      return TRUE;

    case WM_INITDIALOG:
      g_hWnd = hDlgWnd;

      SetWindowText(hDlgWnd, x_szTitle);
      SendMessage(hDlgWnd, WM_SETICON, ICON_BIG, 
                  (LPARAM)LoadIcon(x_hInstance, MAKEINTRESOURCE(IDI_ICON_APPL)));
      SendMessage(hDlgWnd, WM_SETICON, ICON_SMALL, 
                 (LPARAM)LoadImage(x_hInstance, MAKEINTRESOURCE(IDI_ICON_APPL), IMAGE_ICON, 16, 16, 0));
      ShowWindow(hDlgWnd, SW_SHOW); 
  
      uiTimerID = SetTimer( hDlgWnd,  TIMER_ID,  TIMER_PERIOD_MS,  NULL ); 
 
      if ( uiTimerID == 0){ 
        CP_printf("Error: could not create timer!"); // don't exit we are still functional
      } 

      iRes = g_Init_OptoTrack( );
      if( iRes != 0 ) { 
        MessageBox( NULL, "Error: g_Init_OptoTrack() failed.", x_szTitle, MB_OK);
        PostMessage( hDlgWnd, WM_CLOSE, 0, 0);
        return TRUE;
      }

      return TRUE;
  } // switch (uiMsg)

  return FALSE;       // did not process a message 
} 
//============================================================================================
//   MAIN
//============================================================================================
extern "C" int WINAPI WinMain(  HINSTANCE hInstance,      // handle to current instance
                                HINSTANCE hPrevInstance,  // handle to previous instance
                                LPSTR lpCmdLine,          // command line
                                int nCmdShow   ){         // show state

  HANDLE hMutex;
  TCHAR szTokens[] = "-/";
  LPCTSTR lpszToken;
  int iRes;
  HRESULT hRes;

  x_hInstance = hInstance;

  // Check for another instance
  hMutex = OpenMutex( SYNCHRONIZE,  // requested access (lowest possible)
                      FALSE,  // allow inheritance (does not matter)
                      x_szMutexName);  // unique name

  if(hMutex){
    MessageBox( NULL, "Cannot start the application because another instance is already running.\n", 
                x_szTitle, MB_OK | MB_ICONERROR );
    return 1;
  }

  hMutex = CreateMutex( NULL,  // default security
                        TRUE,  // obtain ownership
                        x_szMutexName);  // unique name
  if(!hMutex){
    MessageBox( NULL, "Cannot create application mutex.\n", 
                x_szTitle, MB_OK | MB_ICONERROR );
    return 1;
  }


  // Parse the command line for options
  lpszToken = FindOneOf(lpCmdLine, szTokens);
  while (lpszToken != NULL) {
    if (lstrcmpi(lpszToken, "UnregServer")==0) {
      iRes = g_UnregisterCOM();
      if( iRes != 0 ) { 
        MessageBox( NULL, "Error: Can't unregister server. g_UnregisterCOM() failed.", x_szTitle, MB_OK);
      }
      else {
        MessageBox( NULL, "Success: the server is unregistered.", x_szTitle, MB_OK);
      }
      return iRes;
    }
    if (lstrcmpi(lpszToken, "RegServer")==0) {
      iRes = g_RegisterCOM();
      if( iRes != 0 ) { 
        MessageBox( NULL, "Error: Can't register server. g_RegisterCOM() failed.", x_szTitle, MB_OK);
      }
      else {
        MessageBox( NULL, "Success: the server is registered.", x_szTitle, MB_OK);
      }
      return iRes;
    }
    lpszToken = FindOneOf(lpszToken, szTokens);
  } // while there are tokens

//-------  Regular run starts here
  // Init COM using single-threaded model
  hRes = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED); 
  if( hRes != S_OK) { 
    MessageBox( NULL, "Error in CoInitializeEx()", x_szTitle, MB_OK);
    return 1;
  }
  
  CP_printfCreate(x_szTitle); // create console window
  CP_printf(g_szVersion);
  CP_printf("\n\n");
  CP_printfHide(); // hide console window

  //-------  Windows main loop is here
  DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAIN_DIALOG), NULL, x_DialogProc); 

  CP_printfDestroy();
	CoUninitialize();

  return 0;
}
