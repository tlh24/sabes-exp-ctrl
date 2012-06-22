/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Aug 19 15:52:04 2011
 */
/* Compiler settings for D:\Sabes\Dropbox\2011-LabCode\TDT_RigDev_2011-08\CP_TimeSync\Current\CP_TimeSyncCom.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __CP_TimeSyncCom_h__
#define __CP_TimeSyncCom_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ITimeSync_FWD_DEFINED__
#define __ITimeSync_FWD_DEFINED__
typedef interface ITimeSync ITimeSync;
#endif 	/* __ITimeSync_FWD_DEFINED__ */


#ifndef __CP_TimeSyncClass_FWD_DEFINED__
#define __CP_TimeSyncClass_FWD_DEFINED__

#ifdef __cplusplus
typedef class CP_TimeSyncClass CP_TimeSyncClass;
#else
typedef struct CP_TimeSyncClass CP_TimeSyncClass;
#endif /* __cplusplus */

#endif 	/* __CP_TimeSyncClass_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ITimeSync_INTERFACE_DEFINED__
#define __ITimeSync_INTERFACE_DEFINED__

/* interface ITimeSync */
/* [unique][helpstring][oleautomation][dual][uuid][object] */ 


EXTERN_C const IID IID_ITimeSync;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ebd330d8-ceb1-11d5-9c3e-0050da2a68c8")
    ITimeSync : public IDispatch
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ConnectRP2( 
            /* [in] */ BSTR bstInterfaceType,
            /* [in] */ long iDevIdx,
            /* [retval][out] */ long __RPC_FAR *piResult) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ConnectRX5( 
            /* [in] */ BSTR bstInterfaceType,
            /* [in] */ long iDevIdx,
            /* [retval][out] */ long __RPC_FAR *piResult) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ConnectServer( 
            /* [in] */ BSTR bstServerName,
            /* [retval][out] */ long __RPC_FAR *piResult) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetStatus( 
            /* [retval][out] */ long __RPC_FAR *piStatus) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetDeviceStatus( 
            /* [in] */ BSTR bstDeviceName,
            /* [retval][out] */ long __RPC_FAR *piStatus) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetSysMode( 
            /* [retval][out] */ long __RPC_FAR *piStatus) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ClearCOF( 
            /* [retval][out] */ long __RPC_FAR *piResult) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE LoadCOF( 
            /* [in] */ BSTR bstFileName,
            /* [retval][out] */ long __RPC_FAR *piResult) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReadCOF( 
            /* [in] */ BSTR bstFileName,
            /* [retval][out] */ long __RPC_FAR *piResult) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Run( 
            /* [retval][out] */ long __RPC_FAR *piResult) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Halt( 
            /* [retval][out] */ long __RPC_FAR *piResult) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetSFreq( 
            /* [retval][out] */ float __RPC_FAR *pfSamplingRate) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetDeviceSFreq( 
            /* [in] */ BSTR bstDeviceName,
            /* [retval][out] */ float __RPC_FAR *pfSamplingRate) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SoftTrg( 
            /* [in] */ long iBitIdx,
            /* [retval][out] */ long __RPC_FAR *piResult) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetTagVal( 
            /* [in] */ BSTR bstTag,
            /* [retval][out] */ float __RPC_FAR *pfVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetTagVal( 
            /* [in] */ BSTR bstTag,
            /* [in] */ float fVal,
            /* [retval][out] */ long __RPC_FAR *piResult) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReadTagVEX( 
            /* [in] */ BSTR bstTag,
            /* [in] */ long iStartIdx,
            /* [in] */ long nItems,
            /* [in] */ BSTR bstSrcType,
            /* [in] */ BSTR bstDstType,
            /* [in] */ long nChans,
            /* [retval][out] */ VARIANT __RPC_FAR *pvArray) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITimeSyncVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITimeSync __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITimeSync __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITimeSync __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITimeSync __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITimeSync __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITimeSync __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITimeSync __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConnectRP2 )( 
            ITimeSync __RPC_FAR * This,
            /* [in] */ BSTR bstInterfaceType,
            /* [in] */ long iDevIdx,
            /* [retval][out] */ long __RPC_FAR *piResult);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConnectRX5 )( 
            ITimeSync __RPC_FAR * This,
            /* [in] */ BSTR bstInterfaceType,
            /* [in] */ long iDevIdx,
            /* [retval][out] */ long __RPC_FAR *piResult);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConnectServer )( 
            ITimeSync __RPC_FAR * This,
            /* [in] */ BSTR bstServerName,
            /* [retval][out] */ long __RPC_FAR *piResult);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetStatus )( 
            ITimeSync __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *piStatus);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDeviceStatus )( 
            ITimeSync __RPC_FAR * This,
            /* [in] */ BSTR bstDeviceName,
            /* [retval][out] */ long __RPC_FAR *piStatus);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSysMode )( 
            ITimeSync __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *piStatus);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ClearCOF )( 
            ITimeSync __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *piResult);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadCOF )( 
            ITimeSync __RPC_FAR * This,
            /* [in] */ BSTR bstFileName,
            /* [retval][out] */ long __RPC_FAR *piResult);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReadCOF )( 
            ITimeSync __RPC_FAR * This,
            /* [in] */ BSTR bstFileName,
            /* [retval][out] */ long __RPC_FAR *piResult);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Run )( 
            ITimeSync __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *piResult);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Halt )( 
            ITimeSync __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *piResult);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSFreq )( 
            ITimeSync __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pfSamplingRate);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDeviceSFreq )( 
            ITimeSync __RPC_FAR * This,
            /* [in] */ BSTR bstDeviceName,
            /* [retval][out] */ float __RPC_FAR *pfSamplingRate);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SoftTrg )( 
            ITimeSync __RPC_FAR * This,
            /* [in] */ long iBitIdx,
            /* [retval][out] */ long __RPC_FAR *piResult);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTagVal )( 
            ITimeSync __RPC_FAR * This,
            /* [in] */ BSTR bstTag,
            /* [retval][out] */ float __RPC_FAR *pfVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetTagVal )( 
            ITimeSync __RPC_FAR * This,
            /* [in] */ BSTR bstTag,
            /* [in] */ float fVal,
            /* [retval][out] */ long __RPC_FAR *piResult);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReadTagVEX )( 
            ITimeSync __RPC_FAR * This,
            /* [in] */ BSTR bstTag,
            /* [in] */ long iStartIdx,
            /* [in] */ long nItems,
            /* [in] */ BSTR bstSrcType,
            /* [in] */ BSTR bstDstType,
            /* [in] */ long nChans,
            /* [retval][out] */ VARIANT __RPC_FAR *pvArray);
        
        END_INTERFACE
    } ITimeSyncVtbl;

    interface ITimeSync
    {
        CONST_VTBL struct ITimeSyncVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITimeSync_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITimeSync_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITimeSync_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITimeSync_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITimeSync_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITimeSync_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITimeSync_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITimeSync_ConnectRP2(This,bstInterfaceType,iDevIdx,piResult)	\
    (This)->lpVtbl -> ConnectRP2(This,bstInterfaceType,iDevIdx,piResult)

#define ITimeSync_ConnectRX5(This,bstInterfaceType,iDevIdx,piResult)	\
    (This)->lpVtbl -> ConnectRX5(This,bstInterfaceType,iDevIdx,piResult)

#define ITimeSync_ConnectServer(This,bstServerName,piResult)	\
    (This)->lpVtbl -> ConnectServer(This,bstServerName,piResult)

#define ITimeSync_GetStatus(This,piStatus)	\
    (This)->lpVtbl -> GetStatus(This,piStatus)

#define ITimeSync_GetDeviceStatus(This,bstDeviceName,piStatus)	\
    (This)->lpVtbl -> GetDeviceStatus(This,bstDeviceName,piStatus)

#define ITimeSync_GetSysMode(This,piStatus)	\
    (This)->lpVtbl -> GetSysMode(This,piStatus)

#define ITimeSync_ClearCOF(This,piResult)	\
    (This)->lpVtbl -> ClearCOF(This,piResult)

#define ITimeSync_LoadCOF(This,bstFileName,piResult)	\
    (This)->lpVtbl -> LoadCOF(This,bstFileName,piResult)

#define ITimeSync_ReadCOF(This,bstFileName,piResult)	\
    (This)->lpVtbl -> ReadCOF(This,bstFileName,piResult)

#define ITimeSync_Run(This,piResult)	\
    (This)->lpVtbl -> Run(This,piResult)

#define ITimeSync_Halt(This,piResult)	\
    (This)->lpVtbl -> Halt(This,piResult)

#define ITimeSync_GetSFreq(This,pfSamplingRate)	\
    (This)->lpVtbl -> GetSFreq(This,pfSamplingRate)

#define ITimeSync_GetDeviceSFreq(This,bstDeviceName,pfSamplingRate)	\
    (This)->lpVtbl -> GetDeviceSFreq(This,bstDeviceName,pfSamplingRate)

#define ITimeSync_SoftTrg(This,iBitIdx,piResult)	\
    (This)->lpVtbl -> SoftTrg(This,iBitIdx,piResult)

#define ITimeSync_GetTagVal(This,bstTag,pfVal)	\
    (This)->lpVtbl -> GetTagVal(This,bstTag,pfVal)

#define ITimeSync_SetTagVal(This,bstTag,fVal,piResult)	\
    (This)->lpVtbl -> SetTagVal(This,bstTag,fVal,piResult)

#define ITimeSync_ReadTagVEX(This,bstTag,iStartIdx,nItems,bstSrcType,bstDstType,nChans,pvArray)	\
    (This)->lpVtbl -> ReadTagVEX(This,bstTag,iStartIdx,nItems,bstSrcType,bstDstType,nChans,pvArray)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITimeSync_ConnectRP2_Proxy( 
    ITimeSync __RPC_FAR * This,
    /* [in] */ BSTR bstInterfaceType,
    /* [in] */ long iDevIdx,
    /* [retval][out] */ long __RPC_FAR *piResult);


void __RPC_STUB ITimeSync_ConnectRP2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITimeSync_ConnectRX5_Proxy( 
    ITimeSync __RPC_FAR * This,
    /* [in] */ BSTR bstInterfaceType,
    /* [in] */ long iDevIdx,
    /* [retval][out] */ long __RPC_FAR *piResult);


void __RPC_STUB ITimeSync_ConnectRX5_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITimeSync_ConnectServer_Proxy( 
    ITimeSync __RPC_FAR * This,
    /* [in] */ BSTR bstServerName,
    /* [retval][out] */ long __RPC_FAR *piResult);


void __RPC_STUB ITimeSync_ConnectServer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITimeSync_GetStatus_Proxy( 
    ITimeSync __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *piStatus);


void __RPC_STUB ITimeSync_GetStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITimeSync_GetDeviceStatus_Proxy( 
    ITimeSync __RPC_FAR * This,
    /* [in] */ BSTR bstDeviceName,
    /* [retval][out] */ long __RPC_FAR *piStatus);


void __RPC_STUB ITimeSync_GetDeviceStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITimeSync_GetSysMode_Proxy( 
    ITimeSync __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *piStatus);


void __RPC_STUB ITimeSync_GetSysMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITimeSync_ClearCOF_Proxy( 
    ITimeSync __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *piResult);


void __RPC_STUB ITimeSync_ClearCOF_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITimeSync_LoadCOF_Proxy( 
    ITimeSync __RPC_FAR * This,
    /* [in] */ BSTR bstFileName,
    /* [retval][out] */ long __RPC_FAR *piResult);


void __RPC_STUB ITimeSync_LoadCOF_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITimeSync_ReadCOF_Proxy( 
    ITimeSync __RPC_FAR * This,
    /* [in] */ BSTR bstFileName,
    /* [retval][out] */ long __RPC_FAR *piResult);


void __RPC_STUB ITimeSync_ReadCOF_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITimeSync_Run_Proxy( 
    ITimeSync __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *piResult);


void __RPC_STUB ITimeSync_Run_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITimeSync_Halt_Proxy( 
    ITimeSync __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *piResult);


void __RPC_STUB ITimeSync_Halt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITimeSync_GetSFreq_Proxy( 
    ITimeSync __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pfSamplingRate);


void __RPC_STUB ITimeSync_GetSFreq_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITimeSync_GetDeviceSFreq_Proxy( 
    ITimeSync __RPC_FAR * This,
    /* [in] */ BSTR bstDeviceName,
    /* [retval][out] */ float __RPC_FAR *pfSamplingRate);


void __RPC_STUB ITimeSync_GetDeviceSFreq_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITimeSync_SoftTrg_Proxy( 
    ITimeSync __RPC_FAR * This,
    /* [in] */ long iBitIdx,
    /* [retval][out] */ long __RPC_FAR *piResult);


void __RPC_STUB ITimeSync_SoftTrg_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITimeSync_GetTagVal_Proxy( 
    ITimeSync __RPC_FAR * This,
    /* [in] */ BSTR bstTag,
    /* [retval][out] */ float __RPC_FAR *pfVal);


void __RPC_STUB ITimeSync_GetTagVal_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITimeSync_SetTagVal_Proxy( 
    ITimeSync __RPC_FAR * This,
    /* [in] */ BSTR bstTag,
    /* [in] */ float fVal,
    /* [retval][out] */ long __RPC_FAR *piResult);


void __RPC_STUB ITimeSync_SetTagVal_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITimeSync_ReadTagVEX_Proxy( 
    ITimeSync __RPC_FAR * This,
    /* [in] */ BSTR bstTag,
    /* [in] */ long iStartIdx,
    /* [in] */ long nItems,
    /* [in] */ BSTR bstSrcType,
    /* [in] */ BSTR bstDstType,
    /* [in] */ long nChans,
    /* [retval][out] */ VARIANT __RPC_FAR *pvArray);


void __RPC_STUB ITimeSync_ReadTagVEX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITimeSync_INTERFACE_DEFINED__ */



#ifndef __CP_TimeSync_Lib_LIBRARY_DEFINED__
#define __CP_TimeSync_Lib_LIBRARY_DEFINED__

/* library CP_TimeSync_Lib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_CP_TimeSync_Lib;

EXTERN_C const CLSID CLSID_CP_TimeSyncClass;

#ifdef __cplusplus

class DECLSPEC_UUID("ebd330d0-ceb1-11d5-9c3e-0050da2a68c8")
CP_TimeSyncClass;
#endif
#endif /* __CP_TimeSync_Lib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long __RPC_FAR *, unsigned long            , VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long __RPC_FAR *, VARIANT __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
