#include "ClassFactory.h"
#include "CP_LibertyTrackCom.h"
#include "CP_LibertyClass.h"

//-------------------------------------------------------
HRESULT CFactory::QueryInterface(REFIID iid, void** ppv){

  if (ppv == NULL) return E_INVALIDARG;
  if((iid == IID_IUnknown) || (iid == IID_IClassFactory)) {
		*ppv = (IClassFactory *)this;
	  AddRef();
	  return S_OK;	
  }
	*ppv = NULL;
	return E_NOINTERFACE;
}

//-------------------------------------------------------
HRESULT CFactory::CreateInstance(IUnknown *pUnknownOuter, REFIID iid, void **ppv){
	CP_LibertyClass *pCP_PO;
	HRESULT hr;
  ITypeLib* pTypeLib;

  *ppv = NULL;
  // We don't support aggregation, return an error if requested
	if(pUnknownOuter != NULL)	return CLASS_E_NOAGGREGATION;

  pCP_PO = new CP_LibertyClass; 
	if( pCP_PO == NULL) return E_OUTOFMEMORY;

  //Init m_pTypeInfo
  hr = LoadRegTypeLib(LIBID_CP_LibertyTrackLib, 0, 0, LANG_NEUTRAL, &pTypeLib);
	if(hr != S_OK) return E_FAIL;

  hr = pTypeLib->GetTypeInfoOfGuid(IID_ILibertyTrack, &pCP_PO->m_pTypeInfo);
	pTypeLib->Release();
	if(hr != S_OK) return hr;

  // Return interface pointer
	hr = pCP_PO->QueryInterface(iid, ppv);
	pCP_PO->Release();
	return hr;
}


