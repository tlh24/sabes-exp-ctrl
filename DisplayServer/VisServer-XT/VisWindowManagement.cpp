// VisWindowManagement.cpp



// Window Management Code, incluing...

//    Win OS window creation and maintenace

//    OpenGL initialization

//

// Most of this code was taken from NeHe's OpenGL tutorial (on the web)



#include "stdafx.h"

#include "stdio.h"



#include "VisServer.h"

#include "VisWindow.h"

#include "VisWindowManagement.h"



HDC			hDC=NULL;		// Private GDI Device Context

HGLRC		hRC=NULL;		// Permanent Rendering Context

HWND		hWnd=NULL;		// Holds Our Window Handle

HINSTANCE	hInstance;		// Holds The Instance Of The Application

HMONITOR    hMon=NULL;		// Hold Handle to the Monitor

MONITORINFOEX mInf;			// Information about monitor

HPALETTE    hPal=NULL;      // Color Palette (needed for 8bit color)



#define DC_FUNC 1



int WindowFlag = 0;

extern LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc



////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////

// InitGLWindow

//

void InitGLWindow(void)								// Here's Where We Do All The Drawing

{

	// Depth Buffer

	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing

	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do



	// Clearing

#if INDEX_MODE

	glClearIndex(0.0f);									// Black Background

#else

	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background

#endif

	glClearDepth(1.0f);									// Depth Buffer Setup



	// Color and Lighting

	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading

//		glShadeModel(GL_FLAT);							// Enable Smooth Shading



	// Define projection/perspective

	//     2D) a flat perspective (gluOrtho2D)

	//     3D) a general glFrustrum

	// Use the correct Aspect Ratio Of the Window

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix

	glLoadIdentity();									// Reset The Projection Matrix

	gluOrtho2D(0,VisWindow->width,0,VisWindow->height);

	

	// Clear and Swap Buffers

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer

	SwapBuffers(hDC);									// Swap Buffers (Double Buffering)

}





////////////////////////////////////////////////////////////////////

// GetGLWindowRect

//

// PNS 1/02:

// Getting the right values for the second monitor are a bit of a pain

//

// We'll assume here that we want Monitor 1 OR that:

//   A) the first monitor contains the point (0,0)

//   B) the second monitor is positioned according to the WINDOW_MONITOR_POS 

//       variable -- left, right, up, or down -- w.r.t. the primary Monitor 1

//

// Note that most of these routines require setting WINVER to 

// the "beta" value of 0x0500, which is done in StdAfx.h.

//

int GetGLWindowRect(RECT *rect)	

{

	POINT pt;



	// alloc

	mInf.cbSize=sizeof(MONITORINFOEX);



	// Find a point which lies on the monitor of interest

	int nM=GetSystemMetrics(SM_CMONITORS);	// How many montors?

	if(WINDOW_MONITOR_ID==1 || nM==1) { pt.x=pt.y=0; }  // Forget about it... there's only one monitor!?

	else if(nM==2){

		// First find out size of Monitor 1:

		// use assumption A above:

		pt.x=pt.y=0;

		hMon = MonitorFromPoint(pt,MONITOR_DEFAULTTONEAREST);

		// get information about Monitor 1:

		GetMonitorInfo(hMon,&mInf);

		// Now use assumption B to find a point on the second monitor:

		switch ( WINDOW_MONITOR_POS )

		{

		case 'L':

				pt.x = mInf.rcMonitor.left-10;								// 10pixels to the left of 1st

				pt.y = (mInf.rcMonitor.top + mInf.rcMonitor.bottom)/2;      // midway up

				break;

		case 'R':

				pt.x = mInf.rcMonitor.right+10;								// 10pixels to the right of 1st

				pt.y = (mInf.rcMonitor.top + mInf.rcMonitor.bottom)/2;      // midway up

				break;

		case 'U':

				pt.x = (mInf.rcMonitor.left + mInf.rcMonitor.right)/2;      // midway across

				pt.y = mInf.rcMonitor.top+10;								// 10pixels above 1st

				break;

		case 'D':

				pt.x = (mInf.rcMonitor.left + mInf.rcMonitor.right)/2;      // midway across

				pt.y = mInf.rcMonitor.bottom-10;								// 10pixels above 1st

				break;

		}

	}else{

		MessageBox(NULL,"Unknown Monitor ID.","ERROR",MB_OK|MB_ICONEXCLAMATION);

		return FALSE;								// Return FALSE

	}



	// Get the Monitor Handle that the point is on (or closest to)

	hMon = MonitorFromPoint(pt,MONITOR_DEFAULTTONEAREST);

	// Get information about that Monitor

	GetMonitorInfo(hMon,&mInf);

	

	if(WINDOW_FULLSCREEN){

		rect->left = mInf.rcMonitor.left;

		rect->right = mInf.rcMonitor.right;

		rect->top = mInf.rcMonitor.top;

		rect->bottom = mInf.rcMonitor.bottom;

	} else{

		rect->left = mInf.rcMonitor.left;

		rect->right = VISWIN_MIN(WINDOW_WIDTH,mInf.rcMonitor.right);

		rect->top = mInf.rcMonitor.top;

		rect->bottom = VISWIN_MIN(WINDOW_HEIGHT,mInf.rcMonitor.bottom);

	}



	return TRUE;

}





