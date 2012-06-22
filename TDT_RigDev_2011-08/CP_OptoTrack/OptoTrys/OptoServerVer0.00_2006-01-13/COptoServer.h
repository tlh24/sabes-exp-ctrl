// COptoServer.h: Definition of the COptoServer class
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COPTOSERVER_H__03C76C05_6F58_4AB4_9081_7ACCCE01DD55__INCLUDED_)
#define AFX_COPTOSERVER_H__03C76C05_6F58_4AB4_9081_7ACCCE01DD55__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"       // main symbols


// ND Library Files Included
#include "ndtypes.h"
#include "ndhost.h"
#include "ndopto.h"

#define ERROR_STRING_LENGTH 500

/////////////////////////////////////////////////////////////////////////////
// COptoServer

class COptoServer : 
	public IDispatchImpl<IOptoServer, &IID_IOptoServer, &LIBID_OPTOSERVERLib>, 
	public ISupportErrorInfo,
	public CComObjectRoot,
	public CComCoClass<COptoServer,&CLSID_OptoServer>
{
public:
	COptoServer();
	~COptoServer();
	BEGIN_COM_MAP(COptoServer)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IOptoServer)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()
//DECLARE_NOT_AGGREGATABLE(COptoServer) 
// Remove the comment from the line above if you don't want your object to 
// support aggregation. 

DECLARE_REGISTRY_RESOURCEID(IDR_OptoServer)
// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IOptoServer
public:
	STDMETHOD(get_latestframe)(/*[out, retval]*/ double *pVal);
	STDMETHOD(get_error)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(setframe)(/*[in]*/VARIANT var);
	STDMETHOD(setup)(/*[in]*/ VARIANT makers, /*[in]*/ float rate, /*in optional*/ float time);
	STDMETHOD(getBuffer)(/*[in]*/ short marker, /*[out]*/ VARIANT *posVar);
	STDMETHOD(stopBuffer)();
	STDMETHOD(startBuffer)();
	STDMETHOD(get_latest)(/*[out]*/ VARIANT *posVar);
	STDMETHOD(get_next)(/*[out]*/ VARIANT *posVar);
	STDMETHOD(get_active)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_active)(/*[in]*/ short newVal);

private:
	int initialized;
	int started;
	int active;
	int rotated;
	int buffering;
	int porttable[4];
	int markers;
	float framerate;
	double **pos;
	int poslimit[2];
	float **rot;
	float buffertime;
	float bufferbytes;
	void *buffer;
	long latestFrame;
	unsigned int uRealtimeDataReady,uSpoolComplete,uSpoolStatus;
	unsigned long luFrames;
	
	int initializeOptotrak();
	void OptoRotate(Position3d *p);
	unsigned int OptoLatest(int block);
	unsigned int OptoNext(int block);
	unsigned int spoolUpdate();
	void completeBuffer();

	int setPortTable(VARIANT var);
	int calcTableFrame();

	// Error Handling
	void OPTO_ERROR(char *string);
	void OPTO_WARNING(wchar_t *string);
	wchar_t errorString[ERROR_STRING_LENGTH];

};

#endif // !defined(AFX_COPTOSERVER_H__03C76C05_6F58_4AB4_9081_7ACCCE01DD55__INCLUDED_)
