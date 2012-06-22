// VisCalibrate.h: Definition of the CVisCalibrate class
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VISCALIBRATE_H__8F9791E5_3208_11D5_AF95_00A0C9A51AF0__INCLUDED_)
#define AFX_VISCALIBRATE_H__8F9791E5_3208_11D5_AF95_00A0C9A51AF0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"       // main symbols
#include "VisDisk.h"

/////////////////////////////////////////////////////////////////////////////
// CVisCalibrate

class CVisCalibrate : 
	public IDispatchImpl<IVisCalibrate, &IID_IVisCalibrate, &LIBID_VISSERVERLib>, 
	public ISupportErrorInfo,
	public CComObjectRoot,
	public CComCoClass<CVisCalibrate,&CLSID_VisCalibrate>
{
public:
	CVisCalibrate();
	~CVisCalibrate();
BEGIN_COM_MAP(CVisCalibrate)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IVisCalibrate)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()
//DECLARE_NOT_AGGREGATABLE(CVisCalibrate) 
// Remove the comment from the line above if you don't want your object to 
// support aggregation. 

DECLARE_REGISTRY_RESOURCEID(IDR_VisCalibrate)
// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IVisCalibrate
public:
	STDMETHOD(get_ready)(/*[out, retval]*/ double *pVal);
	STDMETHOD(get_pos)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_pos)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_count)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_count)(/*[in]*/ double newVal);

	void presentTarget();
	void compute();
	int WriteCalibration();

	float *xpos;
	float *ypos;
	float *zpos;
	float *xscr;
	float *yscr;
	IVisDisk   *pID;	// pointer to interface
	int   logmode_hold; // remeber state of logmode so can turn off during calib
};

#endif // !defined(AFX_VISCALIBRATE_H__8F9791E5_3208_11D5_AF95_00A0C9A51AF0__INCLUDED_)


extern float XPosToScreen(float xp, float yp);
extern float YPosToScreen(float xp, float yp);
extern void  DPosToDScreen(float J[][2], float xp, float yp);
extern int IsCalibrated();
extern int ReadCalibration();
extern void ClearCalibration();

///////// Calibration Parameters:

#define XPTS  5
#define YPTS  4
#define MINX  .25
#define MAXX  .75
#define MINY  .15
#define MAXY  .7
#define REPS  1

///////// FILE

#define CALIBRATION_FILENAME "c:\\Lab\\Code\\VisServer\\calibration-data.txt"
