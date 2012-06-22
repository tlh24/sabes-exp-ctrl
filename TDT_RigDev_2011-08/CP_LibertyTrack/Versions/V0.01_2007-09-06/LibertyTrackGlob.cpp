#include <windows.h>

#include "RegisterCom.h"
#include "ClassFactory.h"
#include "CP_LibertyTrackCom.h"

#include "LibertyTrack.h"
#include "LibertyTrackGlob.h"


IClassFactory *x_pIFactory;

DWORD x_dwRegister;

HWND g_hWnd;


// Here we define functions that MainDialog should know about 
// to use the CP_LibertyTrack COM server
//==============================================
int g_RegisterCOM(){

  HRESULT hr;  
  ITypeLib* pTypeLib;

  // Register typelib
  hr = LoadTypeLibEx(L"CP_LibertyTrack.exe", REGKIND_REGISTER, &pTypeLib);
  if( hr != S_OK) {
    return 1;
  }
  pTypeLib->Release();

  // Register server
  hr = g_RegisterServer( "CP_LibertyTrack.exe",  // application filename, full path is not needed
                        CLSID_CP_LibertyClass,          // ClassID GUID
                        "CP_LibertyTrack",      // Friendly name - shows up in dcomcnfg
                        "CP_LibertyTrack.Application",   // Version-independent ProgID used in late - binding
                        "CP_LibertyTrack.Application.1", // ProgID with version
                        NULL);                               // Threading model

  if( hr != S_OK) return 2;

  return 0;
}

//==============================================
int g_UnregisterCOM(){

  HRESULT hr;  

  // Unregister typelib
  hr = UnRegisterTypeLib(LIBID_CP_LibertyTrackLib,   // Typelib GUID
                         0,                 // Version Major
                         0,                 // Version Minor
                         LANG_NEUTRAL,      // LocaleID
                         SYS_WIN32);        // The target operating system
  if( hr != S_OK) { 
    return 1;
  }

  // Unregister server
  hr = g_UnregisterServer(CLSID_CP_LibertyClass, "CP_LibertyTrack.Application", "CP_LibertyTrack.Application.1");
  if( hr != S_OK) { 
    return 2;
  }

  return 0;
}


//==============================================
int g_Init_LibertyTrack( ){

//  int iRet;
  HRESULT hr;


  x_pIFactory = new CFactory();
  if( x_pIFactory == NULL) return 2;

	hr = CoRegisterClassObject( CLSID_CP_LibertyClass,     //Class identifier (CLSID) to be registered
                              x_pIFactory,     //Pointer to the class object
                              CLSCTX_LOCAL_SERVER,  //Context for running executable code
                              REGCLS_MULTIPLEUSE,  // multiple clients for the same server, we do not start a new server for each client
                              &x_dwRegister ); //Save registered object info, for future release by CoRevokeClassObject()
  if( hr != S_OK)  return 3;


  g_pLibertyTrack = new CLibertyTrack;
  if( g_pLibertyTrack == NULL )  return 4;

  return 0;
}

//==============================================
int g_OkToRelease( ){
  //TODO: implement
  return 1;
}
//==============================================
int g_Release_LibertyTrack(){

  delete g_pLibertyTrack;
  g_pLibertyTrack = NULL;
//  CoRevokeClassObject(x_dwRegister);
//	x_pIFactory->Release();

// NOTE!!! do not call the next line here: it should be called at the very appl. end
////	CoUninitialize();  
  
  return 0;
}

//==============================================
void g_OnNewData( WPARAM wParam, LPARAM lParam ) {
  if( g_pLibertyTrack ) { 
    g_pLibertyTrack->OnNewData( g_pLibertyTrack, wParam, lParam ); 
  }
}

//==============================================
// return timestamp in ms and relative coordinates: 0.0 to 1.0
int g_GetLatestCoordinates( int * pnSensors,
                            double * pdTimeStamps,
                            double pdXYZ[N_DISPL_SENSORS][N_COORD_ANGL] ){

  int iState;
  int nSensDevMax, nSensors;
  int iDataIdx;
  tLibertyFrame atLibertyFrame[N_DISPL_SENSORS];

  double pdVelocity[N_DISPL_SENSORS][N_DISPL_COORD];

  g_pLibertyTrack->GetLibertyState( &iState );
  if( iState != 3) return 1;  // if not connected and running
  g_pLibertyTrack->GetN_Sensors( &nSensDevMax, &nSensors );
  if( nSensors > N_DISPL_SENSORS ) return 1;  // just in case

  if( !g_pLibertyTrack->GetLatestItemIdx( &iDataIdx )) return 1;
  
  //Get one frame from the buffer
  if( !g_pLibertyTrack->ReadData( atLibertyFrame, iDataIdx, 1 ) ) return 1;


  // Write timestamps and coordinates to SAFEARRAYs
  g_pLibertyTrack->ParseBuffer(1,                        // N Frames
                               atLibertyFrame,           // Source buffer
                               pdTimeStamps,             // Dest. timestamps
                              (tdXYZ *) pdXYZ,        // Dest. coordinates
                              (tdXYZ *) pdVelocity ); // Dest. velocities

  * pnSensors = nSensors;                         
  return 0;
}


int g_GetSignalDistortion( int aiDistortion[N_DISPL_SENSORS] ){

  g_pLibertyTrack->GetSignalDistortion(aiDistortion);

  return 0;
}
//==============================================
int g_CmdStart(){
  g_pLibertyTrack->ConnectLiberty();
  return 0;
}

//==============================================
int g_CmdStop(){
  g_pLibertyTrack->FinishAndDisconnect();
  return 0;
}

//==============================================
HWND g_GetWindowHandle(){
  return g_hWnd;
}

//==============================================
void g_GetLibertyResult( char ** pszResult, int * piResult  ){
  g_pLibertyTrack->GetLibertyResult(pszResult, piResult);
}
