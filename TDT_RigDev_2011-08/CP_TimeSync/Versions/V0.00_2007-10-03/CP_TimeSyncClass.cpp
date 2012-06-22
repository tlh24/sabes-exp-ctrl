// CP_TimeSyncClass - implementation of COM object

#include "CP_TimeSyncClass.h"
#include "TimeSyncGlob.h"
#include "CP_printf.h"
//#include "Float.h"

//===============================================================================
// CP_TimeSyncClass
CP_TimeSyncClass::CP_TimeSyncClass() : m_cRef(0) { 

  CoAddRefServerProcess();
}

//-------------------------------------------------------
HRESULT CP_TimeSyncClass::m_ErrorToHresult( int iErr ){
   return MAKE_HRESULT( SEVERITY_ERROR,  //  Indicate that function failed
                        FACILITY_ITF,    //  Specific interface - related error 
                        iErr ); // Our own error code
}


//-------------------------------------------------------
HRESULT CP_TimeSyncClass::QueryInterface(REFIID iid, void **ppv){

  if (ppv == NULL) return E_INVALIDARG;
  if(iid == IID_IUnknown)	{
    *ppv = (IUnknown*)this;
  }
  else if(iid == IID_IDispatch)	{
    *ppv = (IDispatch*)this; 
  }
  else if(iid == IID_ITimeSync)	{
    *ppv = (ITimeSync*)this;
  }
	else{
		*ppv = NULL;
		return E_NOINTERFACE;
	}
	AddRef();
	return S_OK;
}

//-------------------------------------------------------
HRESULT CP_TimeSyncClass::GetTypeInfo(UINT iTypeInfo, LCID lcid, ITypeInfo** ppITypeInfo){

  *ppITypeInfo = NULL;
	m_pTypeInfo->AddRef();
	*ppITypeInfo = m_pTypeInfo;
	return S_OK;
}




//-------------------------------------------------------
HRESULT CP_TimeSyncClass::ConnectRP2(BSTR bstInterfaceType, long iDevIdx,
                                     long * piResult){ 
  HRESULT hRes;

  hRes = g_pRPcoX->raw_ConnectRP2(bstInterfaceType, iDevIdx, piResult);

  if( hRes != S_OK ){
    CP_printf("ConnectRP2() ActiveX error!\n");
    *piResult = 0;
  }

  if( *piResult ) 
    CP_printf("ConnectRP2() - Ok. \n");
  else
    CP_printf("ConnectRP2() failed. \n");

  return 0;
}


//-------------------------------------------------------
HRESULT CP_TimeSyncClass::GetStatus(long * piStatus){ 
  HRESULT hRes;

  hRes = g_pRPcoX->raw_GetStatus( piStatus );

  if( hRes != S_OK ){
    CP_printf("GetStatus() ActiveX error!\n");
    return 0;
  }

  CP_printf("GetStatus(): %d \n", * piStatus);

  return 0;
}


//-------------------------------------------------------
HRESULT CP_TimeSyncClass::ClearCOF( long * piResult ){ 
  HRESULT hRes;

  hRes = g_pRPcoX->raw_ClearCOF(piResult);

  if( hRes != S_OK ){
    CP_printf("ClearCOF() ActiveX error!\n");
    *piResult = 0;
  }
  if( *piResult ) 
    CP_printf("ClearCOF() - Ok. \n");
  else
    CP_printf("ClearCOF() failed. \n");

  return 0;
}

//-------------------------------------------------------
HRESULT CP_TimeSyncClass::LoadCOF(BSTR bstFileName, long * piResult ){ 
  HRESULT hRes;

  hRes = g_pRPcoX->raw_LoadCOF( bstFileName, piResult);

  if( hRes != S_OK ){
    CP_printf("LoadCOF() ActiveX error!\n");
    *piResult = 0;
  }

  if( *piResult ) 
    CP_printf("LoadCOF() - Ok. \n");
  else
    CP_printf("LoadCOF() failed. \n");

  return 0;
}

