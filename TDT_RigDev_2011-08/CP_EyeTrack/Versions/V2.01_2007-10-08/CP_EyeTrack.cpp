// CP_EyeTrack.cpp : Implementation of WinMain


#define _WIN32_DCOM

#include <windows.h>
#include <wingdi.h>
#include <objbase.h>
#include <initguid.h>

#include "EyeTrackGlob.h"
#include "CP_printf.h"
// Includes below are generated on every build
#include "resource.h"


#define TIMER_ID 1
#define TIMER_PERIOD_MS 100    // 10 Hz rate

#define ISCAN_MIN_X 50
#define ISCAN_MAX_X 5110
//430 5141

#define ISCAN_MIN_Y 100
#define ISCAN_MAX_Y 2550
//260 2549

#define WIN_SIZE_X 400
#define WIN_SIZE_Y 300

char * x_szTitle = "CP_EyeTrack";
char * g_szVersion = "CP EyeTrack: Ver 2.01 October 8th, 2007";
char * x_szMutexName = "CP_EyeTrack_Application_Mutex";

bool blnIsDrawn = FALSE;


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
void DrawCross( HDC hDC, int iCentX, int iCentY ){
  HPEN hPen;
  hPen = CreatePen( PS_SOLID, 1, RGB(00,0xff,00) );
  SelectObject(hDC, hPen);

  MoveToEx( hDC, iCentX - 10, iCentY, NULL);
  LineTo( hDC, iCentX + 10, iCentY);
  MoveToEx( hDC, iCentX, iCentY-10, NULL);
  LineTo( hDC, iCentX, iCentY + 10);
  DeleteObject( hPen );

}
//----------------------------------------------
// Display current eye position
void OnTimer( HWND hDlgWnd ){
  HWND hPic;
  HDC hDC;
  RECT recClnt;
  int iOffsetX, iOffsetY;
  ET_Struct tET;
  double dX, dY;
  static double dPrevX = 0, dPrevY = 0;
  char szTmp[100];


  hPic = GetDlgItem(hDlgWnd, IDC_PICTURE);
  GetClientRect( hPic, &recClnt );

  iOffsetX = ((recClnt.right - recClnt.left) - WIN_SIZE_X)/2;
  iOffsetY = ((recClnt.bottom - recClnt.top) - WIN_SIZE_Y)/2;
  hDC = GetDC(hPic);

  SetROP2( hDC, R2_XORPEN);

  // erase previous
  if( blnIsDrawn ){
    DrawCross( hDC,
              (int)(dPrevX*WIN_SIZE_X) + iOffsetX,  
              (int)(dPrevY*WIN_SIZE_Y) + iOffsetY  );
    blnIsDrawn = FALSE;
  }

  // draw new
  if(  !g_GetLatestData( &tET ) ) {
    dX = ((double)tET.iRawX - ISCAN_MIN_X)/ ISCAN_MAX_X; 
    dY = ((double)tET.iRawY - ISCAN_MIN_Y)/ ISCAN_MAX_Y;

    dPrevX = dX;
    dPrevY = dY;
    DrawCross( hDC,
              (int)(dX*WIN_SIZE_X) + iOffsetX,  
              (int)(dY*WIN_SIZE_Y) + iOffsetY  );
    blnIsDrawn = TRUE;
    // Print timestamp
    sprintf(szTmp, "%.2f", tET.pdTimeMs/1000.0);
    SetWindowText(GetDlgItem(hDlgWnd, IDC_LBL_TIME ), szTmp);

    // Print raw coordinates
    sprintf(szTmp, "%d", tET.iRawX);
    SetWindowText(GetDlgItem(hDlgWnd, IDC_LBL_RAW_X ), szTmp);
    sprintf(szTmp, "%d", tET.iRawY);
    SetWindowText(GetDlgItem(hDlgWnd, IDC_LBL_RAW_Y ), szTmp);

    // Print transformed coordinates
    sprintf(szTmp, "%.1f", tET.dX);
    SetWindowText(GetDlgItem(hDlgWnd, IDC_LBL_X ), szTmp);
    sprintf(szTmp, "%.1f", tET.dY);
    SetWindowText(GetDlgItem(hDlgWnd, IDC_LBL_Y ), szTmp);

    // Print frame statistics
    sprintf(szTmp, "%d", tET.iFrame);
    SetWindowText(GetDlgItem(hDlgWnd, IDC_LBL_IFRAME ), szTmp);
    sprintf(szTmp, "%d", tET.nMissed);
    SetWindowText(GetDlgItem(hDlgWnd, IDC_LBL_N_MISSED ), szTmp);
    sprintf(szTmp, "%d", tET.iMissCount);
    SetWindowText(GetDlgItem(hDlgWnd, IDC_LBL_MISSED_CNT ), szTmp);
  }

  ReleaseDC(hPic, hDC); 

}
//----------------------------------------------
// Draw black background and white frame
void DrawBackground( HWND hDlgWnd ){
  HWND hPic;
  HDC hDC;
  RECT recClnt;
  int iOffsetX, iOffsetY;


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

  blnIsDrawn = FALSE;
  ReleaseDC(hPic, hDC); 

}

