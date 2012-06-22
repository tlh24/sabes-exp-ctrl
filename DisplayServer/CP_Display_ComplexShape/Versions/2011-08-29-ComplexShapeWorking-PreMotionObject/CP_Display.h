/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Aug 30 22:58:19 2011
 */
/* Compiler settings for D:\Sabes\Dropbox\2011-LabCode (1)\DisplayServer\CP_Display_ComplexShape\Versions\2011-08-29-ComplexShapeWorking-PreMotionObject\CP_Display.idl:
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

#ifndef __CP_Display_h__
#define __CP_Display_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IVMain_FWD_DEFINED__
#define __IVMain_FWD_DEFINED__
typedef interface IVMain IVMain;
#endif 	/* __IVMain_FWD_DEFINED__ */


#ifndef __IVDisk_FWD_DEFINED__
#define __IVDisk_FWD_DEFINED__
typedef interface IVDisk IVDisk;
#endif 	/* __IVDisk_FWD_DEFINED__ */


#ifndef __IVPolygon_FWD_DEFINED__
#define __IVPolygon_FWD_DEFINED__
typedef interface IVPolygon IVPolygon;
#endif 	/* __IVPolygon_FWD_DEFINED__ */


#ifndef __IVText_FWD_DEFINED__
#define __IVText_FWD_DEFINED__
typedef interface IVText IVText;
#endif 	/* __IVText_FWD_DEFINED__ */


#ifndef __IVMouse_FWD_DEFINED__
#define __IVMouse_FWD_DEFINED__
typedef interface IVMouse IVMouse;
#endif 	/* __IVMouse_FWD_DEFINED__ */


#ifndef __IVComplexShape_FWD_DEFINED__
#define __IVComplexShape_FWD_DEFINED__
typedef interface IVComplexShape IVComplexShape;
#endif 	/* __IVComplexShape_FWD_DEFINED__ */


#ifndef __VMain_FWD_DEFINED__
#define __VMain_FWD_DEFINED__

#ifdef __cplusplus
typedef class VMain VMain;
#else
typedef struct VMain VMain;
#endif /* __cplusplus */

#endif 	/* __VMain_FWD_DEFINED__ */


#ifndef __VDisk_FWD_DEFINED__
#define __VDisk_FWD_DEFINED__

#ifdef __cplusplus
typedef class VDisk VDisk;
#else
typedef struct VDisk VDisk;
#endif /* __cplusplus */

#endif 	/* __VDisk_FWD_DEFINED__ */


#ifndef __VPolygon_FWD_DEFINED__
#define __VPolygon_FWD_DEFINED__

#ifdef __cplusplus
typedef class VPolygon VPolygon;
#else
typedef struct VPolygon VPolygon;
#endif /* __cplusplus */

#endif 	/* __VPolygon_FWD_DEFINED__ */


#ifndef __VText_FWD_DEFINED__
#define __VText_FWD_DEFINED__

#ifdef __cplusplus
typedef class VText VText;
#else
typedef struct VText VText;
#endif /* __cplusplus */

#endif 	/* __VText_FWD_DEFINED__ */


#ifndef __VMouse_FWD_DEFINED__
#define __VMouse_FWD_DEFINED__

#ifdef __cplusplus
typedef class VMouse VMouse;
#else
typedef struct VMouse VMouse;
#endif /* __cplusplus */

#endif 	/* __VMouse_FWD_DEFINED__ */


#ifndef __VComplexShape_FWD_DEFINED__
#define __VComplexShape_FWD_DEFINED__

#ifdef __cplusplus
typedef class VComplexShape VComplexShape;
#else
typedef struct VComplexShape VComplexShape;
#endif /* __cplusplus */

#endif 	/* __VComplexShape_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IVMain_INTERFACE_DEFINED__
#define __IVMain_INTERFACE_DEFINED__