////////////////////////////// COLORS	

////////// INDEX

void

CreateIndexPalette()

{

	int i,j;

	int n = 1<<WINDOW_BITS;

	float color[3];

	COLORREF cref;

	char str[1000];



	for(i=0;i<n;i++){

		VisWindow->ColorI2RGB(i,color);

		/*

		auxSetOneColor(i, color[0], color[1], color[2]);

		*/

		cref=0;

		for(j=2;j>=0;j--) cref = (cref<<8) + (unsigned long)color[j]*255;

		if( !wglSetLayerPaletteEntries(hDC,1,i,1,&cref) && i<16 ){

			sprintf(str,"Can't Set Palette Entry %d, %lx: Error (%d)",i,cref,GetLastError());

			MessageBox(NULL,str,"ERROR",MB_OK|MB_ICONEXCLAMATION);

		}

	}

}





/////////// RGB for 8bit

void

CreateRGBPalette()

{

	// Adapted from MSDN article:

	// OpenGL II: Windows Palettes in RGBA Mode

	// http://msdn.microsoft.com/library/default.asp?url=/library/en-us/dnopen/html/msdn_gl2.asp



	char str[200];



	// Check to see if we need a palette.

	//

	PIXELFORMATDESCRIPTOR pfd;

	int n = GetPixelFormat(hDC);

	DescribePixelFormat(hDC, n, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

	if (!( (pfd.dwFlags & PFD_NEED_PALETTE) || (pfd.iPixelType & PFD_TYPE_COLORINDEX) )) return; 

	

	// Allocate a log pal and fill it with the color table info.

	LOGPALETTE* pPal    = (LOGPALETTE*) malloc(sizeof(LOGPALETTE) + 256*sizeof(PALETTEENTRY));

	pPal->palVersion    = 0x300; // Windows 3.0??

	pPal->palNumEntries = 256; // table size



	//

	// Create palette.

	//

	n = 1 << pfd.cColorBits;

	BYTE byRedMask   = (1 << pfd.cRedBits) - 1 ;

	BYTE byGreenMask = (1 << pfd.cGreenBits) - 1 ;

	BYTE byBlueMask  = (1 << pfd.cBlueBits) - 1 ;



	for (int i=0; i<n; i++)

	{

		pPal->palPalEntry[i].peRed =

			(unsigned char)((((i >> pfd.cRedShift) & byRedMask) 	

			* 255) / (double)byRedMask + 0.5) ;

		pPal->palPalEntry[i].peGreen =

			(unsigned char)((((i >> pfd.cGreenShift) & byGreenMask) 	

			* 255) / (double)byGreenMask + 0.5) ;

		pPal->palPalEntry[i].peBlue =

			(unsigned char)((((i >> pfd.cBlueShift) & byBlueMask) 	

			* 255) / (double)byBlueMask + 0.5) ;

	}



/*	

	int m_defaultOverride[13] = {

		0, 3, 24, 27, 64, 67, 88, 173, 181, 236, 247, 164, 91

	};

	PALETTEENTRY m_defaultPalEntry[20] = {

		{ 0,   0,   0,    0 }, //0

		{ 0x80,0,   0,    0 }, 

		{ 0,   0x80,0,    0 }, 

		{ 0x80,0x80,0,    0 }, 

		{ 0,   0,   0x80, 0 },

		{ 0x80,0,   0x80, 0 },

		{ 0,   0x80,0x80, 0 },

		{ 0xC0,0xC0,0xC0, 0 }, //7

		

		{ 192, 220, 192,  0 }, //8

		{ 166, 202, 240,  0 },

		{ 255, 251, 240,  0 },

		{ 160, 160, 164,  0 }, //11

		

		{ 0x80,0x80,0x80, 0 }, //12

		{ 0xFF,0,   0,    0 },

		{ 0,   0xFF,0,    0 },

		{ 0xFF,0xFF,0,    0 },

		{ 0,   0,   0xFF, 0 },

		{ 0xFF,0,   0xFF, 0 },

		{ 0,   0xFF,0xFF, 0 },

		{ 0xFF,0xFF,0xFF, 0 }  //19

	};

	if ((pfd.cColorBits == 8)                           &&

		(pfd.cRedBits   == 3) && (pfd.cRedShift   == 0) &&

		(pfd.cGreenBits == 3) && (pfd.cGreenShift == 3) &&

		(pfd.cBlueBits  == 2) && (pfd.cBlueShift  == 6))

	{

		for (int j = 1 ; j <= 12 ; j++)

			pPal->palPalEntry[m_defaultOverride[j]] = 

			m_defaultPalEntry[j];

	}

*/ // Seem to have no effect

	

#if VISWIN_DEBUG

	// Check System 

	// This shows whether the system will allow device to 

	// realize a palette, or whether palette is fixed

	SetLastError(NULL);

	int sp = SetSystemPaletteUse(hDC,SYSPAL_NOSTATIC256);

	//int sp = SetSystemPaletteUse(hDC,SYSPAL_NOSTATIC);

	sprintf(str,"Old Palette Use\n  NOSTAT %d\n  STAT %d\n  ERR %d (%d)",

		sp==SYSPAL_NOSTATIC,sp==SYSPAL_STATIC,sp==SYSPAL_ERROR,GetLastError());

	MessageBox(NULL,str,"ERROR",MB_OK|MB_ICONEXCLAMATION);

	

	SetLastError(NULL);

	UINT pu = GetSystemPaletteUse(hDC);

	sprintf(str,"New Palette Use\n  NOSTAT %d\n  STAT %d\n  ERR %d (%d)",

		pu==SYSPAL_NOSTATIC,pu==SYSPAL_STATIC,pu==SYSPAL_ERROR,GetLastError());

	MessageBox(NULL,str,"ERROR",MB_OK|MB_ICONEXCLAMATION);

	

	// Check Device

	// This shows whether the device supports palettes

	// see http://msdn.microsoft.com/library/default.asp?url=/library/en-us/gdi/colors_92hx.asp

	int rc = GetDeviceCaps(hDC,RASTERCAPS);

	int sz = GetDeviceCaps(hDC,SIZEPALETTE);

	int cr = GetDeviceCaps(hDC,COLORRES);

	sprintf(str,"DeviceCaps\nRatercaps: %d %X\nSizepalette %d\nColorres %d",rc,rc,sz,cr);

	MessageBox(NULL,str,"ERROR",MB_OK|MB_ICONEXCLAMATION);

	

#else

	// Check System

	if( SetSystemPaletteUse(hDC,SYSPAL_NOSTATIC256)==SYSPAL_ERROR ){

		sprintf(str,"SetSystemPaletteUse:  ERR %d",GetLastError());

		MessageBox(NULL,str,"ERROR",MB_OK|MB_ICONEXCLAMATION);

	}

	if( GetSystemPaletteUse(hDC)==SYSPAL_ERROR ){

		sprintf(str,"GetSystemPaletteUse:  ERR %d",GetLastError());

		MessageBox(NULL,str,"ERROR",MB_OK|MB_ICONEXCLAMATION);

	}



	// Check Device

	// This shows whether the device supports palettes 

	//  (emipirically, I've seen that size=0 when not working)

	// see http://msdn.microsoft.com/library/default.asp?url=/library/en-us/gdi/colors_92hx.asp

	if( GetDeviceCaps(hDC,SIZEPALETTE)< (1<<WINDOW_BITS) ){

		sprintf(str,"Device Caps\nDevice palette limited to %d / %d",

			GetDeviceCaps(hDC,SIZEPALETTE),1<<WINDOW_BITS);

		MessageBox(NULL,str,"ERROR",MB_OK|MB_ICONEXCLAMATION);

	}

#endif

	

#if USE_SYSTEM_PALETTE

	// Try using system palette

	// The following is really lame way to gain access to System LogPalette handle

	// Select it for Device

	HPALETTE hTmpPal;  

	hTmpPal = SelectPalette(hDC,hPal,FALSE);

	if(hTmpPal!=NULL){

		SelectPalette(hDC,hTmpPal,FALSE);

		DeleteObject(hPal);

		hPal = hTmpPal;

	}

	

#else

	// Create Palette

	if( (hPal=CreatePalette(pPal)) == NULL ){

		sprintf(str,"Can't Create Palette: Error (%d)",GetLastError());

		MessageBox(NULL,str,"ERROR",MB_OK|MB_ICONEXCLAMATION);

	}

	

	// Select it for Device

	if( SelectPalette(hDC,hPal,FALSE) == NULL ){

		sprintf(str,"Can't Select Palette: Error (%d)",GetLastError());

		MessageBox(NULL,str,"ERROR",MB_OK|MB_ICONEXCLAMATION);

	};

	

	// "Realize" it

	if( RealizePalette(hDC) == NULL ){

		sprintf(str,"Can't Realize Palette: Error (%d)",GetLastError());

		MessageBox(NULL,str,"ERROR",MB_OK|MB_ICONEXCLAMATION);

	};

#endif

	

	free (pPal);

}



////////////////////////////////////////////////////////////////////

// KillGLWindow

//

void KillGLWindow(void)								// Properly Kill The Window

{

	if(WindowFlag){   // If window not already killed

		

		if (VisWindow->FullScreen)										// Are We In Fullscreen Mode?

		{

			ChangeDisplaySettings(NULL,0);					// If So Switch Back To The Desktop

			ShowCursor(TRUE);								// Show Mouse Pointer

		}

		

		if (hRC)											// Do We Have A Rendering Context?

		{

			if (!wglMakeCurrent(NULL,NULL))					// Are We Able To Release The DC And RC Contexts?

			{

				MessageBox(NULL,"Release Of DC And RC Failed.","VisServer: SHUTDOWN ERROR",

					MB_OK | MB_ICONINFORMATION);

			}

			

			if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?

			{

				MessageBox(NULL,"Release Rendering Context Failed.","VisServer: SHUTDOWN ERROR",

					MB_OK | MB_ICONINFORMATION);

			}

			hRC=NULL;										// Set RC To NULL

		}

		

#if DC_FUNC

		if (hDC && !ReleaseDC(hWnd,hDC))					// Are We Able To Release The DC

#else 

		if (hDC && !DeleteDC(hDC))						// Are We Able To Release The DC

#endif

		{

			MessageBox(NULL,"Release Device Context Failed.","VisServer: SHUTDOWN ERROR",

				MB_OK | MB_ICONINFORMATION);

			hDC=NULL;										// Set DC To NULL

		}

		

		if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?

		{

			MessageBox(NULL,"Could Not Release hWnd.","VisServer: SHUTDOWN ERROR",

				MB_OK | MB_ICONINFORMATION);

			hWnd=NULL;										// Set hWnd To NULL

		}

		

		if (!UnregisterClass("VisServer",hInstance))			// Are We Able To Unregister Class

		{

			MessageBox(NULL,"Could Not Unregister Class.","VisServer: SHUTDOWN ERROR",

				MB_OK | MB_ICONINFORMATION);

			hInstance=NULL;									// Set hInstance To NULL

		}



		// Unset Flag

		WindowFlag=0;

	}

}



////////////////////////////////////////////////////////////////////

// CreateGLWindow

//

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*/

int CreateGLWindow()

{

	GLuint		PixelFormat;			// Holds The Results After Searching For A Match

	WNDCLASSEX	wc;						// Windows Class Structure

	DWORD		dwExStyle;				// Window Extended Style

	DWORD		dwStyle;				// Window Style



	// If window already exists, kill it:

	if(WindowFlag) KillGLWindow();



	// Now Go Ahead and Make Window



	// PNS:

	// First Get the window Rectangle -- made a little more difficult by the 

	// multi monitor situation.  This routine also sets the global HMONITOR *hMon.

	// GetGLWindowRect(width,height,&WindowRect);

	if( !GetGLWindowRect(&(VisWindow->rect)) ){

		return FALSE;

	}



	VisWindow->width  = (float)((VisWindow->rect).right - (VisWindow->rect).left);

	VisWindow->height = (float)((VisWindow->rect).bottom - (VisWindow->rect).top);





	// Window Info

	hInstance			= GetModuleHandle(NULL);				// Grab An Instance For Our Window

	wc.cbSize			= sizeof(WNDCLASSEX);

	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.

	wc.lpfnWndProc		= (WNDPROC) WndProc;					// WndProc Handles Messages

	wc.cbClsExtra		= 0;									// No Extra Window Data

	wc.cbWndExtra		= 0;									// No Extra Window Data

	wc.hInstance		= hInstance;							// Set The Instance

	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon

	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer

	wc.hbrBackground	= NULL;									// No Background Required For GL

	wc.lpszMenuName		= NULL;									// We Don't Want A Menu

	wc.lpszClassName	= "VisServer";							// Set The Class Name

	wc.hIconSm			= NULL;									// Load The Default Icon

	

	if (!RegisterClassEx(&wc))									// Attempt To Register The Window Class

	{

		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);

		return FALSE;											// Return FALSE

	}



	if (VisWindow->FullScreen)												// Are We Still In Fullscreen Mode?

	{

		dwExStyle=WS_EX_APPWINDOW;								// Window Extended Style

		dwStyle=WS_POPUP;										// Windows Style

		ShowCursor(FALSE);										// Hide Mouse Pointer

	}

	else

	{

		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style

		dwStyle=WS_OVERLAPPEDWINDOW;							// Windows Style

	}

	

	AdjustWindowRectEx(&(VisWindow->rect), dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	

	// Create The Window

	if (!(hWnd=CreateWindowEx(	dwExStyle,							// Extended Style For The Window

								"VisServer",						// Class Name

								WINDOW_TITLE,						// Window Title

								dwStyle |							// Defined Window Style

								WS_CLIPSIBLINGS |					// Required Window Style

								WS_CLIPCHILDREN,					// Required Window Style

								(VisWindow->rect).left,				// Window Position

								(VisWindow->rect).top,				// Window Position

								(int)VisWindow->width,					// Window Width

								(int)VisWindow->height,					// Calculate Window Height

								NULL,								// No Parent Window

								NULL,								// No Menu

								hInstance,							// Instance

								NULL)))								// Dont Pass Anything To WM_CREATE

	{

		KillGLWindow();								// Reset The Display

		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);

		return FALSE;								// Return FALSE

	}

	VisWindow->hWnd=hWnd;



	// CREATE Device Context

	// NOTE::: This also actually the wrong the DC -- it's for the primary

	//         monitor.  You'd need to use EnumDisplayMonitors to get the right

	//         hDC, but that is way too difficult and I think it only effects

	//         some painting characteristics

#if DC_FUNC

	if (!(hDC=GetDC(hWnd)))							// Did We Get A Device Context?

#else 

	if(!(hDC = CreateDC(TEXT("DISPLAY"),NULL,NULL,NULL)))

//  if(!(hDC = CreateDC(mInf.szDevice,mInf.szDevice,NULL,NULL)))

//	if(!(hDC = CreateDC(mInf.szDevice,NULL,NULL,NULL)))

#endif

	{

		KillGLWindow();								// Reset The Display

		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);

		return FALSE;								// Return FALSE

	}

	







	// Get/Set Pixel Descriptor

	PIXELFORMATDESCRIPTOR pfd; 

	int npf=2;

	for(int i=1;i<=npf;i++){

		npf = DescribePixelFormat(hDC,i,sizeof(PIXELFORMATDESCRIPTOR),&pfd);

		

#if VISWIN_DEBUG>1



		if(pfd.dwFlags&(0x00000001)) { // PFD_DOUBLEBUFFER

			char str[1000];

			sprintf(str,"Pixel Format %d / %d",i,npf);

			if(pfd.iPixelType==PFD_TYPE_RGBA) sprintf(str,"%s\niPixType RGBA",str);

			else if(pfd.iPixelType==PFD_TYPE_COLORINDEX) sprintf(str,"%s\niPixType COLORINDEX",str);

			else sprintf(str,"%s\niPixType UNKNOWN",str);

			sprintf(str,"%s\nbReserved %d",str,pfd.bReserved);

			sprintf(str,"%s\ncColorBits %d",str,pfd.cColorBits);

			sprintf(str,"%s\ncAlphaBits %d",str,pfd.cAlphaBits);

			sprintf(str,"%s\ncDepthBits %d",str,pfd.cDepthBits);

			sprintf(str,"%s\ncAccumBits %d",str,pfd.cAccumBits);

			sprintf(str,"%s\ncStencilBits %d",str,pfd.cStencilBits);

			sprintf(str,"%s\ndwFlags %lx",str,pfd.dwFlags);

			if(pfd.dwFlags&(0x00000001)) sprintf(str,"%s\nPFD_DOUBLEBUFFER",str);          

			if(pfd.dwFlags&(0x00000002)) sprintf(str,"%s\nPFD_STEREO",str);                

			if(pfd.dwFlags&(0x00000004)) sprintf(str,"%s\nPFD_DRAW_TO_WINDOW",str);        

			if(pfd.dwFlags&(0x00000008)) sprintf(str,"%s\nPFD_DRAW_TO_BITMAP",str);        

			if(pfd.dwFlags&(0x00000010)) sprintf(str,"%s\nPFD_SUPPORT_GDI",str);           

			if(pfd.dwFlags&(0x00000020)) sprintf(str,"%s\nPFD_SUPPORT_OPENGL",str);        

			if(pfd.dwFlags&(0x00000040)) sprintf(str,"%s\nPFD_GENERIC_FORMAT",str);        

			if(pfd.dwFlags&(0x00000080)) sprintf(str,"%s\nPFD_NEED_PALETTE",str);          

			if(pfd.dwFlags&(0x00000100)) sprintf(str,"%s\nPFD_NEED_SYSTEM_PALETTE",str);   

			if(pfd.dwFlags&(0x00000200)) sprintf(str,"%s\nPFD_SWAP_EXCHANGE",str);         

			if(pfd.dwFlags&(0x00000400)) sprintf(str,"%s\nPFD_SWAP_COPY",str);             

			if(pfd.dwFlags&(0x00000800)) sprintf(str,"%s\nPFD_SWAP_LAYER_BUFFERS",str);    

			if(pfd.dwFlags&(0x00001000)) sprintf(str,"%s\nPFD_GENERIC_ACCELERATED",str);   

			if(pfd.dwFlags&(0x00002000)) sprintf(str,"%s\nPFD_SUPPORT_DIRECTDRAW",str);    

			

			MessageBox(NULL,str,"ERROR",MB_OK|MB_ICONEXCLAMATION);

		}

#endif

	}



    pfd.nSize        = sizeof(PIXELFORMATDESCRIPTOR); 

    pfd.nVersion     = 1; 

