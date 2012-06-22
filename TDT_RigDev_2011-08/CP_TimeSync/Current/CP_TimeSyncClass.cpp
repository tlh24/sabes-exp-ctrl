// CP_TimeSyncClass - implementation of COM object

// AtlAxWinInit is implemented in Atl.dll
#pragma comment(lib, "atl.lib")
#include <atldef.h>
//#define _ATL_DLL_IMPL
#include <atliface.h> 
#include <comdef.h>    // Compiler COM support: _com_error

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
	IUnknown * pUnk;
	IUnknown * pUnkCont;
	
	if(g_pTDevAccX==NULL){  
		// Initialize ATL control containment code.
		AtlAxWinInit(); 
		// Create ActiveX control using the window handle 
		// and get the IUnknown interface of this control
		// Also obtain smart pointer to RPcoX/TDevAccX using 
		// IUnknown of the control
		hRes = AtlAxCreateControlEx( OLESTR("RPco.X"), g_hWnd, NULL, 
			&pUnkCont, &pUnk, IID_NULL, NULL );
		g_pRPcoX = pUnk;
		pUnk->Release();
		
		// Connect to RP2
		hRes = g_pRPcoX->raw_ConnectRP2(bstInterfaceType, iDevIdx, piResult);
		
		if( hRes != S_OK ){
			CP_printf("ConnectRP2() ActiveX error!\n");
			*piResult = 0;
		}
		
		if( *piResult ){ 
			CP_printf("ConnectRP2() - Ok. \n");
		}
		else CP_printf("ConnectRP2() failed. \n");
	}
	else CP_printf("ConnectRP2() Cannot connect in OpenDev mode. \n");
	
	return 0;
}

//-------------------------------------------------------
HRESULT CP_TimeSyncClass::ConnectRX5(BSTR bstInterfaceType, long iDevIdx,
                                     long * piResult){ 
	HRESULT hRes;
	IUnknown * pUnk;
	IUnknown * pUnkCont;
	
	if(g_pTDevAccX==NULL){  
		// Initialize ATL control containment code.
		AtlAxWinInit(); 
		// Create ActiveX control using the window handle 
		// and get the IUnknown interface of this control
		// Also obtain smart pointer to RPcoX/TDevAccX using 
		// IUnknown of the control
		hRes = AtlAxCreateControlEx( OLESTR("RPco.X"), g_hWnd, NULL, 
			&pUnkCont, &pUnk, IID_NULL, NULL );
		g_pRPcoX = pUnk;
		pUnk->Release();
		
		// Connect to RX5
		hRes = g_pRPcoX->raw_ConnectRX5(bstInterfaceType, iDevIdx, piResult);
		
		if( hRes != S_OK ){
			CP_printf("ConnectRX5() ActiveX error!\n");
			*piResult = 0;
		}
		
		if( *piResult ) {
			CP_printf("ConnectRX5() - Ok. \n");
		}
		else CP_printf("ConnectRX5() failed. \n");
	}
	else CP_printf("ConnectRX5() Cannot connect in OpenDev mode. \n");
	
	
	return 0;
}

//-------------------------------------------------------
HRESULT CP_TimeSyncClass::ConnectServer(BSTR bstServerName, long * piResult){ 
	
	HRESULT hRes;
	IUnknown * pUnk;
	IUnknown * pUnkCont;
	
	if(g_pRPcoX==NULL){  
		// Initialize ATL control containment code.
		AtlAxWinInit(); 
		// Create ActiveX control using the window handle 
		// and get the IUnknown interface of this control
		// Also obtain smart pointer to RPcoX/TDevAccX using 
		// IUnknown of the control
		hRes = AtlAxCreateControlEx( OLESTR("TDevAccX.ocx"), g_hWnd, NULL, 
			&pUnkCont, &pUnk, IID_NULL, NULL );
		g_pTDevAccX = pUnk;
		pUnk->Release();
		
		if( hRes != S_OK ){
			CP_printf("AtlAxCreateControlEx() Error creating ActiveX object!\n");
			*piResult = 0;
		}

		// Connect to Server
		
		hRes = g_pTDevAccX->raw_ConnectServer(bstServerName, piResult);
		if( hRes != S_OK ){
			CP_printf("ConnectServer(%ls) ActiveX error (%lx)!\n",(LPCTSTR)bstServerName,hRes);
			*piResult = 0;
		}
		
		/*
		try{
		*piResult = g_pTDevAccX->ConnectServer(bstServerName);
		}
		catch(unsigned int u){
		CP_printf("ConnectServer() ActiveX error (%u)!\n",u);
		}
		catch(unsigned long u){
		CP_printf("ConnectServer() ActiveX error (%lu)!\n",u);
		}
		catch(char *u){
		CP_printf("ConnectServer() ActiveX error (%s)!\n",u);
		}
		*/
		if( *piResult ) {
			CP_printf("ConnectServer() - Ok. \n");
		}
		else
			CP_printf("ConnectServer() failed. \n");
	}
	else CP_printf("ConnectServer() Cannot connect in ActiveX mode.  \n");
	
	
	return 0;
}


