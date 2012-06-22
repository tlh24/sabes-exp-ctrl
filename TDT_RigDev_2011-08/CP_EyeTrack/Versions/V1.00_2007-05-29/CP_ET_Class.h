// CP_ET_Class  - implementation of COM object

#ifndef __CP_ET_CLASS_H_
#define __CP_ET_CLASS_H_

#define _WIN32_WINNT 0x0500  // we are compiling for Win2000 or higher

#include "CP_EyeTrackCom.h"

//=================================================================================
// CP_ET_Class
class CP_ET_Class : public IEyeTrack {

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

	CP_ET_Class();

	~CP_ET_Class() {
    m_pTypeInfo->Release(); 
    CoReleaseServerProcess();
  };

  HRESULT __stdcall get_strProgramVersion( BSTR * pVal);
  HRESULT __stdcall ConnectTracker();
  HRESULT __stdcall GetTrackerState(long * piState, long *piTrackerID);
  HRESULT __stdcall DisconnectTracker();
  HRESULT __stdcall GetTransformMatrix( SAFEARRAY ** ppsaMatrix );
  HRESULT __stdcall SetTransformMatrix( SAFEARRAY *   psaMatrix );
  HRESULT __stdcall GetTimeScale( double *pdC0, double *pdC1);
  HRESULT __stdcall SetTimeScale( double dC0, double dC1);
  HRESULT __stdcall get_lngBufferSize( long *pVal);

  HRESULT __stdcall GetIndexLatest( long *plIdx );

  HRESULT __stdcall GetDataLatest( long nItems,
                                   long *plIdx,
                                   SAFEARRAY ** ppsaTimeStampMs,
                                   SAFEARRAY ** ppsaData );

  HRESULT __stdcall GetDataBuffered( long nItems,
                                     long lngIdx,
                                     SAFEARRAY ** ppsaTimeStampMs,
                                     SAFEARRAY ** ppsaData );

  HRESULT __stdcall get_lngCOM_Index( long *pVal);
  HRESULT __stdcall put_lngCOM_Index( long newVal);

  HRESULT __stdcall get_lngBaudRate( long *pVal);
  HRESULT __stdcall put_lngBaudRate( long newVal);
 
private:
	long m_cRef;

  HRESULT m_ErrorToHresult( int iErr );

protected:
};

#endif //__CP_ET_CLASS_H_
