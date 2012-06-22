// CP_LibertyClass - implementation of COM object

//#include "ShadowPrint.h"
#include "CP_LibertyClass.h"
#include "LibertyTrack.h"
#include "CP_printf.h"
#include "SafeArrayLib.h"


//===============================================================================
// CP_LibertyClass
CP_LibertyClass::CP_LibertyClass() : m_cRef(0) { 

  CoAddRefServerProcess();
}

//-------------------------------------------------------
HRESULT CP_LibertyClass::m_ErrorToHresult( int iErr ){
   return MAKE_HRESULT( SEVERITY_ERROR,  //  Indicate that function failed
                        FACILITY_ITF,    //  Specific interface - related error 
                        iErr ); // Our own error code
}


//-------------------------------------------------------
HRESULT CP_LibertyClass::QueryInterface(REFIID iid, void **ppv){

  if (ppv == NULL) return E_INVALIDARG;
  if(iid == IID_IUnknown)	{
    *ppv = (IUnknown*)this;
  }
  else if(iid == IID_IDispatch)	{
    *ppv = (IDispatch*)this; 
  }
  else if(iid == IID_ILibertyTrack)	{
    *ppv = (ILibertyTrack*)this;
  }
	else{
		*ppv = NULL;
		return E_NOINTERFACE;
	}
	AddRef();
	return S_OK;
}

//==============================================================================
HRESULT CP_LibertyClass::GetTypeInfo(UINT iTypeInfo, LCID lcid, ITypeInfo** ppITypeInfo){

  *ppITypeInfo = NULL;
	m_pTypeInfo->AddRef();
	*ppITypeInfo = m_pTypeInfo;
	return S_OK;
}

//==============================================================================
HRESULT CP_LibertyClass::GetVersion( BSTR * pbstVersion){
  g_pLibertyTrack->GetVersion( pbstVersion );
	return S_OK;
}

//==============================================================================
HRESULT CP_LibertyClass::ConnectTracker(){
  int iRes;

  iRes = g_pLibertyTrack->ConnectLiberty();
	return S_OK;
}
//==============================================================================
HRESULT CP_LibertyClass::DisconnectTracker(){
  int iRes;

  iRes = g_pLibertyTrack->FinishAndDisconnect();
	return S_OK;
}

//==============================================================================
HRESULT CP_LibertyClass::GetTrackerState(long * piTrackerID,
                                         long * piState ){
  int iRes;

  * piTrackerID = 1;   // Liberty ID
  iRes = g_pLibertyTrack->GetLibertyState( (int *)piState );
  if( iRes ) return m_ErrorToHresult( iRes );
	return S_OK;
}

//==============================================================================
HRESULT CP_LibertyClass::GetTimeScale( double *pdC0,
                                       double *pdC1){
  int iRes;

  iRes = g_pLibertyTrack->GetTimeScale( pdC0, pdC1);
  if( iRes ){
    CP_printf("\nError: GetTimeScale() failed!\n" );
    return m_ErrorToHresult( 1 );
  }
	return S_OK;
}

//==============================================================================
HRESULT CP_LibertyClass::SetTimeScale( double dC0,
                                       double dC1){
  int iRes;

  iRes = g_pLibertyTrack->SetTimeScale( dC0, dC1);
  if( iRes ){
    CP_printf("\nError: GetTimeScale() failed!\n" );
    return m_ErrorToHresult( 1 );
  }
  return S_OK;
}

//==============================================================================
HRESULT CP_LibertyClass::GetTransformMatrix(long iTransformIdx,
                                            SAFEARRAY ** ppsaTransform){
  int iRes;
  SAFEARRAY *psaMtx;
  double * pdData;

  // Output 4x3 array of floats
  if( g_MakeSafeArray( TRANSFORM_N_J, TRANSFORM_N_I, &psaMtx, &pdData ) ){
    return m_ErrorToHresult(1);
  }

  iRes = g_pLibertyTrack->GetTransformMatrix( iTransformIdx-1, pdData );
  SafeArrayUnaccessData( psaMtx );
  if( iRes ){
    CP_printf("\nError: GetTransformMatrix() failed!\n" );
    return m_ErrorToHresult( 1 );
  }

  * ppsaTransform = psaMtx;
  return S_OK;
}

