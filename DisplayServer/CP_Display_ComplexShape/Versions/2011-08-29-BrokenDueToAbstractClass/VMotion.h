// VMotion.h : Declaration of the CVMotion

#ifndef __VMOTION_H_
#define __VMOTION_H_

#include "resource.h"       // main symbols
#include "VObject.h"
#include "VComplexShape.h"

/////////////////////////////////////////////////////////////////////////////
// CVMotion
class ATL_NO_VTABLE CVMotion : 
    public CComObjectRoot,
	public CComCoClass<CVMotion, &CLSID_VMotion>,
	public IDispatchImpl<IVMotion, &IID_IVMotion, &LIBID_CP_DISPLAYLib>,
	public ISupportErrorInfo,
    public CVObject 
{

DECLARE_REGISTRY_RESOURCEID(IDR_VMOTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CVMotion)
	COM_INTERFACE_ENTRY(IVMotion)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IVMotion
public:
	CVMotion();
	~CVMotion();

// common methods
#include "VObjectMethodsDecl.h"

// IVComplexShape
	STDMETHOD(GetExact)(/*[out, retval]*/ double *pVal);
	STDMETHOD(SetExact)(/*[in]*/ double newVal, long iLogID);

	STDMETHOD(IsCircle)(/*[out, retval]*/ double *pVal);
	STDMETHOD(UseCircle)(/*[in]*/ double newVal, long iLogID);
	STDMETHOD(IsSquare)(/*[out, retval]*/ double *pVal);
	STDMETHOD(UseSquare)(/*[in]*/ double newVal, long iLogID);
	
	STDMETHOD(GetNPoints)(/*[out, retval]*/ double *pVal);
	STDMETHOD(SetNPoiints)(/*[in]*/ double newVal, long iLogID);

	STDMETHOD(GetLifetime)(/*[out, retval]*/ double *pVal);
	STDMETHOD(SetLifetime)(/*[in]*/ double newVal, long iLogID);
	STDMETHOD(GetCoherence)(/*[out, retval]*/ double *pVal);
	STDMETHOD(SetCoherence)(/*[in]*/ double newVal, long iLogID);
	STDMETHOD(GetVelocity)(/*[out, retval]*/ VARIANT *pvXY);
	STDMETHOD(SetVelocity)(/*[in]*/ VARIANT vXY, long iLogID);

	void Draw();

protected:
	CVComplexShape  c_complexShape;
	
	int			nVertices;
    double		*vertices=NULL;
    double		*vertexVel=NULL;
    double		*vertexTimes=NULL;
	void		m_sampleVertex(int i, double *pos, double *vel);
	void		m_sampleVertices();
	void		m_updateVertices();

	bool		resampleFlag;
	bool        circle;
	double		lifetime;
	double		coherence;
	double		velX,velY;

   struct _timeb lastTime;
};

#endif //__VMOTION_H_
