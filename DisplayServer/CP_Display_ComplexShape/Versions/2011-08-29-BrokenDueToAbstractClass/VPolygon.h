#ifndef __VPOLYGON_H_
#define __VPOLYGON_H_

#include "VObject.h"
#include <gl\gl.h>               // Header File For The OpenGL32 Library
#include <gl\glu.h>              // Header File For The GLu32 Library

#define VPOLYGON_MAXTEXW 512
#define VPOLYGON_MAXTEXH 512

typedef struct XY_VtxStructTag {
  double dX;
  double dY;
} XY_VtxStruct;

typedef struct ScrnVtxStructTag {
  double dX;
  double dY;
  double dZ;
  double dTexX;
  double dTexY;
} ScrnVtxStruct;



class CVPolygon : 
  public IDispatchImpl<IVPolygon, &IID_IVPolygon, &LIBID_CP_DISPLAYLib>,
  public CComObjectRoot,
  public CComCoClass<CVPolygon, &CLSID_VPolygon>,
  public CVObject  
{
public:
BEGIN_COM_MAP(CVPolygon)
  COM_INTERFACE_ENTRY(IDispatch)
  COM_INTERFACE_ENTRY(IVPolygon)
END_COM_MAP()

DECLARE_NOT_AGGREGATABLE(CVPolygon) 
DECLARE_REGISTRY_RESOURCEID(IDR_VPolygon)

  CVPolygon();
  ~CVPolygon();

// common methods
#include "VObjectMethodsDecl.h"

// polygon-specific methods
  STDMETHOD(GetVertices)(VARIANT * pvVertices);
  STDMETHOD(SetVertices)(VARIANT vVertices, long iLogID);
  STDMETHOD(GetTexture)(VARIANT * pvTexture,
                        long * pnPixelsW,
                        long * pnPixelsH,
                        double * pdTexturePhysWidth );
  STDMETHOD(SetTexture)(VARIANT vTexture,
                        double dTexturePhysWidth,
                        long iLogID);
  STDMETHOD(GetTextureFlag)( long * plngTextureFlag);
  STDMETHOD(SetTextureFlag)( long lngTextureFlag, long iLogID);
  
  int   m_nTessVtx;         // used in the tessellator callback
  ScrnVtxStruct * m_atTessVtx;    // used in the tessellator callback
  int    m_iUseTexture;   // used in the tessellator callback
  void Draw();
  
private:
  int    m_nVertices;
  GLuint m_uiTextureID;
  int    m_nTextureW;
  int    m_nTextureH;
  double m_dTexturePhysWidth;
  float * m_pfTexture;


  XY_VtxStruct * m_atPhysVtx;
  ScrnVtxStruct * m_atScrnVtx;  // should be persistent!!!

  GLUtesselator   *m_Tess;  // should be persistent!!!
  
  void m_CalcScrnVertices();
  void m_NewVertices();
  void m_NewTexture( double * pdData );

};
  
#endif //__VPOLYGON_H_
