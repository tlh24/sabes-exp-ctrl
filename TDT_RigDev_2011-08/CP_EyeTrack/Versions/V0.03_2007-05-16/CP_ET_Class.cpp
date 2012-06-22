// CP_ET_Class - implementation of COM object

//#include "ShadowPrint.h"
#include "CP_ET_Class.h"
#include "EyeTrack.h"
#include "CP_printf.h"

//===============================================================================
// CP_ET_Class
CP_ET_Class::CP_ET_Class() : m_cRef(0) { 

  CoAddRefServerProcess();
}

//-------------------------------------------------------
HRESULT CP_ET_Class::m_ErrorToHresult( int iErr ){
   return MAKE_HRESULT( SEVERITY_ERROR,  //  Indicate that function failed
                        FACILITY_ITF,    //  Specific interface - related error 
                        iErr ); // Our own error code
}


//-------------------------------------------------------
HRESULT CP_ET_Class::QueryInterface(REFIID iid, void **ppv){

  if (ppv == NULL) return E_INVALIDARG;
  if(iid == IID_IUnknown)	{
    *ppv = (IUnknown*)this;
  }
  else if(iid == IID_IDispatch)	{
    *ppv = (IDispatch*)this; 
  }
  else if(iid == IID_IEyeTrack)	{
    *ppv = (IEyeTrack*)this;
  }
	else{
		*ppv = NULL;
		return E_NOINTERFACE;
	}
	AddRef();
	return S_OK;
}

//-------------------------------------------------------
HRESULT CP_ET_Class::GetTypeInfo(UINT iTypeInfo, LCID lcid, ITypeInfo** ppITypeInfo){

  *ppITypeInfo = NULL;
	m_pTypeInfo->AddRef();
	*ppITypeInfo = m_pTypeInfo;
	return S_OK;
}


