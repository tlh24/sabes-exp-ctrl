// CP_TS_Class - implementation of COM object

//#include "ShadowPrint.h"
#include "CP_TS_Class.h"
#include "TDT_Stream.h"


//===============================================================================
// CP_TS_Class
CP_TS_Class::CP_TS_Class() : m_cRef(0) { 

  CoAddRefServerProcess();
}

//-------------------------------------------------------
HRESULT CP_TS_Class::m_ErrorToHresult( int iErr ){
   return MAKE_HRESULT( SEVERITY_ERROR,  //  Indicate that function failed
                        FACILITY_ITF,    //  Specific interface - related error 
                        iErr ); // Our own error code
}


//-------------------------------------------------------
HRESULT CP_TS_Class::QueryInterface(REFIID iid, void **ppv){

  if (ppv == NULL) return E_INVALIDARG;
  if(iid == IID_IUnknown)	{
    *ppv = (IUnknown*)this;
  }
  else if(iid == IID_IDispatch)	{
    *ppv = (IDispatch*)this; 
  }
  else if(iid == IID_ITDT_Stream)	{
    *ppv = (ITDT_Stream*)this;
  }
	else{
		*ppv = NULL;
		return E_NOINTERFACE;
	}
	AddRef();
	return S_OK;
}

//-------------------------------------------------------
HRESULT CP_TS_Class::GetTypeInfo(UINT iTypeInfo, LCID lcid, ITypeInfo** ppITypeInfo){

  *ppITypeInfo = NULL;
	m_pTypeInfo->AddRef();
	*ppITypeInfo = m_pTypeInfo;
	return S_OK;
}


//-------------------------------------------------------
HRESULT CP_TS_Class::ConnectTDT_Server() {
  int iRes;

  iRes = g_pTDT_Stream->ConnectServer();
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_TS_Class::DisconnectTDT_Server() {
  int iRes;

  iRes = g_pTDT_Stream->DisconnectServer();
  return S_OK;
}


//-------------------------------------------------------
HRESULT CP_TS_Class::put_strServerName( BSTR newVal) {
  int iRes;

  iRes = g_pTDT_Stream->SetServerName(newVal); 
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_TS_Class::get_strServerName( BSTR *pVal) {
  int iRes;

  iRes = g_pTDT_Stream->GetServerName(pVal);
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_TS_Class::put_strDeviceName( BSTR newVal) {
  int iRes;

  iRes = g_pTDT_Stream->SetDeviceName(newVal); 
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_TS_Class::get_strDeviceName( BSTR *pVal) {
  int iRes;

  iRes = g_pTDT_Stream->GetDeviceName(pVal);
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_TS_Class::get_lngSystemMode( long * pVal) {
  int iRes, iMode;

  iRes = g_pTDT_Stream->GetSystemMode( & iMode);
  * pVal = iMode;
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_TS_Class::get_strFileName( BSTR *pVal) {
  int iRes;

  iRes = g_pTDT_Stream->GetFileName(pVal);
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_TS_Class::put_strFileName( BSTR newVal) {
  int iRes;

  iRes = g_pTDT_Stream->SetFileName( newVal );
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_TS_Class::get_lngBlockSize( long *pVal) {
  int iRes;

  iRes = g_pTDT_Stream->GetBlockSize( (int *) pVal);
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_TS_Class::put_lngBlockSize( long newVal) {
  int iRes;

  iRes = g_pTDT_Stream->SetBlockSize( newVal);
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_TS_Class::SetArmedState( ) {
  int iRes;

  iRes = g_pTDT_Stream->SetArmedState();
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_TS_Class::SetIdleState( ) {
  int iRes;

  iRes = g_pTDT_Stream->SetIdleState();
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_TS_Class::get_lngStreamState( long *pVal) {
  int iRes, iStat;

  iRes = g_pTDT_Stream->GetStreamState( & iStat);
  * pVal = iStat;
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_TS_Class::get_lngN_Samples( long *pVal) {
  int iRes, nSamples;

  iRes = g_pTDT_Stream->GetN_Samples( &nSamples );
  *pVal = nSamples;
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_TS_Class::get_lngTimeTick( long *pVal) {
  int iRes, iTick;

  iRes = g_pTDT_Stream->GetTimeTick( &iTick );
  *pVal = iTick;
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_TS_Class::get_strProgramVersion( BSTR * pVal) {
  int iRes;

  iRes = g_pTDT_Stream->GetVersion( pVal);
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_TS_Class::get_lngBufferSize( long *pVal) {
  int iRes;

  iRes = g_pTDT_Stream->GetBufferSize( (int *)pVal);
  return S_OK;
}


//-------------------------------------------------------
HRESULT CP_TS_Class::put_lngBufferSize( long newVal) {
  int iRes;

  iRes = g_pTDT_Stream->SetBufferSize( newVal);
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_TS_Class::get_fSampleRateHz( float *pVal) {
  int iRes;

  iRes = g_pTDT_Stream->GetSampRateHz( pVal);
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_TS_Class::get_strFilePath( BSTR *pVal) {
  int iRes;

  iRes = g_pTDT_Stream->GetFilePath(pVal);
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_TS_Class::put_strFilePath( BSTR newVal) {
  int iRes;

  iRes = g_pTDT_Stream->SetFilePath( newVal );
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_TS_Class::get_blnConvertToInt16( long *pVal) {
  int iRes;

  iRes = g_pTDT_Stream->GetConvertToInt16Flag( (int *)pVal );
  return S_OK;
}

//-------------------------------------------------------
HRESULT CP_TS_Class::put_blnConvertToInt16( long newVal) {
  int iRes;

  iRes = g_pTDT_Stream->SetConvertToInt16Flag( newVal );
  return S_OK;
}
