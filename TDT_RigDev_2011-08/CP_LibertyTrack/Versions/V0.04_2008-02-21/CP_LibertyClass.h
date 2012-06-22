// CP_LibertyClass  - implementation of COM object

#ifndef __CP_LibertyCLASS_H_
#define __CP_LibertyCLASS_H_

#define _WIN32_WINNT 0x0500  // we are compiling for Win2000 or higher

#include "CP_LibertyTrackCom.h"

//=================================================================================
// CP_LibertyClass
class CP_LibertyClass : public ILibertyTrack {

public:
 	ITypeInfo* m_pTypeInfo;


  //IUnknown
	STDMETHOD(QueryInterface)(REFIID iid, void** ppv);
  // We keep the server running even when all clients are gone
  ULONG _stdcall AddRef() { return InterlockedIncrement(&m_cRef); };
  ULONG _stdcall Release() {return InterlockedDecrement(&m_cRef); };

	STDMETHOD(GetTypeInfoCount)(UINT* pnCountTypeInfo) {
    *pnCountTypeInfo = 1;  
    return S_OK; 
  };
	STDMETHOD(GetTypeInfo)(UINT iTypeInfo, LCID lcid, ITypeInfo** ppITypeInfo);
	STDMETHOD(GetIDsOfNames)(REFIID riid, LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgDispId){ 
    return DispGetIDsOfNames(m_pTypeInfo, rgszNames, cNames, rgDispId); 
  };
	STDMETHOD(Invoke)(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS* pDispParams, VARIANT* pVarResult, EXCEPINFO* pExcepInfo, UINT* puArgErr){ 
    return DispInvoke(this, m_pTypeInfo, dispIdMember, wFlags, pDispParams, pVarResult, pExcepInfo, puArgErr); 
  };

	CP_LibertyClass();

	~CP_LibertyClass() {
    m_pTypeInfo->Release(); 
    CoReleaseServerProcess();
  };

  STDMETHOD(GetVersion)( BSTR * pbstVersion);
  STDMETHOD(ConnectTracker)();
  STDMETHOD(DisconnectTracker)();
  STDMETHOD(GetTrackerState)(long * piTrackerID,
                             long * piState );

  STDMETHOD(GetFrameCount)( long * pnFrames );
  STDMETHOD(GetTimeScale)( double *pdC0,
                           double *pdC1);
  STDMETHOD(SetTimeScale)( double dC0,
                           double dC1);

  STDMETHOD(GetTransformMatrix)(long iTransformIdx,
                                SAFEARRAY ** ppsaTransform);
  STDMETHOD(SetTransformMatrix)( SAFEARRAY * psaTransform,
                                 long iTransformIdx);

  STDMETHOD(GetSensors)( SAFEARRAY ** ppsaSensors);
  STDMETHOD(SetSensors)( SAFEARRAY * psaSensors);

  STDMETHOD(ActivateSensors)( );
  STDMETHOD(DeactivateSensors)( );

  STDMETHOD(GetSensorsTransformIdx)( SAFEARRAY ** ppsaTransformIdx);
  STDMETHOD(SetSensorsTransformIdx)( SAFEARRAY * psaTransformIdx);

  STDMETHOD(GetBufferSize)( long *pnFrames);
  STDMETHOD(GetDataIndexLatest)( long *piDataIdx );
  STDMETHOD(GetSensorLatest)( long iSensorIdx,
                              long nFrames,
                              long *piDataIdx,
                              SAFEARRAY ** ppsaTimeStampMs,
                              SAFEARRAY ** ppsaCoord,
                              SAFEARRAY ** ppsaVelocity );
  STDMETHOD(GetSensorBuffered)( long iSensorIdx,
                                long iDataIdx,
                                long nFrames,
                                SAFEARRAY ** ppsaTimeStampMs,
                                SAFEARRAY ** ppsaCoord,
                                SAFEARRAY ** ppsaVelocity );
  STDMETHOD(GetAllSensorsLatest)( long nFrames,
                                  long *piDataIdx,
                                  SAFEARRAY ** ppsaTimeStampMs,
                                  SAFEARRAY ** ppsaCoord,
                                  SAFEARRAY ** ppsaVelocity );
  STDMETHOD(GetAllSensorsBuffered)( long iDataIdx,
                                    long nFrames,
                                    SAFEARRAY ** ppsaTimeStampMs,
                                    SAFEARRAY ** ppsaCoord,
                                    SAFEARRAY ** ppsaVelocity );

private:
	long m_cRef;

  HRESULT m_ErrorToHresult( int iErr );

protected:
};

#endif //__CP_LibertyCLASS_H_
