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
	STDMETHOD(QueryInterface)(REFIID iid, void** ppv);
  // We keep the server running even when all clients are gone
  ULONG __stdcall AddRef() { return InterlockedIncrement(&m_cRef); };
  ULONG __stdcall Release() {return InterlockedDecrement(&m_cRef); };

	STDMETHOD(GetTypeInfoCount)(UINT* pCountTypeInfo) {
    *pCountTypeInfo = 1;  
    return S_OK; 
  };
	STDMETHOD(GetTypeInfo)(UINT iTypeInfo, LCID lcid, ITypeInfo** ppITypeInfo);
	STDMETHOD(GetIDsOfNames)(REFIID riid, LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgDispId){ 
    return DispGetIDsOfNames(m_pTypeInfo, rgszNames, cNames, rgDispId); 
  };
	STDMETHOD(Invoke)(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS* pDispParams, VARIANT* pVarResult, EXCEPINFO* pExcepInfo, UINT* puArgErr){ 
    return DispInvoke(this, m_pTypeInfo, dispIdMember, wFlags, pDispParams, pVarResult, pExcepInfo, puArgErr); 
  };

	CP_ET_Class();

	~CP_ET_Class() {
    m_pTypeInfo->Release(); 
    CoReleaseServerProcess();
  };

  STDMETHOD(GetVersion)( BSTR * pbstVersion);
  STDMETHOD(GetTrackerState)(long *piTrackerID, long * piState);
  STDMETHOD(ConnectTracker)();
  STDMETHOD(DisconnectTracker)();
  STDMETHOD(GetTimeScale)( double *pdC0, double *pdC1);
  STDMETHOD(SetTimeScale)( double dC0, double dC1);
  STDMETHOD(GetTransformMatrix)( SAFEARRAY ** ppsaTransform );
  STDMETHOD(SetTransformMatrix)( SAFEARRAY *  psaTransform );

  STDMETHOD(GetBufferSize)( long * pnFrames );

  STDMETHOD(GetDataIndexLatest)( long * piDataIdx );

  STDMETHOD(GetDataLatest)( long nFrames,
                            long *piDataIdx,
                            SAFEARRAY ** ppsaTimeStampMs,
                            SAFEARRAY ** ppsaCoord);

  STDMETHOD(GetDataBuffered)(long iDataIdx,
                             long nFrames,
                             SAFEARRAY ** ppsaTimeStampMs,
                             SAFEARRAY ** ppsaCoord );

  STDMETHOD(GetCOM_Index)( long * piCOM_Idx );
  STDMETHOD(SetCOM_Index)( long iCOM_Idx );

  STDMETHOD(GetBaudRate)( long * piBaudRate );
  STDMETHOD(SetBaudRate)( long iBaudRate );
 
private:
	long m_cRef;

  HRESULT m_ErrorToHresult( int iErr );

protected:
};

#endif //__CP_ET_CLASS_H_
