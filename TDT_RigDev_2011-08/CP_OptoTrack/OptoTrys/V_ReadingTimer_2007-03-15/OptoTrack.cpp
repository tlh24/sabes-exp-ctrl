#include <windows.h>
#include <comdef.h>


#include "OptoTrack.h"
#include "OptoTrackGlob.h"
#include "CP_printf.h"

#define NUM_SENSORS 3
#define NUM_MARKERS 6
#define MAX_OPTOERROR_LEN ( MAX_ERROR_STRING_LENGTH + 1) 

/*****************************************************************
Static Structures and Types:
*****************************************************************/

// Typedef for sensor data returned in a full raw data packet.
typedef struct SensorDataTag
{
    unsigned char   ucPeak;
    unsigned char   ucDRC;
    unsigned char   ucCode;
    unsigned char   ucPeakNibble;
} SensorDataStruct;


// Typedef for a full raw data packet.
typedef struct FullRawDataTag
{
    float           fCentroid[ NUM_SENSORS];
    SensorDataStruct  SensorData[ NUM_SENSORS];
} FullRawDataStruct;

static FullRawDataStruct
    pFullRawData[ NUM_MARKERS];


// The object pointer, we have only one
COptoTrack * g_pOptoTrack = NULL;
//float x_afBuffer[100000];
VARIANT x_vrtRes;



//==============================================================================
COptoTrack::COptoTrack(){
  int i;

  m_IsConnected = 0;
  m_iIsRunning = 0;
  m_iIsCalibrated = 0;
  m_nSensorsMax = 0;
  for( i = 0; i<N_SENSROS_MAX; i++ ) {
    iSensorState[i] = btSensorInactive;
    iActiveSensorIdx[i] = 0;
  }
  // default - activation is requested on sensor #1
  iSensorState[0] = btSensorRequested;
  iSensorState[1] = btSensorRequested;
  iSensorState[2] = btSensorRequested;
  iSensorState[3] = btSensorRequested;

  ZeroMemory( m_LatestFrames, sizeof(tServerFrame) * N_SENSROS_MAX );

  m_nActiveSensors = 0;

/*
  m_SensorDataList.Empty();
  m_SensorDataList.Append( PDI_MODATA_FRAMECOUNT );
  m_SensorDataList.Append( PDI_MODATA_TIMESTAMP );
  m_SensorDataList.Append( PDI_MODATA_EXTSYNC );
  m_SensorDataList.Append( PDI_MODATA_DISTLEV );
  m_SensorDataList.Append( PDI_MODATA_POS );
  m_SensorDataList.Append( PDI_MODATA_ORI );

  m_iPrevFrame = 0;

  // Initialize to identity transform
  m_adCalibrationMatrix[0][0] = 0;
  m_adCalibrationMatrix[0][1] = 1;
  m_adCalibrationMatrix[0][2] = 0;
  m_adCalibrationMatrix[0][3] = 0;
  m_adCalibrationMatrix[0][4] = 0;
  m_adCalibrationMatrix[0][5] = 0;
  m_adCalibrationMatrix[1][0] = 0;
  m_adCalibrationMatrix[1][1] = 0;
  m_adCalibrationMatrix[1][2] = 1;
  m_adCalibrationMatrix[1][3] = 0;
  m_adCalibrationMatrix[1][4] = 0;
  m_adCalibrationMatrix[1][5] = 0;
*/
}

//==============================================================================
COptoTrack::~COptoTrack(){
  //TODO: Check state and unwind if necessary
  if( m_IsConnected ) DisconnectOpto();
}

//==============================================================================
int COptoTrack::m_PrintOptoError( int iError ){

  char szOptoError[MAX_OPTOERROR_LEN];

  if( OptotrakGetErrorString( szOptoError, MAX_OPTOERROR_LEN ) == 0 ) {
      CP_printf("\n%s   Error: %d\n", szOptoError, iError );
  } 
  return 0;

}
//==============================================================================
int COptoTrack::GetN_Sensors( int * piConfigMax, 
                                 int * piDeviceMax, 
                                 int * piDeviceActive ){

  *piConfigMax = N_SENSROS_MAX;
  *piDeviceMax = m_nSensorsMax;
  *piDeviceActive = m_nActiveSensors;

  return 0;
} 
  
//==============================================================================
int COptoTrack::SetSensorsOn( ){
  int i;

  if( m_IsConnected ) {
    CP_printf("Cannot set sensors. Tracker is active!\n");
    return 1;
  }

  for(i=0; i<N_SENSROS_MAX; i++) iSensorState[i] = btSensorInactive;
  return 0;
} 
  
