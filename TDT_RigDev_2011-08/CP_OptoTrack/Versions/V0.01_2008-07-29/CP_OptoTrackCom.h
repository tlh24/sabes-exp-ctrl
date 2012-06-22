/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Jul 29 19:29:49 2008
 */
/* Compiler settings for C:\users\rebrik\work\Sabes\CP_OptoTrack\Current\CP_OptoTrackCom.idl:
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
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetVersion( 
            /* [out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ConnectTracker( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DisconnectTracker( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetTrackerState( 
            /* [out] */ long __RPC_FAR *piTrackerID,
            /* [out] */ long __RPC_FAR *piState) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetFrameCount( 
            /* [out] */ long __RPC_FAR *pnFrames) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetTimeScale( 
            /* [out] */ double __RPC_FAR *pdC0,
            /* [out] */ double __RPC_FAR *pdC1) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetTimeScale( 
            /* [in] */ double dC0,
            /* [in] */ double dC1) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetTransformMatrix( 
            /* [defaultvalue][in] */ long iTransformIdx,
            /* [out] */ VARIANT __RPC_FAR *pvTransform) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetTransformMatrix( 
            /* [in] */ VARIANT vTransform,
            /* [defaultvalue][in] */ long iTransformIdx = 1) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetSensors( 
            /* [out] */ VARIANT __RPC_FAR *pvSensors) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetSensors( 
            /* [in] */ VARIANT vSensors) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ActivateSensors( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeactivateSensors( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetSensorsTransformIdx( 
            /* [out] */ VARIANT __RPC_FAR *pvTransformIdx) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetSensorsTransformIdx( 
            /* [in] */ VARIANT vTransformIdx) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetBufferSize( 
            /* [out] */ long __RPC_FAR *pnFrames) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetDataIndexLatest( 
            /* [out] */ long __RPC_FAR *piDataIdx) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetSensorLatest( 
            /* [in] */ long iSensorIdx,
            /* [defaultvalue][in] */ long nFrames,
            /* [out] */ long __RPC_FAR *piDataIdx,
            /* [out] */ VARIANT __RPC_FAR *pvTimeStampMs,
            /* [out] */ VARIANT __RPC_FAR *pvCoord,
            /* [out] */ VARIANT __RPC_FAR *pvVelocity) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetSensorBuffered( 
            /* [in] */ long iSensorIdx,
            /* [in] */ long iDataIdx,
            /* [in] */ long nFrames,
            /* [out] */ VARIANT __RPC_FAR *pvTimeStampMs,
            /* [out] */ VARIANT __RPC_FAR *pvCoord,
            /* [out] */ VARIANT __RPC_FAR *pvVelocity) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetAllSensorsLatest( 
            /* [defaultvalue][in] */ long nFrames,
            /* [out] */ long __RPC_FAR *piIdx,
            /* [out] */ VARIANT __RPC_FAR *pvTimeStampMs,
            /* [out] */ VARIANT __RPC_FAR *pvCoord,
            /* [out] */ VARIANT __RPC_FAR *pvVelocity) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetAllSensorsBuffered( 
            /* [in] */ long iDataIdx,
            /* [in] */ long nFrames,
            /* [out] */ VARIANT __RPC_FAR *pvTimeStampMs,
            /* [out] */ VARIANT __RPC_FAR *pvCoord,
            /* [out] */ VARIANT __RPC_FAR *pvVelocity) = 0;
        
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
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetVersion )( 
            IOptoTrack __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConnectTracker )( 
            IOptoTrack __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DisconnectTracker )( 
            IOptoTrack __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTrackerState )( 
            IOptoTrack __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *piTrackerID,
            /* [out] */ long __RPC_FAR *piState);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFrameCount )( 
            IOptoTrack __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pnFrames);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTimeScale )( 
            IOptoTrack __RPC_FAR * This,
            /* [out] */ double __RPC_FAR *pdC0,
            /* [out] */ double __RPC_FAR *pdC1);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetTimeScale )( 
            IOptoTrack __RPC_FAR * This,
            /* [in] */ double dC0,
            /* [in] */ double dC1);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTransformMatrix )( 
            IOptoTrack __RPC_FAR * This,
            /* [defaultvalue][in] */ long iTransformIdx,
            /* [out] */ VARIANT __RPC_FAR *pvTransform);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetTransformMatrix )( 
            IOptoTrack __RPC_FAR * This,
            /* [in] */ VARIANT vTransform,
            /* [defaultvalue][in] */ long iTransformIdx);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSensors )( 
            IOptoTrack __RPC_FAR * This,
            /* [out] */ VARIANT __RPC_FAR *pvSensors);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSensors )( 
            IOptoTrack __RPC_FAR * This,
            /* [in] */ VARIANT vSensors);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ActivateSensors )( 
            IOptoTrack __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeactivateSensors )( 
            IOptoTrack __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSensorsTransformIdx )( 
            IOptoTrack __RPC_FAR * This,
            /* [out] */ VARIANT __RPC_FAR *pvTransformIdx);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSensorsTransformIdx )( 
            IOptoTrack __RPC_FAR * This,
            /* [in] */ VARIANT vTransformIdx);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetBufferSize )( 
            IOptoTrack __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pnFrames);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDataIndexLatest )( 
            IOptoTrack __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *piDataIdx);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSensorLatest )( 
            IOptoTrack __RPC_FAR * This,
            /* [in] */ long iSensorIdx,
            /* [defaultvalue][in] */ long nFrames,
            /* [out] */ long __RPC_FAR *piDataIdx,
            /* [out] */ VARIANT __RPC_FAR *pvTimeStampMs,
            /* [out] */ VARIANT __RPC_FAR *pvCoord,
            /* [out] */ VARIANT __RPC_FAR *pvVelocity);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSensorBuffered )( 
            IOptoTrack __RPC_FAR * This,
            /* [in] */ long iSensorIdx,
            /* [in] */ long iDataIdx,
            /* [in] */ long nFrames,
            /* [out] */ VARIANT __RPC_FAR *pvTimeStampMs,
            /* [out] */ VARIANT __RPC_FAR *pvCoord,
            /* [out] */ VARIANT __RPC_FAR *pvVelocity);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAllSensorsLatest )( 
            IOptoTrack __RPC_FAR * This,
            /* [defaultvalue][in] */ long nFrames,
            /* [out] */ long __RPC_FAR *piIdx,
            /* [out] */ VARIANT __RPC_FAR *pvTimeStampMs,
            /* [out] */ VARIANT __RPC_FAR *pvCoord,
            /* [out] */ VARIANT __RPC_FAR *pvVelocity);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAllSensorsBuffered )( 
            IOptoTrack __RPC_FAR * This,
            /* [in] */ long iDataIdx,
            /* [in] */ long nFrames,
            /* [out] */ VARIANT __RPC_FAR *pvTimeStampMs,
            /* [out] */ VARIANT __RPC_FAR *pvCoord,
            /* [out] */ VARIANT __RPC_FAR *pvVelocity);
        
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


