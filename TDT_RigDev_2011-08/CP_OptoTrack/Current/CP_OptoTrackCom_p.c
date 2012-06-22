/* this ALWAYS GENERATED file contains the proxy stub code */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Oct 23 20:07:10 2008
 */
/* Compiler settings for C:\users\rebrik\work\Sabes\CP_OptoTrack\Current\CP_OptoTrackCom.idl:
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

#define TYPE_FORMAT_STRING_SIZE   1011                              
#define PROC_FORMAT_STRING_SIZE   149                               

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

/* [helpstring] */ HRESULT STDMETHODCALLTYPE IOptoTrack_GetVersion_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *pVal)
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

void __RPC_STUB IOptoTrack_GetVersion_Stub(
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
        _RetVal = (((IOptoTrack*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> GetVersion((IOptoTrack *) ((CStdStubBuffer *)This)->pvServerObject,pVal);
        
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


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IOptoTrack_ConnectTracker_Proxy( 
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


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IOptoTrack_DisconnectTracker_Proxy( 
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


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IOptoTrack_GetTrackerState_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *piTrackerID,
    /* [out] */ long __RPC_FAR *piState)
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
        
        
        
        if(!piTrackerID)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        if(!piState)
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
            
            *piTrackerID = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
            
            *piState = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
            
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
                         ( void __RPC_FAR * )piTrackerID);
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[40],
                         ( void __RPC_FAR * )piState);
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
    long _M2;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long __RPC_FAR *piState;
    long __RPC_FAR *piTrackerID;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( long __RPC_FAR * )piTrackerID = 0;
    ( long __RPC_FAR * )piState = 0;
    RpcTryFinally
        {
        piTrackerID = &_M1;
        piState = &_M2;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IOptoTrack*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> GetTrackerState(
                   (IOptoTrack *) ((CStdStubBuffer *)This)->pvServerObject,
                   piTrackerID,
                   piState);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U + 4U + 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = *piTrackerID;
        
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = *piState;
        
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IOptoTrack_GetFrameCount_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pnFrames)
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
        
        
        
        if(!pnFrames)
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
            
            *pnFrames = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
            
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
                         ( void __RPC_FAR * )pnFrames);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IOptoTrack_GetFrameCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    long _M3;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long __RPC_FAR *pnFrames;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( long __RPC_FAR * )pnFrames = 0;
    RpcTryFinally
        {
        pnFrames = &_M3;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IOptoTrack*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> GetFrameCount((IOptoTrack *) ((CStdStubBuffer *)This)->pvServerObject,pnFrames);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U + 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = *pnFrames;
        
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IOptoTrack_GetTimeScale_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [out] */ double __RPC_FAR *pdC0,
    /* [out] */ double __RPC_FAR *pdC1)
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
        
        
        
        if(!pdC0)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        if(!pdC1)
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
            
            *pdC0 = *(( double __RPC_FAR * )_StubMsg.Buffer)++;
            
            *pdC1 = *(( double __RPC_FAR * )_StubMsg.Buffer)++;
            
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
                         ( void __RPC_FAR * )pdC0);
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[44],
                         ( void __RPC_FAR * )pdC1);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IOptoTrack_GetTimeScale_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    double _M4;
    double _M5;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    double __RPC_FAR *pdC0;
    double __RPC_FAR *pdC1;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( double __RPC_FAR * )pdC0 = 0;
    ( double __RPC_FAR * )pdC1 = 0;
    RpcTryFinally
        {
        pdC0 = &_M4;
        pdC1 = &_M5;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IOptoTrack*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> GetTimeScale(
                (IOptoTrack *) ((CStdStubBuffer *)This)->pvServerObject,
                pdC0,
                pdC1);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8U + 8U + 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( double __RPC_FAR * )_StubMsg.Buffer)++ = *pdC0;
        
        *(( double __RPC_FAR * )_StubMsg.Buffer)++ = *pdC1;
        
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IOptoTrack_SetTimeScale_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [in] */ double dC0,
    /* [in] */ double dC1)
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
            
            _StubMsg.BufferLength = 8U + 8U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( double __RPC_FAR * )_StubMsg.Buffer)++ = dC0;
            
            *(( double __RPC_FAR * )_StubMsg.Buffer)++ = dC1;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[34] );
            
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

void __RPC_STUB IOptoTrack_SetTimeScale_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    double dC0;
    double dC1;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[34] );
        
        dC0 = *(( double __RPC_FAR * )_StubMsg.Buffer)++;
        
        dC1 = *(( double __RPC_FAR * )_StubMsg.Buffer)++;
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IOptoTrack*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> SetTimeScale(
                (IOptoTrack *) ((CStdStubBuffer *)This)->pvServerObject,
                dC0,
                dC1);
        
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


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IOptoTrack_GetTransformMatrix_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [defaultvalue][in] */ long iTransformIdx,
    /* [out] */ VARIANT __RPC_FAR *pvTransform)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(pvTransform)
        {
        MIDL_memset(
               pvTransform,
               0,
               sizeof( VARIANT  ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      14);
        
        
        
        if(!pvTransform)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 4U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( long __RPC_FAR * )_StubMsg.Buffer)++ = iTransformIdx;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[40] );
            
            NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR * __RPC_FAR *)&pvTransform,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[986],
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
                         ( void __RPC_FAR * )pvTransform);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IOptoTrack_GetTransformMatrix_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    VARIANT _M6;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long iTransformIdx;
    VARIANT __RPC_FAR *pvTransform;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( VARIANT __RPC_FAR * )pvTransform = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[40] );
        
        iTransformIdx = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        pvTransform = &_M6;
        MIDL_memset(
               pvTransform,
               0,
               sizeof( VARIANT  ));
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IOptoTrack*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> GetTransformMatrix(
                      (IOptoTrack *) ((CStdStubBuffer *)This)->pvServerObject,
                      iTransformIdx,
                      pvTransform);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8U + 11U;
        NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR *)pvTransform,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[986] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char __RPC_FAR *)pvTransform,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[986] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)pvTransform,
                        &__MIDL_TypeFormatString.Format[48] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IOptoTrack_SetTransformMatrix_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [in] */ VARIANT vTransform,
    /* [defaultvalue][in] */ long iTransformIdx)
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
            
            _StubMsg.BufferLength = 8U + 11U;
            NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR *)&vTransform,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1000] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char __RPC_FAR *)&vTransform,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1000] );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            *(( long __RPC_FAR * )_StubMsg.Buffer)++ = iTransformIdx;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[48] );
            
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