//==============================================================================
int COptoTrack::SetSensorsOff( ){
  int i;

  if( m_IsConnected ) {
    CP_printf("Cannot set sensors. Tracker is active!\n");
    return 1;
  }

  for(i=0; i<N_SENSROS_MAX; i++) iSensorState[i] = btSensorInactive;
  return 0;
} 
//==============================================================================
int COptoTrack::SetSensors( int iSensor, int iSensorOn ){
  if( m_IsConnected ) {
    CP_printf("Cannot set sensor. Tracker is active!\n");
    return 1;
  }

  if( iSensor<0 || iSensor >= N_SENSROS_MAX ){
    CP_printf("Cannot set sensor state. Invalid sensor index: %d\n", iSensor);
    return 2;
  }

  if( iSensorOn ) iSensorState[iSensor] = btSensorRequested;
  else iSensorState[iSensor] = btSensorInactive;
  return 0;
}

//==============================================================================
int COptoTrack::GetSensors( int iSensor, int * piSensorOn ){
  * piSensorOn = 0;

  if( iSensor<0 || iSensor >= N_SENSROS_MAX ){
    CP_printf("Cannot set sensor state. Invalid sensor index: %d\n", iSensor);
    return 2;
  }
  
  * piSensorOn = iSensorState[iSensor];
  return 0;
}
//==============================================================================
int COptoTrack::ResetTimeAndBuffer(){
  
  ResetBuffer();
  ResetTime();
  return 0;
}

