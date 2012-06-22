// CP_OptoClass - implementation of COM object

#include "CP_OptoClass.h"
#include "OptoTrack.h"
#include "VariantLib.h"
#include "CP_printf.h"

extern COptoTrack * g_pOptoTrack;   // from OptoTrackGlob.cpp


//===============================================================================
// CP_OptoClass
CP_OptoClass::CP_OptoClass() : m_cRef(0) { 

  CoAddRefServerProcess();
}

//-------------------------------------------------------
HRESULT CP_OptoClass::m_ErrorToHresult( int iErr ){
   return MAKE_HRESULT( SEVERITY_ERROR,  //  Indicate that function failed
                        FACILITY_ITF,    //  Specific interface - related error 
                        iErr ); // Our own error code
}

//-------------------------------------------------------
HRESULT CP_OptoClass::QueryInterface(REFIID iid, void **ppv){

  if (ppv == NULL) return E_INVALIDARG;
  if(iid == IID_IUnknown)	{
    *ppv = (IUnknown*)this;
  }
  else if(iid == IID_IDispatch)	{
    *ppv = (IDispatch*)this; 
  }
  else if(iid == IID_IOptoTrack)	{
    *ppv = (IOptoTrack*)this;
  }
	else{
		*ppv = NULL;
		return E_NOINTERFACE;
	}
	AddRef();
	return S_OK;
}

//-------------------------------------------------------
HRESULT CP_OptoClass::GetTypeInfo(UINT iTypeInfo, LCID lcid, ITypeInfo** ppITypeInfo){

  *ppITypeInfo = NULL;
	m_pTypeInfo->AddRef();
	*ppITypeInfo = m_pTypeInfo;
	return S_OK;
}



//==============================================================================
HRESULT CP_OptoClass::GetVersion( BSTR * pbstVersion){
  g_pOptoTrack->GetVersion( pbstVersion );
	return S_OK;
}

//==============================================================================
HRESULT CP_OptoClass::ConnectTracker(){
  int iRes;

  iRes = g_pOptoTrack->ConnectOpto();
	return S_OK;
}

//==============================================================================
HRESULT CP_OptoClass::DisconnectTracker(){
  int iRes;

  iRes = g_pOptoTrack->DisconnectOpto();
	return S_OK;
}

//==============================================================================
HRESULT CP_OptoClass::GetTrackerState(long * piTrackerID,
                                         long * piState ){
  int iRes;

  *piTrackerID = 2; // 1 = Liberty, 2 = OptoTrack
  iRes = g_pOptoTrack->GetOptoState( (int *)piState );
  if( iRes ){
    CP_printf("\nError: GetTrackerState() failed!\n" );
    return m_ErrorToHresult( iRes );
  }
  return S_OK;
}

//==============================================================================
HRESULT CP_OptoClass::GetFrameCount( long * pnFrames ){
  int iRes;

  iRes = g_pOptoTrack->GetFrameCount( (int *)pnFrames );
  if( iRes ){
    CP_printf("\nError: GetFrameCount() failed!\n" );
    return m_ErrorToHresult( 1 );
  }
	return S_OK;
}

//==============================================================================
HRESULT CP_OptoClass::GetTimeScale( double *pdC0,
                                       double *pdC1){
  int iRes;

  iRes = g_pOptoTrack->GetTimeScale( pdC0, pdC1);
  if( iRes ){
    CP_printf("\nError: GetTimeScale() failed!\n" );
    return m_ErrorToHresult( 1 );
  }
	return S_OK;
}

//==============================================================================
HRESULT CP_OptoClass::SetTimeScale( double dC0,
                                    double dC1){
  int iRes;

  iRes = g_pOptoTrack->SetTimeScale( dC0, dC1);
  if( iRes ){
    CP_printf("\nError: GetTimeScale() failed!\n" );
    return m_ErrorToHresult( 1 );
  }
  return S_OK;
}

//==============================================================================
HRESULT CP_OptoClass::GetTransformMatrix(long iTransformIdx,
                                            VARIANT * pvTransform){
  int iRes;
  double * pdData;

  // Output 4x3 array of doubles
  if( g_MakeVariantArray( TRANSFORM_N_J, TRANSFORM_N_I, pvTransform, &pdData ) ){
    return m_ErrorToHresult(1);
  }

  iRes = g_pOptoTrack->GetTransformMatrix( iTransformIdx-1, pdData );
  SafeArrayUnaccessData( pvTransform->parray );
  if( iRes ){
    VariantClear(pvTransform);
    CP_printf("\nError: GetTransformMatrix() failed!\n" );
    return m_ErrorToHresult( 1 );
  }

  return S_OK;
}