//-------------------------------------------------------
HRESULT CP_TimeSyncClass::ReadCOF(BSTR bstFileName, long * piResult ){ 
  HRESULT hRes;

  hRes = g_pRPcoX->raw_ReadCOF( bstFileName, piResult);

  if( hRes != S_OK ){
    CP_printf("ReadCOF() ActiveX error!\n");
    *piResult = 0;
  }

  if( *piResult ) 
    CP_printf("ReadCOF() - Ok. \n");
  else
    CP_printf("ReadCOF() failed. \n");

  return 0;
}

//-------------------------------------------------------
HRESULT CP_TimeSyncClass::Run( long * piResult ){ 
  HRESULT hRes;

  hRes = g_pRPcoX->raw_Run( piResult );

  if( hRes != S_OK ){
    CP_printf("Run() ActiveX error!\n");
    *piResult = 0;
  }

  if( *piResult ) 
    CP_printf("Run() - Ok. \n");
  else
    CP_printf("Run() failed. \n");

  return 0;
}

//-------------------------------------------------------
HRESULT CP_TimeSyncClass::Halt( long * piResult ){ 
  HRESULT hRes;

  hRes = g_pRPcoX->raw_Halt( piResult );

  if( hRes != S_OK ){
    CP_printf("Halt() ActiveX error!\n");
    *piResult = 0;
  }

  if( *piResult ) 
    CP_printf("Halt() - Ok. \n");
  else
    CP_printf("Halt() failed. \n");

  return 0;
}

//-------------------------------------------------------
HRESULT CP_TimeSyncClass::GetSFreq(float * pfSamplingRate ){
  HRESULT hRes;

  hRes = g_pRPcoX->raw_GetSFreq( pfSamplingRate );

  if( hRes != S_OK ){
    CP_printf("GetSFreq() ActiveX error!\n");
  }

  CP_printf("GetSFreq(): %f \n", * pfSamplingRate);

  return 0;
}

//-------------------------------------------------------
HRESULT CP_TimeSyncClass::SoftTrg(long iBitIdx, long * piResult){ 
  HRESULT hRes;

  hRes = g_pRPcoX->raw_SoftTrg( iBitIdx, piResult );

  if( hRes != S_OK ){
    CP_printf("SoftTrg() ActiveX error!\n");
    *piResult = 0;
  }

  return 0;
}

//-------------------------------------------------------
HRESULT CP_TimeSyncClass::GetTagVal(BSTR bstTag, float * pfVal ){
  HRESULT hRes;

  hRes = g_pRPcoX->raw_GetTagVal( bstTag, pfVal );

  if( hRes != S_OK ){
    CP_printf("GetTagVal() ActiveX error!\n");
  }

  return 0;
}

//-------------------------------------------------------
HRESULT CP_TimeSyncClass::SetTagVal(BSTR bstTag, float fVal, 
                                    long * piResult){ 
  HRESULT hRes;

  hRes = g_pRPcoX->raw_SetTagVal( bstTag, fVal, piResult );

  if( hRes != S_OK ){
    CP_printf("SetTagVal() ActiveX error!\n");
  }

  return 0;
}

//-------------------------------------------------------
HRESULT CP_TimeSyncClass::ReadTagVEX( BSTR bstTag, 
                                  long iStartIdx, 
                                  long nItems, 
                                  BSTR bstSrcType, 
                                  BSTR bstDstType, 
                                  long nChans, 
                                  VARIANT * pvArray ){ 
  
  HRESULT hRes;

  hRes = g_pRPcoX->raw_ReadTagVEX( bstTag, 
                                  iStartIdx, 
                                  nItems, 
                                  bstSrcType, 
                                  bstDstType, 
                                  nChans, 
                                  pvArray );

  if( hRes != S_OK ){
    CP_printf("ReadTagVEX() ActiveX error!\n");
  }

  return 0;
}