//==============================================================================
HRESULT CP_LibertyClass::SetTransformMatrix( SAFEARRAY * psaTransform,
                                             long iTransformIdx){
  int iRes;
  double * pdData;

  // We expect 4x3 array of floats
  if( g_CheckSafeArray( TRANSFORM_N_J, TRANSFORM_N_I, psaTransform, &pdData )) {
    SafeArrayUnaccessData( psaTransform );
    return m_ErrorToHresult( 1 );
  }
  iRes = g_pLibertyTrack->SetTransformMatrix( iTransformIdx-1, pdData );
  SafeArrayUnaccessData( psaTransform );
  if( iRes ){
    CP_printf("\nError: SetTransformMatrix() failed!\n" );
    return m_ErrorToHresult( 1 );
  }

  return S_OK;
}

//==============================================================================
HRESULT CP_LibertyClass::GetSensors( SAFEARRAY ** ppsaSensors){
  int iRes, iParam;
  SAFEARRAY *psaMtx;
  int * piParams;

  int nSensDevMax, nSensors;

  * ppsaSensors = NULL;
  iRes = g_pLibertyTrack->GetN_Sensors( &nSensDevMax, &nSensors );

  // Output 3xN array of ints
  if( g_MakeSafeArray( N_SENSOR_PARAMS, nSensors, &psaMtx, &piParams ) ) {
    return m_ErrorToHresult(1);
  }

  iRes = g_pLibertyTrack->GetSensors( (tSensorInfo *) piParams );
  // Convert indecies from 0 based to 1 based
  for( iParam=0; iParam < (nSensors * N_SENSOR_PARAMS); iParam++){
    piParams[iParam]++;
  }
  SafeArrayUnaccessData( psaMtx );
  if( iRes ){
    CP_printf("\nError: GetSensors()failed!\n" );
    return m_ErrorToHresult( 1 );
  }
  

  * ppsaSensors = psaMtx;
  return S_OK;
}

//==============================================================================
HRESULT CP_LibertyClass::SetSensors( SAFEARRAY * psaSensors){
  int iRes, nParams, nSensors, iSensor;
  int * piParams;
  tSensorInfo atSensorInfo[N_SENSORS_MAX];

  // We expect 2xN array of ints where N <= N_SENSORS_MAX
  if( g_CheckSafeArray( &nParams, &nSensors, psaSensors,  &piParams )){
    SafeArrayUnaccessData( psaSensors );
    return m_ErrorToHresult( 1 );
  }

  if( (nSensors < 1) || (nSensors > N_SENSORS_MAX) ) {
    CP_printf("SetSensors: incorrect number of sensors: %d, should be > 1 and <= %d\n", 
                                                            nSensors, N_SENSORS_MAX );
    SafeArrayUnaccessData( psaSensors );
    return m_ErrorToHresult( 1 );
  }

  if( (nParams < 1) || (nParams > N_SENSOR_PARAMS) ) {
    CP_printf("SetSensors: incorrect number of paramters: %d, should be > 1 and <= %d\n", 
                                                            nParams, N_SENSOR_PARAMS );
    SafeArrayUnaccessData( psaSensors );
    return m_ErrorToHresult( 1 );
  }

  // copy data to the buffer filling in missing params with defaults
  for( iSensor = 0; iSensor < nSensors; iSensor++) {

    // Sensor index
    atSensorInfo[iSensor].iSensor = (*piParams) - 1; // Input index is 1-based
    piParams++;

    // Port index
    if( nParams < 2 ) {  // we are mising Port index, set to default = 0
      atSensorInfo[iSensor].iPort = 0;
    }
    else{
      atSensorInfo[iSensor].iPort = (*piParams) - 1 ; // Input index is 1-based
      piParams++;
    }
  }
  SafeArrayUnaccessData( psaSensors );

  iRes = g_pLibertyTrack->SetSensors( nSensors, atSensorInfo );
  if( iRes ) return m_ErrorToHresult( iRes );

  return S_OK;
}

//==============================================================================
HRESULT CP_LibertyClass::ActivateSensors( ){
	return S_OK;  // ignored, used for compatibility with CP_OptoTrack
}

