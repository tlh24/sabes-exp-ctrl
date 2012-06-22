// CP_TimeSync.cpp : Implementation of WinMain

#include <windows.h>
//#include <objbase.h>
//#include <initguid.h>

#include "TimeSyncGlob.h"
#include "CP_printf.h"
// Includes below are generated on every build
#include "resource.h"


#define TIMER_ID 1
#define TIMER_PERIOD_MS 333    // 3 Hz rate

char * x_szVersion = "CP_TimeSync: Ver 0.00 October 3rd, 2007";
char * x_szTitle = "CP_TimeSync";
char * x_szMutexName = "CP_TimeSync_Application_Mutex";
int x_iTimerCount = 0;
int x_iTrackFramesFlag = 0;

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
void PrintCount( HWND hDlgWnd, int iCount, int iLabelID ){
  char szTmp[100];
              
//  if( fCoord < INVALID_FLOAT ) { 
//    sprintf(szTmp, "N/A");
//  }
//  else {
    sprintf(szTmp, "%d", iCount );
//  }

  SetWindowText(GetDlgItem(hDlgWnd, iLabelID ), szTmp);
}


//----------------------------------------------
// Display current sensor position
void OnTimer( HWND hDlgWnd ){
  int iTurn;
  int iCount;

  if( !x_iTrackFramesFlag) return;
  iTurn = x_iTimerCount % 3;
  switch (iTurn) {
    case 0: 
      iCount = (int)g_GetValue("DispFrameCnt");
      PrintCount( hDlgWnd, iCount, IDC_TXT_1);
      break;
    case 1: 
      iCount = (int)g_GetValue("EyeFrameCnt");
      PrintCount( hDlgWnd, iCount, IDC_TXT_2);
      break;
    case 2: 
      iCount = (int)g_GetValue("TrackFrameCnt");
      PrintCount( hDlgWnd, iCount, IDC_TXT_3);
      break;
  }



  x_iTimerCount++;
}
//-----------------------------------------------
// Show frame counters
void ShowFrameCounters( HWND hDlgWnd ){
  ShowWindow(GetDlgItem(hDlgWnd, IDC_LBL_1), SW_SHOWNORMAL);
  ShowWindow(GetDlgItem(hDlgWnd, IDC_LBL_2), SW_SHOWNORMAL);
  ShowWindow(GetDlgItem(hDlgWnd, IDC_LBL_3), SW_SHOWNORMAL);
  ShowWindow(GetDlgItem(hDlgWnd, IDC_TXT_1), SW_SHOWNORMAL);
  ShowWindow(GetDlgItem(hDlgWnd, IDC_TXT_2), SW_SHOWNORMAL);
  ShowWindow(GetDlgItem(hDlgWnd, IDC_TXT_3), SW_SHOWNORMAL);
  ShowWindow(GetDlgItem(hDlgWnd, IDC_GROUP_COUNTERS), SW_SHOWNORMAL);
}

//-----------------------------------------------
// Hide frame counters
void HideFrameCounters( HWND hDlgWnd ){
  ShowWindow(GetDlgItem(hDlgWnd, IDC_LBL_1), SW_HIDE);
  ShowWindow(GetDlgItem(hDlgWnd, IDC_LBL_2), SW_HIDE);
  ShowWindow(GetDlgItem(hDlgWnd, IDC_LBL_3), SW_HIDE);
  ShowWindow(GetDlgItem(hDlgWnd, IDC_TXT_1), SW_HIDE);
  ShowWindow(GetDlgItem(hDlgWnd, IDC_TXT_2), SW_HIDE);
  ShowWindow(GetDlgItem(hDlgWnd, IDC_TXT_3), SW_HIDE);
  ShowWindow(GetDlgItem(hDlgWnd, IDC_GROUP_COUNTERS), SW_HIDE);
}

//----------------------------------------------------------------------
// This is  a DialogProc, not a WindowProc
// It should not call "return DefWindowProc()" at the end
// It returns TRUE for handled messages and FALSE otherwise
BOOL CALLBACK x_DialogProc(HWND hDlgWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) { 

  LRESULT lngRes;
 
  switch (uMsg) {
  
    case WM_COMMAND: 
      if (HIWORD(wParam) == BN_CLICKED) { 
        switch (LOWORD(wParam)) { 
          case IDC_CMD_EXIT:  // Exit button
            PostMessage( hDlgWnd, WM_CLOSE, 0,0);
            return TRUE;
          case IDC_CMD_TEST:  // Test button
            g_Test();
            return TRUE;

          // Hide/show log window
          case IDC_CHK_SHOWLOG: 
            // Retrieve the state of the check box. 
            lngRes = SendDlgItemMessage( hDlgWnd, IDC_CHK_SHOWLOG, BM_GETCHECK, 0, 0); 
            if( lngRes == BST_CHECKED ) CP_printfShow();
            if( lngRes == BST_UNCHECKED ) CP_printfHide();
            return TRUE; 

          // Track frame count On/Off
          case IDC_CHK_TRACKFRAMES: 
            // Retrieve the state of the check box. 
            lngRes = SendDlgItemMessage( hDlgWnd, IDC_CHK_TRACKFRAMES, BM_GETCHECK, 0, 0); 
            if( lngRes == BST_CHECKED ) {
              x_iTrackFramesFlag = 1;
              ShowFrameCounters( hDlgWnd );
            }
            if( lngRes == BST_UNCHECKED ) {
              x_iTrackFramesFlag = 1;
              HideFrameCounters( hDlgWnd );
            }
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
      g_ReleaseActX_Control();
      CP_printfDestroy(); // close console window    
      DestroyWindow (hDlgWnd);
      return TRUE;

    } 
    return FALSE;
//    return DefWindowProc( hDlgWnd, uMsg, wParam, lParam);  // should not be called in the DialogProc!!!
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
  HRESULT hr;
  UINT uiTimerID; 

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
//  SetWindowText(GetDlgItem(hDlgWnd, IDC_LBL_VERSION ) , g_szVersion);
  ShowWindow(hDlgWnd, SW_SHOW); 
  CP_printf(x_szVersion);
  CP_printf("\n\n");
  CP_printfHide(); // hide console window

  uiTimerID = SetTimer( hDlgWnd,  TIMER_ID,  TIMER_PERIOD_MS,  NULL ); 
 
  if ( uiTimerID == 0){ 
    CP_printf("Error: could not create timer!"); // don't exit we are still functional
  } 



  // Init COM using multi-threaded model
  hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);    //COINIT_APARTMENTTHREADED
  if( hr != S_OK) { 
    MessageBox( NULL, "Error in CoInitializeEx()", x_szTitle, MB_OK);
    return 1;
  }

  // Init the control, use Picture control to host ActiveX container
  iRes = g_InitActX_Control(GetDlgItem(hDlgWnd, IDC_PICTURE));
  if( iRes != 0 ) { 
    MessageBox( NULL, "Error: Can't init COM object. g_InitCOM() failed.", x_szTitle, MB_OK);
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
	CoUninitialize();

  return 0;
}
