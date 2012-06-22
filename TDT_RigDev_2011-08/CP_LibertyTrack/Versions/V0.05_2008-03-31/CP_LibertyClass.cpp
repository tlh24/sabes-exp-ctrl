// CP_LibertyClass - implementation of COM object

//#include "ShadowPrint.h"
#include "CP_LibertyClass.h"
#include "LibertyTrack.h"
#include "CP_printf.h"
#include "VariantLib.h"


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
HRESULT CP_LibertyClass::GetFrameCount( long * pnFrames ){
  int iRes;

  iRes = g_pLibertyTrack->GetFrameCount( (int *)pnFrames );
  if( iRes ){
    CP_printf("\nError: GetFrameCount() failed!\n" );
    return m_ErrorToHresult( 1 );
  }
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
                                            VARIANT * pvTransform){
  int iRes;
  double * pdData;

  // Output 4x3 array of doubles
  if( g_MakeVariantArray( TRANSFORM_N_J, TRANSFORM_N_I, pvTransform, &pdData ) ){
    return m_ErrorToHresult(1);
  }

  iRes = g_pLibertyTrack->GetTransformMatrix( iTransformIdx-1, pdData );
  SafeArrayUnaccessData( pvTransform->parray );
  if( iRes ){
    VariantClear(pvTransform);
    CP_printf("\nError: GetTransformMatrix() failed!\n" );
    return m_ErrorToHresult( 1 );
  }

  return S_OK;
}

//==============================================================================
HRESULT CP_LibertyClass::SetTransformMatrix( VARIANT vTransform,
                                             long iTransformIdx){
  int iRes;
  double * pdData;

  // We expect 4x3 array of doubles
  if( g_CheckVariantArray( TRANSFORM_N_J, TRANSFORM_N_I, vTransform, &pdData )) {
    SafeArrayUnaccessData( vTransform.parray );
    return m_ErrorToHresult( 1 );
  }
  iRes = g_pLibertyTrack->SetTransformMatrix( iTransformIdx-1, pdData );
  SafeArrayUnaccessData( vTransform.parray );
  if( iRes ){
    CP_printf("\nError: SetTransformMatrix() failed!\n" );
    return m_ErrorToHresult( 1 );
  }

  return S_OK;
}

//==============================================================================
HRESULT CP_LibertyClass::GetSensors( VARIANT * pvSensors){
  int iRes, iParam;
  int * piParams;

  int nSensDevMax, nSensors;

  iRes = g_pLibertyTrack->GetN_Sensors( &nSensDevMax, &nSensors );

  // Output 3xN array of ints
  if( g_MakeVariantArray( N_SENSOR_PARAMS, nSensors, pvSensors, &piParams ) ) {
    return m_ErrorToHresult(1);
  }

  iRes = g_pLibertyTrack->GetSensors( (tSensorInfo *) piParams );
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
HRESULT CP_LibertyClass::SetSensors( VARIANT vSensors){
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
HRESULT CP_LibertyClass::GetSensorsTransformIdx( VARIANT * pvTransformIdx){
  int iRes, iSensor;
  int * piTransIdx;
  int nSensDevMax, nSensors;

  iRes = g_pLibertyTrack->GetN_Sensors( &nSensDevMax, &nSensors );

  // Output 1xN array of ints
  if( g_MakeVariantArray( nSensors, pvTransformIdx, &piTransIdx ) ) {
    return m_ErrorToHresult(1);
  }

  iRes = g_pLibertyTrack->GetSensorsTransformIdx( piTransIdx );
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
HRESULT CP_LibertyClass::SetSensorsTransformIdx( VARIANT vTransformIdx){
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


  iRes = g_pLibertyTrack->SetSensorsTransformIdx( nSensors, piTransIdx );
  SafeArrayUnaccessData( vTransformIdx.parray );
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
                                          VARIANT * pvTimeStamp,
                                          VARIANT * pvCoord,
                                          VARIANT * pvVelocity ){
  
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
                            pvTimeStamp,
                            pvCoord,
                            pvVelocity );
}

//==============================================================================
HRESULT CP_LibertyClass::GetSensorBuffered( long iSensorIdx,
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
  g_pLibertyTrack->ParseBuffer(iSensor,
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
HRESULT CP_LibertyClass::GetAllSensorsLatest( long nFrames,
                                              long *piDataIdx,
                                              VARIANT * pvTimeStamp,
                                              VARIANT * pvCoord,
                                              VARIANT * pvVelocity ){
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
                                pvTimeStamp,
                                pvCoord,
                                pvVelocity );

}

//==============================================================================
HRESULT CP_LibertyClass::GetAllSensorsBuffered( long iDataIdx,
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
  g_pLibertyTrack->ParseBuffer(nFrames, 
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



