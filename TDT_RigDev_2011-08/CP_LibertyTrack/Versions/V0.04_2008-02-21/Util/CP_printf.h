#ifndef CP_PRINTF_H
#define CP_PRINTF_H

#define LEVEL_WARNING LEVEL_HIGH
#define LEVEL_DEBUG     0
#define LEVEL_LOW       1
#define LEVEL_NORMAL    2
#define LEVEL_HIGH      3
#define LEVEL_ERROR     4
#define LEVEL_LOG       5
#define N_PRINT_LEVELS  6

#include <stdarg.h>
#include <stdio.h>
//*********************************************************
// if compiling for C++ declare plain C functions
#ifdef __cplusplus
extern "C" {
#endif

// use these functions to print to the log window
extern int __cdecl CP_printfCreate( char * szTitle );
extern int __cdecl CP_printfDestroy( );
extern int __cdecl CP_printfShow( );
extern int __cdecl CP_printfHide( );
extern int __cdecl CP_printf( const char *format,...);
extern int __cdecl CP_printfDbg( int iDebugLevel, const char *szFormat,...);
extern int __cdecl CP_vprintf( const char *format, va_list args);

// end of extern "C" {
#ifdef __cplusplus
}
#endif

#endif   //#ifndef CP_PRINTF_H
