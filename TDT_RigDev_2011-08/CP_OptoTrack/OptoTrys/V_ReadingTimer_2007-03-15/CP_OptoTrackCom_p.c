/* this ALWAYS GENERATED file contains the proxy stub code */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Mar 07 21:21:54 2007
 */
/* Compiler settings for C:\users\rebrik\CP_OptoTrack\CP_OptoTrackCom.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 440
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif // __RPCPROXY_H_VERSION__


#include "CP_OptoTrackCom.h"

#define TYPE_FORMAT_STRING_SIZE   1025                              
#define PROC_FORMAT_STRING_SIZE   81                                

typedef struct _MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } MIDL_TYPE_FORMAT_STRING;

typedef struct _MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } MIDL_PROC_FORMAT_STRING;


extern const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString;
extern const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString;


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IDispatch, ver. 0.0,
   GUID={0x00020400,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IOptoTrack, ver. 0.0,
   GUID={0xebd33078,0xceb1,0x11d5,{0x9c,0x3e,0x00,0x50,0xda,0x2a,0x68,0xc8}} */


extern const MIDL_STUB_DESC Object_StubDesc;


#pragma code_seg(".orpc")

/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IOptoTrack_get_strProgramVersion_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(pVal)
        {
        MIDL_memset(
               pVal,
               0,
               sizeof( BSTR  ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      7);
        
        
        
        if(!pVal)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[0] );
            
            NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR * __RPC_FAR *)&pVal,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[30],
                                      (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[2],
                         ( void __RPC_FAR * )pVal);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IOptoTrack_get_strProgramVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    BSTR _M0;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    BSTR __RPC_FAR *pVal;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( BSTR __RPC_FAR * )pVal = 0;
    RpcTryFinally
        {
        pVal = &_M0;
        MIDL_memset(
               pVal,
               0,
               sizeof( BSTR  ));
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IOptoTrack*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_strProgramVersion((IOptoTrack *) ((CStdStubBuffer *)This)->pvServerObject,pVal);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8U + 11U;
        NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR *)pVal,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[30] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char __RPC_FAR *)pVal,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[30] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)pVal,
                        &__MIDL_TypeFormatString.Format[2] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IOptoTrack_ConnectTracker_Proxy( 
    IOptoTrack __RPC_FAR * This)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      8);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[6] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IOptoTrack_ConnectTracker_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    RpcTryFinally
        {
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IOptoTrack*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> ConnectTracker((IOptoTrack *) ((CStdStubBuffer *)This)->pvServerObject);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IOptoTrack_GetTrackerState_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pTracker)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      9);
        
        
        
        if(!pTracker)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[8] );
            
            *pTracker = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[40],
                         ( void __RPC_FAR * )pTracker);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IOptoTrack_GetTrackerState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    long _M1;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long __RPC_FAR *pTracker;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( long __RPC_FAR * )pTracker = 0;
    RpcTryFinally
        {
        pTracker = &_M1;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IOptoTrack*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> GetTrackerState((IOptoTrack *) ((CStdStubBuffer *)This)->pvServerObject,pTracker);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U + 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = *pTracker;
        
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IOptoTrack_DisconnectTracker_Proxy( 
    IOptoTrack __RPC_FAR * This)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      10);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[6] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IOptoTrack_DisconnectTracker_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    RpcTryFinally
        {
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IOptoTrack*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> DisconnectTracker((IOptoTrack *) ((CStdStubBuffer *)This)->pvServerObject);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IOptoTrack_get_dPredictionTimeMs_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      11);
        
        
        
        if(!pVal)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[14] );
            
            *pVal = *(( double __RPC_FAR * )_StubMsg.Buffer)++;
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[44],
                         ( void __RPC_FAR * )pVal);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IOptoTrack_get_dPredictionTimeMs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    double _M2;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    double __RPC_FAR *pVal;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( double __RPC_FAR * )pVal = 0;
    RpcTryFinally
        {
        pVal = &_M2;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IOptoTrack*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_dPredictionTimeMs((IOptoTrack *) ((CStdStubBuffer *)This)->pvServerObject,pVal);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8U + 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( double __RPC_FAR * )_StubMsg.Buffer)++ = *pVal;
        
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IOptoTrack_put_dPredictionTimeMs_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [in] */ double newVal)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      12);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 8U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( double __RPC_FAR * )_StubMsg.Buffer)++ = newVal;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[20] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IOptoTrack_put_dPredictionTimeMs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    double newVal;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[20] );
        
        newVal = *(( double __RPC_FAR * )_StubMsg.Buffer)++;
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IOptoTrack*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_dPredictionTimeMs((IOptoTrack *) ((CStdStubBuffer *)This)->pvServerObject,newVal);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IOptoTrack_ResetBuffer_Proxy( 
    IOptoTrack __RPC_FAR * This)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      13);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[6] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IOptoTrack_ResetBuffer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    RpcTryFinally
        {
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IOptoTrack*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> ResetBuffer((IOptoTrack *) ((CStdStubBuffer *)This)->pvServerObject);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IOptoTrack_GetSensors_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [retval][out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *padSensors)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      14);
        
        
        
        if(!padSensors)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[24] );
            
            NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR * __RPC_FAR *)&padSensors,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[982],
                                      (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[48],
                         ( void __RPC_FAR * )padSensors);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IOptoTrack_GetSensors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    SAFEARRAY __RPC_FAR * __RPC_FAR *padSensors;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( SAFEARRAY __RPC_FAR * __RPC_FAR * )padSensors = 0;
    RpcTryFinally
        {
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IOptoTrack*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> GetSensors((IOptoTrack *) ((CStdStubBuffer *)This)->pvServerObject,padSensors);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 0U + 11U;
        NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR *)padSensors,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[982] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char __RPC_FAR *)padSensors,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[982] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)padSensors,
                        &__MIDL_TypeFormatString.Format[48] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IOptoTrack_SetSensors_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [in] */ SAFEARRAY __RPC_FAR * adMatrix)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      15);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR *)adMatrix,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1000] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char __RPC_FAR *)adMatrix,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1000] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[30] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IOptoTrack_SetSensors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    SAFEARRAY __RPC_FAR * adMatrix;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[30] );
        
        NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&adMatrix,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1000],
                                  (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IOptoTrack*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> SetSensors((IOptoTrack *) ((CStdStubBuffer *)This)->pvServerObject,adMatrix);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IOptoTrack_get_lngBufferSize_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pnItems)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      16);
        
        
        
        if(!pnItems)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[8] );
            
            *pnItems = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[40],
                         ( void __RPC_FAR * )pnItems);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IOptoTrack_get_lngBufferSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    long _M3;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long __RPC_FAR *pnItems;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( long __RPC_FAR * )pnItems = 0;
    RpcTryFinally
        {
        pnItems = &_M3;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IOptoTrack*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_lngBufferSize((IOptoTrack *) ((CStdStubBuffer *)This)->pvServerObject,pnItems);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U + 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = *pnItems;
        
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IOptoTrack_get_lngLatestDataIndex_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plIdx)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      17);
        
        
        
        if(!plIdx)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[8] );
            
            *plIdx = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[40],
                         ( void __RPC_FAR * )plIdx);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IOptoTrack_get_lngLatestDataIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    long _M4;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long __RPC_FAR *plIdx;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( long __RPC_FAR * )plIdx = 0;
    RpcTryFinally
        {
        plIdx = &_M4;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IOptoTrack*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_lngLatestDataIndex((IOptoTrack *) ((CStdStubBuffer *)This)->pvServerObject,plIdx);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U + 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = *plIdx;
        
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IOptoTrack_GetSensorLatest_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [in] */ long lngSensorIdx,
    /* [out] */ long __RPC_FAR *plIdx,
    /* [out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *padData)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      18);
        
        
        
        if(!plIdx)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        if(!padData)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 4U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( long __RPC_FAR * )_StubMsg.Buffer)++ = lngSensorIdx;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[36] );
            
            *plIdx = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
            
            NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR * __RPC_FAR *)&padData,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1014],
                                      (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[40],
                         ( void __RPC_FAR * )plIdx);
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[1010],
                         ( void __RPC_FAR * )padData);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IOptoTrack_GetSensorLatest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    long _M5;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long lngSensorIdx;
    SAFEARRAY __RPC_FAR * __RPC_FAR *padData;
    long __RPC_FAR *plIdx;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( long __RPC_FAR * )plIdx = 0;
    ( SAFEARRAY __RPC_FAR * __RPC_FAR * )padData = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[36] );
        
        lngSensorIdx = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        plIdx = &_M5;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IOptoTrack*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> GetSensorLatest(
                   (IOptoTrack *) ((CStdStubBuffer *)This)->pvServerObject,
                   lngSensorIdx,
                   plIdx,
                   padData);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U + 0U + 11U;
        NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR *)padData,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1014] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = *plIdx;
        
        NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char __RPC_FAR *)padData,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1014] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)padData,
                        &__MIDL_TypeFormatString.Format[1010] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IOptoTrack_GetSensorBuffer_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [in] */ long lngSensorIdx,
    /* [in] */ long lngIdx,
    /* [in] */ long nItems,
    /* [out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *padData)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      19);
        
        
        
        if(!padData)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 4U + 4U + 4U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( long __RPC_FAR * )_StubMsg.Buffer)++ = lngSensorIdx;
            
            *(( long __RPC_FAR * )_StubMsg.Buffer)++ = lngIdx;
            
            *(( long __RPC_FAR * )_StubMsg.Buffer)++ = nItems;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[48] );
            
            NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR * __RPC_FAR *)&padData,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1014],
                                      (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[1010],
                         ( void __RPC_FAR * )padData);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IOptoTrack_GetSensorBuffer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long lngIdx;
    long lngSensorIdx;
    long nItems;
    SAFEARRAY __RPC_FAR * __RPC_FAR *padData;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( SAFEARRAY __RPC_FAR * __RPC_FAR * )padData = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[48] );
        
        lngSensorIdx = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        lngIdx = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        nItems = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IOptoTrack*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> GetSensorBuffer(
                   (IOptoTrack *) ((CStdStubBuffer *)This)->pvServerObject,
                   lngSensorIdx,
                   lngIdx,
                   nItems,
                   padData);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 0U + 11U;
        NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR *)padData,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1014] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char __RPC_FAR *)padData,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1014] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)padData,
                        &__MIDL_TypeFormatString.Format[1010] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IOptoTrack_GetAllSensorsLatest_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *plIdx,
    /* [out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *padData)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      20);
        
        
        
        if(!plIdx)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        if(!padData)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[60] );
            
            *plIdx = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
            
            NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR * __RPC_FAR *)&padData,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1014],
                                      (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[40],
                         ( void __RPC_FAR * )plIdx);
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[1010],
                         ( void __RPC_FAR * )padData);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IOptoTrack_GetAllSensorsLatest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    long _M6;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    SAFEARRAY __RPC_FAR * __RPC_FAR *padData;
    long __RPC_FAR *plIdx;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( long __RPC_FAR * )plIdx = 0;
    ( SAFEARRAY __RPC_FAR * __RPC_FAR * )padData = 0;
    RpcTryFinally
        {
        plIdx = &_M6;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IOptoTrack*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> GetAllSensorsLatest(
                       (IOptoTrack *) ((CStdStubBuffer *)This)->pvServerObject,
                       plIdx,
                       padData);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U + 0U + 11U;
        NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR *)padData,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1014] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = *plIdx;
        
        NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char __RPC_FAR *)padData,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1014] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)padData,
                        &__MIDL_TypeFormatString.Format[1010] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IOptoTrack_GetAllSensorsBuffer_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [in] */ long lngIdx,
    /* [in] */ long nItems,
    /* [out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *padData)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      21);
        
        
        
        if(!padData)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 4U + 4U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( long __RPC_FAR * )_StubMsg.Buffer)++ = lngIdx;
            
            *(( long __RPC_FAR * )_StubMsg.Buffer)++ = nItems;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[70] );
            
            NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR * __RPC_FAR *)&padData,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1014],
                                      (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[1010],
                         ( void __RPC_FAR * )padData);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IOptoTrack_GetAllSensorsBuffer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long lngIdx;
    long nItems;
    SAFEARRAY __RPC_FAR * __RPC_FAR *padData;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( SAFEARRAY __RPC_FAR * __RPC_FAR * )padData = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[70] );
        
        lngIdx = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        nItems = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IOptoTrack*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> GetAllSensorsBuffer(
                       (IOptoTrack *) ((CStdStubBuffer *)This)->pvServerObject,
                       lngIdx,
                       nItems,
                       padData);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 0U + 11U;
        NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR *)padData,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1014] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char __RPC_FAR *)padData,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1014] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)padData,
                        &__MIDL_TypeFormatString.Format[1010] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[2];

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    __MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x20000, /* Ndr library version */
    0,
    0x50100a4, /* MIDL Version 5.1.164 */
    0,
    UserMarshalRoutines,
    0,  /* notify & notify_flag routine table */
    1,  /* Flags */
    0,  /* Reserved3 */
    0,  /* Reserved4 */
    0   /* Reserved5 */
    };

