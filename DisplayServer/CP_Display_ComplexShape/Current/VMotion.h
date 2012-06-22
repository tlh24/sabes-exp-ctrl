// VMotion.h : Declaration of the CVMotion

#ifndef __VMOTION_H_
#define __VMOTION_H_

#include "resource.h"       // main symbols
#include "VObject.h"
#include <sys\timeb.h>


/////////////////////////////////////////////////////////////////////////////
// CVMotion
class CVMotion : 
	public IDispatchImpl<IVMotion, &IID_IVMotion, &LIBID_CP_DISPLAYLib>,
    public CComObjectRoot,
	public CComCoClass<CVMotion, &CLSID_VMotion>,
//	public ISupportErrorInfo,
    public CVObject 
{

BEGIN_COM_MAP(CVMotion)
	COM_INTERFACE_ENTRY(IVMotion)
	COM_INTERFACE_ENTRY(IDispatch)
//	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

DECLARE_REGISTRY_RESOURCEID(IDR_VMOTION)
DECLARE_PROTECT_FINAL_CONSTRUCT()

// ISupportsErrorInfo
//	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IVMotion
public:
	CVMotion();
	~CVMotion();

// common methods
#include "VObjectMethodsDecl.h"

// IVMotion
	STDMETHOD(GetExact)(/*[out, retval]*/ double *pVal);
	STDMETHOD(SetExact)(/*[in]*/ double newVal, long iLogID);

	STDMETHOD(IsCircle)(/*[out, retval]*/ double *pVal);
	STDMETHOD(UseCircle)(long iLogID);
	STDMETHOD(IsSquare)(/*[out, retval]*/ double *pVal);
	STDMETHOD(UseSquare)(long iLogID);
	
	STDMETHOD(GetNPoints)(/*[out, retval]*/ double *pVal);
	STDMETHOD(SetNPoints)(/*[in]*/ double newVal, long iLogID);

	STDMETHOD(GetLifetime)(/*[out, retval]*/ double *pVal);
	STDMETHOD(SetLifetime)(/*[in]*/ double newVal, long iLogID);
	STDMETHOD(GetCoherence)(/*[out, retval]*/ double *pVal);
	STDMETHOD(SetCoherence)(/*[in]*/ double newVal, long iLogID);
	STDMETHOD(GetVelocity)(/*[out, retval]*/ VARIANT *pvXY);
	STDMETHOD(SetVelocity)(/*[in]*/ VARIANT vXY, long iLogID);

	STDMETHOD(GetPointSize)(/*[out, retval]*/ double *pVal);
	STDMETHOD(SetPointSize)(/*[in]*/ double newVal, long iLogID);

	STDMETHOD(GetVertices)(/*[out, retval]*/ VARIANT *pVal);  // Mostly for diagnotice purposes

	STDMETHOD(StartUDPSync)(long iLogID);
	STDMETHOD(StopUDPSync)(long iLogID);


	void Draw();

protected:
	int			nVertices;
    double		*vertices;
	double      *scrVertices;
    double		*vertexTimes;
    double		*vertexVelOffset;
	void		m_sampleVertex(int i, double *pos, double *vel);
	void		m_sampleVertices();
	void		m_updateVertices();
	void		m_xformVertices();

	bool		resampleFlag;
	bool        circle;
	double		lifetime;
	double		coherence;
	double		velX,velY;
	double      pointSize;
	int         exact;
	bool        UDPsyncFlag;

	double JAC[2][2],ROT[16];    // Jacobian and OpenGL Rotation

   struct _timeb lastTime;
};

#endif //__VMOTION_H_
