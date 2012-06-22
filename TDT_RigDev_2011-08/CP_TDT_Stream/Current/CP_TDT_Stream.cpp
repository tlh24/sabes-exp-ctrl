// CP_TDT_Stream.cpp : Implementation of WinMain


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f CP_TDT_Stream.mk in the project directory.
//#define _WIN32_DCOM

#include <windows.h>
#include <objbase.h>
#include <initguid.h>

#include "Stream_Glob.h"
#include "CP_printf.h"
// Includes below are generated on every build
#include "resource.h"

char * x_szTitle = "CP_TDT_Stream";

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

//----------------------------------------------------------------------
BOOL CALLBACK x_DialogProc(HWND hDlgWnd, UINT message, WPARAM wParam, LPARAM lParam) { 
 
  switch (message) {
  
    case WM_COMMAND: 
      if (HIWORD(wParam) == BN_CLICKED) { 
        switch (LOWORD(wParam)) { 
          case IDC_CMD_EXIT:  // Exit button
            PostMessage( hDlgWnd, WM_CLOSE, 0,0);
            return TRUE;
          case IDC_CMD_TEST:  // Test button
            g_Test();
            return TRUE;
/*
          case IDC_BOX1: 
            // Retrieve the state of the check box. 
            lState = SendDlgItemMessage( hDlg, IDC_BOX1, BM_GETSTATE, 0, 0); 
            DoSomething(lState); 
            break; 
*/
        } // switch
      }  // if BN_CLICKED
      break;

    case WM_DESTROY:
      PostQuitMessage(0);
      return TRUE;

    case WM_CLOSE:
      // TODO: check status and ask for confirmation
      g_ReleaseStream();
      CP_prn_destroy(); // close console window    
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
  HWND hDlgWnd;
  HRESULT hr;

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
  CP_prn_create(x_szTitle); // create console window

  hDlgWnd=CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MAIN_DIALOG),
                      NULL, x_DialogProc); 
  SetWindowText(hDlgWnd, x_szTitle);
  SendMessage(hDlgWnd, WM_SETICON, ICON_BIG, 
              (LPARAM)LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_APPL)));
  SendMessage(hDlgWnd, WM_SETICON, ICON_SMALL, 
             (LPARAM)LoadImage(hInstance, MAKEINTRESOURCE(IDI_ICON_APPL), IMAGE_ICON, 16, 16, 0));
  SetWindowText(GetDlgItem(hDlgWnd, IDC_LBL_VERSION ) , g_GetVersion());
  ShowWindow(hDlgWnd, SW_SHOW); 
  CP_printf(g_GetVersion());
  CP_printf("\n\n");

  // Init COM using multi-threaded model
  hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);    //COINIT_APARTMENTTHREADED
  if( hr != S_OK) { 
    MessageBox( NULL, "Error in CoInitializeEx()", x_szTitle, MB_OK);
    return 1;
  }

  // Init TDT_Stream object, use Picture control to host ActiveX container
  iRes = g_InitStream(GetDlgItem(hDlgWnd, IDC_PICTURE));
  if( iRes != 0 ) { 
    MessageBox( NULL, "Error: Can't init COM object. g_InitCOM() failed.", x_szTitle, MB_OK);
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
	CoUninitialize();

  return 0;
}