CINTERFACE_PROXY_VTABLE(22) _IOptoTrackProxyVtbl = 
{
    &IID_IOptoTrack,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch_GetTypeInfoCount_Proxy */ ,
    0 /* IDispatch_GetTypeInfo_Proxy */ ,
    0 /* IDispatch_GetIDsOfNames_Proxy */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    IOptoTrack_get_strProgramVersion_Proxy ,
    IOptoTrack_ConnectTracker_Proxy ,
    IOptoTrack_GetTrackerState_Proxy ,
    IOptoTrack_DisconnectTracker_Proxy ,
    IOptoTrack_get_dPredictionTimeMs_Proxy ,
    IOptoTrack_put_dPredictionTimeMs_Proxy ,
    IOptoTrack_ResetBuffer_Proxy ,
    IOptoTrack_GetSensors_Proxy ,
    IOptoTrack_SetSensors_Proxy ,
    IOptoTrack_get_lngBufferSize_Proxy ,
    IOptoTrack_get_lngLatestDataIndex_Proxy ,
    IOptoTrack_GetSensorLatest_Proxy ,
    IOptoTrack_GetSensorBuffer_Proxy ,
    IOptoTrack_GetAllSensorsLatest_Proxy ,
    IOptoTrack_GetAllSensorsBuffer_Proxy
};


