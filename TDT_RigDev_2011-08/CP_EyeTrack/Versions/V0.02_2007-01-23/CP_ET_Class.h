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
  HRESULT __stdcall ConnectISCAN();
  HRESULT __stdcall DisconnectISCAN();
  HRESULT __stdcall ResetBuffer();
  HRESULT __stdcall get_lngCOM_Index( long *pVal);
  HRESULT __stdcall put_lngCOM_Index( long newVal);
  HRESULT __stdcall get_lngBaudRate( long *pVal);
  HRESULT __stdcall put_lngBaudRate( long newVal);
  HRESULT __stdcall GetCalibrationMatrix( SAFEARRAY ** ppadMatrix );
  HRESULT __stdcall PutCalibrationMatrix( SAFEARRAY * ppadMatrix);
  HRESULT __stdcall get_IsCalibrated( long *pVal);
  HRESULT __stdcall put_IsCalibrated( long newVal);
  HRESULT __stdcall get_lngBufferSize( long *pVal);
  HRESULT __stdcall get_lngLatestDataIndex( long *pVal);
  HRESULT __stdcall GetLatestRawData( long *plIdx, double *pdTimeMs, long *plX, long *plY);
  HRESULT __stdcall GetLatestData( long *plIdx, SAFEARRAY ** ppadData );
  HRESULT __stdcall GetDataBuffer( long lngIdx, 
                                   long nItems,
                                   SAFEARRAY ** padData);
  HRESULT __stdcall ResetDataBuffer( );

 
private:
	long m_cRef;

  HRESULT m_ErrorToHresult( int iErr );

protected:
};

#endif //__CP_ET_CLASS_H_
