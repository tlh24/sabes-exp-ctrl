// CP_OptoClass - implementation of COM object

#include "CP_OptoClass.h"
#include "OptoTrack.h"
#include "CP_printf.h"

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


//-------------------------------------------------------
HRESULT CP_OptoClass::get_strProgramVersion( BSTR * pVal) {
  int iRes;

  iRes = g_pOptoTrack->GetVersion( pVal);
  return S_OK;
}
//-------------------------------------------------------
HRESULT CP_OptoClass::ConnectTracker() {
  int iRes;

  iRes = g_pOptoTrack->ConnectOpto();
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_OptoClass::GetTrackerState(long *pVal) {
  int iRes;

  iRes = g_pOptoTrack->GetOptoState( (int *)pVal );
  if( iRes ) return m_ErrorToHresult( iRes );
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_OptoClass::DisconnectTracker() {
  int iRes;

  iRes = g_pOptoTrack->DisconnectOpto();
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_OptoClass::get_dPredictionTimeMs( double *pVal) {
//  *pVal = g_pOptoTrack->GetBufferSizeInItems( );
  *pVal = 0;
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_OptoClass::put_dPredictionTimeMs( double newVal) {

//  *pVal = g_pOptoTrack->GetBufferSizeInItems( );
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_OptoClass::ResetBuffer() {
  int iRes;

  iRes = g_pOptoTrack->ResetTimeAndBuffer();
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_OptoClass::GetSensors( SAFEARRAY ** ppsaMtx ) {
  int iRes;
  SAFEARRAY *psaMtx = NULL;
  SAFEARRAYBOUND rgsabound[1];  // 1-D array
  int nSensors, nDum1, nDum2;
  int i, iSensorState;
  double dSensorState;

  iRes = g_pOptoTrack->GetN_Sensors( &nSensors, &nDum1, &nDum2 );
  // Output Matlab array 1xN
  rgsabound[0].lLbound = 0;
  rgsabound[0].cElements = nSensors;    // 16
  psaMtx = SafeArrayCreate(VT_R8, 1, rgsabound);
  if(!psaMtx) {
    return m_ErrorToHresult(3);
  }

  for( i = 0; i<nSensors; i++ ){
    iRes = g_pOptoTrack->GetSensors(i, &iSensorState);
    dSensorState = iSensorState;
    SafeArrayPutElement( psaMtx, (long *)&i, &dSensorState);
  }

  * ppsaMtx = psaMtx;
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_OptoClass::SetSensors( SAFEARRAY * psaMtx) {
  int iRes;
  int nDims;
  long rgIndices[2];
  long  lngTmp, nStates;
  double dState;
  int i;


  // We expect Matlab array 1xN where N <= N_SENSROS_MAX
  nDims = SafeArrayGetDim( psaMtx );

  if( nDims !=2 ) return m_ErrorToHresult( 4 );
  SafeArrayGetLBound( psaMtx, 1, & lngTmp );
  if( lngTmp != 0) return m_ErrorToHresult( 5 );
  SafeArrayGetUBound( psaMtx, 1, & lngTmp );
  if( lngTmp != 0) return m_ErrorToHresult( 5 );
  SafeArrayGetLBound( psaMtx, 2, & lngTmp );
  if( lngTmp != 0) return m_ErrorToHresult( 5 );
  SafeArrayGetUBound( psaMtx, 2, & nStates );
  if( (nStates+1) > N_SENSROS_MAX  ) {
    CP_printf("\nError: input sensor state array is too long: %d, should be <= %d\n", 
                                                            nStates+1, N_SENSROS_MAX );
    return m_ErrorToHresult( 5 );
  }

//  iRes = g_pOptoTrack->SetAllSensorsOff();
//  if( iRes ) return m_ErrorToHresult( 6 );

  rgIndices[0] = 0;
  for( i = 0; i<nStates; i++ ){
    rgIndices[1] = i;
    SafeArrayGetElement( psaMtx, rgIndices, & dState );
    iRes = g_pOptoTrack->SetSensors( i, (int) dState );
    if( iRes ) return m_ErrorToHresult( 7 );
  }
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_OptoClass::get_lngBufferSize( long *pVal) {

  *pVal = g_pOptoTrack->GetBufferSizeInItems( );
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_OptoClass::get_lngLatestDataIndex( long *pVal) {
  int iRes;

  *pVal = 0;
  iRes = g_pOptoTrack->GetLatestItemIdx( (int *) pVal );
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_OptoClass::GetSensorLatest( long lngSensorIdx, 
                                     long *plIdx, 
                                     SAFEARRAY ** ppsaMtx ) {
  int iIdx;
  tServerFrame ScanData;
  SAFEARRAY *psaMtx = NULL;
  SAFEARRAYBOUND rgsabound[1];  // 2-D array
  long lngIdx;
  double dTmp;

  //Set return pointers
  *plIdx = 0;
  *ppsaMtx = NULL;


  if( ! g_pOptoTrack->ReadLatestItem( &iIdx, &ScanData ) ){
    return m_ErrorToHresult( 1 );
  }


  // Create output SAFEARRAY, 1x4 in Matlab
  rgsabound[0].lLbound = 0;
  rgsabound[0].cElements = 4;  
  // only one dim 
  psaMtx = SafeArrayCreate(VT_R8, 1, rgsabound);
  if(!psaMtx) {
    return m_ErrorToHresult( 3 );
  }

  // Write data to SAFEARRAYs
  lngIdx = 0;
  // Timestamp
  SafeArrayPutElement( psaMtx, &lngIdx, &ScanData.dCalcTimeMs );
  // X-coord
  lngIdx = 1;
  dTmp = ScanData.OptoFrame.afCoord[0];
  SafeArrayPutElement( psaMtx, &lngIdx, &dTmp );
  // Y-coord
  lngIdx = 2;
  dTmp = ScanData.OptoFrame.afCoord[1];
  SafeArrayPutElement( psaMtx, &lngIdx, &dTmp );
  // Z-coord
  lngIdx = 3;
  dTmp = ScanData.OptoFrame.afCoord[2];
  SafeArrayPutElement( psaMtx, &lngIdx, &dTmp );

  //Set return pointers
  *plIdx = iIdx;
  *ppsaMtx = psaMtx;

  return S_OK;

}

//-------------------------------------------------------
HRESULT CP_OptoClass::GetSensorBuffer( long lngSensorIdx, 
                                     long lngIdx,
                                     long nItems,
                                     SAFEARRAY ** ppsaMtx ){
/*
  int iErr = 0;
  void * pBuf = NULL;
  SAFEARRAY *psaMtx = NULL;
  SAFEARRAYBOUND rgsabound[2];  // 2-D array
  long rgIndices[2];
  OptoFrame * pScanData;
  double dRawX, dRawY, dCalibX, dCalibY;
  long i;
*/

  *ppsaMtx = NULL;

/*
  // Create receiving buffer
  pBuf = malloc(nItems * sizeof(OptoFrame)); 
  if(!pBuf) { 
    iErr = 1;
    goto errCleanUp; 
  }

  //Get the data 
  if( ! g_pOptoTrack->ReadData( pBuf, lngIdx, nItems ) ){
    iErr = 2;
    goto errCleanUp; 
  }

  // Create output SAFEARRAY, (nItems x 5) in Matlab
  rgsabound[0].lLbound = 0;
  rgsabound[0].cElements = nItems;
  rgsabound[1].lLbound = 0;
  rgsabound[1].cElements = 5;  // Time, rawX, rawY, calibX, calibY 
  psaMtx = SafeArrayCreate(VT_R8, 2, rgsabound);
  if(!psaMtx) {
    iErr = 3;
    goto errCleanUp; 
  }
  //Set return pointer
  *ppsaMtx = psaMtx;

  pScanData = (OptoFrame *) pBuf; 
  // Write data to SAFEARRAYs
  for( i = 0; i<nItems; i++ ){

    dRawX = pScanData[i].iRawX;;
    dRawY = pScanData[i].iRawY;
    g_pOptoTrack->CalcCalibCoordinates( dRawX, dRawY, &dCalibX, &dCalibY );

    rgIndices[0] = i;
    // Timestamp
    rgIndices[1] = 0;
    SafeArrayPutElement( psaMtx, rgIndices, &pScanData[i].dTimeStampMs );
    // raw X-coord
    rgIndices[1] = 1;
    SafeArrayPutElement( psaMtx, rgIndices, &dRawX );
    // raw Y-coord
    rgIndices[1] = 2;
    SafeArrayPutElement( psaMtx, rgIndices, &dRawY );
    // calib X-coord
    rgIndices[1] = 3;
    SafeArrayPutElement( psaMtx, rgIndices, &dCalibX );
    // calib Y-coord
    rgIndices[1] = 4;
    SafeArrayPutElement( psaMtx, rgIndices, &dCalibY );
  }

  if( pBuf) free( pBuf );
*/ 
  return S_OK;
/*
errCleanUp:

  if( pBuf) free( pBuf );
  if( psaMtx ) SafeArrayDestroy( psaMtx );

  psaMtx = NULL;

  return m_ErrorToHresult( iErr );
*/
}

//-------------------------------------------------------
HRESULT CP_OptoClass::GetAllSensorsLatest( long *plIdx, 
                                           SAFEARRAY ** ppsaMtx ) {
/*
  int iIdx;
  OptoFrame ScanData;
  SAFEARRAY *psaMtx = NULL;
  SAFEARRAYBOUND rgsabound[2];  // 2-D array
  long rgIndices[2];
  double dRawX, dRawY, dCalibX, dCalibY;
*/

  //Set return pointers
  *plIdx = 0;
  *ppsaMtx = NULL;
/*
  if( ! g_pOptoTrack->ReadLatestItem( &iIdx, &ScanData ) ){
    return m_ErrorToHresult( 1 );
  }

  // Create output SAFEARRAY, 1x5 in Matlab
  rgsabound[0].lLbound = 0;
  rgsabound[0].cElements = 1;  // only one item 
  rgsabound[1].lLbound = 0;
  rgsabound[1].cElements = 5;  // Time, rawX, rawY, calibX, calibY
  psaMtx = SafeArrayCreate(VT_R8, 2, rgsabound);
  if(!psaMtx) {
    return m_ErrorToHresult( 3 );
  }

  dRawX = ScanData.iRawX;;
  dRawY = ScanData.iRawY;
  g_pOptoTrack->CalcCalibCoordinates( dRawX, dRawY, &dCalibX, &dCalibY );

  // Write data to SAFEARRAYs
  rgIndices[0] = 0;
  // Timestamp
  rgIndices[1] = 0;
  SafeArrayPutElement( psaMtx, rgIndices, &ScanData.dTimeStampMs );
  // raw X-coord
  rgIndices[1] = 1;
  SafeArrayPutElement( psaMtx, rgIndices, &dRawX );
  // raw Y-coord
  rgIndices[1] = 2;
  SafeArrayPutElement( psaMtx, rgIndices, &dRawY );
  // calib X-coord
  rgIndices[1] = 3;
  SafeArrayPutElement( psaMtx, rgIndices, &dCalibX );
  // calib Y-coord
  rgIndices[1] = 4;
  SafeArrayPutElement( psaMtx, rgIndices, &dCalibY );
  //Set return pointers
  *plIdx = iIdx;
  *ppsaMtx = psaMtx;
*/
  return S_OK;

}

//-------------------------------------------------------
HRESULT CP_OptoClass::GetAllSensorsBuffer( long lngIdx,
                                              long nItems,
                                              SAFEARRAY ** ppsaMtx ){
/*
  int iErr = 0;
  void * pBuf = NULL;
  SAFEARRAY *psaMtx = NULL;
  SAFEARRAYBOUND rgsabound[2];  // 2-D array
  long rgIndices[2];
  OptoFrame * pScanData;
  double dRawX, dRawY, dCalibX, dCalibY;
  long i;
*/

  //Set return pointers
  *ppsaMtx = NULL;

/*
  // Create receiving buffer
  pBuf = malloc(nItems * sizeof(OptoFrame)); 
  if(!pBuf) { 
    iErr = 1;
    goto errCleanUp; 
  }

  //Get the data 
  if( ! g_pOptoTrack->ReadData( pBuf, lngIdx, nItems ) ){
    iErr = 2;
    goto errCleanUp; 
  }

  // Create output SAFEARRAY, (nItems x 5) in Matlab
  rgsabound[0].lLbound = 0;
  rgsabound[0].cElements = nItems;
  rgsabound[1].lLbound = 0;
  rgsabound[1].cElements = 5;  // Time, rawX, rawY, calibX, calibY 
  psaMtx = SafeArrayCreate(VT_R8, 2, rgsabound);
  if(!psaMtx) {
    iErr = 3;
    goto errCleanUp; 
  }
  //Set return pointer
  *ppsaMtx = psaMtx;

  pScanData = (OptoFrame *) pBuf; 
  // Write data to SAFEARRAYs
  for( i = 0; i<nItems; i++ ){

    dRawX = pScanData[i].iRawX;;
    dRawY = pScanData[i].iRawY;
    g_pOptoTrack->CalcCalibCoordinates( dRawX, dRawY, &dCalibX, &dCalibY );

    rgIndices[0] = i;
    // Timestamp
    rgIndices[1] = 0;
    SafeArrayPutElement( psaMtx, rgIndices, &pScanData[i].dTimeStampMs );
    // raw X-coord
    rgIndices[1] = 1;
    SafeArrayPutElement( psaMtx, rgIndices, &dRawX );
    // raw Y-coord
    rgIndices[1] = 2;
    SafeArrayPutElement( psaMtx, rgIndices, &dRawY );
    // calib X-coord
    rgIndices[1] = 3;
    SafeArrayPutElement( psaMtx, rgIndices, &dCalibX );
    // calib Y-coord
    rgIndices[1] = 4;
    SafeArrayPutElement( psaMtx, rgIndices, &dCalibY );
  }

  if( pBuf) free( pBuf );
*/ 
  return S_OK;
/*
errCleanUp:
  if( pBuf) free( pBuf );
  if( psaMtx ) SafeArrayDestroy( psaMtx );

  psaMtx = NULL;

  return m_ErrorToHresult( iErr );
*/
}