static const PRPC_STUB_FUNCTION IOptoTrack_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    IOptoTrack_get_strProgramVersion_Stub,
    IOptoTrack_ConnectTracker_Stub,
    IOptoTrack_GetTrackerState_Stub,
    IOptoTrack_DisconnectTracker_Stub,
    IOptoTrack_get_dPredictionTimeMs_Stub,
    IOptoTrack_put_dPredictionTimeMs_Stub,
    IOptoTrack_ResetBuffer_Stub,
    IOptoTrack_GetSensors_Stub,
    IOptoTrack_SetSensors_Stub,
    IOptoTrack_get_lngBufferSize_Stub,
    IOptoTrack_get_lngLatestDataIndex_Stub,
    IOptoTrack_GetSensorLatest_Stub,
    IOptoTrack_GetSensorBuffer_Stub,
    IOptoTrack_GetAllSensorsLatest_Stub,
    IOptoTrack_GetAllSensorsBuffer_Stub
};

CInterfaceStubVtbl _IOptoTrackStubVtbl =
{
    &IID_IOptoTrack,
    0,
    22,
    &IOptoTrack_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};

#pragma data_seg(".rdata")

static const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[2] = 
        {
            
            {
            BSTR_UserSize
            ,BSTR_UserMarshal
            ,BSTR_UserUnmarshal
            ,BSTR_UserFree
            },
            {
            LPSAFEARRAY_UserSize
            ,LPSAFEARRAY_UserMarshal
            ,LPSAFEARRAY_UserUnmarshal
            ,LPSAFEARRAY_UserFree
            }

        };


