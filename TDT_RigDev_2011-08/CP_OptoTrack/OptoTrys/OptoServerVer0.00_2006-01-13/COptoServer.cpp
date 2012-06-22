// COptoServer.cpp : Implementation of COptoServerApp and DLL registration.

#include "stdafx.h"
#include "OptoServer.h"
#include "OptoFrame.h"
#include "COptoServer.h"
#include "ComUtils.h"

// Optotrak Setup Parameters 
#define MARKER_HZ		2000	// 100 5000  -- each marker's cylce
#define DUTY_CYCLE		.5		// 0 1       -- fraction of that cycle it's on
#define VOLTAGE			7.5		// 6.5 12    -- marker voltage
#define THRESHOLD		30		// 0 255     -- algorithm stuff
#define MIN_GAIN		160		// 0 255     -- algorithm stuff
#define STREAM			1		// ?? Don't change
#define PBUFFERING		0		// 0 or 1		
#define BUFF_TIME		1		// If buffering, this is the buffer length. In any case, must be >0
#define PRE_TRIG_TIME	0		// ?? Don't change
#define FLAGS			0		// Can make requests about algorithm etc... Don't change

/////////////////////////////////////////////////////////////////////////////
//  ERROR REPORTING

//// Required for some of the Common Functions
void
CommonError(char *estring){
	MessageBox(NULL, estring, "OptoServer", MB_OK | MB_ICONEXCLAMATION);
}
////////////////////////////////////////////// OPTO_ERROR
void
COptoServer::OPTO_ERROR(char *estring)
{
	MessageBox(NULL, estring, "OptoServer", MB_OK | MB_ICONEXCLAMATION);
	PostQuitMessage(0);
}

////////////////////////////////////////////// OPTO_WARNING
void
COptoServer::OPTO_WARNING(wchar_t *estring)
{
	int l1,l2;
	l1=wcslen(errorString);
	l2=wcslen(estring);
	if(l1>1 && l1+l2+6<=ERROR_STRING_LENGTH){
		wcscat(errorString,L" :: ");
		wcscat(errorString,estring);
	}
	
	
	//// Don't add the ND error msg if it's a repeat from last time
	static char ndErrLast[MAX_ERROR_STRING_LENGTH+1];
	char ndErr[MAX_ERROR_STRING_LENGTH+1];
	
	if( OptotrakGetErrorString( ndErr,MAX_ERROR_STRING_LENGTH+1 ) == 0 )
	{
		if(!strcmp(ndErr,ndErrLast) && 
			wcslen(errorString)+strlen(ndErr)+4<ERROR_STRING_LENGTH){
			swprintf(errorString,L"%s (%S)",errorString,ndErr);
			strcpy(ndErrLast,ndErr);
		}
	} 
	
}

/////////////////////////////////////////////////////////////////////////////
//

STDMETHODIMP COptoServer::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IOptoServer,
	};

	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
//		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CONSTR/DESTR

COptoServer::COptoServer()
{

	// flags
	initialized=0;
	started=0;
	active=0;
	rotated=0;
	buffering=0;
	// data
	pos = new double*[3];
	for(int i=0;i<3;i++) pos[i]=NULL;
	buffer=NULL;
	// errro
	swprintf(errorString,L"");
}

COptoServer::~COptoServer()
{
	OptotrakDeActivateMarkers();
	TransputerShutdownSystem();  // Close up Optotrak
}

/////////////////////////////////////////////////////////////////////////////
//  PROPERTIES
	
	
STDMETHODIMP COptoServer::get_active(short *pVal)
{
	*pVal=active;
	return S_OK;
}

STDMETHODIMP COptoServer::put_active(short newVal)
{
	if(started){
		if(newVal)
		{
			active=1;
			OptotrakActivateMarkers();
			Sleep(200); // Some time to get markers active
		}
		else if(!newVal)
		{
			active=0;
			OptotrakDeActivateMarkers();
		}
		return S_OK;
	}
	return MAKE_HRESULT(1,FACILITY_ITF,CTL_E_SETNOTPERMITTED);
}


