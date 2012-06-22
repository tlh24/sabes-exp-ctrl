// CP_ET_Class - implementation of COM object

#include "CP_ET_Class.h"
#include "EyeTrack.h"
#include "SafeArrayLib.h"
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
HRESULT CP_ET_Class::GetTrackerState( long *piTrackerID, long * piState ){

  *piState = g_pEyeTrack->IsRunning(); 
  *piTrackerID = 3;  // ISCAN ID

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
HRESULT CP_ET_Class::GetTransformMatrix( SAFEARRAY ** ppsaTransform ) {
  int iRes;
  SAFEARRAY *psaMtx;
  double * pdData;

  * ppsaTransform = NULL;
  // Output 6x2 array of doubles
  if( g_MakeSafeArray( TRANSF_MTX_N_2, TRANSF_MTX_N_1, &psaMtx, &pdData ) ){
    return m_ErrorToHresult(1);
  }

  iRes = g_pEyeTrack->GetTransformMatrix( pdData );
  SafeArrayUnaccessData( psaMtx );
  if( iRes ){
    CP_printf("\nError: GetTransformMatrix() failed!\n" );
    return m_ErrorToHresult( 1 );
  }
  * ppsaTransform = psaMtx;
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_ET_Class::SetTransformMatrix( SAFEARRAY * psaTransform ) {
  int iRes;
  double * pdData;

  // We expect 6x2 array of doubles
  if( g_CheckSafeArray( TRANSF_MTX_N_2, TRANSF_MTX_N_1, psaTransform, &pdData )) {
    SafeArrayUnaccessData( psaTransform );
    return m_ErrorToHresult( 1 );
  }
  iRes = g_pEyeTrack->SetTransformMatrix( pdData );
  SafeArrayUnaccessData( psaTransform );
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
                                    SAFEARRAY ** ppsaTimeStampMs,
                                    SAFEARRAY ** ppsaCoord ) {
  int iIdx;

  * piDataIdx = 0;
  if( ! g_pEyeTrack->GetLatestItemIdx( &iIdx ) ){
    return m_ErrorToHresult( 1 );
  }

  * piDataIdx = iIdx;
  return GetDataBuffered(  iIdx + 1 - nFrames,
                           nFrames,
                           ppsaTimeStampMs,
                           ppsaCoord );

}

//-------------------------------------------------------
HRESULT CP_ET_Class::GetDataBuffered( long iDataIdx,
                                      long nFrames,
                                      SAFEARRAY ** ppsaTimeStampMs,
                                      SAFEARRAY ** ppsaCoord ){

  int iErr = 0;
  void * pBuf;
  SAFEARRAY *psaTime;
  double * pdTimeStamps;
  SAFEARRAY * psaCoord;
  double * pdCoord;

  pBuf = NULL; 
  psaTime = NULL;
  psaCoord = NULL;
  //Set return pointers
  *ppsaTimeStampMs = NULL;
  *ppsaCoord = NULL;

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
  // Create output SAFEARRAY of doubles, size nFrames 
  if( g_MakeSafeArray( nFrames, &psaTime, &pdTimeStamps )){
    iErr = 1;
    goto errCleanUp; 
  }
  // Coordinates
  // Create output SAFEARRAY of floats, size nFrames x 2 
  if( g_MakeSafeArray( N_COORD, nFrames, &psaCoord, &pdCoord )){
    iErr = 1;
    goto errCleanUp; 
  }

  // Write timestamps and coordinates to SAFEARRAYs
  g_pEyeTrack->ParseBuffer(  nFrames, 
                             pBuf,       // Source buffer
                             pdTimeStamps,      // Dest. timestamps
                             pdCoord );      // Dest. coordinates
  
  SafeArrayUnaccessData( psaTime );
  SafeArrayUnaccessData( psaCoord );
  if( pBuf) free( pBuf );

  *ppsaTimeStampMs = psaTime;
  *ppsaCoord = psaCoord;
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

  * ppsaTimeStampMs = NULL;
  * ppsaCoord = NULL;

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



