// VisWindow.cpp : Implementation of CVisServerApp and DLL registration.

#include "stdafx.h"

#include "VisServer.h"
#include "VisWindow.h"
#include "VisWindowManagement.h"
#include "VisWindowActionLog.h"
#include "VisDisk.h"
#include "VisCalibrate.h"
#include "VisMouse.h"
#include "ComUtils.h"

#define WM_UPDATE WM_USER+1 

CVisWindow *VisWindow;		// Pointer to the VisWindow object
int	KeyFlag[256];			// Array Used For The Keyboard Routine


/////////////////////////////////////////////////////////////////////////////
//

STDMETHODIMP CVisWindow::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IVisWindow,
	};

	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid)) return S_OK;
	}
	return S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//  CONSTR/DESTR

CVisWindow::CVisWindow()
{
	if(VisWindow) return;  // Only one should be open!

	// Initialize Variables
	VisWindow = this;
	bufferId=0;
	dispList[0]=dispList[1]=0; // Not a valid list id
	*errorString='\0';

	blockmode=0;
	batchmode=0;
	logmode=0;

	// Create the Window
	FullScreen=1;
	if (!CreateGLWindow()) PostQuitMessage(0);
	
	// Check on Calibration
	ReadCalibration();
	calibrated = IsCalibrated();

	
	// Priority
	put_priority(0); // Normal Priority Class

	// Action Logging
	tagCount=0;
	actionCount=0;
	logIndex=0;
	actionLog = new double*[VISWIN_MAX_LOG_ACTIONS];
	for(int i=0; i<VISWIN_MAX_LOG_ACTIONS; i++) actionLog[i]=NULL;

	// Counter Window
	counterPos[0]=counterPos[1]=0;
	counterX = (int)(counterPos[0]*width);
	counterY = (int)(counterPos[1]*height);
	counterSize[0]=.05; counterSize[1]=.02;
	counterW = (int)(counterSize[0]*width);
	counterH = (int)(counterSize[1]*height);
	
}

