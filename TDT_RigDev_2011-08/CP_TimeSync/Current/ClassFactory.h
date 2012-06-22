#ifndef __CLASS_FACTORY_H_
#define __CLASS_FACTORY_H_

#include <unknwn.h>

//=================================================================================
class CFactory : public IClassFactory {

public:
  //IUnknown
	HRESULT __stdcall QueryInterface(REFIID iid, void** ppv);
	ULONG __stdcall AddRef() {return 1;};
	ULONG __stdcall Release() {return 1;};
  //IClassFactory
	HRESULT __stdcall CreateInstance(IUnknown *pUnknownOuter, REFIID iid, void** ppv);
  HRESULT __stdcall LockServer(BOOL bLock){ return S_OK;};

};

#endif //#ifndef __CLASS_FACTORY_H_
