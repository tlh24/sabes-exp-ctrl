#include "CP_printf.h"
#include <windows.h>
#include <stdio.h>
#include "Console.h"

#define MAX_STR_LEN  1024

int    x_iDebugThresh = 0;
char   x_szTmp[MAX_STR_LEN];
CConsole x_CmdWnd;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int __cdecl CP_prn_create( char * szTitle ){
  x_CmdWnd.Create(szTitle, TRUE);
  //FOREGROUND_BLUE, FOREGROUND_GREEN, FOREGROUND_RED, FOREGROUND_INTENSITY, 
  //BACKGROUND_BLUE, BACKGROUND_GREEN, BACKGROUND_RED, and BACKGROUND_INTENSITY. 
  // See SetConsoleTextAttribute()
  x_CmdWnd.Color( FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY );
  x_CmdWnd.Clear();

  return 0;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int __cdecl CP_prn_destroy( ){
  x_CmdWnd.Close();
  return 0;
}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  A complete (almost) analog of vprintf, but writes into
//  the shadow string.
//  Returns number of caracters written or a negative value on error

int __cdecl CP_vprintf( const char *format, va_list args) {
  int iRet;

  iRet = _vsnprintf( x_szTmp, MAX_STR_LEN, format, args);  
  // Did some error, but not buffer overflow occur?
  if( (iRet < 0) && (iRet != -1) ) { 
    return iRet;
  }
  x_CmdWnd.Output(x_szTmp);

  return strlen(x_szTmp); 

}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  A complete (almost) analog of printf, but writes into
//  the shadow string.
//  Returns number of caracters written or a negative value on error

int __cdecl CP_printf( const char *format,...) {
  va_list args;
  int iRet;

  va_start( args, format);
  iRet = CP_vprintf( format, args);
  va_end(args);
  return iRet;
}
/*
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  A complete (almost) analog of printf, but writes into
//  the shadow string. 
//  Prints only if iDebugLevel >= x_iDebugThresh
//  Returns number of caracters written or a negative value on error

int __cdecl shp_debug( int iDebugLevel, const char *format,...) {
  va_list args;
  int iRet;

  if( iDebugLevel < x_iDebugThresh ) return 0;
  va_start( args, format);
  iRet = shp_vprintf( format, args);
  va_end(args);
  return iRet;
}



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void __cdecl shp_set_debug_thresh( int iNewDebugThresh){
  x_iDebugThresh = iNewDebugThresh;
}
*/