//
CVisWindow::~CVisWindow()
{
	// Destroy the Window
	if(WindowFlag) KillGLWindow();

	// Initialize Variables
	VisWindow = NULL;
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////// GENERAL PROPERTIES

STDMETHODIMP CVisWindow::get_active(double *pVal)
{
	// TODO: Add your implementation code here
	*pVal = WindowFlag;
	return S_OK;
}


/////////////
STDMETHODIMP CVisWindow::get_calibrated(double *pVal)
{
	*pVal=calibrated;
	return S_OK;
}

STDMETHODIMP CVisWindow::put_calibrated(double newVal)
{
	if(newVal){
		ReadCalibration();
		calibrated = IsCalibrated();
	}
	else{
		ClearCalibration();
		calibrated = IsCalibrated();
	}
	return S_OK;
}


///////////////////
STDMETHODIMP CVisWindow::get_priority(double *pVal)
{
	*pVal=priority;
	return S_OK;
}

STDMETHODIMP CVisWindow::put_priority(double newVal)
{
	// Upgrade Process Priority Class???
	priority=(int)newVal;
	switch(priority)
	{
	case 0:	
		SetPriorityClass(GetCurrentProcess(),NORMAL_PRIORITY_CLASS);
		break;
	case 1:	
		SetPriorityClass(GetCurrentProcess(),HIGH_PRIORITY_CLASS);
		break;
	case 2:	
		SetPriorityClass(GetCurrentProcess(),REALTIME_PRIORITY_CLASS);
		break;
	}
	return S_OK;
}


STDMETHODIMP CVisWindow::get_batchmode(double *pVal)
{
	*pVal=batchmode;
	return S_OK;
}

STDMETHODIMP CVisWindow::put_batchmode(double newVal)
{
	batchmode=(int)newVal;
	return S_OK;
}


STDMETHODIMP CVisWindow::get_blockmode(double *pVal)
{
	*pVal=blockmode;
	return S_OK;
}

STDMETHODIMP CVisWindow::put_blockmode(double newVal)
{
	blockmode=(int)newVal;
	return S_OK;
}

/////////////////////////
STDMETHODIMP CVisWindow::get_errstring(BSTR *pVal)
{
	*pVal=SysAllocString(errorString);
	return S_OK;
}



/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////// GENERAL METHODS

////////////////////////////////////////////////////////////////////
// Restart
//

STDMETHODIMP CVisWindow::drawnow()
{
	if( batchmode && NeedsUpdate ) VisWindow->requestUpdate(1);
	return S_OK;
}

STDMETHODIMP CVisWindow::clrscreen()
{
	// Un-show Object, running through the linked list
	if(ObjList!=NULL){
		int done=0;
		VisObjectListStruct *objptr=ObjList;
		CVisObject *obj;

		while(!done){
			obj=(CVisObject*)(objptr->ptr);
			obj->put_show(0);
			if(objptr->next!=NULL) objptr=objptr->next;
			else done=1;
		}
		VisWindow->requestUpdate();
	}
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////// Action Log Properties, Methods, Functions

////////////////////////////////////////////////////////////////////
// 
////////// COUNTER

// Logmode
STDMETHODIMP CVisWindow::get_logmode(double *pVal)
{
	*pVal=logmode;
	return S_OK;
}
STDMETHODIMP CVisWindow::put_logmode(double newVal)
{
	int newmode = (int) newVal;
	if(logmode!=newmode){
		logmode=newmode;
		if(logmode) VisWindow->logAction(0,ACTION_CREATE,(double *)NULL,0);
		VisWindow->requestUpdate();
	}
	return S_OK;
}

// Counter Value
STDMETHODIMP CVisWindow::get_counter(double *pVal)
{
	*pVal=actionCount;
	return S_OK;
}
STDMETHODIMP CVisWindow::put_counter(double newVal)
{
	if(logmode){
		actionCount=(int)newVal-1; // Since this command forces a draw -
		requestUpdate();
		logAction(0,ACTION_CREATE,&newVal,1);
	}
	else actionCount=(int)newVal;  // Silly to set it here, but....

	return S_OK;
}

// Counter Pos -- [0 1] wrt screen edge
STDMETHODIMP CVisWindow::get_counterpos(VARIANT *pVal)
{
	VariantFromArray(2,counterPos,pVal);
	return S_OK;
}
STDMETHODIMP CVisWindow::put_counterpos(VARIANT newVal)
{
	int alen,cx,cy;
	double *aptr;
	if( VariantToArray(&alen,&aptr,&newVal) ) return E_INVALIDARG;
	if( alen<2 ) { delete aptr; return E_INVALIDARG; }
	counterPos[0]=(float)aptr[0];
	counterPos[1]=(float)aptr[1];


	cx = (int)(counterPos[0]*width);
	cy = (int)(counterPos[1]*height);
	if( cx!=counterX || cy!=counterY ){
		counterX = cx;
		counterY = cy;
		if(logmode){
			requestUpdate();
			logAction(0,ACTION_POS,aptr,2);
		}
	}
	delete aptr;
	return S_OK;
}

// Counter Size -- [0 1] wrt screen edge
STDMETHODIMP CVisWindow::get_countersize(VARIANT *pVal)
{
	VariantFromArray(2,counterSize,pVal);
	return S_OK;
}

STDMETHODIMP CVisWindow::put_countersize(VARIANT newVal)
{
	int alen,cw,ch;
	double *aptr;
	if( VariantToArray(&alen,&aptr,&newVal) ) return E_INVALIDARG;
	if( alen<2 ) { delete aptr; return E_INVALIDARG; }
	counterSize[0]=(float)aptr[0];
	counterSize[1]=(float)aptr[1];


	cw = (int)(counterSize[0]*width);
	ch = (int)(counterSize[1]*height);
	if( cw!=counterW || ch!=counterH ){
		counterW = cw;
		counterH = ch;
		if(logmode){
			requestUpdate();
			logAction(0,ACTION_SCALE,aptr,2);
		}
	}
	delete aptr;
	return S_OK;
}


// Draw Counter
void CVisWindow::DrawCounter()
{
	static int cx=0;
	static int cy=0;
	static int cw=0;
	static int ch=0;
	static int ppb;  // pixels per bit
	int i,j,k,b, pixon;
	
	actionCount++;

	// Create Data Structure if Counter Moved
	if(cx!=counterX||cy!=counterY||ch!=counterH||cw!=counterW){
		cx=counterX; cy=counterY; ch=counterH; cw=counterW;
		
		// width must match counter bits
		ppb=(cw-(VISWIN_COUNTER_BITS-1))/VISWIN_COUNTER_BITS;
		if(ppb<1) ppb=1;
		cw = ppb*VISWIN_COUNTER_BITS + (VISWIN_COUNTER_BITS-1);
		if(cw%4) cw = cw + 4-(cw%4);  // cw needs to be a multiple of 4 bytes
			
		
#if INDEX_MODE
		counterImage = new GLubyte[ch*cw];
#else
		counterImage = new GLubyte[ch*cw*3];
#endif
	}

	// Load Pixels
	for(k=i=0;i<ch;i++){
		for(j=0;j<cw;j++){
			b = j/(ppb+1);
			pixon = (b<VISWIN_COUNTER_BITS) & // In case there is overrun due to 4-byte bdry
				((j+1)%(ppb+1)>0)               & // Check if on or between counter spots
				((actionCount&(1<<b))>0);   // Is this bit on?

#if INDEX_MODE
			counterImage[k++] = (GLubyte)255*pixon;
#else
			counterImage[k++] = (GLubyte)255*pixon;
			counterImage[k++] = (GLubyte)255*pixon;
			counterImage[k++] = (GLubyte)255*pixon;
#endif
		}
	}


	// Draw
	glMatrixMode (GL_MODELVIEW);	
	glLoadIdentity();
	glRasterPos2i(cx,cy);
#if INDEX_MODE
	glDrawPixels(cw, ch, GL_COLOR_INDEX, GL_UNSIGNED_BYTE, counterImage);
#else
	glDrawPixels(cw, ch, GL_RGB, GL_UNSIGNED_BYTE, counterImage);
#endif
	glFlush();

}

////////////////////////////////////////////////////////////
// 
// ACTION LOG


STDMETHODIMP CVisWindow::get_actionlog(VARIANT *pVal)
{
	// Save to VARIANT
	int limit[2] = {logIndex,3+VISWIN_MAX_LOG_PARAMS};
	VariantFromArray2(limit,actionLog,pVal);
	return S_OK;
}

STDMETHODIMP CVisWindow::clrlog()
{
	for(int i=0;i<(logIndex-1);i++) { delete actionLog[i]; actionLog[i]=NULL; }
	logIndex=0;
	return S_OK;
}


void  CVisWindow::logAction(int objtag, int action, double *params, int n)
{
	int i;
	if(logIndex < VISWIN_MAX_LOG_ACTIONS-1){
		n = (n>VISWIN_MAX_LOG_PARAMS) ? VISWIN_MAX_LOG_PARAMS:n;

		actionLog[logIndex] = new double[VISWIN_MAX_LOG_PARAMS+3];
		actionLog[logIndex][0] = actionCount+1;
		actionLog[logIndex][1] = objtag;
		actionLog[logIndex][2] = action;
		for(i=0; i<n; i++)                      actionLog[logIndex][i+3] = params[i];
		for(i=n; i<VISWIN_MAX_LOG_PARAMS; i++)  actionLog[logIndex][i+3] = 0;

		logIndex++;
	}
	else{
		if(actionLog[logIndex]!=NULL){
			actionLog[logIndex] = new double[VISWIN_MAX_LOG_PARAMS+2];
			actionLog[logIndex][0]=actionCount+1;
			actionLog[logIndex][1]=0;
			actionLog[logIndex][2]=ACTION_LOGERR;
		}
	}
}

void  CVisWindow::logAction(int objtag, int action, int *params, int n)
{
	double *tmp=new double[n];
	for(int i=0;i<n;i++) tmp[i]=params[i];
	logAction(objtag,action,tmp,n);
}

int  CVisWindow::nextTag(void)
{
	return ++tagCount;
}


////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
// Color
//

#define IBASE 6
extern HDC			hDC;		// Private GDI Device Context
extern HPALETTE    hPal;      // Color Palette (needed for 8bit color)

int CVisWindow::ColorRGB2I(float *Color)
{
	DWORD r = RGB((BYTE)(Color[0]*255),(BYTE)(Color[1]*255),(BYTE)(Color[2]*255)); 
	int   i = GetNearestPaletteIndex( hPal,r );
	return i;

//	return GetNearestPaletteIndex( hPal,
//		RGB((BYTE)(Color[0]*255),(BYTE)(Color[1]*255),(BYTE)(Color[2]*255))	); 
/*
	int j,c,i,base;

	base=1;
	for(i=j=0; j<3; j++){
		if(Color[j]<0)      Color[j]=0;
		else if(Color[j]>1) Color[j]=1;
		c    = (int)( Color[j]*(IBASE-1) + .5 );
		i    += c*base;
		base *= IBASE;
	}
	return i;
*/
}

void CVisWindow::ColorI2RGB(int i, float *Color)
{
	int j,r,inew;

	// Top off with Whites
	if(i >= IBASE*IBASE*IBASE){
		Color[0]=Color[1]=Color[2]=1.0;
		return;
	}

	// Count with base IBASE
	inew=i;
	for(j=0; j<3; j++){
		r    = inew%IBASE;
		inew = (inew-r)/IBASE;
		Color[j]=(float)r/(float)(IBASE-1);
	}
}

#undef IBASE

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
// Update
//
void CVisWindow::update(void)								// Here's Where We Do All The Drawing
{
//	if(WindowFlag && NeedsUpdate)  // Only draw when VisServer requests
	if(WindowFlag)                 // Draw when VisServer or OS requests
	{
		NeedsUpdate=0;

		/////////////////////////////////////////////////////////
		// Need to erase the old frame:
		// either XOR out the stuff or just clear the buffer

#if VISWIN_XOR_DRAWING
		// Enable XOR
		glEnable(GL_COLOR_LOGIC_OP);
		glLogicOp(GL_XOR);

		// Erase Last Image -- all drawing is assumed to be xor
		if( dispList[bufferId] ) glCallList(dispList[bufferId]);	// Have a previous list
		else{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// else Initialize
			dispList[bufferId] = glGenLists(1);
		}

		// Now make a new Display List to save the new image
		glNewList(dispList[bufferId],GL_COMPILE);					// Start List

#else 
		// Clearing and redraw de novo each time
		// This may be too slow, in which case we'll need to 
		// use XOR drawing
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
#endif

		//////////////////////////////////////////////////////////
		// Draw Each Object, running through the linked list
		if(ObjList!=NULL){
			int done=0;
			VisObjectListStruct *objptr=ObjList;
			CVisObject *obj;

			while(!done){
				obj=(CVisObject*)(objptr->ptr);
				obj->draw();
				if(objptr->next!=NULL) objptr=objptr->next;
				else done=1;
			}
		}

		// Action Counter
		if(logmode) DrawCounter();

#if VISWIN_XOR_DRAWING
		// End List
		glEndList();
		// ... and then call it
		glCallList(dispList[bufferId]);
#endif

		// Double Buffering
		SwapBuffers(hDC);									// Swap Buffers (Double Buffering)
		bufferId = bufferId?0:1;							// Swap bufferId
	}
}



////////////////////////////
// RequestUpdate
//
void CVisWindow::requestUpdate(int batch)
{
	NeedsUpdate=1;
	if( !batchmode || (batch && batchmode) ){
		if(blockmode){
			VisWindow->update();
		} else {	
			PostMessage(VisWindow->hWnd,WM_UPDATE,0,0);
		}
	}
}


////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
// WndProc
//
// Message Handler for all but WM_QUIT


////////////////////
LRESULT
VisHandleMsg(HWND	hWnd,			// Handle For This Window
			 UINT	uMsg,			// Message For This Window
			 WPARAM	wParam,			// Additional Message Information
			 LPARAM	lParam)			// Additional Message Information
{
	switch (uMsg)									// Check For Windows Messages
	{
		case WM_SYSCOMMAND:							// Intercept System Commands
		{
			switch (wParam)							// Check System Calls
			{
				case SC_SCREENSAVE:					// Screensaver Trying To Start?
				case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
				return 0;							// Prevent From Happening
			}
			break;									// Exit
		}

		case WM_CLOSE:								// Received A Quit-like Message
		case WM_DESTROY:							
		{
			PostQuitMessage(0);						// Send A Quit Message
			return 0;								// Jump Back
		}

		case WM_UPDATE:								// OpenGL Window Needs Painting
		{
			if(VisWindow) {
				VisWindow->update();
			}
			return 0;
			break;
		}

		case WM_SIZE:								// Resize The OpenGL Window
		{
		//	ReSizeGLWindow(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
		//	if(VisWindow) VisWindow->init();
			if(VisWindow) VisWindow->requestUpdate();
			return 0;								// Jump Back
		}

		case WM_CHAR:								// Has A Key Been Pressed?
		{
			switch (wParam)							// Handle Some Keys, Ignore Rest
			{
			case VK_ESCAPE:
				PostQuitMessage(0);
				break;
			}
			return 0;
		}
		
		// Remove some potentially pernicious messages?!?
		case WM_WINDOWPOSCHANGING: 
		case WM_WINDOWPOSCHANGED:
		case WM_NCACTIVATE:           
			return 0;
			
			
		default:
			break;
	}

	///// MOUSE ONLY
	if(VisMouse)
	{
		POINTS mpt;

		switch(uMsg)
		{
			
		case WM_LBUTTONDOWN:
		case WM_NCLBUTTONDOWN:
			VisMouse->Event(LEFT,DOWN);
			return 0;
		case WM_MBUTTONDOWN:
		case WM_NCMBUTTONDOWN:
			VisMouse->Event(MIDDLE,DOWN);
			return 0;
		case WM_RBUTTONDOWN:
		case WM_NCRBUTTONDOWN:
			VisMouse->Event(RIGHT,DOWN);
			return 0;

		case WM_LBUTTONUP:
		case WM_NCLBUTTONUP:
			VisMouse->Event(LEFT,UP);
			return 0;
		case WM_MBUTTONUP:
		case WM_NCMBUTTONUP:
			VisMouse->Event(MIDDLE,UP);
			return 0;
		case WM_RBUTTONUP:
		case WM_NCRBUTTONUP:
			VisMouse->Event(RIGHT,UP);
			return 0;
			
		case WM_LBUTTONDBLCLK:
		case WM_NCLBUTTONDBLCLK:
			VisMouse->Event(LEFT,DBLCLICK);
			return 0;
		case WM_MBUTTONDBLCLK:
		case WM_NCMBUTTONDBLCLK:
			VisMouse->Event(MIDDLE,DBLCLICK);
			return 0;
		case WM_RBUTTONDBLCLK:
		case WM_NCRBUTTONDBLCLK:
			VisMouse->Event(RIGHT,DBLCLICK);
			return 0;

		case WM_MOUSEMOVE:
			mpt = MAKEPOINTS(lParam); 
			VisMouse->Update((VisWindow->rect).left+mpt.x,(VisWindow->rect).top+mpt.y);		
			return 0;
		case WM_NCMOUSEMOVE:	// I think this doesn't work
			mpt = MAKEPOINTS(lParam); 
			VisMouse->Update(mpt.x,mpt.y);		
			return 0;

		default:
			break;
			
		}
	}


	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}


// WndProc
//
// Message Handler for all but WM_QUIT
//
LRESULT CALLBACK WndProc(	HWND	hWnd,			// Handle For This Window
							UINT	uMsg,			// Message For This Window
							WPARAM	wParam,			// Additional Message Information
							LPARAM	lParam)			// Additional Message Information
{
	LRESULT res;
//	LPMSG   msg;
//	int m;

//	static FILE *fp = NULL;

//	if(fp==NULL) fp=fopen("c:\\msglist.txt","w");

	res=VisHandleMsg(hWnd,uMsg,wParam,lParam);
	
//	fprintf(fp,"%x\n",uMsg); fflush(fp);

	/*
	msg = new MSG[1];
	
	int i;
	m=PeekMessage(msg,0,0,0,PM_NOREMOVE);
	for(i=0;i<5 && m;i++){
		m=PeekMessage(msg,0,0,0,PM_NOREMOVE);
//		VisHandleMsg(msg->hwnd,msg->message,msg->wParam,msg->lParam);
	}
*/
	return res;
}

