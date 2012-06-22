// Liberty.cpp : Implementation of CLiberty
#include "stdafx.h"
#include "LibertyServer.h"
#include "Liberty.h"
#include "common\ComUtils.h"
#include "common\nrutil_for_regression.h"
#include "math.h"


// THIS
CLiberty* pLiberty;


// LATEST LAYOUT
#define L_ID_TIME  0
#define L_ID_POS   1   
#define L_ID_ORI   4
#define L_ID_POSV  7  
#define L_ID_ORIV  10
#define L_ID_POSP  13
#define L_ID_ORIP  16
#define L_ID_DIST  19
#define L_ID_ERR   20
#define L_DOUBLES 21

// TRIAL BUFFER LAYOUT
#define B_ID_TIME  0
#define B_ID_POS   1   
#define B_ID_ORI   4
#define B_ID_DIST  7
#define B_ID_ERR   8
#define B_DOUBLES  9

// POLHEMUS DEBUGGING

/////////////////////////////////////////////////////////////////////////////
// CLiberty 

// i modulus n
// we will never be more than n away
long mod(long i, long n){
	if(i<0) return i+n; 
	if(i<n) return i;
	return i-n;
}
int rint(double x){
	if(fmod(x,1)<=.5) return (int)floor(x);
	else return (int)ceil(x);
}

/////////////////////////////////////////////////////////////////////////////
// CLiberty 

STDMETHODIMP CLiberty::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ILiberty
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

CLiberty::CLiberty()
{
	pLiberty = this;

	// flags
	started=0;
	active=0;
	buffering=bufferWaiting=bufferStopRequest=0;
	frameCount=0;
	// data
	lBuffer=NULL; 
	regBuffer=NULL; regT=NULL; regW=NULL; regOut=NULL; regPolyT=NULL;
	latest=NULL; latestDist=NULL; latestErr=NULL;

	sensorIndex=NULL;
	activeSensors=availableSensors=NULL;

	Errors = new wchar_t*[LIBERTY_MAX_ERRORS];
	ErrorCount=0;
	
}

CLiberty::~CLiberty()
{
	// Liberty
	if(active) Dev.StopContPno();
	Sleep(50);
	Dev.Disconnect(); 
	
	// Data
	ManageDataStructures(0);
	clearErrs();
	if (frameList != NULL) delete frameList;
	if (activeSensors != NULL) delete activeSensors;
	if (availableSensors != NULL) delete availableSensors;
}


/////////////////////////////////////////////////////////////////////////////
// SETUP

STDMETHODIMP CLiberty::setup(double buftime, double predtime)
{
	int i;

	// Connect to Device and Check Its Status
	if( !Dev.ConnectUSB() ){
		ErrBox("Can't Connect to Liberty via USB", Dev.GetLastResultStr());
		PostQuitMessage(0);
		return MAKE_HRESULT(1,FACILITY_ITF,CONNECT_E_CANNOTCONNECT);
	}

	if( !Dev.CnxReady() ){
		ErrBox("Liberty not Ready", Dev.GetLastResultStr());
		PostQuitMessage(0);
		return MAKE_HRESULT(1,FACILITY_ITF,CONNECT_E_CANNOTCONNECT);
	}
	started=1;

	// Clear BIT (Built In Test) ERRORS and check for other errors
	CPDIbiterr cBE;
	Dev.GetBITErrs( cBE );
	if (!(cBE.IsClear())) AddLibertyErr("Setup (Cnx):");

		
	// Enable Sensors
	// First, enable all sensors to see what's available
	// Later, this may be changed with the activeSensors property
	maxSensors = Dev.MaxSensors();
	sensorIndex    = new int[maxSensors];
	activeSensors  = new double[maxSensors];
	if( !Dev.EnableSensor(PDI_ALL_SENSORS,TRUE) )  { AddLibertyErr("Setup (Enable)"); }
	// Put values in activeSensors
	GetStationMap();
	// These values are the "availableSensors"
	availableSensors  = new double[maxSensors];
	for(i=0;i<maxSensors;i++) availableSensors[i]=activeSensors[i];


	// Setup Data Transfer
	lFrameSize=0;      // Bytes per Frame
	lFrameDoubles=0;   // "Double-sized" items per Frame per Sensor

	DatList.Empty();                       lFrameSize +=8;  // Frames have a 1 byte header(??)
	DatList.Append(PDI_MODATA_TIMESTAMP);  lFrameSize +=4;   lFrameDoubles +=1;
	DatList.Append(PDI_MODATA_POS);        lFrameSize +=12;  lFrameDoubles +=3;
	DatList.Append(PDI_MODATA_ORI);        lFrameSize +=12;  lFrameDoubles +=3;
	DatList.Append(PDI_MODATA_DISTLEV);    lFrameSize +=4;	 lFrameDoubles +=1;
	DatList.Append(PDI_MODATA_EXTSYNC);    lFrameSize +=4;	 lFrameDoubles +=1;

	if( !Dev.SetSDataList(PDI_ALL_SENSORS,DatList) ) { AddLibertyErr("Setup (Set List)"); }


	// Query Order of Data
    frameItems = DatList.NumItems();
	frameList  = new int[frameItems];
	for (int j=0; j<frameItems; j++)  frameList[j] = DatList.ItemAt(j);
	
	// Buffer Duration
	if(buftime<=0) lBufferTime=LIBERTY_DEF_TBUFFER_TIME;
	else lBufferTime=(int)buftime;

	// Veloctiy Regression
	regPredTime =  predtime;

	// Set Default filters
	posFilter = CPDIfilter(PDI_FLT_OFF, PDI_FLT_DEF_LOW, PDI_FLT_DEF_HIGH, PDI_FLT_DEF_MAXT);
	attFilter = posFilter;
	if( !Dev.SetPosFilter(posFilter) )  { AddLibertyErr("Setup (PosFilter)"); }
	if( !Dev.SetAttFilter(attFilter) )  { AddLibertyErr("Setup (AttFilter)"); }

	
	syncEnabled = FALSE;
	if( !Dev.SetSyncEnabled(syncEnabled) ) AddLibertyErr("Setup (Synch):");


	// Create Data Structures
	ManageDataStructures(1);

	started = 1;

	return S_OK;
}