//==============================================================================
HRESULT CP_LibertyClass::DeactivateSensors( ){
	return S_OK;  //  ignored, used for compatibility with CP_OptoTrack
} 

//==============================================================================
HRESULT CP_LibertyClass::GetSensorsTransformIdx( SAFEARRAY ** ppsaTransformIdx){
  int iRes, iSensor;
  SAFEARRAY *psaMtx;
  int * piTransIdx;
  int nSensDevMax, nSensors;

  *ppsaTransformIdx = NULL;
  iRes = g_pLibertyTrack->GetN_Sensors( &nSensDevMax, &nSensors );

  // Output 1xN array of ints
  if( g_MakeSafeArray( nSensors, &psaMtx, &piTransIdx ) ) {
    return m_ErrorToHresult(1);
  }

  iRes = g_pLibertyTrack->GetSensorsTransformIdx( piTransIdx );
  if( iRes ) {
    SafeArrayUnaccessData( psaMtx );
    return m_ErrorToHresult( iRes );
  }
  for( iSensor = 0; iSensor < nSensors; iSensor++) {
    piTransIdx[iSensor] ++; // Output index is 1-based, internal is 0-based
  }

  SafeArrayUnaccessData( psaMtx );
  *ppsaTransformIdx = psaMtx;
  return S_OK;
}

//==============================================================================
HRESULT CP_LibertyClass::SetSensorsTransformIdx( SAFEARRAY * psaTransformIdx){
  int nSensors;
  int * piTransIdx;
  int iSensor;
  int iRes;
 
  // We expect array of ints 
  if( g_CheckSafeArray( &nSensors,  psaTransformIdx, &piTransIdx )){
    SafeArrayUnaccessData( psaTransformIdx );
    return m_ErrorToHresult( 1 );
  }

  for( iSensor = 0; iSensor < nSensors; iSensor++) {
    piTransIdx[iSensor] --; // Input index is 1-based, internal is 0-based
  }


  iRes = g_pLibertyTrack->SetSensorsTransformIdx( nSensors, piTransIdx );
  SafeArrayUnaccessData( psaTransformIdx );
  if( iRes ) return m_ErrorToHresult( iRes );

  return S_OK;
}

//==============================================================================
HRESULT CP_LibertyClass::GetBufferSize( long *pnFrames){

  *pnFrames = g_pLibertyTrack->GetBufferSizeInItems( );
	return S_OK;
}

//==============================================================================
HRESULT CP_LibertyClass::GetDataIndexLatest( long *piDataIdx ){

  *piDataIdx = 0;
  if(!g_pLibertyTrack->GetLatestItemIdx( (int *) piDataIdx )){
    CP_printf("\nError in GetDataIndexLatest(), check if Liberty is connected.\n");
    return m_ErrorToHresult(1);
  }
  return S_OK;
}

//==============================================================================
HRESULT CP_LibertyClass::GetSensorLatest( long iSensorIdx,
                                          long nFrames,
                                          long *piDataIdx,
                                          SAFEARRAY ** ppsaTimeStampMs,
                                          SAFEARRAY ** ppsaCoord,
                                          SAFEARRAY ** ppsaVelocity ){
  
  int iStartIdx, iEndIdx;

  *piDataIdx = 0;
  if(!g_pLibertyTrack->GetLatestItemIdx( &iEndIdx )){
    CP_printf("\nError in GetDataIndexLatest(), check if Liberty is connected.\n");
    return m_ErrorToHresult(1);
  }
  *piDataIdx = iEndIdx;

  iStartIdx = iEndIdx - nFrames + 1;   // this will make last frame iEndIdx
	return GetSensorBuffered( iSensorIdx,
                            iStartIdx,
                            nFrames,
                            ppsaTimeStampMs,
                            ppsaCoord,
                            ppsaVelocity );
}

