#ifndef __ATL_DEFS_H
#define __ATL_DEFS_H

// define minimum system required
// Windows 2000 _WIN32_WINNT=0x0500 and WINVER=0x0500 (generates warnings with old headers)
// Windows NT 4.0 _WIN32_WINNT=0x0400 and WINVER=0x0400 

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif

#ifndef WINVER
#define WINVER 0x0400
#endif


#define _ATL_APARTMENT_THREADED

#include <atlbase.h>
//  _Module is used in <atlcom.h>
// <atlcom.h> is required by all interfaces
// 

// We define our custom Lock()/Unlock methods (see CP_Display.cpp)
class CExeModule : public CComModule
{
public:
  LONG Unlock();
  LONG Lock();
};
extern CExeModule _Module;


#include <atlcom.h>

#endif // #ifndef __ATL_DEFS_H