//-------------------------------------------------------
HRESULT CP_TimeSyncClass::GetStatus(long * piStatus){ 
		
	if(g_pTDevAccX==NULL){
		HRESULT hRes;
		hRes = g_pRPcoX->raw_GetStatus( piStatus );
		
		if( hRes != S_OK ){
			CP_printf("GetStatus() ActiveX error!\n");
			return 0;
		}
		
		CP_printf("GetStatus(): %d \n", * piStatus);
	} else
		CP_printf("GetStatus(): Not defined in OpenDev mode\n");	
	return 0;
}

//-------------------------------------------------------
HRESULT CP_TimeSyncClass::GetDeviceStatus(BSTR bstDeviceName, long * piStatus){ 

	if(g_pRPcoX==NULL){
		HRESULT hRes;
		hRes = g_pTDevAccX->raw_GetDeviceStatus( bstDeviceName, piStatus );
		
		if( hRes != S_OK ){
			CP_printf("GetDeviceStatus() ActiveX error!\n");
			return 0;
		}
		
		CP_printf("GetDeviceStatus(): %d \n", * piStatus);
		
	} else
		CP_printf("GetDeviceStatus() Not defined for ActiveX mode. \n");
	
	
	return 0;
}

//-------------------------------------------------------
HRESULT CP_TimeSyncClass::GetSysMode(long * piStatus){ 

	if(g_pRPcoX==NULL){
		HRESULT hRes;
		hRes = g_pTDevAccX->raw_GetSysMode( piStatus );
		
		if( hRes != S_OK ){
			CP_printf("GetSysMode() ActiveX error!\n");
			return 0;
		}
		
		CP_printf("GetSysMode(): %d \n", * piStatus);
		
	} else
		CP_printf("GetSysMode() Not defined for RPcoX ActiveX interface. \n");
	
	
	return 0;
}


//-------------------------------------------------------
HRESULT CP_TimeSyncClass::ClearCOF( long * piResult ){ 
	
	if(g_pTDevAccX==NULL){
		HRESULT hRes;
		hRes = g_pRPcoX->raw_ClearCOF(piResult);
		
		if( hRes != S_OK ){
			CP_printf("ClearCOF() ActiveX error!\n");
			*piResult = 0;
		}
		if( *piResult ) CP_printf("ClearCOF() - Ok. \n");
		else			CP_printf("ClearCOF() failed. \n");
	}else
		CP_printf("ClearCOF() - Not Defined in OpenDev mode. \n");
	
	return 0;
}

//-------------------------------------------------------
HRESULT CP_TimeSyncClass::LoadCOF(BSTR bstFileName, long * piResult ){ 
	
	if(g_pTDevAccX==NULL){
		HRESULT hRes;
		hRes = g_pRPcoX->raw_LoadCOF( bstFileName, piResult);
		
		if( hRes != S_OK ){
			CP_printf("LoadCOF() ActiveX error!\n");
			*piResult = 0;
		}
		
		if( *piResult ) CP_printf("LoadCOF() - Ok. \n");
		else			CP_printf("LoadCOF() failed. \n");
	}else
		CP_printf("LoadCOF() - Not Defined in OpenDev mode. \n");
	
	return 0;
}

//-------------------------------------------------------
HRESULT CP_TimeSyncClass::ReadCOF(BSTR bstFileName, long * piResult ){ 
	
	if(g_pTDevAccX==NULL){
		HRESULT hRes;
		hRes = g_pRPcoX->raw_ReadCOF( bstFileName, piResult);
		
		if( hRes != S_OK ){
			CP_printf("ReadCOF() ActiveX error!\n");
			*piResult = 0;
		}
		
		if( *piResult ) CP_printf("ReadCOF() - Ok. \n");
		else			CP_printf("ReadCOF() failed. \n");
	}else
		CP_printf("ReadCOF() - Not Defined in OpenDev mode. \n");

  return 0;
}

//-------------------------------------------------------
HRESULT CP_TimeSyncClass::Run( long * piResult ){ 
	HRESULT hRes;
		
	if(g_pRPcoX){
		hRes = g_pRPcoX->raw_Run( piResult );
		
		if( hRes != S_OK ){
			CP_printf("Run() ActiveX error!\n");
			*piResult = 0;
		}
		if( *piResult ) CP_printf("Run() - Ok. \n");
		else			CP_printf("Run() failed. \n");
		
	}
	else if(g_pTDevAccX){
		hRes = g_pTDevAccX->raw_SetSysMode((long)3, piResult);  // Set status to Record==3
		
		if( hRes != S_OK ){
			CP_printf("Run() ActiveX error!\n");
			*piResult = 0;
		}
		if( *piResult ) CP_printf("Run() - Ok. \n");
		else			CP_printf("Run() failed. \n");
	} else
		CP_printf("Run() failed -- no servers connected. \n");
	
	return 0;
}

