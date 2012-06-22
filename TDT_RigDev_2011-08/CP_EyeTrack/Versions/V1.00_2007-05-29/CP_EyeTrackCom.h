/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue May 29 21:59:25 2007
 */
/* Compiler settings for Y:\work\Sabes\CP_EyeTrack\Current\CP_EyeTrackCom.idl:
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

#ifndef __CP_EyeTrackCom_h__
#define __CP_EyeTrackCom_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEyeTrack_FWD_DEFINED__
#define __IEyeTrack_FWD_DEFINED__
typedef interface IEyeTrack IEyeTrack;
#endif 	/* __IEyeTrack_FWD_DEFINED__ */


#ifndef __CP_ET_Class_FWD_DEFINED__
#define __CP_ET_Class_FWD_DEFINED__

#ifdef __cplusplus
typedef class CP_ET_Class CP_ET_Class;
#else
typedef struct CP_ET_Class CP_ET_Class;
#endif /* __cplusplus */

#endif 	/* __CP_ET_Class_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IEyeTrack_INTERFACE_DEFINED__
#define __IEyeTrack_INTERFACE_DEFINED__

/* interface IEyeTrack */
/* [unique][helpstring][oleautomation][dual][uuid][object] */ 


EXTERN_C const IID IID_IEyeTrack;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ebd33058-ceb1-11d5-9c3e-0050da2a68c8")
    IEyeTrack : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_strProgramVersion( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ConnectTracker( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTrackerState( 
            /* [out] */ long __RPC_FAR *piState,
            /* [out] */ long __RPC_FAR *piTrackerID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DisconnectTracker( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTransformMatrix( 
            /* [out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *psaMatrix) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetTransformMatrix( 
            /* [in] */ SAFEARRAY __RPC_FAR * saMatrix) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTimeScale( 
            /* [out] */ double __RPC_FAR *pdC0,
            /* [out] */ double __RPC_FAR *pdC1) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetTimeScale( 
            /* [in] */ double dC0,
            /* [in] */ double dC1) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_lngBufferSize( 
            /* [retval][out] */ long __RPC_FAR *pnItems) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetIndexLatest( 
            /* [out] */ long __RPC_FAR *plIdx) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDataLatest( 
            /* [defaultvalue][in] */ long nItems,
            /* [out] */ long __RPC_FAR *plIdx,
            /* [out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *padTimeStampMs,
            /* [out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *pafData) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDataBuffered( 
            /* [in] */ long nItems,
            /* [in] */ long lngIdx,
            /* [out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *padTimeStampMs,
            /* [out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *pafData) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_lngCOM_Index( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_lngCOM_Index( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_lngBaudRate( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_lngBaudRate( 
            /* [in] */ long newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEyeTrackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEyeTrack __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEyeTrack __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEyeTrack __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IEyeTrack __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IEyeTrack __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IEyeTrack __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IEyeTrack __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_strProgramVersion )( 
            IEyeTrack __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConnectTracker )( 
            IEyeTrack __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTrackerState )( 
            IEyeTrack __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *piState,
            /* [out] */ long __RPC_FAR *piTrackerID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DisconnectTracker )( 
            IEyeTrack __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTransformMatrix )( 
            IEyeTrack __RPC_FAR * This,
            /* [out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *psaMatrix);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetTransformMatrix )( 
            IEyeTrack __RPC_FAR * This,
            /* [in] */ SAFEARRAY __RPC_FAR * saMatrix);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTimeScale )( 
            IEyeTrack __RPC_FAR * This,
            /* [out] */ double __RPC_FAR *pdC0,
            /* [out] */ double __RPC_FAR *pdC1);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetTimeScale )( 
            IEyeTrack __RPC_FAR * This,
            /* [in] */ double dC0,
            /* [in] */ double dC1);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lngBufferSize )( 
            IEyeTrack __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pnItems);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIndexLatest )( 
            IEyeTrack __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *plIdx);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDataLatest )( 
            IEyeTrack __RPC_FAR * This,
            /* [defaultvalue][in] */ long nItems,
            /* [out] */ long __RPC_FAR *plIdx,
            /* [out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *padTimeStampMs,
            /* [out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *pafData);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDataBuffered )( 
            IEyeTrack __RPC_FAR * This,
            /* [in] */ long nItems,
            /* [in] */ long lngIdx,
            /* [out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *padTimeStampMs,
            /* [out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *pafData);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lngCOM_Index )( 
            IEyeTrack __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_lngCOM_Index )( 
            IEyeTrack __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lngBaudRate )( 
            IEyeTrack __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_lngBaudRate )( 
            IEyeTrack __RPC_FAR * This,
            /* [in] */ long newVal);
        
        END_INTERFACE
    } IEyeTrackVtbl;

    interface IEyeTrack
    {
        CONST_VTBL struct IEyeTrackVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEyeTrack_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEyeTrack_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEyeTrack_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEyeTrack_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IEyeTrack_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IEyeTrack_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IEyeTrack_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IEyeTrack_get_strProgramVersion(This,pVal)	\
    (This)->lpVtbl -> get_strProgramVersion(This,pVal)

#define IEyeTrack_ConnectTracker(This)	\
    (This)->lpVtbl -> ConnectTracker(This)

#define IEyeTrack_GetTrackerState(This,piState,piTrackerID)	\
    (This)->lpVtbl -> GetTrackerState(This,piState,piTrackerID)

#define IEyeTrack_DisconnectTracker(This)	\
    (This)->lpVtbl -> DisconnectTracker(This)

#define IEyeTrack_GetTransformMatrix(This,psaMatrix)	\
    (This)->lpVtbl -> GetTransformMatrix(This,psaMatrix)

#define IEyeTrack_SetTransformMatrix(This,saMatrix)	\
    (This)->lpVtbl -> SetTransformMatrix(This,saMatrix)

#define IEyeTrack_GetTimeScale(This,pdC0,pdC1)	\
    (This)->lpVtbl -> GetTimeScale(This,pdC0,pdC1)

#define IEyeTrack_SetTimeScale(This,dC0,dC1)	\
    (This)->lpVtbl -> SetTimeScale(This,dC0,dC1)

#define IEyeTrack_get_lngBufferSize(This,pnItems)	\
    (This)->lpVtbl -> get_lngBufferSize(This,pnItems)

#define IEyeTrack_GetIndexLatest(This,plIdx)	\
    (This)->lpVtbl -> GetIndexLatest(This,plIdx)

#define IEyeTrack_GetDataLatest(This,nItems,plIdx,padTimeStampMs,pafData)	\
    (This)->lpVtbl -> GetDataLatest(This,nItems,plIdx,padTimeStampMs,pafData)

#define IEyeTrack_GetDataBuffered(This,nItems,lngIdx,padTimeStampMs,pafData)	\
    (This)->lpVtbl -> GetDataBuffered(This,nItems,lngIdx,padTimeStampMs,pafData)

#define IEyeTrack_get_lngCOM_Index(This,pVal)	\
    (This)->lpVtbl -> get_lngCOM_Index(This,pVal)

#define IEyeTrack_put_lngCOM_Index(This,newVal)	\
    (This)->lpVtbl -> put_lngCOM_Index(This,newVal)

#define IEyeTrack_get_lngBaudRate(This,pVal)	\
    (This)->lpVtbl -> get_lngBaudRate(This,pVal)

#define IEyeTrack_put_lngBaudRate(This,newVal)	\
    (This)->lpVtbl -> put_lngBaudRate(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEyeTrack_get_strProgramVersion_Proxy( 
    IEyeTrack __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IEyeTrack_get_strProgramVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEyeTrack_ConnectTracker_Proxy( 
    IEyeTrack __RPC_FAR * This);


void __RPC_STUB IEyeTrack_ConnectTracker_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEyeTrack_GetTrackerState_Proxy( 
    IEyeTrack __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *piState,
    /* [out] */ long __RPC_FAR *piTrackerID);


void __RPC_STUB IEyeTrack_GetTrackerState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEyeTrack_DisconnectTracker_Proxy( 
    IEyeTrack __RPC_FAR * This);


void __RPC_STUB IEyeTrack_DisconnectTracker_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEyeTrack_GetTransformMatrix_Proxy( 
    IEyeTrack __RPC_FAR * This,
    /* [out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *psaMatrix);


void __RPC_STUB IEyeTrack_GetTransformMatrix_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEyeTrack_SetTransformMatrix_Proxy( 
    IEyeTrack __RPC_FAR * This,
    /* [in] */ SAFEARRAY __RPC_FAR * saMatrix);


void __RPC_STUB IEyeTrack_SetTransformMatrix_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEyeTrack_GetTimeScale_Proxy( 
    IEyeTrack __RPC_FAR * This,
    /* [out] */ double __RPC_FAR *pdC0,
    /* [out] */ double __RPC_FAR *pdC1);


void __RPC_STUB IEyeTrack_GetTimeScale_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEyeTrack_SetTimeScale_Proxy( 
    IEyeTrack __RPC_FAR * This,
    /* [in] */ double dC0,
    /* [in] */ double dC1);


void __RPC_STUB IEyeTrack_SetTimeScale_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEyeTrack_get_lngBufferSize_Proxy( 
    IEyeTrack __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pnItems);


void __RPC_STUB IEyeTrack_get_lngBufferSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEyeTrack_GetIndexLatest_Proxy( 
    IEyeTrack __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *plIdx);


void __RPC_STUB IEyeTrack_GetIndexLatest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEyeTrack_GetDataLatest_Proxy( 
    IEyeTrack __RPC_FAR * This,
    /* [defaultvalue][in] */ long nItems,
    /* [out] */ long __RPC_FAR *plIdx,
    /* [out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *padTimeStampMs,
    /* [out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *pafData);


void __RPC_STUB IEyeTrack_GetDataLatest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEyeTrack_GetDataBuffered_Proxy( 
    IEyeTrack __RPC_FAR * This,
    /* [in] */ long nItems,
    /* [in] */ long lngIdx,
    /* [out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *padTimeStampMs,
    /* [out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *pafData);


void __RPC_STUB IEyeTrack_GetDataBuffered_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEyeTrack_get_lngCOM_Index_Proxy( 
    IEyeTrack __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IEyeTrack_get_lngCOM_Index_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IEyeTrack_put_lngCOM_Index_Proxy( 
    IEyeTrack __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IEyeTrack_put_lngCOM_Index_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEyeTrack_get_lngBaudRate_Proxy( 
    IEyeTrack __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IEyeTrack_get_lngBaudRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IEyeTrack_put_lngBaudRate_Proxy( 
    IEyeTrack __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IEyeTrack_put_lngBaudRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEyeTrack_INTERFACE_DEFINED__ */



#ifndef __CP_EyeTrackLib_LIBRARY_DEFINED__
#define __CP_EyeTrackLib_LIBRARY_DEFINED__

/* library CP_EyeTrackLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_CP_EyeTrackLib;

EXTERN_C const CLSID CLSID_CP_ET_Class;

#ifdef __cplusplus

class DECLSPEC_UUID("ebd33050-ceb1-11d5-9c3e-0050da2a68c8")
CP_ET_Class;
#endif
#endif /* __CP_EyeTrackLib_LIBRARY_DEFINED__ */

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
