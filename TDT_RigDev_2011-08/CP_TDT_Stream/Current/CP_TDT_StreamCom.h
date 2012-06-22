/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Jul 07 21:08:51 2006
 */
/* Compiler settings for Y:\work\Sabes\CP_TDT_Stream\Current\CP_TDT_StreamCom.idl:
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

#ifndef __CP_TDT_StreamCom_h__
#define __CP_TDT_StreamCom_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ITDT_Stream_FWD_DEFINED__
#define __ITDT_Stream_FWD_DEFINED__
typedef interface ITDT_Stream ITDT_Stream;
#endif 	/* __ITDT_Stream_FWD_DEFINED__ */


#ifndef __CP_TS_Class_FWD_DEFINED__
#define __CP_TS_Class_FWD_DEFINED__

#ifdef __cplusplus
typedef class CP_TS_Class CP_TS_Class;
#else
typedef struct CP_TS_Class CP_TS_Class;
#endif /* __cplusplus */

#endif 	/* __CP_TS_Class_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ITDT_Stream_INTERFACE_DEFINED__
#define __ITDT_Stream_INTERFACE_DEFINED__

/* interface ITDT_Stream */
/* [unique][helpstring][oleautomation][dual][uuid][object] */ 


EXTERN_C const IID IID_ITDT_Stream;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ebd33040-ceb1-11d5-9c3e-0050da2a68c8")
    ITDT_Stream : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ConnectTDT_Server( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DisconnectTDT_Server( void) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_strServerName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_strServerName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_strDeviceName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_strDeviceName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_lngSystemMode( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_strFileName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_strFileName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_lngBlockSize( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_lngBlockSize( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetArmedState( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetIdleState( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_lngStreamState( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_lngN_Samples( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_lngTimeTick( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_strProgramVersion( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_lngBufferSize( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_lngBufferSize( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_fSampleRateHz( 
            /* [retval][out] */ float __RPC_FAR *fVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_strFilePath( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_strFilePath( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_blnConvertToInt16( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_blnConvertToInt16( 
            /* [in] */ long newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITDT_StreamVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITDT_Stream __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITDT_Stream __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITDT_Stream __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITDT_Stream __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITDT_Stream __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITDT_Stream __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITDT_Stream __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConnectTDT_Server )( 
            ITDT_Stream __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DisconnectTDT_Server )( 
            ITDT_Stream __RPC_FAR * This);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_strServerName )( 
            ITDT_Stream __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_strServerName )( 
            ITDT_Stream __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_strDeviceName )( 
            ITDT_Stream __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_strDeviceName )( 
            ITDT_Stream __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lngSystemMode )( 
            ITDT_Stream __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_strFileName )( 
            ITDT_Stream __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_strFileName )( 
            ITDT_Stream __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lngBlockSize )( 
            ITDT_Stream __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_lngBlockSize )( 
            ITDT_Stream __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetArmedState )( 
            ITDT_Stream __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetIdleState )( 
            ITDT_Stream __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lngStreamState )( 
            ITDT_Stream __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lngN_Samples )( 
            ITDT_Stream __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lngTimeTick )( 
            ITDT_Stream __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_strProgramVersion )( 
            ITDT_Stream __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lngBufferSize )( 
            ITDT_Stream __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_lngBufferSize )( 
            ITDT_Stream __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_fSampleRateHz )( 
            ITDT_Stream __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *fVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_strFilePath )( 
            ITDT_Stream __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_strFilePath )( 
            ITDT_Stream __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_blnConvertToInt16 )( 
            ITDT_Stream __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_blnConvertToInt16 )( 
            ITDT_Stream __RPC_FAR * This,
            /* [in] */ long newVal);
        
        END_INTERFACE
    } ITDT_StreamVtbl;

    interface ITDT_Stream
    {
        CONST_VTBL struct ITDT_StreamVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITDT_Stream_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITDT_Stream_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITDT_Stream_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITDT_Stream_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITDT_Stream_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITDT_Stream_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITDT_Stream_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITDT_Stream_ConnectTDT_Server(This)	\
    (This)->lpVtbl -> ConnectTDT_Server(This)

#define ITDT_Stream_DisconnectTDT_Server(This)	\
    (This)->lpVtbl -> DisconnectTDT_Server(This)

#define ITDT_Stream_put_strServerName(This,newVal)	\
    (This)->lpVtbl -> put_strServerName(This,newVal)

#define ITDT_Stream_get_strServerName(This,pVal)	\
    (This)->lpVtbl -> get_strServerName(This,pVal)

#define ITDT_Stream_put_strDeviceName(This,newVal)	\
    (This)->lpVtbl -> put_strDeviceName(This,newVal)

#define ITDT_Stream_get_strDeviceName(This,pVal)	\
    (This)->lpVtbl -> get_strDeviceName(This,pVal)

#define ITDT_Stream_get_lngSystemMode(This,pVal)	\
    (This)->lpVtbl -> get_lngSystemMode(This,pVal)

#define ITDT_Stream_get_strFileName(This,pVal)	\
    (This)->lpVtbl -> get_strFileName(This,pVal)

#define ITDT_Stream_put_strFileName(This,newVal)	\
    (This)->lpVtbl -> put_strFileName(This,newVal)

#define ITDT_Stream_get_lngBlockSize(This,pVal)	\
    (This)->lpVtbl -> get_lngBlockSize(This,pVal)

#define ITDT_Stream_put_lngBlockSize(This,newVal)	\
    (This)->lpVtbl -> put_lngBlockSize(This,newVal)

#define ITDT_Stream_SetArmedState(This)	\
    (This)->lpVtbl -> SetArmedState(This)

#define ITDT_Stream_SetIdleState(This)	\
    (This)->lpVtbl -> SetIdleState(This)

#define ITDT_Stream_get_lngStreamState(This,pVal)	\
    (This)->lpVtbl -> get_lngStreamState(This,pVal)

#define ITDT_Stream_get_lngN_Samples(This,pVal)	\
    (This)->lpVtbl -> get_lngN_Samples(This,pVal)

#define ITDT_Stream_get_lngTimeTick(This,pVal)	\
    (This)->lpVtbl -> get_lngTimeTick(This,pVal)

#define ITDT_Stream_get_strProgramVersion(This,pVal)	\
    (This)->lpVtbl -> get_strProgramVersion(This,pVal)

#define ITDT_Stream_get_lngBufferSize(This,pVal)	\
    (This)->lpVtbl -> get_lngBufferSize(This,pVal)

#define ITDT_Stream_put_lngBufferSize(This,newVal)	\
    (This)->lpVtbl -> put_lngBufferSize(This,newVal)

#define ITDT_Stream_get_fSampleRateHz(This,fVal)	\
    (This)->lpVtbl -> get_fSampleRateHz(This,fVal)

#define ITDT_Stream_get_strFilePath(This,pVal)	\
    (This)->lpVtbl -> get_strFilePath(This,pVal)

#define ITDT_Stream_put_strFilePath(This,newVal)	\
    (This)->lpVtbl -> put_strFilePath(This,newVal)

#define ITDT_Stream_get_blnConvertToInt16(This,pVal)	\
    (This)->lpVtbl -> get_blnConvertToInt16(This,pVal)

#define ITDT_Stream_put_blnConvertToInt16(This,newVal)	\
    (This)->lpVtbl -> put_blnConvertToInt16(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITDT_Stream_ConnectTDT_Server_Proxy( 
    ITDT_Stream __RPC_FAR * This);


void __RPC_STUB ITDT_Stream_ConnectTDT_Server_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITDT_Stream_DisconnectTDT_Server_Proxy( 
    ITDT_Stream __RPC_FAR * This);


void __RPC_STUB ITDT_Stream_DisconnectTDT_Server_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITDT_Stream_put_strServerName_Proxy( 
    ITDT_Stream __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ITDT_Stream_put_strServerName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITDT_Stream_get_strServerName_Proxy( 
    ITDT_Stream __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ITDT_Stream_get_strServerName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITDT_Stream_put_strDeviceName_Proxy( 
    ITDT_Stream __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ITDT_Stream_put_strDeviceName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITDT_Stream_get_strDeviceName_Proxy( 
    ITDT_Stream __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ITDT_Stream_get_strDeviceName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITDT_Stream_get_lngSystemMode_Proxy( 
    ITDT_Stream __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITDT_Stream_get_lngSystemMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITDT_Stream_get_strFileName_Proxy( 
    ITDT_Stream __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ITDT_Stream_get_strFileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITDT_Stream_put_strFileName_Proxy( 
    ITDT_Stream __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ITDT_Stream_put_strFileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITDT_Stream_get_lngBlockSize_Proxy( 
    ITDT_Stream __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITDT_Stream_get_lngBlockSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITDT_Stream_put_lngBlockSize_Proxy( 
    ITDT_Stream __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB ITDT_Stream_put_lngBlockSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITDT_Stream_SetArmedState_Proxy( 
    ITDT_Stream __RPC_FAR * This);


void __RPC_STUB ITDT_Stream_SetArmedState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITDT_Stream_SetIdleState_Proxy( 
    ITDT_Stream __RPC_FAR * This);


void __RPC_STUB ITDT_Stream_SetIdleState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITDT_Stream_get_lngStreamState_Proxy( 
    ITDT_Stream __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITDT_Stream_get_lngStreamState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITDT_Stream_get_lngN_Samples_Proxy( 
    ITDT_Stream __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITDT_Stream_get_lngN_Samples_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITDT_Stream_get_lngTimeTick_Proxy( 
    ITDT_Stream __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITDT_Stream_get_lngTimeTick_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITDT_Stream_get_strProgramVersion_Proxy( 
    ITDT_Stream __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ITDT_Stream_get_strProgramVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITDT_Stream_get_lngBufferSize_Proxy( 
    ITDT_Stream __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITDT_Stream_get_lngBufferSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITDT_Stream_put_lngBufferSize_Proxy( 
    ITDT_Stream __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB ITDT_Stream_put_lngBufferSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITDT_Stream_get_fSampleRateHz_Proxy( 
    ITDT_Stream __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *fVal);


void __RPC_STUB ITDT_Stream_get_fSampleRateHz_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITDT_Stream_get_strFilePath_Proxy( 
    ITDT_Stream __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ITDT_Stream_get_strFilePath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITDT_Stream_put_strFilePath_Proxy( 
    ITDT_Stream __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ITDT_Stream_put_strFilePath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITDT_Stream_get_blnConvertToInt16_Proxy( 
    ITDT_Stream __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITDT_Stream_get_blnConvertToInt16_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITDT_Stream_put_blnConvertToInt16_Proxy( 
    ITDT_Stream __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB ITDT_Stream_put_blnConvertToInt16_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITDT_Stream_INTERFACE_DEFINED__ */



#ifndef __CP_TDT_Stream_Lib_LIBRARY_DEFINED__
#define __CP_TDT_Stream_Lib_LIBRARY_DEFINED__

/* library CP_TDT_Stream_Lib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_CP_TDT_Stream_Lib;

EXTERN_C const CLSID CLSID_CP_TS_Class;

#ifdef __cplusplus

class DECLSPEC_UUID("ebd33030-ceb1-11d5-9c3e-0050da2a68c8")
CP_TS_Class;
#endif
#endif /* __CP_TDT_Stream_Lib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