/////////////////////////
// flag = 0 : delete all
// flag = 1 : setup all
//
// The setup (1) code will not check to make sure that buffers are
// currently deallocated.  Therefore, code that calls this function should
// check or else there is a potential for memory leaks.
void CLiberty::ManageDataStructures(int flag)
{
	int i,j;

	switch (flag)
	{
	case 0: // DELETE

		// LIBERTY BUFFER
		if (lBuffer != NULL) delete lBuffer;


		// VELOCITY REGRESSION BUFFERS
		if (regBuffer != NULL){ 
			free_matrix(regPolyT,1,regPts,1,LIBERTY_REGRESSION_ORDER+1);
			for (i=0;i<nSensors;i++) {	
				delete regT[i];
				delete regW[i];
				delete regOut[i];
				
				for (j=0;j<6;j++) delete  regBuffer[i][j];
				delete regBuffer[i];
			}
			delete regT;   delete regW;   
			delete regOut; delete regBuffer;
		}
		break;
		
		// LATEST
		if (latest != NULL) {
			for (i=0;i<nSensors;i++) {
				if (latest[i] != NULL) delete latest[i];
			}
			delete latest;
		}
		if( latestDist != NULL)  delete latestDist;
		if( latestErr != NULL)  delete latestErr;
		
	case 1:  // CREATE

		// LIBERTY BUFFER
		// Buffer for Raw Liberty Data
		lBufferFrames = lBufferTime*LIBERTY_FRAME_RATE;
		lBufferSize = nSensors*lFrameSize*lBufferFrames ;  // Total buffer size in bytes
		lBuffer = new unsigned char[lBufferSize];

		if( !Dev.SetPnoBuffer(lBuffer, lBufferSize ) )  { AddLibertyErr("ManageData(Buffer)"); }


		// VELOCITY REGRESSION BUFFERS
		regPts = (int)ceil(LIBERTY_FRAME_RATE*LIBERTY_REGRESSION_WINDOW)+1;
		
		regBuffer=new float**[nSensors];  regT=new float*[nSensors];
		regW=new float*[nSensors];        regOut=new int*[nSensors];
		for (i=0;i<nSensors;i++) {	
			// Note that NR matrices go [1,N] 
			regT[i]   = new float[regPts];			  // Sample Time
			regW[i]   = new float[regPts];			  // Distortion dependent weight
			regOut[i] = new int [regPts];			  // Outlier Flag

			regBuffer[i]=new float*[6];
			for(j=0;j<6;j++) regBuffer[i][j] = new float[regPts];     // DEP VAR:    Pos_k or Ori_k
		}
		// Use numrec 1-based data structure
		regPolyT = matrix(1,regPts,1,LIBERTY_REGRESSION_ORDER+1);	 // INDEP VAR:  [1 t t^2 ..]


		// LATEST
		latest = new double*[nSensors];
		for (i=0;i<nSensors;i++)  latest[i] = new double[L_DOUBLES];
		latestDist = new int[nSensors];
		latestErr  = new int[nSensors];

		break;
	}
}


//////////////////////////////////////////////////////////
/////  STATION MAP
//
// The "Station Map" is the list of sensors that are being used

void CLiberty::GetStationMap()
{
	DWORD w, wMap;
	int   i;

	if( !Dev.GetStationMap(wMap) )  { AddLibertyErr("GetStationMap"); }
	for(w=1,i=0,nSensors=0; i<maxSensors; i++,w<<=1) {
		if(w&wMap){	 activeSensors[i]=1;  sensorIndex[i]=nSensors++; }
		else      {	 activeSensors[i]=0;  sensorIndex[i]=-1; }
	}
}

