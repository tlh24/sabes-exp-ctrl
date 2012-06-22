// CP_LibertyTrack.cpp : Implementation of WinMain


#define _WIN32_DCOM

#include <windows.h>
#include <wingdi.h>
#include <objbase.h>
#include <initguid.h>

#include "LibertyTrackGlob.h"
#include "CP_printf.h"
#include "Liberty\PDI.h"

// Includes below are generated on every build
#include "resource.h"


#define TIMER_ID 1
#define TIMER_PERIOD_MS 100    // 10 Hz rate


// in mm
#define RAW_MIN_X -400.0f
#define RAW_MAX_X 400.0f

#define RAW_MIN_Y -300.0f
#define RAW_MAX_Y 300.0f

#define WIN_SIZE_X 400
#define WIN_SIZE_Y 300

char * g_szVersion = "CP_LibertyTrack: Ver 0.04 February 21st, 2008";

char * x_szTitle = "CP_LibertyTrack";
char x_szMutexName[] = "CP_LibertyTrack_Application_Mutex";


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
              
//  if( fCoord < INVALID_FLOAT ) { 
//    sprintf(szTmp, "N/A");
//  }
//  else {
    sprintf(szTmp, "%.1f", dCoord );
//  }

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
  int iFrame;
  double dT_ms;
  double adXYZ[N_DISPL_SENSORS][N_COORD_ANGL];
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
  if( g_GetLatestCoordinates( &nSensors, &iFrame, &dT_ms, adXYZ ) ) return; 
  g_GetSignalDistortion( aiDistortion );

  hPic = GetDlgItem(hDlgWnd, IDC_PICTURE);
  GetClientRect( hPic, &recClnt );

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

  DrawDistortionBox( hDlgWnd, x_atDistortionColors[aiDistortion[0]],  IDC_PIC_SENS1);
  DrawDistortionBox( hDlgWnd, x_atDistortionColors[aiDistortion[1]],  IDC_PIC_SENS2);
  DrawDistortionBox( hDlgWnd, x_atDistortionColors[aiDistortion[2]],  IDC_PIC_SENS3);
  DrawDistortionBox( hDlgWnd, x_atDistortionColors[aiDistortion[3]],  IDC_PIC_SENS4);

  // Print timestamp
  sprintf(szTmp, "%.2f", dT_ms/1000.0);
  SetWindowText(GetDlgItem(hDlgWnd, IDC_LBL_TIME ), szTmp);
  // Print frame
  sprintf(szTmp, "%d", iFrame);
  SetWindowText(GetDlgItem(hDlgWnd, IDC_LBL_IFRAME ), szTmp);

  // Print coordinates
  PrintCoord(hDlgWnd, adXYZ[0][0], IDC_LBL_X1);
  PrintCoord(hDlgWnd, adXYZ[0][1], IDC_LBL_Y1);
  PrintCoord(hDlgWnd, adXYZ[0][2], IDC_LBL_Z1);

  PrintCoord(hDlgWnd, adXYZ[1][0], IDC_LBL_X2);
  PrintCoord(hDlgWnd, adXYZ[1][1], IDC_LBL_Y2);
  PrintCoord(hDlgWnd, adXYZ[1][2], IDC_LBL_Z2);

  PrintCoord(hDlgWnd, adXYZ[2][0], IDC_LBL_X3);
  PrintCoord(hDlgWnd, adXYZ[2][1], IDC_LBL_Y3);
  PrintCoord(hDlgWnd, adXYZ[2][2], IDC_LBL_Z3);

  PrintCoord(hDlgWnd, adXYZ[3][0], IDC_LBL_X4);
  PrintCoord(hDlgWnd, adXYZ[3][1], IDC_LBL_Y4);
  PrintCoord(hDlgWnd, adXYZ[3][2], IDC_LBL_Z4);

}

