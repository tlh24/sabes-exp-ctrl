/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Mar 26 17:57:13 2008
 */
/* Compiler settings for C:\users\rebrik\work\Sabes\CP_LibertyTrack\Current\CP_LibertyTrackCom.idl:
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

#ifndef __CP_LibertyTrackCom_h__
#define __CP_LibertyTrackCom_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ILibertyTrack_FWD_DEFINED__
#define __ILibertyTrack_FWD_DEFINED__
typedef interface ILibertyTrack ILibertyTrack;
#endif 	/* __ILibertyTrack_FWD_DEFINED__ */


#ifndef __CP_LibertyClass_FWD_DEFINED__
#define __CP_LibertyClass_FWD_DEFINED__

#ifdef __cplusplus
typedef class CP_LibertyClass CP_LibertyClass;
#else
typedef struct CP_LibertyClass CP_LibertyClass;
#endif /* __cplusplus */

#endif 	/* __CP_LibertyClass_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ILibertyTrack_INTERFACE_DEFINED__
#define __ILibertyTrack_INTERFACE_DEFINED__

/* interface ILibertyTrack */
/* [unique][helpstring][oleautomation][dual][uuid][object] */ 


EXTERN_C const IID IID_ILibertyTrack;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ebd33068-ceb1-11d5-9c3e-0050da2a68c8")
    ILibertyTrack : public IDispatch
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

    typedef struct ILibertyTrackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ILibertyTrack __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ILibertyTrack __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ILibertyTrack __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ILibertyTrack __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ILibertyTrack __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ILibertyTrack __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ILibertyTrack __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetVersion )( 
            ILibertyTrack __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConnectTracker )( 
            ILibertyTrack __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DisconnectTracker )( 
            ILibertyTrack __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTrackerState )( 
            ILibertyTrack __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *piTrackerID,
            /* [out] */ long __RPC_FAR *piState);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFrameCount )( 
            ILibertyTrack __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pnFrames);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTimeScale )( 
            ILibertyTrack __RPC_FAR * This,
            /* [out] */ double __RPC_FAR *pdC0,
            /* [out] */ double __RPC_FAR *pdC1);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetTimeScale )( 
            ILibertyTrack __RPC_FAR * This,
            /* [in] */ double dC0,
            /* [in] */ double dC1);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTransformMatrix )( 
            ILibertyTrack __RPC_FAR * This,
            /* [defaultvalue][in] */ long iTransformIdx,
            /* [out] */ VARIANT __RPC_FAR *pvTransform);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetTransformMatrix )( 
            ILibertyTrack __RPC_FAR * This,
            /* [in] */ VARIANT vTransform,
            /* [defaultvalue][in] */ long iTransformIdx);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSensors )( 
            ILibertyTrack __RPC_FAR * This,
            /* [out] */ VARIANT __RPC_FAR *pvSensors);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSensors )( 
            ILibertyTrack __RPC_FAR * This,
            /* [in] */ VARIANT vSensors);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ActivateSensors )( 
            ILibertyTrack __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeactivateSensors )( 
            ILibertyTrack __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSensorsTransformIdx )( 
            ILibertyTrack __RPC_FAR * This,
            /* [out] */ VARIANT __RPC_FAR *pvTransformIdx);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSensorsTransformIdx )( 
            ILibertyTrack __RPC_FAR * This,
            /* [in] */ VARIANT vTransformIdx);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetBufferSize )( 
            ILibertyTrack __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pnFrames);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDataIndexLatest )( 
            ILibertyTrack __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *piDataIdx);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSensorLatest )( 
            ILibertyTrack __RPC_FAR * This,
            /* [in] */ long iSensorIdx,
            /* [defaultvalue][in] */ long nFrames,
            /* [out] */ long __RPC_FAR *piDataIdx,
            /* [out] */ VARIANT __RPC_FAR *pvTimeStampMs,
            /* [out] */ VARIANT __RPC_FAR *pvCoord,
            /* [out] */ VARIANT __RPC_FAR *pvVelocity);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSensorBuffered )( 
            ILibertyTrack __RPC_FAR * This,
            /* [in] */ long iSensorIdx,
            /* [in] */ long iDataIdx,
            /* [in] */ long nFrames,
            /* [out] */ VARIANT __RPC_FAR *pvTimeStampMs,
            /* [out] */ VARIANT __RPC_FAR *pvCoord,
            /* [out] */ VARIANT __RPC_FAR *pvVelocity);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAllSensorsLatest )( 
            ILibertyTrack __RPC_FAR * This,
            /* [defaultvalue][in] */ long nFrames,
            /* [out] */ long __RPC_FAR *piIdx,
            /* [out] */ VARIANT __RPC_FAR *pvTimeStampMs,
            /* [out] */ VARIANT __RPC_FAR *pvCoord,
            /* [out] */ VARIANT __RPC_FAR *pvVelocity);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAllSensorsBuffered )( 
            ILibertyTrack __RPC_FAR * This,
            /* [in] */ long iDataIdx,
            /* [in] */ long nFrames,
            /* [out] */ VARIANT __RPC_FAR *pvTimeStampMs,
            /* [out] */ VARIANT __RPC_FAR *pvCoord,
            /* [out] */ VARIANT __RPC_FAR *pvVelocity);
        
        END_INTERFACE
    } ILibertyTrackVtbl;

    interface ILibertyTrack
    {
        CONST_VTBL struct ILibertyTrackVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILibertyTrack_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILibertyTrack_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILibertyTrack_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ILibertyTrack_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ILibertyTrack_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ILibertyTrack_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ILibertyTrack_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ILibertyTrack_GetVersion(This,pVal)	\
    (This)->lpVtbl -> GetVersion(This,pVal)

#define ILibertyTrack_ConnectTracker(This)	\
    (This)->lpVtbl -> ConnectTracker(This)

#define ILibertyTrack_DisconnectTracker(This)	\
    (This)->lpVtbl -> DisconnectTracker(This)

#define ILibertyTrack_GetTrackerState(This,piTrackerID,piState)	\
    (This)->lpVtbl -> GetTrackerState(This,piTrackerID,piState)

#define ILibertyTrack_GetFrameCount(This,pnFrames)	\
    (This)->lpVtbl -> GetFrameCount(This,pnFrames)

#define ILibertyTrack_GetTimeScale(This,pdC0,pdC1)	\
    (This)->lpVtbl -> GetTimeScale(This,pdC0,pdC1)

#define ILibertyTrack_SetTimeScale(This,dC0,dC1)	\
    (This)->lpVtbl -> SetTimeScale(This,dC0,dC1)

#define ILibertyTrack_GetTransformMatrix(This,iTransformIdx,pvTransform)	\
    (This)->lpVtbl -> GetTransformMatrix(This,iTransformIdx,pvTransform)

#define ILibertyTrack_SetTransformMatrix(This,vTransform,iTransformIdx)	\
    (This)->lpVtbl -> SetTransformMatrix(This,vTransform,iTransformIdx)

#define ILibertyTrack_GetSensors(This,pvSensors)	\
    (This)->lpVtbl -> GetSensors(This,pvSensors)

#define ILibertyTrack_SetSensors(This,vSensors)	\
    (This)->lpVtbl -> SetSensors(This,vSensors)

#define ILibertyTrack_ActivateSensors(This)	\
    (This)->lpVtbl -> ActivateSensors(This)

#define ILibertyTrack_DeactivateSensors(This)	\
    (This)->lpVtbl -> DeactivateSensors(This)

#define ILibertyTrack_GetSensorsTransformIdx(This,pvTransformIdx)	\
    (This)->lpVtbl -> GetSensorsTransformIdx(This,pvTransformIdx)

#define ILibertyTrack_SetSensorsTransformIdx(This,vTransformIdx)	\
    (This)->lpVtbl -> SetSensorsTransformIdx(This,vTransformIdx)

#define ILibertyTrack_GetBufferSize(This,pnFrames)	\
    (This)->lpVtbl -> GetBufferSize(This,pnFrames)

#define ILibertyTrack_GetDataIndexLatest(This,piDataIdx)	\
    (This)->lpVtbl -> GetDataIndexLatest(This,piDataIdx)

#define ILibertyTrack_GetSensorLatest(This,iSensorIdx,nFrames,piDataIdx,pvTimeStampMs,pvCoord,pvVelocity)	\
    (This)->lpVtbl -> GetSensorLatest(This,iSensorIdx,nFrames,piDataIdx,pvTimeStampMs,pvCoord,pvVelocity)

#define ILibertyTrack_GetSensorBuffered(This,iSensorIdx,iDataIdx,nFrames,pvTimeStampMs,pvCoord,pvVelocity)	\
    (This)->lpVtbl -> GetSensorBuffered(This,iSensorIdx,iDataIdx,nFrames,pvTimeStampMs,pvCoord,pvVelocity)

#define ILibertyTrack_GetAllSensorsLatest(This,nFrames,piIdx,pvTimeStampMs,pvCoord,pvVelocity)	\
    (This)->lpVtbl -> GetAllSensorsLatest(This,nFrames,piIdx,pvTimeStampMs,pvCoord,pvVelocity)

#define ILibertyTrack_GetAllSensorsBuffered(This,iDataIdx,nFrames,pvTimeStampMs,pvCoord,pvVelocity)	\
    (This)->lpVtbl -> GetAllSensorsBuffered(This,iDataIdx,nFrames,pvTimeStampMs,pvCoord,pvVelocity)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ILibertyTrack_GetVersion_Proxy( 
    ILibertyTrack __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ILibertyTrack_GetVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ILibertyTrack_ConnectTracker_Proxy( 
    ILibertyTrack __RPC_FAR * This);


void __RPC_STUB ILibertyTrack_ConnectTracker_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ILibertyTrack_DisconnectTracker_Proxy( 
    ILibertyTrack __RPC_FAR * This);


void __RPC_STUB ILibertyTrack_DisconnectTracker_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ILibertyTrack_GetTrackerState_Proxy( 
    ILibertyTrack __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *piTrackerID,
    /* [out] */ long __RPC_FAR *piState);


void __RPC_STUB ILibertyTrack_GetTrackerState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ILibertyTrack_GetFrameCount_Proxy( 
    ILibertyTrack __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pnFrames);


void __RPC_STUB ILibertyTrack_GetFrameCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ILibertyTrack_GetTimeScale_Proxy( 
    ILibertyTrack __RPC_FAR * This,
    /* [out] */ double __RPC_FAR *pdC0,
    /* [out] */ double __RPC_FAR *pdC1);


void __RPC_STUB ILibertyTrack_GetTimeScale_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ILibertyTrack_SetTimeScale_Proxy( 
    ILibertyTrack __RPC_FAR * This,
    /* [in] */ double dC0,
    /* [in] */ double dC1);


void __RPC_STUB ILibertyTrack_SetTimeScale_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ILibertyTrack_GetTransformMatrix_Proxy( 
    ILibertyTrack __RPC_FAR * This,
    /* [defaultvalue][in] */ long iTransformIdx,
    /* [out] */ VARIANT __RPC_FAR *pvTransform);


void __RPC_STUB ILibertyTrack_GetTransformMatrix_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ILibertyTrack_SetTransformMatrix_Proxy( 
    ILibertyTrack __RPC_FAR * This,
    /* [in] */ VARIANT vTransform,
    /* [defaultvalue][in] */ long iTransformIdx);


void __RPC_STUB ILibertyTrack_SetTransformMatrix_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ILibertyTrack_GetSensors_Proxy( 
    ILibertyTrack __RPC_FAR * This,
    /* [out] */ VARIANT __RPC_FAR *pvSensors);


void __RPC_STUB ILibertyTrack_GetSensors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ILibertyTrack_SetSensors_Proxy( 
    ILibertyTrack __RPC_FAR * This,
    /* [in] */ VARIANT vSensors);


void __RPC_STUB ILibertyTrack_SetSensors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ILibertyTrack_ActivateSensors_Proxy( 
    ILibertyTrack __RPC_FAR * This);


void __RPC_STUB ILibertyTrack_ActivateSensors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ILibertyTrack_DeactivateSensors_Proxy( 
    ILibertyTrack __RPC_FAR * This);


void __RPC_STUB ILibertyTrack_DeactivateSensors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ILibertyTrack_GetSensorsTransformIdx_Proxy( 
    ILibertyTrack __RPC_FAR * This,
    /* [out] */ VARIANT __RPC_FAR *pvTransformIdx);


void __RPC_STUB ILibertyTrack_GetSensorsTransformIdx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ILibertyTrack_SetSensorsTransformIdx_Proxy( 
    ILibertyTrack __RPC_FAR * This,
    /* [in] */ VARIANT vTransformIdx);


void __RPC_STUB ILibertyTrack_SetSensorsTransformIdx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ILibertyTrack_GetBufferSize_Proxy( 
    ILibertyTrack __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pnFrames);


void __RPC_STUB ILibertyTrack_GetBufferSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ILibertyTrack_GetDataIndexLatest_Proxy( 
    ILibertyTrack __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *piDataIdx);


void __RPC_STUB ILibertyTrack_GetDataIndexLatest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ILibertyTrack_GetSensorLatest_Proxy( 
    ILibertyTrack __RPC_FAR * This,
    /* [in] */ long iSensorIdx,
    /* [defaultvalue][in] */ long nFrames,
    /* [out] */ long __RPC_FAR *piDataIdx,
    /* [out] */ VARIANT __RPC_FAR *pvTimeStampMs,
    /* [out] */ VARIANT __RPC_FAR *pvCoord,
    /* [out] */ VARIANT __RPC_FAR *pvVelocity);


void __RPC_STUB ILibertyTrack_GetSensorLatest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ILibertyTrack_GetSensorBuffered_Proxy( 
    ILibertyTrack __RPC_FAR * This,
    /* [in] */ long iSensorIdx,
    /* [in] */ long iDataIdx,
    /* [in] */ long nFrames,
    /* [out] */ VARIANT __RPC_FAR *pvTimeStampMs,
    /* [out] */ VARIANT __RPC_FAR *pvCoord,
    /* [out] */ VARIANT __RPC_FAR *pvVelocity);


void __RPC_STUB ILibertyTrack_GetSensorBuffered_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ILibertyTrack_GetAllSensorsLatest_Proxy( 
    ILibertyTrack __RPC_FAR * This,
    /* [defaultvalue][in] */ long nFrames,
    /* [out] */ long __RPC_FAR *piIdx,
    /* [out] */ VARIANT __RPC_FAR *pvTimeStampMs,
    /* [out] */ VARIANT __RPC_FAR *pvCoord,
    /* [out] */ VARIANT __RPC_FAR *pvVelocity);


void __RPC_STUB ILibertyTrack_GetAllSensorsLatest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ILibertyTrack_GetAllSensorsBuffered_Proxy( 
    ILibertyTrack __RPC_FAR * This,
    /* [in] */ long iDataIdx,
    /* [in] */ long nFrames,
    /* [out] */ VARIANT __RPC_FAR *pvTimeStampMs,
    /* [out] */ VARIANT __RPC_FAR *pvCoord,
    /* [out] */ VARIANT __RPC_FAR *pvVelocity);


void __RPC_STUB ILibertyTrack_GetAllSensorsBuffered_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ILibertyTrack_INTERFACE_DEFINED__ */



#ifndef __CP_LibertyTrackLib_LIBRARY_DEFINED__
#define __CP_LibertyTrackLib_LIBRARY_DEFINED__

/* library CP_LibertyTrackLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_CP_LibertyTrackLib;

EXTERN_C const CLSID CLSID_CP_LibertyClass;

#ifdef __cplusplus

class DECLSPEC_UUID("ebd33060-ceb1-11d5-9c3e-0050da2a68c8")
CP_LibertyClass;
#endif
#endif /* __CP_LibertyTrackLib_LIBRARY_DEFINED__ */

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
