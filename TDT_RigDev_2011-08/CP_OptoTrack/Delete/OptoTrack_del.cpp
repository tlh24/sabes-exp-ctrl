#include <windows.h>
#include <comdef.h>

#include "OptoTrack.h"
#include "OptoTrackGlob.h"
#include "CP_printf.h"

#define MAX_OPTOERROR_LEN ( MAX_ERROR_STRING_LENGTH + 1) 

// The object pointer, we have only one
COptoTrack * g_pOptoTrack = NULL;

//==============================================================================
int COptoTrack::m_PrintOptoError( int iError ){

  char szOptoError[MAX_OPTOERROR_LEN];

  if( OptotrakGetErrorString( szOptoError, MAX_OPTOERROR_LEN ) == 0 ) {
      CP_printf("\n%s   Error: %d\n", szOptoError, iError );
  } 
  return 0;

}

//==============================================================================
int COptoTrack::ReadingFunc( ){

  unsigned int
    uFlags,
    uElements,
    uFrameNumber;
  int 
    iSensor, 
    iSensorWrite,
    iTrans,
    nMissed;
  Position3d      atBufferXYZ[N_SENSROS_MAX];  // includes all sensors
  OptoFrameStruct tmpFrame;

  // Get a frame of data.
  uFrameNumber = 0;
  if( DataGetNext3D( &uFrameNumber, &uElements, &uFlags, atBufferXYZ ) ){
    CP_printf("\nDataGetNext3d() failed!\n");
    return 1;
  }

  // Check for buffer errors
  if( uFlags ) {
    CP_printf("\nError in DataGetNext3d() buffering!\n");
    return 1;
  }
  // Check if we have the right number of sensors
  if( m_nSensorsToRead != (int)uElements ) {
    CP_printf("\nWrong number of Sensors in the raw frame! Expected: %d    Recieved: %d\n",
                                                                 m_nSensorsToRead, uElements);
    return 1;
  }
  //TODO -estimate using time server coeffs
  tmpFrame.tHeader.dMeasurementTimeMs = FRAME_TIME_MS * uFrameNumber; 
  tmpFrame.tHeader.iFrame = uFrameNumber;
  tmpFrame.tHeader.nSensors = m_nSensorsToWrite;

//  CP_printf("Frame Number: %8u\r", uFrameNumber );

  nMissed = uFrameNumber - m_iPrevFrame - 1;
  if( nMissed && ( m_ReadCount > 1) ){
    m_nMissedCount++;
    m_nMissedFrames += nMissed;
//    CP_printf("\nMissed frames:     %d     %d\n",  uFrameNumber,  nMissed);
  }
  
  // Parse the data, write into buffer
  iSensorWrite = 0;
  for( iSensor = 0; iSensor < m_nSensorsToRead; iSensor++ ) {
    if(m_atSensorState[iSensor].iSaveToBuffer){
      //check for invalid data (enough to check just one coordinate)
      if(atBufferXYZ[iSensor].x < MAX_NEGATIVE) {  
      // Set all coordinates to bad float
        tmpFrame.atXYZ[iSensorWrite].x= BAD_FLOAT;
        tmpFrame.atXYZ[iSensorWrite].y= BAD_FLOAT;
        tmpFrame.atXYZ[iSensorWrite].z= BAD_FLOAT;
      } // if bad data
      else {
        // apply the transform 
        iTrans = m_atSensorState[iSensor].iTransform;
        tmpFrame.atXYZ[iSensorWrite].x = 
            m_atTransformMtx[iTrans][0][0] * atBufferXYZ[iSensor].x + 
            m_atTransformMtx[iTrans][0][1] * atBufferXYZ[iSensor].y +
            m_atTransformMtx[iTrans][0][2] * atBufferXYZ[iSensor].z +
            m_atTransformMtx[iTrans][0][3];     // X0

        tmpFrame.atXYZ[iSensorWrite].y = 
            m_atTransformMtx[iTrans][1][0] * atBufferXYZ[iSensor].x + 
            m_atTransformMtx[iTrans][1][1] * atBufferXYZ[iSensor].y +
            m_atTransformMtx[iTrans][1][2] * atBufferXYZ[iSensor].z +
            m_atTransformMtx[iTrans][1][3];     // Y0

        tmpFrame.atXYZ[iSensorWrite].z = 
            m_atTransformMtx[iTrans][2][0] * atBufferXYZ[iSensor].x + 
            m_atTransformMtx[iTrans][2][1] * atBufferXYZ[iSensor].y +
            m_atTransformMtx[iTrans][2][2] * atBufferXYZ[iSensor].z +
            m_atTransformMtx[iTrans][2][3];     // Z0
      } // if not bad data
      iSensorWrite++;
    }  // if save to buffer
  } // for all sensors
   
  WriteData(&tmpFrame, 1);  // save 1 frame in the buffer

  m_iPrevFrame = uFrameNumber;
  m_ReadCount++;

  return 0;
}

