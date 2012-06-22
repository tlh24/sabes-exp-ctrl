// if compiling for C++ declare plain C functions
#ifdef __cplusplus
extern "C" {
#endif

#include <conio.h>

#define PortOutput(a,b) _outp(a,b)

#define PortInput(a) _inp(a)

extern int g_SysGrantIO( int iPort );

#ifdef __cplusplus
}
#endif
