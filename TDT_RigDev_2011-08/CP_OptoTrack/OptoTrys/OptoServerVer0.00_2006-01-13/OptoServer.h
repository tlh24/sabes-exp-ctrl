/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Jan 13 18:18:44 2006
 */
/* Compiler settings for C:\LAB\Source\OptoServer\OptoServer.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
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

#ifndef __OptoServer_h__
#define __OptoServer_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IOptoServer_FWD_DEFINED__
#define __IOptoServer_FWD_DEFINED__
typedef interface IOptoServer IOptoServer;
#endif 	/* __IOptoServer_FWD_DEFINED__ */


#ifndef __OptoServer_FWD_DEFINED__
#define __OptoServer_FWD_DEFINED__

#ifdef __cplusplus
typedef class OptoServer OptoServer;
#else
typedef struct OptoServer OptoServer;
#endif /* __cplusplus */

#endif 	/* __OptoServer_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IOptoServer_INTERFACE_DEFINED__
#define __IOptoServer_INTERFACE_DEFINED__

/* interface IOptoServer */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IOptoServer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B066FF86-7D9E-4C8F-9A34-F640BFDD3BE4")
    IOptoServer : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_active( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_active( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_latest( 
            /* [retval][out] */ VARIANT __RPC_FAR *posVar) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_next( 
            /* [retval][out] */ VARIANT __RPC_FAR *posVar) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE startBuffer( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE stopBuffer( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getBuffer( 
            /* [in] */ short marker,
            /* [retval][out] */ VARIANT __RPC_FAR *posVar) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE setup( 
            /* [in] */ VARIANT makers,
            /* [in] */ float rate,
            /* [optional][in] */ float time) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE setframe( 
            /* [in] */ VARIANT makers) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_error( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_latestframe( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IOptoServerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IOptoServer __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IOptoServer __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IOptoServer __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IOptoServer __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IOptoServer __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IOptoServer __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IOptoServer __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_active )( 
            IOptoServer __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_active )( 
            IOptoServer __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_latest )( 
            IOptoServer __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *posVar);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_next )( 
            IOptoServer __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *posVar);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *startBuffer )( 
            IOptoServer __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *stopBuffer )( 
            IOptoServer __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getBuffer )( 
            IOptoServer __RPC_FAR * This,
            /* [in] */ short marker,
            /* [retval][out] */ VARIANT __RPC_FAR *posVar);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setup )( 
            IOptoServer __RPC_FAR * This,
            /* [in] */ VARIANT makers,
            /* [in] */ float rate,
            /* [optional][in] */ float time);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setframe )( 
            IOptoServer __RPC_FAR * This,
            /* [in] */ VARIANT makers);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_error )( 
            IOptoServer __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_latestframe )( 
            IOptoServer __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        END_INTERFACE
    } IOptoServerVtbl;

    interface IOptoServer
    {
        CONST_VTBL struct IOptoServerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IOptoServer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IOptoServer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IOptoServer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IOptoServer_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IOptoServer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IOptoServer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IOptoServer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IOptoServer_get_active(This,pVal)	\
    (This)->lpVtbl -> get_active(This,pVal)

#define IOptoServer_put_active(This,newVal)	\
    (This)->lpVtbl -> put_active(This,newVal)

#define IOptoServer_get_latest(This,posVar)	\
    (This)->lpVtbl -> get_latest(This,posVar)

#define IOptoServer_get_next(This,posVar)	\
    (This)->lpVtbl -> get_next(This,posVar)

#define IOptoServer_startBuffer(This)	\
    (This)->lpVtbl -> startBuffer(This)

#define IOptoServer_stopBuffer(This)	\
    (This)->lpVtbl -> stopBuffer(This)

#define IOptoServer_getBuffer(This,marker,posVar)	\
    (This)->lpVtbl -> getBuffer(This,marker,posVar)

#define IOptoServer_setup(This,makers,rate,time)	\
    (This)->lpVtbl -> setup(This,makers,rate,time)

#define IOptoServer_setframe(This,makers)	\
    (This)->lpVtbl -> setframe(This,makers)

#define IOptoServer_get_error(This,pVal)	\
    (This)->lpVtbl -> get_error(This,pVal)

#define IOptoServer_get_latestframe(This,pVal)	\
    (This)->lpVtbl -> get_latestframe(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IOptoServer_get_active_Proxy( 
    IOptoServer __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IOptoServer_get_active_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IOptoServer_put_active_Proxy( 
    IOptoServer __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB IOptoServer_put_active_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IOptoServer_get_latest_Proxy( 
    IOptoServer __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *posVar);


void __RPC_STUB IOptoServer_get_latest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IOptoServer_get_next_Proxy( 
    IOptoServer __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *posVar);


void __RPC_STUB IOptoServer_get_next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IOptoServer_startBuffer_Proxy( 
    IOptoServer __RPC_FAR * This);


void __RPC_STUB IOptoServer_startBuffer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IOptoServer_stopBuffer_Proxy( 
    IOptoServer __RPC_FAR * This);


void __RPC_STUB IOptoServer_stopBuffer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IOptoServer_getBuffer_Proxy( 
    IOptoServer __RPC_FAR * This,
    /* [in] */ short marker,
    /* [retval][out] */ VARIANT __RPC_FAR *posVar);


void __RPC_STUB IOptoServer_getBuffer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IOptoServer_setup_Proxy( 
    IOptoServer __RPC_FAR * This,
    /* [in] */ VARIANT makers,
    /* [in] */ float rate,
    /* [optional][in] */ float time);


void __RPC_STUB IOptoServer_setup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IOptoServer_setframe_Proxy( 
    IOptoServer __RPC_FAR * This,
    /* [in] */ VARIANT makers);


void __RPC_STUB IOptoServer_setframe_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IOptoServer_get_error_Proxy( 
    IOptoServer __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IOptoServer_get_error_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IOptoServer_get_latestframe_Proxy( 
    IOptoServer __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IOptoServer_get_latestframe_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IOptoServer_INTERFACE_DEFINED__ */



#ifndef __OPTOSERVERLib_LIBRARY_DEFINED__
#define __OPTOSERVERLib_LIBRARY_DEFINED__

/* library OPTOSERVERLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_OPTOSERVERLib;

EXTERN_C const CLSID CLSID_OptoServer;

#ifdef __cplusplus

class DECLSPEC_UUID("858130AA-8F41-4B35-B8F0-04E358904B48")
OptoServer;
#endif
#endif /* __OPTOSERVERLib_LIBRARY_DEFINED__ */

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
