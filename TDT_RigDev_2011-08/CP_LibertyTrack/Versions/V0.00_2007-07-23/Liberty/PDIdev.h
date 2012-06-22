/////////////////////////////////////////////////////////////////////
// Polhemus Inc.,  www.polhemus.com
// © 2003 Alken, Inc. dba Polhemus, All Rights Reserved
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
//
//  Filename:           $Workfile: PDIdev.h $
//
//  Project Name:       Polhemus Developer Interface  
//
//  Description:        Tracker Device Object Class
//
//  VSS $Header: /PIDevTools/Inc/PDIdev.h 25    7/27/05 10:40a Suzanne $  
//
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
#ifndef _PDIDEV_H_
#define _PDIDEV_H_

/////////////////////////////////////////////////////////////////////
class CPDImdat;
class CPDIser;
class CPiCmdIF;
class CPiError;

class CPDIfilter;

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
// CLASS CPDIdev
/////////////////////////////////////////////////////////////////////
class PDI_API CPDIdev 
{
public:
	CPDIdev( VOID );
	virtual ~CPDIdev( VOID );

	////////////////////////////////////
	// Connection Methods
	////////////////////////////////////
	BOOL		CnxReady	( VOID );	// Returns TRUE if Connection established
	ePiCommType CnxType		( VOID );	// Returns current connection type.
	ePiCommType	DiscoverCnx	( VOID );	// Search for USB, then Serial Connection to device
	BOOL		ConnectSer  ( VOID );   // Attempts to connect via current serial port parameters
	BOOL		ConnectUSB	( VOID );	// Attempts to connect via USB device
	BOOL		Disconnect	( VOID );	// Ends current connection

	// Serial Interface Parameters
	BOOL		SetSerialIF	( CPDIser * ); // Sets current serial port parameters locally: if no connection, does not configure device
	BOOL		GetSerialIF	( CPDIser * ); // Returns current serial port parameters locally: if no connection, does not configure device


	////////////////////////////////////
	// Configuration Methods
	////////////////////////////////////
	BOOL	GetAttFilter	( CPDIfilter & );	// Gets Attitude Filter ( 'Y' Command )
	BOOL	GetBinary		( BOOL & );			// Gets binary output mode( 'F' Command ) 
	BOOL	GetEcho			( BOOL & );			// Gets echo mode ( '^E' Command )
	BOOL	GetFrameRate	( ePiFrameRate & );	// Gets P&O Frame Rate ( 'R' Command )	
	BOOL	GetMetric		( BOOL & );			// Gets device to metric output ( 'U' Command )
	BOOL	GetPosFilter	( CPDIfilter & );	// Gets Position Filter ( 'X' Command )
	BOOL	GetStationMap	( DWORD & dwMap );	// Gets Active Station Map ( '^U' Command )
	BOOL	GetSourceFrame	( PDIori & );		// Gets Source Frame Rotation ( 'G' Command )
	BOOL	GetSyncEnabled  ( BOOL & );			// Gets Sync Enabled ( 'Z' Command )

	BOOL	SetAttFilter	( const CPDIfilter & );	// Sets Attitude Filter ( 'Y' Command )
	BOOL	SetBinary		( BOOL );				// Sets device to binary output ( 'F' Command ) 
	BOOL	SetEcho			( BOOL );				// Sets echo mode ( '^E' Command )
	BOOL	SetFrameRate	( const ePiFrameRate );	// Sets P&O Frame Rate ( 'R' Command )
	BOOL	SetMetric		( BOOL );				// Sets device to metric output ( 'U' Command )
	BOOL	SetPosFilter	( const CPDIfilter & );	// Sets Position Filter ( 'X' Command )
	BOOL	SetStationMap	( const DWORD & dwMap );// Sets Active Station Map ( '^U' Command )
	BOOL	SetSourceFrame	( const PDIori & );		// Sets Source Frame Rotation ( 'G' Command )
	BOOL	SetSyncEnabled  ( BOOL );				// Sets Sync Enabled ( 'Z' Command )

	// Per-sensor configuration Notes:
	//	: nSensor arguments are 1-based.
	//	: if (nSensor == -1), all sensors are configured

