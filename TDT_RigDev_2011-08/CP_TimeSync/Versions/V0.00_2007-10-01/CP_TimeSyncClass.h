// CP_TimeSyncClass  - implementation of COM object

#ifndef __CP_TimeSyncCLASS_H_
#define __CP_TimeSyncCLASS_H_

#define _WIN32_WINNT 0x0500  // we are compiling for Win2000 or higher

#include "CP_TimeSyncCom.h"

//=================================================================================
// CP_TimeSyncClass
class CP_TimeSyncClass : public ITimeSync {

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

	CP_TimeSyncClass();

	~CP_TimeSyncClass() {
    m_pTypeInfo->Release(); 
    CoReleaseServerProcess();
  };

    HRESULT __stdcall ConnectRP2(BSTR bstInterfaceType, long iDevIdx,
                                 long * piResult );
    HRESULT __stdcall GetStatus(long * piStatus);
    HRESULT __stdcall ClearCOF( long * piResult );
    HRESULT __stdcall LoadCOF(BSTR bstFileName, long * piResult );
    HRESULT __stdcall ReadCOF(BSTR bstFileName, long * piResult );
    HRESULT __stdcall Run( long * piResult );
    HRESULT __stdcall Halt( long * piResult );
    HRESULT __stdcall GetSFreq(float * pfSamplingRate );
    HRESULT __stdcall SoftTrg(long iBitIdx, long * piResult );
    HRESULT __stdcall GetTagVal(BSTR bstTag, float * pfVal );
    HRESULT __stdcall SetTagVal(BSTR bstTag, float fVal,
                                long * piResult );
    HRESULT __stdcall ReadTagVEX( BSTR bstTag, 
                                  long iStartIdx, 
                                  long nItems, 
                                  BSTR bstSrcType, 
                                  BSTR bstDstType, 
                                  long nChans, 
                                  VARIANT * pvArray );

  
private:
	long m_cRef;

  HRESULT m_ErrorToHresult( int iErr );

protected:
};

#endif //__CP_TimeSyncCLASS_H_
