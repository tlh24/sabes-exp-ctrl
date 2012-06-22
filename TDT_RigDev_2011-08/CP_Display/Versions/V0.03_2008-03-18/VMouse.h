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
  STDMETHOD(GetXY)( SAFEARRAY ** ppsaMtx);
  STDMETHOD(GetAllEvents)(SAFEARRAY ** ppsaMtx);
  STDMETHOD(GetDownEvents)(SAFEARRAY ** ppsaMtx);
  STDMETHOD(GetUpEvents)(SAFEARRAY ** ppsaMtx);
  STDMETHOD(GetDblclickEvents)(SAFEARRAY ** ppsaMtx);
  STDMETHOD(ClearEvents)();
  STDMETHOD(Show)();
  STDMETHOD(Hide)();

};


#endif //__VMOUSE_H_