//==============================================================================
HRESULT CP_OptoClass::SetTransformMatrix( VARIANT vTransform,
                                             long iTransformIdx){
  int iRes;
  double * pdData;

  // We expect 4x3 array of doubles
  if( g_CheckVariantArray( TRANSFORM_N_J, TRANSFORM_N_I, vTransform, &pdData )) {
    SafeArrayUnaccessData( vTransform.parray );
    return m_ErrorToHresult( 1 );
  }
  iRes = g_pOptoTrack->SetTransformMatrix( iTransformIdx-1, pdData );
  SafeArrayUnaccessData( vTransform.parray );
  if( iRes ){
    CP_printf("\nError: SetTransformMatrix() failed!\n" );
    return m_ErrorToHresult( 1 );
  }

  return S_OK;
}

//==============================================================================
HRESULT CP_OptoClass::GetSensors( VARIANT * pvSensors){
  int iRes, iParam;
  int * piParams;

  int nSensDevMax, nSensors;

  iRes = g_pOptoTrack->GetN_Sensors( &nSensDevMax, &nSensors );

  // Output 3xN array of ints
  if( g_MakeVariantArray( N_SENSOR_PARAMS, nSensors, pvSensors, &piParams ) ) {
    return m_ErrorToHresult(1);
  }

  iRes = g_pOptoTrack->GetSensors( (tSensorInfo *) piParams );
  // Convert indexes from 0 based to 1 based
  for( iParam=0; iParam < (nSensors * N_SENSOR_PARAMS); iParam++){
    piParams[iParam]++;
  }
  SafeArrayUnaccessData( pvSensors->parray );
  if( iRes ){
    VariantClear(pvSensors);
    CP_printf("\nError: GetSensors()failed!\n" );
    return m_ErrorToHresult( 1 );
  }
  
  return S_OK;
}

