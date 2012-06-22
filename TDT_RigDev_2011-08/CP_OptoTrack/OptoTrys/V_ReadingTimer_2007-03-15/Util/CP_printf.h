
#ifndef CP_PRINTF_H
#define CP_PRINTF_H

#include <stdarg.h>
#include <stdio.h>
//*********************************************************
// if compiling for C++ declare plain C functions
#ifdef __cplusplus
extern "C" {
#endif

// use these functions to print to the log window
extern int __cdecl CP_prn_create( char * szTitle );
extern int __cdecl CP_prn_destroy( );
extern int __cdecl CP_printf( const char *format,...);
extern int __cdecl CP_vprintf( const char *format, va_list args);

// end of extern "C" {
#ifdef __cplusplus
}
#endif

#endif   //#ifndef CP_PRINTF_H