void __RPC_STUB IOptoTrack_SetTransformMatrix_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    void __RPC_FAR *_p_vTransform;
    long iTransformIdx;
    VARIANT vTransform;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    _p_vTransform = &vTransform;
    MIDL_memset(
               _p_vTransform,
               0,
               sizeof( VARIANT  ));
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[48] );
        
        NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&_p_vTransform,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1000],
                                  (unsigned char)0 );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        iTransformIdx = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IOptoTrack*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> SetTransformMatrix(
                      (IOptoTrack *) ((CStdStubBuffer *)This)->pvServerObject,
                      vTransform,
                      iTransformIdx);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrUserMarshalFree( &_StubMsg,
                            (unsigned char __RPC_FAR *)&vTransform,
                            &__MIDL_TypeFormatString.Format[1000] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IOptoTrack_GetSensors_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [out] */ VARIANT __RPC_FAR *pvSensors)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(pvSensors)
        {
        MIDL_memset(
               pvSensors,
               0,
               sizeof( VARIANT  ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      16);
        
        
        
        if(!pvSensors)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[56] );
            
            NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR * __RPC_FAR *)&pvSensors,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[986],
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
                         ( void __RPC_FAR * )pvSensors);
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
    VARIANT _M7;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    VARIANT __RPC_FAR *pvSensors;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( VARIANT __RPC_FAR * )pvSensors = 0;
    RpcTryFinally
        {
        pvSensors = &_M7;
        MIDL_memset(
               pvSensors,
               0,
               sizeof( VARIANT  ));
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IOptoTrack*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> GetSensors((IOptoTrack *) ((CStdStubBuffer *)This)->pvServerObject,pvSensors);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8U + 11U;
        NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR *)pvSensors,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[986] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char __RPC_FAR *)pvSensors,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[986] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)pvSensors,
                        &__MIDL_TypeFormatString.Format[48] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IOptoTrack_SetSensors_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [in] */ VARIANT vSensors)
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
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 8U;
            NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR *)&vSensors,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1000] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char __RPC_FAR *)&vSensors,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1000] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[62] );
            
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
    void __RPC_FAR *_p_vSensors;
    VARIANT vSensors;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    _p_vSensors = &vSensors;
    MIDL_memset(
               _p_vSensors,
               0,
               sizeof( VARIANT  ));
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[62] );
        
        NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&_p_vSensors,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1000],
                                  (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IOptoTrack*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> SetSensors((IOptoTrack *) ((CStdStubBuffer *)This)->pvServerObject,vSensors);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrUserMarshalFree( &_StubMsg,
                            (unsigned char __RPC_FAR *)&vSensors,
                            &__MIDL_TypeFormatString.Format[1000] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IOptoTrack_ActivateSensors_Proxy( 
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
                      18);
        
        
        
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

void __RPC_STUB IOptoTrack_ActivateSensors_Stub(
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
        _RetVal = (((IOptoTrack*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> ActivateSensors((IOptoTrack *) ((CStdStubBuffer *)This)->pvServerObject);
        
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


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IOptoTrack_DeactivateSensors_Proxy( 
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
                      19);
        
        
        
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

void __RPC_STUB IOptoTrack_DeactivateSensors_Stub(
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
        _RetVal = (((IOptoTrack*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> DeactivateSensors((IOptoTrack *) ((CStdStubBuffer *)This)->pvServerObject);
        
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


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IOptoTrack_GetSensorsTransformIdx_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [out] */ VARIANT __RPC_FAR *pvTransformIdx)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(pvTransformIdx)
        {
        MIDL_memset(
               pvTransformIdx,
               0,
               sizeof( VARIANT  ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      20);
        
        
        
        if(!pvTransformIdx)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[56] );
            
            NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR * __RPC_FAR *)&pvTransformIdx,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[986],
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
                         ( void __RPC_FAR * )pvTransformIdx);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IOptoTrack_GetSensorsTransformIdx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    VARIANT _M8;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    VARIANT __RPC_FAR *pvTransformIdx;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( VARIANT __RPC_FAR * )pvTransformIdx = 0;
    RpcTryFinally
        {
        pvTransformIdx = &_M8;
        MIDL_memset(
               pvTransformIdx,
               0,
               sizeof( VARIANT  ));
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IOptoTrack*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> GetSensorsTransformIdx((IOptoTrack *) ((CStdStubBuffer *)This)->pvServerObject,pvTransformIdx);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8U + 11U;
        NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR *)pvTransformIdx,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[986] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char __RPC_FAR *)pvTransformIdx,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[986] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)pvTransformIdx,
                        &__MIDL_TypeFormatString.Format[48] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IOptoTrack_SetSensorsTransformIdx_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [in] */ VARIANT vTransformIdx)
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
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 8U;
            NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR *)&vTransformIdx,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1000] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char __RPC_FAR *)&vTransformIdx,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1000] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[62] );
            
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