#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT40_OR_LATER)
#error You need a Windows NT 4.0 or later to run this stub because it uses these features:
#error   [wire_marshal] or [user_marshal] attribute.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will die there with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {
			
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/*  2 */	NdrFcShort( 0x2 ),	/* Type Offset=2 */
/*  4 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/*  6 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/*  8 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 10 */	NdrFcShort( 0x28 ),	/* Type Offset=40 */
/* 12 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 14 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 16 */	NdrFcShort( 0x2c ),	/* Type Offset=44 */
/* 18 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 20 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0xc,		/* FC_DOUBLE */
/* 22 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 24 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 26 */	NdrFcShort( 0x30 ),	/* Type Offset=48 */
/* 28 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 30 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x0,		/* x86, MIPS & PPC Stack size = 0 */
#else
			0x0,		/* Alpha Stack size = 0 */
#endif
/* 32 */	NdrFcShort( 0x3e8 ),	/* Type Offset=1000 */
/* 34 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 36 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 38 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 40 */	NdrFcShort( 0x28 ),	/* Type Offset=40 */
/* 42 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 44 */	NdrFcShort( 0x3f2 ),	/* Type Offset=1010 */
/* 46 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 48 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 50 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 52 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 54 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 56 */	NdrFcShort( 0x3f2 ),	/* Type Offset=1010 */
/* 58 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 60 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 62 */	NdrFcShort( 0x28 ),	/* Type Offset=40 */
/* 64 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 66 */	NdrFcShort( 0x3f2 ),	/* Type Offset=1010 */
/* 68 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 70 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 72 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 74 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 76 */	NdrFcShort( 0x3f2 ),	/* Type Offset=1010 */
/* 78 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */

			0x0
        }
    };

static const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/*  4 */	NdrFcShort( 0x1a ),	/* Offset= 26 (30) */
/*  6 */	
			0x13, 0x0,	/* FC_OP */
/*  8 */	NdrFcShort( 0xc ),	/* Offset= 12 (20) */
/* 10 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 12 */	NdrFcShort( 0x2 ),	/* 2 */
/* 14 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 16 */	NdrFcShort( 0xfffc ),	/* -4 */
/* 18 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 20 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 22 */	NdrFcShort( 0x8 ),	/* 8 */
/* 24 */	NdrFcShort( 0xfffffff2 ),	/* Offset= -14 (10) */
/* 26 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 28 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 30 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 32 */	NdrFcShort( 0x0 ),	/* 0 */
/* 34 */	NdrFcShort( 0x4 ),	/* 4 */
/* 36 */	NdrFcShort( 0x0 ),	/* 0 */
/* 38 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (6) */
/* 40 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 42 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 44 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 46 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 48 */	
			0x11, 0x0,	/* FC_RP */
/* 50 */	NdrFcShort( 0x3a4 ),	/* Offset= 932 (982) */
/* 52 */	
			0x13, 0x10,	/* FC_OP */
/* 54 */	NdrFcShort( 0x2 ),	/* Offset= 2 (56) */
/* 56 */	
			0x13, 0x0,	/* FC_OP */
/* 58 */	NdrFcShort( 0x38a ),	/* Offset= 906 (964) */
/* 60 */	
			0x2a,		/* FC_ENCAPSULATED_UNION */
			0x49,		/* 73 */
/* 62 */	NdrFcShort( 0x18 ),	/* 24 */
/* 64 */	NdrFcShort( 0xa ),	/* 10 */
/* 66 */	NdrFcLong( 0x8 ),	/* 8 */
/* 70 */	NdrFcShort( 0x58 ),	/* Offset= 88 (158) */
/* 72 */	NdrFcLong( 0xd ),	/* 13 */
/* 76 */	NdrFcShort( 0x8a ),	/* Offset= 138 (214) */
/* 78 */	NdrFcLong( 0x9 ),	/* 9 */
/* 82 */	NdrFcShort( 0xb8 ),	/* Offset= 184 (266) */
/* 84 */	NdrFcLong( 0xc ),	/* 12 */
/* 88 */	NdrFcShort( 0x27a ),	/* Offset= 634 (722) */
/* 90 */	NdrFcLong( 0x24 ),	/* 36 */
/* 94 */	NdrFcShort( 0x2a2 ),	/* Offset= 674 (768) */
/* 96 */	NdrFcLong( 0x800d ),	/* 32781 */
/* 100 */	NdrFcShort( 0x2be ),	/* Offset= 702 (802) */
/* 102 */	NdrFcLong( 0x10 ),	/* 16 */
/* 106 */	NdrFcShort( 0x2d6 ),	/* Offset= 726 (832) */
/* 108 */	NdrFcLong( 0x2 ),	/* 2 */
/* 112 */	NdrFcShort( 0x2ee ),	/* Offset= 750 (862) */
/* 114 */	NdrFcLong( 0x3 ),	/* 3 */
/* 118 */	NdrFcShort( 0x306 ),	/* Offset= 774 (892) */
/* 120 */	NdrFcLong( 0x14 ),	/* 20 */
/* 124 */	NdrFcShort( 0x31e ),	/* Offset= 798 (922) */
/* 126 */	NdrFcShort( 0xffffffff ),	/* Offset= -1 (125) */
/* 128 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 130 */	NdrFcShort( 0x4 ),	/* 4 */
/* 132 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 134 */	NdrFcShort( 0x0 ),	/* 0 */
/* 136 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 138 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 140 */	NdrFcShort( 0x4 ),	/* 4 */
/* 142 */	NdrFcShort( 0x0 ),	/* 0 */
/* 144 */	NdrFcShort( 0x1 ),	/* 1 */
/* 146 */	NdrFcShort( 0x0 ),	/* 0 */
/* 148 */	NdrFcShort( 0x0 ),	/* 0 */
/* 150 */	0x13, 0x0,	/* FC_OP */
/* 152 */	NdrFcShort( 0xffffff7c ),	/* Offset= -132 (20) */
/* 154 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 156 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 158 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 160 */	NdrFcShort( 0x8 ),	/* 8 */
/* 162 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 164 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 166 */	NdrFcShort( 0x4 ),	/* 4 */
/* 168 */	NdrFcShort( 0x4 ),	/* 4 */
/* 170 */	0x11, 0x0,	/* FC_RP */
/* 172 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (128) */
/* 174 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 176 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 178 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 180 */	NdrFcLong( 0x0 ),	/* 0 */
/* 184 */	NdrFcShort( 0x0 ),	/* 0 */
/* 186 */	NdrFcShort( 0x0 ),	/* 0 */
/* 188 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 190 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 192 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 194 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 196 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 198 */	NdrFcShort( 0x0 ),	/* 0 */
/* 200 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 202 */	NdrFcShort( 0x0 ),	/* 0 */
/* 204 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 208 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 210 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (178) */
/* 212 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 214 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 216 */	NdrFcShort( 0x8 ),	/* 8 */
/* 218 */	NdrFcShort( 0x0 ),	/* 0 */
/* 220 */	NdrFcShort( 0x6 ),	/* Offset= 6 (226) */
/* 222 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 224 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 226 */	
			0x11, 0x0,	/* FC_RP */
