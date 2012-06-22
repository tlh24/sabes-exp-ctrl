#include <windows.h>

#include "RegisterCom.h"
#include "ClassFactory.h"
#include "CP_OptoTrackCom.h"

#include "OptoTrack.h"
#include "OptoTrackGlob.h"


COptoTrack * g_pOptoTrack = NULL;  // The object pointer, we have only one
HWND g_hWnd;


IClassFactory *x_pIFactory;
DWORD x_dwRegister;


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

  if( hr != S_OK) return 1;

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
    return 1;
  }

  return 0;
}


//==============================================
int g_Init_OptoTrack( ){

//  int iRet;
  HRESULT hr;


  x_pIFactory = new CFactory();
  if( x_pIFactory == NULL) return 1;

	hr = CoRegisterClassObject( CLSID_CP_OptoClass,     //Class identifier (CLSID) to be registered
                              x_pIFactory,     //Pointer to the class object
                              CLSCTX_LOCAL_SERVER,  //Context for running executable code
                              REGCLS_MULTIPLEUSE,  // multiple clients for the same server, we do not start a new server for each client
                              &x_dwRegister ); //Save registered object info, for future release by CoRevokeClassObject()
  if( hr != S_OK)  return 1;


  g_pOptoTrack = new COptoTrack;
  if( g_pOptoTrack == NULL )  return 1;

  return 0;
}

//==============================================
int g_OkToRelease( ){
  //TODO: implement
  return 1;
}
//==============================================
int g_Release_OptoTrack(){

  delete g_pOptoTrack;
  g_pOptoTrack = NULL;
//  CoRevokeClassObject(x_dwRegister);
//	x_pIFactory->Release();

// NOTE!!! do not call the next line here: it should be called at the very appl. end
////	CoUninitialize();  
  
  return 0;
}

//==============================================
int g_GetLatestCoordinates( int nSensorsMax, 
                            int * pnSensors,
                            int * piFrame,
                            double * pdTimeMs,
                            double * pdXYZs ){

  int iState;
  int nSensDevMax, nSensors;
  int iDataIdx;
  tOptoFrame atOptoFrame[N_SENSORS_MAX];
  tdXYZ atCoord[N_SENSORS_MAX];
  tdXYZ atVelocity[N_SENSORS_MAX];

  g_pOptoTrack->GetOptoState( &iState );
  if( iState != 1) return 1;  // if not running
  g_pOptoTrack->GetN_Sensors( &nSensDevMax, &nSensors );
  nSensors = __min(nSensors, nSensorsMax);
  * pnSensors = nSensors;   

  if( !g_pOptoTrack->GetLatestItemIdx( &iDataIdx )) return 1;
  * piFrame = iDataIdx;
  
  //Get one frame from the buffer
  if( !g_pOptoTrack->ReadData( atOptoFrame, iDataIdx, 1 ) ) return 1;


  // Write timestamps and coordinates to arrays
  g_pOptoTrack->ParseBuffer(1,                        // N Frames
                            atOptoFrame,           // Source buffer
                            pdTimeMs,             // Dest. timestamps
                            atCoord,        // Dest. coordinates
                            atVelocity ); // Dest. velocities

  // copy data to the output buffer
  memcpy(pdXYZs, atCoord, sizeof(tdXYZ) * nSensors );

  return 0;
}

//==============================================
int g_GetSignalDistortion( int aiDistortion[N_DISPL_SENSORS] ){
  int aiBuff[N_SENSORS_MAX];

  g_pOptoTrack->GetSignalDistortion(aiBuff);
  // Note: sizeof(aiDistortion) == 4 (size of the pointer) a bug?
  memcpy( aiDistortion, aiBuff, sizeof(int)*N_DISPL_SENSORS);
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