void __RPC_STUB IOptoTrack_SetSensorsTransformIdx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    void __RPC_FAR *_p_vTransformIdx;
    VARIANT vTransformIdx;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    _p_vTransformIdx = &vTransformIdx;
    MIDL_memset(
               _p_vTransformIdx,
               0,
               sizeof( VARIANT  ));
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[62] );
        
        NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&_p_vTransformIdx,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1000],
                                  (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IOptoTrack*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> SetSensorsTransformIdx((IOptoTrack *) ((CStdStubBuffer *)This)->pvServerObject,vTransformIdx);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrUserMarshalFree( &_StubMsg,
                            (unsigned char __RPC_FAR *)&vTransformIdx,
                            &__MIDL_TypeFormatString.Format[1000] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IOptoTrack_GetBufferSize_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pnFrames)
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
        
        
        
        if(!pnFrames)
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
            
            *pnFrames = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
            
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
                         ( void __RPC_FAR * )pnFrames);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IOptoTrack_GetBufferSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    long _M9;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long __RPC_FAR *pnFrames;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( long __RPC_FAR * )pnFrames = 0;
    RpcTryFinally
        {
        pnFrames = &_M9;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IOptoTrack*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> GetBufferSize((IOptoTrack *) ((CStdStubBuffer *)This)->pvServerObject,pnFrames);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U + 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = *pnFrames;
        
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IOptoTrack_GetDataIndexLatest_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *piDataIdx)
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
        
        
        
        if(!piDataIdx)
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
            
            *piDataIdx = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
            
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
                         ( void __RPC_FAR * )piDataIdx);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IOptoTrack_GetDataIndexLatest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    long _M10;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long __RPC_FAR *piDataIdx;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( long __RPC_FAR * )piDataIdx = 0;
    RpcTryFinally
        {
        piDataIdx = &_M10;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IOptoTrack*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> GetDataIndexLatest((IOptoTrack *) ((CStdStubBuffer *)This)->pvServerObject,piDataIdx);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U + 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = *piDataIdx;
        
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IOptoTrack_GetSensorLatest_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [in] */ long iSensorIdx,
    /* [defaultvalue][in] */ long nFrames,
    /* [out] */ long __RPC_FAR *piDataIdx,
    /* [out] */ VARIANT __RPC_FAR *pvTimeStampMs,
    /* [out] */ VARIANT __RPC_FAR *pvCoord,
    /* [out] */ VARIANT __RPC_FAR *pvVelocity)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(pvTimeStampMs)
        {
        MIDL_memset(
               pvTimeStampMs,
               0,
               sizeof( VARIANT  ));
        }
    if(pvCoord)
        {
        MIDL_memset(
               pvCoord,
               0,
               sizeof( VARIANT  ));
        }
    if(pvVelocity)
        {
        MIDL_memset(
               pvVelocity,
               0,
               sizeof( VARIANT  ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      24);
        
        
        
        if(!piDataIdx)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        if(!pvTimeStampMs)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        if(!pvCoord)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        if(!pvVelocity)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 4U + 4U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( long __RPC_FAR * )_StubMsg.Buffer)++ = iSensorIdx;
            
            *(( long __RPC_FAR * )_StubMsg.Buffer)++ = nFrames;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[68] );
            
            *piDataIdx = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
            
            NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR * __RPC_FAR *)&pvTimeStampMs,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[986],
                                      (unsigned char)0 );
            
            NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR * __RPC_FAR *)&pvCoord,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[986],
                                      (unsigned char)0 );
            
            NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR * __RPC_FAR *)&pvVelocity,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[986],
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
                         ( void __RPC_FAR * )piDataIdx);
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[48],
                         ( void __RPC_FAR * )pvTimeStampMs);
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[48],
                         ( void __RPC_FAR * )pvCoord);
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[48],
                         ( void __RPC_FAR * )pvVelocity);
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
    long _M11;
    VARIANT _M12;
    VARIANT _M13;
    VARIANT _M14;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long iSensorIdx;
    long nFrames;
    long __RPC_FAR *piDataIdx;
    VARIANT __RPC_FAR *pvCoord;
    VARIANT __RPC_FAR *pvTimeStampMs;
    VARIANT __RPC_FAR *pvVelocity;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( long __RPC_FAR * )piDataIdx = 0;
    ( VARIANT __RPC_FAR * )pvTimeStampMs = 0;
    ( VARIANT __RPC_FAR * )pvCoord = 0;
    ( VARIANT __RPC_FAR * )pvVelocity = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[68] );
        
        iSensorIdx = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        nFrames = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        piDataIdx = &_M11;
        pvTimeStampMs = &_M12;
        MIDL_memset(
               pvTimeStampMs,
               0,
               sizeof( VARIANT  ));
        pvCoord = &_M13;
        MIDL_memset(
               pvCoord,
               0,
               sizeof( VARIANT  ));
        pvVelocity = &_M14;
        MIDL_memset(
               pvVelocity,
               0,
               sizeof( VARIANT  ));
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IOptoTrack*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> GetSensorLatest(
                   (IOptoTrack *) ((CStdStubBuffer *)This)->pvServerObject,
                   iSensorIdx,
                   nFrames,
                   piDataIdx,
                   pvTimeStampMs,
                   pvCoord,
                   pvVelocity);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U + 4U + 15U + 15U + 11U;
        NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR *)pvTimeStampMs,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[986] );
        
        NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR *)pvCoord,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[986] );
        
        NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR *)pvVelocity,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[986] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = *piDataIdx;
        
        NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char __RPC_FAR *)pvTimeStampMs,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[986] );
        
        NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char __RPC_FAR *)pvCoord,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[986] );
        
        NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char __RPC_FAR *)pvVelocity,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[986] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)pvTimeStampMs,
                        &__MIDL_TypeFormatString.Format[48] );
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)pvCoord,
                        &__MIDL_TypeFormatString.Format[48] );
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)pvVelocity,
                        &__MIDL_TypeFormatString.Format[48] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IOptoTrack_GetSensorBuffered_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [in] */ long iSensorIdx,
    /* [in] */ long iDataIdx,
    /* [in] */ long nFrames,
    /* [out] */ VARIANT __RPC_FAR *pvTimeStampMs,
    /* [out] */ VARIANT __RPC_FAR *pvCoord,
    /* [out] */ VARIANT __RPC_FAR *pvVelocity)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(pvTimeStampMs)
        {
        MIDL_memset(
               pvTimeStampMs,
               0,
               sizeof( VARIANT  ));
        }
    if(pvCoord)
        {
        MIDL_memset(
               pvCoord,
               0,
               sizeof( VARIANT  ));
        }
    if(pvVelocity)
        {
        MIDL_memset(
               pvVelocity,
               0,
               sizeof( VARIANT  ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      25);
        
        
        
        if(!pvTimeStampMs)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        if(!pvCoord)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        if(!pvVelocity)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 4U + 4U + 4U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( long __RPC_FAR * )_StubMsg.Buffer)++ = iSensorIdx;
            
            *(( long __RPC_FAR * )_StubMsg.Buffer)++ = iDataIdx;
            
            *(( long __RPC_FAR * )_StubMsg.Buffer)++ = nFrames;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[90] );
            
            NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR * __RPC_FAR *)&pvTimeStampMs,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[986],
                                      (unsigned char)0 );
            
            NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR * __RPC_FAR *)&pvCoord,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[986],
                                      (unsigned char)0 );
            
            NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR * __RPC_FAR *)&pvVelocity,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[986],
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
                         ( void __RPC_FAR * )pvTimeStampMs);
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[48],
                         ( void __RPC_FAR * )pvCoord);
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[48],
                         ( void __RPC_FAR * )pvVelocity);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IOptoTrack_GetSensorBuffered_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    VARIANT _M15;
    VARIANT _M16;
    VARIANT _M17;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long iDataIdx;
    long iSensorIdx;
    long nFrames;
    VARIANT __RPC_FAR *pvCoord;
    VARIANT __RPC_FAR *pvTimeStampMs;
    VARIANT __RPC_FAR *pvVelocity;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( VARIANT __RPC_FAR * )pvTimeStampMs = 0;
    ( VARIANT __RPC_FAR * )pvCoord = 0;
    ( VARIANT __RPC_FAR * )pvVelocity = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[90] );
        
        iSensorIdx = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        iDataIdx = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        nFrames = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        pvTimeStampMs = &_M15;
        MIDL_memset(
               pvTimeStampMs,
               0,
               sizeof( VARIANT  ));
        pvCoord = &_M16;
        MIDL_memset(
               pvCoord,
               0,
               sizeof( VARIANT  ));
        pvVelocity = &_M17;
        MIDL_memset(
               pvVelocity,
               0,
               sizeof( VARIANT  ));
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IOptoTrack*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> GetSensorBuffered(
                     (IOptoTrack *) ((CStdStubBuffer *)This)->pvServerObject,
                     iSensorIdx,
                     iDataIdx,
                     nFrames,
                     pvTimeStampMs,
                     pvCoord,
                     pvVelocity);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8U + 15U + 15U + 11U;
        NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR *)pvTimeStampMs,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[986] );
        
        NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR *)pvCoord,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[986] );
        
        NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR *)pvVelocity,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[986] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char __RPC_FAR *)pvTimeStampMs,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[986] );
        
        NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char __RPC_FAR *)pvCoord,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[986] );
        
        NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char __RPC_FAR *)pvVelocity,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[986] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)pvTimeStampMs,
                        &__MIDL_TypeFormatString.Format[48] );
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)pvCoord,
                        &__MIDL_TypeFormatString.Format[48] );
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)pvVelocity,
                        &__MIDL_TypeFormatString.Format[48] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IOptoTrack_GetAllSensorsLatest_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [defaultvalue][in] */ long nFrames,
    /* [out] */ long __RPC_FAR *piIdx,
    /* [out] */ VARIANT __RPC_FAR *pvTimeStampMs,
    /* [out] */ VARIANT __RPC_FAR *pvCoord,
    /* [out] */ VARIANT __RPC_FAR *pvVelocity)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(pvTimeStampMs)
        {
        MIDL_memset(
               pvTimeStampMs,
               0,
               sizeof( VARIANT  ));
        }
    if(pvCoord)
        {
        MIDL_memset(
               pvCoord,
               0,
               sizeof( VARIANT  ));
        }
    if(pvVelocity)
        {
        MIDL_memset(
               pvVelocity,
               0,
               sizeof( VARIANT  ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      26);
        
        
        
        if(!piIdx)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        if(!pvTimeStampMs)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        if(!pvCoord)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        if(!pvVelocity)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 4U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( long __RPC_FAR * )_StubMsg.Buffer)++ = nFrames;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[110] );
            
            *piIdx = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
            
            NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR * __RPC_FAR *)&pvTimeStampMs,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[986],
                                      (unsigned char)0 );
            
            NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR * __RPC_FAR *)&pvCoord,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[986],
                                      (unsigned char)0 );
            
            NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR * __RPC_FAR *)&pvVelocity,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[986],
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
                         ( void __RPC_FAR * )piIdx);
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[48],
                         ( void __RPC_FAR * )pvTimeStampMs);
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[48],
                         ( void __RPC_FAR * )pvCoord);
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[48],
                         ( void __RPC_FAR * )pvVelocity);
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
    long _M18;
    VARIANT _M19;
    VARIANT _M20;
    VARIANT _M21;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long nFrames;
    long __RPC_FAR *piIdx;
    VARIANT __RPC_FAR *pvCoord;
    VARIANT __RPC_FAR *pvTimeStampMs;
    VARIANT __RPC_FAR *pvVelocity;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( long __RPC_FAR * )piIdx = 0;
    ( VARIANT __RPC_FAR * )pvTimeStampMs = 0;
    ( VARIANT __RPC_FAR * )pvCoord = 0;
    ( VARIANT __RPC_FAR * )pvVelocity = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[110] );
        
        nFrames = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        piIdx = &_M18;
        pvTimeStampMs = &_M19;
        MIDL_memset(
               pvTimeStampMs,
               0,
               sizeof( VARIANT  ));
        pvCoord = &_M20;
        MIDL_memset(
               pvCoord,
               0,
               sizeof( VARIANT  ));
        pvVelocity = &_M21;
        MIDL_memset(
               pvVelocity,
               0,
               sizeof( VARIANT  ));
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IOptoTrack*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> GetAllSensorsLatest(
                       (IOptoTrack *) ((CStdStubBuffer *)This)->pvServerObject,
                       nFrames,
                       piIdx,
                       pvTimeStampMs,
                       pvCoord,
                       pvVelocity);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U + 4U + 15U + 15U + 11U;
        NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR *)pvTimeStampMs,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[986] );
        
        NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR *)pvCoord,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[986] );
        
        NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR *)pvVelocity,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[986] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = *piIdx;
        
        NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char __RPC_FAR *)pvTimeStampMs,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[986] );
        
        NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char __RPC_FAR *)pvCoord,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[986] );
        
        NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char __RPC_FAR *)pvVelocity,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[986] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)pvTimeStampMs,
                        &__MIDL_TypeFormatString.Format[48] );
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)pvCoord,
                        &__MIDL_TypeFormatString.Format[48] );
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)pvVelocity,
                        &__MIDL_TypeFormatString.Format[48] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IOptoTrack_GetAllSensorsBuffered_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [in] */ long iDataIdx,
    /* [in] */ long nFrames,
    /* [out] */ VARIANT __RPC_FAR *pvTimeStampMs,
    /* [out] */ VARIANT __RPC_FAR *pvCoord,
    /* [out] */ VARIANT __RPC_FAR *pvVelocity)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(pvTimeStampMs)
        {
        MIDL_memset(
               pvTimeStampMs,
               0,
               sizeof( VARIANT  ));
        }
    if(pvCoord)
        {
        MIDL_memset(
               pvCoord,
               0,
               sizeof( VARIANT  ));
        }
    if(pvVelocity)
        {
        MIDL_memset(
               pvVelocity,
               0,
               sizeof( VARIANT  ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      27);
        
        
        
        if(!pvTimeStampMs)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        if(!pvCoord)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        if(!pvVelocity)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 4U + 4U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( long __RPC_FAR * )_StubMsg.Buffer)++ = iDataIdx;
            
            *(( long __RPC_FAR * )_StubMsg.Buffer)++ = nFrames;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[130] );
            
            NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR * __RPC_FAR *)&pvTimeStampMs,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[986],
                                      (unsigned char)0 );
            
            NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR * __RPC_FAR *)&pvCoord,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[986],
                                      (unsigned char)0 );
            
            NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR * __RPC_FAR *)&pvVelocity,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[986],
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
                         ( void __RPC_FAR * )pvTimeStampMs);
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[48],
                         ( void __RPC_FAR * )pvCoord);
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[48],
                         ( void __RPC_FAR * )pvVelocity);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IOptoTrack_GetAllSensorsBuffered_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    VARIANT _M22;
    VARIANT _M23;
    VARIANT _M24;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long iDataIdx;
    long nFrames;
    VARIANT __RPC_FAR *pvCoord;
    VARIANT __RPC_FAR *pvTimeStampMs;
    VARIANT __RPC_FAR *pvVelocity;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( VARIANT __RPC_FAR * )pvTimeStampMs = 0;
    ( VARIANT __RPC_FAR * )pvCoord = 0;
    ( VARIANT __RPC_FAR * )pvVelocity = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[130] );
        
        iDataIdx = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        nFrames = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        pvTimeStampMs = &_M22;
        MIDL_memset(
               pvTimeStampMs,
               0,
               sizeof( VARIANT  ));
        pvCoord = &_M23;
        MIDL_memset(
               pvCoord,
               0,
               sizeof( VARIANT  ));
        pvVelocity = &_M24;
        MIDL_memset(
               pvVelocity,
               0,
               sizeof( VARIANT  ));
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IOptoTrack*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> GetAllSensorsBuffered(
                         (IOptoTrack *) ((CStdStubBuffer *)This)->pvServerObject,
                         iDataIdx,
                         nFrames,
                         pvTimeStampMs,
                         pvCoord,
                         pvVelocity);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8U + 15U + 15U + 11U;
        NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR *)pvTimeStampMs,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[986] );
        
        NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR *)pvCoord,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[986] );
        
        NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR *)pvVelocity,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[986] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char __RPC_FAR *)pvTimeStampMs,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[986] );
        
        NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char __RPC_FAR *)pvCoord,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[986] );
        
        NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char __RPC_FAR *)pvVelocity,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[986] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)pvTimeStampMs,
                        &__MIDL_TypeFormatString.Format[48] );
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)pvCoord,
                        &__MIDL_TypeFormatString.Format[48] );
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)pvVelocity,
                        &__MIDL_TypeFormatString.Format[48] );
        
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