//==============================================================================
int COptoTrack::ShutdownFunc( ){
  int iErr;


  // Shutdown the transputer message passing system.
  iErr = TransputerShutdownSystem();
  if( iErr ) {
    CP_printf("\nTransputerShutdownSystem() Failed!\n");
    return 2;
  }
  return 0;
}

//==============================================================================
COptoTrack::COptoTrack(){
  int iTrans;

  m_IsConnected = 0;
  m_nSensorsToRead = 0;
  m_nSensorsToWrite = 0;
  ZeroMemory(m_anSensorsPerPort, sizeof(m_anSensorsPerPort) );
  ZeroMemory(m_atSensorState, sizeof(m_atSensorState) );

  // Set defaults for 1 sensor on port 1
  m_nSensorsToRead = 1;
  m_nSensorsToWrite = 1;
  m_anSensorsPerPort[0] = 1;
  m_atSensorState[0].iPort = 0;
  m_atSensorState[0].iSensor = 0;
  m_atSensorState[0].iSaveToBuffer = 1;
  m_atSensorState[0].iTransform = 0;

  m_ReadCount = 0;
  m_nMissedCount = 0;
  m_nMissedFrames = 0;
  m_iPrevFrame = 0;
  m_iFrameSize = 0;

  // Initialize to identity transform
  for( iTrans = 0; iTrans<N_TRANSFORMS; iTrans++ ) {
    m_atTransformMtx[iTrans][0][0] = 1;     // X
    m_atTransformMtx[iTrans][0][1] = 0;     // Y
    m_atTransformMtx[iTrans][0][2] = 0;     // Z
    m_atTransformMtx[iTrans][0][3] = 0;     // X0
    m_atTransformMtx[iTrans][1][0] = 0;     // X
    m_atTransformMtx[iTrans][1][1] = 1;     // Y
    m_atTransformMtx[iTrans][1][2] = 0;     // Z
    m_atTransformMtx[iTrans][1][3] = 0;     // Y0
    m_atTransformMtx[iTrans][2][0] = 0;     // X
    m_atTransformMtx[iTrans][2][1] = 0;     // Y
    m_atTransformMtx[iTrans][2][2] = 1;     // Z
    m_atTransformMtx[iTrans][2][3] = 0;     // Z0
  }

/*
  // Initialize to the rig transform
  m_atTransformMtx[0][0][0] = 0.002619680390876f;     // X to X
  m_atTransformMtx[0][0][1] = 0.99994911868751f;     // Y to X
  m_atTransformMtx[0][0][2] = 0.009741525071601f;     // Z to X
  m_atTransformMtx[0][0][3] = 300.74466955487156f;     // X0
  m_atTransformMtx[0][1][0] = -0.244212304835805f;     // X to Y
  m_atTransformMtx[0][1][1] = -0.008806869464799f;     // Y to Y
  m_atTransformMtx[0][1][2] = 0.96968179791982f;     // Z to Y
  m_atTransformMtx[0][1][3] = 1541.4572967483682f;     // Y0
  m_atTransformMtx[0][2][0] = 0.969718251576938f;     // X to Z
  m_atTransformMtx[0][2][1] = -0.004919256681752f;     // Y to Z
  m_atTransformMtx[0][2][2] = 0.244176807809967f;     // Z to Z
  m_atTransformMtx[0][2][3] = 336.2203235849135f;     // Z0
*/
}