void CLiberty::SetStationMap()
{
	DWORD w, wMap;
	int   i,activeflag;


	// TURN STUFF OFF AND RELEASE MEMORY BEFORE CHANGING STATION MAP
	// note that ManageDataStructures(0) needs to know the OLD nMarkers, so it 
	// must come before GetStationMap()
	if(buffering) { stopBuffer(); AddErr("SetStationMap:","Stopped buffer"); }
	if(active) { put_active(0); activeflag=1; } else activeflag=0;
	ManageDataStructures(0); // Reset Data Structures


	// SEND NEW MAP to LIBERTY
	for(wMap=i=0,w=1; i<maxSensors; i++,w<<=1)
		if(activeSensors[i]==1)  wMap+=w;
	if( !Dev.GetStationMap(wMap) )  { AddLibertyErr("GetStationMap"); }
	// Now Get map from Liberty ... thus if Liberty can't 
	// acheive the values in activeSensors, that array will
	// still reflect the true values
	GetStationMap();


	// CREATE DATA STRUCTURES AND TURN STUFF BACK ON
	ManageDataStructures(1); // Reset Data Structures
	if(activeflag) put_active(1.);
}

///////////////////////
///// Sensor Properties
STDMETHODIMP CLiberty::put_activeSensors(VARIANT newVal)
{
	int i;

	if(activeSensors==NULL){
		AddErr("ActiveSensors: System not started (Setup)", "");
		return MAKE_HRESULT(1,FACILITY_ITF,CONNECT_E_CANNOTCONNECT);
	}		

	// Convert Vector
	double *x;
	int n, changed;
	
	VariantToArray(&n,&x,&newVal);
	for(changed=i=0; i < ((n<maxSensors)?n:maxSensors); i++)
		if(	activeSensors[i]!=(int)x[i] ){	
			activeSensors[i]=(int)x[i]; changed=1;
		}	
	delete x;

	// Set Station Map
	if(changed) SetStationMap();

	return S_OK;
}

STDMETHODIMP CLiberty::get_activeSensors(VARIANT *pVal)
{

	if(activeSensors==NULL){
		double tmp[4] = {0., 0., 0., 0.};	
		VariantFromArray(4,tmp,pVal);
		AddErr("getActiveSensors: get called before system setup", "");
	}		
	else VariantFromArray(maxSensors,activeSensors,pVal);
	return S_OK;
}

STDMETHODIMP CLiberty::get_availableSensors(VARIANT *pVal)
{
	if(availableSensors==NULL){
		double tmp[4] = {0., 0., 0., 0.};	
		VariantFromArray(4,tmp,pVal);
		AddErr("getAvailableSensors: get called before system setup", "");
	}		
	else VariantFromArray(maxSensors,availableSensors,pVal);
	return S_OK;
}



////////////////////////////////////////////////////////////////////
////  ACTIVE 
//  Whether continuous data collection is occuring (ContPno)

STDMETHODIMP CLiberty::get_active(double *pVal)
{
	*pVal=active;
	return S_OK;
}

STDMETHODIMP CLiberty::put_active(double newVal)
{
	unsigned char *lPtr;

	// In the Liberty Server, "Active" will refer to the 
	// state of the continuous data collection:
	//    active==1  : collection on
	//    active==0  : collectoin off
	if(started){
		if(!active && newVal)
		{
			int i,j;

			active=1;

			// Prepare/Reset Regression Buffer
			// regOut signals outliers in the regression data buffer
			// since these are not used in the regression, if we set
			// them to 1 at the start, we won't regress with junk
			for(i=0;i<nSensors;i++) {
				for(j=0;j<regPts;j++) { regOut[i][j]=1; regW[i][j]=0.; }
			}
			
			if( !Dev.ResetPnoPtr() )        { AddLibertyErr("Active (Reset Ptr)"); }
			if( !Dev.StartContPno( NULL ) ) { AddLibertyErr("Active (Start)"); }
			Sleep(200);

			// SET the timeOffset
			// Wait until at least one frame has been collected
			if( (lPtr=WaitNextFrame(lBuffer)) == NULL ){ 
				AddLibertyErr("startActive (WaitForFrame)");
				return S_OK;
			}

			// Liberty Buffer bookeeping
			frameCount=0;
			timeOffsetFrame = 0;  // always start at lBuffer
			timeOffset = GetFrameTime(timeOffsetFrame);
			lBufferPrevLatestFrame = -1;  // reset for Update
			regIdx = -1;                  // reset for Update
			buffering = 0;                // resetting Liberty buffer screws with 
			bufferWaiting = 0;            //  buffer bookkeeping, so abort any pending buffering

		}
		else if(active && !newVal)
		{
			active=0;
			buffering=0;
			if( !Dev.StopContPno() ) { AddLibertyErr("Active (Stop)"); }
		}
	}
	return S_OK;
}


////////////////////////////////////////////////////////////////////
////  LATEST

//
//    tBuffer = [ t , [p1:3], [o1:3], [distortion] ]
//    latest  = [ t , [p1:3], [o1:3], [pv1:3], [ov1:3], [ppred1:3], [opred1:3], [distortion] [error] ]
//                0     1:3     4:6     7:9     10:12     13:15       16:18        19          20
//  If p/o is an outlier, then p/o is replaced with predicted values (ppred/opred)
//  If the p/o regression fails, then pv/ov and ppred/opred are filled with ERROR_VALUE


