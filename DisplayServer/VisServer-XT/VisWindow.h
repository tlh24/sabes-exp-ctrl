// VisWindow.h: Definition of the CVisWindow class
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VISWINDOW_H__F3D6CF29_CD85_48E6_99EC_B3141C72A3E5__INCLUDED_)
#define AFX_VISWINDOW_H__F3D6CF29_CD85_48E6_99EC_B3141C72A3E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CVisWindow

class CVisWindow : 
	public IDispatchImpl<IVisWindow, &IID_IVisWindow, &LIBID_VISSERVERLib>, 
	public ISupportErrorInfo,
	public CComObjectRoot,
	public CComCoClass<CVisWindow,&CLSID_VisWindow>
{
public:
	CVisWindow();
	~CVisWindow();
BEGIN_COM_MAP(CVisWindow)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IVisWindow)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()
//DECLARE_NOT_AGGREGATABLE(CVisWindow) 
// Remove the comment from the line above if you don't want your object to 
// support aggregation. 

DECLARE_REGISTRY_RESOURCEID(IDR_VisWindow)
// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);


// IVisWindow
public:
	STDMETHOD(get_counter)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_counter)(/*[in]*/ double newVal);
	STDMETHOD(get_calibrated)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_calibrated)(/*[in]*/ double newVal);
	STDMETHOD(get_active)(/*[out, retval]*/ double *pVal);
	STDMETHOD(get_priority)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_priority)(/*[in]*/ double newVal);
	STDMETHOD(get_errstring)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_batchmode)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_batchmode)(/*[in]*/ double newVal);
	STDMETHOD(get_blockmode)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_blockmode)(/*[in]*/ double newVal);
	STDMETHOD(drawnow)();
	STDMETHOD(clrscreen)();
	STDMETHOD(clrlog)();
	STDMETHOD(get_actionlog)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(get_logmode)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_logmode)(/*[in]*/ double newVal);
	STDMETHOD(get_countersize)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_countersize)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_counterpos)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_counterpos)(/*[in]*/ VARIANT newVal);

	void update(void);
	void init(void);
	void requestUpdate(int drawnow=0);
	int  nextTag();
	void logAction(int objtag, int action, double *params=NULL, int n=0);
	void logAction(int objtag, int action, int *params=NULL, int n=0);
	int  ColorRGB2I(float *Color);
	void ColorI2RGB(int i, float *Color);

	int FullScreen;
	float width;
	float height;
	RECT  rect;				// rect: left, right, bottom, top
	HWND   hWnd;

	int logmode;

private:
	int NeedsUpdate;
	int calibrated;
	int priority;
	int batchmode;
	int blockmode;

	int dispList[2];
	int bufferId;

	int tagCount;
	int actionCount;
	int logIndex;
	double **actionLog;
	double counterPos[2];
	double counterSize[2];
	int counterX, counterY, counterW, counterH;
	GLubyte *counterImage;
	void DrawCounter();

	wchar_t errorString[200];

};


// Other Globals
extern CVisWindow *VisWindow;

#define VISWIN_XOR_DRAWING     0
#define VISWIN_IS_CLIPPED(x,y) ( ((x)<0 || (x)>VisWindow->width || (y)<0 || (y)>VisWindow->height) ? 1:0 )
#define VISWIN_MIN(x,y)        ((x)<(y)?(x):(y))
#define VISWIN_MAX(x,y)        ((x)>(y)?(x):(y))
#define VISWIN_DEBUG           0 // 0 // 2

#endif // !defined(AFX_VISWINDOW_H__F3D6CF29_CD85_48E6_99EC_B3141C72A3E5__INCLUDED_)