//-------------------------------------------------------
HRESULT CP_TimeSyncClass::Halt( long * piResult ){ 
	HRESULT hRes;
	
	if(g_pRPcoX){
		hRes = g_pRPcoX->raw_Halt( piResult );
		
		if( hRes != S_OK ){
			CP_printf("Halt() ActiveX error!\n");
			*piResult = 0;
		}
		if( *piResult ) CP_printf("Halt() - Ok. \n");
		else			CP_printf("Halt() failed. \n");
	}
	else if(g_pTDevAccX){
		hRes = g_pTDevAccX->raw_SetSysMode((long)0, piResult);  // Set status to Idle==0
		
		if( hRes != S_OK ){
			CP_printf("Halt() ActiveX error!\n");
			*piResult = 0;
		}
		if( *piResult ) CP_printf("Halt() - Ok. \n");
		else			CP_printf("Halt() failed. \n");
	} else
		CP_printf("Halt() failed -- no servers connected. \n");
	
	
	return 0;
}

//-------------------------------------------------------
HRESULT CP_TimeSyncClass::GetSFreq(float * pfSamplingRate ){
	
	if(g_pTDevAccX==NULL){
		HRESULT hRes;
		hRes = g_pRPcoX->raw_GetSFreq( pfSamplingRate );
		
		if( hRes != S_OK ){
			CP_printf("GetSFreq() ActiveX error!\n");
		}
		
		CP_printf("GetSFreq(): %f \n", * pfSamplingRate);
	}else
		CP_printf("GetSFreq() Not defined in OpenDev mode.\n");
	
	return 0;
}

//-------------------------------------------------------
HRESULT CP_TimeSyncClass::GetDeviceSFreq(BSTR bstDeviceName, float * pfSamplingRate ){
	
	if(g_pRPcoX==NULL){
		HRESULT hRes;
		hRes = g_pTDevAccX->raw_GetDeviceSF( bstDeviceName, pfSamplingRate );
		
		if( hRes != S_OK ){
			CP_printf("GetDeviceSFreq() ActiveX error!\n");
		}
		
		CP_printf("GetDeviceSFreq(): %f \n", * pfSamplingRate);
	}else
		CP_printf("GetDeviceSFreq() Not defined for RPcoX ActiveX interface.\n");


  return 0;
}

//-------------------------------------------------------
HRESULT CP_TimeSyncClass::SoftTrg(long iBitIdx, long * piResult){ 
	HRESULT hRes=S_OK;
	
	if(g_pTDevAccX==NULL){
		hRes = g_pRPcoX->raw_SoftTrg( iBitIdx, piResult );
	}else{
		// CP_printf("SoftTrg() Action not available in OpenDev mode.\n");
		LPTSTR lstr = new TCHAR[10];
		BSTR bstr;
		wsprintf(lstr,"zSwTrg~%ld",iBitIdx);
		bstr = SysAllocString(LPOLESTR(lstr));
		
		double dVal;
		// Set trigger to 1
		dVal=1;
		hRes = g_pTDevAccX->raw_SetTargetVal( bstr, dVal, piResult );
	}
	
	
	if( hRes != S_OK ){
		CP_printf("SoftTrg() ActiveX error!\n");
		*piResult = 0;
	}
	return 0;
}

//-------------------------------------------------------
HRESULT CP_TimeSyncClass::GetTagVal(BSTR bstTag, float * pfVal ){
	HRESULT hRes = S_OK;
	
	if(g_pRPcoX){
		hRes = g_pRPcoX->raw_GetTagVal( bstTag, pfVal );
	}
	else if(g_pTDevAccX){
		double pdVal;
		hRes = g_pTDevAccX->raw_GetTargetVal( bstTag, &pdVal );
		*pfVal = (float)pdVal;
	} else
		CP_printf("GetTagVal() failed -- no servers connected. \n");

	if( hRes != S_OK ) CP_printf("GetTagVal() ActiveX error!\n");
	
	return 0;
}


//-------------------------------------------------------
HRESULT CP_TimeSyncClass::SetTagVal(BSTR bstTag, float fVal, 
                                    long * piResult){ 
	HRESULT hRes = S_OK;
	
	if(g_pRPcoX){
		hRes = g_pRPcoX->raw_SetTagVal( bstTag, fVal, piResult );
	}
	else if(g_pTDevAccX){
		double dVal = fVal;
		hRes = g_pTDevAccX->raw_SetTargetVal( bstTag, dVal, piResult );
	} else
		CP_printf("SetTagVal() failed -- no servers connected. \n");

  if( hRes != S_OK )  CP_printf("SetTagVal() ActiveX error!\n");

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
	if(g_pTDevAccX==NULL){
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
	}else
		CP_printf("ReadTagVEX() Not defined (yet) in OpenDev mode\n");
	
	return 0;
}