////////// ERROR
STDMETHODIMP 
COptoServer::get_error(BSTR *pVal)
{
	// Put Lastest Optotrak Msg into Error
	OPTO_WARNING(L"");

	*pVal=SysAllocString(errorString);
	swprintf(errorString,L"");
	return S_OK;
}

///////////////////////////////////////////////////////
////////  METHODS


////////////////////////////  INITIALIZE OPTOTRAK
// starts everything again....
int
COptoServer::initializeOptotrak()
{
	static int first=1;

	if(~first) // Not the first call
	{
		TransputerShutdownSystem();  // Close up Optotrak
	}
	first=0;

	//////////////// INITIALIZE SYSTEM: STUFF YOU DO ONLY ONCE
	// TRANSPUTER
	if( TransputerLoadSystem( "system" ) ){
		OPTO_ERROR("Can't load system file to transputer"); return 1; 
	}

	Sleep(2000); // Put in a 2 sec delay to ensure the params are done loading
	if( TransputerInitializeSystem(OPTO_LOG_ERRORS_FLAG) ){ 
		OPTO_ERROR("Can't initialize transputer"); return 2; 
	}
	
	// OPTOTRAK
	if( OptotrakLoadCameraParameters( "standard" ) ){ 
		OPTO_ERROR("Can't load camera parameters"); return 3;
	}

	initialized = 1;

	return 0;
}

////////////////////////////  SET PORTTABLE
int 
COptoServer::setPortTable(VARIANT var)
{
	int i,n;
	double *tmp;

	// Port Table: How Many Markers Per Port (0:3)
	VariantToArray(&n,&tmp,&var);					// Get from array
	for(i=0;i<n&&i<4;i++) porttable[i]=(int)tmp[i];		// Fill out 4-vector if missing elements
	for(   ;i<4    ;i++) porttable[i]=0;
	delete tmp;
	if( OptotrakSetStroberPortTable(porttable[0],porttable[1],porttable[2],porttable[3]) )
	{
		OPTO_ERROR("Can't load port table" );
	}
	return porttable[0]+porttable[1]+porttable[2]+porttable[3];
}


//////////////////////////// SETUP
STDMETHODIMP COptoServer::setup(VARIANT var, float rate, float time)
{
	int e;
	char str[50];

	if( !initialized && (e = initializeOptotrak()) ){
	//return S_OK;
		sprintf(str,"Can't initialize:  error %d",e);
		OPTO_ERROR(str);
		started = 0;
		return MAKE_HRESULT(1,FACILITY_ITF,CONNECT_E_CANNOTCONNECT);
	}

	markers=setPortTable(var);							// Read porttable and send it to Optotrak
	if(rate<=0) framerate=100;	else framerate=rate;	// Frame Rate
	if(time<=0) buffertime = 1; else buffertime=time;	// Buffer Time

	// Collection Parameters
	if( OptotrakSetupCollection( markers, rate,
		MARKER_HZ,THRESHOLD,MIN_GAIN,STREAM,DUTY_CYCLE,VOLTAGE,buffertime,PRE_TRIG_TIME, FLAGS) )
	{
		char str[50];
		sprintf(str,"Can't load collection parameters:\n  [%d,%d,%d,%d], %f, %f",
			porttable[0],porttable[1],porttable[2],porttable[3],rate,time);
		OPTO_ERROR(str);
		started = 0;
		return MAKE_HRESULT(1,FACILITY_ITF,CONNECT_E_CANNOTCONNECT);
	}
	Sleep(1000);
	
	// Allocate Pos Memory
	poslimit[0]=3; poslimit[1]=markers;

	for(int i=0;i<3;i++){
		if(pos[i]!=NULL) delete pos[i];
		pos[i]=new double[markers];
	}

	// Allocate Buffer Memory
	if(buffertime<=0) return E_INVALIDARG;
	if(buffer!=NULL) delete buffer;
	buffer = (void *)malloc( (size_t) 
		((buffertime+.5) * framerate * markers) * sizeof(Position3d) );
	

	// Flag
	started = 1;

	// Make sure markers are off to start
	put_active(0);
	
	return S_OK;
}