CINTERFACE_PROXY_VTABLE(28) _IOptoTrackProxyVtbl = 
{
    &IID_IOptoTrack,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch_GetTypeInfoCount_Proxy */ ,
    0 /* IDispatch_GetTypeInfo_Proxy */ ,
    0 /* IDispatch_GetIDsOfNames_Proxy */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    IOptoTrack_GetVersion_Proxy ,
    IOptoTrack_ConnectTracker_Proxy ,
    IOptoTrack_DisconnectTracker_Proxy ,
    IOptoTrack_GetTrackerState_Proxy ,
    IOptoTrack_GetFrameCount_Proxy ,
    IOptoTrack_GetTimeScale_Proxy ,
    IOptoTrack_SetTimeScale_Proxy ,
    IOptoTrack_GetTransformMatrix_Proxy ,
    IOptoTrack_SetTransformMatrix_Proxy ,
    IOptoTrack_GetSensors_Proxy ,
    IOptoTrack_SetSensors_Proxy ,
    IOptoTrack_ActivateSensors_Proxy ,
    IOptoTrack_DeactivateSensors_Proxy ,
    IOptoTrack_GetSensorsTransformIdx_Proxy ,
    IOptoTrack_SetSensorsTransformIdx_Proxy ,
    IOptoTrack_GetBufferSize_Proxy ,
    IOptoTrack_GetDataIndexLatest_Proxy ,
    IOptoTrack_GetSensorLatest_Proxy ,
    IOptoTrack_GetSensorBuffered_Proxy ,
    IOptoTrack_GetAllSensorsLatest_Proxy ,
    IOptoTrack_GetAllSensorsBuffered_Proxy
};