	BOOL	ClearSBoresight	( INT nSensor );				// UN-Boresight sensor ('^B' command )
	BOOL	EnableStation	( INT nStation, BOOL bEnable );	// Enables or disables station ( '^U' Command )

	BOOL	GetSDataList	( INT nStation, CPDImdat &   );	   // Gets motion data output list per sensor ( 'O' Command )
	BOOL	GetSAlignment	( INT nStation, PDI3vec & O, 
										    PDI3vec & X, 
										    PDI3vec & Y );	   // Gets Alignment Reference Frame per sensor ( 'A' Command )
	BOOL	GetSBoresight	( INT nStation, PDIori & );		   // Get boresight per sensor ( 'B' Command )
	BOOL	GetSHemisphere	( INT nStation, PDI3vec & );	   // Get Hemisphere Of Operation per sensor ( 'H' Command )
	BOOL	GetSHemiTrack	( INT nStation, BOOL & );		   // Query Hemisphere Tracking per sensor ('H' Command )
	BOOL	GetSStylusMode	( INT nStation, ePiStylusMode & ); // Get Stylus Mode per sensor ( 'L' Command )

	BOOL	ResetSAlignment ( INT nStation );				  // Reset Alignment per sensor ( '^R' Command )

	BOOL	SetSDataList	( INT nStation, const CPDImdat &   );		  // Sets motion data output list per sensor ( 'O' Command )
	BOOL	SetSAlignment	( INT nStation, const PDI3vec & O, 
		                                    const PDI3vec & X, 
										    const PDI3vec & Y );		   // Sets Alignment Reference Frame per sensor ( 'A' Command )
	BOOL	SetSBoresight	( INT nStation, const PDIori &, BOOL bReset ); // Set boresight per sensor ( 'B' Command )
	BOOL	SetSHemisphere	( INT nStation, const PDI3vec & );			   // Set Hemisphere Of Operation per sensor ( 'H' Command )
	BOOL	SetSHemiTrack	( INT nStation );							   // Enable Hemisphere Tracking per sensor ('H' Command )
	BOOL	SetSStylusMode	( INT nStation, ePiStylusMode );			   // Set Stylus Mode per sensor ( 'L' Command )
	
	////////////////////////////////////
	// Configuration management
	////////////////////////////////////
	BOOL	GetSavedLabels	( PDIlabels & );			// Gets currently saved configuration labels ( '^X' )
	BOOL	GetCfgLabel		( LPCSTR & );				// Gets current configuration label. ( '^X' )
	BOOL	GetStartupSlot	( ePiConfigSlot & eSlot );	// Gets current startup configuration slot number ('^W' )

	BOOL	SaveCfgToSlot	( const ePiConfigSlot & );  // Saves current configuration to slot ( '^K' )
	BOOL	SetCfgLabel		( const LPCSTR );			// Assigns label to current configuration ( '^X' )
	BOOL	SetStartupSlot	( const ePiConfigSlot & );	// Sets startup configuration slot number ('^W' )

	////////////////////////////////////
	//	Map management
	////////////////////////////////////
	BOOL	GetCompState	( INT & nMap );				   // Gets current compensation state ( 'D' )
	BOOL	GetSavedMaps	( PDIlabels &, INT & nCount ); // Gets currently saved map labels and count( '^D' )
	BOOL	SetCompState	( INT nMap );				   // Enables compensation, using the given map number, 0 disables ( 'D' )

	////////////////////////////////////
	// Runtime Methods
	////////////////////////////////////
	// P&O Buffer methods
	BOOL	ClearPnoBuffer	( VOID );						 // Clears output P&O output buffer
	BOOL	LastPnoPtr		( PBYTE & pBuf, DWORD & dwSize );// Returns pointer to last P&O frame collected
	BOOL	ResetPnoPtr		( VOID );						 // Resets P&O output pointer to beginning of buffer
	BOOL	SetPnoBuffer	( PBYTE pBuf, DWORD dwSize );	 // Sets/Clears output P&O output buffer
	BOOL	ResetHostFrameCount ( VOID );					 // Resets Host P&O frame counter
	BOOL	LastHostFrameCount  ( DWORD & dwFrameCount );    // Returns index of last P&O frame collected by the host

