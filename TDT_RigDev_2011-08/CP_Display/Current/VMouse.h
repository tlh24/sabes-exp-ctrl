#ifndef __VMOUSE_H_
#define __VMOUSE_H_


class CVMouse : 
  public IDispatchImpl<IVMouse, &IID_IVMouse, &LIBID_CP_DISPLAYLib>, 
  public CComObjectRoot,
  public CComCoClass<CVMouse,&CLSID_VMouse>
{
public:
BEGIN_COM_MAP(CVMouse)
  COM_INTERFACE_ENTRY(IDispatch)
  COM_INTERFACE_ENTRY(IVMouse)
END_COM_MAP()
    
DECLARE_REGISTRY_RESOURCEID(IDR_VMouse)

  
  CVMouse();
  ~CVMouse();
  STDMETHOD(GetShowFlag)(long * piShowFlag);
  STDMETHOD(SetShowFlag)(long iShowFlag);
  STDMETHOD(GetXY)( VARIANT * pvMtx);
  STDMETHOD(GetAllEvents)(VARIANT * pvMtx);
  STDMETHOD(GetDownEvents)(VARIANT * pvMtx);
  STDMETHOD(GetUpEvents)(VARIANT * pvMtx);
  STDMETHOD(GetDblclickEvents)(VARIANT * pvMtx);
  STDMETHOD(ClearEvents)();
  STDMETHOD(Show)();
  STDMETHOD(Hide)();

};


#endif //__VMOUSE_H_
