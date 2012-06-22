// CP_TS_Class  - implementation of COM object

#ifndef __CP_TS_CLASS_H_
#define __CP_TS_CLASS_H_

#define _WIN32_WINNT 0x0500  // we are compiling for Win2000 or higher

#include "CP_TDT_StreamCom.h"

//=================================================================================
// CP_TS_Class
class CP_TS_Class : public ITDT_Stream {

public:
 	ITypeInfo* m_pTypeInfo;


  //IUnknown
	HRESULT __stdcall QueryInterface(REFIID iid, void** ppv);
  // We keep the server running even when all clients are gone
  ULONG __stdcall AddRef() { return InterlockedIncrement(&m_cRef); };
  ULONG __stdcall Release() {return InterlockedDecrement(&m_cRef); };

	HRESULT __stdcall GetTypeInfoCount(UINT* pCountTypeInfo) {
    *pCountTypeInfo = 1;  
    return S_OK; 
  };
	HRESULT __stdcall GetTypeInfo(UINT iTypeInfo, LCID lcid, ITypeInfo** ppITypeInfo);
	HRESULT __stdcall GetIDsOfNames(REFIID riid, LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgDispId){ 
    return DispGetIDsOfNames(m_pTypeInfo, rgszNames, cNames, rgDispId); 
  };
	HRESULT __stdcall Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS* pDispParams, VARIANT* pVarResult, EXCEPINFO* pExcepInfo, UINT* puArgErr){ 
    return DispInvoke(this, m_pTypeInfo, dispIdMember, wFlags, pDispParams, pVarResult, pExcepInfo, puArgErr); 
  };

	CP_TS_Class();

	~CP_TS_Class() {
    m_pTypeInfo->Release(); 
    CoReleaseServerProcess();
  };

  HRESULT __stdcall ConnectTDT_Server();
  HRESULT __stdcall DisconnectTDT_Server();
  HRESULT __stdcall put_strServerName( BSTR newVal);
  HRESULT __stdcall get_strServerName( BSTR *pVal);
  HRESULT __stdcall put_strDeviceName( BSTR newVal);
  HRESULT __stdcall get_strDeviceName( BSTR *pVal);
  HRESULT __stdcall get_lngSystemMode( long * pVal);
  HRESULT __stdcall get_strFileName( BSTR *pVal);
  HRESULT __stdcall put_strFileName( BSTR newVal);
  HRESULT __stdcall get_lngBlockSize( long *pVal);
  HRESULT __stdcall put_lngBlockSize( long newVal);
  HRESULT __stdcall SetArmedState( );
  HRESULT __stdcall SetIdleState( );
  HRESULT __stdcall get_lngStreamState( long *pVal);
  HRESULT __stdcall get_lngN_Samples( long *pVal);
  HRESULT __stdcall get_lngTimeTick( long *pVal);
  HRESULT __stdcall get_strProgramVersion( BSTR * pVal);
  HRESULT __stdcall get_lngBufferSize( long *pVal);
  HRESULT __stdcall put_lngBufferSize( long newVal);
  HRESULT __stdcall get_fSampleRateHz( float *pVal);
  HRESULT __stdcall get_strFilePath( BSTR *pVal);
  HRESULT __stdcall put_strFilePath( BSTR newVal);
  HRESULT __stdcall get_blnConvertToInt16( long *pVal);
  HRESULT __stdcall put_blnConvertToInt16( long newVal);
 
private:
	long m_cRef;

  HRESULT m_ErrorToHresult( int iErr );

protected:
};

#endif //__CP_TS_CLASS_H_
