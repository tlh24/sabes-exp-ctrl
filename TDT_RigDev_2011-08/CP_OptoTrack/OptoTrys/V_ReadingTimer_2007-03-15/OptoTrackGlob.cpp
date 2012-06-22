#include <windows.h>

#include "RegisterCom.h"
#include "ClassFactory.h"
#include "CP_OptoTrackCom.h"

#include "OptoTrack.h"
#include "OptoTrackGlob.h"


IClassFactory *x_pIFactory;

DWORD x_dwRegister;

HWND g_hWnd;
char * g_szVersion = "CP_OptoTrack: Ver 0.00\r\nMarch 7th, 2007\r\nby Sergei Rebrik <rebrik@phy.ucsf.edu>";


// Here we define functions that MainDialog should know about 
// to use the CP_OptoTrack COM server
//==============================================
int g_RegisterCOM(){

  HRESULT hr;  
  ITypeLib* pTypeLib;

  // Register typelib
  hr = LoadTypeLibEx(L"CP_OptoTrack.exe", REGKIND_REGISTER, &pTypeLib);
  if( hr != S_OK) {
    return 1;
  }
  pTypeLib->Release();

  // Register server
  hr = g_RegisterServer( "CP_OptoTrack.exe",  // application filename, full path is not needed
                        CLSID_CP_OptoClass,          // ClassID GUID
                        "CP_OptoTrack",      // Friendly name - shows up in dcomcnfg
                        "CP_OptoTrack.Application",   // Version-independent ProgID used in late - binding
                        "CP_OptoTrack.Application.1", // ProgID with version
                        NULL);                               // Threading model

  if( hr != S_OK) return 2;

  return 0;
}

//==============================================
int g_UnregisterCOM(){

  HRESULT hr;  

  // Unregister typelib
  hr = UnRegisterTypeLib(LIBID_CP_OptoTrackLib,   // Typelib GUID
                         0,                 // Version Major
                         0,                 // Version Minor
                         LANG_NEUTRAL,      // LocaleID
                         SYS_WIN32);        // The target operating system
  if( hr != S_OK) { 
    return 1;
  }

  // Unregister server
  hr = g_UnregisterServer(CLSID_CP_OptoClass, "CP_OptoTrack.Application", "CP_OptoTrack.Application.1");
  if( hr != S_OK) { 
    return 2;
  }

  return 0;
}


//==============================================
int g_Init_OptoTrack( ){

//  int iRet;
  HRESULT hr;


  x_pIFactory = new CFactory();
  if( x_pIFactory == NULL) return 2;

	hr = CoRegisterClassObject( CLSID_CP_OptoClass,     //Class identifier (CLSID) to be registered
                              x_pIFactory,     //Pointer to the class object
                              CLSCTX_LOCAL_SERVER,  //Context for running executable code
                              REGCLS_MULTIPLEUSE,  // multiple clients for the same server, we do not start a new server for each client
                              &x_dwRegister ); //Save registered object info, for future release by CoRevokeClassObject()
  if( hr != S_OK)  return 3;


  g_pOptoTrack = new COptoTrack;
  if( g_pOptoTrack == NULL )  return 4;

//  iRet = g_pOptoTrack->Initialize( );
//  if( iRet )  return 5;

  return 0;
}

//==============================================
int g_OkToRelease( ){
  //TODO: implement
  return 1;
}
//==============================================
int g_Release_OptoTrack(){

//  int iRet;

//  iRet = g_pOptoTrack->Uninitialize();
  delete g_pOptoTrack;
  g_pOptoTrack = NULL;
//  CoRevokeClassObject(x_dwRegister);
//	x_pIFactory->Release();

// NOTE!!! do not call the next line here: it should be called at the very appl. end
////	CoUninitialize();  
  
  return 0;
}

//==============================================
// return timestamp in ms and relative coordinates: 0.0 to 1.0
int g_GetLatestRawCoordinates( int iIdx, double * pdTimeMs, float * pfRawX, float * pfRawY,  float * pfRawZ){

  tServerFrame * pFrame;
  
  * pdTimeMs = 0;
  * pfRawX = 0; 
  * pfRawY = 0; 
  * pfRawZ = 0; 

/*
  if( g_pOptoTrack->GetLatestFramePtr( iIdx,  &pFrame ) ) return 1;

  * pdTimeMs = pFrame->dReceivedTimeMs;
  * pfRawX =  pFrame->OptoFrame.afCoord[0]; 
  * pfRawY =  pFrame->OptoFrame.afCoord[1]; 
  * pfRawZ =  pFrame->OptoFrame.afCoord[2]; 
*/
  return 0;
}
//==============================================
int g_CmdStart(){
  g_pOptoTrack->ConnectOpto();
  return 0;
}

//==============================================
int g_CmdStop(){
  g_pOptoTrack->DisconnectOpto();
  return 0;
}

//==============================================
HWND g_GetWindowHandle(){
  return g_hWnd;
}