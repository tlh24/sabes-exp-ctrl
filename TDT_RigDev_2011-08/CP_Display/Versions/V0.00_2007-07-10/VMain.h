#ifndef __VMAIN_H_
#define __VMAIN_H_

class CVMain : 
  public IDispatchImpl<IVMain, &IID_IVMain, &LIBID_CP_DISPLAYLib>, 
  public CComObjectRoot,
  public CComCoClass<CVMain,&CLSID_VMain>
{
public:
BEGIN_COM_MAP(CVMain)
  COM_INTERFACE_ENTRY(IDispatch)
  COM_INTERFACE_ENTRY(IVMain)
END_COM_MAP()

DECLARE_NOT_AGGREGATABLE(CVMain) 
DECLARE_REGISTRY_RESOURCEID(IDR_VMain)

  CVMain();
  ~CVMain();

  STDMETHOD(GetVersion)( BSTR * pbstVersion );
  STDMETHOD(GetTransformMatrix)( SAFEARRAY **ppsaMatrix);
  STDMETHOD(SetTransformMatrix)(SAFEARRAY * psaMatrix);
  STDMETHOD(StartSync)( );
  STDMETHOD(StopSync)( );
  STDMETHOD(GetTimeScale)( double *pdC0, double *pdC1);
  STDMETHOD(SetTimeScale)( double dC0, double dC1);
  STDMETHOD(StartBatchDraw)();
  STDMETHOD(FinishBatchDraw)( long iLogID );
  STDMETHOD(MoveGroup)(long iGroupID, SAFEARRAY * psaXY, long iLogID );
  STDMETHOD(ScaleGroup)(long iGroupID, double dScale, long iLogID );
  STDMETHOD(RotateGroup)(long iGroupID, double dAngle, long iLogID );
  STDMETHOD(HideGroup)(long iGroupID, long iLogID );
  STDMETHOD(ShowGroup)(long iGroupID, long iLogID );
  STDMETHOD(ResetEventLog)();
  STDMETHOD(GetEventLog)(SAFEARRAY ** ppsaLogID, 
                         SAFEARRAY ** ppsaTimeStampMs );

};

#endif //__VMAIN_H_