#define IOptoTrack_GetVersion(This,pVal)	\
    (This)->lpVtbl -> GetVersion(This,pVal)

#define IOptoTrack_ConnectTracker(This)	\
    (This)->lpVtbl -> ConnectTracker(This)

#define IOptoTrack_DisconnectTracker(This)	\
    (This)->lpVtbl -> DisconnectTracker(This)

#define IOptoTrack_GetTrackerState(This,piTrackerID,piState)	\
    (This)->lpVtbl -> GetTrackerState(This,piTrackerID,piState)

#define IOptoTrack_GetFrameCount(This,pnFrames)	\
    (This)->lpVtbl -> GetFrameCount(This,pnFrames)

#define IOptoTrack_GetTimeScale(This,pdC0,pdC1)	\
    (This)->lpVtbl -> GetTimeScale(This,pdC0,pdC1)

#define IOptoTrack_SetTimeScale(This,dC0,dC1)	\
    (This)->lpVtbl -> SetTimeScale(This,dC0,dC1)

#define IOptoTrack_GetTransformMatrix(This,iTransformIdx,pvTransform)	\
    (This)->lpVtbl -> GetTransformMatrix(This,iTransformIdx,pvTransform)

#define IOptoTrack_SetTransformMatrix(This,vTransform,iTransformIdx)	\
    (This)->lpVtbl -> SetTransformMatrix(This,vTransform,iTransformIdx)