static const PRPC_STUB_FUNCTION IOptoTrack_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    IOptoTrack_GetVersion_Stub,
    IOptoTrack_ConnectTracker_Stub,
    IOptoTrack_DisconnectTracker_Stub,
    IOptoTrack_GetTrackerState_Stub,
    IOptoTrack_GetFrameCount_Stub,
    IOptoTrack_GetTimeScale_Stub,
    IOptoTrack_SetTimeScale_Stub,
    IOptoTrack_GetTransformMatrix_Stub,
    IOptoTrack_SetTransformMatrix_Stub,
    IOptoTrack_GetSensors_Stub,
    IOptoTrack_SetSensors_Stub,
    IOptoTrack_ActivateSensors_Stub,
    IOptoTrack_DeactivateSensors_Stub,
    IOptoTrack_GetSensorsTransformIdx_Stub,
    IOptoTrack_SetSensorsTransformIdx_Stub,
    IOptoTrack_GetBufferSize_Stub,
    IOptoTrack_GetDataIndexLatest_Stub,
    IOptoTrack_GetSensorLatest_Stub,
    IOptoTrack_GetSensorBuffered_Stub,
    IOptoTrack_GetAllSensorsLatest_Stub,
    IOptoTrack_GetAllSensorsBuffered_Stub
};

