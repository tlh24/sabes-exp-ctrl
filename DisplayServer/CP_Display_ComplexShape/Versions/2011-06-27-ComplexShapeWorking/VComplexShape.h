// VComplexShape.h : Declaration of the CVComplexShape

#ifndef __VCOMPLEXSHAPE_H_
#define __VCOMPLEXSHAPE_H_

#include "resource.h"       // main symbols
#include "VObject.h"


enum VOpglDrawMode {
    odmPoints         ,
    odmLines          ,
    odmLineStrip      ,
    odmLineLoop       ,
    odmTriangles      ,
    odmTriangleStrip  ,
    odmTriangleFan    ,
    odmQuads          ,
    odmQuadStrip      ,
    odmPolygon        ,
};

int VariantToDoubleArray(double **data, VARIANT *var);
int VariantFromDoubleArray(double **data, VARIANT *var);

double *CreateDoubleArray(int dim, int *dimlen);
double *CopyDoubleArray(double *data);
double *CopyDoubleArrayStruct(double *data);
void FreeDoubleArray(double *data);
inline int GetDim(double *data)
{
    return ((int *)data)[-2];
}
inline int GetLength(double *data)
{
    return ((int *)data)[-1];
}
inline int GetLength(double *data, int dim)
{
    return ((int *)data)[-3-dim];
}
inline double &GetAt(double *data, int index0)
{
    return data[index0];
}
inline double &GetAt(double *data, int index0, int index1)
{
    return data[index0 + GetLength(data, 0) * index1];
}
inline double &GetAt(double *data, int index0, int index1, int index2)
{
    return data[index0 + GetLength(data, 0) * (index1 + GetLength(data, 1) * index2)];
}
inline double &GetAt(double *data, int index0, int index1, int index2, int index3)
{
    return data[index0 + GetLength(data, 0) * (index1 + GetLength(data, 1) * (index2 + GetLength(data, 2) * index3))];
}
inline double &GetAt(double *data, int index0, int index1, int index2, int index3, int index4)
{
    return data[index0 + GetLength(data, 0) * (index1 + GetLength(data, 1) * (index2 + GetLength(data, 2) * (index3 + GetLength(data, 3) * index4)))];
}



/////////////////////////////////////////////////////////////////////////////
// CVComplexShape
class CVComplexShape : 
	public IDispatchImpl<IVComplexShape, &IID_IVComplexShape, &LIBID_CP_DISPLAYLib>,
    public CComObjectRoot,
	public CComCoClass<CVComplexShape, &CLSID_VComplexShape>,
	public ISupportErrorInfo,
    public CVObject 
{
public:
BEGIN_COM_MAP(CVComplexShape)
	COM_INTERFACE_ENTRY(IVComplexShape)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

DECLARE_REGISTRY_RESOURCEID(IDR_VCOMPLEXSHAPE)
DECLARE_PROTECT_FINAL_CONSTRUCT()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IVComplexShape
public:
	CVComplexShape();
	~CVComplexShape();

// common methods
#include "VObjectMethodsDecl.h"

// IVComplexShape
	STDMETHOD(GetDrawMode)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(SetDrawMode)(/*[in]*/ BSTR newVal, long iLogID);
	STDMETHOD(GetExact)(/*[out, retval]*/ double *pVal);
	STDMETHOD(SetExact)(/*[in]*/ double newVal, long iLogID);
	STDMETHOD(GetVertices)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(SetVertices)(/*[in]*/ VARIANT newVal, long iLogID);
	STDMETHOD(GetColors)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(SetColors)(/*[in]*/ VARIANT newVal, long iLogID);
	STDMETHOD(GetPointSize)(/*[out, retval]*/ double *pVal);
	STDMETHOD(SetPointSize)(/*[in]*/ double newVal, long iLogID);
	STDMETHOD(GetLineWidth)(/*[out, retval]*/ double *pVal);
	STDMETHOD(SetLineWidth)(/*[in]*/ double newVal, long iLogID);
	STDMETHOD(GetLineStippleFactor)(/*[out, retval]*/ double *pVal);
	STDMETHOD(SetLineStippleFactor)(/*[in]*/ double newVal, long iLogID);
	STDMETHOD(GetLineStipple)(/*[out, retval]*/ double *pVal);
	STDMETHOD(SetLineStipple)(/*[in]*/ double newVal, long iLogID);
	STDMETHOD(GetPolygonStipple)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(SetPolygonStipple)(/*[in]*/ VARIANT newVal, long iLogID);
	STDMETHOD(GetIndices)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(SetIndices)(/*[in]*/ VARIANT newVal, long iLogID);
	STDMETHOD(GetEdgeFlags)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(SetEdgeFlags)(/*[in]*/ VARIANT newVal, long iLogID);
	void Draw();

protected:
    enum VArrayIndex {
        aiVertices, aiColors, aiEdgeFlags, aiIndices,
        aiPolygonStipple, aiTopIndex,
    };

    double		*arrays[aiTopIndex];
    double		*scrVertices;
    int			lineStipple;
    int			lineStippleFactor;
    double		lineWidth;
    double		pointSize;
	int			exact;			// Xform Each Vertex? (Can't use display list in this case)
    VOpglDrawMode       drawMode;
	double JAC[2][2],ROT[16];    // Jacobian and OpenGL Rotation

    void updateScrVertices(void);
    void setArray(int index, double *data)
	{
		if (arrays[index] != NULL)  FreeDoubleArray(arrays[index]);
		arrays[index] = data;
	}

	double * m_getVertices (void)   {   return arrays[aiVertices ];   }
    double * m_getColors   (void)   {   return arrays[aiColors   ];   }
    double * m_getEdgeFlags(void)   {   return arrays[aiEdgeFlags];   }
    double * m_getIndices  (void)   {   return arrays[aiIndices  ];   }
    double * m_getPolygonStipple(void) {   return arrays[aiPolygonStipple];   }
};

#endif //__VCOMPLEXSHAPE_H_
