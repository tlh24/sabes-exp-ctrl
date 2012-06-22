/* this ALWAYS GENERATED file contains the proxy stub code */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Dec 07 17:05:40 2006
 */
/* Compiler settings for Y:\work\Sabes\CP_EyeTrack\Current\CP_EyeTrackCom.idl:
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


#include "CP_EyeTrackCom.h"

#define TYPE_FORMAT_STRING_SIZE   1021                              
#define PROC_FORMAT_STRING_SIZE   51                                

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


/* Object interface: IEyeTrack, ver. 0.0,
   GUID={0xebd33058,0xceb1,0x11d5,{0x9c,0x3e,0x00,0x50,0xda,0x2a,0x68,0xc8}} */


extern const MIDL_STUB_DESC Object_StubDesc;


#pragma code_seg(".orpc")

/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEyeTrack_get_strProgramVersion_Proxy( 
    IEyeTrack __RPC_FAR * This,
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

void __RPC_STUB IEyeTrack_get_strProgramVersion_Stub(
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
        _RetVal = (((IEyeTrack*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_strProgramVersion((IEyeTrack *) ((CStdStubBuffer *)This)->pvServerObject,pVal);
        
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


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEyeTrack_ConnectISCAN_Proxy( 
    IEyeTrack __RPC_FAR * This)
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

void __RPC_STUB IEyeTrack_ConnectISCAN_Stub(
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
        _RetVal = (((IEyeTrack*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> ConnectISCAN((IEyeTrack *) ((CStdStubBuffer *)This)->pvServerObject);
        
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


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEyeTrack_DisconnectISCAN_Proxy( 
    IEyeTrack __RPC_FAR * This)
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

void __RPC_STUB IEyeTrack_DisconnectISCAN_Stub(
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
        _RetVal = (((IEyeTrack*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> DisconnectISCAN((IEyeTrack *) ((CStdStubBuffer *)This)->pvServerObject);
        
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


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEyeTrack_ResetBuffer_Proxy( 
    IEyeTrack __RPC_FAR * This)
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

void __RPC_STUB IEyeTrack_ResetBuffer_Stub(
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
        _RetVal = (((IEyeTrack*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> ResetBuffer((IEyeTrack *) ((CStdStubBuffer *)This)->pvServerObject);
        
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


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEyeTrack_get_lngCOM_Index_Proxy( 
    IEyeTrack __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal)
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
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[8] );
            
            *pVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
            
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
                         ( void __RPC_FAR * )pVal);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IEyeTrack_get_lngCOM_Index_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    long _M1;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long __RPC_FAR *pVal;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( long __RPC_FAR * )pVal = 0;
    RpcTryFinally
        {
        pVal = &_M1;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IEyeTrack*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_lngCOM_Index((IEyeTrack *) ((CStdStubBuffer *)This)->pvServerObject,pVal);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U + 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = *pVal;
        
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IEyeTrack_put_lngCOM_Index_Proxy( 
    IEyeTrack __RPC_FAR * This,
    /* [in] */ long newVal)
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
            
            _StubMsg.BufferLength = 4U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( long __RPC_FAR * )_StubMsg.Buffer)++ = newVal;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[14] );
            
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

void __RPC_STUB IEyeTrack_put_lngCOM_Index_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long newVal;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[14] );
        
        newVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IEyeTrack*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_lngCOM_Index((IEyeTrack *) ((CStdStubBuffer *)This)->pvServerObject,newVal);
        
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


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEyeTrack_get_lngBaudRate_Proxy( 
    IEyeTrack __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal)
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
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[8] );
            
            *pVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
            
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
                         ( void __RPC_FAR * )pVal);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IEyeTrack_get_lngBaudRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    long _M2;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long __RPC_FAR *pVal;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( long __RPC_FAR * )pVal = 0;
    RpcTryFinally
        {
        pVal = &_M2;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IEyeTrack*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_lngBaudRate((IEyeTrack *) ((CStdStubBuffer *)This)->pvServerObject,pVal);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U + 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = *pVal;
        
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IEyeTrack_put_lngBaudRate_Proxy( 
    IEyeTrack __RPC_FAR * This,
    /* [in] */ long newVal)
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
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 4U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( long __RPC_FAR * )_StubMsg.Buffer)++ = newVal;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[14] );
            
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

void __RPC_STUB IEyeTrack_put_lngBaudRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long newVal;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[14] );
        
        newVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IEyeTrack*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_lngBaudRate((IEyeTrack *) ((CStdStubBuffer *)This)->pvServerObject,newVal);
        
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


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEyeTrack_GetCalibrationMatrix_Proxy( 
    IEyeTrack __RPC_FAR * This,
    /* [retval][out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *padMatrix)
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
        
        
        
        if(!padMatrix)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[18] );
            
            NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR * __RPC_FAR *)&padMatrix,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[978],
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[44],
                         ( void __RPC_FAR * )padMatrix);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IEyeTrack_GetCalibrationMatrix_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    SAFEARRAY __RPC_FAR * __RPC_FAR *padMatrix;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( SAFEARRAY __RPC_FAR * __RPC_FAR * )padMatrix = 0;
    RpcTryFinally
        {
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IEyeTrack*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> GetCalibrationMatrix((IEyeTrack *) ((CStdStubBuffer *)This)->pvServerObject,padMatrix);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 0U + 11U;
        NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR *)padMatrix,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[978] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char __RPC_FAR *)padMatrix,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[978] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)padMatrix,
                        &__MIDL_TypeFormatString.Format[44] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEyeTrack_PutCalibrationMatrix_Proxy( 
    IEyeTrack __RPC_FAR * This,
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
                      16);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR *)adMatrix,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[996] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char __RPC_FAR *)adMatrix,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[996] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[24] );
            
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

void __RPC_STUB IEyeTrack_PutCalibrationMatrix_Stub(
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
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[24] );
        
        NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&adMatrix,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[996],
                                  (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IEyeTrack*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> PutCalibrationMatrix((IEyeTrack *) ((CStdStubBuffer *)This)->pvServerObject,adMatrix);
        
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


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEyeTrack_get_IsCalibrated_Proxy( 
    IEyeTrack __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal)
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
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[8] );
            
            *pVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
            
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
                         ( void __RPC_FAR * )pVal);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IEyeTrack_get_IsCalibrated_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    long _M3;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long __RPC_FAR *pVal;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( long __RPC_FAR * )pVal = 0;
    RpcTryFinally
        {
        pVal = &_M3;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IEyeTrack*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_IsCalibrated((IEyeTrack *) ((CStdStubBuffer *)This)->pvServerObject,pVal);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U + 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = *pVal;
        
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IEyeTrack_put_IsCalibrated_Proxy( 
    IEyeTrack __RPC_FAR * This,
    /* [in] */ long newVal)
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
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 4U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( long __RPC_FAR * )_StubMsg.Buffer)++ = newVal;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[14] );
            
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

void __RPC_STUB IEyeTrack_put_IsCalibrated_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long newVal;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[14] );
        
        newVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IEyeTrack*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_IsCalibrated((IEyeTrack *) ((CStdStubBuffer *)This)->pvServerObject,newVal);
        
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


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEyeTrack_get_lngBufferSize_Proxy( 
    IEyeTrack __RPC_FAR * This,
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
                      19);
        
        
        
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

void __RPC_STUB IEyeTrack_get_lngBufferSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    long _M4;
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
        pnItems = &_M4;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IEyeTrack*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_lngBufferSize((IEyeTrack *) ((CStdStubBuffer *)This)->pvServerObject,pnItems);
        
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


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEyeTrack_get_lngLatestDataIndex_Proxy( 
    IEyeTrack __RPC_FAR * This,
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
                      20);
        
        
        
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

void __RPC_STUB IEyeTrack_get_lngLatestDataIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    long _M5;
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
        plIdx = &_M5;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IEyeTrack*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_lngLatestDataIndex((IEyeTrack *) ((CStdStubBuffer *)This)->pvServerObject,plIdx);
        
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


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEyeTrack_GetLatestData_Proxy( 
    IEyeTrack __RPC_FAR * This,
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
                      21);
        
        
        
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
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[30] );
            
            *plIdx = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
            
            NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR * __RPC_FAR *)&padData,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1010],
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[1006],
                         ( void __RPC_FAR * )padData);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IEyeTrack_GetLatestData_Stub(
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
        _RetVal = (((IEyeTrack*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> GetLatestData(
                 (IEyeTrack *) ((CStdStubBuffer *)This)->pvServerObject,
                 plIdx,
                 padData);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U + 0U + 11U;
        NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR *)padData,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1010] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = *plIdx;
        
        NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char __RPC_FAR *)padData,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1010] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)padData,
                        &__MIDL_TypeFormatString.Format[1006] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEyeTrack_GetDataBuffer_Proxy( 
    IEyeTrack __RPC_FAR * This,
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
                      22);
        
        
        
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
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[40] );
            
            NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR * __RPC_FAR *)&padData,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1010],
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[1006],
                         ( void __RPC_FAR * )padData);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IEyeTrack_GetDataBuffer_Stub(
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
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[40] );
        
        lngIdx = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        nItems = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IEyeTrack*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> GetDataBuffer(
                 (IEyeTrack *) ((CStdStubBuffer *)This)->pvServerObject,
                 lngIdx,
                 nItems,
                 padData);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 0U + 11U;
        NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR *)padData,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1010] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char __RPC_FAR *)padData,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1010] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)padData,
                        &__MIDL_TypeFormatString.Format[1006] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEyeTrack_ResetDataBuffer_Proxy( 
    IEyeTrack __RPC_FAR * This)
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
                      23);
        
        
        
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