//    pfd.dwFlags      = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_NEED_PALETTE; 

    pfd.dwFlags      = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER; 

    pfd.dwLayerMask  = PFD_MAIN_PLANE; 

#if INDEX_MODE

	pfd.iPixelType   = PFD_TYPE_COLORINDEX;

#else

	pfd.iPixelType   = PFD_TYPE_RGBA; 

#endif

    pfd.cColorBits   = WINDOW_BITS; 

    pfd.cDepthBits   = 8;

    pfd.cAccumBits   = 0; 

    pfd.cStencilBits = 0; 

 

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	// Did Windows Find A Matching Pixel Format?

	{

		KillGLWindow();								// Reset The Display

		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);

		return FALSE;								// Return FALSE

	}

	

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		// Are We Able To Set The Pixel Format?

	{

		KillGLWindow();								// Reset The Display

		char str[200];

		sprintf(str,"Can't set pixel format: Error (%d/%d)",GetLastError(),PixelFormat);

		MessageBox(NULL,str,"ERROR",MB_OK|MB_ICONEXCLAMATION);

		return FALSE;								// Return FALSE

	}

		

	wglMakeCurrent(NULL, NULL); 

	if (!(hRC=wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?

	{

		KillGLWindow();								// Reset The Display

		char str[200];

		sprintf(str,"Can't Create A GL Rendering Context: Error (%d/%X)",GetLastError());

		MessageBox(NULL,str,"ERROR",MB_OK|MB_ICONEXCLAMATION);

		return FALSE;								// Return FALSE

	}



#if VISWIN_DEBUG

	// DEBUG -- LOOK AT PFD

	char str[1000];

	DescribePixelFormat(hDC, PixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

	if(pfd.iPixelType&PFD_TYPE_RGBA) sprintf(str,"iPixType RGBA");

	else if(pfd.iPixelType&PFD_TYPE_COLORINDEX) sprintf(str,"iPixType COLORINDEX");

	else sprintf(str,"iPixType UNKNOWN");

	sprintf(str,"%s\nbReserved %d",str,pfd.bReserved);

	sprintf(str,"%s\ncColorBits %d",str,pfd.cColorBits);

	sprintf(str,"%s\ncAlphaBits %d",str,pfd.cAlphaBits);

	sprintf(str,"%s\ncDepthBits %d",str,pfd.cDepthBits);

	sprintf(str,"%s\ncAccumBits %d",str,pfd.cAccumBits);

	sprintf(str,"%s\ncStencilBits %d",str,pfd.cStencilBits);

	sprintf(str,"%s\ndwFlags %lx",str,pfd.dwFlags);

	MessageBox(NULL,str,"ERROR",MB_OK|MB_ICONEXCLAMATION);

#endif





#if INDEX_MODE

//	CreateIndexPalette(); // Color Palette for 8bit color

	CreateRGBPalette(); // Color Palette for 8bit color

#else

	CreateRGBPalette(); // Color Palette for 8bit color

#endif

		



	if(!wglMakeCurrent(hDC,hRC))					// Try To Activate The Rendering Context

	{

		KillGLWindow();								// Reset The Display

		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);

		return FALSE;								// Return FALSE

	}



	ShowWindow(hWnd,SW_SHOW);						// Show The Window

	SetForegroundWindow(hWnd);						// Slightly Higher Priority

	SetFocus(hWnd);									// Sets Keyboard Focus To The Window

	glViewport(0,0,(int)(VisWindow->width),(int)(VisWindow->height));  // Set Up Our Perspective GL Screen





	// Setup the OpenGL Properties on the Window

	InitGLWindow();







	// SetFlag

	WindowFlag=1;

	return TRUE;									// Success

}





