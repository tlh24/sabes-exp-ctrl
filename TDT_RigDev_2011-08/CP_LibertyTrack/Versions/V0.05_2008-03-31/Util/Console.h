#if !defined(__CONSOLE_H_)
#define __CONSOLE_H_

#include <windows.h>
class CConsole
{
public:
	CConsole() 
	{ 
		hConsole = NULL; 
	};

public:
	// create the console
	bool   Create(const char* szTitle, bool bNoClose = false);
	
	// set color for output
	void   Color(WORD wColor = NULL);
	// write output to console
	void   Output(const char* szOutput = NULL, ...);
	
	// set and get title of console
	void   SetTitle(const char* szTitle);
	char*  GetTitle();

	// get HWND and/or HANDLE of console
	HWND   GetHWND();
	HANDLE GetHandle();

	// show/hide the console
	void   Show(bool bShow = true);
	// disable the [x] button of the console
	void   DisableClose();
	// clear all output
	void   Clear();

	// close the console and delete it
	void   Close();

private:
	HANDLE hConsole;
};

#endif 