//==============================================================================
HRESULT CP_LibertyClass::GetSensorBuffered( long iSensorIdx,
                                            long iDataIdx,
                                            long nFrames,
                                            SAFEARRAY ** ppsaTimeStampMs,
                                            SAFEARRAY ** ppsaCoord,
                                            SAFEARRAY ** ppsaVelocity ){

  int iErr = 0;
  int nSensDevMax, nSensors;
  int iSensor;
  void * pBuf;
  SAFEARRAY *psaTime;
  double * pdTimeStamps;
  SAFEARRAY * psaCoord;
  double * pdCoord;
  SAFEARRAY * psaVelocity;
  double * pdVelocity;

  pBuf = NULL; 
  psaTime = NULL;
  psaCoord = NULL;
  psaVelocity = NULL;
  //Set return pointers
  *ppsaTimeStampMs = NULL;
  *ppsaCoord = NULL;
  *ppsaVelocity = NULL;

  g_pLibertyTrack->GetN_Sensors( &nSensDevMax, &nSensors );
  // check input sensor index (input sensors start from 1)
  if( iSensorIdx < 1 || iSensorIdx > nSensors ) {
    CP_printf("\nGetSensorBuffered(): invalid sensor requested: %d\n", iSensorIdx);
    return m_ErrorToHresult( 1 );
  }
  iSensor = iSensorIdx-1;  // input sensors start from 1, internal from 0

  // Create receiving buffer
  pBuf = malloc(nFrames * g_pLibertyTrack->GetItemSizeInBytes());
  if(!pBuf) { 
    iErr = 1;
    goto errCleanUp; 
  }

  //Get data from the buffer
  if( ! g_pLibertyTrack->ReadData( pBuf, iDataIdx, nFrames ) ){
    iErr = 1;
    goto errCleanUp; 
  }

  //  Timestamps
  // Create output SAFEARRAY of doubles, size nFrames 
  if( g_MakeSafeArray( nFrames, &psaTime, &pdTimeStamps )){
    iErr = 1;
    goto errCleanUp; 
  }
  // Coordinates
  // Create output SAFEARRAY of floats, size nFrames x 6 (3 coords and 3 angles) 
  if( g_MakeSafeArray( N_COORD * 2, nFrames, &psaCoord, &pdCoord )){
    iErr = 1;
    goto errCleanUp; 
  }
  // Velocities
  // Create output SAFEARRAY of floats, size nFrames x 3 
  if( g_MakeSafeArray( N_COORD, nFrames, &psaVelocity, &pdVelocity )){
    iErr = 1;
    goto errCleanUp; 
  }

  // Write timestamps and coordinates to SAFEARRAYs
  g_pLibertyTrack->ParseBuffer(iSensor,
                               nFrames, 
                               pBuf,                     // Source buffer
                               pdTimeStamps,             // Dest. timestamps
                              (tdXYZ *) pdCoord,      // Dest. coordinates and angles
                              (tdXYZ *) pdVelocity ); // Dest. velocities
  
  SafeArrayUnaccessData( psaTime );
  SafeArrayUnaccessData( psaCoord );
  SafeArrayUnaccessData( psaVelocity );
  if( pBuf) free( pBuf );

  *ppsaTimeStampMs = psaTime;
  *ppsaCoord = psaCoord;
  *ppsaVelocity = psaVelocity;
  return S_OK;

errCleanUp:

  if( pBuf) free( pBuf );
  if( psaTime ) {
    SafeArrayUnaccessData( psaTime );
    SafeArrayDestroy( psaTime );
  }
  if( psaCoord ) {
    SafeArrayUnaccessData( psaCoord );
    SafeArrayDestroy( psaCoord );
  }
  if( psaVelocity ) {
    SafeArrayUnaccessData( psaVelocity );
    SafeArrayDestroy( psaVelocity );
  }

  * ppsaTimeStampMs = NULL;
  * ppsaCoord = NULL;
  * ppsaVelocity = NULL;

  return m_ErrorToHresult(iErr);
}

