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


// in cm
#define RAW_MIN_X -40.0f
#define RAW_MAX_X 40.0f

#define RAW_MIN_Y -30.0f
#define RAW_MAX_Y 30.0f

#define WIN_SIZE_X 400
#define WIN_SIZE_Y 300

char * g_szVersion = "CP_LibertyTrack: Ver 0.00 July 23rd, 2007";

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
void PrintCoord( HWND hDlgWnd, float fCoord, int iLabelID ){
  char szTmp[100];
              
//  if( fCoord < INVALID_FLOAT ) { 
//    sprintf(szTmp, "N/A");
//  }
//  else {
    sprintf(szTmp, "%.1f", fCoord );
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
  double dT_ms;
  float afXYZ[N_DISPL_SENSORS][N_COORD_ANGL];
  int aiDistortion[N_DISPL_SENSORS];
  HWND hPic;
  HDC hDC, hBitmapDC;
  HBITMAP hBitmap;
  RECT recClnt;
  int iSensor;
  int iOffsetX, iOffsetY;
  int iW, iH;
  int nSensors;
  float fSensX, fSensY;
  float fX, fY;
  char szTmp[100];

  ZeroMemory(afXYZ, sizeof(afXYZ));
  if( g_GetLatestCoordinates( &nSensors, &dT_ms, afXYZ ) ) return; 
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
    fSensX = afXYZ[iSensor][0];
    fSensY = afXYZ[iSensor][1];
    // normalize coordinates to 0-1 
    fX = (fSensX - RAW_MIN_X)/ (RAW_MAX_X - RAW_MIN_X);  
    fY = (RAW_MAX_Y - fSensY)/ (RAW_MAX_Y - RAW_MIN_Y);  // make Y axis bottom->top

    // clip coordinates
    if(fX < 0) fX = 0;
    if(fX > 1) fX = 1;
    if(fY < 0) fY = 0;
    if(fY > 1) fY = 1;

    DrawCross( hBitmapDC, x_atMarkerColors[iSensor],
              (int)(fX*WIN_SIZE_X) + iOffsetX,  
              (int)(fY*WIN_SIZE_Y) + iOffsetY  );
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

  // Print coordinates
  PrintCoord(hDlgWnd, afXYZ[0][0], IDC_LBL_X1);
  PrintCoord(hDlgWnd, afXYZ[0][1], IDC_LBL_Y1);
  PrintCoord(hDlgWnd, afXYZ[0][2], IDC_LBL_Z1);

  PrintCoord(hDlgWnd, afXYZ[1][0], IDC_LBL_X2);
  PrintCoord(hDlgWnd, afXYZ[1][1], IDC_LBL_Y2);
  PrintCoord(hDlgWnd, afXYZ[1][2], IDC_LBL_Z2);

  PrintCoord(hDlgWnd, afXYZ[2][0], IDC_LBL_X3);
  PrintCoord(hDlgWnd, afXYZ[2][1], IDC_LBL_Y3);
  PrintCoord(hDlgWnd, afXYZ[2][2], IDC_LBL_Z3);

  PrintCoord(hDlgWnd, afXYZ[3][0], IDC_LBL_X4);
  PrintCoord(hDlgWnd, afXYZ[3][1], IDC_LBL_Y4);
  PrintCoord(hDlgWnd, afXYZ[3][2], IDC_LBL_Z4);

}

//----------------------------------------------------------------------
BOOL CALLBACK x_DialogProc(HWND hDlgWnd, UINT message, WPARAM wParam, LPARAM lParam) { 
  LRESULT  lngRes;
 
  switch (message) {

    case WM_PI_RAWDATA_READY:
      g_OnNewData( wParam, lParam);
      return TRUE;

    case WM_PI_DATA_STARTED:
      return TRUE;
      
    case WM_PI_DATA_STOPPED:
      InvalidateRgn( hDlgWnd, NULL, TRUE); // refresh the window
      return TRUE;
      
    case WM_PI_RAWDATA_ERROR :
      return TRUE;
      
    case WM_PI_RAWDATA_WARNING :
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
      // TODO: check status and ask for confirmation
      g_Release_LibertyTrack();
      CP_printfDestroy(); // close console window    
      DestroyWindow (hDlgWnd);
      return TRUE;

    } 
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
  CP_printfHide();

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
    // Process dialog messages in IsDialogMessage() pass others to translate/dispatch
    if(!IsDialogMessage(hDlgWnd,&msg)){
      TranslateMessage(&msg);
      DispatchMessage(&msg); 
    }
  }  // end of message loop
  KillTimer( hDlgWnd, TIMER_ID);
	CoUninitialize();
  ReleaseMutex(hMutex); 

  return 0;
}
