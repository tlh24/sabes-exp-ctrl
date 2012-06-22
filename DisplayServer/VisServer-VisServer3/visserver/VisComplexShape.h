// VisComplexShape.h : Declaration of the CVisComplexShape

#ifndef __VISCOMPLEXSHAPE_H_
#define __VISCOMPLEXSHAPE_H_

#include "resource.h"       // main symbols
#include "VisWindowActionLog.h"
#include "VisWindow.h"

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
// CVisComplexShape
class CVisComplexShape : 
	public IDispatchImpl<IVisComplexShape, &IID_IVisComplexShape, &LIBID_VISSERVERLib>,
	public ISupportErrorInfo,
	public CComObjectRoot,
	public CComCoClass<CVisComplexShape, &CLSID_VisComplexShape>,
	public CVisObject
/*
class ATL_NO_VTABLE CVisComplexShape : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CVisComplexShape, &CLSID_VisComplexShape>,
	public ISupportErrorInfo,
	public IDispatchImpl<IVisComplexShape, &IID_IVisComplexShape, &LIBID_VISSERVERLib>
*/
{
public:
	CVisComplexShape();
	~CVisComplexShape();

DECLARE_REGISTRY_RESOURCEID(IDR_VISCOMPLEXSHAPE)

//DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CVisComplexShape)
	COM_INTERFACE_ENTRY(IVisComplexShape)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IVisComplexShape
public:
	STDMETHOD(get_drawMode)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_drawMode)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_pointSize)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_pointSize)(/*[in]*/ double newVal);
	STDMETHOD(get_lineWidth)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_lineWidth)(/*[in]*/ double newVal);
	STDMETHOD(get_lineStippleFactor)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_lineStippleFactor)(/*[in]*/ double newVal);
	STDMETHOD(get_lineStipple)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_lineStipple)(/*[in]*/ double newVal);
	STDMETHOD(get_polygonStipple)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_polygonStipple)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_indices)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_indices)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_edgeFlags)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_edgeFlags)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_colors)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_colors)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_vertices)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_vertices)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_color)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_color)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_exact)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_exact)(/*[in]*/ double newVal);
	STDMETHOD(get_angle)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_angle)(/*[in]*/ double newVal);
	STDMETHOD(get_scale)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_scale)(/*[in]*/ double newVal);
	STDMETHOD(get_clipped)(/*[out, retval]*/ double *pVal);
//	STDMETHOD(get_errstring)(/*[out, retval]*/ BSTR *pVal);
//	STDMETHOD(get_z)(/*[out, retval]*/ double *pVal);
//	STDMETHOD(put_z)(/*[in]*/ double newVal);
//	STDMETHOD(get_pos)(/*[out, retval]*/ VARIANT *pVal);
//	STDMETHOD(put_pos)(/*[in]*/ VARIANT newVal);
//	STDMETHOD(get_show)(/*[out, retval]*/ double *pVal);
//	STDMETHOD(put_show)(/*[in]*/ double newVal);
//	STDMETHOD(get_tag)(/*[out, retval]*/ double *pVal);

	STDMETHOD(get_show)(/*[out, retval]*/ double *pVal)		{ return CVisObject::get_show(pVal); };
	STDMETHOD(put_show)(/*[in]*/ double newVal)				{ return CVisObject::put_show(newVal); };
	STDMETHOD(get_z)(/*[out, retval]*/ double *pVal)		{ return CVisObject::get_z(pVal); };
	STDMETHOD(put_z)(/*[in]*/ double newVal)				{ return CVisObject::put_z(newVal); };
	STDMETHOD(get_tag)(/*[out, retval]*/ double *pVal)	    { return CVisObject::get_tag(pVal); };
	STDMETHOD(get_errstring)(/*[out, retval]*/ BSTR *pVal)	{ return CVisObject::get_errstring(pVal); };
	STDMETHOD(get_pos)(/*[out, retval]*/ VARIANT *pVal)		{ return CVisObject::get_pos(pVal); };
	STDMETHOD(put_pos)(/*[in]*/ VARIANT newVal)
    {
        HRESULT result = CVisObject::put_pos(newVal);
        if (result == S_OK) updateScrVertices();
        return result;
    };

protected:
    enum VArrayIndex {
        aiVertices, aiNormals, aiColors, aiTexCoords, aiEdgeFlags, aiIndices,
        aiPolygonStipple, aiTopIndex,
    };

    double *arrays[aiTopIndex];
    double *scrVertices;
    int          lineStipple;
    int          lineStippleFactor;
    double       lineWidth;
    double       pointSize;
    VOpglDrawMode       drawMode;

	double scale;				// Scaling of Vertices 
	double angle;				// Rotation of Vertices (about Origin)
	float  color[3];            // Color
#if INDEX_MODE
	int   ColorIndex;
#endif
	double alpha;
	int    exact;				// Xform Each Vertex? (Can't use display list in this case)
	float JAC[2][2],ROT[16];    // Jacobian and OpenGL Rotation

	template <class T>
	void update(int action, T *params=NULL, int n=0)
	{
		if(VisWindow && Show){ 
			VisWindow->requestUpdate();
			if(VisWindow->logmode) VisWindow->logAction(tag,action,params,n);
		}
	}

    void updateScrVertices(void);

    void setArray(int index, double *data)
	{
		if (arrays[index] != NULL)  FreeDoubleArray(arrays[index]);
		arrays[index] = data;
		update(ACTION_ARRAYDATA, &index, 1);
	}

	double * getVertices (void)   {   return arrays[aiVertices ];   }
    double * getNormals  (void)   {   return arrays[aiNormals  ];   }
    double * getColors   (void)   {   return arrays[aiColors   ];   }
    double * getTexCoords(void)   {   return arrays[aiTexCoords];   }
    double * getEdgeFlags(void)   {   return arrays[aiEdgeFlags];   }
    double * getIndices  (void)   {   return arrays[aiIndices  ];   }
    void    setVertices (double *data)   {  setArray(aiVertices , data);    }
    void    setNormals  (double *data)   {  setArray(aiNormals  , data);    }
    void    setColors   (double *data)   {  setArray(aiColors   , data);    }
    void    setTexCoords(double *data)   {  setArray(aiTexCoords, data);    }
    void    setEdgeFlags(double *data)   {  setArray(aiEdgeFlags, data);    }
    void    setIndices  (double *data)   {  setArray(aiIndices  , data);    }
    double *getPolygonStipple(void)      {   return arrays[aiPolygonStipple];   }
    void    setPolygonStipple(double *data)   {  setArray(aiPolygonStipple, data);    }

    void setLineStipple(int v)               {  lineStipple = v;       update(ACTION_LINESTIPPLE, &v, 1);  }
    void setLineStippleFactor(int v)         {  lineStippleFactor = v; update(ACTION_LINESTIPPLEFACTOR, &v, 1);  }
    void setLineWidth  (double v)            {  lineWidth   = v;       update(ACTION_LINEWIDTH, &v, 1);  }
    void setPointSize  (double v)            {  pointSize   = v;       update(ACTION_POINTSIZE, &v, 1);  }
    void setDrawMode   (VOpglDrawMode v)     {  drawMode    = v;       update(ACTION_DRAWMODE, (int*)&v, 1);  }

public:
	void draw();
};

#endif //__VISCOMPLEXSHAPE_H_
