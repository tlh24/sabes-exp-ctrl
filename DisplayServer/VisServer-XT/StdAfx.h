// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__903D8F49_E9E8_4810_8198_2CA38526FDD5__INCLUDED_)
#define AFX_STDAFX_H__903D8F49_E9E8_4810_8198_2CA38526FDD5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRICT

// PNS 4/01:  MS hasn't released new gdk headers, and so you need
//            to manually add these to get WIN2K ONLY support
//            for multiple monitors
#define WIN32_WINNT 0x0500
#define WINVER 0x0500 
// Following was the orginal
//#ifndef _WIN32_WINNT
//#define _WIN32_WINNT 0x0400
//#endif
#define _ATL_APARTMENT_THREADED

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
class CExeModule : public CComModule
{
public:
	LONG Unlock();
	DWORD dwThreadID;
	HANDLE hEventShutdown;
	void MonitorShutdown();
	bool StartMonitor();
	bool bActivity;
};
extern CExeModule _Module;
#include <atlcom.h>


// PNS:
#include "windows.h"
#include "wingdi.h"
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <gl\glaux.h>		// Header File For The Glaux Library
#include "VisObject.h"		// VisObject base clase

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__903D8F49_E9E8_4810_8198_2CA38526FDD5__INCLUDED)
