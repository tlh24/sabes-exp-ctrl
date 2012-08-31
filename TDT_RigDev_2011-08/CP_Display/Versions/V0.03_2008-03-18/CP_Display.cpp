#include "ATL_Defs.h"            // ATL, COM and Windows definitions
#include "resource.h"            // Resource IDs for registry
#include "CP_Display.h"          // this file is generated by MIDL compiler
#include "CP_Display_i.c"        // this file is generated by MIDL compiler

// COM interfaces (use ATL and IDs)
#include "VDisk.h"
#include "VMain.h"
#include "VMouse.h"
#include "VPolygon.h"
#include "VText.h"

#include "BuildOptions.h"
#include <math.h>
#include <stdio.h>
#include <gl\gl.h>               // Header File For The OpenGL32 Library
#include <gl\glu.h>              // Header File For The GLu32 Library

#include "GL_Engine.h"
#include "Util\CP_printf.h"
#include "Util\SafeArrayLib.h"


#define COM_THREAD_WAIT_MS 1000  // time to wait for threads to finish up

char g_szVersion[] = "CP_Display: Ver 0.03  March 18th, 2008";
char g_szAppTitile[] = "CP_Display";

char x_szMutexName[] = "CP_Display_Application_Mutex";

//------------------------------------------
LONG CExeModule::Unlock() {
  LONG nObjects;
      
  nObjects = CComModule::Unlock();
  CP_printfDbg(LEVEL_DEBUG,"Object deleted. New N objects: %d\n", nObjects );
  return nObjects;
}
//------------------------------------------
LONG CExeModule::Lock() {
  LONG nObjects;
      
  nObjects = CComModule::Lock();
  CP_printfDbg(LEVEL_DEBUG,"Object created. New N objects: %d\n", nObjects );
  return nObjects;
}

//------------------------------------------
CExeModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
  OBJECT_ENTRY(CLSID_VMain, CVMain)
  OBJECT_ENTRY(CLSID_VDisk, CVDisk)
  OBJECT_ENTRY(CLSID_VMouse, CVMouse)
  OBJECT_ENTRY(CLSID_VPolygon, CVPolygon)
  OBJECT_ENTRY(CLSID_VText, CVText)
END_OBJECT_MAP()


//------------------------------------------
LPCTSTR FindOneOf(LPCTSTR p1, LPCTSTR p2)
{
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

//===========================================================================
extern "C" int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
                                LPTSTR lpCmdLine, int nShowCmd ) {

  HANDLE hMutex;
  int iRet;
  HRESULT hRes;
  TCHAR szTokens[] = _T("-/");

  // Check for another instance
  hMutex = OpenMutex( SYNCHRONIZE,  // requested access (lowest possible)
                      FALSE,  // allow inheritance (does not matter)
                      x_szMutexName);  // unique name

  if(hMutex){
    MessageBox( NULL, "Cannot start the application because another instance is already running.\n", 
                g_szAppTitile, MB_OK | MB_ICONERROR );
    return 1;
  }

  hMutex = CreateMutex( NULL,  // default security
                        TRUE,  // obtain ownership
                        x_szMutexName);  // unique name
  if(!hMutex){
    MessageBox( NULL, "Cannot create application mutex.\n", 
                g_szAppTitile, MB_OK | MB_ICONERROR );
    return 1;
  }
    

  hRes = CoInitialize(NULL);  // single-threaded apartment 
  _ASSERTE(SUCCEEDED(hRes));
  _Module.Init(ObjectMap, hInstance, &LIBID_CP_DISPLAYLib);
  hRes = _Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER, REGCLS_MULTIPLEUSE);
  _ASSERTE(SUCCEEDED(hRes));

  lpCmdLine = GetCommandLine(); //this line is necessary for _ATL_MIN_CRT


  // Parse the command line for options
  LPCTSTR lpszToken = FindOneOf(lpCmdLine, szTokens);
  while (lpszToken != NULL) {
    if (lstrcmpi(lpszToken, "UnregServer")==0) {
      _Module.UpdateRegistryFromResource(IDR_CP_Display, FALSE);
      iRet = _Module.UnregisterServer(TRUE);

      if( iRet != 0 ) { 
        MessageBox( NULL, "Error: Can't unregister server. UnregisterServer() failed.", g_szAppTitile, MB_OK);
      }
      else {
        MessageBox( NULL, "Success: the server is unregistered.", g_szAppTitile, MB_OK);
      }
      _Module.Term();
      CoUninitialize();
      return iRet;
    }
    if (lstrcmpi(lpszToken, "RegServer")==0) {
      _Module.UpdateRegistryFromResource(IDR_CP_Display, TRUE);
      iRet = _Module.RegisterServer(TRUE);
      if( iRet != 0 ) { 
        MessageBox( NULL, "Error: Can't register server. g_RegisterCOM() failed.", g_szAppTitile, MB_OK);
      }
      else {
        MessageBox( NULL, "Success: the server is registered.", g_szAppTitile, MB_OK);
      }
      _Module.Term();
      CoUninitialize();
      return iRet;
    }
    lpszToken = FindOneOf(lpszToken, szTokens);
  } // while there are tokens


  CP_printfCreate( g_szAppTitile );  // Creates log window (console)
  CP_printf("%s\n", g_szVersion );


  CP_printf("----------------------------------------\n");
  CP_printf("Build options:\n\n");
//~~~~~~~~~~~~~~~~~
#ifdef _DEBUG
  CP_printf("Debug version.\n");
#else
  CP_printf("Release version. \n\n");
#endif  // #ifdef _DEBUG
//~~~~~~~~~~~~~~~~~
  CP_printf("SET_FULLSCREEN_MODE: %d\n", SET_FULLSCREEN_MODE);
  CP_printf("DEBUG_THRESHOLD: %d\n", DEBUG_THRESHOLD);
  CP_printf("----------------------------------------\n");

  srand( (unsigned)123 );
  try {
    if ( !g_StartGL_Engine( hInstance, nShowCmd ) ){
      g_MainLoop();
    }
  }
  catch( ... ) {
    MessageBox( NULL, "Exception!!! SOS!!! The program will shut down!", 
               g_szAppTitile, MB_OK | MB_ICONERROR );
    exit(1);
  }

  CP_printf("N objects before quitting: %d\n", _Module.GetLockCount() );

  _Module.RevokeClassObjects();
  Sleep(COM_THREAD_WAIT_MS); //wait for any threads to finish


  // WrapUp
  _Module.Term();
  CoUninitialize();
  // Left-over objects are deleted in CoUninitialize(). Since they call RequestUpdate 
  // in the destuctor, we have to delete GL_Window after CoUninitialize()
  g_StopGL_Engine( );  
  InvalidateRect(NULL, NULL, TRUE); // redraw the desktop
  Sleep(5000); // show log window for 5 sec before quitting
  CP_printfDestroy( );  // Kills log window (console)
  ReleaseMutex(hMutex); 

  return 0;
}