#define IOptoTrack_GetSensors(This,pvSensors)	\
    (This)->lpVtbl -> GetSensors(This,pvSensors)

#define IOptoTrack_SetSensors(This,vSensors)	\
    (This)->lpVtbl -> SetSensors(This,vSensors)

#define IOptoTrack_ActivateSensors(This)	\
    (This)->lpVtbl -> ActivateSensors(This)

#define IOptoTrack_DeactivateSensors(This)	\
    (This)->lpVtbl -> DeactivateSensors(This)

#define IOptoTrack_GetSensorsTransformIdx(This,pvTransformIdx)	\
    (This)->lpVtbl -> GetSensorsTransformIdx(This,pvTransformIdx)

#define IOptoTrack_SetSensorsTransformIdx(This,vTransformIdx)	\
    (This)->lpVtbl -> SetSensorsTransformIdx(This,vTransformIdx)

#define IOptoTrack_GetBufferSize(This,pnFrames)	\
    (This)->lpVtbl -> GetBufferSize(This,pnFrames)

#define IOptoTrack_GetDataIndexLatest(This,piDataIdx)	\
    (This)->lpVtbl -> GetDataIndexLatest(This,piDataIdx)

#define IOptoTrack_GetSensorLatest(This,iSensorIdx,nFrames,piDataIdx,pvTimeStampMs,pvCoord,pvVelocity)	\
    (This)->lpVtbl -> GetSensorLatest(This,iSensorIdx,nFrames,piDataIdx,pvTimeStampMs,pvCoord,pvVelocity)

#define IOptoTrack_GetSensorBuffered(This,iSensorIdx,iDataIdx,nFrames,pvTimeStampMs,pvCoord,pvVelocity)	\
    (This)->lpVtbl -> GetSensorBuffered(This,iSensorIdx,iDataIdx,nFrames,pvTimeStampMs,pvCoord,pvVelocity)

#define IOptoTrack_GetAllSensorsLatest(This,nFrames,piIdx,pvTimeStampMs,pvCoord,pvVelocity)	\
    (This)->lpVtbl -> GetAllSensorsLatest(This,nFrames,piIdx,pvTimeStampMs,pvCoord,pvVelocity)

#define IOptoTrack_GetAllSensorsBuffered(This,iDataIdx,nFrames,pvTimeStampMs,pvCoord,pvVelocity)	\
    (This)->lpVtbl -> GetAllSensorsBuffered(This,iDataIdx,nFrames,pvTimeStampMs,pvCoord,pvVelocity)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IOptoTrack_GetVersion_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IOptoTrack_GetVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IOptoTrack_ConnectTracker_Proxy( 
    IOptoTrack __RPC_FAR * This);


void __RPC_STUB IOptoTrack_ConnectTracker_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IOptoTrack_DisconnectTracker_Proxy( 
    IOptoTrack __RPC_FAR * This);


void __RPC_STUB IOptoTrack_DisconnectTracker_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IOptoTrack_GetTrackerState_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *piTrackerID,
    /* [out] */ long __RPC_FAR *piState);


void __RPC_STUB IOptoTrack_GetTrackerState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IOptoTrack_GetFrameCount_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pnFrames);


void __RPC_STUB IOptoTrack_GetFrameCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IOptoTrack_GetTimeScale_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [out] */ double __RPC_FAR *pdC0,
    /* [out] */ double __RPC_FAR *pdC1);