/* interface IVMain */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IVMain;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ebd3308c-ceb1-11d5-9c3e-0050da2a68c8")
    IVMain : public IDispatch
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetVersion( 
            /* [out] */ BSTR __RPC_FAR *pbstVersion) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE StartSync( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE StopSync( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetFrameCount( 
            /* [out] */ long __RPC_FAR *pnFrames) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetTransformMatrix( 
            /* [out] */ VARIANT __RPC_FAR *pvMatrix) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetTransformMatrix( 
            /* [in] */ VARIANT vMatrix) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetTimeScale( 
            /* [out] */ double __RPC_FAR *pdC0,
            /* [out] */ double __RPC_FAR *pdC1) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetTimeScale( 
            /* [in] */ double dC0,
            /* [in] */ double dC1) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE StartBatchDraw( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FinishBatchDraw( 
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE MoveGroup( 
            /* [in] */ long iGroupID,
            /* [in] */ VARIANT vXY,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ScaleGroup( 
            /* [in] */ long iGroupID,
            /* [in] */ double dScale,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RotateGroup( 
            /* [in] */ long iGroupID,
            /* [in] */ double dAngle,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE HideGroup( 
            /* [in] */ long iGroupID,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ShowGroup( 
            /* [in] */ long iGroupID,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ResetEventLog( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetEventLog( 
            /* [out] */ VARIANT __RPC_FAR *pvLogID,
            /* [out] */ VARIANT __RPC_FAR *pvTimeStampMs) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVMainVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IVMain __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IVMain __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IVMain __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IVMain __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IVMain __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IVMain __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IVMain __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetVersion )( 
            IVMain __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *pbstVersion);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StartSync )( 
            IVMain __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StopSync )( 
            IVMain __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFrameCount )( 
            IVMain __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pnFrames);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTransformMatrix )( 
            IVMain __RPC_FAR * This,
            /* [out] */ VARIANT __RPC_FAR *pvMatrix);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetTransformMatrix )( 
            IVMain __RPC_FAR * This,
            /* [in] */ VARIANT vMatrix);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTimeScale )( 
            IVMain __RPC_FAR * This,
            /* [out] */ double __RPC_FAR *pdC0,
            /* [out] */ double __RPC_FAR *pdC1);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetTimeScale )( 
            IVMain __RPC_FAR * This,
            /* [in] */ double dC0,
            /* [in] */ double dC1);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StartBatchDraw )( 
            IVMain __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FinishBatchDraw )( 
            IVMain __RPC_FAR * This,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MoveGroup )( 
            IVMain __RPC_FAR * This,
            /* [in] */ long iGroupID,
            /* [in] */ VARIANT vXY,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ScaleGroup )( 
            IVMain __RPC_FAR * This,
            /* [in] */ long iGroupID,
            /* [in] */ double dScale,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RotateGroup )( 
            IVMain __RPC_FAR * This,
            /* [in] */ long iGroupID,
            /* [in] */ double dAngle,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *HideGroup )( 
            IVMain __RPC_FAR * This,
            /* [in] */ long iGroupID,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShowGroup )( 
            IVMain __RPC_FAR * This,
            /* [in] */ long iGroupID,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetEventLog )( 
            IVMain __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEventLog )( 
            IVMain __RPC_FAR * This,
            /* [out] */ VARIANT __RPC_FAR *pvLogID,
            /* [out] */ VARIANT __RPC_FAR *pvTimeStampMs);
        
        END_INTERFACE
    } IVMainVtbl;

    interface IVMain
    {
        CONST_VTBL struct IVMainVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVMain_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVMain_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVMain_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVMain_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IVMain_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IVMain_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IVMain_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IVMain_GetVersion(This,pbstVersion)	\
    (This)->lpVtbl -> GetVersion(This,pbstVersion)

#define IVMain_StartSync(This)	\
    (This)->lpVtbl -> StartSync(This)

#define IVMain_StopSync(This)	\
    (This)->lpVtbl -> StopSync(This)

#define IVMain_GetFrameCount(This,pnFrames)	\
    (This)->lpVtbl -> GetFrameCount(This,pnFrames)

#define IVMain_GetTransformMatrix(This,pvMatrix)	\
    (This)->lpVtbl -> GetTransformMatrix(This,pvMatrix)

#define IVMain_SetTransformMatrix(This,vMatrix)	\
    (This)->lpVtbl -> SetTransformMatrix(This,vMatrix)

#define IVMain_GetTimeScale(This,pdC0,pdC1)	\
    (This)->lpVtbl -> GetTimeScale(This,pdC0,pdC1)

#define IVMain_SetTimeScale(This,dC0,dC1)	\
    (This)->lpVtbl -> SetTimeScale(This,dC0,dC1)

#define IVMain_StartBatchDraw(This)	\
    (This)->lpVtbl -> StartBatchDraw(This)

#define IVMain_FinishBatchDraw(This,iLogID)	\
    (This)->lpVtbl -> FinishBatchDraw(This,iLogID)

#define IVMain_MoveGroup(This,iGroupID,vXY,iLogID)	\
    (This)->lpVtbl -> MoveGroup(This,iGroupID,vXY,iLogID)

#define IVMain_ScaleGroup(This,iGroupID,dScale,iLogID)	\
    (This)->lpVtbl -> ScaleGroup(This,iGroupID,dScale,iLogID)

#define IVMain_RotateGroup(This,iGroupID,dAngle,iLogID)	\
    (This)->lpVtbl -> RotateGroup(This,iGroupID,dAngle,iLogID)

#define IVMain_HideGroup(This,iGroupID,iLogID)	\
    (This)->lpVtbl -> HideGroup(This,iGroupID,iLogID)

#define IVMain_ShowGroup(This,iGroupID,iLogID)	\
    (This)->lpVtbl -> ShowGroup(This,iGroupID,iLogID)

#define IVMain_ResetEventLog(This)	\
    (This)->lpVtbl -> ResetEventLog(This)

#define IVMain_GetEventLog(This,pvLogID,pvTimeStampMs)	\
    (This)->lpVtbl -> GetEventLog(This,pvLogID,pvTimeStampMs)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVMain_GetVersion_Proxy( 
    IVMain __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *pbstVersion);


void __RPC_STUB IVMain_GetVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVMain_StartSync_Proxy( 
    IVMain __RPC_FAR * This);


void __RPC_STUB IVMain_StartSync_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVMain_StopSync_Proxy( 
    IVMain __RPC_FAR * This);


void __RPC_STUB IVMain_StopSync_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVMain_GetFrameCount_Proxy( 
    IVMain __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pnFrames);


void __RPC_STUB IVMain_GetFrameCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVMain_GetTransformMatrix_Proxy( 
    IVMain __RPC_FAR * This,
    /* [out] */ VARIANT __RPC_FAR *pvMatrix);


void __RPC_STUB IVMain_GetTransformMatrix_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVMain_SetTransformMatrix_Proxy( 
    IVMain __RPC_FAR * This,
    /* [in] */ VARIANT vMatrix);


void __RPC_STUB IVMain_SetTransformMatrix_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVMain_GetTimeScale_Proxy( 
    IVMain __RPC_FAR * This,
    /* [out] */ double __RPC_FAR *pdC0,
    /* [out] */ double __RPC_FAR *pdC1);


void __RPC_STUB IVMain_GetTimeScale_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVMain_SetTimeScale_Proxy( 
    IVMain __RPC_FAR * This,
    /* [in] */ double dC0,
    /* [in] */ double dC1);


void __RPC_STUB IVMain_SetTimeScale_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVMain_StartBatchDraw_Proxy( 
    IVMain __RPC_FAR * This);


void __RPC_STUB IVMain_StartBatchDraw_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVMain_FinishBatchDraw_Proxy( 
    IVMain __RPC_FAR * This,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVMain_FinishBatchDraw_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVMain_MoveGroup_Proxy( 
    IVMain __RPC_FAR * This,
    /* [in] */ long iGroupID,
    /* [in] */ VARIANT vXY,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVMain_MoveGroup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVMain_ScaleGroup_Proxy( 
    IVMain __RPC_FAR * This,
    /* [in] */ long iGroupID,
    /* [in] */ double dScale,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVMain_ScaleGroup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVMain_RotateGroup_Proxy( 
    IVMain __RPC_FAR * This,
    /* [in] */ long iGroupID,
    /* [in] */ double dAngle,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVMain_RotateGroup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVMain_HideGroup_Proxy( 
    IVMain __RPC_FAR * This,
    /* [in] */ long iGroupID,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVMain_HideGroup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVMain_ShowGroup_Proxy( 
    IVMain __RPC_FAR * This,
    /* [in] */ long iGroupID,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVMain_ShowGroup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVMain_ResetEventLog_Proxy( 
    IVMain __RPC_FAR * This);


void __RPC_STUB IVMain_ResetEventLog_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVMain_GetEventLog_Proxy( 
    IVMain __RPC_FAR * This,
    /* [out] */ VARIANT __RPC_FAR *pvLogID,
    /* [out] */ VARIANT __RPC_FAR *pvTimeStampMs);


void __RPC_STUB IVMain_GetEventLog_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVMain_INTERFACE_DEFINED__ */


#ifndef __IVDisk_INTERFACE_DEFINED__
#define __IVDisk_INTERFACE_DEFINED__

/* interface IVDisk */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IVDisk;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ebd33094-ceb1-11d5-9c3e-0050da2a68c8")
    IVDisk : public IDispatch
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetXY( 
            /* [out] */ VARIANT __RPC_FAR *pvXY) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetXY( 
            /* [in] */ VARIANT vXY,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetZ( 
            /* [out] */ double __RPC_FAR *pdZ) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetZ( 
            /* [in] */ double dZ,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetScale( 
            /* [out] */ double __RPC_FAR *pdScale) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetScale( 
            /* [in] */ double dScale,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetAngle( 
            /* [out] */ double __RPC_FAR *pdAngle) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetAngle( 
            /* [in] */ double dAngle,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetColor( 
            /* [out] */ VARIANT __RPC_FAR *pvColors) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetColor( 
            /* [in] */ VARIANT vColors,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetAlpha( 
            /* [out] */ double __RPC_FAR *pdAlpha) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetAlpha( 
            /* [in] */ double dAlpha,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetFillFlag( 
            /* [out] */ long __RPC_FAR *piFillFlag) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetFillFlag( 
            /* [in] */ long iFillFlag,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetShowFlag( 
            /* [out] */ long __RPC_FAR *piShowFlag) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetShowFlag( 
            /* [in] */ long iShowFlag,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetGroupID( 
            /* [out] */ long __RPC_FAR *piGroupID) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetGroupID( 
            /* [in] */ long iGroupID) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetClippedCount( 
            /* [out] */ long __RPC_FAR *piClippedCount) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Move( 
            /* [in] */ VARIANT vXY,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Scale( 
            /* [in] */ double dScale,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Rotate( 
            /* [in] */ double dAngle,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Show( 
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Hide( 
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetRadius( 
            /* [out] */ double __RPC_FAR *pdRadius) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetRadius( 
            /* [in] */ double dRadius,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetN_Vertices( 
            /* [out] */ long __RPC_FAR *pnVertices) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetN_Vertices( 
            /* [in] */ long nVertices,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVDiskVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IVDisk __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IVDisk __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IVDisk __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IVDisk __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IVDisk __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IVDisk __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IVDisk __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetXY )( 
            IVDisk __RPC_FAR * This,
            /* [out] */ VARIANT __RPC_FAR *pvXY);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetXY )( 
            IVDisk __RPC_FAR * This,
            /* [in] */ VARIANT vXY,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetZ )( 
            IVDisk __RPC_FAR * This,
            /* [out] */ double __RPC_FAR *pdZ);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetZ )( 
            IVDisk __RPC_FAR * This,
            /* [in] */ double dZ,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetScale )( 
            IVDisk __RPC_FAR * This,
            /* [out] */ double __RPC_FAR *pdScale);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetScale )( 
            IVDisk __RPC_FAR * This,
            /* [in] */ double dScale,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAngle )( 
            IVDisk __RPC_FAR * This,
            /* [out] */ double __RPC_FAR *pdAngle);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAngle )( 
            IVDisk __RPC_FAR * This,
            /* [in] */ double dAngle,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetColor )( 
            IVDisk __RPC_FAR * This,
            /* [out] */ VARIANT __RPC_FAR *pvColors);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetColor )( 
            IVDisk __RPC_FAR * This,
            /* [in] */ VARIANT vColors,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAlpha )( 
            IVDisk __RPC_FAR * This,
            /* [out] */ double __RPC_FAR *pdAlpha);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAlpha )( 
            IVDisk __RPC_FAR * This,
            /* [in] */ double dAlpha,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFillFlag )( 
            IVDisk __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *piFillFlag);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetFillFlag )( 
            IVDisk __RPC_FAR * This,
            /* [in] */ long iFillFlag,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetShowFlag )( 
            IVDisk __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *piShowFlag);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetShowFlag )( 
            IVDisk __RPC_FAR * This,
            /* [in] */ long iShowFlag,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetGroupID )( 
            IVDisk __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *piGroupID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetGroupID )( 
            IVDisk __RPC_FAR * This,
            /* [in] */ long iGroupID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetClippedCount )( 
            IVDisk __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *piClippedCount);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Move )( 
            IVDisk __RPC_FAR * This,
            /* [in] */ VARIANT vXY,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Scale )( 
            IVDisk __RPC_FAR * This,
            /* [in] */ double dScale,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Rotate )( 
            IVDisk __RPC_FAR * This,
            /* [in] */ double dAngle,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Show )( 
            IVDisk __RPC_FAR * This,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Hide )( 
            IVDisk __RPC_FAR * This,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRadius )( 
            IVDisk __RPC_FAR * This,
            /* [out] */ double __RPC_FAR *pdRadius);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetRadius )( 
            IVDisk __RPC_FAR * This,
            /* [in] */ double dRadius,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetN_Vertices )( 
            IVDisk __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pnVertices);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetN_Vertices )( 
            IVDisk __RPC_FAR * This,
            /* [in] */ long nVertices,
            /* [defaultvalue][in] */ long iLogID);
        
        END_INTERFACE
    } IVDiskVtbl;

    interface IVDisk
    {
        CONST_VTBL struct IVDiskVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVDisk_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVDisk_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVDisk_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVDisk_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IVDisk_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IVDisk_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IVDisk_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IVDisk_GetXY(This,pvXY)	\
    (This)->lpVtbl -> GetXY(This,pvXY)

#define IVDisk_SetXY(This,vXY,iLogID)	\
    (This)->lpVtbl -> SetXY(This,vXY,iLogID)

#define IVDisk_GetZ(This,pdZ)	\
    (This)->lpVtbl -> GetZ(This,pdZ)

#define IVDisk_SetZ(This,dZ,iLogID)	\
    (This)->lpVtbl -> SetZ(This,dZ,iLogID)

#define IVDisk_GetScale(This,pdScale)	\
    (This)->lpVtbl -> GetScale(This,pdScale)

#define IVDisk_SetScale(This,dScale,iLogID)	\
    (This)->lpVtbl -> SetScale(This,dScale,iLogID)

#define IVDisk_GetAngle(This,pdAngle)	\
    (This)->lpVtbl -> GetAngle(This,pdAngle)

#define IVDisk_SetAngle(This,dAngle,iLogID)	\
    (This)->lpVtbl -> SetAngle(This,dAngle,iLogID)

#define IVDisk_GetColor(This,pvColors)	\
    (This)->lpVtbl -> GetColor(This,pvColors)

#define IVDisk_SetColor(This,vColors,iLogID)	\
    (This)->lpVtbl -> SetColor(This,vColors,iLogID)

#define IVDisk_GetAlpha(This,pdAlpha)	\
    (This)->lpVtbl -> GetAlpha(This,pdAlpha)

#define IVDisk_SetAlpha(This,dAlpha,iLogID)	\
    (This)->lpVtbl -> SetAlpha(This,dAlpha,iLogID)

#define IVDisk_GetFillFlag(This,piFillFlag)	\
    (This)->lpVtbl -> GetFillFlag(This,piFillFlag)

#define IVDisk_SetFillFlag(This,iFillFlag,iLogID)	\
    (This)->lpVtbl -> SetFillFlag(This,iFillFlag,iLogID)

#define IVDisk_GetShowFlag(This,piShowFlag)	\
    (This)->lpVtbl -> GetShowFlag(This,piShowFlag)

#define IVDisk_SetShowFlag(This,iShowFlag,iLogID)	\
    (This)->lpVtbl -> SetShowFlag(This,iShowFlag,iLogID)

#define IVDisk_GetGroupID(This,piGroupID)	\
    (This)->lpVtbl -> GetGroupID(This,piGroupID)

#define IVDisk_SetGroupID(This,iGroupID)	\
    (This)->lpVtbl -> SetGroupID(This,iGroupID)

#define IVDisk_GetClippedCount(This,piClippedCount)	\
    (This)->lpVtbl -> GetClippedCount(This,piClippedCount)

#define IVDisk_Move(This,vXY,iLogID)	\
    (This)->lpVtbl -> Move(This,vXY,iLogID)

#define IVDisk_Scale(This,dScale,iLogID)	\
    (This)->lpVtbl -> Scale(This,dScale,iLogID)

#define IVDisk_Rotate(This,dAngle,iLogID)	\
    (This)->lpVtbl -> Rotate(This,dAngle,iLogID)

#define IVDisk_Show(This,iLogID)	\
    (This)->lpVtbl -> Show(This,iLogID)

#define IVDisk_Hide(This,iLogID)	\
    (This)->lpVtbl -> Hide(This,iLogID)

#define IVDisk_GetRadius(This,pdRadius)	\
    (This)->lpVtbl -> GetRadius(This,pdRadius)

#define IVDisk_SetRadius(This,dRadius,iLogID)	\
    (This)->lpVtbl -> SetRadius(This,dRadius,iLogID)

#define IVDisk_GetN_Vertices(This,pnVertices)	\
    (This)->lpVtbl -> GetN_Vertices(This,pnVertices)

#define IVDisk_SetN_Vertices(This,nVertices,iLogID)	\
    (This)->lpVtbl -> SetN_Vertices(This,nVertices,iLogID)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVDisk_GetXY_Proxy( 
    IVDisk __RPC_FAR * This,
    /* [out] */ VARIANT __RPC_FAR *pvXY);


void __RPC_STUB IVDisk_GetXY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVDisk_SetXY_Proxy( 
    IVDisk __RPC_FAR * This,
    /* [in] */ VARIANT vXY,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVDisk_SetXY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVDisk_GetZ_Proxy( 
    IVDisk __RPC_FAR * This,
    /* [out] */ double __RPC_FAR *pdZ);


void __RPC_STUB IVDisk_GetZ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVDisk_SetZ_Proxy( 
    IVDisk __RPC_FAR * This,
    /* [in] */ double dZ,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVDisk_SetZ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVDisk_GetScale_Proxy( 
    IVDisk __RPC_FAR * This,
    /* [out] */ double __RPC_FAR *pdScale);


void __RPC_STUB IVDisk_GetScale_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVDisk_SetScale_Proxy( 
    IVDisk __RPC_FAR * This,
    /* [in] */ double dScale,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVDisk_SetScale_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVDisk_GetAngle_Proxy( 
    IVDisk __RPC_FAR * This,
    /* [out] */ double __RPC_FAR *pdAngle);


void __RPC_STUB IVDisk_GetAngle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVDisk_SetAngle_Proxy( 
    IVDisk __RPC_FAR * This,
    /* [in] */ double dAngle,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVDisk_SetAngle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVDisk_GetColor_Proxy( 
    IVDisk __RPC_FAR * This,
    /* [out] */ VARIANT __RPC_FAR *pvColors);


void __RPC_STUB IVDisk_GetColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVDisk_SetColor_Proxy( 
    IVDisk __RPC_FAR * This,
    /* [in] */ VARIANT vColors,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVDisk_SetColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVDisk_GetAlpha_Proxy( 
    IVDisk __RPC_FAR * This,
    /* [out] */ double __RPC_FAR *pdAlpha);


void __RPC_STUB IVDisk_GetAlpha_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVDisk_SetAlpha_Proxy( 
    IVDisk __RPC_FAR * This,
    /* [in] */ double dAlpha,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVDisk_SetAlpha_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVDisk_GetFillFlag_Proxy( 
    IVDisk __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *piFillFlag);


void __RPC_STUB IVDisk_GetFillFlag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVDisk_SetFillFlag_Proxy( 
    IVDisk __RPC_FAR * This,
    /* [in] */ long iFillFlag,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVDisk_SetFillFlag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVDisk_GetShowFlag_Proxy( 
    IVDisk __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *piShowFlag);


void __RPC_STUB IVDisk_GetShowFlag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVDisk_SetShowFlag_Proxy( 
    IVDisk __RPC_FAR * This,
    /* [in] */ long iShowFlag,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVDisk_SetShowFlag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVDisk_GetGroupID_Proxy( 
    IVDisk __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *piGroupID);


void __RPC_STUB IVDisk_GetGroupID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVDisk_SetGroupID_Proxy( 
    IVDisk __RPC_FAR * This,
    /* [in] */ long iGroupID);


void __RPC_STUB IVDisk_SetGroupID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVDisk_GetClippedCount_Proxy( 
    IVDisk __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *piClippedCount);


void __RPC_STUB IVDisk_GetClippedCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVDisk_Move_Proxy( 
    IVDisk __RPC_FAR * This,
    /* [in] */ VARIANT vXY,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVDisk_Move_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVDisk_Scale_Proxy( 
    IVDisk __RPC_FAR * This,
    /* [in] */ double dScale,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVDisk_Scale_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVDisk_Rotate_Proxy( 
    IVDisk __RPC_FAR * This,
    /* [in] */ double dAngle,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVDisk_Rotate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVDisk_Show_Proxy( 
    IVDisk __RPC_FAR * This,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVDisk_Show_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVDisk_Hide_Proxy( 
    IVDisk __RPC_FAR * This,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVDisk_Hide_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVDisk_GetRadius_Proxy( 
    IVDisk __RPC_FAR * This,
    /* [out] */ double __RPC_FAR *pdRadius);


void __RPC_STUB IVDisk_GetRadius_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVDisk_SetRadius_Proxy( 
    IVDisk __RPC_FAR * This,
    /* [in] */ double dRadius,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVDisk_SetRadius_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVDisk_GetN_Vertices_Proxy( 
    IVDisk __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pnVertices);


void __RPC_STUB IVDisk_GetN_Vertices_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVDisk_SetN_Vertices_Proxy( 
    IVDisk __RPC_FAR * This,
    /* [in] */ long nVertices,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVDisk_SetN_Vertices_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVDisk_INTERFACE_DEFINED__ */


#ifndef __IVPolygon_INTERFACE_DEFINED__
#define __IVPolygon_INTERFACE_DEFINED__

/* interface IVPolygon */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IVPolygon;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ebd3309c-ceb1-11d5-9c3e-0050da2a68c8")
    IVPolygon : public IDispatch
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetXY( 
            /* [out] */ VARIANT __RPC_FAR *pvXY) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetXY( 
            /* [in] */ VARIANT vXY,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetZ( 
            /* [out] */ double __RPC_FAR *pdZ) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetZ( 
            /* [in] */ double dZ,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetScale( 
            /* [out] */ double __RPC_FAR *pdScale) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetScale( 
            /* [in] */ double dScale,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetAngle( 
            /* [out] */ double __RPC_FAR *pdAngle) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetAngle( 
            /* [in] */ double dAngle,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetColor( 
            /* [out] */ VARIANT __RPC_FAR *pvColors) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetColor( 
            /* [in] */ VARIANT vColors,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetAlpha( 
            /* [out] */ double __RPC_FAR *pdAlpha) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetAlpha( 
            /* [in] */ double dAlpha,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetFillFlag( 
            /* [out] */ long __RPC_FAR *piFillFlag) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetFillFlag( 
            /* [in] */ long iFillFlag,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetShowFlag( 
            /* [out] */ long __RPC_FAR *piShowFlag) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetShowFlag( 
            /* [in] */ long iShowFlag,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetGroupID( 
            /* [out] */ long __RPC_FAR *piGroupID) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetGroupID( 
            /* [in] */ long iGroupID) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetClippedCount( 
            /* [out] */ long __RPC_FAR *piClippedCount) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Move( 
            /* [in] */ VARIANT vXY,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Scale( 
            /* [in] */ double dScale,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Rotate( 
            /* [in] */ double dAngle,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Show( 
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Hide( 
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetVertices( 
            /* [out] */ VARIANT __RPC_FAR *pvVertices) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetVertices( 
            /* [in] */ VARIANT vVertices,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetTexture( 
            /* [out] */ VARIANT __RPC_FAR *pvTexture,
            /* [out] */ long __RPC_FAR *pnPixelsW,
            /* [out] */ long __RPC_FAR *pnPixelH,
            /* [out] */ double __RPC_FAR *pdTexturePhysWidth) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetTexture( 
            /* [in] */ VARIANT vTexture,
            /* [in] */ double dTexturePhysWidth,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetTextureFlag( 
            /* [out] */ long __RPC_FAR *plngTextureFlag) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetTextureFlag( 
            /* [in] */ long lngTextureFlag,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVPolygonVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IVPolygon __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IVPolygon __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IVPolygon __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IVPolygon __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IVPolygon __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IVPolygon __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IVPolygon __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetXY )( 
            IVPolygon __RPC_FAR * This,
            /* [out] */ VARIANT __RPC_FAR *pvXY);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetXY )( 
            IVPolygon __RPC_FAR * This,
            /* [in] */ VARIANT vXY,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetZ )( 
            IVPolygon __RPC_FAR * This,
            /* [out] */ double __RPC_FAR *pdZ);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetZ )( 
            IVPolygon __RPC_FAR * This,
            /* [in] */ double dZ,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetScale )( 
            IVPolygon __RPC_FAR * This,
            /* [out] */ double __RPC_FAR *pdScale);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetScale )( 
            IVPolygon __RPC_FAR * This,
            /* [in] */ double dScale,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAngle )( 
            IVPolygon __RPC_FAR * This,
            /* [out] */ double __RPC_FAR *pdAngle);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAngle )( 
            IVPolygon __RPC_FAR * This,
            /* [in] */ double dAngle,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetColor )( 
            IVPolygon __RPC_FAR * This,
            /* [out] */ VARIANT __RPC_FAR *pvColors);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetColor )( 
            IVPolygon __RPC_FAR * This,
            /* [in] */ VARIANT vColors,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAlpha )( 
            IVPolygon __RPC_FAR * This,
            /* [out] */ double __RPC_FAR *pdAlpha);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAlpha )( 
            IVPolygon __RPC_FAR * This,
            /* [in] */ double dAlpha,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFillFlag )( 
            IVPolygon __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *piFillFlag);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetFillFlag )( 
            IVPolygon __RPC_FAR * This,
            /* [in] */ long iFillFlag,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetShowFlag )( 
            IVPolygon __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *piShowFlag);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetShowFlag )( 
            IVPolygon __RPC_FAR * This,
            /* [in] */ long iShowFlag,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetGroupID )( 
            IVPolygon __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *piGroupID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetGroupID )( 
            IVPolygon __RPC_FAR * This,
            /* [in] */ long iGroupID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetClippedCount )( 
            IVPolygon __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *piClippedCount);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Move )( 
            IVPolygon __RPC_FAR * This,
            /* [in] */ VARIANT vXY,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Scale )( 
            IVPolygon __RPC_FAR * This,
            /* [in] */ double dScale,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Rotate )( 
            IVPolygon __RPC_FAR * This,
            /* [in] */ double dAngle,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Show )( 
            IVPolygon __RPC_FAR * This,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Hide )( 
            IVPolygon __RPC_FAR * This,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetVertices )( 
            IVPolygon __RPC_FAR * This,
            /* [out] */ VARIANT __RPC_FAR *pvVertices);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetVertices )( 
            IVPolygon __RPC_FAR * This,
            /* [in] */ VARIANT vVertices,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTexture )( 
            IVPolygon __RPC_FAR * This,
            /* [out] */ VARIANT __RPC_FAR *pvTexture,
            /* [out] */ long __RPC_FAR *pnPixelsW,
            /* [out] */ long __RPC_FAR *pnPixelH,
            /* [out] */ double __RPC_FAR *pdTexturePhysWidth);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetTexture )( 
            IVPolygon __RPC_FAR * This,
            /* [in] */ VARIANT vTexture,
            /* [in] */ double dTexturePhysWidth,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTextureFlag )( 
            IVPolygon __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *plngTextureFlag);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetTextureFlag )( 
            IVPolygon __RPC_FAR * This,
            /* [in] */ long lngTextureFlag,
            /* [defaultvalue][in] */ long iLogID);
        
        END_INTERFACE
    } IVPolygonVtbl;

    interface IVPolygon
    {
        CONST_VTBL struct IVPolygonVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVPolygon_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVPolygon_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVPolygon_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVPolygon_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IVPolygon_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IVPolygon_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IVPolygon_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IVPolygon_GetXY(This,pvXY)	\
    (This)->lpVtbl -> GetXY(This,pvXY)

#define IVPolygon_SetXY(This,vXY,iLogID)	\
    (This)->lpVtbl -> SetXY(This,vXY,iLogID)

#define IVPolygon_GetZ(This,pdZ)	\
    (This)->lpVtbl -> GetZ(This,pdZ)

#define IVPolygon_SetZ(This,dZ,iLogID)	\
    (This)->lpVtbl -> SetZ(This,dZ,iLogID)

#define IVPolygon_GetScale(This,pdScale)	\
    (This)->lpVtbl -> GetScale(This,pdScale)

#define IVPolygon_SetScale(This,dScale,iLogID)	\
    (This)->lpVtbl -> SetScale(This,dScale,iLogID)

#define IVPolygon_GetAngle(This,pdAngle)	\
    (This)->lpVtbl -> GetAngle(This,pdAngle)

#define IVPolygon_SetAngle(This,dAngle,iLogID)	\
    (This)->lpVtbl -> SetAngle(This,dAngle,iLogID)

#define IVPolygon_GetColor(This,pvColors)	\
    (This)->lpVtbl -> GetColor(This,pvColors)

#define IVPolygon_SetColor(This,vColors,iLogID)	\
    (This)->lpVtbl -> SetColor(This,vColors,iLogID)

#define IVPolygon_GetAlpha(This,pdAlpha)	\
    (This)->lpVtbl -> GetAlpha(This,pdAlpha)

#define IVPolygon_SetAlpha(This,dAlpha,iLogID)	\
    (This)->lpVtbl -> SetAlpha(This,dAlpha,iLogID)

#define IVPolygon_GetFillFlag(This,piFillFlag)	\
    (This)->lpVtbl -> GetFillFlag(This,piFillFlag)

#define IVPolygon_SetFillFlag(This,iFillFlag,iLogID)	\
    (This)->lpVtbl -> SetFillFlag(This,iFillFlag,iLogID)

#define IVPolygon_GetShowFlag(This,piShowFlag)	\
    (This)->lpVtbl -> GetShowFlag(This,piShowFlag)

#define IVPolygon_SetShowFlag(This,iShowFlag,iLogID)	\
    (This)->lpVtbl -> SetShowFlag(This,iShowFlag,iLogID)

#define IVPolygon_GetGroupID(This,piGroupID)	\
    (This)->lpVtbl -> GetGroupID(This,piGroupID)

#define IVPolygon_SetGroupID(This,iGroupID)	\
    (This)->lpVtbl -> SetGroupID(This,iGroupID)

#define IVPolygon_GetClippedCount(This,piClippedCount)	\
    (This)->lpVtbl -> GetClippedCount(This,piClippedCount)

#define IVPolygon_Move(This,vXY,iLogID)	\
    (This)->lpVtbl -> Move(This,vXY,iLogID)

#define IVPolygon_Scale(This,dScale,iLogID)	\
    (This)->lpVtbl -> Scale(This,dScale,iLogID)

#define IVPolygon_Rotate(This,dAngle,iLogID)	\
    (This)->lpVtbl -> Rotate(This,dAngle,iLogID)

#define IVPolygon_Show(This,iLogID)	\
    (This)->lpVtbl -> Show(This,iLogID)

#define IVPolygon_Hide(This,iLogID)	\
    (This)->lpVtbl -> Hide(This,iLogID)

#define IVPolygon_GetVertices(This,pvVertices)	\
    (This)->lpVtbl -> GetVertices(This,pvVertices)

#define IVPolygon_SetVertices(This,vVertices,iLogID)	\
    (This)->lpVtbl -> SetVertices(This,vVertices,iLogID)

#define IVPolygon_GetTexture(This,pvTexture,pnPixelsW,pnPixelH,pdTexturePhysWidth)	\
    (This)->lpVtbl -> GetTexture(This,pvTexture,pnPixelsW,pnPixelH,pdTexturePhysWidth)

#define IVPolygon_SetTexture(This,vTexture,dTexturePhysWidth,iLogID)	\
    (This)->lpVtbl -> SetTexture(This,vTexture,dTexturePhysWidth,iLogID)

#define IVPolygon_GetTextureFlag(This,plngTextureFlag)	\
    (This)->lpVtbl -> GetTextureFlag(This,plngTextureFlag)

#define IVPolygon_SetTextureFlag(This,lngTextureFlag,iLogID)	\
    (This)->lpVtbl -> SetTextureFlag(This,lngTextureFlag,iLogID)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVPolygon_GetXY_Proxy( 
    IVPolygon __RPC_FAR * This,
    /* [out] */ VARIANT __RPC_FAR *pvXY);


void __RPC_STUB IVPolygon_GetXY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVPolygon_SetXY_Proxy( 
    IVPolygon __RPC_FAR * This,
    /* [in] */ VARIANT vXY,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVPolygon_SetXY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVPolygon_GetZ_Proxy( 
    IVPolygon __RPC_FAR * This,
    /* [out] */ double __RPC_FAR *pdZ);


void __RPC_STUB IVPolygon_GetZ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVPolygon_SetZ_Proxy( 
    IVPolygon __RPC_FAR * This,
    /* [in] */ double dZ,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVPolygon_SetZ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVPolygon_GetScale_Proxy( 
    IVPolygon __RPC_FAR * This,
    /* [out] */ double __RPC_FAR *pdScale);


void __RPC_STUB IVPolygon_GetScale_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVPolygon_SetScale_Proxy( 
    IVPolygon __RPC_FAR * This,
    /* [in] */ double dScale,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVPolygon_SetScale_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVPolygon_GetAngle_Proxy( 
    IVPolygon __RPC_FAR * This,
    /* [out] */ double __RPC_FAR *pdAngle);


void __RPC_STUB IVPolygon_GetAngle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVPolygon_SetAngle_Proxy( 
    IVPolygon __RPC_FAR * This,
    /* [in] */ double dAngle,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVPolygon_SetAngle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVPolygon_GetColor_Proxy( 
    IVPolygon __RPC_FAR * This,
    /* [out] */ VARIANT __RPC_FAR *pvColors);


void __RPC_STUB IVPolygon_GetColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVPolygon_SetColor_Proxy( 
    IVPolygon __RPC_FAR * This,
    /* [in] */ VARIANT vColors,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVPolygon_SetColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVPolygon_GetAlpha_Proxy( 
    IVPolygon __RPC_FAR * This,
    /* [out] */ double __RPC_FAR *pdAlpha);


void __RPC_STUB IVPolygon_GetAlpha_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVPolygon_SetAlpha_Proxy( 
    IVPolygon __RPC_FAR * This,
    /* [in] */ double dAlpha,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVPolygon_SetAlpha_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVPolygon_GetFillFlag_Proxy( 
    IVPolygon __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *piFillFlag);


void __RPC_STUB IVPolygon_GetFillFlag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVPolygon_SetFillFlag_Proxy( 
    IVPolygon __RPC_FAR * This,
    /* [in] */ long iFillFlag,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVPolygon_SetFillFlag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVPolygon_GetShowFlag_Proxy( 
    IVPolygon __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *piShowFlag);


void __RPC_STUB IVPolygon_GetShowFlag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVPolygon_SetShowFlag_Proxy( 
    IVPolygon __RPC_FAR * This,
    /* [in] */ long iShowFlag,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVPolygon_SetShowFlag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVPolygon_GetGroupID_Proxy( 
    IVPolygon __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *piGroupID);


void __RPC_STUB IVPolygon_GetGroupID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVPolygon_SetGroupID_Proxy( 
    IVPolygon __RPC_FAR * This,
    /* [in] */ long iGroupID);


void __RPC_STUB IVPolygon_SetGroupID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVPolygon_GetClippedCount_Proxy( 
    IVPolygon __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *piClippedCount);


void __RPC_STUB IVPolygon_GetClippedCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVPolygon_Move_Proxy( 
    IVPolygon __RPC_FAR * This,
    /* [in] */ VARIANT vXY,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVPolygon_Move_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVPolygon_Scale_Proxy( 
    IVPolygon __RPC_FAR * This,
    /* [in] */ double dScale,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVPolygon_Scale_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVPolygon_Rotate_Proxy( 
    IVPolygon __RPC_FAR * This,
    /* [in] */ double dAngle,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVPolygon_Rotate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVPolygon_Show_Proxy( 
    IVPolygon __RPC_FAR * This,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVPolygon_Show_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVPolygon_Hide_Proxy( 
    IVPolygon __RPC_FAR * This,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVPolygon_Hide_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVPolygon_GetVertices_Proxy( 
    IVPolygon __RPC_FAR * This,
    /* [out] */ VARIANT __RPC_FAR *pvVertices);


void __RPC_STUB IVPolygon_GetVertices_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVPolygon_SetVertices_Proxy( 
    IVPolygon __RPC_FAR * This,
    /* [in] */ VARIANT vVertices,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVPolygon_SetVertices_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVPolygon_GetTexture_Proxy( 
    IVPolygon __RPC_FAR * This,
    /* [out] */ VARIANT __RPC_FAR *pvTexture,
    /* [out] */ long __RPC_FAR *pnPixelsW,
    /* [out] */ long __RPC_FAR *pnPixelH,
    /* [out] */ double __RPC_FAR *pdTexturePhysWidth);


void __RPC_STUB IVPolygon_GetTexture_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVPolygon_SetTexture_Proxy( 
    IVPolygon __RPC_FAR * This,
    /* [in] */ VARIANT vTexture,
    /* [in] */ double dTexturePhysWidth,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVPolygon_SetTexture_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVPolygon_GetTextureFlag_Proxy( 
    IVPolygon __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *plngTextureFlag);


void __RPC_STUB IVPolygon_GetTextureFlag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVPolygon_SetTextureFlag_Proxy( 
    IVPolygon __RPC_FAR * This,
    /* [in] */ long lngTextureFlag,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVPolygon_SetTextureFlag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVPolygon_INTERFACE_DEFINED__ */


#ifndef __IVText_INTERFACE_DEFINED__
#define __IVText_INTERFACE_DEFINED__

/* interface IVText */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IVText;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ebd330a4-ceb1-11d5-9c3e-0050da2a68c8")
    IVText : public IDispatch
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetXY( 
            /* [out] */ VARIANT __RPC_FAR *pvXY) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetXY( 
            /* [in] */ VARIANT vXY,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetZ( 
            /* [out] */ double __RPC_FAR *pdZ) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetZ( 
            /* [in] */ double dZ,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetScale( 
            /* [out] */ double __RPC_FAR *pdScale) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetScale( 
            /* [in] */ double dScale,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetAngle( 
            /* [out] */ double __RPC_FAR *pdAngle) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetAngle( 
            /* [in] */ double dAngle,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetColor( 
            /* [out] */ VARIANT __RPC_FAR *pvColors) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetColor( 
            /* [in] */ VARIANT vColors,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetAlpha( 
            /* [out] */ double __RPC_FAR *pdAlpha) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetAlpha( 
            /* [in] */ double dAlpha,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetFillFlag( 
            /* [out] */ long __RPC_FAR *piFillFlag) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetFillFlag( 
            /* [in] */ long iFillFlag,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetShowFlag( 
            /* [out] */ long __RPC_FAR *piShowFlag) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetShowFlag( 
            /* [in] */ long iShowFlag,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetGroupID( 
            /* [out] */ long __RPC_FAR *piGroupID) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetGroupID( 
            /* [in] */ long iGroupID) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetClippedCount( 
            /* [out] */ long __RPC_FAR *piClippedCount) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Move( 
            /* [in] */ VARIANT vXY,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Scale( 
            /* [in] */ double dScale,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Rotate( 
            /* [in] */ double dAngle,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Show( 
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Hide( 
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetText( 
            /* [out] */ BSTR __RPC_FAR *pbstText) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetText( 
            /* [in] */ BSTR bstText,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetFontName( 
            /* [out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetFontName( 
            /* [in] */ BSTR newVal,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetFontWeight( 
            /* [out] */ long __RPC_FAR *lngWeight) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetFontWeight( 
            /* [in] */ long lngWeight,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetFontUnderlineFlag( 
            /* [out] */ long __RPC_FAR *plngUnderlineFlag) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetFontUnderlineFlag( 
            /* [in] */ long lngUnderlineFlag,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetFontItalicFlag( 
            /* [out] */ long __RPC_FAR *plngItalicFlag) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetFontItalicFlag( 
            /* [in] */ long lngItalicFlag,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVTextVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IVText __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IVText __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IVText __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IVText __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IVText __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IVText __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IVText __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetXY )( 
            IVText __RPC_FAR * This,
            /* [out] */ VARIANT __RPC_FAR *pvXY);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetXY )( 
            IVText __RPC_FAR * This,
            /* [in] */ VARIANT vXY,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetZ )( 
            IVText __RPC_FAR * This,
            /* [out] */ double __RPC_FAR *pdZ);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetZ )( 
            IVText __RPC_FAR * This,
            /* [in] */ double dZ,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetScale )( 
            IVText __RPC_FAR * This,
            /* [out] */ double __RPC_FAR *pdScale);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetScale )( 
            IVText __RPC_FAR * This,
            /* [in] */ double dScale,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAngle )( 
            IVText __RPC_FAR * This,
            /* [out] */ double __RPC_FAR *pdAngle);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAngle )( 
            IVText __RPC_FAR * This,
            /* [in] */ double dAngle,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetColor )( 
            IVText __RPC_FAR * This,
            /* [out] */ VARIANT __RPC_FAR *pvColors);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetColor )( 
            IVText __RPC_FAR * This,
            /* [in] */ VARIANT vColors,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAlpha )( 
            IVText __RPC_FAR * This,
            /* [out] */ double __RPC_FAR *pdAlpha);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAlpha )( 
            IVText __RPC_FAR * This,
            /* [in] */ double dAlpha,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFillFlag )( 
            IVText __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *piFillFlag);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetFillFlag )( 
            IVText __RPC_FAR * This,
            /* [in] */ long iFillFlag,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetShowFlag )( 
            IVText __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *piShowFlag);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetShowFlag )( 
            IVText __RPC_FAR * This,
            /* [in] */ long iShowFlag,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetGroupID )( 
            IVText __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *piGroupID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetGroupID )( 
            IVText __RPC_FAR * This,
            /* [in] */ long iGroupID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetClippedCount )( 
            IVText __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *piClippedCount);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Move )( 
            IVText __RPC_FAR * This,
            /* [in] */ VARIANT vXY,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Scale )( 
            IVText __RPC_FAR * This,
            /* [in] */ double dScale,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Rotate )( 
            IVText __RPC_FAR * This,
            /* [in] */ double dAngle,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Show )( 
            IVText __RPC_FAR * This,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Hide )( 
            IVText __RPC_FAR * This,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetText )( 
            IVText __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *pbstText);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetText )( 
            IVText __RPC_FAR * This,
            /* [in] */ BSTR bstText,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFontName )( 
            IVText __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetFontName )( 
            IVText __RPC_FAR * This,
            /* [in] */ BSTR newVal,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFontWeight )( 
            IVText __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *lngWeight);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetFontWeight )( 
            IVText __RPC_FAR * This,
            /* [in] */ long lngWeight,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFontUnderlineFlag )( 
            IVText __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *plngUnderlineFlag);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetFontUnderlineFlag )( 
            IVText __RPC_FAR * This,
            /* [in] */ long lngUnderlineFlag,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFontItalicFlag )( 
            IVText __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *plngItalicFlag);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetFontItalicFlag )( 
            IVText __RPC_FAR * This,
            /* [in] */ long lngItalicFlag,
            /* [defaultvalue][in] */ long iLogID);
        
        END_INTERFACE
    } IVTextVtbl;

    interface IVText
    {
        CONST_VTBL struct IVTextVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVText_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVText_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVText_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVText_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IVText_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IVText_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IVText_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IVText_GetXY(This,pvXY)	\
    (This)->lpVtbl -> GetXY(This,pvXY)

#define IVText_SetXY(This,vXY,iLogID)	\
    (This)->lpVtbl -> SetXY(This,vXY,iLogID)

#define IVText_GetZ(This,pdZ)	\
    (This)->lpVtbl -> GetZ(This,pdZ)

#define IVText_SetZ(This,dZ,iLogID)	\
    (This)->lpVtbl -> SetZ(This,dZ,iLogID)

#define IVText_GetScale(This,pdScale)	\
    (This)->lpVtbl -> GetScale(This,pdScale)

#define IVText_SetScale(This,dScale,iLogID)	\
    (This)->lpVtbl -> SetScale(This,dScale,iLogID)

#define IVText_GetAngle(This,pdAngle)	\
    (This)->lpVtbl -> GetAngle(This,pdAngle)

#define IVText_SetAngle(This,dAngle,iLogID)	\
    (This)->lpVtbl -> SetAngle(This,dAngle,iLogID)

#define IVText_GetColor(This,pvColors)	\
    (This)->lpVtbl -> GetColor(This,pvColors)

#define IVText_SetColor(This,vColors,iLogID)	\
    (This)->lpVtbl -> SetColor(This,vColors,iLogID)

#define IVText_GetAlpha(This,pdAlpha)	\
    (This)->lpVtbl -> GetAlpha(This,pdAlpha)

#define IVText_SetAlpha(This,dAlpha,iLogID)	\
    (This)->lpVtbl -> SetAlpha(This,dAlpha,iLogID)

#define IVText_GetFillFlag(This,piFillFlag)	\
    (This)->lpVtbl -> GetFillFlag(This,piFillFlag)

#define IVText_SetFillFlag(This,iFillFlag,iLogID)	\
    (This)->lpVtbl -> SetFillFlag(This,iFillFlag,iLogID)

#define IVText_GetShowFlag(This,piShowFlag)	\
    (This)->lpVtbl -> GetShowFlag(This,piShowFlag)

#define IVText_SetShowFlag(This,iShowFlag,iLogID)	\
    (This)->lpVtbl -> SetShowFlag(This,iShowFlag,iLogID)

#define IVText_GetGroupID(This,piGroupID)	\
    (This)->lpVtbl -> GetGroupID(This,piGroupID)

#define IVText_SetGroupID(This,iGroupID)	\
    (This)->lpVtbl -> SetGroupID(This,iGroupID)

#define IVText_GetClippedCount(This,piClippedCount)	\
    (This)->lpVtbl -> GetClippedCount(This,piClippedCount)

#define IVText_Move(This,vXY,iLogID)	\
    (This)->lpVtbl -> Move(This,vXY,iLogID)

#define IVText_Scale(This,dScale,iLogID)	\
    (This)->lpVtbl -> Scale(This,dScale,iLogID)

#define IVText_Rotate(This,dAngle,iLogID)	\
    (This)->lpVtbl -> Rotate(This,dAngle,iLogID)

#define IVText_Show(This,iLogID)	\
    (This)->lpVtbl -> Show(This,iLogID)

#define IVText_Hide(This,iLogID)	\
    (This)->lpVtbl -> Hide(This,iLogID)

#define IVText_GetText(This,pbstText)	\
    (This)->lpVtbl -> GetText(This,pbstText)

#define IVText_SetText(This,bstText,iLogID)	\
    (This)->lpVtbl -> SetText(This,bstText,iLogID)

#define IVText_GetFontName(This,pVal)	\
    (This)->lpVtbl -> GetFontName(This,pVal)

#define IVText_SetFontName(This,newVal,iLogID)	\
    (This)->lpVtbl -> SetFontName(This,newVal,iLogID)

#define IVText_GetFontWeight(This,lngWeight)	\
    (This)->lpVtbl -> GetFontWeight(This,lngWeight)

#define IVText_SetFontWeight(This,lngWeight,iLogID)	\
    (This)->lpVtbl -> SetFontWeight(This,lngWeight,iLogID)

#define IVText_GetFontUnderlineFlag(This,plngUnderlineFlag)	\
    (This)->lpVtbl -> GetFontUnderlineFlag(This,plngUnderlineFlag)

#define IVText_SetFontUnderlineFlag(This,lngUnderlineFlag,iLogID)	\
    (This)->lpVtbl -> SetFontUnderlineFlag(This,lngUnderlineFlag,iLogID)

#define IVText_GetFontItalicFlag(This,plngItalicFlag)	\
    (This)->lpVtbl -> GetFontItalicFlag(This,plngItalicFlag)

#define IVText_SetFontItalicFlag(This,lngItalicFlag,iLogID)	\
    (This)->lpVtbl -> SetFontItalicFlag(This,lngItalicFlag,iLogID)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVText_GetXY_Proxy( 
    IVText __RPC_FAR * This,
    /* [out] */ VARIANT __RPC_FAR *pvXY);


void __RPC_STUB IVText_GetXY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVText_SetXY_Proxy( 
    IVText __RPC_FAR * This,
    /* [in] */ VARIANT vXY,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVText_SetXY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVText_GetZ_Proxy( 
    IVText __RPC_FAR * This,
    /* [out] */ double __RPC_FAR *pdZ);


void __RPC_STUB IVText_GetZ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVText_SetZ_Proxy( 
    IVText __RPC_FAR * This,
    /* [in] */ double dZ,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVText_SetZ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVText_GetScale_Proxy( 
    IVText __RPC_FAR * This,
    /* [out] */ double __RPC_FAR *pdScale);


void __RPC_STUB IVText_GetScale_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVText_SetScale_Proxy( 
    IVText __RPC_FAR * This,
    /* [in] */ double dScale,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVText_SetScale_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVText_GetAngle_Proxy( 
    IVText __RPC_FAR * This,
    /* [out] */ double __RPC_FAR *pdAngle);


void __RPC_STUB IVText_GetAngle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVText_SetAngle_Proxy( 
    IVText __RPC_FAR * This,
    /* [in] */ double dAngle,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVText_SetAngle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVText_GetColor_Proxy( 
    IVText __RPC_FAR * This,
    /* [out] */ VARIANT __RPC_FAR *pvColors);


void __RPC_STUB IVText_GetColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVText_SetColor_Proxy( 
    IVText __RPC_FAR * This,
    /* [in] */ VARIANT vColors,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVText_SetColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVText_GetAlpha_Proxy( 
    IVText __RPC_FAR * This,
    /* [out] */ double __RPC_FAR *pdAlpha);


void __RPC_STUB IVText_GetAlpha_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVText_SetAlpha_Proxy( 
    IVText __RPC_FAR * This,
    /* [in] */ double dAlpha,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVText_SetAlpha_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVText_GetFillFlag_Proxy( 
    IVText __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *piFillFlag);


void __RPC_STUB IVText_GetFillFlag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVText_SetFillFlag_Proxy( 
    IVText __RPC_FAR * This,
    /* [in] */ long iFillFlag,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVText_SetFillFlag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVText_GetShowFlag_Proxy( 
    IVText __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *piShowFlag);


void __RPC_STUB IVText_GetShowFlag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVText_SetShowFlag_Proxy( 
    IVText __RPC_FAR * This,
    /* [in] */ long iShowFlag,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVText_SetShowFlag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVText_GetGroupID_Proxy( 
    IVText __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *piGroupID);


void __RPC_STUB IVText_GetGroupID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVText_SetGroupID_Proxy( 
    IVText __RPC_FAR * This,
    /* [in] */ long iGroupID);


void __RPC_STUB IVText_SetGroupID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVText_GetClippedCount_Proxy( 
    IVText __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *piClippedCount);


void __RPC_STUB IVText_GetClippedCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVText_Move_Proxy( 
    IVText __RPC_FAR * This,
    /* [in] */ VARIANT vXY,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVText_Move_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVText_Scale_Proxy( 
    IVText __RPC_FAR * This,
    /* [in] */ double dScale,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVText_Scale_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVText_Rotate_Proxy( 
    IVText __RPC_FAR * This,
    /* [in] */ double dAngle,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVText_Rotate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVText_Show_Proxy( 
    IVText __RPC_FAR * This,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVText_Show_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVText_Hide_Proxy( 
    IVText __RPC_FAR * This,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVText_Hide_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVText_GetText_Proxy( 
    IVText __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *pbstText);


void __RPC_STUB IVText_GetText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVText_SetText_Proxy( 
    IVText __RPC_FAR * This,
    /* [in] */ BSTR bstText,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVText_SetText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVText_GetFontName_Proxy( 
    IVText __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IVText_GetFontName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVText_SetFontName_Proxy( 
    IVText __RPC_FAR * This,
    /* [in] */ BSTR newVal,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVText_SetFontName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVText_GetFontWeight_Proxy( 
    IVText __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *lngWeight);


void __RPC_STUB IVText_GetFontWeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVText_SetFontWeight_Proxy( 
    IVText __RPC_FAR * This,
    /* [in] */ long lngWeight,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVText_SetFontWeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVText_GetFontUnderlineFlag_Proxy( 
    IVText __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *plngUnderlineFlag);


void __RPC_STUB IVText_GetFontUnderlineFlag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVText_SetFontUnderlineFlag_Proxy( 
    IVText __RPC_FAR * This,
    /* [in] */ long lngUnderlineFlag,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVText_SetFontUnderlineFlag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVText_GetFontItalicFlag_Proxy( 
    IVText __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *plngItalicFlag);


void __RPC_STUB IVText_GetFontItalicFlag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVText_SetFontItalicFlag_Proxy( 
    IVText __RPC_FAR * This,
    /* [in] */ long lngItalicFlag,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVText_SetFontItalicFlag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVText_INTERFACE_DEFINED__ */


#ifndef __IVMouse_INTERFACE_DEFINED__
#define __IVMouse_INTERFACE_DEFINED__

/* interface IVMouse */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IVMouse;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ebd330ac-ceb1-11d5-9c3e-0050da2a68c8")
    IVMouse : public IDispatch
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetShowFlag( 
            /* [out] */ long __RPC_FAR *piShowFlag) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetShowFlag( 
            /* [in] */ long iShowFlag) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetXY( 
            /* [out] */ VARIANT __RPC_FAR *pvMtx) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetAllEvents( 
            /* [out] */ VARIANT __RPC_FAR *pvMtx) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetDownEvents( 
            /* [out] */ VARIANT __RPC_FAR *pvMtx) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetUpEvents( 
            /* [out] */ VARIANT __RPC_FAR *pvMtx) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetDblclickEvents( 
            /* [out] */ VARIANT __RPC_FAR *pvMtx) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ClearEvents( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Show( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Hide( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVMouseVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IVMouse __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IVMouse __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IVMouse __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IVMouse __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IVMouse __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IVMouse __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IVMouse __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetShowFlag )( 
            IVMouse __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *piShowFlag);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetShowFlag )( 
            IVMouse __RPC_FAR * This,
            /* [in] */ long iShowFlag);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetXY )( 
            IVMouse __RPC_FAR * This,
            /* [out] */ VARIANT __RPC_FAR *pvMtx);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAllEvents )( 
            IVMouse __RPC_FAR * This,
            /* [out] */ VARIANT __RPC_FAR *pvMtx);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDownEvents )( 
            IVMouse __RPC_FAR * This,
            /* [out] */ VARIANT __RPC_FAR *pvMtx);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetUpEvents )( 
            IVMouse __RPC_FAR * This,
            /* [out] */ VARIANT __RPC_FAR *pvMtx);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDblclickEvents )( 
            IVMouse __RPC_FAR * This,
            /* [out] */ VARIANT __RPC_FAR *pvMtx);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ClearEvents )( 
            IVMouse __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Show )( 
            IVMouse __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Hide )( 
            IVMouse __RPC_FAR * This);
        
        END_INTERFACE
    } IVMouseVtbl;

    interface IVMouse
    {
        CONST_VTBL struct IVMouseVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVMouse_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVMouse_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVMouse_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVMouse_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IVMouse_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IVMouse_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IVMouse_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IVMouse_GetShowFlag(This,piShowFlag)	\
    (This)->lpVtbl -> GetShowFlag(This,piShowFlag)

#define IVMouse_SetShowFlag(This,iShowFlag)	\
    (This)->lpVtbl -> SetShowFlag(This,iShowFlag)

#define IVMouse_GetXY(This,pvMtx)	\
    (This)->lpVtbl -> GetXY(This,pvMtx)

#define IVMouse_GetAllEvents(This,pvMtx)	\
    (This)->lpVtbl -> GetAllEvents(This,pvMtx)

#define IVMouse_GetDownEvents(This,pvMtx)	\
    (This)->lpVtbl -> GetDownEvents(This,pvMtx)

#define IVMouse_GetUpEvents(This,pvMtx)	\
    (This)->lpVtbl -> GetUpEvents(This,pvMtx)

#define IVMouse_GetDblclickEvents(This,pvMtx)	\
    (This)->lpVtbl -> GetDblclickEvents(This,pvMtx)

#define IVMouse_ClearEvents(This)	\
    (This)->lpVtbl -> ClearEvents(This)

#define IVMouse_Show(This)	\
    (This)->lpVtbl -> Show(This)

#define IVMouse_Hide(This)	\
    (This)->lpVtbl -> Hide(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVMouse_GetShowFlag_Proxy( 
    IVMouse __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *piShowFlag);


void __RPC_STUB IVMouse_GetShowFlag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVMouse_SetShowFlag_Proxy( 
    IVMouse __RPC_FAR * This,
    /* [in] */ long iShowFlag);


void __RPC_STUB IVMouse_SetShowFlag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVMouse_GetXY_Proxy( 
    IVMouse __RPC_FAR * This,
    /* [out] */ VARIANT __RPC_FAR *pvMtx);


void __RPC_STUB IVMouse_GetXY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVMouse_GetAllEvents_Proxy( 
    IVMouse __RPC_FAR * This,
    /* [out] */ VARIANT __RPC_FAR *pvMtx);


void __RPC_STUB IVMouse_GetAllEvents_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVMouse_GetDownEvents_Proxy( 
    IVMouse __RPC_FAR * This,
    /* [out] */ VARIANT __RPC_FAR *pvMtx);


void __RPC_STUB IVMouse_GetDownEvents_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVMouse_GetUpEvents_Proxy( 
    IVMouse __RPC_FAR * This,
    /* [out] */ VARIANT __RPC_FAR *pvMtx);


void __RPC_STUB IVMouse_GetUpEvents_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVMouse_GetDblclickEvents_Proxy( 
    IVMouse __RPC_FAR * This,
    /* [out] */ VARIANT __RPC_FAR *pvMtx);


void __RPC_STUB IVMouse_GetDblclickEvents_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVMouse_ClearEvents_Proxy( 
    IVMouse __RPC_FAR * This);


void __RPC_STUB IVMouse_ClearEvents_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVMouse_Show_Proxy( 
    IVMouse __RPC_FAR * This);


void __RPC_STUB IVMouse_Show_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVMouse_Hide_Proxy( 
    IVMouse __RPC_FAR * This);


void __RPC_STUB IVMouse_Hide_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVMouse_INTERFACE_DEFINED__ */


#ifndef __IVComplexShape_INTERFACE_DEFINED__
#define __IVComplexShape_INTERFACE_DEFINED__

/* interface IVComplexShape */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IVComplexShape;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0C1E4878-2C44-4A45-B6B5-0EA5B9F28402")
    IVComplexShape : public IDispatch
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetXY( 
            /* [out] */ VARIANT __RPC_FAR *pvXY) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetXY( 
            /* [in] */ VARIANT vXY,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetZ( 
            /* [out] */ double __RPC_FAR *pdZ) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetZ( 
            /* [in] */ double dZ,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetScale( 
            /* [out] */ double __RPC_FAR *pdScale) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetScale( 
            /* [in] */ double dScale,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetAngle( 
            /* [out] */ double __RPC_FAR *pdAngle) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetAngle( 
            /* [in] */ double dAngle,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetColor( 
            /* [out] */ VARIANT __RPC_FAR *pvColors) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetColor( 
            /* [in] */ VARIANT vColors,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetAlpha( 
            /* [out] */ double __RPC_FAR *pdAlpha) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetAlpha( 
            /* [in] */ double dAlpha,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetFillFlag( 
            /* [out] */ long __RPC_FAR *piFillFlag) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetFillFlag( 
            /* [in] */ long iFillFlag,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetShowFlag( 
            /* [out] */ long __RPC_FAR *piShowFlag) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetShowFlag( 
            /* [in] */ long iShowFlag,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetGroupID( 
            /* [out] */ long __RPC_FAR *piGroupID) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetGroupID( 
            /* [in] */ long iGroupID) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetClippedCount( 
            /* [out] */ long __RPC_FAR *piClippedCount) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Move( 
            /* [in] */ VARIANT vXY,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Scale( 
            /* [in] */ double dScale,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Rotate( 
            /* [in] */ double dAngle,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Show( 
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Hide( 
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetDrawMode( 
            /* [out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetDrawMode( 
            /* [in] */ BSTR newVal,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetExact( 
            /* [out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetExact( 
            /* [in] */ double newVal,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetVertices( 
            /* [out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetVertices( 
            /* [in] */ VARIANT newVal,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetColors( 
            /* [out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetColors( 
            /* [in] */ VARIANT newVal,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetPointSize( 
            /* [out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetPointSize( 
            /* [in] */ double newVal,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetLineWidth( 
            /* [out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetLineWidth( 
            /* [in] */ double newVal,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetLineStipple( 
            /* [out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetLineStipple( 
            /* [in] */ double newVal,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetLineStippleFactor( 
            /* [out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetLineStippleFactor( 
            /* [in] */ double newVal,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetPolygonStipple( 
            /* [out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetPolygonStipple( 
            /* [in] */ VARIANT newVal,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetIndices( 
            /* [out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetIndices( 
            /* [in] */ VARIANT newVal,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetEdgeFlags( 
            /* [out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetEdgeFlags( 
            /* [in] */ VARIANT newVal,
            /* [defaultvalue][in] */ long iLogID = 0) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVComplexShapeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IVComplexShape __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IVComplexShape __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IVComplexShape __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IVComplexShape __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IVComplexShape __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IVComplexShape __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IVComplexShape __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetXY )( 
            IVComplexShape __RPC_FAR * This,
            /* [out] */ VARIANT __RPC_FAR *pvXY);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetXY )( 
            IVComplexShape __RPC_FAR * This,
            /* [in] */ VARIANT vXY,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetZ )( 
            IVComplexShape __RPC_FAR * This,
            /* [out] */ double __RPC_FAR *pdZ);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetZ )( 
            IVComplexShape __RPC_FAR * This,
            /* [in] */ double dZ,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetScale )( 
            IVComplexShape __RPC_FAR * This,
            /* [out] */ double __RPC_FAR *pdScale);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetScale )( 
            IVComplexShape __RPC_FAR * This,
            /* [in] */ double dScale,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAngle )( 
            IVComplexShape __RPC_FAR * This,
            /* [out] */ double __RPC_FAR *pdAngle);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAngle )( 
            IVComplexShape __RPC_FAR * This,
            /* [in] */ double dAngle,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetColor )( 
            IVComplexShape __RPC_FAR * This,
            /* [out] */ VARIANT __RPC_FAR *pvColors);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetColor )( 
            IVComplexShape __RPC_FAR * This,
            /* [in] */ VARIANT vColors,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAlpha )( 
            IVComplexShape __RPC_FAR * This,
            /* [out] */ double __RPC_FAR *pdAlpha);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAlpha )( 
            IVComplexShape __RPC_FAR * This,
            /* [in] */ double dAlpha,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFillFlag )( 
            IVComplexShape __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *piFillFlag);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetFillFlag )( 
            IVComplexShape __RPC_FAR * This,
            /* [in] */ long iFillFlag,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetShowFlag )( 
            IVComplexShape __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *piShowFlag);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetShowFlag )( 
            IVComplexShape __RPC_FAR * This,
            /* [in] */ long iShowFlag,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetGroupID )( 
            IVComplexShape __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *piGroupID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetGroupID )( 
            IVComplexShape __RPC_FAR * This,
            /* [in] */ long iGroupID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetClippedCount )( 
            IVComplexShape __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *piClippedCount);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Move )( 
            IVComplexShape __RPC_FAR * This,
            /* [in] */ VARIANT vXY,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Scale )( 
            IVComplexShape __RPC_FAR * This,
            /* [in] */ double dScale,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Rotate )( 
            IVComplexShape __RPC_FAR * This,
            /* [in] */ double dAngle,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Show )( 
            IVComplexShape __RPC_FAR * This,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Hide )( 
            IVComplexShape __RPC_FAR * This,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDrawMode )( 
            IVComplexShape __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetDrawMode )( 
            IVComplexShape __RPC_FAR * This,
            /* [in] */ BSTR newVal,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetExact )( 
            IVComplexShape __RPC_FAR * This,
            /* [out] */ double __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetExact )( 
            IVComplexShape __RPC_FAR * This,
            /* [in] */ double newVal,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetVertices )( 
            IVComplexShape __RPC_FAR * This,
            /* [out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetVertices )( 
            IVComplexShape __RPC_FAR * This,
            /* [in] */ VARIANT newVal,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetColors )( 
            IVComplexShape __RPC_FAR * This,
            /* [out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetColors )( 
            IVComplexShape __RPC_FAR * This,
            /* [in] */ VARIANT newVal,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPointSize )( 
            IVComplexShape __RPC_FAR * This,
            /* [out] */ double __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPointSize )( 
            IVComplexShape __RPC_FAR * This,
            /* [in] */ double newVal,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLineWidth )( 
            IVComplexShape __RPC_FAR * This,
            /* [out] */ double __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetLineWidth )( 
            IVComplexShape __RPC_FAR * This,
            /* [in] */ double newVal,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLineStipple )( 
            IVComplexShape __RPC_FAR * This,
            /* [out] */ double __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetLineStipple )( 
            IVComplexShape __RPC_FAR * This,
            /* [in] */ double newVal,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLineStippleFactor )( 
            IVComplexShape __RPC_FAR * This,
            /* [out] */ double __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetLineStippleFactor )( 
            IVComplexShape __RPC_FAR * This,
            /* [in] */ double newVal,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPolygonStipple )( 
            IVComplexShape __RPC_FAR * This,
            /* [out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPolygonStipple )( 
            IVComplexShape __RPC_FAR * This,
            /* [in] */ VARIANT newVal,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIndices )( 
            IVComplexShape __RPC_FAR * This,
            /* [out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetIndices )( 
            IVComplexShape __RPC_FAR * This,
            /* [in] */ VARIANT newVal,
            /* [defaultvalue][in] */ long iLogID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEdgeFlags )( 
            IVComplexShape __RPC_FAR * This,
            /* [out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetEdgeFlags )( 
            IVComplexShape __RPC_FAR * This,
            /* [in] */ VARIANT newVal,
            /* [defaultvalue][in] */ long iLogID);
        
        END_INTERFACE
    } IVComplexShapeVtbl;

    interface IVComplexShape
    {
        CONST_VTBL struct IVComplexShapeVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVComplexShape_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVComplexShape_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVComplexShape_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVComplexShape_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IVComplexShape_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IVComplexShape_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IVComplexShape_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IVComplexShape_GetXY(This,pvXY)	\
    (This)->lpVtbl -> GetXY(This,pvXY)

#define IVComplexShape_SetXY(This,vXY,iLogID)	\
    (This)->lpVtbl -> SetXY(This,vXY,iLogID)

#define IVComplexShape_GetZ(This,pdZ)	\
    (This)->lpVtbl -> GetZ(This,pdZ)

#define IVComplexShape_SetZ(This,dZ,iLogID)	\
    (This)->lpVtbl -> SetZ(This,dZ,iLogID)

#define IVComplexShape_GetScale(This,pdScale)	\
    (This)->lpVtbl -> GetScale(This,pdScale)

#define IVComplexShape_SetScale(This,dScale,iLogID)	\
    (This)->lpVtbl -> SetScale(This,dScale,iLogID)

#define IVComplexShape_GetAngle(This,pdAngle)	\
    (This)->lpVtbl -> GetAngle(This,pdAngle)

#define IVComplexShape_SetAngle(This,dAngle,iLogID)	\
    (This)->lpVtbl -> SetAngle(This,dAngle,iLogID)

#define IVComplexShape_GetColor(This,pvColors)	\
    (This)->lpVtbl -> GetColor(This,pvColors)

#define IVComplexShape_SetColor(This,vColors,iLogID)	\
    (This)->lpVtbl -> SetColor(This,vColors,iLogID)

#define IVComplexShape_GetAlpha(This,pdAlpha)	\
    (This)->lpVtbl -> GetAlpha(This,pdAlpha)

#define IVComplexShape_SetAlpha(This,dAlpha,iLogID)	\
    (This)->lpVtbl -> SetAlpha(This,dAlpha,iLogID)

#define IVComplexShape_GetFillFlag(This,piFillFlag)	\
    (This)->lpVtbl -> GetFillFlag(This,piFillFlag)

#define IVComplexShape_SetFillFlag(This,iFillFlag,iLogID)	\
    (This)->lpVtbl -> SetFillFlag(This,iFillFlag,iLogID)

#define IVComplexShape_GetShowFlag(This,piShowFlag)	\
    (This)->lpVtbl -> GetShowFlag(This,piShowFlag)

#define IVComplexShape_SetShowFlag(This,iShowFlag,iLogID)	\
    (This)->lpVtbl -> SetShowFlag(This,iShowFlag,iLogID)

#define IVComplexShape_GetGroupID(This,piGroupID)	\
    (This)->lpVtbl -> GetGroupID(This,piGroupID)

#define IVComplexShape_SetGroupID(This,iGroupID)	\
    (This)->lpVtbl -> SetGroupID(This,iGroupID)

#define IVComplexShape_GetClippedCount(This,piClippedCount)	\
    (This)->lpVtbl -> GetClippedCount(This,piClippedCount)

#define IVComplexShape_Move(This,vXY,iLogID)	\
    (This)->lpVtbl -> Move(This,vXY,iLogID)

#define IVComplexShape_Scale(This,dScale,iLogID)	\
    (This)->lpVtbl -> Scale(This,dScale,iLogID)

#define IVComplexShape_Rotate(This,dAngle,iLogID)	\
    (This)->lpVtbl -> Rotate(This,dAngle,iLogID)

#define IVComplexShape_Show(This,iLogID)	\
    (This)->lpVtbl -> Show(This,iLogID)

#define IVComplexShape_Hide(This,iLogID)	\
    (This)->lpVtbl -> Hide(This,iLogID)

#define IVComplexShape_GetDrawMode(This,pVal)	\
    (This)->lpVtbl -> GetDrawMode(This,pVal)

#define IVComplexShape_SetDrawMode(This,newVal,iLogID)	\
    (This)->lpVtbl -> SetDrawMode(This,newVal,iLogID)

#define IVComplexShape_GetExact(This,pVal)	\
    (This)->lpVtbl -> GetExact(This,pVal)

#define IVComplexShape_SetExact(This,newVal,iLogID)	\
    (This)->lpVtbl -> SetExact(This,newVal,iLogID)

#define IVComplexShape_GetVertices(This,pVal)	\
    (This)->lpVtbl -> GetVertices(This,pVal)

#define IVComplexShape_SetVertices(This,newVal,iLogID)	\
    (This)->lpVtbl -> SetVertices(This,newVal,iLogID)

#define IVComplexShape_GetColors(This,pVal)	\
    (This)->lpVtbl -> GetColors(This,pVal)

#define IVComplexShape_SetColors(This,newVal,iLogID)	\
    (This)->lpVtbl -> SetColors(This,newVal,iLogID)

#define IVComplexShape_GetPointSize(This,pVal)	\
    (This)->lpVtbl -> GetPointSize(This,pVal)

#define IVComplexShape_SetPointSize(This,newVal,iLogID)	\
    (This)->lpVtbl -> SetPointSize(This,newVal,iLogID)

#define IVComplexShape_GetLineWidth(This,pVal)	\
    (This)->lpVtbl -> GetLineWidth(This,pVal)

#define IVComplexShape_SetLineWidth(This,newVal,iLogID)	\
    (This)->lpVtbl -> SetLineWidth(This,newVal,iLogID)

#define IVComplexShape_GetLineStipple(This,pVal)	\
    (This)->lpVtbl -> GetLineStipple(This,pVal)

#define IVComplexShape_SetLineStipple(This,newVal,iLogID)	\
    (This)->lpVtbl -> SetLineStipple(This,newVal,iLogID)

#define IVComplexShape_GetLineStippleFactor(This,pVal)	\
    (This)->lpVtbl -> GetLineStippleFactor(This,pVal)

#define IVComplexShape_SetLineStippleFactor(This,newVal,iLogID)	\
    (This)->lpVtbl -> SetLineStippleFactor(This,newVal,iLogID)

#define IVComplexShape_GetPolygonStipple(This,pVal)	\
    (This)->lpVtbl -> GetPolygonStipple(This,pVal)

#define IVComplexShape_SetPolygonStipple(This,newVal,iLogID)	\
    (This)->lpVtbl -> SetPolygonStipple(This,newVal,iLogID)

#define IVComplexShape_GetIndices(This,pVal)	\
    (This)->lpVtbl -> GetIndices(This,pVal)

#define IVComplexShape_SetIndices(This,newVal,iLogID)	\
    (This)->lpVtbl -> SetIndices(This,newVal,iLogID)

#define IVComplexShape_GetEdgeFlags(This,pVal)	\
    (This)->lpVtbl -> GetEdgeFlags(This,pVal)

#define IVComplexShape_SetEdgeFlags(This,newVal,iLogID)	\
    (This)->lpVtbl -> SetEdgeFlags(This,newVal,iLogID)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVComplexShape_GetXY_Proxy( 
    IVComplexShape __RPC_FAR * This,
    /* [out] */ VARIANT __RPC_FAR *pvXY);


void __RPC_STUB IVComplexShape_GetXY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVComplexShape_SetXY_Proxy( 
    IVComplexShape __RPC_FAR * This,
    /* [in] */ VARIANT vXY,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVComplexShape_SetXY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVComplexShape_GetZ_Proxy( 
    IVComplexShape __RPC_FAR * This,
    /* [out] */ double __RPC_FAR *pdZ);


void __RPC_STUB IVComplexShape_GetZ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVComplexShape_SetZ_Proxy( 
    IVComplexShape __RPC_FAR * This,
    /* [in] */ double dZ,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVComplexShape_SetZ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVComplexShape_GetScale_Proxy( 
    IVComplexShape __RPC_FAR * This,
    /* [out] */ double __RPC_FAR *pdScale);


void __RPC_STUB IVComplexShape_GetScale_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVComplexShape_SetScale_Proxy( 
    IVComplexShape __RPC_FAR * This,
    /* [in] */ double dScale,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVComplexShape_SetScale_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVComplexShape_GetAngle_Proxy( 
    IVComplexShape __RPC_FAR * This,
    /* [out] */ double __RPC_FAR *pdAngle);


void __RPC_STUB IVComplexShape_GetAngle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVComplexShape_SetAngle_Proxy( 
    IVComplexShape __RPC_FAR * This,
    /* [in] */ double dAngle,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVComplexShape_SetAngle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVComplexShape_GetColor_Proxy( 
    IVComplexShape __RPC_FAR * This,
    /* [out] */ VARIANT __RPC_FAR *pvColors);


void __RPC_STUB IVComplexShape_GetColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVComplexShape_SetColor_Proxy( 
    IVComplexShape __RPC_FAR * This,
    /* [in] */ VARIANT vColors,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVComplexShape_SetColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVComplexShape_GetAlpha_Proxy( 
    IVComplexShape __RPC_FAR * This,
    /* [out] */ double __RPC_FAR *pdAlpha);


void __RPC_STUB IVComplexShape_GetAlpha_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVComplexShape_SetAlpha_Proxy( 
    IVComplexShape __RPC_FAR * This,
    /* [in] */ double dAlpha,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVComplexShape_SetAlpha_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVComplexShape_GetFillFlag_Proxy( 
    IVComplexShape __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *piFillFlag);


void __RPC_STUB IVComplexShape_GetFillFlag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVComplexShape_SetFillFlag_Proxy( 
    IVComplexShape __RPC_FAR * This,
    /* [in] */ long iFillFlag,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVComplexShape_SetFillFlag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVComplexShape_GetShowFlag_Proxy( 
    IVComplexShape __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *piShowFlag);


void __RPC_STUB IVComplexShape_GetShowFlag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVComplexShape_SetShowFlag_Proxy( 
    IVComplexShape __RPC_FAR * This,
    /* [in] */ long iShowFlag,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVComplexShape_SetShowFlag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVComplexShape_GetGroupID_Proxy( 
    IVComplexShape __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *piGroupID);


void __RPC_STUB IVComplexShape_GetGroupID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVComplexShape_SetGroupID_Proxy( 
    IVComplexShape __RPC_FAR * This,
    /* [in] */ long iGroupID);


void __RPC_STUB IVComplexShape_SetGroupID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVComplexShape_GetClippedCount_Proxy( 
    IVComplexShape __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *piClippedCount);


void __RPC_STUB IVComplexShape_GetClippedCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVComplexShape_Move_Proxy( 
    IVComplexShape __RPC_FAR * This,
    /* [in] */ VARIANT vXY,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVComplexShape_Move_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVComplexShape_Scale_Proxy( 
    IVComplexShape __RPC_FAR * This,
    /* [in] */ double dScale,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVComplexShape_Scale_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVComplexShape_Rotate_Proxy( 
    IVComplexShape __RPC_FAR * This,
    /* [in] */ double dAngle,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVComplexShape_Rotate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVComplexShape_Show_Proxy( 
    IVComplexShape __RPC_FAR * This,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVComplexShape_Show_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVComplexShape_Hide_Proxy( 
    IVComplexShape __RPC_FAR * This,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVComplexShape_Hide_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVComplexShape_GetDrawMode_Proxy( 
    IVComplexShape __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IVComplexShape_GetDrawMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVComplexShape_SetDrawMode_Proxy( 
    IVComplexShape __RPC_FAR * This,
    /* [in] */ BSTR newVal,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVComplexShape_SetDrawMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVComplexShape_GetExact_Proxy( 
    IVComplexShape __RPC_FAR * This,
    /* [out] */ double __RPC_FAR *pVal);


void __RPC_STUB IVComplexShape_GetExact_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVComplexShape_SetExact_Proxy( 
    IVComplexShape __RPC_FAR * This,
    /* [in] */ double newVal,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVComplexShape_SetExact_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVComplexShape_GetVertices_Proxy( 
    IVComplexShape __RPC_FAR * This,
    /* [out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVComplexShape_GetVertices_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVComplexShape_SetVertices_Proxy( 
    IVComplexShape __RPC_FAR * This,
    /* [in] */ VARIANT newVal,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVComplexShape_SetVertices_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVComplexShape_GetColors_Proxy( 
    IVComplexShape __RPC_FAR * This,
    /* [out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVComplexShape_GetColors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVComplexShape_SetColors_Proxy( 
    IVComplexShape __RPC_FAR * This,
    /* [in] */ VARIANT newVal,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVComplexShape_SetColors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVComplexShape_GetPointSize_Proxy( 
    IVComplexShape __RPC_FAR * This,
    /* [out] */ double __RPC_FAR *pVal);


void __RPC_STUB IVComplexShape_GetPointSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVComplexShape_SetPointSize_Proxy( 
    IVComplexShape __RPC_FAR * This,
    /* [in] */ double newVal,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVComplexShape_SetPointSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVComplexShape_GetLineWidth_Proxy( 
    IVComplexShape __RPC_FAR * This,
    /* [out] */ double __RPC_FAR *pVal);


void __RPC_STUB IVComplexShape_GetLineWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVComplexShape_SetLineWidth_Proxy( 
    IVComplexShape __RPC_FAR * This,
    /* [in] */ double newVal,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVComplexShape_SetLineWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVComplexShape_GetLineStipple_Proxy( 
    IVComplexShape __RPC_FAR * This,
    /* [out] */ double __RPC_FAR *pVal);


void __RPC_STUB IVComplexShape_GetLineStipple_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVComplexShape_SetLineStipple_Proxy( 
    IVComplexShape __RPC_FAR * This,
    /* [in] */ double newVal,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVComplexShape_SetLineStipple_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVComplexShape_GetLineStippleFactor_Proxy( 
    IVComplexShape __RPC_FAR * This,
    /* [out] */ double __RPC_FAR *pVal);


void __RPC_STUB IVComplexShape_GetLineStippleFactor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVComplexShape_SetLineStippleFactor_Proxy( 
    IVComplexShape __RPC_FAR * This,
    /* [in] */ double newVal,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVComplexShape_SetLineStippleFactor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVComplexShape_GetPolygonStipple_Proxy( 
    IVComplexShape __RPC_FAR * This,
    /* [out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVComplexShape_GetPolygonStipple_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVComplexShape_SetPolygonStipple_Proxy( 
    IVComplexShape __RPC_FAR * This,
    /* [in] */ VARIANT newVal,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVComplexShape_SetPolygonStipple_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVComplexShape_GetIndices_Proxy( 
    IVComplexShape __RPC_FAR * This,
    /* [out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVComplexShape_GetIndices_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVComplexShape_SetIndices_Proxy( 
    IVComplexShape __RPC_FAR * This,
    /* [in] */ VARIANT newVal,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVComplexShape_SetIndices_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVComplexShape_GetEdgeFlags_Proxy( 
    IVComplexShape __RPC_FAR * This,
    /* [out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVComplexShape_GetEdgeFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVComplexShape_SetEdgeFlags_Proxy( 
    IVComplexShape __RPC_FAR * This,
    /* [in] */ VARIANT newVal,
    /* [defaultvalue][in] */ long iLogID);


void __RPC_STUB IVComplexShape_SetEdgeFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVComplexShape_INTERFACE_DEFINED__ */



#ifndef __CP_DISPLAYLib_LIBRARY_DEFINED__
#define __CP_DISPLAYLib_LIBRARY_DEFINED__

/* library CP_DISPLAYLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_CP_DISPLAYLib;

EXTERN_C const CLSID CLSID_VMain;

#ifdef __cplusplus

class DECLSPEC_UUID("ebd33088-ceb1-11d5-9c3e-0050da2a68c8")
VMain;
#endif

EXTERN_C const CLSID CLSID_VDisk;

#ifdef __cplusplus

class DECLSPEC_UUID("ebd33090-ceb1-11d5-9c3e-0050da2a68c8")
VDisk;
#endif

EXTERN_C const CLSID CLSID_VPolygon;

#ifdef __cplusplus

class DECLSPEC_UUID("ebd33098-ceb1-11d5-9c3e-0050da2a68c8")
VPolygon;
#endif

EXTERN_C const CLSID CLSID_VText;

#ifdef __cplusplus

class DECLSPEC_UUID("ebd330a0-ceb1-11d5-9c3e-0050da2a68c8")
VText;
#endif

EXTERN_C const CLSID CLSID_VMouse;

#ifdef __cplusplus

class DECLSPEC_UUID("ebd330a8-ceb1-11d5-9c3e-0050da2a68c8")
VMouse;
#endif

EXTERN_C const CLSID CLSID_VComplexShape;

#ifdef __cplusplus

class DECLSPEC_UUID("015EA1C0-B904-4D55-B4F7-C195665FEF69")
VComplexShape;
#endif
#endif /* __CP_DISPLAYLib_LIBRARY_DEFINED__ */

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
