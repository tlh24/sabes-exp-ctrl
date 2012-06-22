// Liberty.h : Declaration of the CLiberty

#ifndef __LIBERTY_H_
#define __LIBERTY_H_

#include "resource.h"       // main symbols
#include "PDI\PDI.h"

/////////////////////////////////////////////////////////////////////////////
// CLiberty
class ATL_NO_VTABLE CLiberty : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLiberty, &CLSID_Liberty>,
	public ISupportErrorInfo,
	public IDispatchImpl<ILiberty, &IID_ILiberty, &LIBID_LIBERTYSERVERLib>
{
public:
	CLiberty();
	~CLiberty();

DECLARE_REGISTRY_RESOURCEID(IDR_LIBERTY)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLiberty)
	COM_INTERFACE_ENTRY(ILiberty)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ILiberty
public:
	STDMETHOD(setup)(double time, double predtime);
	STDMETHOD(get_active)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_active)(/*[in]*/ double newVal);
	STDMETHOD(get_latest)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(stopBuffer)();
	STDMETHOD(startBuffer)();
	STDMETHOD(getBuffer)(int,VARIANT *pVal);
	STDMETHOD(get_activeSensors)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_activeSensors)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_availableSensors)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(get_attFilter)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_attFilter)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_posFilter)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_posFilter)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_errCount)(/*[out, retval]*/ double *pVal);
	STDMETHOD(getErr)(int i, BSTR *pVal);
	STDMETHOD(clearErrs)();

private:
	void ManageDataStructures(int flag);
	void GetStationMap();
	void SetStationMap();
	void ErrBox(char *, LPCTSTR);
	void AddErr(char *, LPCTSTR);
	void AddLibertyErr(char *);
	int  UpdateRegBuffers();
	int  RegressData(int, double *, double *, double *, int);
	unsigned char *WaitNextFrame(unsigned char *);
	double GetFrameTime(long frame);
	void LoadBufferVariant(int, VARIANT *);

	CPDIdev Dev;
	CPDImdat DatList;
	CPDIfilter posFilter, attFilter;

	int started;								// Flag: whether setup has been run 
	int active;									// Flag: whether continuous data collection is on or off
	int buffering, bufferWaiting;            	// Flags for state of trial buffer
	int bufferStopRequest; 						// Flags for state of trial buffer
 	BOOL syncEnabled;							// Flag for Liberty sync output

	int nSensors, maxSensors;
	double *activeSensors, *availableSensors;
	int *sensorIndex;

	int frameItems, *frameList;                 // Data Item Labels

	
	// lBuffer:  "Liberty Buffer" -- raw data buffer for Liberty raw data transfer
	long lBufferTime;              //  Time (sec) that lBuffer can hold
	long lBufferFrames;            //  Frames (samples-per-sensor) that lBuffer can hold
	long lBufferSize;              //  lBuffer Size in bytes
	int  lFrameDoubles;			   //  Number of "double-sized" items per frame per sensor
	int  lFrameSize;               //  Bytes per frame per sensor
	unsigned char *lBuffer;        //  Raw Buffer, data from liberty
	double timeOffset;             //  Time recorded at first frame
	long timeOffsetFrame;          //  Frame that serves as offset (i.e. 1st frame)
	long frameCount;               //  Total number of frames collected since timeOffsetFrame
	long lBufferLatestFrame;       //  Number of the last frame collected
	long lBufferPrevLatestFrame;   //  
	long lBufferStartFrame;        //  First frame of buffer collection
	long lBufferStopFrame;         //  Last frame of buffer collection (inclusive)



	// regBuffer:  "Regression Buffer" -- storage for velocity regression
	float ***regBuffer;            // Regression Indep Data ([pos ori])
	float **regT;                  // Regression Time Variable
	float **regW;                  // Regression Weights
	float **regPolyT;              // Regression Depdendent Data
	int  **regOut;                 // Regression Outlier Flags
	double regPredTime;            // Regression prediction time (sec)
	int regPts;                    // Number of frames used in Regression
	int regIdx;                    // Current frames index

	// latest:   buffer for DCOM data transfer
	int latestDoubles;             // Number of "double-size" items per latest-frame per sensor
	double **latest;               // Double Buffer, processed data
	int *latestDist;			   // temporary storage of Distortion data for latest
	int *latestErr;                // temporary storage of Error data for latest

	int ErrorCount;                // Number of error messages
	wchar_t **Errors;              // Error message buffer
};

#define LIBERTY_FRAME_RATE			   240		// Sample Rate
#define LIBERTY_DEF_TBUFFER_TIME	   600		// Seconds
#define LIBERTY_LBUFFER_FRAMES         100		// Sample Rate
#define LIBERTY_REGRESSION_WINDOW	   .05		// Seconds
#define LIBERTY_REGRESSION_ORDER	   2		// Polynomial Order of Pos vs Time regression
#define LIBERTY_REGRESSION_RECURSIONS  1		// Regression recursions allowed (to remove outliers)
#define LIBERTY_REGRESSION_OUTLIER_WINDOW 15    // Error in mm
#define LIBERTY_MAX_ERRORS			   1000		// How many error strings to store
#define LIBERTY_ERR_STRLEN             200      // Maximum string length for each error msg
#define ERROR_VALUE  (float)-3.0E28

#endif //__LIBERTY_H_