CInterfaceStubVtbl _IOptoTrackStubVtbl =
{
    &IID_IOptoTrack,
    0,
    28,
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
            VARIANT_UserSize
            ,VARIANT_UserMarshal
            ,VARIANT_UserUnmarshal
            ,VARIANT_UserFree
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
/* 12 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 14 */	NdrFcShort( 0x28 ),	/* Type Offset=40 */
/* 16 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 18 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 20 */	NdrFcShort( 0x28 ),	/* Type Offset=40 */
/* 22 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 24 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 26 */	NdrFcShort( 0x2c ),	/* Type Offset=44 */
/* 28 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 30 */	NdrFcShort( 0x2c ),	/* Type Offset=44 */
/* 32 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 34 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0xc,		/* FC_DOUBLE */
/* 36 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0xc,		/* FC_DOUBLE */
/* 38 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 40 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 42 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 44 */	NdrFcShort( 0x30 ),	/* Type Offset=48 */
/* 46 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 48 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x4,		/* x86, MIPS & PPC Stack size = 4 */
#else
			0x4,		/* Alpha Stack size = 4 */
#endif
/* 50 */	NdrFcShort( 0x3e8 ),	/* Type Offset=1000 */
/* 52 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 54 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 56 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 58 */	NdrFcShort( 0x30 ),	/* Type Offset=48 */
/* 60 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 62 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x4,		/* x86, MIPS & PPC Stack size = 4 */
#else
			0x4,		/* Alpha Stack size = 4 */
#endif
/* 64 */	NdrFcShort( 0x3e8 ),	/* Type Offset=1000 */
/* 66 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 68 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 70 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 72 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 74 */	NdrFcShort( 0x28 ),	/* Type Offset=40 */
/* 76 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 78 */	NdrFcShort( 0x30 ),	/* Type Offset=48 */
/* 80 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 82 */	NdrFcShort( 0x30 ),	/* Type Offset=48 */
/* 84 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 86 */	NdrFcShort( 0x30 ),	/* Type Offset=48 */
/* 88 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 90 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 92 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 94 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 96 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 98 */	NdrFcShort( 0x30 ),	/* Type Offset=48 */
/* 100 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 102 */	NdrFcShort( 0x30 ),	/* Type Offset=48 */
/* 104 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 106 */	NdrFcShort( 0x30 ),	/* Type Offset=48 */
/* 108 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 110 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 112 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 114 */	NdrFcShort( 0x28 ),	/* Type Offset=40 */
/* 116 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 118 */	NdrFcShort( 0x30 ),	/* Type Offset=48 */
/* 120 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 122 */	NdrFcShort( 0x30 ),	/* Type Offset=48 */
/* 124 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 126 */	NdrFcShort( 0x30 ),	/* Type Offset=48 */
/* 128 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 130 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 132 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 134 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 136 */	NdrFcShort( 0x30 ),	/* Type Offset=48 */
/* 138 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 140 */	NdrFcShort( 0x30 ),	/* Type Offset=48 */
/* 142 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 144 */	NdrFcShort( 0x30 ),	/* Type Offset=48 */
/* 146 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
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
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 50 */	NdrFcShort( 0x3a8 ),	/* Offset= 936 (986) */
/* 52 */	
			0x13, 0x0,	/* FC_OP */
/* 54 */	NdrFcShort( 0x390 ),	/* Offset= 912 (966) */
/* 56 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 58 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 60 */	NdrFcShort( 0xfff8 ),	/* -8 */
/* 62 */	NdrFcShort( 0x2 ),	/* Offset= 2 (64) */
/* 64 */	NdrFcShort( 0x10 ),	/* 16 */
/* 66 */	NdrFcShort( 0x2b ),	/* 43 */
/* 68 */	NdrFcLong( 0x3 ),	/* 3 */
/* 72 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 74 */	NdrFcLong( 0x11 ),	/* 17 */
/* 78 */	NdrFcShort( 0x8002 ),	/* Simple arm type: FC_CHAR */
/* 80 */	NdrFcLong( 0x2 ),	/* 2 */
/* 84 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 86 */	NdrFcLong( 0x4 ),	/* 4 */
/* 90 */	NdrFcShort( 0x800a ),	/* Simple arm type: FC_FLOAT */
/* 92 */	NdrFcLong( 0x5 ),	/* 5 */
/* 96 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 98 */	NdrFcLong( 0xb ),	/* 11 */
/* 102 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 104 */	NdrFcLong( 0xa ),	/* 10 */
/* 108 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 110 */	NdrFcLong( 0x6 ),	/* 6 */
/* 114 */	NdrFcShort( 0xd6 ),	/* Offset= 214 (328) */
/* 116 */	NdrFcLong( 0x7 ),	/* 7 */
/* 120 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 122 */	NdrFcLong( 0x8 ),	/* 8 */
/* 126 */	NdrFcShort( 0xffffff88 ),	/* Offset= -120 (6) */
/* 128 */	NdrFcLong( 0xd ),	/* 13 */
/* 132 */	NdrFcShort( 0xca ),	/* Offset= 202 (334) */
/* 134 */	NdrFcLong( 0x9 ),	/* 9 */
/* 138 */	NdrFcShort( 0xd6 ),	/* Offset= 214 (352) */
/* 140 */	NdrFcLong( 0x2000 ),	/* 8192 */
/* 144 */	NdrFcShort( 0xe2 ),	/* Offset= 226 (370) */
/* 146 */	NdrFcLong( 0x24 ),	/* 36 */
/* 150 */	NdrFcShort( 0x2ec ),	/* Offset= 748 (898) */
/* 152 */	NdrFcLong( 0x4024 ),	/* 16420 */
/* 156 */	NdrFcShort( 0x2e6 ),	/* Offset= 742 (898) */
/* 158 */	NdrFcLong( 0x4011 ),	/* 16401 */
/* 162 */	NdrFcShort( 0x2e4 ),	/* Offset= 740 (902) */
/* 164 */	NdrFcLong( 0x4002 ),	/* 16386 */
/* 168 */	NdrFcShort( 0x2e2 ),	/* Offset= 738 (906) */
/* 170 */	NdrFcLong( 0x4003 ),	/* 16387 */
/* 174 */	NdrFcShort( 0x2e0 ),	/* Offset= 736 (910) */
/* 176 */	NdrFcLong( 0x4004 ),	/* 16388 */
/* 180 */	NdrFcShort( 0x2de ),	/* Offset= 734 (914) */
/* 182 */	NdrFcLong( 0x4005 ),	/* 16389 */
/* 186 */	NdrFcShort( 0x2dc ),	/* Offset= 732 (918) */
/* 188 */	NdrFcLong( 0x400b ),	/* 16395 */
/* 192 */	NdrFcShort( 0x2ca ),	/* Offset= 714 (906) */
/* 194 */	NdrFcLong( 0x400a ),	/* 16394 */
/* 198 */	NdrFcShort( 0x2c8 ),	/* Offset= 712 (910) */
/* 200 */	NdrFcLong( 0x4006 ),	/* 16390 */
/* 204 */	NdrFcShort( 0x2ce ),	/* Offset= 718 (922) */
/* 206 */	NdrFcLong( 0x4007 ),	/* 16391 */
/* 210 */	NdrFcShort( 0x2c4 ),	/* Offset= 708 (918) */
/* 212 */	NdrFcLong( 0x4008 ),	/* 16392 */
/* 216 */	NdrFcShort( 0x2c6 ),	/* Offset= 710 (926) */
/* 218 */	NdrFcLong( 0x400d ),	/* 16397 */
/* 222 */	NdrFcShort( 0x2c4 ),	/* Offset= 708 (930) */
/* 224 */	NdrFcLong( 0x4009 ),	/* 16393 */
/* 228 */	NdrFcShort( 0x2c2 ),	/* Offset= 706 (934) */
/* 230 */	NdrFcLong( 0x6000 ),	/* 24576 */
/* 234 */	NdrFcShort( 0x2c0 ),	/* Offset= 704 (938) */
/* 236 */	NdrFcLong( 0x400c ),	/* 16396 */
/* 240 */	NdrFcShort( 0x2be ),	/* Offset= 702 (942) */
/* 242 */	NdrFcLong( 0x10 ),	/* 16 */
/* 246 */	NdrFcShort( 0x8002 ),	/* Simple arm type: FC_CHAR */
/* 248 */	NdrFcLong( 0x12 ),	/* 18 */
/* 252 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 254 */	NdrFcLong( 0x13 ),	/* 19 */
/* 258 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 260 */	NdrFcLong( 0x16 ),	/* 22 */
/* 264 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 266 */	NdrFcLong( 0x17 ),	/* 23 */
/* 270 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 272 */	NdrFcLong( 0xe ),	/* 14 */
/* 276 */	NdrFcShort( 0x2a2 ),	/* Offset= 674 (950) */
/* 278 */	NdrFcLong( 0x400e ),	/* 16398 */
/* 282 */	NdrFcShort( 0x2a8 ),	/* Offset= 680 (962) */
/* 284 */	NdrFcLong( 0x4010 ),	/* 16400 */
/* 288 */	NdrFcShort( 0x266 ),	/* Offset= 614 (902) */
/* 290 */	NdrFcLong( 0x4012 ),	/* 16402 */
/* 294 */	NdrFcShort( 0x264 ),	/* Offset= 612 (906) */
/* 296 */	NdrFcLong( 0x4013 ),	/* 16403 */
/* 300 */	NdrFcShort( 0x262 ),	/* Offset= 610 (910) */
/* 302 */	NdrFcLong( 0x4016 ),	/* 16406 */
/* 306 */	NdrFcShort( 0x25c ),	/* Offset= 604 (910) */
/* 308 */	NdrFcLong( 0x4017 ),	/* 16407 */
/* 312 */	NdrFcShort( 0x256 ),	/* Offset= 598 (910) */
/* 314 */	NdrFcLong( 0x0 ),	/* 0 */
/* 318 */	NdrFcShort( 0x0 ),	/* Offset= 0 (318) */
/* 320 */	NdrFcLong( 0x1 ),	/* 1 */
/* 324 */	NdrFcShort( 0x0 ),	/* Offset= 0 (324) */
/* 326 */	NdrFcShort( 0xffffffff ),	/* Offset= -1 (325) */
/* 328 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 330 */	NdrFcShort( 0x8 ),	/* 8 */
/* 332 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 334 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 336 */	NdrFcLong( 0x0 ),	/* 0 */
/* 340 */	NdrFcShort( 0x0 ),	/* 0 */
/* 342 */	NdrFcShort( 0x0 ),	/* 0 */
/* 344 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 346 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 348 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 350 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 352 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 354 */	NdrFcLong( 0x20400 ),	/* 132096 */
/* 358 */	NdrFcShort( 0x0 ),	/* 0 */
/* 360 */	NdrFcShort( 0x0 ),	/* 0 */
/* 362 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 364 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 366 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 368 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 370 */	
			0x13, 0x0,	/* FC_OP */
/* 372 */	NdrFcShort( 0x1fc ),	/* Offset= 508 (880) */
/* 374 */	
			0x2a,		/* FC_ENCAPSULATED_UNION */
			0x49,		/* 73 */
/* 376 */	NdrFcShort( 0x18 ),	/* 24 */
/* 378 */	NdrFcShort( 0xa ),	/* 10 */
/* 380 */	NdrFcLong( 0x8 ),	/* 8 */
/* 384 */	NdrFcShort( 0x58 ),	/* Offset= 88 (472) */
/* 386 */	NdrFcLong( 0xd ),	/* 13 */
/* 390 */	NdrFcShort( 0x78 ),	/* Offset= 120 (510) */
/* 392 */	NdrFcLong( 0x9 ),	/* 9 */
/* 396 */	NdrFcShort( 0x94 ),	/* Offset= 148 (544) */
/* 398 */	NdrFcLong( 0xc ),	/* 12 */
/* 402 */	NdrFcShort( 0xbc ),	/* Offset= 188 (590) */
/* 404 */	NdrFcLong( 0x24 ),	/* 36 */
/* 408 */	NdrFcShort( 0x114 ),	/* Offset= 276 (684) */
/* 410 */	NdrFcLong( 0x800d ),	/* 32781 */
/* 414 */	NdrFcShort( 0x130 ),	/* Offset= 304 (718) */
/* 416 */	NdrFcLong( 0x10 ),	/* 16 */
/* 420 */	NdrFcShort( 0x148 ),	/* Offset= 328 (748) */
/* 422 */	NdrFcLong( 0x2 ),	/* 2 */
/* 426 */	NdrFcShort( 0x160 ),	/* Offset= 352 (778) */
/* 428 */	NdrFcLong( 0x3 ),	/* 3 */
/* 432 */	NdrFcShort( 0x178 ),	/* Offset= 376 (808) */
/* 434 */	NdrFcLong( 0x14 ),	/* 20 */
/* 438 */	NdrFcShort( 0x190 ),	/* Offset= 400 (838) */
/* 440 */	NdrFcShort( 0xffffffff ),	/* Offset= -1 (439) */
/* 442 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 444 */	NdrFcShort( 0x4 ),	/* 4 */
/* 446 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 448 */	NdrFcShort( 0x0 ),	/* 0 */
/* 450 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 452 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 454 */	NdrFcShort( 0x4 ),	/* 4 */
/* 456 */	NdrFcShort( 0x0 ),	/* 0 */
/* 458 */	NdrFcShort( 0x1 ),	/* 1 */
/* 460 */	NdrFcShort( 0x0 ),	/* 0 */
/* 462 */	NdrFcShort( 0x0 ),	/* 0 */
/* 464 */	0x13, 0x0,	/* FC_OP */
/* 466 */	NdrFcShort( 0xfffffe42 ),	/* Offset= -446 (20) */
/* 468 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 470 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 472 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 474 */	NdrFcShort( 0x8 ),	/* 8 */
/* 476 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 478 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 480 */	NdrFcShort( 0x4 ),	/* 4 */
/* 482 */	NdrFcShort( 0x4 ),	/* 4 */
/* 484 */	0x11, 0x0,	/* FC_RP */
/* 486 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (442) */
/* 488 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 490 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 492 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 494 */	NdrFcShort( 0x0 ),	/* 0 */
/* 496 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 498 */	NdrFcShort( 0x0 ),	/* 0 */
/* 500 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 504 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 506 */	NdrFcShort( 0xffffff54 ),	/* Offset= -172 (334) */
/* 508 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 510 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 512 */	NdrFcShort( 0x8 ),	/* 8 */
/* 514 */	NdrFcShort( 0x0 ),	/* 0 */
/* 516 */	NdrFcShort( 0x6 ),	/* Offset= 6 (522) */
/* 518 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 520 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 522 */	
			0x11, 0x0,	/* FC_RP */
/* 524 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (492) */
/* 526 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 528 */	NdrFcShort( 0x0 ),	/* 0 */
/* 530 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 532 */	NdrFcShort( 0x0 ),	/* 0 */
/* 534 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 538 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 540 */	NdrFcShort( 0xffffff44 ),	/* Offset= -188 (352) */
/* 542 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 544 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 546 */	NdrFcShort( 0x8 ),	/* 8 */
/* 548 */	NdrFcShort( 0x0 ),	/* 0 */
/* 550 */	NdrFcShort( 0x6 ),	/* Offset= 6 (556) */
/* 552 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 554 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 556 */	
			0x11, 0x0,	/* FC_RP */
/* 558 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (526) */
/* 560 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 562 */	NdrFcShort( 0x4 ),	/* 4 */
/* 564 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 566 */	NdrFcShort( 0x0 ),	/* 0 */
/* 568 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 570 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 572 */	NdrFcShort( 0x4 ),	/* 4 */
/* 574 */	NdrFcShort( 0x0 ),	/* 0 */
/* 576 */	NdrFcShort( 0x1 ),	/* 1 */
/* 578 */	NdrFcShort( 0x0 ),	/* 0 */
/* 580 */	NdrFcShort( 0x0 ),	/* 0 */
/* 582 */	0x13, 0x0,	/* FC_OP */
/* 584 */	NdrFcShort( 0x17e ),	/* Offset= 382 (966) */
/* 586 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 588 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 590 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 592 */	NdrFcShort( 0x8 ),	/* 8 */
/* 594 */	NdrFcShort( 0x0 ),	/* 0 */
/* 596 */	NdrFcShort( 0x6 ),	/* Offset= 6 (602) */
/* 598 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 600 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 602 */	
			0x11, 0x0,	/* FC_RP */
/* 604 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (560) */
/* 606 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 608 */	NdrFcLong( 0x2f ),	/* 47 */
/* 612 */	NdrFcShort( 0x0 ),	/* 0 */
/* 614 */	NdrFcShort( 0x0 ),	/* 0 */
/* 616 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 618 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 620 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 622 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 624 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 626 */	NdrFcShort( 0x1 ),	/* 1 */
/* 628 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 630 */	NdrFcShort( 0x4 ),	/* 4 */
/* 632 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 634 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 636 */	NdrFcShort( 0x10 ),	/* 16 */
/* 638 */	NdrFcShort( 0x0 ),	/* 0 */
/* 640 */	NdrFcShort( 0xa ),	/* Offset= 10 (650) */
/* 642 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 644 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 646 */	NdrFcShort( 0xffffffd8 ),	/* Offset= -40 (606) */
/* 648 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 650 */	
			0x13, 0x0,	/* FC_OP */
/* 652 */	NdrFcShort( 0xffffffe4 ),	/* Offset= -28 (624) */
/* 654 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 656 */	NdrFcShort( 0x4 ),	/* 4 */
/* 658 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 660 */	NdrFcShort( 0x0 ),	/* 0 */
/* 662 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 664 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 666 */	NdrFcShort( 0x4 ),	/* 4 */
/* 668 */	NdrFcShort( 0x0 ),	/* 0 */
/* 670 */	NdrFcShort( 0x1 ),	/* 1 */
/* 672 */	NdrFcShort( 0x0 ),	/* 0 */
/* 674 */	NdrFcShort( 0x0 ),	/* 0 */
/* 676 */	0x13, 0x0,	/* FC_OP */
/* 678 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (634) */
/* 680 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 682 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 684 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 686 */	NdrFcShort( 0x8 ),	/* 8 */
/* 688 */	NdrFcShort( 0x0 ),	/* 0 */
/* 690 */	NdrFcShort( 0x6 ),	/* Offset= 6 (696) */
/* 692 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 694 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 696 */	
			0x11, 0x0,	/* FC_RP */
/* 698 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (654) */
/* 700 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 702 */	NdrFcShort( 0x8 ),	/* 8 */
/* 704 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/* 706 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 708 */	NdrFcShort( 0x10 ),	/* 16 */
/* 710 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 712 */	0x6,		/* FC_SHORT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 714 */	0x0,		/* 0 */
			NdrFcShort( 0xfffffff1 ),	/* Offset= -15 (700) */
			0x5b,		/* FC_END */
/* 718 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 720 */	NdrFcShort( 0x18 ),	/* 24 */
/* 722 */	NdrFcShort( 0x0 ),	/* 0 */
/* 724 */	NdrFcShort( 0xa ),	/* Offset= 10 (734) */
/* 726 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 728 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 730 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (706) */
/* 732 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 734 */	
			0x11, 0x0,	/* FC_RP */
/* 736 */	NdrFcShort( 0xffffff0c ),	/* Offset= -244 (492) */
/* 738 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 740 */	NdrFcShort( 0x1 ),	/* 1 */
/* 742 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 744 */	NdrFcShort( 0x0 ),	/* 0 */
/* 746 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 748 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 750 */	NdrFcShort( 0x8 ),	/* 8 */
/* 752 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 754 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 756 */	NdrFcShort( 0x4 ),	/* 4 */
/* 758 */	NdrFcShort( 0x4 ),	/* 4 */
/* 760 */	0x13, 0x0,	/* FC_OP */
/* 762 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (738) */
/* 764 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 766 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 768 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 770 */	NdrFcShort( 0x2 ),	/* 2 */
/* 772 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 774 */	NdrFcShort( 0x0 ),	/* 0 */
/* 776 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 778 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 780 */	NdrFcShort( 0x8 ),	/* 8 */
/* 782 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 784 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 786 */	NdrFcShort( 0x4 ),	/* 4 */
/* 788 */	NdrFcShort( 0x4 ),	/* 4 */
/* 790 */	0x13, 0x0,	/* FC_OP */
/* 792 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (768) */
/* 794 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 796 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 798 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 800 */	NdrFcShort( 0x4 ),	/* 4 */
/* 802 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 804 */	NdrFcShort( 0x0 ),	/* 0 */
/* 806 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 808 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 810 */	NdrFcShort( 0x8 ),	/* 8 */
/* 812 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 814 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 816 */	NdrFcShort( 0x4 ),	/* 4 */
/* 818 */	NdrFcShort( 0x4 ),	/* 4 */
/* 820 */	0x13, 0x0,	/* FC_OP */
/* 822 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (798) */
/* 824 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 826 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 828 */	
			0x1b,		/* FC_CARRAY */
			0x7,		/* 7 */
/* 830 */	NdrFcShort( 0x8 ),	/* 8 */
/* 832 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 834 */	NdrFcShort( 0x0 ),	/* 0 */
/* 836 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 838 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 840 */	NdrFcShort( 0x8 ),	/* 8 */
/* 842 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 844 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 846 */	NdrFcShort( 0x4 ),	/* 4 */
/* 848 */	NdrFcShort( 0x4 ),	/* 4 */
/* 850 */	0x13, 0x0,	/* FC_OP */
/* 852 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (828) */
/* 854 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 856 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 858 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 860 */	NdrFcShort( 0x8 ),	/* 8 */
/* 862 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 864 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 866 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 868 */	NdrFcShort( 0x8 ),	/* 8 */
/* 870 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 872 */	NdrFcShort( 0xffd8 ),	/* -40 */
/* 874 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 876 */	NdrFcShort( 0xffffffee ),	/* Offset= -18 (858) */
/* 878 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 880 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 882 */	NdrFcShort( 0x28 ),	/* 40 */
/* 884 */	NdrFcShort( 0xffffffee ),	/* Offset= -18 (866) */
/* 886 */	NdrFcShort( 0x0 ),	/* Offset= 0 (886) */
/* 888 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 890 */	0x38,		/* FC_ALIGNM4 */
			0x8,		/* FC_LONG */
/* 892 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 894 */	0x0,		/* 0 */
			NdrFcShort( 0xfffffdf7 ),	/* Offset= -521 (374) */
			0x5b,		/* FC_END */
/* 898 */	
			0x13, 0x0,	/* FC_OP */
/* 900 */	NdrFcShort( 0xfffffef6 ),	/* Offset= -266 (634) */
/* 902 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 904 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 906 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 908 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 910 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 912 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 914 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 916 */	0xa,		/* FC_FLOAT */
			0x5c,		/* FC_PAD */
/* 918 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 920 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 922 */	
			0x13, 0x0,	/* FC_OP */
/* 924 */	NdrFcShort( 0xfffffdac ),	/* Offset= -596 (328) */
/* 926 */	
			0x13, 0x10,	/* FC_OP */
/* 928 */	NdrFcShort( 0xfffffc66 ),	/* Offset= -922 (6) */
/* 930 */	
			0x13, 0x10,	/* FC_OP */
/* 932 */	NdrFcShort( 0xfffffdaa ),	/* Offset= -598 (334) */
/* 934 */	
			0x13, 0x10,	/* FC_OP */
/* 936 */	NdrFcShort( 0xfffffdb8 ),	/* Offset= -584 (352) */
/* 938 */	
			0x13, 0x10,	/* FC_OP */
/* 940 */	NdrFcShort( 0xfffffdc6 ),	/* Offset= -570 (370) */
/* 942 */	
			0x13, 0x10,	/* FC_OP */
/* 944 */	NdrFcShort( 0x2 ),	/* Offset= 2 (946) */
/* 946 */	
			0x13, 0x0,	/* FC_OP */
/* 948 */	NdrFcShort( 0xfffffc4c ),	/* Offset= -948 (0) */
/* 950 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 952 */	NdrFcShort( 0x10 ),	/* 16 */
/* 954 */	0x6,		/* FC_SHORT */
			0x2,		/* FC_CHAR */
/* 956 */	0x2,		/* FC_CHAR */
			0x38,		/* FC_ALIGNM4 */
/* 958 */	0x8,		/* FC_LONG */
			0x39,		/* FC_ALIGNM8 */
/* 960 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 962 */	
			0x13, 0x0,	/* FC_OP */
/* 964 */	NdrFcShort( 0xfffffff2 ),	/* Offset= -14 (950) */
/* 966 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 968 */	NdrFcShort( 0x20 ),	/* 32 */
/* 970 */	NdrFcShort( 0x0 ),	/* 0 */
/* 972 */	NdrFcShort( 0x0 ),	/* Offset= 0 (972) */
/* 974 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 976 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 978 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 980 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 982 */	NdrFcShort( 0xfffffc62 ),	/* Offset= -926 (56) */
/* 984 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 986 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 988 */	NdrFcShort( 0x1 ),	/* 1 */
/* 990 */	NdrFcShort( 0x10 ),	/* 16 */
/* 992 */	NdrFcShort( 0x0 ),	/* 0 */
/* 994 */	NdrFcShort( 0xfffffc52 ),	/* Offset= -942 (52) */
/* 996 */	
			0x12, 0x0,	/* FC_UP */
/* 998 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (966) */
/* 1000 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1002 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1004 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1006 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1008 */	NdrFcShort( 0xfffffff4 ),	/* Offset= -12 (996) */

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
