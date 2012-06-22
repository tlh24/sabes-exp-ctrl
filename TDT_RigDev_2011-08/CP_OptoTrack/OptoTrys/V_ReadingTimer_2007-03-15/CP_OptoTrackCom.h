/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Mar 07 21:21:54 2007
 */
/* Compiler settings for C:\users\rebrik\CP_OptoTrack\CP_OptoTrackCom.idl:
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

#ifndef __CP_OptoTrackCom_h__
#define __CP_OptoTrackCom_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IOptoTrack_FWD_DEFINED__
#define __IOptoTrack_FWD_DEFINED__
typedef interface IOptoTrack IOptoTrack;
#endif 	/* __IOptoTrack_FWD_DEFINED__ */


#ifndef __CP_OptoClass_FWD_DEFINED__
#define __CP_OptoClass_FWD_DEFINED__

#ifdef __cplusplus
typedef class CP_OptoClass CP_OptoClass;
#else
typedef struct CP_OptoClass CP_OptoClass;
#endif /* __cplusplus */

#endif 	/* __CP_OptoClass_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IOptoTrack_INTERFACE_DEFINED__
#define __IOptoTrack_INTERFACE_DEFINED__

/* interface IOptoTrack */
/* [unique][helpstring][oleautomation][dual][uuid][object] */ 