/* 228 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (196) */
/* 230 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 232 */	NdrFcLong( 0x20400 ),	/* 132096 */
/* 236 */	NdrFcShort( 0x0 ),	/* 0 */
/* 238 */	NdrFcShort( 0x0 ),	/* 0 */
/* 240 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 242 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 244 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 246 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 248 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 250 */	NdrFcShort( 0x0 ),	/* 0 */
/* 252 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 254 */	NdrFcShort( 0x0 ),	/* 0 */
/* 256 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 260 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 262 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (230) */
/* 264 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 266 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 268 */	NdrFcShort( 0x8 ),	/* 8 */
/* 270 */	NdrFcShort( 0x0 ),	/* 0 */
/* 272 */	NdrFcShort( 0x6 ),	/* Offset= 6 (278) */
/* 274 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 276 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 278 */	
			0x11, 0x0,	/* FC_RP */
/* 280 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (248) */
/* 282 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 284 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 286 */	NdrFcShort( 0xfff8 ),	/* -8 */
/* 288 */	NdrFcShort( 0x2 ),	/* Offset= 2 (290) */
/* 290 */	NdrFcShort( 0x10 ),	/* 16 */
/* 292 */	NdrFcShort( 0x2b ),	/* 43 */
/* 294 */	NdrFcLong( 0x3 ),	/* 3 */
/* 298 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 300 */	NdrFcLong( 0x11 ),	/* 17 */
/* 304 */	NdrFcShort( 0x8002 ),	/* Simple arm type: FC_CHAR */
/* 306 */	NdrFcLong( 0x2 ),	/* 2 */
/* 310 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 312 */	NdrFcLong( 0x4 ),	/* 4 */
/* 316 */	NdrFcShort( 0x800a ),	/* Simple arm type: FC_FLOAT */
/* 318 */	NdrFcLong( 0x5 ),	/* 5 */
/* 322 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 324 */	NdrFcLong( 0xb ),	/* 11 */
/* 328 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 330 */	NdrFcLong( 0xa ),	/* 10 */
/* 334 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 336 */	NdrFcLong( 0x6 ),	/* 6 */
/* 340 */	NdrFcShort( 0xd6 ),	/* Offset= 214 (554) */
/* 342 */	NdrFcLong( 0x7 ),	/* 7 */
/* 346 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 348 */	NdrFcLong( 0x8 ),	/* 8 */
/* 352 */	NdrFcShort( 0xfffffea6 ),	/* Offset= -346 (6) */
/* 354 */	NdrFcLong( 0xd ),	/* 13 */
/* 358 */	NdrFcShort( 0xffffff4c ),	/* Offset= -180 (178) */
/* 360 */	NdrFcLong( 0x9 ),	/* 9 */
/* 364 */	NdrFcShort( 0xffffff7a ),	/* Offset= -134 (230) */
/* 366 */	NdrFcLong( 0x2000 ),	/* 8192 */
/* 370 */	NdrFcShort( 0xbe ),	/* Offset= 190 (560) */
/* 372 */	NdrFcLong( 0x24 ),	/* 36 */
/* 376 */	NdrFcShort( 0xbc ),	/* Offset= 188 (564) */
/* 378 */	NdrFcLong( 0x4024 ),	/* 16420 */
/* 382 */	NdrFcShort( 0xb6 ),	/* Offset= 182 (564) */
/* 384 */	NdrFcLong( 0x4011 ),	/* 16401 */
/* 388 */	NdrFcShort( 0xe4 ),	/* Offset= 228 (616) */
/* 390 */	NdrFcLong( 0x4002 ),	/* 16386 */
/* 394 */	NdrFcShort( 0xe2 ),	/* Offset= 226 (620) */
/* 396 */	NdrFcLong( 0x4003 ),	/* 16387 */
/* 400 */	NdrFcShort( 0xe0 ),	/* Offset= 224 (624) */
/* 402 */	NdrFcLong( 0x4004 ),	/* 16388 */
/* 406 */	NdrFcShort( 0xde ),	/* Offset= 222 (628) */
/* 408 */	NdrFcLong( 0x4005 ),	/* 16389 */
/* 412 */	NdrFcShort( 0xdc ),	/* Offset= 220 (632) */
/* 414 */	NdrFcLong( 0x400b ),	/* 16395 */
/* 418 */	NdrFcShort( 0xca ),	/* Offset= 202 (620) */
/* 420 */	NdrFcLong( 0x400a ),	/* 16394 */
/* 424 */	NdrFcShort( 0xc8 ),	/* Offset= 200 (624) */
/* 426 */	NdrFcLong( 0x4006 ),	/* 16390 */
/* 430 */	NdrFcShort( 0xce ),	/* Offset= 206 (636) */
/* 432 */	NdrFcLong( 0x4007 ),	/* 16391 */
/* 436 */	NdrFcShort( 0xc4 ),	/* Offset= 196 (632) */
/* 438 */	NdrFcLong( 0x4008 ),	/* 16392 */
/* 442 */	NdrFcShort( 0xc6 ),	/* Offset= 198 (640) */
/* 444 */	NdrFcLong( 0x400d ),	/* 16397 */
/* 448 */	NdrFcShort( 0xc4 ),	/* Offset= 196 (644) */
/* 450 */	NdrFcLong( 0x4009 ),	/* 16393 */
/* 454 */	NdrFcShort( 0xc2 ),	/* Offset= 194 (648) */
/* 456 */	NdrFcLong( 0x6000 ),	/* 24576 */
/* 460 */	NdrFcShort( 0xc0 ),	/* Offset= 192 (652) */
/* 462 */	NdrFcLong( 0x400c ),	/* 16396 */
/* 466 */	NdrFcShort( 0xba ),	/* Offset= 186 (652) */
/* 468 */	NdrFcLong( 0x10 ),	/* 16 */
/* 472 */	NdrFcShort( 0x8002 ),	/* Simple arm type: FC_CHAR */
/* 474 */	NdrFcLong( 0x12 ),	/* 18 */
/* 478 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 480 */	NdrFcLong( 0x13 ),	/* 19 */
/* 484 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 486 */	NdrFcLong( 0x16 ),	/* 22 */
/* 490 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 492 */	NdrFcLong( 0x17 ),	/* 23 */
/* 496 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 498 */	NdrFcLong( 0xe ),	/* 14 */
/* 502 */	NdrFcShort( 0x9a ),	/* Offset= 154 (656) */
/* 504 */	NdrFcLong( 0x400e ),	/* 16398 */
/* 508 */	NdrFcShort( 0xa0 ),	/* Offset= 160 (668) */
/* 510 */	NdrFcLong( 0x4010 ),	/* 16400 */
/* 514 */	NdrFcShort( 0x66 ),	/* Offset= 102 (616) */
/* 516 */	NdrFcLong( 0x4012 ),	/* 16402 */
/* 520 */	NdrFcShort( 0x64 ),	/* Offset= 100 (620) */
/* 522 */	NdrFcLong( 0x4013 ),	/* 16403 */
/* 526 */	NdrFcShort( 0x62 ),	/* Offset= 98 (624) */
/* 528 */	NdrFcLong( 0x4016 ),	/* 16406 */
/* 532 */	NdrFcShort( 0x5c ),	/* Offset= 92 (624) */
/* 534 */	NdrFcLong( 0x4017 ),	/* 16407 */
/* 538 */	NdrFcShort( 0x56 ),	/* Offset= 86 (624) */
/* 540 */	NdrFcLong( 0x0 ),	/* 0 */
/* 544 */	NdrFcShort( 0x0 ),	/* Offset= 0 (544) */
/* 546 */	NdrFcLong( 0x1 ),	/* 1 */
/* 550 */	NdrFcShort( 0x0 ),	/* Offset= 0 (550) */
/* 552 */	NdrFcShort( 0xffffffff ),	/* Offset= -1 (551) */
/* 554 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 556 */	NdrFcShort( 0x8 ),	/* 8 */
/* 558 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 560 */	
			0x13, 0x0,	/* FC_OP */