	// P&O Collection methods
	BOOL	ReadSinglePno	( HWND );						 // Reads single P&O frame. ('P' command): posts data msg to HWND
	BOOL	ReadSinglePnoBuf( PBYTE & pBuf, DWORD & dwSize );// Reads single P&O frame. ('P' command): returns pointer to frame
	BOOL	ResetFrameCount	( VOID );						 // Reset motion framecount ( 'Q' Command )
	BOOL	ResetTimeStamp	( VOID );						 // Reset motion frame timestamp ( 'T' Command )
	BOOL	StartContPno	( HWND );						 // Starts continuous P&O collection: posts data msg to HWND
	BOOL	StopContPno		( VOID );						 // Stops continuous P&O collection
	BOOL	StartStylusPno	( HWND );						 // Starts stylus-driven P&O collection: posts data msgs to HWND
	BOOL	StopStylusPno	( VOID );						 // Stops stylus-driven P&O collection

	BOOL	ResetTracker	( VOID );						 // Initializes Tracker, disconnects ( '^Y' Command )
	BOOL	TxtCmd	( LPCTSTR szCmd, DWORD & dwRspSize, LPCTSTR szRsp=0 );	// Sends generic text command to device
	BOOL	WhoAmI			( LPCSTR & );									// Issues tracker WhoAmI command ('^V' command ); puts result in argument 
	BOOL	WhoAmISensor	( INT nSensor,  LPCSTR & );						// Issues sensor WhoAmI command ( '^V' command ); puts result in argument 

	BOOL	GetBITErrs		( CPDIbiterr & );	// Read tracker BIT error data
	BOOL	ClearBITErrs	( VOID );			// Clears tracker BIT errors

	////////////////////////////////////
	// Other Methods
	////////////////////////////////////
	ePiErrCode	GetLastResult		( VOID );					// Returns numeric result of last operation
	ePiErrCode	GetLastResult		( ePiDevError & d );		// Returns numeric result of last operation, plus any device error code
	LPCTSTR		GetLastResultStr	( VOID );					// Returns const string result of last operation
	LPCTSTR		ResultStr			( ePiErrCode, ePiDevError );// Returns const string definition of enum result code
	INT 		MaxSensors			( VOID );					// Returns max number of sensors supported by device.
	ePiTrackerType TrackerType		( VOID );					// Returns tracker type.

	BOOL		GetDetectedStationMap ( DWORD & dwMap );		// Gets Detected Station Map

	////////////////////////////////////
	// Troubleshooting Methods
	////////////////////////////////////
	BOOL	Simulate	( BOOL );			// Puts object in/out of simulation mode, returns status
	PVOID	Trace		( BOOL, INT n=0 );	// Enables trace output to debug window (DEBUG build only)
	VOID	Log			( BOOL );			// Enables tracker I/O logging to file PICMDIF.LOG

	////////////////////////////////////
	// Pipe Export Methods
	////////////////////////////////////
	BOOL	StartPipeExport	( LPCTSTR szPipeName=PDI_EXPORT_PIPE_NAME );//Starts raw P&O export on named pipe
	BOOL	CancelPipeExport( VOID );									// Cancels raw P&O export on named pipe


	////////////////////////////////////
	// Legacy Methods
	////////////////////////////////////
	// Please avoid use of the following methods as they may be phased out in the future.
	BOOL	EnableSensor	( INT nSensor, BOOL bEnable )	// Enables or disables sensor ( '^U' Command )
							{ return EnableStation( nSensor, bEnable ); }
	BOOL	RestartTracker	( VOID )  // Restarts Tracker, disconnects ( '^Y' Command )
							{ return ResetTracker(); }

private:
	CPDIdev( const CPDIdev & );

	CPiCmdIF * m_pDev;
	CPiError * m_pResult;

	friend class CPDIlatus;
};


/////////////////////////////////////////////////////////////////////
// END $Workfile: PDIdev.h $
/////////////////////////////////////////////////////////////////////
#endif // _PDIDEV_H_
