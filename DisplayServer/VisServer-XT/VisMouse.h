// VisMouse.h: Definition of the VisMouse class

//

//////////////////////////////////////////////////////////////////////



#if !defined(AFX_VISMOUSE_H__EA71FE73_9AF2_409B_AB30_B9690512FCB7__INCLUDED_)

#define AFX_VISMOUSE_H__EA71FE73_9AF2_409B_AB30_B9690512FCB7__INCLUDED_



#if _MSC_VER > 1000

#pragma once

#endif // _MSC_VER > 1000



#include "resource.h"       // main symbols

#include "time.h"



/////////////////////////////////////////////////////////////////////////////

// VisMouse



class CVisMouse : 

	public IDispatchImpl<IVisMouse, &IID_IVisMouse, &LIBID_VISSERVERLib>, 

	public ISupportErrorInfo,

	public CComObjectRoot,

	public CComCoClass<CVisMouse,&CLSID_VisMouse>

{

public:

	CVisMouse();

	~CVisMouse();

BEGIN_COM_MAP(CVisMouse)

	COM_INTERFACE_ENTRY(IDispatch)

	COM_INTERFACE_ENTRY(IVisMouse)

	COM_INTERFACE_ENTRY(ISupportErrorInfo)

END_COM_MAP()

	//DECLARE_NOT_AGGREGATABLE(VisMouse) 

	// Remove the comment from the line above if you don't want your object to 

	// support aggregation. 

		

	DECLARE_REGISTRY_RESOURCEID(IDR_VisMouse)

	// ISupportsErrorInfo

	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

	

	// IVisMouse

public:

	STDMETHOD(capture)();

	STDMETHOD(get_started)(/*[out, retval]*/ double *pVal);

	STDMETHOD(get_error)(/*[out, retval]*/ BSTR *pVal);

	STDMETHOD(get_confine)(/*[out, retval]*/ double *pVal);

	STDMETHOD(put_confine)(/*[in]*/ double newVal);

	STDMETHOD(get_pos)(/*[out, retval]*/ VARIANT *pVal);

	STDMETHOD(put_pos)(/*[in]*/ VARIANT newVal);

	STDMETHOD(get_events)(/*[out, retval]*/ VARIANT *pVal);

	STDMETHOD(get_down)(/*[out, retval]*/ VARIANT *pVal);

	STDMETHOD(get_click)(/*[out, retval]*/ VARIANT *pVal);

	STDMETHOD(get_dblclick)(/*[out, retval]*/ VARIANT *pVal);

	STDMETHOD(reset)();

	

	// Flags and Binary Properties

	int started;

	int confined;

	

	// Update and Event -- WinProc calls these

	void Update(int x, int y);

	void Event(int x, int y);

	

	// Error Handling

	void MOUSE_ERROR(char *string);

	wchar_t errorString[200];

	

private:

	RECT oldClipRect;

	// Data Structures

	double *pos;

	double **events;

	

	};



#define LEFT		0

#define MIDDLE		1

#define RIGHT		2



#define DOWN		0

#define UP			1

#define DBLCLICK	2



extern CVisMouse *VisMouse;



#endif // !defined(AFX_VISMOUSE_H__EA71FE73_9AF2_409B_AB30_B9690512FCB7__INCLUDED_)

