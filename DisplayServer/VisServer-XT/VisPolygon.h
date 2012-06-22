// VisPolygon.h : Declaration of the CVisPolygon



#ifndef __VISPOLYGON_H_
#define __VISPOLYGON_H_

#include "resource.h"       // main symbols
#include "VisObject.h"

#define VISPOLYGON_MAXTEXW 512
#define VISPOLYGON_MAXTEXH 512

////////////////////////////////////////////////////////////////////////////

// CVisPolygon

class CVisPolygon : 

	public IDispatchImpl<IVisPolygon, &IID_IVisPolygon, &LIBID_VISSERVERLib>,
	public ISupportErrorInfo,
	public CComObjectRoot,
	public CComCoClass<CVisPolygon, &CLSID_VisPolygon>,
	public CVisObject
{

public:

	CVisPolygon();

	~CVisPolygon();

BEGIN_COM_MAP(CVisPolygon)
	COM_INTERFACE_ENTRY(IVisPolygon)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

DECLARE_REGISTRY_RESOURCEID(IDR_VISPOLYGON)

// ISupportsErrorInfo

STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);



// IVisPolygon

public:

	STDMETHOD(get_image)(/*[out, retval]*/ VARIANT *pVal);

	STDMETHOD(put_image)(/*[in]*/ VARIANT newVal);

	// For Some Reason, the DCOM Interface Doesn't See the Inherited Functions, so I'll

	// Make Reimplmented Wrappers (ughhh):



	//STDMETHOD(get_show)(/*[out, retval]*/ double *pVal);

	//STDMETHOD(put_show)(/*[in]*/ double newVal);

	//STDMETHOD(get_pos)(/*[out, retval]*/ VARIANT *pVal);

	//STDMETHOD(put_pos)(/*[in]*/ VARIANT newVal);

	//STDMETHOD(get_z)(/*[out, retval]*/ double *pVal);

	//STDMETHOD(put_z)(/*[in]*/ double newVal);

	//STDMETHOD(get_errstring)(/*[out, retval]*/ BSTR *pVal);



	STDMETHOD(get_show)(/*[out, retval]*/ double *pVal)		{ return CVisObject::get_show(pVal); };

	STDMETHOD(put_show)(/*[in]*/ double newVal)				{ return CVisObject::put_show(newVal); };

	STDMETHOD(get_pos)(/*[out, retval]*/ VARIANT *pVal)		{ return CVisObject::get_pos(pVal); };

	STDMETHOD(put_pos)(/*[in]*/ VARIANT newVal)				{ return CVisObject::put_pos(newVal); };

	STDMETHOD(get_z)(/*[out, retval]*/ double *pVal)		{ return CVisObject::get_z(pVal); };

	STDMETHOD(put_z)(/*[in]*/ double newVal)				{ return CVisObject::put_z(newVal); };

	STDMETHOD(get_tag)(/*[out, retval]*/ double *pVal)	    { return CVisObject::get_tag(pVal); };

	STDMETHOD(get_errstring)(/*[out, retval]*/ BSTR *pVal)	{ return CVisObject::get_errstring(pVal); };



	STDMETHOD(get_exact)(/*[out, retval]*/ double *pVal);

	STDMETHOD(put_exact)(/*[in]*/ double newVal);

	STDMETHOD(get_color)(/*[out, retval]*/ VARIANT *pVal);

	STDMETHOD(put_color)(/*[in]*/ VARIANT newVal);

	STDMETHOD(get_alpha)(/*[out, retval]*/ double *pVal);

	STDMETHOD(put_alpha)(/*[in]*/ double newVal);

	STDMETHOD(get_fill)(/*[out, retval]*/ double *pVal);

	STDMETHOD(put_fill)(/*[in]*/ double newVal);

	STDMETHOD(get_points)(/*[out, retval]*/ VARIANT *pVal);

	STDMETHOD(put_points)(/*[in]*/ VARIANT newVal);

	STDMETHOD(get_angle)(/*[out, retval]*/ double *pVal);

	STDMETHOD(put_angle)(/*[in]*/ double newVal);

	STDMETHOD(get_scale)(/*[out, retval]*/ double *pVal);

	STDMETHOD(put_scale)(/*[in]*/ double newVal);

	STDMETHOD(get_clipped)(/*[out, retval]*/ double *pVal);

	

	void draw();

	

private:

	

	int   NPoints;

	double **Points;				// Raw Vertex locations w.r.t Origin

	double **ScrPoints;			// Screen Transformed Vertex locations

	double Scale;				// Scaling of Vertices 

	double Angle;				// Rotation of Vertices (about Origin)

	float Color[3];  // Color

#if INDEX_MODE

	int   ColorIndex;

#endif

	float Alpha;

	int   Fill;					// Fill Flag

	int   Exact;				// Xform Each Vertex? (Can't use display list in this case)

	float JAC[2][2],ROT[16];    // Jacobian and OpenGL Rotation



	GLubyte textureImage[VISPOLYGON_MAXTEXW][VISPOLYGON_MAXTEXH][3];

	int  textureFlag;

	GLuint textureId;

	int  textureW, textureH;



	// Diplay List contains precomputed quadratic rendering	

	void CALLBACK tessVertexCallback(GLdouble *vtx);

	void CALLBACK tessBeginCallback(GLenum typ);

	void CALLBACK tessEndCallback(void);

	void CALLBACK tessErrorCallback(GLenum errorCode);

	//void CALLBACK tessCombineVtx(GLdouble coords[3], GLdouble *vtx_data[4], GLfloat wt[4], GLdouble **out);

	// void CALLBACK tessCombineVtx(GLvoid coords[3], GLvoid *vtx_data[4], GLvoid wt[4], GLvoid **out);

	//void CALLBACK tessCombineVtx(GLdouble coords[3], void *vtx_data[4], GLfloat wt[4], void **out);

	//void (void(CALLBACK*)()) tessCombineVtx();

	void makeTess(double **pts);

	void makeDispList();

	int dispList;

	GLUtesselator *tess;

};

	

#endif //__VISPOLYGON_H_