void __RPC_STUB IOptoTrack_GetTimeScale_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IOptoTrack_SetTimeScale_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [in] */ double dC0,
    /* [in] */ double dC1);


void __RPC_STUB IOptoTrack_SetTimeScale_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IOptoTrack_GetTransformMatrix_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [defaultvalue][in] */ long iTransformIdx,
    /* [out] */ VARIANT __RPC_FAR *pvTransform);


void __RPC_STUB IOptoTrack_GetTransformMatrix_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IOptoTrack_SetTransformMatrix_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [in] */ VARIANT vTransform,
    /* [defaultvalue][in] */ long iTransformIdx);


void __RPC_STUB IOptoTrack_SetTransformMatrix_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IOptoTrack_GetSensors_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [out] */ VARIANT __RPC_FAR *pvSensors);


void __RPC_STUB IOptoTrack_GetSensors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IOptoTrack_SetSensors_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [in] */ VARIANT vSensors);


void __RPC_STUB IOptoTrack_SetSensors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IOptoTrack_ActivateSensors_Proxy( 
    IOptoTrack __RPC_FAR * This);


void __RPC_STUB IOptoTrack_ActivateSensors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IOptoTrack_DeactivateSensors_Proxy( 
    IOptoTrack __RPC_FAR * This);


void __RPC_STUB IOptoTrack_DeactivateSensors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IOptoTrack_GetSensorsTransformIdx_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [out] */ VARIANT __RPC_FAR *pvTransformIdx);


void __RPC_STUB IOptoTrack_GetSensorsTransformIdx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IOptoTrack_SetSensorsTransformIdx_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [in] */ VARIANT vTransformIdx);


void __RPC_STUB IOptoTrack_SetSensorsTransformIdx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IOptoTrack_GetBufferSize_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pnFrames);


void __RPC_STUB IOptoTrack_GetBufferSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IOptoTrack_GetDataIndexLatest_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *piDataIdx);


void __RPC_STUB IOptoTrack_GetDataIndexLatest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IOptoTrack_GetSensorLatest_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [in] */ long iSensorIdx,
    /* [defaultvalue][in] */ long nFrames,
    /* [out] */ long __RPC_FAR *piDataIdx,
    /* [out] */ VARIANT __RPC_FAR *pvTimeStampMs,
    /* [out] */ VARIANT __RPC_FAR *pvCoord,
    /* [out] */ VARIANT __RPC_FAR *pvVelocity);


void __RPC_STUB IOptoTrack_GetSensorLatest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IOptoTrack_GetSensorBuffered_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [in] */ long iSensorIdx,
    /* [in] */ long iDataIdx,
    /* [in] */ long nFrames,
    /* [out] */ VARIANT __RPC_FAR *pvTimeStampMs,
    /* [out] */ VARIANT __RPC_FAR *pvCoord,
    /* [out] */ VARIANT __RPC_FAR *pvVelocity);


void __RPC_STUB IOptoTrack_GetSensorBuffered_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IOptoTrack_GetAllSensorsLatest_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [defaultvalue][in] */ long nFrames,
    /* [out] */ long __RPC_FAR *piIdx,
    /* [out] */ VARIANT __RPC_FAR *pvTimeStampMs,
    /* [out] */ VARIANT __RPC_FAR *pvCoord,
    /* [out] */ VARIANT __RPC_FAR *pvVelocity);


void __RPC_STUB IOptoTrack_GetAllSensorsLatest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IOptoTrack_GetAllSensorsBuffered_Proxy( 
    IOptoTrack __RPC_FAR * This,
    /* [in] */ long iDataIdx,
    /* [in] */ long nFrames,
    /* [out] */ VARIANT __RPC_FAR *pvTimeStampMs,
    /* [out] */ VARIANT __RPC_FAR *pvCoord,
    /* [out] */ VARIANT __RPC_FAR *pvVelocity);


void __RPC_STUB IOptoTrack_GetAllSensorsBuffered_Stub(
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

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long __RPC_FAR *, unsigned long            , VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long __RPC_FAR *, VARIANT __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
