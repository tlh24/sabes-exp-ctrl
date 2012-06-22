// VisMouse.cpp : Implementation of CVisServerApp and DLL registration.

#include "stdafx.h"
#include "stdio.h"
#include "time.h"
#include "math.h"

#include "VisServer.h"
#include "VisMouse.h"
#include "VisWindow.h"
#include "VisWindowManagement.h"
#include "ComUtils.h"

#define MAX_NEGATIVE -99999
#define BUFFER_LEN 5000

CVisMouse *VisMouse=NULL;

/////////////////////////////////////////////////////////////////////////////
//

STDMETHODIMP CVisMouse::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IVisMouse,
	};

	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}




/////////////////////////////////////////////////////////////////////////////
//  ERROR REPORTING

//// Required for some of the Common Functions
void
CommonError(char *estring){
	MessageBox(NULL, estring, "MouseServer", MB_OK | MB_ICONINFORMATION);
}
////////////////////////////////////////////// OPTO_ERROR
void
CVisMouse::MOUSE_ERROR(char *estring)
{
	MessageBox(NULL, estring, "MouseServer", MB_OK | MB_ICONINFORMATION);
}

/////////////////////////////////////////////////////////////////////////////
// CONSTR/DESTR

CVisMouse::CVisMouse()
{
	int i,j;

	// Pointer to me!
	VisMouse = this;

	// Initialize
	pos=new double[2];
	pos[0]=pos[1]=0;

	events = new double*[3]; 
	for(i=0;i<3;i++) {
		events[i] = new double[3];
		for(j=0;j<3;j++) events[i][j]=0;
	}


	// Default is NOT to force the cursor to remain in the window
	confined = 0;

	errorString[0]='\0';

	started=1;
}

CVisMouse::~CVisMouse()
{
	if(confined) ClipCursor(&oldClipRect);	// restore cursor clip rectangle to old value
	VisMouse=NULL;
}

/////////////////////////////////////////////////////////////////////////////
//  PROPERTIES

//////////////////////////// STARTED
STDMETHODIMP 
CVisMouse::get_started(double *pVal)
{
	*pVal = started;
	return S_OK;
}


//////////////////////////// ERROR
STDMETHODIMP 
CVisMouse::get_error(BSTR *pVal)
{
	*pVal=SysAllocString(errorString);
	return S_OK;
}


//////////////////////////// CONFINED
STDMETHODIMP 
CVisMouse::get_confine(double *pVal)
{
	if(started){
		*pVal=confined;
		return S_OK;
	}
	else{
		swprintf(errorString,L"Mouse not active!");
		return MAKE_HRESULT(1,FACILITY_ITF,CONNECT_E_CANNOTCONNECT);
	}
}

STDMETHODIMP 
CVisMouse::put_confine(double newVal)
{
	int newConfined = fabs(newVal)>.01;   // newVal is double not int
	
	if(started){
		if(!confined && newConfined){				// Confining cursor
			GetClipCursor(&oldClipRect);			// save current setting in order to restor
			ClipCursor(&(VisWindow->rect));		// clip cursor
			confined=1;
		}
		else if(confined && !newConfined){			// Unconfining cursor
			ClipCursor(&oldClipRect);			// restore to old value
			confined=0;
		}
		return S_OK;
	}
	else{
		swprintf(errorString,L"Mouse not active!");
		return MAKE_HRESULT(1,FACILITY_ITF,CONNECT_E_CANNOTCONNECT);
	}
}


//////////////////////////// POS
STDMETHODIMP 
CVisMouse::get_pos(VARIANT *pVal)
{
	if(started){
		VariantFromArray(2,pos,pVal);
		return S_OK;
	}
	else{
		swprintf(errorString,L"Mouse not active!");
		return MAKE_HRESULT(1,FACILITY_ITF,CONNECT_E_CANNOTCONNECT);
	}
}

STDMETHODIMP 
CVisMouse::put_pos(VARIANT newVal)
{
	if(started){
		return S_OK;
	}
	else{
		swprintf(errorString,L"Mouse not active!");
		return MAKE_HRESULT(1,FACILITY_ITF,CONNECT_E_CANNOTCONNECT);
	}
}


////////////////////////////// ALL EVENTS
STDMETHODIMP CVisMouse::get_events(VARIANT *pVal)
{
	if(started){
		int limits[2]={3,3};
		VariantFromArray2(limits,events,pVal);
		return S_OK;
	}
	else{
		swprintf(errorString,L"Can't get events if VisMouse not setup");
		return MAKE_HRESULT(1,FACILITY_ITF,CONNECT_E_CANNOTCONNECT);
	}
}

////////////////////////////////////

STDMETHODIMP CVisMouse::get_down(VARIANT *pVal)
{
	if(started){
		VariantFromArray(3,events[DOWN],pVal);
		return S_OK;
	}
	else{
		swprintf(errorString,L"Can't get down events if VisMouse not setup");
		return MAKE_HRESULT(1,FACILITY_ITF,CONNECT_E_CANNOTCONNECT);
	}
}

STDMETHODIMP CVisMouse::get_click(VARIANT *pVal)
{
	if(started){
		VariantFromArray(3,events[UP],pVal);
		return S_OK;
	}
	else{
		swprintf(errorString,L"Can't get down events if VisMouse not setup");
		return MAKE_HRESULT(1,FACILITY_ITF,CONNECT_E_CANNOTCONNECT);
	}
}

STDMETHODIMP CVisMouse::get_dblclick(VARIANT *pVal)
{
	if(started){
		VariantFromArray(3,events[DBLCLICK],pVal);
		return S_OK;
	}
	else{
		swprintf(errorString,L"Can't get down events if VisMouse not setup");
		return MAKE_HRESULT(1,FACILITY_ITF,CONNECT_E_CANNOTCONNECT);
	}
}

///////////////////////////////////////////////////////
////////  METHODS
STDMETHODIMP CVisMouse::reset()
{
	int i,j;
	if(started){
		for(i=0;i<3;i++) for(j=0;j<3;j++) events[i][j]=0;
	}
	return S_OK;
}


////////////////
STDMETHODIMP CVisMouse::capture()
{
	// Position cursor in the middle of the VisWindow and have capture the focus
	SetCursorPos(
		((VisWindow->rect).right+(VisWindow->rect).left)/2,
		((VisWindow->rect).top+(VisWindow->rect).bottom)/2
		);

	SetCapture(hWnd);
	return S_OK;
}

///////////////////////////////////////////////////
/////////// PUBLIC VISWINDOW INTERFACES

//////////////////////////////
void
CVisMouse::Update(int x, int y)
{
	if(started){ pos[0]=x; pos[1]=y;}
}

//////////////////////////////
void
CVisMouse::Event(int but, int ev)
{
	if(started){
		events[ev][but] = 1; 
		if(ev==UP) events[DOWN][but]=0;
	}
}