//----------------------------------------------------------------------
// This is  a DialogProc, not a WindowProc
// It should not call "return DefWindowProc()" at the end
// It returns TRUE for handled messages and FALSE otherwise
BOOL CALLBACK x_DialogProc(HWND hDlgWnd, UINT message, WPARAM wParam, LPARAM lParam) { 
 
  LRESULT lngRes;

  switch (message) {
  
    case WM_COMMAND: 
      if (HIWORD(wParam) == BN_CLICKED) { 
        switch (LOWORD(wParam)) { 
          case IDC_CMD_EXIT:  // Exit button
            PostMessage( hDlgWnd, WM_CLOSE, 0,0);
            return TRUE;
          case IDC_CMD_START:  // Start button
            g_CmdStart();
            DrawBackground( hDlgWnd );
            return TRUE;
          case IDC_CMD_STOP:  // Stop button
            g_CmdStop();
            DrawBackground( hDlgWnd );
            return TRUE;

          // Hide/show log window
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

    case WM_PAINT:
      DrawBackground( hDlgWnd );
      return FALSE;

    case WM_DESTROY:
      PostQuitMessage(0);
      return TRUE;

    case WM_CLOSE:
      // TODO: check status and ask for confirmation
      g_Release_EyeTrack();
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


  
//-------  Windows staff starts here
  CP_printfCreate(x_szTitle); // create console window

  hDlgWnd=CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MAIN_DIALOG),
                      NULL, x_DialogProc); 
  SetWindowText(hDlgWnd, x_szTitle);
  SendMessage(hDlgWnd, WM_SETICON, ICON_BIG, 
              (LPARAM)LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_APPL)));
  SendMessage(hDlgWnd, WM_SETICON, ICON_SMALL, 
             (LPARAM)LoadImage(hInstance, MAKEINTRESOURCE(IDI_ICON_APPL), IMAGE_ICON, 16, 16, 0));
  ShowWindow(hDlgWnd, SW_SHOW); 
  CP_printf(g_szVersion);
  CP_printf("\n\n");
  CP_printfHide(); // hide console window


  uiTimerID = SetTimer( hDlgWnd,  TIMER_ID,  TIMER_PERIOD_MS,  NULL ); 
 
  if ( uiTimerID == 0){ 
    CP_printf("Error: could not create timer!"); // don't exit we are still functional
  } 

  // Init COM using apartment-threaded model
  hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);   
  if( hr != S_OK) { 
    MessageBox( NULL, "Error in CoInitializeEx()", x_szTitle, MB_OK);
    return 1;
  }

  iRes = g_Init_EyeTrack( );
  if( iRes != 0 ) { 
    MessageBox( NULL, "Error: g_Init_EyeTrack() failed.", x_szTitle, MB_OK);
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
  }  // end of message loop
  KillTimer( hDlgWnd, TIMER_ID);
	CoUninitialize();

  return 0;
}
