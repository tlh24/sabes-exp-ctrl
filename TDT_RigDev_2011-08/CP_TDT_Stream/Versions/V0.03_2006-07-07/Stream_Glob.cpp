//#define _WIN32_DCOM
#include <objbase.h>
#include <initguid.h>


#include "Stream_Glob.h"
#include "RegisterCom.h"
#include "ClassFactory.h"
#include "CP_TDT_StreamCom.h"
#include "TDT_Stream.h"


IClassFactory *x_pIFactory;
DWORD x_dwRegister;

const DWORD x_dwPause = 100; // time to wait for threads to finish up


// Here we define functions that MainDialog should know about 
// to use the CP_TDT_Stream COM server

//==============================================
int g_RegisterCOM(){
  HRESULT hr;  
  ITypeLib* pTypeLib;

  // Register typelib
  hr = LoadTypeLibEx(L"CP_TDT_Stream.exe", REGKIND_REGISTER, &pTypeLib);
  if( hr != S_OK) {
    return 1;
  }
  pTypeLib->Release();

  // Register server
  hr = g_RegisterServer( "CP_TDT_Stream.exe",  // application filename, full path is not needed
                        CLSID_CP_TS_Class,          // ClassID GUID
                        "CP_TDT_Stream",      // Friendly name - shows up in dcomcnfg
                        "CP_TDT_Stream.Application",   // Version-independent ProgID used in late - binding
                        "CP_TDT_Stream.Application.1", // ProgID with version
                        NULL);                               // Threading model

  if( hr != S_OK) return 2;
  return 0;

}

//==============================================
int g_UnregisterCOM(){
  HRESULT hr;  

  // Unregister typelib
  hr = UnRegisterTypeLib(LIBID_CP_TDT_Stream_Lib,   // Typelib GUID
                         0,                 // Version Major
                         0,                 // Version Minor
                         LANG_NEUTRAL,      // LocaleID
                         SYS_WIN32);        // The target operating system
  if( hr != S_OK) { 
    return 1;
  }

  // Unregister server
  hr = g_UnregisterServer(CLSID_CP_TS_Class, "CP_TDT_Stream.Application", "CP_TDT_Stream.Application.1");
  if( hr != S_OK) { 
    return 2;
  }

  return 0;
}


//==============================================
int g_InitStream( HWND hWnd){
  HRESULT hr;
  int iRet;


  x_pIFactory = new CFactory();
  if( x_pIFactory == NULL) return 2;

	hr = CoRegisterClassObject( CLSID_CP_TS_Class,     //Class identifier (CLSID) to be registered
                              x_pIFactory,     //Pointer to the class object
                              CLSCTX_LOCAL_SERVER,  //Context for running executable code
                              REGCLS_MULTIPLEUSE,  // multiple clients for the same server, we do not start a new server for each client
                              &x_dwRegister ); //Save registered object info, for future release by CoRevokeClassObject()
  if( hr != S_OK)  return 3;


  g_pTDT_Stream = new CTDT_Stream;
  if( g_pTDT_Stream == NULL )  return 4;

  iRet = g_pTDT_Stream->Initialize( hWnd );
  if( iRet )  return 5;

  return 0;
}

//==============================================
int g_OkToRelease( ){
  //TODO: implement
  return 1;
}
//==============================================
char * g_GetVersion(){

  char * szVersion;

  g_pTDT_Stream->GetVersion( & szVersion );
  
  return szVersion;

}
//==============================================
int g_ReleaseStream(){
  int iRet;

  iRet = g_pTDT_Stream->Uninitialize();
  if( iRet )  return 5;
  delete g_pTDT_Stream;
  CoRevokeClassObject(x_dwRegister);
  Sleep(x_dwPause); //wait for any threads to finish
	x_pIFactory->Release();
//	CoUninitialize();  // do not call here: should be called at the very appl. end
  return 0;
}

//==============================================
int g_Test(){
  g_pTDT_Stream->Test();
  return 0;
}