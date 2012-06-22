// VisDisk.h: Definition of the CVisDisk class
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VISDISK_H__935A9C33_5027_43C3_9427_14D89FFEFD6E__INCLUDED_)
#define AFX_VISDISK_H__935A9C33_5027_43C3_9427_14D89FFEFD6E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"       // main symbols
#include "VisObject.h"

/////////////////////////////////////////////////////////////////////////////
// CVisDisk

class CVisDisk : 
	public IDispatchImpl<IVisDisk, &IID_IVisDisk, &LIBID_VISSERVERLib>, 
	public ISupportErrorInfo,
	public CComObjectRoot,
	public CComCoClass<CVisDisk,&CLSID_VisDisk>,
	public CVisObject
{
public:
	CVisDisk();
	~CVisDisk();
BEGIN_COM_MAP(CVisDisk)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IVisDisk)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()
//DECLARE_NOT_AGGREGATABLE(CVisDisk) 
// Remove the comment from the line above if you don't want your object to 
// support aggregation. 

DECLARE_REGISTRY_RESOURCEID(IDR_VisDisk)
// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IVisDisk
public:
	STDMETHOD(get_points)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_points)(/*[in]*/ double newVal);

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

	STDMETHOD(get_radius)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_radius)(/*[in]*/ double newVal);
	STDMETHOD(get_color)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_color)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_alpha)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_alpha)(/*[in]*/ double newVal);
	STDMETHOD(get_fill)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_fill)(/*[in]*/ double newVal);
	STDMETHOD(get_clipped)(/*[out, retval]*/ double *pVal);

	void draw();

private:


	float Radius;
	float Color[3];
#if INDEX_MODE
	int   ColorIndex;
#endif
	float Alpha;
	int   Fill;
	int   Points;
	float JAC[2][2],ROT[16];  // Jacobian and OpenGL Rotation
//	int   Clipped;
//	float X,Y;
//	float Z;
//	int	  Show;
//	wchar_t errorString[200];

	// Display List contains precomputed quadratic rendering
	void makeDispList();
	int dispList;
	GLUquadric *quad;

};

#endif // !defined(AFX_VISDISK_H__935A9C33_5027_43C3_9427_14D89FFEFD6E__INCLUDED_)