// LATEST:  Return the most recently received datapoint and velocity
STDMETHODIMP CLiberty::get_latest(VARIANT *pVal)
{
	int i,j,k, n[2] = {nSensors, L_DOUBLES};
	int err = 0;
	double t, t0, vel[6], xfit[6], xpred[6];

	///////////////////// ERROR CHECKING AND UPDATING BUFFERS
	// Error if Not Active
	if (!active) {  AddErr("getLatest: Liberty not yet active", ""); err = 1; }

	// Transfer Data From lBuffer to regBuffer
	if( UpdateRegBuffers()<0) err=1;     // This is error flag

	if(err){
		double tmp=ERROR_VALUE;	
		VariantFromArray(1,&tmp,pVal);
		return S_OK;
	}
	//////////////////////////////////////////////////////

	// Time and Distortion come directly from tBuffer
	for(i=0; i<nSensors; i++){
		latest[i][L_ID_TIME] = regT[i][regIdx];  // Time
		latest[i][L_ID_DIST] = latestDist[i];    // Distortion
		latest[i][L_ID_ERR]  = latestErr[i];     // Distortion
	}

	
	// Regression estimates of velocity and predicted position
	for(i=0;i<nSensors;i++){

		// POSITION & ORIENTATION
		for(j=0;j<3;j++){
			latest[i][L_ID_POS+j] = regBuffer[i][j][regIdx];
			latest[i][L_ID_ORI+j] = regBuffer[i][j+3][regIdx];
		}
		
		// PREPARE INDEP VARIABLE (polynomial in time)
		t0=regT[i][regIdx];   
		for(j=0; j<regPts; j++){
			// regT:    sensor(i) x frame(j)    - 0-base
			// regPoly: frame(j)  x t_order(k)  - 1-base
			t = regT[i][j]-t0;
			regPolyT[j+1][1] = 1;
			for(k=2;k<=LIBERTY_REGRESSION_ORDER+1;k++) 
				regPolyT[j+1][k] = regPolyT[j+1][k-1]*(float)t;
		}
		
		// PERFORM REGRESSION AND STORE RESULTS
		if( RegressData(i,vel,xfit,xpred,0) ){  // Error in Regression
			for(j=0;j<3;j++){
				// VELOCITY
				latest[i][L_ID_POSV+j] = ERROR_VALUE;
				latest[i][L_ID_ORIV+j] = ERROR_VALUE;
				// PREDICTIONS
				latest[i][L_ID_POSP+j] = ERROR_VALUE;
				latest[i][L_ID_ORIP+j] = ERROR_VALUE;
			}
		}
		else{                                   // Regression OK
			for(j=0;j<3;j++){
				// VELOCITY
				latest[i][L_ID_POSV+j] = vel[j];
				latest[i][L_ID_ORIV+j] = vel[j+3];
				// PREDICTIONS
				latest[i][L_ID_POSP+j] = xpred[j];
				latest[i][L_ID_ORIP+j] = xpred[j+3];
				// POSITION & ORIENTATION
				// If this datapoint is an outlier, then
				// replace it with the regression-fit position
				if(regOut[i][regIdx]){
					latest[i][L_ID_POS+j] = xfit[j];
					latest[i][L_ID_ORI+j] = xfit[j+3];
				}
			}
		}
	}

	VariantFromArray2(n,latest,pVal);

	return S_OK;
}

////////////////////////////////////////////////////////////////////
////  VELOCITY ESTIMATION

int CLiberty::RegressData(int sensor, double *vel, double *xfit, double *xpred, int recursion)
{
	double err,fit,t;
	int count,f,d,o;  // frame var order
	BOOL outFlag;
	static float **params=NULL;

	if(params==NULL){ 
		params = new float*[6];
		for(d=0;d<6;d++) params[d] = vector(1,LIBERTY_REGRESSION_ORDER+1);
	}

	
	// Count Non-Outliers
	for(count=0,f=0;f<regPts;f++) {
		if(!regOut[sensor][f]) count++;
	}

	if(count<5) return 1; // Require at least 5 datapoints (say) to regress 3 parameters

	// Do Weighted Regression
	for(d=0;d<6;d++){
		// Offset regBuffer and regW to make them 1-based vectors
		regress(params[d],regPolyT,regBuffer[sensor][d]-1,regW[sensor]-1,regPts,LIBERTY_REGRESSION_ORDER+1);  
		xfit[d]  = params[d][1];
		vel[d]   = params[d][2];
		for(xpred[d]=0., t=o=1; o<=LIBERTY_REGRESSION_ORDER+1;  o++ , t*=regPredTime)
			xpred[d] += params[d][o]*t;
	}
	
	// Check for Outliers
	// If a datapoint is too far from a regression prediction, then
	// it is labelled an outlier and the weight is set to 0.
	// Once a point is labelled an outlier, it will remain so until
	// it is outside the regression window.
	if(recursion<LIBERTY_REGRESSION_RECURSIONS){
		for(outFlag=0,f=0;f<regPts;f++){
			if(!regOut[sensor][f]){
				// Just consider position variables
				for(err=0.,d=0; d<3; d++){
					for(fit=0,o=1; o<=LIBERTY_REGRESSION_ORDER+1; o++)  {
						fit += params[d][o]*regPolyT[f+1][o];
					}
					err += (fit - regBuffer[sensor][d][f]) * (fit - regBuffer[sensor][d][f]);
				}
				if( sqrt(err)>LIBERTY_REGRESSION_OUTLIER_WINDOW) { 
					regOut[sensor][f] = 1; 
					regW[sensor][f]   = 0; 
					outFlag=1; 
				}
			}
		}
		if(outFlag) return RegressData(sensor,vel,xfit,xpred,recursion+1);
	}
	
	
	return 0;
}

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////
//// Load Raw Data into Reg Buffer