void __RPC_STUB IEyeTrack_ResetDataBuffer_Stub(
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
        _RetVal = (((IEyeTrack*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> ResetDataBuffer((IEyeTrack *) ((CStdStubBuffer *)This)->pvServerObject);
        
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

CINTERFACE_PROXY_VTABLE(24) _IEyeTrackProxyVtbl = 
{
    &IID_IEyeTrack,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch_GetTypeInfoCount_Proxy */ ,
    0 /* IDispatch_GetTypeInfo_Proxy */ ,
    0 /* IDispatch_GetIDsOfNames_Proxy */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    IEyeTrack_get_strProgramVersion_Proxy ,
    IEyeTrack_ConnectISCAN_Proxy ,
    IEyeTrack_DisconnectISCAN_Proxy ,
    IEyeTrack_ResetBuffer_Proxy ,
    IEyeTrack_get_lngCOM_Index_Proxy ,
    IEyeTrack_put_lngCOM_Index_Proxy ,
    IEyeTrack_get_lngBaudRate_Proxy ,
    IEyeTrack_put_lngBaudRate_Proxy ,
    IEyeTrack_GetCalibrationMatrix_Proxy ,
    IEyeTrack_PutCalibrationMatrix_Proxy ,
    IEyeTrack_get_IsCalibrated_Proxy ,
    IEyeTrack_put_IsCalibrated_Proxy ,
    IEyeTrack_get_lngBufferSize_Proxy ,
    IEyeTrack_get_lngLatestDataIndex_Proxy ,
    IEyeTrack_GetLatestData_Proxy ,
    IEyeTrack_GetDataBuffer_Proxy ,
    IEyeTrack_ResetDataBuffer_Proxy
};


static const PRPC_STUB_FUNCTION IEyeTrack_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    IEyeTrack_get_strProgramVersion_Stub,
    IEyeTrack_ConnectISCAN_Stub,
    IEyeTrack_DisconnectISCAN_Stub,
    IEyeTrack_ResetBuffer_Stub,
    IEyeTrack_get_lngCOM_Index_Stub,
    IEyeTrack_put_lngCOM_Index_Stub,
    IEyeTrack_get_lngBaudRate_Stub,
    IEyeTrack_put_lngBaudRate_Stub,
    IEyeTrack_GetCalibrationMatrix_Stub,
    IEyeTrack_PutCalibrationMatrix_Stub,
    IEyeTrack_get_IsCalibrated_Stub,
    IEyeTrack_put_IsCalibrated_Stub,
    IEyeTrack_get_lngBufferSize_Stub,
    IEyeTrack_get_lngLatestDataIndex_Stub,
    IEyeTrack_GetLatestData_Stub,
    IEyeTrack_GetDataBuffer_Stub,
    IEyeTrack_ResetDataBuffer_Stub
};

CInterfaceStubVtbl _IEyeTrackStubVtbl =
{
    &IID_IEyeTrack,
    0,
    24,
    &IEyeTrack_table[-3],
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
/* 14 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 16 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 18 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 20 */	NdrFcShort( 0x2c ),	/* Type Offset=44 */
/* 22 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 24 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x0,		/* x86, MIPS & PPC Stack size = 0 */
#else
			0x0,		/* Alpha Stack size = 0 */
#endif
/* 26 */	NdrFcShort( 0x3e4 ),	/* Type Offset=996 */
/* 28 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 30 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 32 */	NdrFcShort( 0x28 ),	/* Type Offset=40 */
/* 34 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 36 */	NdrFcShort( 0x3ee ),	/* Type Offset=1006 */
/* 38 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 40 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 42 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 44 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 46 */	NdrFcShort( 0x3ee ),	/* Type Offset=1006 */
/* 48 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
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
			0x11, 0x0,	/* FC_RP */
/* 46 */	NdrFcShort( 0x3a4 ),	/* Offset= 932 (978) */
/* 48 */	
			0x13, 0x10,	/* FC_OP */
/* 50 */	NdrFcShort( 0x2 ),	/* Offset= 2 (52) */
/* 52 */	
			0x13, 0x0,	/* FC_OP */
/* 54 */	NdrFcShort( 0x38a ),	/* Offset= 906 (960) */
/* 56 */	
			0x2a,		/* FC_ENCAPSULATED_UNION */
			0x49,		/* 73 */
/* 58 */	NdrFcShort( 0x18 ),	/* 24 */
/* 60 */	NdrFcShort( 0xa ),	/* 10 */
/* 62 */	NdrFcLong( 0x8 ),	/* 8 */
/* 66 */	NdrFcShort( 0x58 ),	/* Offset= 88 (154) */
/* 68 */	NdrFcLong( 0xd ),	/* 13 */
/* 72 */	NdrFcShort( 0x8a ),	/* Offset= 138 (210) */
/* 74 */	NdrFcLong( 0x9 ),	/* 9 */
/* 78 */	NdrFcShort( 0xb8 ),	/* Offset= 184 (262) */
/* 80 */	NdrFcLong( 0xc ),	/* 12 */
/* 84 */	NdrFcShort( 0x27a ),	/* Offset= 634 (718) */
/* 86 */	NdrFcLong( 0x24 ),	/* 36 */
/* 90 */	NdrFcShort( 0x2a2 ),	/* Offset= 674 (764) */
/* 92 */	NdrFcLong( 0x800d ),	/* 32781 */
/* 96 */	NdrFcShort( 0x2be ),	/* Offset= 702 (798) */
/* 98 */	NdrFcLong( 0x10 ),	/* 16 */
/* 102 */	NdrFcShort( 0x2d6 ),	/* Offset= 726 (828) */
/* 104 */	NdrFcLong( 0x2 ),	/* 2 */
/* 108 */	NdrFcShort( 0x2ee ),	/* Offset= 750 (858) */
/* 110 */	NdrFcLong( 0x3 ),	/* 3 */
/* 114 */	NdrFcShort( 0x306 ),	/* Offset= 774 (888) */
/* 116 */	NdrFcLong( 0x14 ),	/* 20 */
/* 120 */	NdrFcShort( 0x31e ),	/* Offset= 798 (918) */
/* 122 */	NdrFcShort( 0xffffffff ),	/* Offset= -1 (121) */
/* 124 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 126 */	NdrFcShort( 0x4 ),	/* 4 */
/* 128 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 130 */	NdrFcShort( 0x0 ),	/* 0 */
/* 132 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 134 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 136 */	NdrFcShort( 0x4 ),	/* 4 */
/* 138 */	NdrFcShort( 0x0 ),	/* 0 */
/* 140 */	NdrFcShort( 0x1 ),	/* 1 */
/* 142 */	NdrFcShort( 0x0 ),	/* 0 */
/* 144 */	NdrFcShort( 0x0 ),	/* 0 */
/* 146 */	0x13, 0x0,	/* FC_OP */
/* 148 */	NdrFcShort( 0xffffff80 ),	/* Offset= -128 (20) */
/* 150 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 152 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 154 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 156 */	NdrFcShort( 0x8 ),	/* 8 */
/* 158 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 160 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 162 */	NdrFcShort( 0x4 ),	/* 4 */
/* 164 */	NdrFcShort( 0x4 ),	/* 4 */
/* 166 */	0x11, 0x0,	/* FC_RP */
/* 168 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (124) */
/* 170 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 172 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 174 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 176 */	NdrFcLong( 0x0 ),	/* 0 */
/* 180 */	NdrFcShort( 0x0 ),	/* 0 */
/* 182 */	NdrFcShort( 0x0 ),	/* 0 */
/* 184 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 186 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 188 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 190 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 192 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 194 */	NdrFcShort( 0x0 ),	/* 0 */
/* 196 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 198 */	NdrFcShort( 0x0 ),	/* 0 */
/* 200 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 204 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 206 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (174) */
/* 208 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 210 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 212 */	NdrFcShort( 0x8 ),	/* 8 */
/* 214 */	NdrFcShort( 0x0 ),	/* 0 */
/* 216 */	NdrFcShort( 0x6 ),	/* Offset= 6 (222) */
/* 218 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 220 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 222 */	
			0x11, 0x0,	/* FC_RP */
/* 224 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (192) */
/* 226 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 228 */	NdrFcLong( 0x20400 ),	/* 132096 */
/* 232 */	NdrFcShort( 0x0 ),	/* 0 */
/* 234 */	NdrFcShort( 0x0 ),	/* 0 */
/* 236 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 238 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 240 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 242 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 244 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 246 */	NdrFcShort( 0x0 ),	/* 0 */
/* 248 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 250 */	NdrFcShort( 0x0 ),	/* 0 */
/* 252 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 256 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 258 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (226) */
/* 260 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 262 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 264 */	NdrFcShort( 0x8 ),	/* 8 */
/* 266 */	NdrFcShort( 0x0 ),	/* 0 */
/* 268 */	NdrFcShort( 0x6 ),	/* Offset= 6 (274) */
/* 270 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 272 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 274 */	
			0x11, 0x0,	/* FC_RP */
/* 276 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (244) */
/* 278 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 280 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 282 */	NdrFcShort( 0xfff8 ),	/* -8 */
/* 284 */	NdrFcShort( 0x2 ),	/* Offset= 2 (286) */
/* 286 */	NdrFcShort( 0x10 ),	/* 16 */
/* 288 */	NdrFcShort( 0x2b ),	/* 43 */
/* 290 */	NdrFcLong( 0x3 ),	/* 3 */
/* 294 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 296 */	NdrFcLong( 0x11 ),	/* 17 */
/* 300 */	NdrFcShort( 0x8002 ),	/* Simple arm type: FC_CHAR */
/* 302 */	NdrFcLong( 0x2 ),	/* 2 */
/* 306 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 308 */	NdrFcLong( 0x4 ),	/* 4 */
/* 312 */	NdrFcShort( 0x800a ),	/* Simple arm type: FC_FLOAT */
/* 314 */	NdrFcLong( 0x5 ),	/* 5 */
/* 318 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 320 */	NdrFcLong( 0xb ),	/* 11 */
/* 324 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 326 */	NdrFcLong( 0xa ),	/* 10 */
/* 330 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 332 */	NdrFcLong( 0x6 ),	/* 6 */
/* 336 */	NdrFcShort( 0xd6 ),	/* Offset= 214 (550) */
/* 338 */	NdrFcLong( 0x7 ),	/* 7 */
/* 342 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 344 */	NdrFcLong( 0x8 ),	/* 8 */
/* 348 */	NdrFcShort( 0xfffffeaa ),	/* Offset= -342 (6) */
/* 350 */	NdrFcLong( 0xd ),	/* 13 */
/* 354 */	NdrFcShort( 0xffffff4c ),	/* Offset= -180 (174) */
/* 356 */	NdrFcLong( 0x9 ),	/* 9 */
/* 360 */	NdrFcShort( 0xffffff7a ),	/* Offset= -134 (226) */
/* 362 */	NdrFcLong( 0x2000 ),	/* 8192 */
/* 366 */	NdrFcShort( 0xbe ),	/* Offset= 190 (556) */
/* 368 */	NdrFcLong( 0x24 ),	/* 36 */
/* 372 */	NdrFcShort( 0xbc ),	/* Offset= 188 (560) */
/* 374 */	NdrFcLong( 0x4024 ),	/* 16420 */
/* 378 */	NdrFcShort( 0xb6 ),	/* Offset= 182 (560) */
/* 380 */	NdrFcLong( 0x4011 ),	/* 16401 */
/* 384 */	NdrFcShort( 0xe4 ),	/* Offset= 228 (612) */
/* 386 */	NdrFcLong( 0x4002 ),	/* 16386 */
/* 390 */	NdrFcShort( 0xe2 ),	/* Offset= 226 (616) */
/* 392 */	NdrFcLong( 0x4003 ),	/* 16387 */
/* 396 */	NdrFcShort( 0xe0 ),	/* Offset= 224 (620) */
/* 398 */	NdrFcLong( 0x4004 ),	/* 16388 */
/* 402 */	NdrFcShort( 0xde ),	/* Offset= 222 (624) */
/* 404 */	NdrFcLong( 0x4005 ),	/* 16389 */
/* 408 */	NdrFcShort( 0xdc ),	/* Offset= 220 (628) */
/* 410 */	NdrFcLong( 0x400b ),	/* 16395 */
/* 414 */	NdrFcShort( 0xca ),	/* Offset= 202 (616) */
/* 416 */	NdrFcLong( 0x400a ),	/* 16394 */
/* 420 */	NdrFcShort( 0xc8 ),	/* Offset= 200 (620) */
/* 422 */	NdrFcLong( 0x4006 ),	/* 16390 */
/* 426 */	NdrFcShort( 0xce ),	/* Offset= 206 (632) */
/* 428 */	NdrFcLong( 0x4007 ),	/* 16391 */
/* 432 */	NdrFcShort( 0xc4 ),	/* Offset= 196 (628) */
/* 434 */	NdrFcLong( 0x4008 ),	/* 16392 */
/* 438 */	NdrFcShort( 0xc6 ),	/* Offset= 198 (636) */
/* 440 */	NdrFcLong( 0x400d ),	/* 16397 */
/* 444 */	NdrFcShort( 0xc4 ),	/* Offset= 196 (640) */
/* 446 */	NdrFcLong( 0x4009 ),	/* 16393 */
/* 450 */	NdrFcShort( 0xc2 ),	/* Offset= 194 (644) */
/* 452 */	NdrFcLong( 0x6000 ),	/* 24576 */
/* 456 */	NdrFcShort( 0xc0 ),	/* Offset= 192 (648) */
/* 458 */	NdrFcLong( 0x400c ),	/* 16396 */
/* 462 */	NdrFcShort( 0xba ),	/* Offset= 186 (648) */
/* 464 */	NdrFcLong( 0x10 ),	/* 16 */
/* 468 */	NdrFcShort( 0x8002 ),	/* Simple arm type: FC_CHAR */
/* 470 */	NdrFcLong( 0x12 ),	/* 18 */
/* 474 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 476 */	NdrFcLong( 0x13 ),	/* 19 */
/* 480 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 482 */	NdrFcLong( 0x16 ),	/* 22 */
/* 486 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 488 */	NdrFcLong( 0x17 ),	/* 23 */
/* 492 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 494 */	NdrFcLong( 0xe ),	/* 14 */
/* 498 */	NdrFcShort( 0x9a ),	/* Offset= 154 (652) */
/* 500 */	NdrFcLong( 0x400e ),	/* 16398 */
/* 504 */	NdrFcShort( 0xa0 ),	/* Offset= 160 (664) */
/* 506 */	NdrFcLong( 0x4010 ),	/* 16400 */
/* 510 */	NdrFcShort( 0x66 ),	/* Offset= 102 (612) */
/* 512 */	NdrFcLong( 0x4012 ),	/* 16402 */
/* 516 */	NdrFcShort( 0x64 ),	/* Offset= 100 (616) */
/* 518 */	NdrFcLong( 0x4013 ),	/* 16403 */
/* 522 */	NdrFcShort( 0x62 ),	/* Offset= 98 (620) */
/* 524 */	NdrFcLong( 0x4016 ),	/* 16406 */
/* 528 */	NdrFcShort( 0x5c ),	/* Offset= 92 (620) */
/* 530 */	NdrFcLong( 0x4017 ),	/* 16407 */
/* 534 */	NdrFcShort( 0x56 ),	/* Offset= 86 (620) */
/* 536 */	NdrFcLong( 0x0 ),	/* 0 */
/* 540 */	NdrFcShort( 0x0 ),	/* Offset= 0 (540) */
/* 542 */	NdrFcLong( 0x1 ),	/* 1 */
/* 546 */	NdrFcShort( 0x0 ),	/* Offset= 0 (546) */
/* 548 */	NdrFcShort( 0xffffffff ),	/* Offset= -1 (547) */
/* 550 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 552 */	NdrFcShort( 0x8 ),	/* 8 */
/* 554 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 556 */	
			0x13, 0x0,	/* FC_OP */
/* 558 */	NdrFcShort( 0x192 ),	/* Offset= 402 (960) */
/* 560 */	
			0x13, 0x0,	/* FC_OP */
/* 562 */	NdrFcShort( 0x1e ),	/* Offset= 30 (592) */
/* 564 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 566 */	NdrFcLong( 0x2f ),	/* 47 */
/* 570 */	NdrFcShort( 0x0 ),	/* 0 */
/* 572 */	NdrFcShort( 0x0 ),	/* 0 */
/* 574 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 576 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 578 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 580 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 582 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 584 */	NdrFcShort( 0x1 ),	/* 1 */
/* 586 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 588 */	NdrFcShort( 0x4 ),	/* 4 */
/* 590 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 592 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 594 */	NdrFcShort( 0x10 ),	/* 16 */
/* 596 */	NdrFcShort( 0x0 ),	/* 0 */
/* 598 */	NdrFcShort( 0xa ),	/* Offset= 10 (608) */
/* 600 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 602 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 604 */	NdrFcShort( 0xffffffd8 ),	/* Offset= -40 (564) */
/* 606 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 608 */	
			0x13, 0x0,	/* FC_OP */
/* 610 */	NdrFcShort( 0xffffffe4 ),	/* Offset= -28 (582) */
/* 612 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 614 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 616 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 618 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 620 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 622 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 624 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 626 */	0xa,		/* FC_FLOAT */
			0x5c,		/* FC_PAD */
/* 628 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 630 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 632 */	
			0x13, 0x0,	/* FC_OP */
/* 634 */	NdrFcShort( 0xffffffac ),	/* Offset= -84 (550) */
/* 636 */	
			0x13, 0x10,	/* FC_OP */
/* 638 */	NdrFcShort( 0xfffffd88 ),	/* Offset= -632 (6) */
/* 640 */	
			0x13, 0x10,	/* FC_OP */
/* 642 */	NdrFcShort( 0xfffffe2c ),	/* Offset= -468 (174) */
/* 644 */	
			0x13, 0x10,	/* FC_OP */
/* 646 */	NdrFcShort( 0xfffffe5c ),	/* Offset= -420 (226) */
/* 648 */	
			0x13, 0x10,	/* FC_OP */
/* 650 */	NdrFcShort( 0xffffffa2 ),	/* Offset= -94 (556) */
/* 652 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 654 */	NdrFcShort( 0x10 ),	/* 16 */
/* 656 */	0x6,		/* FC_SHORT */
			0x2,		/* FC_CHAR */
/* 658 */	0x2,		/* FC_CHAR */
			0x38,		/* FC_ALIGNM4 */
/* 660 */	0x8,		/* FC_LONG */
			0x39,		/* FC_ALIGNM8 */
/* 662 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 664 */	
			0x13, 0x0,	/* FC_OP */
/* 666 */	NdrFcShort( 0xfffffff2 ),	/* Offset= -14 (652) */
/* 668 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 670 */	NdrFcShort( 0x20 ),	/* 32 */
/* 672 */	NdrFcShort( 0x0 ),	/* 0 */
/* 674 */	NdrFcShort( 0x0 ),	/* Offset= 0 (674) */
/* 676 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 678 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 680 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 682 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 684 */	NdrFcShort( 0xfffffe6a ),	/* Offset= -406 (278) */
/* 686 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 688 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 690 */	NdrFcShort( 0x4 ),	/* 4 */
/* 692 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 694 */	NdrFcShort( 0x0 ),	/* 0 */
/* 696 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 698 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 700 */	NdrFcShort( 0x4 ),	/* 4 */
/* 702 */	NdrFcShort( 0x0 ),	/* 0 */
/* 704 */	NdrFcShort( 0x1 ),	/* 1 */
/* 706 */	NdrFcShort( 0x0 ),	/* 0 */
/* 708 */	NdrFcShort( 0x0 ),	/* 0 */
/* 710 */	0x13, 0x0,	/* FC_OP */
/* 712 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (668) */
/* 714 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 716 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 718 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 720 */	NdrFcShort( 0x8 ),	/* 8 */
/* 722 */	NdrFcShort( 0x0 ),	/* 0 */
/* 724 */	NdrFcShort( 0x6 ),	/* Offset= 6 (730) */
/* 726 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 728 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 730 */	
			0x11, 0x0,	/* FC_RP */
/* 732 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (688) */
/* 734 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 736 */	NdrFcShort( 0x4 ),	/* 4 */
/* 738 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 740 */	NdrFcShort( 0x0 ),	/* 0 */
/* 742 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 744 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 746 */	NdrFcShort( 0x4 ),	/* 4 */
/* 748 */	NdrFcShort( 0x0 ),	/* 0 */
/* 750 */	NdrFcShort( 0x1 ),	/* 1 */
/* 752 */	NdrFcShort( 0x0 ),	/* 0 */
/* 754 */	NdrFcShort( 0x0 ),	/* 0 */
/* 756 */	0x13, 0x0,	/* FC_OP */
/* 758 */	NdrFcShort( 0xffffff5a ),	/* Offset= -166 (592) */
/* 760 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 762 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 764 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 766 */	NdrFcShort( 0x8 ),	/* 8 */
/* 768 */	NdrFcShort( 0x0 ),	/* 0 */
/* 770 */	NdrFcShort( 0x6 ),	/* Offset= 6 (776) */
/* 772 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 774 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 776 */	
			0x11, 0x0,	/* FC_RP */
/* 778 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (734) */
/* 780 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 782 */	NdrFcShort( 0x8 ),	/* 8 */
/* 784 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/* 786 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 788 */	NdrFcShort( 0x10 ),	/* 16 */
/* 790 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 792 */	0x6,		/* FC_SHORT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 794 */	0x0,		/* 0 */
			NdrFcShort( 0xfffffff1 ),	/* Offset= -15 (780) */
			0x5b,		/* FC_END */
/* 798 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 800 */	NdrFcShort( 0x18 ),	/* 24 */
/* 802 */	NdrFcShort( 0x0 ),	/* 0 */
/* 804 */	NdrFcShort( 0xa ),	/* Offset= 10 (814) */
/* 806 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 808 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 810 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (786) */
/* 812 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 814 */	
			0x11, 0x0,	/* FC_RP */
/* 816 */	NdrFcShort( 0xfffffd90 ),	/* Offset= -624 (192) */
/* 818 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 820 */	NdrFcShort( 0x1 ),	/* 1 */
/* 822 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 824 */	NdrFcShort( 0x0 ),	/* 0 */
/* 826 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 828 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 830 */	NdrFcShort( 0x8 ),	/* 8 */
/* 832 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 834 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 836 */	NdrFcShort( 0x4 ),	/* 4 */
/* 838 */	NdrFcShort( 0x4 ),	/* 4 */
/* 840 */	0x13, 0x0,	/* FC_OP */
/* 842 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (818) */
/* 844 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 846 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 848 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 850 */	NdrFcShort( 0x2 ),	/* 2 */
/* 852 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 854 */	NdrFcShort( 0x0 ),	/* 0 */
/* 856 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 858 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 860 */	NdrFcShort( 0x8 ),	/* 8 */
/* 862 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 864 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 866 */	NdrFcShort( 0x4 ),	/* 4 */
/* 868 */	NdrFcShort( 0x4 ),	/* 4 */
/* 870 */	0x13, 0x0,	/* FC_OP */
/* 872 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (848) */
/* 874 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 876 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 878 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 880 */	NdrFcShort( 0x4 ),	/* 4 */
/* 882 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 884 */	NdrFcShort( 0x0 ),	/* 0 */
/* 886 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 888 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 890 */	NdrFcShort( 0x8 ),	/* 8 */
/* 892 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 894 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 896 */	NdrFcShort( 0x4 ),	/* 4 */
/* 898 */	NdrFcShort( 0x4 ),	/* 4 */
/* 900 */	0x13, 0x0,	/* FC_OP */
/* 902 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (878) */
/* 904 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 906 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 908 */	
			0x1b,		/* FC_CARRAY */
			0x7,		/* 7 */
/* 910 */	NdrFcShort( 0x8 ),	/* 8 */
/* 912 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 914 */	NdrFcShort( 0x0 ),	/* 0 */
/* 916 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 918 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 920 */	NdrFcShort( 0x8 ),	/* 8 */
/* 922 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 924 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 926 */	NdrFcShort( 0x4 ),	/* 4 */
/* 928 */	NdrFcShort( 0x4 ),	/* 4 */
/* 930 */	0x13, 0x0,	/* FC_OP */
/* 932 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (908) */
/* 934 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 936 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 938 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 940 */	NdrFcShort( 0x8 ),	/* 8 */
/* 942 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 944 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 946 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 948 */	NdrFcShort( 0x8 ),	/* 8 */
/* 950 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 952 */	NdrFcShort( 0xffd8 ),	/* -40 */
/* 954 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 956 */	NdrFcShort( 0xffffffee ),	/* Offset= -18 (938) */
/* 958 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 960 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 962 */	NdrFcShort( 0x28 ),	/* 40 */
/* 964 */	NdrFcShort( 0xffffffee ),	/* Offset= -18 (946) */
/* 966 */	NdrFcShort( 0x0 ),	/* Offset= 0 (966) */
/* 968 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 970 */	0x38,		/* FC_ALIGNM4 */
			0x8,		/* FC_LONG */
/* 972 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 974 */	0x0,		/* 0 */
			NdrFcShort( 0xfffffc69 ),	/* Offset= -919 (56) */
			0x5b,		/* FC_END */
/* 978 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 980 */	NdrFcShort( 0x1 ),	/* 1 */
/* 982 */	NdrFcShort( 0x4 ),	/* 4 */
/* 984 */	NdrFcShort( 0x0 ),	/* 0 */
/* 986 */	NdrFcShort( 0xfffffc56 ),	/* Offset= -938 (48) */
/* 988 */	
			0x12, 0x10,	/* FC_UP */
/* 990 */	NdrFcShort( 0x2 ),	/* Offset= 2 (992) */
/* 992 */	
			0x12, 0x0,	/* FC_UP */
/* 994 */	NdrFcShort( 0xffffffde ),	/* Offset= -34 (960) */
/* 996 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 998 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1000 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1002 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1004 */	NdrFcShort( 0xfffffff0 ),	/* Offset= -16 (988) */
/* 1006 */	
			0x11, 0x0,	/* FC_RP */
/* 1008 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1010) */
/* 1010 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1012 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1014 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1016 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1018 */	NdrFcShort( 0xfffffe8e ),	/* Offset= -370 (648) */

			0x0
        }
    };

const CInterfaceProxyVtbl * _CP_EyeTrackCom_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IEyeTrackProxyVtbl,
    0
};

const CInterfaceStubVtbl * _CP_EyeTrackCom_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IEyeTrackStubVtbl,
    0
};

PCInterfaceName const _CP_EyeTrackCom_InterfaceNamesList[] = 
{
    "IEyeTrack",
    0
};

const IID *  _CP_EyeTrackCom_BaseIIDList[] = 
{
    &IID_IDispatch,
    0
};


#define _CP_EyeTrackCom_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _CP_EyeTrackCom, pIID, n)

int __stdcall _CP_EyeTrackCom_IID_Lookup( const IID * pIID, int * pIndex )
{
    
    if(!_CP_EyeTrackCom_CHECK_IID(0))
        {
        *pIndex = 0;
        return 1;
        }

    return 0;
}

const ExtendedProxyFileInfo CP_EyeTrackCom_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _CP_EyeTrackCom_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _CP_EyeTrackCom_StubVtblList,
    (const PCInterfaceName * ) & _CP_EyeTrackCom_InterfaceNamesList,
    (const IID ** ) & _CP_EyeTrackCom_BaseIIDList,
    & _CP_EyeTrackCom_IID_Lookup, 
    1,
    1,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
