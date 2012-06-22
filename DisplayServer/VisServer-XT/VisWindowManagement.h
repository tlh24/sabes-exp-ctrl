// VisWindowManagement.h
//
//////////////////////////////////////////////////////////////////////

//#if _MSC_VER > 1000
//#pragma once
//#endif // _MSC_VER > 1000

#include "resource.h"       // main symbols

#define WINDOW_MONITOR_POS  'L'    // If not primary monitor (ID==1), which position
                                   // 'L'eft, 'R'ight, 'U'p, or 'D'own
#define WINDOW_MONITOR_ID   1 //2	   // INT -- Which Monitor?
#define WINDOW_FULLSCREEN   1 //0	   // BOOLEAN -- whether to use full-screen mode
#define WINDOW_WIDTH		640    // INT -- Only used if NOT full-screen mode (debugging mostly)
#define WINDOW_HEIGHT		480    // INT -- Only used if NOT full-screen mode (debugging mostly)
#define WINDOW_BITS			8	   // INT -- color depth
#define WINDOW_TITLE		"VisServer"
#define INDEX_MODE          0
#define USE_SYSTEM_PALETTE  0

extern HDC			hDC;		// Private GDI Device Context
extern HGLRC		hRC;		// Permanent Rendering Context
extern HWND			hWnd;		// Holds Our Window Handle
extern HINSTANCE	hInstance;	// Holds The Instance Of The Application

extern int          WindowFlag; // Flag Existence of Window

void KillGLWindow(void);
int  CreateGLWindow(void);
void ReSizeGLWindow(int width, int heigth);