int CLiberty::UpdateRegBuffers()
{
	int lF0,newFrames,lFrame;
	int f,i,j,hsensor,sidx;
	int nF, fsize;
	unsigned char *lPtr;
	unsigned char herr;
	int distortion,sync;
	DWORD lSize;
	
	
	///////////// BOOKKEEPING
	// Which frames need to be loaded into regBuffer?
	// lF0    - frame number of first lBuffer frame to be loaded
	// nF     - number of frames to be loaded
	// regIdx - index in regBuffer (frame number) for the NEXT frame to be loaded

	// Get Current Pointer
	if( !Dev.LastPnoPtr(lPtr,lSize) ){
		AddLibertyErr("Update (LastPnoPtr)");
		return -1;
	}
	lBufferLatestFrame = (lPtr-lBuffer)/(nSensors*lFrameSize);

	newFrames = mod(lBufferLatestFrame-lBufferPrevLatestFrame,lBufferFrames);
	if(newFrames>=regPts ){
		// Case: you haven't been here in a while, so refill regBuffer
		regIdx=-1;  lF0=mod(lBufferLatestFrame-regPts+1,lBufferFrames);  nF=regPts;
	}
	else{
		// Case: were here recently, so only load the data that have not yet
		//   been loaded; regIdx is already correct
		lF0=lBufferPrevLatestFrame+1;  nF=newFrames;
	}
	
	lBufferPrevLatestFrame = lBufferLatestFrame;
	
	// DATA CONVERSION
	// Convert Data and place into regBuffer and associated data structures
	
	
	for (f=0; f<nF; f++){
		lFrame = mod(lF0+f,lBufferFrames);
		lPtr = lBuffer + nSensors*lFrameSize*lFrame;
		regIdx=mod(regIdx+1,regPts);
		
		// N.B.: Buffer is always a multiple of nSensor frames, so 
		// you don't have to worry below about looping back
		for (i=0; i<nSensors; i++){  
			
			// Header
			if(lPtr[0]!='L' || lPtr[1]!='Y'){
				// Frame alignement error!
				AddErr("Frame Alignment Error", "");
				// Mark whole frame as error and continue
				for(j=0; j<nSensors; j++){
					regW[j][regIdx]=0;	
					regOut[j][regIdx]=1;	
				}
				break;  // Break from i-loop and move on to next frame
			}
			
			hsensor = lPtr[2];
			herr   = lPtr[4];
			// report error
			if(herr!=' '){
				char str[LIBERTY_ERR_STRLEN];
				sprintf(str,"sensor %d, error %d",sidx,(int)herr);
				AddErr("Header Error Code", str);
			} else herr=0;
			
			// sensor id
			sidx = sensorIndex[hsensor-1];
			if(sidx<0){
				char str[LIBERTY_ERR_STRLEN];
				sprintf(str,"sensor %d",sidx);
				AddErr("Header Reported Invalid Sensor: ", str);
				// Don't know which sensor is a problem, so just
				// mark whole frame as error and continue
				for(j=0; j<nSensors; j++){
					regW[j][regIdx]=0;	
					regOut[j][regIdx]=1;	
				}
				break;  // Break from i-loop and move on to next frame
			}
			
			fsize = lPtr[6];  // Body Size
			
			if( fsize!=(lFrameSize-8) ){
				char str[LIBERTY_ERR_STRLEN];
				sprintf(str," %d / %d",fsize+8,(int)lFrameSize);
				AddErr("UpdateRegBuffers: unexpected frame size",str);
			}
			

			// Body
			lPtr += 8;
			for (j=0; j<frameItems; j++)
			{
				switch (frameList[j]) {
				case PDI_MODATA_TIMESTAMP:
					regT[sidx][regIdx] = ((*(int *)lPtr)-timeOffset)/1000.0;  lPtr+=4;  // time in ms
					break;
				case PDI_MODATA_POS:
					regBuffer[sidx][0][regIdx] = (*(float *)lPtr)*25.4;  lPtr+=4;
					regBuffer[sidx][1][regIdx] = (*(float *)lPtr)*25.4;  lPtr+=4;
					regBuffer[sidx][2][regIdx] = (*(float *)lPtr)*25.4;  lPtr+=4;
					break;
				case PDI_MODATA_ORI:
					regBuffer[sidx][3][regIdx] = *(float *)lPtr;   lPtr+=4;
					regBuffer[sidx][4][regIdx] = *(float *)lPtr;   lPtr+=4;
					regBuffer[sidx][5][regIdx] = *(float *)lPtr;   lPtr+=4;
					break;
				case PDI_MODATA_DISTLEV:
					distortion = *(int *)lPtr;  lPtr+=4;
					regW[sidx][regIdx] = 1; // For now, don't weight by distortion
					break;
				case PDI_MODATA_EXTSYNC:
					sync = *(int *)lPtr;  lPtr+=4;
					break;
				default:
					break;
				}
			}
			
			// Other frame information
			regOut[sidx][regIdx] = 0;  // Frames are assumed to be good until regression
			
			if( f==(nF-1) ){
				latestDist[sidx] = distortion;
				latestErr[sidx]  = herr;
			}
		} // for i (sensor)

		// If trying to stop buffering, then we're looking for any frame with EXYSYNC set low
		if(bufferStopRequest && !sync){
			// Called stop buffer, and have just received 
			// a frame with the external sync set to 0
			bufferStopRequest=0;
			lBufferStopFrame = lFrame;
		}
	
	} // for f (frame)

	return nF;
	
}