/* 562 */	NdrFcShort( 0x192 ),	/* Offset= 402 (964) */
/* 564 */	
			0x13, 0x0,	/* FC_OP */
/* 566 */	NdrFcShort( 0x1e ),	/* Offset= 30 (596) */
/* 568 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 570 */	NdrFcLong( 0x2f ),	/* 47 */
/* 574 */	NdrFcShort( 0x0 ),	/* 0 */
/* 576 */	NdrFcShort( 0x0 ),	/* 0 */
/* 578 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 580 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 582 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 584 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 586 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 588 */	NdrFcShort( 0x1 ),	/* 1 */
/* 590 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 592 */	NdrFcShort( 0x4 ),	/* 4 */
/* 594 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 596 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 598 */	NdrFcShort( 0x10 ),	/* 16 */
/* 600 */	NdrFcShort( 0x0 ),	/* 0 */
/* 602 */	NdrFcShort( 0xa ),	/* Offset= 10 (612) */
/* 604 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 606 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 608 */	NdrFcShort( 0xffffffd8 ),	/* Offset= -40 (568) */
/* 610 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 612 */	
			0x13, 0x0,	/* FC_OP */
/* 614 */	NdrFcShort( 0xffffffe4 ),	/* Offset= -28 (586) */
/* 616 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 618 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 620 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 622 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 624 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 626 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 628 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 630 */	0xa,		/* FC_FLOAT */
			0x5c,		/* FC_PAD */