//////////////////////////// SETFRAME
STDMETHODIMP COptoServer::setframe(VARIANT var)
{

	// Setup for Frame measurement
	setup(var,100,1);
	// Measure and calculate Frame
	if( calcTableFrame() )  return MAKE_HRESULT(1,FACILITY_ITF,CONNECT_E_CANNOTCONNECT);
	
	rotated=1;
	started=0;
	return S_OK;
}

//////////////////////////// OPTO ROTATE
void
COptoServer::OptoRotate(Position3d *p)
{
	int i,k;

	// ROTATED INTO CALIBRATED FRAME
	if(rotated){
		for(k=0;k<markers;k++){
			if( p[k].x<MAX_NEGATIVE ){ pos[0][k]=pos[1][k]=pos[2][k]=MAX_NEGATIVE-1; }
			else{
				for(i=0;i<3;i++)   
					pos[i][k] = rot[i][0]*p[k].x + rot[i][1]*p[k].y + rot[i][2]*p[k].z + rot[i][3];
			}
		}
	}
	// RAW 3D POSITION
	else{
		for(k=0;k<markers;k++){
			if( p[k].x<MAX_NEGATIVE ){ pos[0][k]=pos[1][k]=pos[2][k]=MAX_NEGATIVE-1; }
			else { pos[0][k]=p[k].x; pos[1][k]=p[k].y; pos[2][k]=p[k].z; }
		}
		
	}

}
//////////////////////////// OPTO LATEST
//   - doesn't check if frame is new
unsigned int
COptoServer::OptoLatest(int block)
{
	int k,done;
	unsigned int uElements,uFlags,uFrame;
	Position3d *p = new Position3d[markers];
	
	do{
		done=1;
		DataGetLatest3D(&uFrame,&uElements,&uFlags,p);
		for(k=0; k<markers && done; k++)
			if(block && p[k].x<MAX_NEGATIVE){ done=0; }
	}  while(done==0);
	if(uFlags) OPTO_WARNING(L"Buffer Error (latest)");
	if(markers!=(int)uElements){
		wchar_t tmp[100];
		swprintf(tmp,L"Wrong number of elements (%u/%d latest)",uElements,markers);
		OPTO_WARNING(tmp);
	}

	OptoRotate(p);

	return uFrame;
}

//////////////////////////// LATEST
//   - doesn't check if frame is new
STDMETHODIMP COptoServer::get_latest(VARIANT *posVar)
{
	latestFrame = OptoLatest(0);
	VariantFromArray2(poslimit,pos,posVar);

	// Need to spool periodically
	if(buffering){
		if( spoolUpdate() ) OPTO_WARNING(L"Buffer overflow");
	}

	return S_OK;
}


STDMETHODIMP COptoServer::get_latestframe(double *pVal)
{
	*pVal = (double) latestFrame;
	return S_OK;
}

//////////////////////////// OPTO NEXT
unsigned int
COptoServer::OptoNext(int block)
{
	int k,done;
	unsigned int uElements,uFlags,uFrame;
	Position3d *p = new Position3d[markers];
	
	do{
		done=1;
		DataGetNext3D(&uFrame,&uElements,&uFlags,p);
		for(k=0; k<markers && done; k++)
			if(block && p[k].x<MAX_NEGATIVE){ done=0; }
	}  while(done==0);

	if(uFlags) OPTO_WARNING(L"Buffer Error (next)");
	if(markers!=(int)uElements){
		wchar_t tmp[100];
		swprintf(tmp,L"Wrong number of elements (%u/%d next)",uElements,markers);
		OPTO_WARNING(tmp);
	}
	
	OptoRotate(p);

	return uFrame;
}
//////////////////////////// NEXT
STDMETHODIMP COptoServer::get_next(VARIANT *posVar)
{
	long frame;
	frame = OptoNext(0);
	VariantFromArray2(poslimit,pos,posVar);

	// Need to spool periodically??
	if(buffering){
		if( spoolUpdate() ) OPTO_WARNING(L"Buffer overflow");
	}

	return S_OK;
}