///////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//// Bookkeeping Utils

///////////////////////////////////////////
//// Load Raw Data into Reg Buffer
double CLiberty::GetFrameTime(long frame)
{
	int j;
	unsigned char *fptr;
	double time;
	
	fptr = lBuffer + (frame*nSensors*lFrameSize) + 8;  // 8 is for header
	
	// TIME OFFSET
	for (j=0; j<frameItems; j++) {
		switch (frameList[j]) {
		case PDI_MODATA_TIMESTAMP:
			time = *((int*)fptr);
			return time;
		case PDI_MODATA_POS:
		case PDI_MODATA_ORI:
			fptr += 3*sizeof(float);
			break;
		case PDI_MODATA_DISTLEV:
		case PDI_MODATA_EXTSYNC:
			fptr+=sizeof(DWORD);
			break;
		default:
			break;
		}
	}
	return 0;  // Shouldn't get here!
}


///////////////////////////////////////////
// WAIT for a FRAME and then return the PTR to it
// Useful for start/stop issues

unsigned char * CLiberty::WaitNextFrame(unsigned char *lPtrOld)
{
	unsigned char *lPtr;
	DWORD lSize;

	// Wait until LastPnoPtr moves beyong lPtrOld
	// If the argument is NULL, then set it to current pointer
	if( lPtrOld==NULL ){
		if( !Dev.LastPnoPtr(lPtrOld,lSize) ) return NULL;
	}

	lPtr=lPtrOld;
	while( lPtr==lPtrOld ){
		if( !Dev.LastPnoPtr(lPtr,lSize) ) return NULL;
	}
	return lPtr;
}


///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
//  BUFFERING

STDMETHODIMP CLiberty::startBuffer()
{
	// Error if Not Active
	if(!buffering){
		if(!active) put_active(1);

		// Get last frame location, which should have EXTSYNC flag set low
		UpdateRegBuffers();
		lBufferStartFrame = lBufferLatestFrame;
		
		// Start blipping frame TTL pulse (SyncEnable)
		// This will allow external device to monitor times of buffered data
		syncEnabled = TRUE;
		Dev.SetSyncEnabled(syncEnabled);
		// command above will generate error if PnoCont is on (i.e. active=1)
		// "Z : Command sent in Cont mode, no response collected"
		// but seems to work ok anyway
		// if( !Dev.SetSyncEnabled(syncEnabled) ) AddLibertyErr("Start Buffer (Synch):");

		// Set Flags
		buffering = 1;
		bufferWaiting = 0;
	}

	return S_OK;
}


STDMETHODIMP CLiberty::stopBuffer()
{
	int i,nF;

	if(buffering){

		// Stop blipping frame TTL pulse (SyncEnable)
		syncEnabled = FALSE;
		Dev.SetSyncEnabled(syncEnabled);
		// will generate error: 
		// "Z : Command sent in Cont mode, no response collected"
		// but seems to work ok
		// if( !Dev.SetSyncEnabled(syncEnabled) ) AddLibertyErr("Stop Buffer (Synch):");

		// Wait until you collect a frame with the ExtSync flag low
		int UPDATE_ATTEMPTS = 20;  
		int UPDATE_DELAY    = 20; // msec
		for(bufferStopRequest=1, i=nF=0; i<UPDATE_ATTEMPTS && bufferStopRequest; i++){
			Sleep(UPDATE_DELAY);
			nF=nF+UpdateRegBuffers();
		}
		if( bufferStopRequest ) {
			char str[LIBERTY_ERR_STRLEN];
			sprintf(str,"%d Frames collected",nF);  
			AddErr("stopBuffer: Didn't catch a Liberty frame with ExtSync off. Buffering length will not match Sync Count.", str);
			lBufferStopFrame = lBufferLatestFrame;
		}

		buffering = 0;
		bufferWaiting = 1;
	}
	return S_OK;
}

STDMETHODIMP CLiberty::getBuffer(int sensor, VARIANT *pVal)
{
	// do an updateRegbuffer until stop is set??!?!

	if (buffering) {
		stopBuffer();
		AddErr("getBuffer: Requested a running buffer, buffering stopped", "");
	}
	if (!bufferWaiting ) {
		AddErr("getBuffer: No buffer waiting", "");
		return S_OK;
	}
	
	if ( sensor>nSensors || sensor<=0) {
		AddErr("getBuffer: Requested invalid sensor id", "");
		return MAKE_HRESULT(1,FACILITY_ITF,CONNECT_E_CANNOTCONNECT);
	}
			

	LoadBufferVariant(sensor,pVal);

	return S_OK;
}


///////////////////////////////////////////
//// Load Raw Data into Reg Buffer