//----------------------------------------------------------------------
// This is  a DialogProc, not a WindowProc
// It should not call "return DefWindowProc()" at the end
// It returns TRUE for handled messages and FALSE otherwise
BOOL CALLBACK x_DialogProc(HWND hDlgWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) { 
  LRESULT  lngRes;
  char * szResult;
  int  iResult; 

  switch (uMsg) {

    case WM_PI_RAWDATA_READY:
      g_OnNewData( wParam, lParam);
      return TRUE;

    case WM_PI_DATA_STARTED:
      g_OnDataStart( wParam, lParam);
      return TRUE;
      
    case WM_PI_DATA_STOPPED:
      CP_printf("\nLiberty data stopped.\n");
      InvalidateRgn( hDlgWnd, NULL, TRUE); // refresh the window
      return TRUE;
      
    case WM_PI_RAWDATA_ERROR :
      g_GetLibertyResult( &szResult, &iResult  );
      CP_printf("\nLiberty data error: %s   Code: %X\n", szResult, iResult);
      return TRUE;
      
    case WM_PI_RAWDATA_WARNING :
      CP_printf("\nLiberty data warning.\n");
      return TRUE;
      
 
    case WM_COMMAND: 
      if (HIWORD(wParam) == BN_CLICKED) { 
        switch (LOWORD(wParam)) { 
          case IDC_CMD_EXIT:  // Exit button
            PostMessage( hDlgWnd, WM_CLOSE, 0,0);
            return TRUE;
          case IDC_CMD_START:  // Start button
            g_CmdStart();
            return TRUE;
          case IDC_CMD_STOP:  // Stop button
            g_CmdStop();
            return TRUE;
          case IDC_CHK_SHOWLOG: 
            // Retrieve the state of the check box. 
            lngRes = SendDlgItemMessage( hDlgWnd, IDC_CHK_SHOWLOG, BM_GETCHECK, 0, 0); 
            if( lngRes == BST_CHECKED ) CP_printfShow();
            if( lngRes == BST_UNCHECKED ) CP_printfHide();
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
      g_Release_LibertyTrack();
      CP_printfDestroy(); // close console window    
      DestroyWindow (hDlgWnd);
      return TRUE;
    } 
  return FALSE;
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
  HWND hDlgWnd;
  UINT uiTimerID; 
  HRESULT hr;


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


  
//-------  Windows staff starts here
  CP_printfCreate(x_szTitle); // create console window

  hDlgWnd=CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MAIN_DIALOG),
                      NULL, x_DialogProc); 
  g_hWnd = hDlgWnd;

  SetWindowText(hDlgWnd, x_szTitle);
  SendMessage(hDlgWnd, WM_SETICON, ICON_BIG, 
              (LPARAM)LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_APPL)));
  SendMessage(hDlgWnd, WM_SETICON, ICON_SMALL, 
             (LPARAM)LoadImage(hInstance, MAKEINTRESOURCE(IDI_ICON_APPL), IMAGE_ICON, 16, 16, 0));
  ShowWindow(hDlgWnd, SW_SHOW); 
  CP_printf(g_szVersion);
  CP_printf("\n\n");
  
  uiTimerID = SetTimer( hDlgWnd,  TIMER_ID,  TIMER_PERIOD_MS,  NULL ); 
 
  if ( uiTimerID == 0){ 
    CP_printf("Error: could not create timer!"); // don't exit we are still functional
  } 

  CP_printfHide();  // default is no log window

  // Init COM using single-thread apartment model
  hr = CoInitialize(NULL); 
  if( hr != S_OK) { 
    MessageBox( NULL, "Error in CoInitializeEx()", x_szTitle, MB_OK);
    return 1;
  }

  iRes = g_Init_LibertyTrack( );
  if( iRes != 0 ) { 
    MessageBox( NULL, "Error: g_Init_LibertyTrack() failed.", x_szTitle, MB_OK);
    return 1;
  }
  // Message loop
  MSG msg;
  while (GetMessage(&msg, 0, 0, 0)) {
    // IsDialogMessage() processes keyboard events for the dialog and
    // passes others to translate/dispatch
    if(!IsDialogMessage(hDlgWnd,&msg)){
      TranslateMessage(&msg);
      DispatchMessage(&msg); 
    }
  }  // end of uMsg loop

  KillTimer( hDlgWnd, TIMER_ID);
	CoUninitialize();
  ReleaseMutex(hMutex); 

  return 0;
}