//////////////////////////////  BUFFER
STDMETHODIMP COptoServer::startBuffer()
{
	// Stop buffering if it's already started
	if(buffering){
		int e;
		if( e=DataBufferStop() ){
			wchar_t tmp[100];
			swprintf(tmp,L"Spool Stop Error (%d, frames %lu)",e,luFrames);
			OPTO_WARNING(tmp);
		}
		buffering=0;
	}

	// Dissociate previous buffer
	DataBufferAbortSpooling();
	

	if( DataBufferInitializeMem(OPTOTRAK,buffer) )
		OPTO_WARNING(L"Can't initialize buffer");

	// Flags need to be reset?!?
	uRealtimeDataReady=uSpoolComplete=uSpoolStatus=0;
	luFrames=0;

	// Start
	if( DataBufferStart() ) OPTO_WARNING(L"Can't start buffer");
	buffering=1;	

	return S_OK;
}


STDMETHODIMP COptoServer::stopBuffer()
{
	int e;
	if( e=DataBufferStop() ){
		wchar_t tmp[100];
		swprintf(tmp,L"Spool Stop Error (%d, frames %lu)",e,luFrames);
		OPTO_WARNING(tmp);
	}
	buffering=0;
	
	return S_OK;
}

void COptoServer::completeBuffer()
{
	int i;

	if(buffering){
		DataBufferStop();
		buffering=0;
	}

	// Finish Getting Spool
	for(i=0; !uSpoolComplete && i<1000; i++) { spoolUpdate(); Sleep(10); }
	if(!uSpoolComplete){
		wchar_t tmp[100];
		swprintf(tmp,L"Couldn't Complete Spool(complete 0x%04x, frames %lu)",uSpoolComplete,luFrames);
		OPTO_WARNING(tmp);
	}
}

unsigned int
COptoServer::spoolUpdate()
{
	if( DataBufferWriteData( &uRealtimeDataReady, &uSpoolComplete, &uSpoolStatus, &luFrames ) ){
		
		if( uRealtimeDataReady ){
			wchar_t tmp[100];
			swprintf(tmp,L"Spool Update Error (ready 0x%04x, frames %lu)",uRealtimeDataReady,luFrames);
			OPTO_WARNING(tmp);
			uRealtimeDataReady=0;
		}
		if( uSpoolStatus ){
			wchar_t tmp[100];
			swprintf(tmp,L"Spool Update Error (status 0x%04x, frames %lu)",uSpoolStatus,luFrames);
			OPTO_WARNING(tmp);
			uSpoolStatus=0;
		}
	}
	return uSpoolComplete;
}

STDMETHODIMP COptoServer::getBuffer(short marker, VARIANT *posVar)
{	
	/////////////////// Convert Spool to pos matrix
	double **bpos;
	unsigned long f;
	int j,id;
	Position3d *p;

	// ...
	completeBuffer();
	
	// Make Data Structures
	bpos=new double*[luFrames];
	for(f=0;f<luFrames;f++){
		bpos[f]=new double[3];
	}
	
	// Copy and rotate
	p=(Position3d *)buffer;
	for( f=0;f<luFrames;f++){
		id = f*markers + (marker-1);
		if(rotated){
			if( p[id].x<MAX_NEGATIVE ){ bpos[f][0]=bpos[f][1]=bpos[f][2]=MAX_NEGATIVE-1; }
			else{
				for(j=0;j<3;j++)   
					bpos[f][j] = rot[j][0]*p[id].x + rot[j][1]*p[id].y + rot[j][2]*p[id].z + rot[j][3];
			}
		}
		// RAW 3D POSITION
		else{
			if( p[id].x<MAX_NEGATIVE ){ bpos[f][0]=bpos[f][1]=bpos[f][2]=MAX_NEGATIVE-1; }
			else { bpos[f][0]=p[id].x; bpos[f][1]=p[id].y; bpos[f][2]=p[id].z; }
		}
		// Advance the pointer
	}
	
	// Save to VARIANT
	int limit[3] = {luFrames,3};
	VariantFromArray2(limit,bpos,posVar);
	
	
	return S_OK;
}