void CLiberty::LoadBufferVariant(int sensor, VARIANT *pVal)
{
	int f,i,j,hsensor;
	int nF, fsize, fidx, sidx;
	int frameCt, *sync;     // how many frames have syncs frames with SYNCs
	unsigned char *lPtr;
	unsigned char herr;

	SAFEARRAY *psa;
    SAFEARRAYBOUND *sabnd = new SAFEARRAYBOUND[2];
	double *sap;

	///////////// OVERFLOW
	if( GetFrameTime(timeOffsetFrame) != timeOffset ){
		lBufferStartFrame = mod(lBufferStopFrame+1,lBufferFrames);

		char str[LIBERTY_ERR_STRLEN];
		sprintf(str," %.1f sec for a %.1f sec buffer.",  
			GetFrameTime(lBufferStopFrame) - timeOffset, lBufferTime );
		AddErr("buffer overflow: ", str);
	}

	nF = mod( lBufferStopFrame-lBufferStartFrame+1, lBufferFrames );
	sync = new int[nF];
	
	// Count Frames with SYNC
	// Only look at first SENSOR, since should be same for all
	// This has to be done first in order to allocate SafeArray properly
	frameCt=0;
	for (f=0; f<nF; f++){
		lPtr = lBuffer + nSensors*lFrameSize*mod(lBufferStartFrame+f,lBufferFrames) + 8;
		for (fidx=j=0; j<frameItems; j++)
		{
			switch (frameList[j]) {
			case PDI_MODATA_POS:
			case PDI_MODATA_ORI:
				lPtr += 12;
				break;
			case PDI_MODATA_TIMESTAMP:
			case PDI_MODATA_DISTLEV:
				lPtr += 4;
				break;
			case PDI_MODATA_EXTSYNC:
				sync[f] = *(int *)lPtr;
				j=frameItems; // Done with this frame
				break;
			default:
				break;
			}
		}
		if(sync[f])	frameCt++;
	}

	
	////// Construct the SafeArray and bounds
	sabnd[0].cElements=frameCt;     sabnd[0].lLbound=0;
	sabnd[1].cElements=B_DOUBLES;   sabnd[1].lLbound=0;
	psa = SafeArrayCreate(VT_R8,2,sabnd);            // Create the safearrays
	SafeArrayAccessData(psa, (void**)&(sap));	 // Access data pts



	// Fill Data 
	for (sidx=f=0; f<nF; f++){
		// Only return frames with SYNCs
		if(!sync[f]) continue; 
		
		lPtr = lBuffer + nSensors*lFrameSize*mod(lBufferStartFrame+f,lBufferFrames);

		// N.B.: Buffer is always a multiple of nSensor frames, so 
		// you don't have to worry below about looping back
		for (i=0; i<nSensors; i++, lPtr+=lFrameSize){  

			///////////// Header
			if(lPtr[0]!='L' || lPtr[1]!='Y'){
				// Frame alignement error!
				AddErr("Buffer Frame Alignment Error!!!", "");
				continue;  // Break from i-loop and move on to next frame
			}

			// sensor id -- collect data from one sensor only
			// THIS IS CONFUSING!@!!
			// "sensor" is sensor requested by user, 1:nSenors
			// "hsensor" is sensor id'd by Liberty, 1:maxSensors
			// sensorIndex maps avail to active, but uses BASE 0!!!!
			hsensor = lPtr[2];
			if( sensor-1 != sensorIndex[hsensor-1] ) continue;

			// error
			herr = lPtr[4];
			if(herr==' ') herr=0;
			sap[B_ID_ERR*frameCt+sidx] = herr;
			
			// body size
			fsize = lPtr[6];  

			if( fsize!=(lFrameSize-8) ){
				char str[LIBERTY_ERR_STRLEN];
				sprintf(str," %d / %d",fsize+8,(int)lFrameSize);
				AddErr("LoadBufferVariant: unexpected frame size",str);
			}

			///////////////// Body
			lPtr+=8;
			for (fidx=j=0; j<frameItems; j++)
			{
				switch (frameList[j]) {
				case PDI_MODATA_TIMESTAMP:
					sap[B_ID_TIME*nF+sidx] = ((*(int *)lPtr)-timeOffset)/1000.0; lPtr+=4;  // time in ms
					break;
				case PDI_MODATA_POS:
					sap[(B_ID_POS  )*frameCt+sidx] = (*(float *)lPtr)*25.4;  lPtr+=4;
					sap[(B_ID_POS+1)*frameCt+sidx] = (*(float *)lPtr)*25.4;  lPtr+=4;
					sap[(B_ID_POS+2)*frameCt+sidx] = (*(float *)lPtr)*25.4;  lPtr+=4;
					break;
				case PDI_MODATA_ORI:
					sap[(B_ID_ORI  )*frameCt+sidx] = *(float *)lPtr; lPtr+=4; 
					sap[(B_ID_ORI+1)*frameCt+sidx] = *(float *)lPtr; lPtr+=4; 
					sap[(B_ID_ORI+2)*frameCt+sidx] = *(float *)lPtr; lPtr+=4; 
					break;
				case PDI_MODATA_DISTLEV:
					sap[B_ID_DIST*frameCt+sidx]    = *(int *)lPtr; lPtr+=4;
					break;
				case PDI_MODATA_EXTSYNC:
					lPtr+=4;
					break;
				default:
					break;
				}
			}
		} // for i
		sidx++;  // increment sap index
	} // for f
	delete sync;

	// Construct the Variant
	SafeArrayUnaccessData(psa);	// Unaccess
	VariantInit(pVal);			// Initialize the Variant
	pVal->vt = VT_ARRAY|VT_R8;	// Tell it to hold an array of doubles
	pVal->parray = psa;

}