//==============================================================================
int COptoTrack::ConnectOpto(  ){
//  BOOL bRes;
  int iErr = 0;
  int iTry;
//  LPCSTR szWhoAmI = NULL;
//  int i;
//  DWORD dwStationMap;
//  int iBitMask;
  


  CP_printf("Connecting to OptoTrack...\n");
  if( m_IsConnected ) {
    CP_printf(" Opto is already connected!\n");
    return 1;
  }

  // Make several trys to load system. If OptoTrack was just
  // turned on, first attempt is unsuccessful
  iTry = 0;
  do {

    // Load OptoTrack transputers with system software
    iErr = TransputerLoadSystem( "system" );
    if( iErr )  {
      CP_printf("Error: TransputerLoadSystem() failed!\n");
      m_PrintOptoError( iErr );
      if( iTry > 2) {
        CP_printf("Giving up on TransputerLoadSystem()\n");
        return 2;

      }
    }
    Sleep( 1000 ); // Wait one second to let the system finish loading.
    iTry++;
  }  while( iErr );

  // Initialize the transputer system.
  iErr = TransputerInitializeSystem( OPTO_LOG_ERRORS_FLAG );
  if( iErr )  {
    CP_printf("Error: TransputerInitializeSystem() failed!\n");
    return 2;
    } 

  // Set optional processing flags (this overides settings in OPTOTRAK.INI).
  iErr = OptotrakSetProcessingFlags( 
//              OPTO_LIB_POLL_REAL_DATA |  // DataIsReady() would not block
              OPTO_CONVERT_ON_HOST |     // Convert raw to 3D on PC
              OPTO_RIGID_ON_HOST );      // Convert 3D to rigid on PC
  if( iErr )  {
    CP_printf("Error: OptotrakSetProcessingFlags() failed!\n");
    return 3;
  }

  // Load the standard camera parameters.
  iErr = OptotrakLoadCameraParameters( "standard" );
  if( iErr )  {
    CP_printf("Error: OptotrakLoadCameraParameters() failed!\n");
    return 4;
  }


  CP_printf("Connected!\n");
  m_IsConnected = 1;
/*
  bRes = m_PdiDev.WhoAmI ( szWhoAmI ); 
  CP_printf("=========== Opto info =============");
  CP_printf("%s", szWhoAmI);
  CP_printf("======================================\n");

  
  bRes = m_PdiDev.SetBinary( TRUE );  // Set binary mode
  bRes = m_PdiDev.SetMetric( TRUE );  // Set metric units (cm)
  bRes = m_PdiDev.SetFrameRate( PI_FRATE_240 ); // 240 Hz
  bRes = m_PdiDev.SetSyncEnabled ( TRUE ); // Enable input TTL sync 
// TODO: ?? BOOL SetSourceFrame ( const PDIori & ); // rotate ref. frame

  m_nSensorsMax = m_PdiDev.MaxSensors();
  CP_printf("Max number of sensors:  %d\n", m_nSensorsMax);
  
  // setup bitmask for requested sensors
  iBitMask = 1;
  dwStationMap = 0;
  for( i = 0; i<N_SENSROS_MAX; i++ ) {
    if( iSensorState[i] & btSensorRequested ) dwStationMap |= iBitMask;
    iBitMask <<= 1;
  }
  // Enable/disable sensors specified dy the bits
  bRes = m_PdiDev.SetStationMap ( dwStationMap ); 

  // Check actual active sensors
  bRes = m_PdiDev.GetStationMap ( dwStationMap ); 

  // Determine which sensors have been actually activated
  // Get the number of active sensors
  // Warn if a requested sensor was not activated
  m_nActiveSensors = 0;
  iBitMask = 1;
  for( i = 0; i<N_SENSROS_MAX; i++ ) {
    if( dwStationMap & iBitMask ) {
      iSensorState[i] |= btSensorActive;
      iActiveSensorIdx[m_nActiveSensors] = i;
      m_nActiveSensors++;
    }
    if( iSensorState[i] == btSensorRequested ) {
      CP_printf("Warning: failed to activate sensor# %d  \n", i+1 );
    }
    iBitMask <<= 1;
  }
  if( m_nActiveSensors  < 1 ) {
    m_PdiDev.SetStationMap ( 0 ); // disable all sensors
    CP_printf("Error: no active sensors found!\n");
    iErr = 4;
    goto errExit;
  }

  CP_printf("Number of active sensors: %d \n", m_nActiveSensors);
  CP_printf("List of active sensors:   ");
  for( i = 0; i<m_nActiveSensors; i++ ) {
    CP_printf("%d    ", iActiveSensorIdx[i] +1);
  }
  CP_printf("\n");
  // set output vars for ALL sensors
  bRes = m_PdiDev.SetSDataList ( -1, m_SensorDataList );

  // set data buffer
  bRes = m_PdiDev.SetPnoBuffer ( m_pPnoBuf, PNO_BUF_SIZE ); 

  // create sliding buffer
  bRes = SetBuffer( sizeof(tServerFrame) * m_nActiveSensors, // Item size
                    BUFFER_SIZE_SECONDS * FRAME_RATE_HZ );   // N items
  if( !bRes ) {
    CP_printf("Error: SetBuffer() failed!\n");
    iErr = 5;
    goto errExit;
  }

//  CP_printf("Raw frame size: %d \n\n", sizeof(tOptoFrame));


  m_iPrevFrame = 0;
// SetAttFilter
// SetPosFilter
  // Reset device counters
  bRes = m_PdiDev.ResetTimeStamp();
  bRes = m_PdiDev.ResetFrameCount();
  // Start cont. acquisition
  bRes = m_PdiDev.StartContPno( g_GetWindowHandle() );
*/

  // Set up a collection for the OPTOTRAK.

  iErr = OptotrakSetupCollection(
          NUM_MARKERS,    // Number of markers in the collection. 
          (float)FRAME_RATE_HZ,   // Frequency to collect data frames at. 
          (float)2500.0,  // Marker frequency for marker maximum on-time. 
          30,             // Dynamic or Static Threshold value to use. 
          160,            // Minimum gain code amplification to use. 
          0,              // Stream mode for the data buffers. 
          (float)0.35,    // Marker Duty Cycle to use. 
          (float)7.0,     // Voltage to use when turning on markers. 
          (float)1.0,     // Number of seconds of data to collect. 
          (float)0.0,     // Number of seconds to pre-trigger data by. 
          OPTOTRAK_GET_NEXT_FRAME_FLAG | // TODO: maybe we should not use this?
          OPTOTRAK_BUFFER_RAW_FLAG );   
  
  if( iErr )  {
    CP_printf("Error: OptotrakSetupCollection() failed!\n");
    iErr = 6;
    goto errExit;
  }

  // manual warns of errors if we don't wait enough 
  // after calling OptotrakSetupCollection()
  Sleep( 1000 );  

  if( m_StartReadingTimer( 1000/FRAME_RATE_HZ ) ) {
    CP_printf("Error: m_StartReadingTimer() failed!\n");
    iErr = 6;
    goto errExit;
  }


  m_iIsRunning = 1;
  return 0;

errExit:
    DisconnectOpto();
    return iErr;
}

