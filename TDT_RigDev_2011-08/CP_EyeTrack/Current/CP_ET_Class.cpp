// CP_ET_Class - implementation of COM object

#include "CP_ET_Class.h"
#include "EyeTrack.h"
#include "VariantLib.h"
#include "CP_printf.h"


#define N_COORD 2      // number of output coordinates

extern CEyeTrack * g_pEyeTrack;

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
HRESULT CP_ET_Class::GetVersion( BSTR * pbstVersion) {
  int iRes;

  iRes = g_pEyeTrack->GetVersion( pbstVersion );
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_ET_Class::ConnectTracker() {
  int iRes;

  iRes = g_pEyeTrack->ConnectISCAN();
  return S_OK;
}
//-------------------------------------------------------
HRESULT CP_ET_Class::DisconnectTracker() {
  int iRes;

  iRes = g_pEyeTrack->DisconnectISCAN();
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_ET_Class::GetTrackerState( long *piTrackerID, long * piState ){

  *piState = g_pEyeTrack->IsRunning(); 
  *piTrackerID = 3;  // ISCAN ID

  return S_OK;
}

//==============================================================================
HRESULT CP_ET_Class::GetFrameCount( long * pnFrames ){
  int iRes;

  iRes = g_pEyeTrack->GetFrameCount( (int *)pnFrames );
  if( iRes ){
    CP_printf("\nError: GetFrameCount() failed!\n" );
    return m_ErrorToHresult( 1 );
  }
	return S_OK;
}

//-------------------------------------------------------
HRESULT CP_ET_Class::GetTimeScale( double *pdC0, double *pdC1){
  int iRes;

  iRes = g_pEyeTrack->GetTimeScale( pdC0, pdC1);
  if( iRes ){
    CP_printf("\nError: GetTimeScale() failed!\n" );
    return m_ErrorToHresult( 1 );
  }
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_ET_Class::SetTimeScale( double dC0, double dC1){
  int iRes;

  iRes = g_pEyeTrack->SetTimeScale( dC0, dC1);
  if( iRes ){
    CP_printf("\nError: GetTimeScale() failed!\n" );
    return m_ErrorToHresult( 1 );
  }
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_ET_Class::GetTransformMatrix( VARIANT * pvTransform ) {
  int iRes;
  double * pdData;

  // Output 6x2 array of doubles
  if( g_MakeVariantArray( TRANSF_MTX_N_2, TRANSF_MTX_N_1, pvTransform, &pdData ) ){
    return m_ErrorToHresult(1);
  }

  iRes = g_pEyeTrack->GetTransformMatrix( pdData );
  SafeArrayUnaccessData( pvTransform->parray );
  if( iRes ){
    VariantClear(pvTransform);
    CP_printf("\nError: GetTransformMatrix() failed!\n" );
    return m_ErrorToHresult( 1 );
  }

  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_ET_Class::SetTransformMatrix( VARIANT vTransform ) {
  int iRes;
  double * pdData;

  // We expect 6x2 array of doubles
  if( g_CheckVariantArray( TRANSF_MTX_N_2, TRANSF_MTX_N_1, vTransform, &pdData )) {
    SafeArrayUnaccessData( vTransform.parray );
    return m_ErrorToHresult( 1 );
  }
  iRes = g_pEyeTrack->SetTransformMatrix( pdData );
  SafeArrayUnaccessData( vTransform.parray );
  if( iRes ){
    CP_printf("\nError: SetTransformMatrix() failed!\n" );
    return m_ErrorToHresult( 1 );
  }
  return S_OK;
}


//-------------------------------------------------------
HRESULT CP_ET_Class::GetBufferSize( long * pnFrames ) {

  *pnFrames = g_pEyeTrack->GetBufferSizeInItems( );
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_ET_Class::GetDataIndexLatest( long * piDataIdx ) {
  int iRes;

  *piDataIdx = 0;
  iRes = g_pEyeTrack->GetLatestItemIdx( (int *) piDataIdx );
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_ET_Class::GetDataLatest( long nFrames,
                                    long *piDataIdx,
                                    VARIANT *pvTimeStampMs,
                                    VARIANT *pvCoord ) {
  int iIdx;

  * piDataIdx = 0;
  if( ! g_pEyeTrack->GetLatestItemIdx( &iIdx ) ){
    return m_ErrorToHresult( 1 );
  }

  * piDataIdx = iIdx;
  return GetDataBuffered(  iIdx + 1 - nFrames,
                           nFrames,
                           pvTimeStampMs,
                           pvCoord );

}

//-------------------------------------------------------
HRESULT CP_ET_Class::GetDataBuffered( long iDataIdx,
                                      long nFrames,
                                      VARIANT *pvTimeStampMs,
                                      VARIANT *pvCoord ){

  int iErr = 0;
  void * pBuf;
  double * pdTimeStamps;
  double * pdCoord;

  pBuf = NULL; 

  // Create receiving buffer
  pBuf = malloc(nFrames * sizeof(IScanFrameStruct)); 
  if(!pBuf) { 
    iErr = 1;
    goto errCleanUp; 
  }

  //Get data from the buffer
  if( ! g_pEyeTrack->ReadData( pBuf, iDataIdx, nFrames ) ){
    iErr = 1;
    goto errCleanUp; 
  }

  //  Timestamps
  // Create output array of doubles, size nFrames 
  if( g_MakeVariantArray( nFrames, pvTimeStampMs, &pdTimeStamps )){
    iErr = 1;
    goto errCleanUp; 
  }
  // Coordinates
  // Create output array of doubles, size nFrames x 2 
  if( g_MakeVariantArray( N_COORD, nFrames, pvCoord, &pdCoord )){
    iErr = 1;
    goto errCleanUp; 
  }

  // Write timestamps and coordinates to the arrays
  g_pEyeTrack->ParseBuffer(  nFrames, 
                             pBuf,       // Source buffer
                             pdTimeStamps,      // Dest. timestamps
                             pdCoord );      // Dest. coordinates
  
  SafeArrayUnaccessData( pvTimeStampMs->parray );
  SafeArrayUnaccessData( pvCoord->parray );
  if( pBuf) free( pBuf );

  return S_OK;

errCleanUp:

  if( pBuf) free( pBuf );
  if( pvTimeStampMs->parray ) {
    SafeArrayUnaccessData( pvTimeStampMs->parray );
    VariantClear( pvTimeStampMs );
  }
  if( pvCoord->parray ) {
    SafeArrayUnaccessData( pvCoord->parray );
    VariantClear( pvCoord );
  }

  return m_ErrorToHresult(iErr);
}

//-------------------------------------------------------
HRESULT CP_ET_Class::GetCOM_Index( long * piCOM_Idx ) {

  g_pEyeTrack->GetComPort( (int *) piCOM_Idx );
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_ET_Class::SetCOM_Index( long iCOM_Idx )  {

  g_pEyeTrack->SetComPort( iCOM_Idx );
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_ET_Class::GetBaudRate( long * piBaudRate ) {

  *piBaudRate = 0;
  g_pEyeTrack->GetBaudRate( (int *) piBaudRate );
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_ET_Class::SetBaudRate( long iBaudRate) {

  g_pEyeTrack->SetBaudRate( iBaudRate );
  return S_OK;
}