//==============================================================================
HRESULT CP_OptoClass::SetSensors( VARIANT vSensors){
  int iRes, nParams, nSensors, iSensor;
  int * piParams;
  tSensorInfo atSensorInfo[N_SENSORS_MAX];

  // We expect NxN array of ints 
  if( g_CheckVariantArray( &nParams, &nSensors, vSensors,  &piParams )){
    SafeArrayUnaccessData( vSensors.parray );
    return m_ErrorToHresult( 1 );
  }

  if( (nSensors < 1) || (nSensors > N_SENSORS_MAX) ) {
    CP_printf("SetSensors: incorrect number of sensors: %d, should be > 1 and <= %d\n", 
                                                            nSensors, N_SENSORS_MAX );
    SafeArrayUnaccessData( vSensors.parray );
    return m_ErrorToHresult( 1 );
  }

  if( (nParams < 1) || (nParams > N_SENSOR_PARAMS) ) {
    CP_printf("SetSensors: incorrect number of paramters: %d, should be > 1 and <= %d\n", 
                                                            nParams, N_SENSOR_PARAMS );
    SafeArrayUnaccessData( vSensors.parray );
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
  SafeArrayUnaccessData( vSensors.parray );

  iRes = g_pOptoTrack->SetSensors( nSensors, atSensorInfo );
  if( iRes ) return m_ErrorToHresult( iRes );

  return S_OK;
}

//==============================================================================
HRESULT CP_OptoClass::ActivateSensors( ){
  int iRes;

  iRes = g_pOptoTrack->ActivateSensors(  );
  if( iRes ){
    CP_printf("\nError: ActivateSensors() failed!\n" );
    return m_ErrorToHresult( 1 );
  }
	return S_OK;  
}

//==============================================================================
HRESULT CP_OptoClass::DeactivateSensors( ){  
  int iRes;

  iRes = g_pOptoTrack->DeactivateSensors(  );
  if( iRes ){
    CP_printf("\nError: DeactivateSensors() failed!\n" );
    return m_ErrorToHresult( 1 );
  }
	return S_OK;  

} 

//==============================================================================
HRESULT CP_OptoClass::GetSensorsTransformIdx( VARIANT * pvTransformIdx){
  int iRes, iSensor;
  int * piTransIdx;
  int nSensDevMax, nSensors;

  iRes = g_pOptoTrack->GetN_Sensors( &nSensDevMax, &nSensors );

  // Output 1xN array of ints
  if( g_MakeVariantArray( nSensors, pvTransformIdx, &piTransIdx ) ) {
    return m_ErrorToHresult(1);
  }

  iRes = g_pOptoTrack->GetSensorsTransformIdx( piTransIdx );
  if( iRes ) {
    SafeArrayUnaccessData( pvTransformIdx->parray );
    VariantClear(pvTransformIdx);
    return m_ErrorToHresult( iRes );
  }
  for( iSensor = 0; iSensor < nSensors; iSensor++) {
    piTransIdx[iSensor] ++; // Output index is 1-based, internal is 0-based
  }

  SafeArrayUnaccessData( pvTransformIdx->parray );
  return S_OK;
}

//==============================================================================
HRESULT CP_OptoClass::SetSensorsTransformIdx( VARIANT vTransformIdx){
  int nSensors;
  int * piTransIdx;
  int iSensor;
  int iRes;
 
  // We expect 1-D array of ints 
  if( g_CheckVariantArray( &nSensors,  vTransformIdx, &piTransIdx )){
    SafeArrayUnaccessData( vTransformIdx.parray );
    return m_ErrorToHresult( 1 );
  }

  for( iSensor = 0; iSensor < nSensors; iSensor++) {
    piTransIdx[iSensor] --; // Input index is 1-based, internal is 0-based
  }


  iRes = g_pOptoTrack->SetSensorsTransformIdx( nSensors, piTransIdx );
  SafeArrayUnaccessData( vTransformIdx.parray );
  if( iRes ) return m_ErrorToHresult( iRes );

  return S_OK;
}

//==============================================================================
HRESULT CP_OptoClass::GetBufferSize( long *pnFrames){

  *pnFrames = g_pOptoTrack->GetBufferSizeInItems( );
	return S_OK;
}

//==============================================================================
HRESULT CP_OptoClass::GetDataIndexLatest( long *piDataIdx ){

  *piDataIdx = 0;
  if(!g_pOptoTrack->GetLatestItemIdx( (int *) piDataIdx )){
    CP_printf("\nError in GetDataIndexLatest(), check if Opto is connected.\n");
    return m_ErrorToHresult(1);
  }
  return S_OK;
}

//==============================================================================
HRESULT CP_OptoClass::GetSensorLatest( long iSensorIdx,
                                          long nFrames,
                                          long *piDataIdx,
                                          VARIANT * pvTimeStamp,
                                          VARIANT * pvCoord,
                                          VARIANT * pvVelocity ){
  
  int iStartIdx, iEndIdx;

  *piDataIdx = 0;
  if(!g_pOptoTrack->GetLatestItemIdx( &iEndIdx )){
    CP_printf("\nError in GetDataIndexLatest(), check if Opto is connected.\n");
    return m_ErrorToHresult(1);
  }
  *piDataIdx = iEndIdx;

  iStartIdx = iEndIdx - nFrames + 1;   // this will make last frame iEndIdx
	return GetSensorBuffered( iSensorIdx,
                            iStartIdx,
                            nFrames,
                            pvTimeStamp,
                            pvCoord,
                            pvVelocity );
}

//==============================================================================
HRESULT CP_OptoClass::GetSensorBuffered( long iSensorIdx,
                                            long iDataIdx,
                                            long nFrames,
                                            VARIANT * pvTimeStamp,
                                            VARIANT * pvCoord,
                                            VARIANT * pvVelocity ){

  int iErr = 0;
  int nSensDevMax, nSensors;
  int iSensor;
  void * pBuf;
  double * pdTimeStamp;
  double * pdCoord;
  double * pdVelocity;

  pBuf = NULL; 

  g_pOptoTrack->GetN_Sensors( &nSensDevMax, &nSensors );
  // check input sensor index (input sensors start from 1)
  if( iSensorIdx < 1 || iSensorIdx > nSensors ) {
    CP_printf("\nGetSensorBuffered(): invalid sensor requested: %d\n", iSensorIdx);
    return m_ErrorToHresult( 1 );
  }
  iSensor = iSensorIdx-1;  // input sensors start from 1, internal from 0

  // Create receiving buffer
  pBuf = malloc(nFrames * g_pOptoTrack->GetItemSizeInBytes());
  if(!pBuf) { 
    iErr = 1;
    goto errCleanUp; 
  }

  //Get data from the buffer
  if( ! g_pOptoTrack->ReadData( pBuf, iDataIdx, nFrames ) ){
    iErr = 1;
    goto errCleanUp; 
  }

  //  Timestamps
  // Create output array of doubles, size nFrames 
  if( g_MakeVariantArray( nFrames, pvTimeStamp, &pdTimeStamp )){
    iErr = 1;
    goto errCleanUp; 
  }
  // Coordinates
  // Create output array of doubles, size nFrames x 6 (3 coords and 3 angles) 
  if( g_MakeVariantArray( N_COORD * 2, nFrames, pvCoord, &pdCoord )){
    iErr = 1;
    goto errCleanUp; 
  }
  // Velocities
  // Create output array of doubles, size nFrames x 3 
  if( g_MakeVariantArray( N_COORD, nFrames, pvVelocity, &pdVelocity )){
    iErr = 1;
    goto errCleanUp; 
  }

  // Write timestamps and coordinates to SAFEARRAYs
  g_pOptoTrack->ParseBuffer( iSensor,
                             nFrames, 
                             pBuf,                     // Source buffer
                             pdTimeStamp,             // Dest. timestamps
                            (tdXYZ *) pdCoord,      // Dest. coordinates and angles
                            (tdXYZ *) pdVelocity ); // Dest. velocities
  
  SafeArrayUnaccessData( pvTimeStamp->parray );
  SafeArrayUnaccessData( pvCoord->parray );
  SafeArrayUnaccessData( pvVelocity->parray );
  if( pBuf) free( pBuf );

  return S_OK;

errCleanUp:

  if( pBuf) free( pBuf );
  if( pvTimeStamp->parray ) {
    SafeArrayUnaccessData( pvTimeStamp->parray );
    VariantClear( pvTimeStamp );
  }
  if( pvCoord->parray ) {
    SafeArrayUnaccessData( pvCoord->parray );
    VariantClear( pvCoord );
  }
  if( pvVelocity->parray ) {
    SafeArrayUnaccessData( pvVelocity->parray );
    VariantClear( pvVelocity );
  }


  return m_ErrorToHresult(iErr);
}

//==============================================================================
HRESULT CP_OptoClass::GetAllSensorsLatest( long nFrames,
                                              long *piDataIdx,
                                              VARIANT * pvTimeStamp,
                                              VARIANT * pvCoord,
                                              VARIANT * pvVelocity ){
  int iStartIdx, iEndIdx;
  
  *piDataIdx = 0;
  if(!g_pOptoTrack->GetLatestItemIdx( &iEndIdx )){
    CP_printf("\nError in GetDataIndexLatest(), check if OptoTrak is connected.\n");
    return m_ErrorToHresult(1);
  }
  *piDataIdx = iEndIdx;

  iStartIdx = iEndIdx - nFrames + 1;   // this will make last frame iEndIdx
	return GetAllSensorsBuffered( iStartIdx,
                                nFrames,
                                pvTimeStamp,
                                pvCoord,
                                pvVelocity );

}

//==============================================================================
HRESULT CP_OptoClass::GetAllSensorsBuffered( long iDataIdx,
                                                long nFrames,
                                                VARIANT * pvTimeStamp,
                                                VARIANT * pvCoord,
                                                VARIANT * pvVelocity ){
  int iErr = 0;
  int nSensDevMax, nSensors;
  void * pBuf;
  double * pdTimeStamp;
  double * pdCoord;
  double * pdVelocity;

  pBuf = NULL; 

  g_pOptoTrack->GetN_Sensors( &nSensDevMax, &nSensors );
  // Create receiving buffer
  pBuf = malloc(nFrames * g_pOptoTrack->GetItemSizeInBytes());
  if(!pBuf) { 
    iErr = 1;
    goto errCleanUp; 
  }

  //Get data from the buffer
  if( ! g_pOptoTrack->ReadData( pBuf, iDataIdx, nFrames ) ){
    iErr = 1;
    goto errCleanUp; 
  }

  //  Timestamps
  // Create output array of doubles, size nFrames 
  if( g_MakeVariantArray( nFrames, pvTimeStamp, &pdTimeStamp )){
    iErr = 1;
    goto errCleanUp; 
  }
  // Coordinates
  // Create output array of doubles, size nFrames x ( 6 x nSensors), 6 = (3 coords and 3 angles) 
  if( g_MakeVariantArray( N_COORD * 2 * nSensors, nFrames, pvCoord, &pdCoord )){
    iErr = 1;
    goto errCleanUp; 
  }
  // Velocities
  // Create output array of doubles, size nFrames x 3 
  if( g_MakeVariantArray( N_COORD * nSensors, nFrames, pvVelocity, &pdVelocity )){
    iErr = 1;
    goto errCleanUp; 
  }

  // Write timestamps and coordinates to SAFEARRAYs
  g_pOptoTrack->ParseBuffer(nFrames, 
                               pBuf,                  // Source buffer
                               pdTimeStamp,          // Dest. timestamps
                              (tdXYZ *) pdCoord,      // Dest. coordinates
                              (tdXYZ *) pdVelocity ); // Dest. velocities
  
  SafeArrayUnaccessData( pvTimeStamp->parray );
  SafeArrayUnaccessData( pvCoord->parray );
  SafeArrayUnaccessData( pvVelocity->parray );
  if( pBuf) free( pBuf );

  return S_OK;

errCleanUp:

  if( pBuf) free( pBuf );
  if( pvTimeStamp->parray ) {
    SafeArrayUnaccessData( pvTimeStamp->parray );
    VariantClear( pvTimeStamp );
  }
  if( pvCoord->parray ) {
    SafeArrayUnaccessData( pvCoord->parray );
    VariantClear( pvCoord );
  }
  if( pvVelocity->parray ) {
    SafeArrayUnaccessData( pvVelocity->parray );
    VariantClear( pvVelocity );
  }

  return m_ErrorToHresult(iErr);
}


//==============================================================================





















/*
//-------------------------------------------------------
HRESULT CP_OptoClass::GetSensors( SAFEARRAY ** ppsaMtx ) {
  int iRes, iParam;
  SAFEARRAY *psaMtx;
  int * piParams;

  int nSensMax, nSensRead, nSensWrite;

  * ppsaMtx = NULL;
  iRes = g_pOptoTrack->GetN_Sensors( &nSensMax, &nSensRead, &nSensWrite );

  // Output 3xN array of ints
  if( g_MakeSafeArray( N_SENSOR_PARAMS, nSensWrite, &psaMtx, &piParams ) ) {
    return m_ErrorToHresult(1);
  }

  iRes = g_pOptoTrack->GetSensors( (SensorInfo *) piParams );
  // Convert indecies from 0 based to 1 based
  for( iParam=0; iParam < (nSensWrite * N_SENSOR_PARAMS); iParam++){
    piParams[iParam]++;
  }
  SafeArrayUnaccessData( psaMtx );
  if( iRes ){
    CP_printf("\nError: GetSensors()failed!\n" );
    return m_ErrorToHresult( 1 );
  }
  

  * ppsaMtx = psaMtx;
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_OptoClass::SetSensors( SAFEARRAY * psaMtx) {
  int iRes, nParams, nSensors, iSensor;
  int * piParams;
  SensorInfo atSensorInfo[N_SENSROS_MAX];

  // We expect 2xN array of ints where N <= N_SENSROS_MAX
  if( g_CheckSafeArray( &nParams, &nSensors, psaMtx,  &piParams )){
    return m_ErrorToHresult( 1 );
  }

  if( (nSensors < 1) || (nSensors > N_SENSROS_MAX) ) {
    CP_printf("SetSensors: incorrect number of sensors: %d, should be > 1 and <= %d\n", 
                                                            nSensors, N_SENSROS_MAX );
    SafeArrayUnaccessData( psaMtx );
    return m_ErrorToHresult( 1 );
  }

  if( (nParams < 1) || (nParams > N_SENSOR_PARAMS) ) {
    CP_printf("SetSensors: incorrect number of paramters: %d, should be > 1 and <= %d\n", 
                                                            nParams, N_SENSOR_PARAMS );
    SafeArrayUnaccessData( psaMtx );
    return m_ErrorToHresult( 1 );
  }

  // copy data to the buffer filling in missing params with defaults
  for( iSensor = 0; iSensor < nSensors; iSensor++) {

    // Sensor index
    atSensorInfo[iSensor].iSensor = (*piParams) - 1; // Input index is 1-based
    piParams++;

    // Transform index
    if( nParams < 2 ) {  // we are mising Transform index, set to default = 0
      atSensorInfo[iSensor].iTransform = 0;
    }
    else{
      atSensorInfo[iSensor].iTransform = (*piParams) - 1; // Input index is 1-based
      piParams++;
    }
    
    // Port index
    if( nParams < 3 ) {  // we are mising Port index, set to default = 0
      atSensorInfo[iSensor].iPort = 0;
    }
    else{
      atSensorInfo[iSensor].iPort = (*piParams) - 1 ; // Input index is 1-based
      piParams++;
    }
  }
  SafeArrayUnaccessData( psaMtx );

  iRes = g_pOptoTrack->SetSensors( nSensors, atSensorInfo );
  if( iRes ) return m_ErrorToHresult( iRes );

  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_OptoClass::GetTransformMatrix( long iTransformIdx, SAFEARRAY ** ppsaMtx ){
  int iRes;
  SAFEARRAY *psaMtx;
  float * pData;

  // Output 4x3 array of floats
  if( g_MakeSafeArray( TRANSFORM_N_J, TRANSFORM_N_I, &psaMtx, &pData ) ){
    return m_ErrorToHresult(1);
  }

  iRes = g_pOptoTrack->GetTransformMatrix( iTransformIdx-1, pData );
  SafeArrayUnaccessData( psaMtx );
  if( iRes ){
    CP_printf("\nError: GetTransformMatrix()failed!\n" );
    return m_ErrorToHresult( 1 );
  }

  * ppsaMtx = psaMtx;
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_OptoClass::SetTransformMatrix( long iTransformIdx, SAFEARRAY * psaMtx){
  int iRes;
  float * pData;

  // We expect 4x3 array of floats
  if( g_CheckSafeArray( TRANSFORM_N_J, TRANSFORM_N_I, psaMtx, &pData )) {
    SafeArrayUnaccessData( psaMtx );
    return m_ErrorToHresult( 1 );
  }
  iRes = g_pOptoTrack->SetTransformMatrix( iTransformIdx-1, pData );
  SafeArrayUnaccessData( psaMtx );
  if( iRes ) return m_ErrorToHresult( iRes );

  return S_OK;
}
//-------------------------------------------------------
HRESULT CP_OptoClass::ActivateSensors( ){
  int iRes;

  iRes = g_pOptoTrack->ActivateSensors( );
  if( iRes ) return m_ErrorToHresult( iRes );
  return S_OK;
}
//-------------------------------------------------------
HRESULT CP_OptoClass::DeactivateSensors( ){
  int iRes;

  iRes = g_pOptoTrack->DeactivateSensors( );
  if( iRes ) return m_ErrorToHresult( iRes );
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_OptoClass::get_lngBufferSize( long *pVal) {

  *pVal = g_pOptoTrack->GetBufferSizeInItems( );
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_OptoClass::ResetBuffer() {

  g_pOptoTrack->ResetBuffer();
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_OptoClass::GetDataIndexLatest( long * piDataIdx) {
  int iRes;

  *piDataIdx = 0;
  iRes = g_pOptoTrack->GetLatestItemIdx( (int *) piDataIdx );
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_OptoClass::GetSensorLatest( long iSensorIdx, 
                                       long *piDataIdx, 
                                       double * pdTimeStampMs,
                                       SAFEARRAY ** ppsaCoord,
                                       SAFEARRAY ** ppsaVelocity ) {

  int iErr = 0;
  int nSensMax, nSensRead, nSensWrite;
  int iSensor;
  int iIdx;
  OptoFrameStruct tOptoFrame;
  double dTimeStamp;
  SAFEARRAY * psaCoord;
  float * pfCoord;
  SAFEARRAY * psaVelocity;
  float * pfVelocity;

  psaCoord = NULL;
  psaVelocity = NULL;
  //Set return pointers
  *piDataIdx = 0;
  *pdTimeStampMs = 0;
  *ppsaCoord = NULL;
  *ppsaVelocity = NULL;

  g_pOptoTrack->GetN_Sensors( &nSensMax, &nSensRead, &nSensWrite );
  // check input sensor index
  if( iSensorIdx < 1 || iSensorIdx > nSensWrite ) {
    CP_printf("\nGetSensorLatest(): invalid sensor requested: %d\n", iSensorIdx);
    return m_ErrorToHresult( 1 );
  }
  iSensor = iSensorIdx-1;

  //Get data from the buffer
  if( ! g_pOptoTrack->ReadLatestItem( &iIdx, &tOptoFrame ) ){
    return m_ErrorToHresult( 1 );
  }

  // Coordinates
  // Create output SAFEARRAY of floats, size 3 
  if( g_MakeSafeArray( N_COORD, &psaCoord, &pfCoord )){
    iErr = 1;
    goto errCleanUp; 
  }
  // Velocities
  // Create output SAFEARRAY of floats, size 3 
  if( g_MakeSafeArray( N_COORD, &psaVelocity, &pfVelocity )){
    iErr = 1;
    goto errCleanUp; 
  }

  // Write timestamps and coordinates to SAFEARRAYs
  g_pOptoTrack->ParseBuffer( iSensor,
                             1,                 // one frame
                             &tOptoFrame,       // Source buffer
                             &dTimeStamp,      // Dest. timestamps
                             pfCoord,          // Dest. coordinates
                             pfVelocity);      // Dest. velocities

  SafeArrayUnaccessData( psaCoord );
  SafeArrayUnaccessData( psaVelocity );

  *piDataIdx = iIdx;
  *pdTimeStampMs = dTimeStamp;
  *ppsaCoord = psaCoord;
  *ppsaVelocity = psaVelocity;
  return S_OK;

errCleanUp:

  if( psaCoord ) {
    SafeArrayUnaccessData( psaCoord );
    SafeArrayDestroy( psaCoord );
  }
  if( psaVelocity ) {
    SafeArrayUnaccessData( psaVelocity );
    SafeArrayDestroy( psaVelocity );
  }

  * ppsaCoord = NULL;
  * ppsaVelocity = NULL;

  return m_ErrorToHresult(iErr);
}

//-------------------------------------------------------
HRESULT CP_OptoClass::GetSensorBuffered( long iSensorIdx, 
                                         long iDataIdx,
                                         long nFrames,
                                         SAFEARRAY ** ppsaTimeStampMs,
                                         SAFEARRAY ** ppsaCoord,
                                         SAFEARRAY ** ppsaVelocity ) {
  int iErr = 0;
  int nSensMax, nSensRead, nSensWrite;
  int iSensor;
  void * pBuf;
  SAFEARRAY *psaTime;
  double * pdTimeStamps;
  SAFEARRAY * psaCoord;
  float * pfCoord;
  SAFEARRAY * psaVelocity;
  float * pfVelocity;

  pBuf = NULL; 
  psaTime = NULL;
  psaCoord = NULL;
  psaVelocity = NULL;
  //Set return pointers
  *ppsaTimeStampMs = NULL;
  *ppsaCoord = NULL;
  *ppsaVelocity = NULL;

  g_pOptoTrack->GetN_Sensors( &nSensMax, &nSensRead, &nSensWrite );
  // check input sensor index
  if( iSensorIdx < 1 || iSensorIdx > nSensWrite ) {
    CP_printf("\nGetSensorBuffered(): invalid sensor requested: %d\n", iSensorIdx);
    return m_ErrorToHresult( 1 );
  }
  iSensor = iSensorIdx-1;

  // Create receiving buffer
  pBuf = malloc(nFrames * sizeof(OptoFrameStruct)); 
  if(!pBuf) { 
    iErr = 1;
    goto errCleanUp; 
  }

  //Get data from the buffer
  if( ! g_pOptoTrack->ReadData( pBuf, iDataIdx, nFrames ) ){
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
  // Create output SAFEARRAY of floats, size nFrames x 3 
  if( g_MakeSafeArray( N_COORD, nFrames, &psaCoord, &pfCoord )){
    iErr = 1;
    goto errCleanUp; 
  }
  // Velocities
  // Create output SAFEARRAY of floats, size 3 
  if( g_MakeSafeArray( N_COORD, &psaVelocity, &pfVelocity )){
    iErr = 1;
    goto errCleanUp; 
  }

  // Write timestamps and coordinates to SAFEARRAYs
  g_pOptoTrack->ParseBuffer( iSensor,
                             nFrames, 
                             pBuf,       // Source buffer
                             pdTimeStamps,      // Dest. timestamps
                             pfCoord,      // Dest. coordinates
                             pfVelocity);      // Dest. velocities
  
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

//-------------------------------------------------------
HRESULT CP_OptoClass::GetAllSensorsLatest( long * piDataIdx, 
                                           double * pdTimeStampMs,
                                           SAFEARRAY ** ppsaCoord,
                                           SAFEARRAY ** ppsaVelocity ) {
  int iErr = 0;
  int nSensMax, nSensRead, nSensWrite;
  int iIdx;
  OptoFrameStruct tOptoFrame;
  double dTimeStamp;
  SAFEARRAY * psaCoord;
  float * pfCoord;
  SAFEARRAY * psaVelocity;
  float * pfVelocity;

  psaCoord = NULL;
  psaVelocity = NULL;
  //Set return pointers
  *piDataIdx = 0;
  *pdTimeStampMs = 0;
  *ppsaCoord = NULL;
  *ppsaVelocity = NULL;

  g_pOptoTrack->GetN_Sensors( &nSensMax, &nSensRead, &nSensWrite );

  //Get data from the buffer
  if( ! g_pOptoTrack->ReadLatestItem( &iIdx, &tOptoFrame ) ){
    return m_ErrorToHresult( 1 );
  }

  // Coordinates
  // Create output SAFEARRAY of floats, size nSensWrite x 3 
  if( g_MakeSafeArray( nSensWrite, N_COORD, &psaCoord, &pfCoord )){
    iErr = 1;
    goto errCleanUp; 
  }
  // Velocities
  // Create output SAFEARRAY of floats, size nSensWrite x 3 
  if( g_MakeSafeArray( nSensWrite, N_COORD, &psaVelocity, &pfVelocity )){
    iErr = 1;
    goto errCleanUp; 
  }

  // Write timestamps and coordinates to SAFEARRAYs
  g_pOptoTrack->ParseBuffer( 1,                 // one frame
                             &tOptoFrame,       // Source buffer
                             &dTimeStamp,      // Dest. timestamps
                             pfCoord,          // Dest. coordinates  
                             pfVelocity);      // Dest. velocities

  SafeArrayUnaccessData( psaCoord );
  SafeArrayUnaccessData( psaVelocity );

  *piDataIdx = iIdx;
  *pdTimeStampMs = dTimeStamp;
  *ppsaCoord = psaCoord;
  *ppsaVelocity = psaVelocity;
  return S_OK;

errCleanUp:

  if( psaCoord ) {
    SafeArrayUnaccessData( psaCoord );
    SafeArrayDestroy( psaCoord );
  }
  if( psaVelocity ) {
    SafeArrayUnaccessData( psaVelocity );
    SafeArrayDestroy( psaVelocity );
  }

  * ppsaCoord = NULL;
  * ppsaVelocity = NULL;

  return m_ErrorToHresult(iErr);
}

//-------------------------------------------------------
HRESULT CP_OptoClass::GetAllSensorsBuffered( long iDataIdx,
                                             long nFrames,
                                             SAFEARRAY ** ppsaTimeStampMs,
                                             SAFEARRAY ** ppsaCoord,
                                             SAFEARRAY ** ppsaVelocity ) {
  int iErr = 0;
  int nSensMax, nSensRead, nSensWrite;
  void * pBuf;
  SAFEARRAY *psaTime;
  double * pdTimeStamps;
  SAFEARRAY * psaCoord;
  float * pfCoord;
  SAFEARRAY * psaVelocity;
  float * pfVelocity;

  pBuf = NULL; 
  psaTime = NULL;
  psaCoord = NULL;
  psaVelocity = NULL;
  //Set return pointers
  *ppsaTimeStampMs = NULL;
  *ppsaCoord = NULL;
  *ppsaVelocity = NULL;

  g_pOptoTrack->GetN_Sensors( &nSensMax, &nSensRead, &nSensWrite );

  // Create receiving buffer
  pBuf = malloc(nFrames * sizeof(OptoFrameStruct)); 
  if(!pBuf) { 
    iErr = 1;
    goto errCleanUp; 
  }

  //Get data from the buffer
  if( ! g_pOptoTrack->ReadData( pBuf, iDataIdx, nFrames ) ){
    iErr = 1;
    goto errCleanUp; 
  }

  //  Timestamps
  // Create output SAFEARRAY of doubles, size nFrames 
  if( g_MakeSafeArray( nFrames, &psaTime, &pdTimeStamps )){
    SafeArrayUnaccessData( psaTime );
    iErr = 1;
    goto errCleanUp; 
  }
  // Coordinates
  // Create output 2D SAFEARRAY of floats, size nFrames x (nSensors x 3)
  // Matlab does not allow to pass 3D SAFEARRAYS via DCOM
  if( g_MakeSafeArray( nSensWrite * N_COORD, nFrames, &psaCoord, &pfCoord )){
    iErr = 1;
    goto errCleanUp; 
  }
  // Velocities
  // Create output 2D SAFEARRAY of floats, size nFrames x (nSensors x 3)
  // Matlab does not allow to pass 3D SAFEARRAYS via DCOM
  if( g_MakeSafeArray( nSensWrite * N_COORD, nFrames, &psaVelocity, &pfVelocity )){
    iErr = 1;
    goto errCleanUp; 
  }

  // Write timestamps and coordinates to SAFEARRAYs
  g_pOptoTrack->ParseBuffer( nFrames, 
                             pBuf,             // Source buffer
                             pdTimeStamps,     // Dest. timestamps
                             pfCoord,          // Dest. coordinates
                             pfVelocity);      // Dest. velocities
  
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

  return m_ErrorToHresult( iErr );
}


*/