//==============================================================================
COptoTrack::~COptoTrack(){
  if( m_IsConnected ) DisconnectOpto();
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
int COptoTrack::GetSensors( SensorInfo * ptSensorInfo ){
  int idxIn;
  int idxOut;

  idxOut = 0;
  for( idxIn = 0; idxIn < m_nSensorsToRead; idxIn++ ){
    if( m_atSensorState[idxIn].iSaveToBuffer) {
      ptSensorInfo[idxOut].iSensor = m_atSensorState[idxIn].iSensor;
      ptSensorInfo[idxOut].iTransform = m_atSensorState[idxIn].iTransform;
      ptSensorInfo[idxOut].iPort = m_atSensorState[idxIn].iPort;
      idxOut++;
    }
  }  // for all sensors
  
  return 0;
}

//==============================================================================
int COptoTrack::SetSensors( int nSensors, SensorInfo * ptSensorInfo ){
  int idxIn, idxOut;
  int iPort, iSensor, iTrans, nPortSensors;
  int iPortPrev, iSensorPrev;

  if( m_IsConnected ) {
    CP_printf("Cannot set sensors. Tracker is active!\n");
    return 1;
  }

  if( nSensors < 0 || nSensors >= N_SENSROS_MAX ){
    CP_printf("Cannot set sensors. Number of sensors is out of range: %d\n", nSensors);
    return 1;
  }
  // reset to zero
  ZeroMemory(m_atSensorState, sizeof(m_atSensorState) );
  ZeroMemory(m_anSensorsPerPort, sizeof(m_anSensorsPerPort) );
  m_nSensorsToRead = 0;
  m_nSensorsToWrite = 0;

  iPortPrev = -1;
  iSensorPrev = -1;
  for( idxIn = 0; idxIn < nSensors; idxIn++) {
    iSensor = ptSensorInfo[idxIn].iSensor; 
    // Check sensor for valid range
    if( iSensor < 0 || iSensor >= N_SENSROS_AT_PORT_MAX ){
      CP_printf("Cannot set sensors. Sensor out of range: %d\n", iSensor );
      return 1;
    }

    iTrans = ptSensorInfo[idxIn].iTransform; 
    // Check transform for valid range
    if( iTrans < 0 || iTrans >= N_TRANSFORMS ){
      CP_printf("Cannot set sensors. Transfrom index out of range: %d\n", iTrans );
      return 1;
    }

    iPort = ptSensorInfo[idxIn].iPort;
    // Check port for valid range
    if( iPort < 0 || iPort >= N_PORTS )  {
      CP_printf("Cannot set sensors. Port out of range: %d\n", iPort);
      return 1;
    }

    // Check ports for order
    if( iPort < iPortPrev ) {
      CP_printf("Cannot set sensors. Ports/Sensors should be ordered.\n");
      return 1;
    }
    if( iPort > iPortPrev )  {
      iSensorPrev = -1;  // start over sensor sequence
    }
    iPortPrev = iPort;

    if( iSensor <= iSensorPrev ) {
      CP_printf("Cannot set sensors. Ports/Sensors should be ordered.\n");
      return 1;
    }
    iSensorPrev = iSensor;
    m_anSensorsPerPort[iPort] = iSensor+1;
  }  // for all ptSensorInfo elements

  m_nSensorsToWrite = nSensors;

  idxIn = 0;
  idxOut = 0;
  CP_printf("Optotrak ports setup:\n"); 
  for( iPort = 0; iPort < N_PORTS; iPort++ ){
    nPortSensors = m_anSensorsPerPort[iPort];
    m_nSensorsToRead += nPortSensors;
    for( iSensor = 0; iSensor < nPortSensors; iSensor++ ){
      m_atSensorState[idxOut].iPort = iPort;
      m_atSensorState[idxOut].iSensor = iSensor;
      // Set the flag if we need to save data from this sensor
      // And the transform matrix index
      if( ptSensorInfo[idxIn].iPort == iPort && 
          ptSensorInfo[idxIn].iSensor == iSensor ){
        m_atSensorState[idxOut].iSaveToBuffer = 1;
        m_atSensorState[idxOut].iTransform = ptSensorInfo[idxIn].iTransform;
        idxIn++;
      }
      idxOut++;
    }  // for all port sensors
    CP_printf("Port:  %d,   N Sensors: %d\n", iPort+1, nPortSensors);
  }  // for all ports
  CP_printf("Total %d sensors to acquire,   %d sensros to save.\n", m_nSensorsToRead,   m_nSensorsToWrite);
  return 0;
}

//==============================================================================
int COptoTrack::GetTransformMatrix( int iTransform, float * pfMtx ){

  //      dest              src
  memcpy( pfMtx, m_atTransformMtx[iTransform], sizeof(tTransformMtx)) ;
  return 0;
}

//==============================================================================
int COptoTrack::SetTransformMatrix( int iTransform, float * pfMtx ){
  
  if ( m_IsConnected ) return 1;
  //      dest              src
  memcpy( m_atTransformMtx[iTransform], pfMtx, sizeof(tTransformMtx)) ;
  return 0;
}

//==============================================================================
int COptoTrack::GetN_Sensors( int * piConfigMax, 
                              int * pnSensorsToRead, 
                              int * pnSensorsToWrite ){

  *piConfigMax = N_SENSROS_MAX;
  *pnSensorsToRead = m_nSensorsToRead;
  *pnSensorsToWrite = m_nSensorsToWrite;

  return 0;
} 
  
//==============================================================================
int COptoTrack::ConnectOpto(  ){
  BOOL bRes;
  int iErr;
  int iAttempt;

  CP_printf("Connecting to OptoTrack...\n");
  if( m_IsConnected ) {
    CP_printf(" Opto is already connected!\n");
    return 1;
  }

  // Make several attempts to load system. If OptoTrack was just
  // turned on, first attempt is unsuccessful
  iErr = 1;
  for( iAttempt = 0; iAttempt < 2 && iErr;  iAttempt++ ){
    // Load OptoTrack transputers with system software
    iErr = TransputerLoadSystem( "system" );
    Sleep( 1000 ); // Wait one second to let the system finish loading.
  }
  if( iErr )  {
    CP_printf("Error: % d attempts of TransputerLoadSystem() failed!\n", iAttempt);
    m_PrintOptoError( iErr );
    CP_printf("Giving up on TransputerLoadSystem()\n");
    return 1;
  }
  CP_printf("TransputerLoadSystem(): Ok \n");

  // Initialize the transputer system.
  iErr = TransputerInitializeSystem( 0 );  // 0 == don't create log files
  if( iErr )  {
    CP_printf("Error: TransputerInitializeSystem() failed!\n");
    return 1;
  } 
  CP_printf("TransputerInitializeSystem(): Ok \n");

  // Set optional processing flags (this overrides settings in OPTOTRAK.INI).
  iErr = OptotrakSetProcessingFlags( 
//              OPTO_LIB_POLL_REAL_DATA |  // if this flag is set, CPU clocks are waisted
              OPTO_CONVERT_ON_HOST |     // Convert raw to 3D on PC
              OPTO_RIGID_ON_HOST );      // Convert 3D to rigid on PC
  if( iErr )  {
    CP_printf("Error: OptotrakSetProcessingFlags() failed!\n");
    return 1;
  }
  CP_printf("OptotrakSetProcessingFlags(): Ok \n");
  
  // Load the standard camera parameters.
  iErr = OptotrakLoadCameraParameters( "standard" );
  if( iErr )  {
    CP_printf("Error: OptotrakLoadCameraParameters() failed!\n");
    return 1;
  }
  CP_printf("OptotrakLoadCameraParameters(): Ok \n");


  // create sliding buffer
  m_iFrameSize = sizeof(FrameHeaderStruct) + 
                    sizeof(Position3d) * m_nSensorsToWrite;
  bRes = SetBuffer( m_iFrameSize, // Item size
                    int(BUFFER_SIZE_SECONDS * FRAME_RATE_HZ) );   // N items
  if( !bRes ) {
    CP_printf("Error: SetBuffer() failed!\n");
    iErr = 1;
    goto errExit;
  }

//  CP_printf("Raw frame size: %d \n\n", sizeof(tOptoFrame));

  CP_printf("Connected!\n");
  m_IsConnected = 1;

  m_iPrevFrame = 0;

  iErr = OptotrakSetStroberPortTable( m_anSensorsPerPort[0],
                                      m_anSensorsPerPort[1],
                                      m_anSensorsPerPort[2],
                                      m_anSensorsPerPort[3] );
  if( iErr )  {
    CP_printf("Error: OptotrakSetStroberPortTable() failed!\n");
    iErr = 1;
    goto errExit;
  }

  // Set up collection 
  // This starts data acquisition
  iErr = OptotrakSetupCollection(
            m_nSensorsToRead,    // Number of markers in the collection. 
            FRAME_RATE_HZ,  // Frequency to collect data frames at. 
            2000.0f,        // Marker frequency for marker maximum on-time. 
            30,             // Dynamic or Static Threshold value to use. 
            160,            // Minimum gain code amplification to use. 
            0,              // Stream mode for the data buffers. 
            0.5f,           // Marker Duty Cycle to use. 
            5.0f,           // Voltage to supply strobers and LEDs 
//            7.5f,           // Voltage to supply strobers and LEDs 
            0.0f,           // Number of seconds of data to collect. 
            0.0f,           // Number of seconds to pre-trigger data by. 
            0 );            // No flags

// Possible flags (not used):
//    OPTOTRAK_GET_NEXT_FRAME_FLAG // Don't receive the same frame twice
//  | OPTOTRAK_BUFFER_RAW_FLAG 
  
  if( iErr )  {
    CP_printf("Error: OptotrakSetupCollection() failed!\n");
    iErr = 1;
    goto errExit;
  }

  // manual warns of errors if we don't wait enough 
  // after calling OptotrakSetupCollection()
  Sleep( 1000 );  
//  TODO: what should be the default state??
//  iErr = OptotrakDeActivateMarkers();

  m_ReadCount = 0;
  m_nMissedCount = 0;
  m_nMissedFrames = 0;
  m_iPrevFrame = 0;
  // Start the thread
  if( m_StartReadingThread( )) {
    CP_printf("Error: m_StartReadingThread() failed!\n");
    iErr = 1;
    goto errExit;
  }

  return 0;

errExit:
    DisconnectOpto();
    return iErr;
}

//==============================================================================
int COptoTrack::DisconnectOpto(){

  if( !m_IsConnected ) {
    CP_printf("Opto is not connected!\n");
    return 1;
  }
  CP_printf("\nDisonnecting OptoTrak...   ");
  // Stop the thread, specify stopping time in ms (duration of 10 frames)
  if( m_StopReadingThread( int(FRAME_TIME_MS) * 10 )  > 1 ) {
    CP_printf("\nError: m_StopReadingThread() failed!\n");
    return 1;
  }

  // release the buffers
  RemoveBuffer();

  m_IsConnected = 0;
  CP_printf("Ok!\n");
  CP_printf("++++++++++++++++++++++++++++++++++++++\n");

  return 0;
}

//==============================================================================
int COptoTrack::GetOptoState( int * piState ){
  
  *piState = m_IsConnected; 
  return 0;
}

//==============================================================================
int COptoTrack::ActivateSensors( ){
  int iErr;

  if( !m_IsConnected ) {
    CP_printf("Cannot activate sensors. Tracker is not active!\n");
    return 1;
  }
  iErr = OptotrakActivateMarkers();
  if( iErr ) {
    CP_printf("Error: OptotrakActivateMarkers() failed!\n");
    return 1;
  }

  return 0;
} 
  
//==============================================================================
int COptoTrack::DeactivateSensors( ){
  int iErr;

  if( !m_IsConnected ) {
    CP_printf("Cannot deactivate sensors. Tracker is not active!\n");
    return 1;
  }

  iErr = OptotrakDeActivateMarkers();
  if( iErr ) {
    CP_printf("Error: OptotrakDeActivateMarkers() failed!\n");
    return 1;
  }

  return 0;
} 

//===========================================================================
int COptoTrack::GetLatestData( double * pdTimeMs,
                               int * piFrame,
                               int * pnMissedFrames,
                               int * pnMissedCount,
                               int nSensors,
                               float * pfXYZ ) {

  OptoFrameStruct   tLatestFrame;
  int iIdx;
  int nOut, iCoord;
  
  if ( !m_IsConnected ) return 1;

  // Get latest frame from the buffer
  ReadLatestItem( &iIdx, &tLatestFrame );
  * pdTimeMs = tLatestFrame.tHeader.dMeasurementTimeMs;
  * piFrame = tLatestFrame.tHeader.iFrame;
  * pnMissedCount = m_nMissedCount;
  * pnMissedFrames = m_nMissedFrames;
  nOut = min(nSensors, m_nSensorsToWrite);
  // Copy the data from the frame to the buffer
  memcpy( pfXYZ, tLatestFrame.atXYZ, sizeof(float) * nOut * N_COORD);
  // fill the rest (if any) with the missing data constant
  for( iCoord = nOut * N_COORD; iCoord < nSensors * N_COORD; iCoord++)
    pfXYZ[iCoord] = BAD_FLOAT;

  return 0;
}

//===========================================================================
int COptoTrack::ParseBuffer( int iSensor,
                             int nFrames,
                             void * pvSrcBuffer,
                             double * pdTimeStamps, 
                             float * pfCoordinates,
                             float *pfVelocities  ){

  FrameHeaderStruct * ptFrameHeader;
  int iFrameSize, iHeaderSize;
  char * pcFrame;
  void * pvCoordSrc;
  int iFrame;

  iFrameSize = g_pOptoTrack->GetItemSize();
  iHeaderSize =  sizeof( FrameHeaderStruct );

  pcFrame = (char *) pvSrcBuffer;
  for( iFrame = 0; iFrame < nFrames; iFrame++ ) {
    ptFrameHeader = (FrameHeaderStruct *) pcFrame;
    pdTimeStamps[iFrame] = ptFrameHeader->dMeasurementTimeMs;
    pvCoordSrc = pcFrame + (iHeaderSize + sizeof(Position3d) * iSensor);
    memcpy( pfCoordinates, pvCoordSrc, sizeof(Position3d) );
    pfCoordinates += N_COORD;
    pcFrame += iFrameSize;
  }

  return 0;
}

//===========================================================================
int COptoTrack::ParseBuffer( int nFrames,
                             void * pvSrcBuffer,
                             double * pdTimeStamps, 
                             float * pfCoordinates,
                             float *pfVelocities  ){

  FrameHeaderStruct * ptFrameHeader;
  int iFrameSize, iHeaderSize, iDataSize;
  int nCoordinates;
  char * pcFrame;
  void * pvCoordSrc;
  int iFrame;

  iFrameSize = g_pOptoTrack->GetItemSize();
  iHeaderSize =  sizeof( FrameHeaderStruct );
  iDataSize = iFrameSize - iHeaderSize;
  nCoordinates = iDataSize / sizeof(float);

  pcFrame = (char *) pvSrcBuffer;
  for( iFrame = 0; iFrame < nFrames; iFrame++ ) {
    ptFrameHeader = (FrameHeaderStruct *) pcFrame;
    pdTimeStamps[iFrame] = ptFrameHeader->dMeasurementTimeMs;
    pvCoordSrc = pcFrame + iHeaderSize;
    memcpy( pfCoordinates, pvCoordSrc, iDataSize );
    pfCoordinates += nCoordinates;
    pcFrame += iFrameSize;
  }

  return 0;
}