///////////////////////////////////////////////////////////////////////
//  FILTERING
//
// Parameter settings for on-board Liberty position and 
// attitude (orientation) filters

STDMETHODIMP CLiberty::get_posFilter(VARIANT *pVal)
{
	double params[4];
	params[0] = posFilter.m_fSensitivity;
	params[1] = posFilter.m_fLowValue;
	params[2] = posFilter.m_fHighValue;
	params[3] = posFilter.m_fMaxTransRate;
	VariantFromArray(4,params,pVal);
	return S_OK;
}

STDMETHODIMP CLiberty::put_posFilter(VARIANT newVal)
{
	double *params;
	int n;

	if(active){
		AddErr("putPosFilter: filter vector must be length 4, [Sensitivity, Low, High, MaxTransRate]", "");

	}

	VariantToArray(&n,&params,&newVal);
	if(n<4) {
		AddErr("putPosFilter: filter vector must be length 4, [Sensitivity, Low, High, MaxTransRate]", "");
		return MAKE_HRESULT(1,FACILITY_ITF,CONNECT_E_CANNOTCONNECT);
	}
	posFilter = CPDIfilter((float)params[0],(float)params[1],(float)params[2],(float)params[3]);	
	delete params;

	if( !Dev.SetPosFilter(posFilter) ) { AddLibertyErr("putPosFilter:"); }
	return S_OK;
}

STDMETHODIMP CLiberty::get_attFilter(VARIANT *pVal)
{
	double params[4];
	params[0] = attFilter.m_fSensitivity;
	params[1] = attFilter.m_fLowValue;
	params[2] = attFilter.m_fHighValue;
	params[3] = attFilter.m_fMaxTransRate;
	VariantFromArray(4,params,pVal);
	return S_OK;
}

STDMETHODIMP CLiberty::put_attFilter(VARIANT newVal)
{
	double *params;
	int n;
	VariantToArray(&n,&params,&newVal);
	if(n<4) {
		AddErr("putAttFilter: filter vector must be length 4, [Sensitivity, Low, High, MaxTransRate]", "");
		return MAKE_HRESULT(1,FACILITY_ITF,CONNECT_E_CANNOTCONNECT);
	}
	attFilter = CPDIfilter((float)params[0],(float)params[1],(float)params[2],(float)params[3]);	
	delete params;

	if( !Dev.SetAttFilter(attFilter) ) { AddLibertyErr("putAttFilter:"); }
	return S_OK;
}



///////////////////////////////////////////////////////////////////////
//  ERROR REPORTING

//// Create a Popup Box
void CLiberty::ErrBox(char *str, LPCTSTR lstring){
	char estr[200];
	sprintf(estr,"%s (%s)\n", str, lstring);
	MessageBox(NULL, estr, "LibertyServer", MB_OK | MB_ICONEXCLAMATION);
}

//// Add an Item to the Errors Array
void CLiberty::AddErr(char *str, LPCTSTR lstring){
	// No Room Left
	if(ErrorCount > LIBERTY_MAX_ERRORS-1) {
		ErrorCount++; return;
	} 

	// Create and Fill String
	Errors[ErrorCount] = new wchar_t[LIBERTY_ERR_STRLEN];
	if( ErrorCount == LIBERTY_MAX_ERRORS-1 )
		swprintf(Errors[ErrorCount],L"AddErr: Maximum Number of Error Strings Exceeded");
	else
		swprintf(Errors[ErrorCount],L"%S (%S)\n", str, lstring);
	ErrorCount++;
}


//// Add an Item to the Errors Array
void CLiberty::AddLibertyErr(char *str)
{	
	// Check for Error in Last Function
	if(Dev.GetLastResult()) AddErr(str, Dev.GetLastResultStr());
	
	// Check for BIT Errors
	CPDIbiterr cBE;
	Dev.GetBITErrs( cBE );
	if (!(cBE.IsClear()))
	{
		char bitstr[LIBERTY_ERR_STRLEN];
		cBE.Parse( bitstr, LIBERTY_ERR_STRLEN );
		AddErr(str,bitstr);
		Dev.ClearBITErrs();
	}
	
}
	

//// ERROR INTERFACES

STDMETHODIMP CLiberty::get_errCount(double *pVal)
{
	*pVal = ErrorCount;
	return S_OK;
}

STDMETHODIMP CLiberty::getErr(int i, BSTR *pVal)
{

	if(i>0 && i<=ErrorCount)   *pVal=SysAllocString(Errors[i-1]);
	else                       *pVal=SysAllocString(L"getErr: index out of range");
	return S_OK;
}

STDMETHODIMP CLiberty::clearErrs()
{
	int i;
	for(i=0;i<ErrorCount;i++) delete Errors[i];
	ErrorCount=0;
	return S_OK;
}



