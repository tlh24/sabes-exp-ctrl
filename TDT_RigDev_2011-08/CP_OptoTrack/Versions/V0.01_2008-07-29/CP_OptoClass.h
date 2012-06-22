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

	CP_OptoClass();

	~CP_OptoClass() {
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
                                VARIANT * pvTransform);
  STDMETHOD(SetTransformMatrix)( VARIANT vTransform,
                                 long iTransformIdx);

  STDMETHOD(GetSensors)( VARIANT * pvSensors);
  STDMETHOD(SetSensors)( VARIANT vSensors);

  STDMETHOD(ActivateSensors)( );
  STDMETHOD(DeactivateSensors)( );

  STDMETHOD(GetSensorsTransformIdx)( VARIANT * pvTransformIdx);
  STDMETHOD(SetSensorsTransformIdx)( VARIANT vTransformIdx);

  STDMETHOD(GetBufferSize)( long *pnFrames);
  STDMETHOD(GetDataIndexLatest)( long *piDataIdx );
  STDMETHOD(GetSensorLatest)( long iSensorIdx,
                              long nFrames,
                              long *piDataIdx,
                              VARIANT * pvTimeStamp,
                              VARIANT * pvCoord,
                              VARIANT * pvVelocity );
  STDMETHOD(GetSensorBuffered)( long iSensorIdx,
                                long iDataIdx,
                                long nFrames,
                                VARIANT * pvTimeStamp,
                                VARIANT * pvCoord,
                                VARIANT * pvVelocity );
  STDMETHOD(GetAllSensorsLatest)( long nFrames,
                                  long *piDataIdx,
                                  VARIANT * pvTimeStamp,
                                  VARIANT * pvCoord,
                                  VARIANT * pvVelocity );
  STDMETHOD(GetAllSensorsBuffered)( long iDataIdx,
                                    long nFrames,
                                    VARIANT * pvTimeStamp,
                                    VARIANT * pvCoord,
                                    VARIANT * pvVelocity );
  
private:
	long m_cRef;

  HRESULT m_ErrorToHresult( int iErr );

protected:
};

#endif //__CP_OptoCLASS_H_