//==============================================================================
HRESULT CP_LibertyClass::GetAllSensorsLatest( long nFrames,
                                              long *piDataIdx,
                                              SAFEARRAY ** ppsaTimeStampMs,
                                              SAFEARRAY ** ppsaCoord,
                                              SAFEARRAY ** ppsaVelocity ){
  int iStartIdx, iEndIdx;
  
  *piDataIdx = 0;
  if(!g_pLibertyTrack->GetLatestItemIdx( &iEndIdx )){
    CP_printf("\nError in GetDataIndexLatest(), check if Liberty is connected.\n");
    return m_ErrorToHresult(1);
  }
  *piDataIdx = iEndIdx;

  iStartIdx = iEndIdx - nFrames + 1;   // this will make last frame iEndIdx
	return GetAllSensorsBuffered( iStartIdx,
                                nFrames,
                                ppsaTimeStampMs,
                                ppsaCoord,
                                ppsaVelocity );

}

//==============================================================================
HRESULT CP_LibertyClass::GetAllSensorsBuffered( long iDataIdx,
                                                long nFrames,
                                                SAFEARRAY ** ppsaTimeStampMs,
                                                SAFEARRAY ** ppsaCoord,
                                                SAFEARRAY ** ppsaVelocity ){
  int iErr = 0;
  int nSensDevMax, nSensors;
  void * pBuf;
  SAFEARRAY *psaTime;
  double * pdTimeStamps;
  SAFEARRAY * psaCoord;
  double * pdCoord;
  SAFEARRAY * psaVelocity;
  double * pdVelocity;

  pBuf = NULL; 
  psaTime = NULL;
  psaCoord = NULL;
  psaVelocity = NULL;
  //Set return pointers
  *ppsaTimeStampMs = NULL;
  *ppsaCoord = NULL;
  *ppsaVelocity = NULL;

  g_pLibertyTrack->GetN_Sensors( &nSensDevMax, &nSensors );
  // Create receiving buffer
  pBuf = malloc(nFrames * g_pLibertyTrack->GetItemSizeInBytes());
  if(!pBuf) { 
    iErr = 1;
    goto errCleanUp; 
  }

  //Get data from the buffer
  if( ! g_pLibertyTrack->ReadData( pBuf, iDataIdx, nFrames ) ){
    iErr = 1;
    goto errCleanUp; 
  }

  //  Timestamps
  // Create output SAFEARRAY of doubles, size nFrames 
  if( g_MakeSafeArray( nFrames, &psaTime, &pdTimeStamps )){
    iErr = 1;
    goto errCleanUp; 
  }
  // Coordinates
  // Create output SAFEARRAY of floats, size nFrames x ( 6 x nSensors), 6 = (3 coords and 3 angles) 
  if( g_MakeSafeArray( N_COORD * 2 * nSensors, nFrames, &psaCoord, &pdCoord )){
    iErr = 1;
    goto errCleanUp; 
  }
  // Velocities
  // Create output SAFEARRAY of floats, size nFrames x 3 
  if( g_MakeSafeArray( N_COORD * nSensors, nFrames, &psaVelocity, &pdVelocity )){
    iErr = 1;
    goto errCleanUp; 
  }

  // Write timestamps and coordinates to SAFEARRAYs
  g_pLibertyTrack->ParseBuffer(nFrames, 
                               pBuf,                  // Source buffer
                               pdTimeStamps,          // Dest. timestamps
                              (tdXYZ *) pdCoord,      // Dest. coordinates
                              (tdXYZ *) pdVelocity ); // Dest. velocities
  
  SafeArrayUnaccessData( psaTime );
  SafeArrayUnaccessData( psaCoord );
  SafeArrayUnaccessData( psaVelocity );
  if( pBuf) free( pBuf );

  *ppsaTimeStampMs = psaTime;
  *ppsaCoord = psaCoord;
  *ppsaVelocity = psaVelocity;
  return S_OK;

errCleanUp:

  if( pBuf) free( pBuf );
  if( psaTime ) {
    SafeArrayUnaccessData( psaTime );
    SafeArrayDestroy( psaTime );
  }
  if( psaCoord ) {
    SafeArrayUnaccessData( psaCoord );
    SafeArrayDestroy( psaCoord );
  }
  if( psaVelocity ) {
    SafeArrayUnaccessData( psaVelocity );
    SafeArrayDestroy( psaVelocity );
  }

  * ppsaTimeStampMs = NULL;
  * ppsaCoord = NULL;
  * ppsaVelocity = NULL;

  return m_ErrorToHresult(iErr);
}


//==============================================================================



