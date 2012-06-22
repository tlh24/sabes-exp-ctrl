#ifndef __VDISK_H_
#define __VDISK_H_

#include "VObject.h"

class CVDisk : 
  public IDispatchImpl<IVDisk, &IID_IVDisk, &LIBID_CP_DISPLAYLib>, 
  public CComObjectRoot,
  public CComCoClass<CVDisk,&CLSID_VDisk>, 
  public CVObject 
{
public:
BEGIN_COM_MAP(CVDisk)
  COM_INTERFACE_ENTRY(IDispatch)
  COM_INTERFACE_ENTRY(IVDisk)
END_COM_MAP()

DECLARE_NOT_AGGREGATABLE(CVDisk) 
DECLARE_REGISTRY_RESOURCEID(IDR_VDisk)

  CVDisk();
  ~CVDisk();

// common methods
#include "VObjectMethodsDecl.h"

// disk-specific methods
  STDMETHOD(GetRadius)( VARIANT *pvRadius );
  STDMETHOD(SetRadius)( double dRadius, long iLogID );
  STDMETHOD(GetN_Vertices)( long *pnVertices);
  STDMETHOD(SetN_Vertices)( long nVertices, long iLogID );

  void Draw();   // virtual method

private:
  int   m_nVertices;
  float * m_afScrnVtxX;
  float * m_afScrnVtxY;

  void m_CalcScrnVertices();
  void m_NewVertices();

};

#endif //__VDISK_H_


