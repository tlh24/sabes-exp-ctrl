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

#define N_SENSORS 4
#define INVALID_FLOAT  ((float)-3.0E28)   // from the NDI include

// in mm
#define RAW_MIN_X -400.0f
#define RAW_MAX_X 400.0f

#define RAW_MIN_Y -300.0f
#define RAW_MAX_Y 300.0f

// in pix
#define WIN_SIZE_X 400
#define WIN_SIZE_Y 300

char * g_szVersion = "CP_OptoTrack: Ver 0.01 July 22nd, 2008";

char * x_szTitle = "CP_OptoTrack";
char * x_szMutexName = "CP_OptoTrack_Application_Mutex";

HINSTANCE x_hInstance;

bool blnIsDrawn[N_SENSORS] = {0,0,0,0};
float fPrevX[N_SENSORS] = {0,0,0,0};
float fPrevY[N_SENSORS] = {0,0,0,0};

COLORREF aMarkerColors[N_SENSORS] = { 
    RGB( 0xff,    0,    0),    // Red
    RGB(    0, 0xff,    0),    // green
    RGB( 0xff, 0xff,    0),    // yellow
    RGB(    0, 0xff, 0xff)     // cyan
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
void PrintCoord( HWND hDlgWnd, float fCoord, int iLabelID ){
  char szTmp[100];
              
  if( fCoord < INVALID_FLOAT ) { 
    sprintf(szTmp, "N/A");
  }
  else {
    sprintf(szTmp, "%.1f", fCoord );
  }

  SetWindowText(GetDlgItem(hDlgWnd, iLabelID ), szTmp);
}

//----------------------------------------------
// Display current data
void OnTimer( HWND hDlgWnd ){
  HWND hPic;
  HDC hDC;
  RECT recClnt;
  double dTimeMs;
  int iFrame, nMissedFrames, nMissedCount;
  float afXYZ[N_SENSORS][3];
  int iSensor;
  int iOffsetX, iOffsetY;
  float fX, fY;
  char szTmp[100];

  if(g_GetLatestCoordinates( &dTimeMs, 
                             &iFrame,
                             &nMissedFrames,
                             &nMissedCount,
                             N_SENSORS,
                             &afXYZ[0][0] ) ) 
    return;
  hPic = GetDlgItem(hDlgWnd, IDC_PICTURE);
  GetClientRect( hPic, &recClnt );

  iOffsetX = ((recClnt.right - recClnt.left) - WIN_SIZE_X)/2;
  iOffsetY = ((recClnt.bottom - recClnt.top) - WIN_SIZE_Y)/2;
  hDC = GetDC(hPic);

  SetROP2( hDC, R2_XORPEN);

  for( iSensor = 0; iSensor < N_SENSORS; iSensor++){
    // erase previous
    if( blnIsDrawn[iSensor] ){
      DrawCross( hDC, aMarkerColors[iSensor],
                (int)(fPrevX[iSensor]*WIN_SIZE_X) + iOffsetX,  
                (int)(fPrevY[iSensor]*WIN_SIZE_Y) + iOffsetY  );
      blnIsDrawn[iSensor] = FALSE;
    }

    // draw new
    // check for invalid coordinates 
    if( afXYZ[iSensor][0] < INVALID_FLOAT ) {
      fX = 0.0f;
      fY = 0.0f;
    }
    else {
      // normalize coordinates to 0-1 
      fX = (afXYZ[iSensor][0] - RAW_MIN_X)/ (RAW_MAX_X - RAW_MIN_X);  
      fY = (afXYZ[iSensor][1] - RAW_MIN_Y)/ (RAW_MAX_Y - RAW_MIN_Y);
    }
    fPrevX[iSensor] = fX;
    fPrevY[iSensor] = fY;
    DrawCross( hDC, aMarkerColors[iSensor],
              (int)(fX*WIN_SIZE_X) + iOffsetX,  
              (int)(fY*WIN_SIZE_Y) + iOffsetY  );
    blnIsDrawn[iSensor] = TRUE;
  } // for all sensors
  ReleaseDC(hPic, hDC); 

  // Print timestamp
  sprintf(szTmp, "%.2f", dTimeMs/1000.0);
  SetWindowText(GetDlgItem(hDlgWnd, IDC_LBL_TIME ), szTmp);
  // Print frame index
  sprintf(szTmp, "%d", iFrame);
  SetWindowText(GetDlgItem(hDlgWnd, IDC_LBL_FRAME ), szTmp);
  // Print N missed frames
  sprintf(szTmp, "%d", nMissedFrames);
  SetWindowText(GetDlgItem(hDlgWnd, IDC_LBL_N_MISSED ), szTmp);
  // Print N missed counts
  sprintf(szTmp, "%d", nMissedCount);
  SetWindowText(GetDlgItem(hDlgWnd, IDC_LBL_MISSED_CNT ), szTmp);
  
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
//----------------------------------------------
// Draw black background and white frame
void OnPaint( HWND hDlgWnd ){
  HWND hPic;
  HDC hDC;
  RECT recClnt;
  int iOffsetX, iOffsetY;
  int iSensor;


  hPic = GetDlgItem(hDlgWnd, IDC_PICTURE);
  GetClientRect( hPic, &recClnt );

  iOffsetX = ((recClnt.right - recClnt.left) - WIN_SIZE_X)/2;
  iOffsetY = ((recClnt.bottom - recClnt.top) - WIN_SIZE_Y)/2;
  hDC = GetDC(hPic);
  // Black backgound
  SelectObject( hDC, GetStockObject( BLACK_BRUSH ));
  Rectangle( hDC, recClnt.left, recClnt.top, 
             recClnt.right - recClnt.left, recClnt.bottom - recClnt.top);
  // White box
  SelectObject( hDC, GetStockObject( WHITE_PEN ));
  MoveToEx( hDC, iOffsetX, iOffsetY, NULL);
  LineTo(hDC, WIN_SIZE_X + iOffsetX,iOffsetY);
  LineTo(hDC, WIN_SIZE_X + iOffsetX, WIN_SIZE_Y + iOffsetY );
  LineTo(hDC, iOffsetX, WIN_SIZE_Y + iOffsetY );
  LineTo(hDC, iOffsetX, iOffsetY );

  for( iSensor = 0; iSensor < N_SENSORS; iSensor++){
    blnIsDrawn[iSensor] = FALSE;
  }
  ReleaseDC(hPic, hDC); 

}

//----------------------------------------------------------------------
BOOL CALLBACK x_DialogProc(HWND hDlgWnd, UINT message, WPARAM wParam, LPARAM lParam) { 
  UINT uiTimerID; 
  int iRes;
 
  switch (message) {

    case WM_COMMAND: 
      if (HIWORD(wParam) == BN_CLICKED) { 
        switch (LOWORD(wParam)) { 
          case IDC_CMD_EXIT:  // Exit button
            PostMessage( hDlgWnd, WM_CLOSE, 0, 0);
            return TRUE;
          case IDC_CMD_START:  // Start button
            g_CmdStart();
            OnPaint(hDlgWnd);
            return TRUE;
          case IDC_CMD_STOP:  // Stop button
            g_CmdStop();
            OnPaint(hDlgWnd);
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

    case WM_PAINT:
      OnPaint( hDlgWnd );
      return FALSE;

    case WM_DESTROY:
      PostQuitMessage(0);
      return TRUE;

    case WM_CLOSE:
      // TODO: check status and ask for confirmation
      KillTimer( hDlgWnd, TIMER_ID);
      g_Release_OptoTrack();
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

  TCHAR szTokens[] = "-/";
  int iRes;
  HRESULT hRes;
  HANDLE hMutex;

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
  LPCTSTR lpszToken = FindOneOf(lpCmdLine, szTokens);
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