//==============================================================================
int COptoTrack::DisconnectOpto(){
  int iErr;
  int i;

  // Stop acquisition if needed
  if( m_iIsRunning ) {
    if( m_StopReadingTimer() ) {
      CP_printf("Error: m_StopReadingTimer() failed!\n");
      return 1;
    }
    m_iIsRunning = 0;
  }

  // release the buffers
  RemoveBuffer();
  CP_printf("DisonnectOpto...   ");

  if( !m_IsConnected ) {
    CP_printf("Opto is not connected!\n");
    return 2;
  }

  // Shutdown the transputer message passing system.
  iErr = TransputerShutdownSystem();
  if( iErr ) {
    CP_printf("Failed!\n");
    goto errExit;
  }

  CP_printf("Ok!\n");
  CP_printf("++++++++++++++++++++++++++++++++++++++\n");
  m_nActiveSensors = 0;
  for( i = 0; i<N_SENSROS_MAX; i++ ) {
    iSensorState[i] &= btSensorRequested;
    iActiveSensorIdx[i] = 0;
  }
  m_IsConnected = 0;
  return 0;

errExit: 
    m_IsConnected = 0;
    return 2;

}
//==============================================================================
int COptoTrack::ProcessTimerEvent( int iTimerCounter ){

  unsigned int
    uFlags,
    uElements,
    uFrameNumber;
  static int iPrevFrame = 0;
  int nFrames;

  // Get a frame of data.
	// we did set OPTOTRAK_GET_NEXT_FRAME_FLAG, so we will have
  // no repeating frames
  uFrameNumber = 0;
  nFrames = 0;
/*
  RequestLatestRaw();  // prepare for the next frame
  while( DataIsReady()) {

    if( DataGetLatestRaw( &uFrameNumber, &uElements, &uFlags,
                          pFullRawData ) ){
      return 1;
    }
    nFrames++;
  }
  if( nFrames != 1 ){
    CP_printf("N Frames:  %d\n", nFrames);
  }
*/

  if( DataGetLatestRaw( &uFrameNumber, &uElements, &uFlags,
                        pFullRawData ) ){
    CP_printf("DataGetLatestRaw() failed!\n");
    return 1;
  }
  if( uFrameNumber - iPrevFrame > 1 ){
    CP_printf("Missed frames: %d     %d     %d\n", iTimerCounter,  uFrameNumber,  iPrevFrame);
  }


//  CP_printf("\r%d     ", iTimerCounter);

  iPrevFrame = uFrameNumber;
  return 0;
}
//==============================================================================
int COptoTrack::GetVersion( BSTR * pbstVer){
  
  _bstr_t bscTmp(g_szVersion);
  *pbstVer =  bscTmp.copy();

  return 0;
}
//==============================================================================
int COptoTrack::GetVersion( char ** pszVer){
  
  * pszVer = g_szVersion;
  return 0;
}

//==============================================================================
int COptoTrack::GetOptoState( int * piState ){
  
  *piState = m_IsConnected + m_iIsRunning * 2;
 
  return 0;
}

//==============================================================================
int COptoTrack::GetCalibrationMatrixPtr(  double ** pdMtx ){
  
  * pdMtx = (double *) m_adCalibrationMatrix;
  return 0;
}

//==============================================================================
int COptoTrack::GetCalibrationFlag(   int * piIsCalibrated ){
  
  * piIsCalibrated = m_iIsCalibrated;
  return 0;
}

//==============================================================================
int COptoTrack::SetCalibrationFlag(  int iIsCalibrated ){
  
  m_iIsCalibrated = iIsCalibrated;
  return 0;
}
//==============================================================================
int COptoTrack::CalcCalibCoordinates( double dX_Raw, double dY_Raw, double * pdX_Calib, double * pdY_Calib ){

  double dRawMtx[CALIB_N_J];
  int j;
  double dX, dY;

  dRawMtx[0] = 1;
  dRawMtx[1] = dX_Raw;
  dRawMtx[2] = dY_Raw;
  dRawMtx[3] = dX_Raw * dX_Raw;
  dRawMtx[4] = dX_Raw * dY_Raw;
  dRawMtx[5] = dY_Raw * dY_Raw;

  dX = 0; dY = 0;
  for(j = 0; j< CALIB_N_J; j++ ) {
    dX += dRawMtx[j] * m_adCalibrationMatrix[0][j];
    dY += dRawMtx[j] * m_adCalibrationMatrix[1][j];
  }
  * pdX_Calib = dX;
  * pdY_Calib = dY;

  return 0;
}

//===========================================================================
int COptoTrack::GetLatestFramePtr( int iIdx, tServerFrame ** ppFrame ) {
  
  if ( !( m_IsConnected && m_iIsRunning) ) goto errExit;
  if ( iIdx >= m_nActiveSensors ) goto errExit;
  
  * ppFrame = &m_LatestFrames[iIdx];
  return 0;

errExit: 
  * ppFrame = NULL;
  return 1;
}