//-------------------------------------------------------
HRESULT CP_ET_Class::get_strProgramVersion( BSTR * pVal) {
  int iRes;

  iRes = g_pEyeTrack->GetVersion( pVal);
  return S_OK;
}
//-------------------------------------------------------
HRESULT CP_ET_Class::ConnectISCAN() {
  int iRes;

  iRes = g_pEyeTrack->ConnectISCAN();
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_ET_Class::DisconnectISCAN() {
  int iRes;

  iRes = g_pEyeTrack->DisconnectISCAN();
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_ET_Class::ResetBuffer() {
  int iRes;

  iRes = g_pEyeTrack->ResetTimeAndBuffer();
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_ET_Class::get_lngCOM_Index( long *pVal) {

  g_pEyeTrack->GetComPort( (int *) pVal );
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_ET_Class::put_lngCOM_Index( long newVal) {

  g_pEyeTrack->SetComPort( newVal );
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_ET_Class::get_lngBaudRate( long *pVal) {

  *pVal = 0;
  g_pEyeTrack->GetBaudRate( (int *) pVal );
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_ET_Class::put_lngBaudRate( long newVal) {

  g_pEyeTrack->SetBaudRate( newVal );
  return S_OK;
}


//-------------------------------------------------------
HRESULT CP_ET_Class::GetCalibrationMatrix( SAFEARRAY ** ppsaMtx ) {
  int iRes;
  int iErr = 0;
  SAFEARRAY *psaMtx = NULL;
  SAFEARRAYBOUND rgsabound[2];  // 2-D array
  long rgIndices[2];
  double * pdMtx;
  int i, j;

  // Output Matlab array 6x2
  rgsabound[0].lLbound = 0;
  rgsabound[0].cElements = CALIB_N_J;    // 6
  rgsabound[1].lLbound = 0;
  rgsabound[1].cElements = CALIB_N_I;    // 2
  psaMtx = SafeArrayCreate(VT_R8, 2, rgsabound);
  if(!psaMtx) {
    return m_ErrorToHresult(3);
  }

  iRes = g_pEyeTrack->GetCalibrationMatrixPtr( & pdMtx );


  for( i = 0; i<CALIB_N_I; i++ ){
    for( j = 0; j<CALIB_N_J; j++ ){
      // in Matlab order of indexes is the opposite to C
      rgIndices[0] = j;
      rgIndices[1] = i;
      SafeArrayPutElement( psaMtx, rgIndices, pdMtx );
      pdMtx++;
    }
  }

  * ppsaMtx = psaMtx;
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_ET_Class::PutCalibrationMatrix( SAFEARRAY * psaMtx) {
  int iRes;
  long rgIndices[2];
  long  lngTmp;
  double * pdMtx;
  int i, j;


  iRes = g_pEyeTrack->GetCalibrationMatrixPtr( & pdMtx );

  // We expect Matlab array 6x2
  if( SafeArrayGetDim( psaMtx ) !=2 ) return m_ErrorToHresult( 4 );
  SafeArrayGetLBound( psaMtx, 1, & lngTmp );
  if( lngTmp != 0) return m_ErrorToHresult( 5 );
  SafeArrayGetUBound( psaMtx, 1, & lngTmp );
  if( lngTmp != 5) return m_ErrorToHresult( 5 );
  SafeArrayGetLBound( psaMtx, 2, & lngTmp );
  if( lngTmp != 0) return m_ErrorToHresult( 5 );
  SafeArrayGetUBound( psaMtx, 2, & lngTmp );
  if( lngTmp != 1) return m_ErrorToHresult( 5 );

  for( i = 0; i<CALIB_N_I; i++ ){
    for( j = 0; j<CALIB_N_J; j++ ){
      // in Matlab order of indexes is the opposite to C
      rgIndices[0] = j;
      rgIndices[1] = i;
      SafeArrayGetElement( psaMtx, rgIndices, pdMtx );
      pdMtx++;
    }
  }
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_ET_Class::get_IsCalibrated( long *pVal) {
  g_pEyeTrack->GetCalibrationFlag( (int *) pVal );
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_ET_Class::put_IsCalibrated( long newVal) {
  g_pEyeTrack->SetCalibrationFlag( newVal );
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_ET_Class::get_lngBufferSize( long *pVal) {

  *pVal = g_pEyeTrack->GetBufferSizeInItems( );
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_ET_Class::get_lngLatestDataIndex( long *pVal) {
  int iRes;

  *pVal = 0;
  iRes = g_pEyeTrack->GetLatestItemIdx( (int *) pVal );
  return S_OK;
}

//-------------------------------------------------------
// this method is used internally to draw cursor on the screen
HRESULT CP_ET_Class::GetLatestRawData( long *plIdx, double *pdTimeMs, long *plX, long *plY) {
  int iIdx;
  IScanData ScanData;

  if( g_pEyeTrack->ReadLatestItem( &iIdx, &ScanData ) ){
    * plIdx = iIdx;
    * pdTimeMs = ScanData.dLocalTimeMs; 
    * plX = ScanData.iRawX; 
    * plY = ScanData.iRawY;
//    CP_printf("%f\t%d\t%d\n", *pdTimeMs, *plX, *plY );
    return S_OK;
  }
  else{
    * plIdx = 0;
    * pdTimeMs = 0;
    * plX = 0; 
    * plY = 0; 
    return m_ErrorToHresult( 1 );
  }
}

//-------------------------------------------------------
HRESULT CP_ET_Class::GetLatestData( long *plIdx, SAFEARRAY ** ppadData ) {
  int iIdx;
  IScanData ScanData;
  SAFEARRAY *padData = NULL;
  SAFEARRAYBOUND rgsabound[2];  // 2-D array
  long rgIndices[2];
  double dRawX, dRawY, dCalibX, dCalibY;


  //Set return pointers
  *plIdx = 0;
  *ppadData = NULL;
  if( ! g_pEyeTrack->ReadLatestItem( &iIdx, &ScanData ) ){
    return m_ErrorToHresult( 1 );
  }

  // Create output SAFEARRAY, 1x5 in Matlab
  rgsabound[0].lLbound = 0;
  rgsabound[0].cElements = 1;  // only one item 
  rgsabound[1].lLbound = 0;
  rgsabound[1].cElements = 5;  // Time, rawX, rawY, calibX, calibY
  padData = SafeArrayCreate(VT_R8, 2, rgsabound);
  if(!padData) {
    return m_ErrorToHresult( 3 );
  }

  dRawX = ScanData.iRawX;;
  dRawY = ScanData.iRawY;
  g_pEyeTrack->CalcCalibCoordinates( dRawX, dRawY, &dCalibX, &dCalibY );

  // Write data to SAFEARRAYs
  rgIndices[0] = 0;
  // Timestamp
  rgIndices[1] = 0;
  SafeArrayPutElement( padData, rgIndices, &ScanData.dLocalTimeMs );
  // raw X-coord
  rgIndices[1] = 1;
  SafeArrayPutElement( padData, rgIndices, &dRawX );
  // raw Y-coord
  rgIndices[1] = 2;
  SafeArrayPutElement( padData, rgIndices, &dRawY );
  // calib X-coord
  rgIndices[1] = 3;
  SafeArrayPutElement( padData, rgIndices, &dCalibX );
  // calib Y-coord
  rgIndices[1] = 4;
  SafeArrayPutElement( padData, rgIndices, &dCalibY );

  //Set return pointers
  *plIdx = iIdx;
  *ppadData = padData;
  return S_OK;

}

//-------------------------------------------------------
HRESULT CP_ET_Class::GetDataBuffer( long lngIdx,
                                       long nItems,
                                       SAFEARRAY ** ppadData ){
  int iErr = 0;
  void * pBuf = NULL;
  SAFEARRAY *padData = NULL;
  SAFEARRAYBOUND rgsabound[2];  // 2-D array
  long rgIndices[2];
  IScanData * pScanData;
  double dRawX, dRawY, dCalibX, dCalibY;
  long i;

  // Create receiving buffer
  pBuf = malloc(nItems * sizeof(IScanData)); 
  if(!pBuf) { 
    iErr = 1;
    goto errCleanUp; 
  }

  //Get the data 
  if( ! g_pEyeTrack->ReadData( pBuf, lngIdx, nItems ) ){
    iErr = 2;
    goto errCleanUp; 
  }

  // Create output SAFEARRAY, (nItems x 5) in Matlab
  rgsabound[0].lLbound = 0;
  rgsabound[0].cElements = nItems;
  rgsabound[1].lLbound = 0;
  rgsabound[1].cElements = 5;  // Time, rawX, rawY, calibX, calibY 
  padData = SafeArrayCreate(VT_R8, 2, rgsabound);
  if(!padData) {
    iErr = 3;
    goto errCleanUp; 
  }
  //Set return pointer
  *ppadData = padData;

  pScanData = (IScanData *) pBuf; 
  // Write data to SAFEARRAYs
  for( i = 0; i<nItems; i++ ){
    dRawX = pScanData[i].iRawX;;
    dRawY = pScanData[i].iRawY;
    g_pEyeTrack->CalcCalibCoordinates( dRawX, dRawY, &dCalibX, &dCalibY );

    rgIndices[0] = i;
    // Timestamp
    rgIndices[1] = 0;
    SafeArrayPutElement( padData, rgIndices, &pScanData[i].dLocalTimeMs );
    // raw X-coord
    rgIndices[1] = 1;
    SafeArrayPutElement( padData, rgIndices, &dRawX );
    // raw Y-coord
    rgIndices[1] = 2;
    SafeArrayPutElement( padData, rgIndices, &dRawY );
    // calib X-coord
    rgIndices[1] = 3;
    SafeArrayPutElement( padData, rgIndices, &dCalibX );
    // calib Y-coord
    rgIndices[1] = 4;
    SafeArrayPutElement( padData, rgIndices, &dCalibY );
  }

  if( pBuf) free( pBuf );
  return S_OK;

errCleanUp:
  if( pBuf) free( pBuf );
  if( padData ) SafeArrayDestroy( padData );

  padData = NULL;

  return m_ErrorToHresult( iErr );
}


//-------------------------------------------------------
HRESULT CP_ET_Class::ResetDataBuffer( ) {

  g_pEyeTrack->ResetTimeAndBuffer();
  return S_OK;
}