EXTERN_C const IID IID_IOptoTrack;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ebd33078-ceb1-11d5-9c3e-0050da2a68c8")
    IOptoTrack : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_strProgramVersion( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ConnectTracker( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTrackerState( 
            /* [out] */ long __RPC_FAR *pTracker) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DisconnectTracker( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_dPredictionTimeMs( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_dPredictionTimeMs( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ResetBuffer( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSensors( 
            /* [retval][out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *padSensors) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetSensors( 
            /* [in] */ SAFEARRAY __RPC_FAR * adMatrix) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_lngBufferSize( 
            /* [retval][out] */ long __RPC_FAR *pnItems) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_lngLatestDataIndex( 
            /* [retval][out] */ long __RPC_FAR *plIdx) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSensorLatest( 
            /* [in] */ long lngSensorIdx,
            /* [out] */ long __RPC_FAR *plIdx,
            /* [out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *padData) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSensorBuffer( 
            /* [in] */ long lngSensorIdx,
            /* [in] */ long lngIdx,
            /* [in] */ long nItems,
            /* [out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *padData) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAllSensorsLatest( 
            /* [out] */ long __RPC_FAR *plIdx,
            /* [out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *padData) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAllSensorsBuffer( 
            /* [in] */ long lngIdx,
            /* [in] */ long nItems,
            /* [out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *padData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IOptoTrackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IOptoTrack __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IOptoTrack __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IOptoTrack __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IOptoTrack __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IOptoTrack __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IOptoTrack __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IOptoTrack __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_strProgramVersion )( 
            IOptoTrack __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConnectTracker )( 
            IOptoTrack __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTrackerState )( 
            IOptoTrack __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pTracker);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DisconnectTracker )( 
            IOptoTrack __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_dPredictionTimeMs )( 
            IOptoTrack __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_dPredictionTimeMs )( 
            IOptoTrack __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetBuffer )( 
            IOptoTrack __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSensors )( 
            IOptoTrack __RPC_FAR * This,
            /* [retval][out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *padSensors);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSensors )( 
            IOptoTrack __RPC_FAR * This,
            /* [in] */ SAFEARRAY __RPC_FAR * adMatrix);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lngBufferSize )( 
            IOptoTrack __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pnItems);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lngLatestDataIndex )( 
            IOptoTrack __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plIdx);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSensorLatest )( 
            IOptoTrack __RPC_FAR * This,
            /* [in] */ long lngSensorIdx,
            /* [out] */ long __RPC_FAR *plIdx,
            /* [out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *padData);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSensorBuffer )( 
            IOptoTrack __RPC_FAR * This,
            /* [in] */ long lngSensorIdx,
            /* [in] */ long lngIdx,
            /* [in] */ long nItems,
            /* [out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *padData);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAllSensorsLatest )( 
            IOptoTrack __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *plIdx,
            /* [out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *padData);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAllSensorsBuffer )( 
            IOptoTrack __RPC_FAR * This,
            /* [in] */ long lngIdx,
            /* [in] */ long nItems,
            /* [out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *padData);
        
        END_INTERFACE
    } IOptoTrackVtbl;

    interface IOptoTrack
    {
        CONST_VTBL struct IOptoTrackVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IOptoTrack_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IOptoTrack_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IOptoTrack_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IOptoTrack_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IOptoTrack_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IOptoTrack_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IOptoTrack_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IOptoTrack_get_strProgramVersion(This,pVal)	\
    (This)->lpVtbl -> get_strProgramVersion(This,pVal)

#define IOptoTrack_ConnectTracker(This)	\
    (This)->lpVtbl -> ConnectTracker(This)

#define IOptoTrack_GetTrackerState(This,pTracker)	\
    (This)->lpVtbl -> GetTrackerState(This,pTracker)

#define IOptoTrack_DisconnectTracker(This)	\
    (This)->lpVtbl -> DisconnectTracker(This)

#define IOptoTrack_get_dPredictionTimeMs(This,pVal)	\
    (This)->lpVtbl -> get_dPredictionTimeMs(This,pVal)

#define IOptoTrack_put_dPredictionTimeMs(This,newVal)	\
    (This)->lpVtbl -> put_dPredictionTimeMs(This,newVal)

#define IOptoTrack_ResetBuffer(This)	\
    (This)->lpVtbl -> ResetBuffer(This)

#define IOptoTrack_GetSensors(This,padSensors)	\
    (This)->lpVtbl -> GetSensors(This,padSensors)

#define IOptoTrack_SetSensors(This,adMatrix)	\
    (This)->lpVtbl -> SetSensors(This,adMatrix)

#define IOptoTrack_get_lngBufferSize(This,pnItems)	\
    (This)->lpVtbl -> get_lngBufferSize(This,pnItems)

#define IOptoTrack_get_lngLatestDataIndex(This,plIdx)	\
    (This)->lpVtbl -> get_lngLatestDataIndex(This,plIdx)

#define IOptoTrack_GetSensorLatest(This,lngSensorIdx,plIdx,padData)	\
    (This)->lpVtbl -> GetSensorLatest(This,lngSensorIdx,plIdx,padData)

#define IOptoTrack_GetSensorBuffer(This,lngSensorIdx,lngIdx,nItems,padData)	\
    (This)->lpVtbl -> GetSensorBuffer(This,lngSensorIdx,lngIdx,nItems,padData)

#define IOptoTrack_GetAllSensorsLatest(This,plIdx,padData)	\
    (This)->lpVtbl -> GetAllSensorsLatest(This,plIdx,padData)

#define IOptoTrack_GetAllSensorsBuffer(This,lngIdx,nItems,padData)	\
    (This)->lpVtbl -> GetAllSensorsBuffer(This,lngIdx,nItems,padData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IOptoTrack_get_strProgramVersion_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IOptoTrack_get_strProgramVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IOptoTrack_ConnectTracker_Proxy( 
    IOptoTrack __RPC_FAR * This);


void __RPC_STUB IOptoTrack_ConnectTracker_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IOptoTrack_GetTrackerState_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pTracker);


void __RPC_STUB IOptoTrack_GetTrackerState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IOptoTrack_DisconnectTracker_Proxy( 
    IOptoTrack __RPC_FAR * This);


void __RPC_STUB IOptoTrack_DisconnectTracker_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IOptoTrack_get_dPredictionTimeMs_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IOptoTrack_get_dPredictionTimeMs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IOptoTrack_put_dPredictionTimeMs_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IOptoTrack_put_dPredictionTimeMs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IOptoTrack_ResetBuffer_Proxy( 
    IOptoTrack __RPC_FAR * This);


void __RPC_STUB IOptoTrack_ResetBuffer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IOptoTrack_GetSensors_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [retval][out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *padSensors);


void __RPC_STUB IOptoTrack_GetSensors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IOptoTrack_SetSensors_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [in] */ SAFEARRAY __RPC_FAR * adMatrix);


void __RPC_STUB IOptoTrack_SetSensors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IOptoTrack_get_lngBufferSize_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pnItems);


void __RPC_STUB IOptoTrack_get_lngBufferSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IOptoTrack_get_lngLatestDataIndex_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plIdx);


void __RPC_STUB IOptoTrack_get_lngLatestDataIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IOptoTrack_GetSensorLatest_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [in] */ long lngSensorIdx,
    /* [out] */ long __RPC_FAR *plIdx,
    /* [out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *padData);


void __RPC_STUB IOptoTrack_GetSensorLatest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IOptoTrack_GetSensorBuffer_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [in] */ long lngSensorIdx,
    /* [in] */ long lngIdx,
    /* [in] */ long nItems,
    /* [out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *padData);


void __RPC_STUB IOptoTrack_GetSensorBuffer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IOptoTrack_GetAllSensorsLatest_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *plIdx,
    /* [out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *padData);


void __RPC_STUB IOptoTrack_GetAllSensorsLatest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IOptoTrack_GetAllSensorsBuffer_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [in] */ long lngIdx,
    /* [in] */ long nItems,
    /* [out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *padData);


void __RPC_STUB IOptoTrack_GetAllSensorsBuffer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IOptoTrack_INTERFACE_DEFINED__ */



#ifndef __CP_OptoTrackLib_LIBRARY_DEFINED__
#define __CP_OptoTrackLib_LIBRARY_DEFINED__

/* library CP_OptoTrackLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_CP_OptoTrackLib;

EXTERN_C const CLSID CLSID_CP_OptoClass;

#ifdef __cplusplus

class DECLSPEC_UUID("ebd33070-ceb1-11d5-9c3e-0050da2a68c8")
CP_OptoClass;
#endif
#endif /* __CP_OptoTrackLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

unsigned long             __RPC_USER  LPSAFEARRAY_UserSize(     unsigned long __RPC_FAR *, unsigned long            , LPSAFEARRAY __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  LPSAFEARRAY_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, LPSAFEARRAY __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  LPSAFEARRAY_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, LPSAFEARRAY __RPC_FAR * ); 
void                      __RPC_USER  LPSAFEARRAY_UserFree(     unsigned long __RPC_FAR *, LPSAFEARRAY __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