/* 632 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 634 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 636 */	
			0x13, 0x0,	/* FC_OP */
/* 638 */	NdrFcShort( 0xffffffac ),	/* Offset= -84 (554) */
/* 640 */	
			0x13, 0x10,	/* FC_OP */
/* 642 */	NdrFcShort( 0xfffffd84 ),	/* Offset= -636 (6) */
/* 644 */	
			0x13, 0x10,	/* FC_OP */
/* 646 */	NdrFcShort( 0xfffffe2c ),	/* Offset= -468 (178) */
/* 648 */	
			0x13, 0x10,	/* FC_OP */
/* 650 */	NdrFcShort( 0xfffffe5c ),	/* Offset= -420 (230) */
/* 652 */	
			0x13, 0x10,	/* FC_OP */
/* 654 */	NdrFcShort( 0xffffffa2 ),	/* Offset= -94 (560) */
/* 656 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 658 */	NdrFcShort( 0x10 ),	/* 16 */
/* 660 */	0x6,		/* FC_SHORT */
			0x2,		/* FC_CHAR */
/* 662 */	0x2,		/* FC_CHAR */
			0x38,		/* FC_ALIGNM4 */
/* 664 */	0x8,		/* FC_LONG */
			0x39,		/* FC_ALIGNM8 */
/* 666 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 668 */	
			0x13, 0x0,	/* FC_OP */
/* 670 */	NdrFcShort( 0xfffffff2 ),	/* Offset= -14 (656) */
/* 672 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 674 */	NdrFcShort( 0x20 ),	/* 32 */
/* 676 */	NdrFcShort( 0x0 ),	/* 0 */
/* 678 */	NdrFcShort( 0x0 ),	/* Offset= 0 (678) */
/* 680 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 682 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 684 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 686 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 688 */	NdrFcShort( 0xfffffe6a ),	/* Offset= -406 (282) */
/* 690 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 692 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 694 */	NdrFcShort( 0x4 ),	/* 4 */
/* 696 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 698 */	NdrFcShort( 0x0 ),	/* 0 */
/* 700 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 702 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 704 */	NdrFcShort( 0x4 ),	/* 4 */
/* 706 */	NdrFcShort( 0x0 ),	/* 0 */
/* 708 */	NdrFcShort( 0x1 ),	/* 1 */
/* 710 */	NdrFcShort( 0x0 ),	/* 0 */
/* 712 */	NdrFcShort( 0x0 ),	/* 0 */
/* 714 */	0x13, 0x0,	/* FC_OP */
/* 716 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (672) */
/* 718 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 720 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 722 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 724 */	NdrFcShort( 0x8 ),	/* 8 */
/* 726 */	NdrFcShort( 0x0 ),	/* 0 */
/* 728 */	NdrFcShort( 0x6 ),	/* Offset= 6 (734) */
/* 730 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 732 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 734 */	
			0x11, 0x0,	/* FC_RP */
/* 736 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (692) */
/* 738 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 740 */	NdrFcShort( 0x4 ),	/* 4 */
/* 742 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 744 */	NdrFcShort( 0x0 ),	/* 0 */
/* 746 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 748 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 750 */	NdrFcShort( 0x4 ),	/* 4 */
/* 752 */	NdrFcShort( 0x0 ),	/* 0 */
/* 754 */	NdrFcShort( 0x1 ),	/* 1 */
/* 756 */	NdrFcShort( 0x0 ),	/* 0 */
/* 758 */	NdrFcShort( 0x0 ),	/* 0 */
/* 760 */	0x13, 0x0,	/* FC_OP */
/* 762 */	NdrFcShort( 0xffffff5a ),	/* Offset= -166 (596) */
/* 764 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 766 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 768 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 770 */	NdrFcShort( 0x8 ),	/* 8 */
/* 772 */	NdrFcShort( 0x0 ),	/* 0 */
/* 774 */	NdrFcShort( 0x6 ),	/* Offset= 6 (780) */
/* 776 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 778 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 780 */	
			0x11, 0x0,	/* FC_RP */
/* 782 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (738) */
/* 784 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 786 */	NdrFcShort( 0x8 ),	/* 8 */
/* 788 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/* 790 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 792 */	NdrFcShort( 0x10 ),	/* 16 */
/* 794 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 796 */	0x6,		/* FC_SHORT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 798 */	0x0,		/* 0 */
			NdrFcShort( 0xfffffff1 ),	/* Offset= -15 (784) */
			0x5b,		/* FC_END */
/* 802 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 804 */	NdrFcShort( 0x18 ),	/* 24 */
/* 806 */	NdrFcShort( 0x0 ),	/* 0 */
/* 808 */	NdrFcShort( 0xa ),	/* Offset= 10 (818) */
/* 810 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 812 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 814 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (790) */
/* 816 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 818 */	
			0x11, 0x0,	/* FC_RP */
