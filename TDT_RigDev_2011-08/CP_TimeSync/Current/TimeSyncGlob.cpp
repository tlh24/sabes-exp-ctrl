//#define _WIN32_DCOM
#include <objbase.h>
#include <initguid.h>

// AtlAxWinInit is implemented in Atl.dll
#pragma comment(lib, "atl.lib")
#include <atldef.h>
//#define _ATL_DLL_IMPL
#include <atliface.h> 


#include "TimeSyncGlob.h"
#include "RegisterCom.h"
#include "ClassFactory.h"
#include "CP_TimeSyncCom.h"
#include "CP_printf.h"

_DRPcoXPtr g_pRPcoX = NULL;
_DTDevAccXPtr g_pTDevAccX = NULL;
HWND g_hWnd;

IClassFactory *x_pIFactory;
DWORD x_dwRegister;

const DWORD x_dwPause = 100; // time to wait for threads to finish up


// Here we define functions that MainDialog should know about 
// to use the CP_TimeSync COM server

//==============================================
int g_RegisterCOM(){
  HRESULT hr;  
  ITypeLib* pTypeLib;

  // Register typelib
  hr = LoadTypeLibEx(L"CP_TimeSync.exe", REGKIND_REGISTER, &pTypeLib);
  if( hr != S_OK) {
    return 1;
  }
  pTypeLib->Release();

  // Register server
  hr = g_RegisterServer( "CP_TimeSync.exe",  // application filename, full path is not needed
                        CLSID_CP_TimeSyncClass,          // ClassID GUID
                        "CP_TimeSync",      // Friendly name - shows up in dcomcnfg
                        "CP_TimeSync.Application",   // Version-independent ProgID used in late - binding
                        "CP_TimeSync.Application.1", // ProgID with version
                        NULL);                               // Threading model

  if( hr != S_OK) return 2;
  return 0;

}

//==============================================
int g_UnregisterCOM(){
  HRESULT hr;  

  // Unregister typelib
  hr = UnRegisterTypeLib(LIBID_CP_TimeSync_Lib,   // Typelib GUID
                         0,                 // Version Major
                         0,                 // Version Minor
                         LANG_NEUTRAL,      // LocaleID
                         SYS_WIN32);        // The target operating system
  if( hr != S_OK) { 
    return 1;
  }

  // Unregister server
  hr = g_UnregisterServer(CLSID_CP_TimeSyncClass, "CP_TimeSync.Application", "CP_TimeSync.Application.1");
  if( hr != S_OK) { 
    return 2;
  }

  return 0;
}


//==============================================
int g_InitActX_Control( HWND hWnd){
  HRESULT hRet;

  g_hWnd = hWnd;
  x_pIFactory = new CFactory();
  if( x_pIFactory == NULL) return 2;

  hRet = CoRegisterClassObject( CLSID_CP_TimeSyncClass,     //Class identifier (CLSID) to be registered
                              x_pIFactory,     //Pointer to the class object
                              CLSCTX_LOCAL_SERVER,  //Context for running executable code
                              REGCLS_MULTIPLEUSE,  // multiple clients for the same server, we do not start a new server for each client
                              &x_dwRegister ); //Save registered object info, for future release by CoRevokeClassObject()
  if( hRet != S_OK)  return 3;

  return 0;
}

//==============================================
int g_ReleaseActX_Control(){

	g_pRPcoX = NULL; // release the smart pointer object
	g_pTDevAccX = NULL; // release the smart pointer object

	CoRevokeClassObject(x_dwRegister);
	Sleep(x_dwPause); //wait for any threads to finish
	x_pIFactory->Release();
//	CoUninitialize();  // do not call here: should be called at the very appl. end
  return 0;
}

//==============================================
float g_GetValue( char * szTag ){
  HRESULT hRes;
  _bstr_t bscTmp;
  float fRes;

  bscTmp = szTag;  
  if(g_pRPcoX)        
	  hRes = g_pRPcoX->raw_GetTagVal(bscTmp, &fRes);
  else if(g_pTDevAccX) {
	  double dRes;
	  hRes = g_pTDevAccX->raw_GetTargetVal(bscTmp, &dRes);
	  fRes = (float)dRes;
  }
  else    
	  hRes = -1;

  if( hRes != S_OK ){
    return 0;
  }
  return fRes;
}
