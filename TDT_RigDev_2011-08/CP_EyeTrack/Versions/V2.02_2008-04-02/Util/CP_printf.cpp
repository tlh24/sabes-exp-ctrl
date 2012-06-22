#include "../BuildOptions.h"
#include <windows.h>
#include <stdio.h>
#include "Console.h"
#include "CP_printf.h"

#define MAX_STR_LEN  2048

int    x_iDebugThresh = 0;
char   x_szTmp[MAX_STR_LEN];
CConsole x_CmdWnd;


// Colors for different debug levels
//FOREGROUND_BLUE, FOREGROUND_GREEN, FOREGROUND_RED, FOREGROUND_INTENSITY, 
//BACKGROUND_BLUE, BACKGROUND_GREEN, BACKGROUND_RED, and BACKGROUND_INTENSITY. 
// See SetConsoleTextAttribute()
WORD x_awDebugColors[N_PRINT_LEVELS] = {
                   FOREGROUND_GREEN,
                   FOREGROUND_BLUE | FOREGROUND_INTENSITY,
                   FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED,
                   FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY,
                   FOREGROUND_RED | FOREGROUND_INTENSITY, 
                   FOREGROUND_GREEN | FOREGROUND_INTENSITY};


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int __cdecl CP_printfCreate( char * szTitle ){
  x_CmdWnd.Create(szTitle, TRUE);
  x_CmdWnd.Color( x_awDebugColors[LEVEL_NORMAL] );
  x_CmdWnd.Clear();

  return 0;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int __cdecl CP_printfDestroy( ){
  x_CmdWnd.Close();
  return 0;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int __cdecl CP_printfShow( ){
  x_CmdWnd.Show(1);
  return 0;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int __cdecl CP_printfHide( ){
  x_CmdWnd.Show(0);
  return 0;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  A complete (almost) analog of vprintf, but writes into
//  the shadow string.
//  Returns number of caracters written or a negative value on error

int __cdecl CP_vprintf( int iDebugLevel, const char *format, va_list args) {
  int iRet;

  if( (iDebugLevel < DEBUG_THRESHOLD) || 
      (iDebugLevel < 0) || (iDebugLevel >= N_PRINT_LEVELS))  return 0;

  iRet = _vsnprintf( x_szTmp, MAX_STR_LEN, format, args);  
  // Did some error, but not buffer overflow occur?
  if( (iRet < 0) && (iRet != -1) ) { 
    return iRet;
  }
  // Set text color
  x_CmdWnd.Color( x_awDebugColors[iDebugLevel] );
  x_CmdWnd.Output(x_szTmp);

//  strcat( g_szLogBuffer, x_szTmp );  // add to the log string
  return iRet; 

}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  A complete (almost) analog of printf, but writes into
//  the shadow string.
//  Returns number of caracters written or a negative value on error

int __cdecl CP_printf( const char *format, ...) {
  va_list args;
  int iRet;

  va_start( args, format);
  iRet = CP_vprintf(LEVEL_LOG, format, args );
  va_end(args);
  return iRet;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int __cdecl CP_printfDbg( int iDebugLevel, const char *format, ... ) {
  va_list args;
  int iRet;

  va_start( args, format);
  iRet = CP_vprintf(iDebugLevel, format, args );
  va_end(args);
  return iRet;

}

