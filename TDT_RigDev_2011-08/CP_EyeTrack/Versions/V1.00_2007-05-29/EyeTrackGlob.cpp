#define _WIN32_DCOM
#include <windows.h>
#include <comdef.h>  // _bstr_t

#include <objbase.h>
#include <initguid.h>


#include "RegisterCom.h"
#include "ClassFactory.h"
#include "CP_EyeTrackCom.h"

#include "EyeTrack.h"
#include "EyeTrackGlob.h"




CEyeTrack * g_pEyeTrack; // The object pointer, we have only one

IClassFactory *x_pIFactory;

DWORD x_dwRegister;

char * g_szVersion = "CP EyeTrack: Ver 1.00\r\nMay 29th, 2007\r\nby Sergei Rebrik <rebrik@phy.ucsf.edu>";


// Here we define functions that MainDialog should know about 
// to use the CP_EyeTrack COM server
//==============================================
int g_RegisterCOM(){

  HRESULT hr;  
  ITypeLib* pTypeLib;

  // Register typelib
  hr = LoadTypeLibEx(L"CP_EyeTrack.exe", REGKIND_REGISTER, &pTypeLib);
  if( hr != S_OK) {
    return 1;
  }
  pTypeLib->Release();

  // Register server
  hr = g_RegisterServer( "CP_EyeTrack.exe",  // application filename, full path is not needed
                        CLSID_CP_ET_Class,          // ClassID GUID
                        "CP_EyeTrack",      // Friendly name - shows up in dcomcnfg
                        "CP_EyeTrack.Application",   // Version-independent ProgID used in late - binding
                        "CP_EyeTrack.Application.1", // ProgID with version
                        NULL);                               // Threading model

  if( hr != S_OK) return 2;

  return 0;
}

//==============================================
int g_UnregisterCOM(){

  HRESULT hr;  

  // Unregister typelib
  hr = UnRegisterTypeLib(LIBID_CP_EyeTrackLib,   // Typelib GUID
                         0,                 // Version Major
                         0,                 // Version Minor
                         LANG_NEUTRAL,      // LocaleID
                         SYS_WIN32);        // The target operating system
  if( hr != S_OK) { 
    return 1;
  }

  // Unregister server
  hr = g_UnregisterServer(CLSID_CP_ET_Class, "CP_EyeTrack.Application", "CP_EyeTrack.Application.1");
  if( hr != S_OK) { 
    return 2;
  }

  return 0;
}


//==============================================
int g_Init_EyeTrack( ){

//  int iRet;
  HRESULT hr;


  x_pIFactory = new CFactory();
  if( x_pIFactory == NULL) return 2;

	hr = CoRegisterClassObject( CLSID_CP_ET_Class,     //Class identifier (CLSID) to be registered
                              x_pIFactory,     //Pointer to the class object
                              CLSCTX_LOCAL_SERVER,  //Context for running executable code
                              REGCLS_MULTIPLEUSE,  // multiple clients for the same server, we do not start a new server for each client
                              &x_dwRegister ); //Save registered object info, for future release by CoRevokeClassObject()
  if( hr != S_OK)  return 3;


  g_pEyeTrack = new CEyeTrack;
  if( g_pEyeTrack == NULL )  return 4;

//  iRet = g_pEyeTrack->Initialize( );
//  if( iRet )  return 5;

  return 0;
}

//==============================================
int g_OkToRelease( ){
  //TODO: implement
  return 1;
}
//==============================================
int g_Release_EyeTrack(){

//  int iRet;

//  iRet = g_pEyeTrack->Uninitialize();
  delete g_pEyeTrack;

//  CoRevokeClassObject(x_dwRegister);
//	x_pIFactory->Release();

////	CoUninitialize();  // do not call here: should be called at the very appl. end

  
    return 0;
}

//==============================================
int g_GetLatestData( ET_Struct * ptET ){
  int iIdx;
  IScanFrameStruct isdTmp;
  int iRawX, iRawY;
  double dX, dY;
  int nMissed, iMissCount;

  ZeroMemory(ptET, sizeof(* ptET));
 
  if( !g_pEyeTrack->ReadLatestItem( &iIdx, &isdTmp ) ) return 1;
  iRawX = isdTmp.iRawX;
  iRawY = isdTmp.iRawY;

  g_pEyeTrack->TransformCoordinates( iRawX, iRawY, &dX, &dY );
  g_pEyeTrack->GetMissedCount( &nMissed, &iMissCount);
  
  g_pEyeTrack->CalcTime( isdTmp.iFrame, &ptET->pdTimeMs);
//  ptET->pdTimeMs = isdTmp.dLocalTimeMs;
  ptET->iRawX = iRawX;
  ptET->iRawY = iRawY;
  ptET->dX = dX;
  ptET->dY = dY;
  ptET->iFrame = isdTmp.iFrame;
  ptET->nMissed = nMissed;
  ptET->iMissCount = iMissCount;

  return 0;
}
//==============================================
int g_CmdStart(){
  g_pEyeTrack->ConnectISCAN();
  return 0;
}

//==============================================
int g_CmdStop(){
  g_pEyeTrack->DisconnectISCAN();
  return 0;
}