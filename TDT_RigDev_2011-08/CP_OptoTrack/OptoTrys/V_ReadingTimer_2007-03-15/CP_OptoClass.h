// CP_OptoClass  - implementation of COM object

#ifndef __CP_OptoCLASS_H_
#define __CP_OptoCLASS_H_

#define _WIN32_WINNT 0x0500  // we are compiling for Win2000 or higher

#include "CP_OptoTrackCom.h"

//=================================================================================
// CP_OptoClass
class CP_OptoClass : public IOptoTrack {

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

	CP_OptoClass();

	~CP_OptoClass() {
    m_pTypeInfo->Release(); 
    CoReleaseServerProcess();
  };

  HRESULT __stdcall get_strProgramVersion( BSTR * pVal);
  HRESULT __stdcall ConnectTracker();
  HRESULT __stdcall GetTrackerState(long *pVal);
  HRESULT __stdcall DisconnectTracker();
  HRESULT __stdcall get_dPredictionTimeMs( double *pVal);
  HRESULT __stdcall put_dPredictionTimeMs( double newVal);
  HRESULT __stdcall ResetBuffer();
  HRESULT __stdcall GetSensors( SAFEARRAY ** ppadMatrix );
  HRESULT __stdcall SetSensors( SAFEARRAY * ppadMatrix);
  HRESULT __stdcall get_lngBufferSize( long *pVal);
  HRESULT __stdcall get_lngLatestDataIndex( long *pVal);
  HRESULT __stdcall GetSensorLatest( long lngSensorIdx, 
                                     long *plIdx, 
                                     SAFEARRAY ** ppadData );
  HRESULT __stdcall GetSensorBuffer( long lngSensorIdx, 
                                     long lngIdx, 
                                     long nItems,
                                     SAFEARRAY ** padData);
  HRESULT __stdcall GetAllSensorsLatest( long *plIdx, 
                                         SAFEARRAY ** ppadData );
  HRESULT __stdcall GetAllSensorsBuffer( long lngIdx, 
                                         long nItems,
                                         SAFEARRAY ** padData);

 
private:
	long m_cRef;

  HRESULT m_ErrorToHresult( int iErr );

protected:
};

#endif //__CP_OptoCLASS_H_