/* 820 */	NdrFcShort( 0xfffffd90 ),	/* Offset= -624 (196) */
/* 822 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 824 */	NdrFcShort( 0x1 ),	/* 1 */
/* 826 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 828 */	NdrFcShort( 0x0 ),	/* 0 */
/* 830 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 832 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 834 */	NdrFcShort( 0x8 ),	/* 8 */
/* 836 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 838 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 840 */	NdrFcShort( 0x4 ),	/* 4 */
/* 842 */	NdrFcShort( 0x4 ),	/* 4 */
/* 844 */	0x13, 0x0,	/* FC_OP */
/* 846 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (822) */
/* 848 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 850 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 852 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 854 */	NdrFcShort( 0x2 ),	/* 2 */
/* 856 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 858 */	NdrFcShort( 0x0 ),	/* 0 */
/* 860 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 862 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 864 */	NdrFcShort( 0x8 ),	/* 8 */
/* 866 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 868 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 870 */	NdrFcShort( 0x4 ),	/* 4 */
/* 872 */	NdrFcShort( 0x4 ),	/* 4 */
/* 874 */	0x13, 0x0,	/* FC_OP */
/* 876 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (852) */
/* 878 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 880 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 882 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 884 */	NdrFcShort( 0x4 ),	/* 4 */
/* 886 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 888 */	NdrFcShort( 0x0 ),	/* 0 */
/* 890 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 892 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 894 */	NdrFcShort( 0x8 ),	/* 8 */
/* 896 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 898 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 900 */	NdrFcShort( 0x4 ),	/* 4 */
/* 902 */	NdrFcShort( 0x4 ),	/* 4 */
/* 904 */	0x13, 0x0,	/* FC_OP */
/* 906 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (882) */
/* 908 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 910 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 912 */	
			0x1b,		/* FC_CARRAY */
			0x7,		/* 7 */
/* 914 */	NdrFcShort( 0x8 ),	/* 8 */
/* 916 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 918 */	NdrFcShort( 0x0 ),	/* 0 */
/* 920 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 922 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 924 */	NdrFcShort( 0x8 ),	/* 8 */
/* 926 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 928 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 930 */	NdrFcShort( 0x4 ),	/* 4 */
/* 932 */	NdrFcShort( 0x4 ),	/* 4 */
/* 934 */	0x13, 0x0,	/* FC_OP */
/* 936 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (912) */
/* 938 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 940 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 942 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 944 */	NdrFcShort( 0x8 ),	/* 8 */
/* 946 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 948 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 950 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 952 */	NdrFcShort( 0x8 ),	/* 8 */
/* 954 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 956 */	NdrFcShort( 0xffd8 ),	/* -40 */
/* 958 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 960 */	NdrFcShort( 0xffffffee ),	/* Offset= -18 (942) */
/* 962 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 964 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 966 */	NdrFcShort( 0x28 ),	/* 40 */
/* 968 */	NdrFcShort( 0xffffffee ),	/* Offset= -18 (950) */
/* 970 */	NdrFcShort( 0x0 ),	/* Offset= 0 (970) */
/* 972 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 974 */	0x38,		/* FC_ALIGNM4 */
			0x8,		/* FC_LONG */
/* 976 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 978 */	0x0,		/* 0 */
			NdrFcShort( 0xfffffc69 ),	/* Offset= -919 (60) */
			0x5b,		/* FC_END */
/* 982 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 984 */	NdrFcShort( 0x1 ),	/* 1 */
/* 986 */	NdrFcShort( 0x4 ),	/* 4 */
/* 988 */	NdrFcShort( 0x0 ),	/* 0 */
/* 990 */	NdrFcShort( 0xfffffc56 ),	/* Offset= -938 (52) */
/* 992 */	
			0x12, 0x10,	/* FC_UP */
/* 994 */	NdrFcShort( 0x2 ),	/* Offset= 2 (996) */
/* 996 */	
			0x12, 0x0,	/* FC_UP */
/* 998 */	NdrFcShort( 0xffffffde ),	/* Offset= -34 (964) */
/* 1000 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1002 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1004 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1006 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1008 */	NdrFcShort( 0xfffffff0 ),	/* Offset= -16 (992) */
/* 1010 */	
			0x11, 0x0,	/* FC_RP */
/* 1012 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1014) */
/* 1014 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1016 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1018 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1020 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1022 */	NdrFcShort( 0xfffffe8e ),	/* Offset= -370 (652) */

			0x0
        }
    };

const CInterfaceProxyVtbl * _CP_OptoTrackCom_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IOptoTrackProxyVtbl,
    0
};

const CInterfaceStubVtbl * _CP_OptoTrackCom_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IOptoTrackStubVtbl,
    0
};

PCInterfaceName const _CP_OptoTrackCom_InterfaceNamesList[] = 
{
    "IOptoTrack",
    0
};

const IID *  _CP_OptoTrackCom_BaseIIDList[] = 
{
    &IID_IDispatch,
    0
};


#define _CP_OptoTrackCom_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _CP_OptoTrackCom, pIID, n)

int __stdcall _CP_OptoTrackCom_IID_Lookup( const IID * pIID, int * pIndex )
{
    
    if(!_CP_OptoTrackCom_CHECK_IID(0))
        {
        *pIndex = 0;
        return 1;
        }

    return 0;
}

const ExtendedProxyFileInfo CP_OptoTrackCom_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _CP_OptoTrackCom_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _CP_OptoTrackCom_StubVtblList,
    (const PCInterfaceName * ) & _CP_OptoTrackCom_InterfaceNamesList,
    (const IID ** ) & _CP_OptoTrackCom_BaseIIDList,
    & _CP_OptoTrackCom_IID_Lookup, 
    1,
    1,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
