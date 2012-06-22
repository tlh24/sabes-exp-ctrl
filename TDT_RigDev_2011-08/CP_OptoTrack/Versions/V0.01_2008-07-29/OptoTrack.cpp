#include <windows.h>
#include <comdef.h>


#include "OptoTrack.h"
#include "OptoTrackGlob.h"
#include "CP_printf.h"

// the first marked frame should have index less than MAX_START_FRAME
// if it's bigger, we ignore it and keep waiting
#define MAX_START_FRAME  50   

//==============================================================================
COptoTrack::COptoTrack(){
  int iTrans, i;

  // Generic inits first
  m_nSensorsToRead = 0;
  m_nSensorsToWrite = 0;
  m_iReadCount = 0;
  m_iOptoFrameIdx = 0;
  m_iPrevFrame = 0;
  m_nMissedTimes = 0;
  m_nMissedFrames = 0;
  m_dTimeC0 = 0;
  m_dTimeC1 = 1000.0/FRAME_RATE_HZ;

  ZeroMemory(m_atSensorState, sizeof(m_atSensorState));
  ZeroMemory(m_aiWriteFlag, sizeof(m_aiWriteFlag)); 
  ZeroMemory(m_anSensorsPerPort, sizeof(m_anSensorsPerPort)); 

  // Initialize to the identity transform
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

  // Set signal level indicator to OFF
  for(i =0; i < N_SENSORS_MAX; i++)
    m_iDistirtionLevel[i]= ecSensorOff;

  // Set the defaults
  // default: 1 active sensor at port #1
  m_nSensorsToRead = 1;
  m_nSensorsToWrite = 1;
  m_atSensorState[0].iSensor = 0;
  m_aiWriteFlag[0] = 1;
  m_anSensorsPerPort[0] = 1;

  // default: 4 active sensors at port #1
  m_nSensorsToRead = 4;
  m_nSensorsToWrite = 4;

  m_atSensorState[0].iSensor = 0;
  m_atSensorState[1].iSensor = 1;
  m_atSensorState[2].iSensor = 2;
  m_atSensorState[3].iSensor = 3;

  m_aiWriteFlag[0] = 1;
  m_aiWriteFlag[1] = 1;
  m_aiWriteFlag[2] = 1;
  m_aiWriteFlag[3] = 1;

  m_anSensorsPerPort[0] = 4;

/*
  // Initialize transform #1 to the rig transform
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
  //TODO: Check state and unwind if necessary
  if( IsRunning() ) DisconnectOpto();
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
  
  *piState = IsRunning();
 
  return 0;
}


//==============================================================================
int COptoTrack::GetSignalDistortion( int aiDistortion[N_SENSORS_MAX] ){
  int i;

  for(i =0; i < N_SENSORS_MAX; i++)
    aiDistortion[i] = m_iDistirtionLevel[i];

  return 0;
}

//==============================================================================
int COptoTrack::GetTransformMatrix( int iTransform, float * pfMtx ){

  if( iTransform < 0 || iTransform >= N_TRANSFORMS) return 1;
  //      dest              src
  memcpy( pfMtx, m_atTransformMtx[iTransform], sizeof(tTransformMtx)) ;
  return 0;
}

//==============================================================================
int COptoTrack::GetTransformMatrix( int iTransform, double * pdMtx ){
 
  int i;
  float  * pfMtx;

  if( iTransform < 0 || iTransform >= N_TRANSFORMS) return 1;

  pfMtx = (float *) m_atTransformMtx[iTransform];
  for(i = 0; i < TRANSFORM_N_I*TRANSFORM_N_J; i++)
    *pdMtx++ = (double) *pfMtx++;

  return 0;
}

//==============================================================================
int COptoTrack::SetTransformMatrix( int iTransform, float * pfMtx ){
  
  if( iTransform < 0 || iTransform >= N_TRANSFORMS) return 1;
  //      dest              src
  memcpy( m_atTransformMtx[iTransform], pfMtx, sizeof(tTransformMtx)) ;
  return 0;
}

//==============================================================================
int COptoTrack::SetTransformMatrix( int iTransform, double * pdMtx ){
  int i;
  float  * pfMtx;

  if( iTransform < 0 || iTransform >= N_TRANSFORMS) return 1;

  pfMtx = (float *) m_atTransformMtx[iTransform];
  for(i = 0; i < TRANSFORM_N_I*TRANSFORM_N_J; i++)
    *pfMtx++ = (float) *pdMtx++;

  return 0;
}

//==============================================================================
int COptoTrack::GetFrameCount( int *pnFrames){

  // The first frame has index 1
  // This way it is compatible with the frame counter hardware
  *pnFrames = m_iOptoFrameIdx + 1;
  return 0;
}
 
//==============================================================================
int COptoTrack::GetTimeScale( double *pdC0, double *pdC1){

  *pdC0 = m_dTimeC0;
  *pdC1 = m_dTimeC1;

  return 0;
}

//==============================================================================
int COptoTrack::SetTimeScale( double dC0, double dC1){

  m_dTimeC0 = dC0;
  m_dTimeC1 = dC1;

  return 0;
}
//==============================================================================
int COptoTrack::GetSensors( tSensorInfo * atSensorInfo ){
  int i;
  
  for( i = 0; i < m_nSensorsToWrite; i++ ){
    atSensorInfo[i].iSensor = m_atSensorState[i].iSensor;
    atSensorInfo[i].iPort = m_atSensorState[i].iPort;
  } 
  
  return 0;
}

//==============================================================================
int COptoTrack::SetSensors( int nSensorsToSet, tSensorInfo * atSensorInfo ){
  int i;
  int iPortSensor, iPortSensorPrev;
  int iPort, iPortPrev;

  if( IsRunning() ) {
    CP_printf("Cannot set sensors. Tracker is active!\n");
    return 1;
  }

  if( nSensorsToSet < 1 || nSensorsToSet > N_SENSORS_MAX ){
    CP_printf("Cannot set sensors. Number of sensors is out of range: %d\n", nSensorsToSet);
    return 1;
  }
  // reset to zero
  m_nSensorsToRead = 0;
  m_nSensorsToWrite = 0;
  ZeroMemory(m_atSensorState, sizeof(m_atSensorState) );


  iPortSensorPrev = -1;
  iPortPrev = -1;
  for( i = 0; i < nSensorsToSet; i++) {
    iPort = atSensorInfo[i].iPort;
    if( iPort < iPortPrev ) {
      CP_printf("Cannot set sensors. Ports should be ordered.\n");
      return 1;
    }
    if( iPort > iPortPrev ) {
      iPortSensorPrev = -1;
    }
    iPortSensor = atSensorInfo[i].iSensor;  // incoming sensors start from 0
    if( iPortSensor <= iPortSensorPrev ) {
      CP_printf("Cannot set sensors. Sensors should be ordered.\n");
      return 1;
    }
    // Check sensor for valid range
    if( iPortSensor < 0 || iPortSensor >= N_SENSORS_AT_PORT_MAX ){
      CP_printf("Cannot set sensors. Sensor out of range: %d\n", iPortSensor );
      return 1;
    }
    iPortSensorPrev = iPortSensor;
    m_atSensorState[i].iSensor = iPortSensor;
    m_atSensorState[i].iPort = iPort;
  }  


  // Optotrak cannot setup sensors individually. If we want say
  // sensor #3 at port #2 we need to include sensors #1,#2, and #3
  // So we mark #3 as useful and ignore the others
  // Calc N sensors at each port
  ZeroMemory(m_anSensorsPerPort, sizeof(m_anSensorsPerPort));

  // The settings are ordered by port/sensor, 
  // so in the sequence the last sensor for the port
  // has the largest sensor #
  for( i = 0; i<nSensorsToSet; i++){
    iPort = m_atSensorState[i].iPort;
    iPortSensor = m_atSensorState[i].iSensor;
    m_anSensorsPerPort[iPort] = iPortSensor+1;
  }
  
  // Mark sensors that should be saved
  ZeroMemory(m_aiWriteFlag, sizeof(m_aiWriteFlag));
  i = 0;
  for( iPort = 0; iPort < N_PORTS; iPort++ ){
    for( iPortSensor = 0; iPortSensor<m_anSensorsPerPort[iPort]; iPortSensor++){
      if( (m_atSensorState[i].iPort == iPort) && 
        (m_atSensorState[i].iSensor == iPortSensor) ){
         m_aiWriteFlag[i] = 1;
      }
      i++;
    }
  }
  
  m_nSensorsToRead = i;
  m_nSensorsToWrite = nSensorsToSet;
  CP_printf("Sensors set:\n");
  for( i = 0; i<nSensorsToSet; i++){
    CP_printf("Port: %d, Sensor: %d\n", 
               m_atSensorState[i].iPort+1, m_atSensorState[i].iSensor+1);
  }
  CP_printf("Total %d (%d) sensors to acquire.\n", m_nSensorsToWrite, m_nSensorsToRead );
  
  return 0;
}

//==============================================================================
int COptoTrack::ActivateSensors(  ){
  int iErr;

  if( !IsRunning()) {
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
int COptoTrack::DeactivateSensors(  ){
  int iErr;

  if( !IsRunning()) {
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
//==============================================================================
int COptoTrack::GetSensorsTransformIdx( int * piTransformIdx ){

  int i;
  
  for( i = 0; i < m_nSensorsToWrite; i++ ){
    piTransformIdx[i] = m_atSensorState[i].iTransformIdx;
  } 

  return 0;
} 

//==============================================================================
int COptoTrack::SetSensorsTransformIdx(  int nSensors, int * piTransformIdx ){

  int i, iTrans;

  if( nSensors < m_nSensorsToWrite ){
    CP_printf("\nError: wrong input number of sensors: %d", nSensors);
    CP_printf("      Should be: %d\n", m_nSensorsToWrite);
    return 1;
  }

  // we allow input longer than actual m_nSensorsToWrite
  // it's a hack to set a single sensor transform idx
  // Matlab will not send a single number as a SAFEARRAY
  if( nSensors > m_nSensorsToWrite ){
    CP_printf("\nWarning: wrong input number of sensors: %d", nSensors);
    CP_printf("      Using first %d values.\n", m_nSensorsToWrite);
  }

  for( i = 0; i < m_nSensorsToWrite; i++ ){
    iTrans = piTransformIdx[i]; 
    // Check transform for valid range
    if( iTrans < 0 || iTrans >= N_TRANSFORMS ){
      CP_printf("\nCannot set transform. Transfrom index out of range: %d\n", iTrans );
      return 1;
    }
  } 

  for( i = 0; i < m_nSensorsToWrite; i++ ){
    m_atSensorState[i].iTransformIdx = piTransformIdx[i];
  } 
  
  return 0;
} 
  
//==============================================================================
int COptoTrack::GetN_Sensors( int * piDeviceMax, 
                                 int * piDeviceActive ){

  *piDeviceMax = N_SENSORS_MAX;
  *piDeviceActive = m_nSensorsToWrite;

  return 0;
} 
  
//==============================================================================
int COptoTrack::ConnectOpto(  ){
  BOOL bRes;
  int iErr;
  int iFrameSize;
  int iAttempt, nAttempts;

  CP_printf("Connecting to OptoTrak...\n");
  if( IsRunning() ) {
    CP_printf("  OptoTrak is already connected!\n");
    return 1;
  }

  m_iReadCount = 0;
  m_iOptoFrameIdx = 0;
  m_iPrevFrame = 0;
  m_nMissedTimes = 0;
  m_nMissedFrames = 0;


  // Make several attempts to load system. If OptoTrack was just
  // turned on, first attempt is unsuccessful
  nAttempts = 2;
  iErr = 1;  // we exit the loop when iErr==0
  for( iAttempt = 0; iAttempt < nAttempts && iErr;  iAttempt++ ){
    // Load OptoTrack transputers with system software
    CP_printf("TransputerLoadSystem() Attempt %d of %d\n", iAttempt+1, nAttempts);
    iErr = TransputerLoadSystem( "system" );
    Sleep( 1000 ); // Wait one second to let the system finish loading.
  }
  if( iErr )  {
    CP_printf("Error: %d attempts of TransputerLoadSystem() failed!\n", iAttempt);
    m_PrintOptoError( iErr );
    CP_printf("Make sure that both OptoTrak modules are turned on.\n");
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
  iFrameSize = sizeof(tOptoFrame) * m_nSensorsToWrite;
  bRes = SetBuffer( iFrameSize, // Item size
                    int(BUFFER_SIZE_SECONDS * FRAME_RATE_HZ) );   // N items
  if( !bRes ) {
    CP_printf("Error: SetBuffer() failed!\n");
    iErr = 1;
    goto errExit;
  }

//  CP_printf("Raw frame size: %d \n\n", sizeof(tOptoFrame));


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

  // Start the thread
  if( m_StartReadingThread( )) {
    CP_printf("Error: m_StartReadingThread() failed!\n");
    iErr = 1;
    goto errExit;
  }

  CP_printf("Connected!\n");
  return 0;

errExit:
    DisconnectOpto();
    return iErr;
}

//==============================================================================
int COptoTrack::DisconnectOpto(){

  int iSensor;
  if( !IsRunning() ) {
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

  // Set signal level indicator to OFF
  for(iSensor =0; iSensor < N_SENSORS_MAX; iSensor++)
    m_iDistirtionLevel[iSensor]= ecSensorOff;

  CP_printf("Opto disconnected.\n");
  CP_printf("Collected %d frames.\n", m_iReadCount);
  CP_printf("Last frame index from OptotTrak:  %d\n", m_iOptoFrameIdx);
  CP_printf("Number of missed frames: %d\n", m_nMissedFrames);
  CP_printf("Number of missed times: %d\n", m_nMissedTimes);
  
  CP_printf("++++++++++++++++++++++++++++++++++++++\n");

  return 0;
}

//===========================================================================
int COptoTrack::ParseBuffer(int iSensorIdx,
                            int nFrames,
                            void * pvSrcBuffer,
                            double * pdTimeStamps, 
                            tdXYZ * pdCoordinates,
                            tdXYZ * pdVelocities  ){

  tOptoFrame * ptFrame;
  int iFrame, iSensor, iTrans;


  ptFrame = (tOptoFrame *) pvSrcBuffer;
  for( iFrame = 0; iFrame < nFrames; iFrame++ ) {
    for (iSensor = 0; iSensor < m_nSensorsToWrite; iSensor++){

      if(iSensor == iSensorIdx){
        m_CalcTime(ptFrame->iFrameIdx, pdTimeStamps++);
        iTrans = m_atSensorState[iSensor].iTransformIdx;
        m_TransformCoordinates( iTrans, &ptFrame->tfCoord, pdCoordinates++); // coordinates
        ZeroMemory(pdVelocities++, sizeof(tdXYZ));
      }
      ptFrame++;
    }
  }

  return 0;
}
//===========================================================================
int COptoTrack::ParseBuffer(int nFrames,
                            void * pvSrcBuffer,
                            double * pdTimeStamps, 
                            tdXYZ * pdCoordinates,
                            tdXYZ * pdVelocities  ){

  tOptoFrame * ptFrame;
  int iFrame, iSensor, iTrans;


  ptFrame = (tOptoFrame *) pvSrcBuffer;
  for( iFrame = 0; iFrame < nFrames; iFrame++ ) {
    m_CalcTime(ptFrame->iFrameIdx, pdTimeStamps++);
    for (iSensor = 0; iSensor < m_nSensorsToWrite; iSensor++){
      iTrans = m_atSensorState[iSensor].iTransformIdx;
      m_TransformCoordinates( iTrans, &ptFrame->tfCoord, pdCoordinates++);  // coordinates 
      ZeroMemory(pdVelocities++, sizeof(tdXYZ));
      ptFrame++;
    }
  }

  return 0;
}

//==============================================================================
void COptoTrack::m_TransformCoordinates( int iTrans, 
                                            tfXYZ * ptInXYZ,   
                                            tdXYZ * ptOutXYZ ){

  ptOutXYZ->X = 
      m_atTransformMtx[iTrans][0][0] * ptInXYZ->X + 
      m_atTransformMtx[iTrans][0][1] * ptInXYZ->Y +
      m_atTransformMtx[iTrans][0][2] * ptInXYZ->Z +
      m_atTransformMtx[iTrans][0][3];     // X0

  ptOutXYZ->Y = 
      m_atTransformMtx[iTrans][1][0] * ptInXYZ->X + 
      m_atTransformMtx[iTrans][1][1] * ptInXYZ->Y +
      m_atTransformMtx[iTrans][1][2] * ptInXYZ->Z +
      m_atTransformMtx[iTrans][1][3];     // Y0

  ptOutXYZ->Z = 
      m_atTransformMtx[iTrans][2][0] * ptInXYZ->X + 
      m_atTransformMtx[iTrans][2][1] * ptInXYZ->Y +
      m_atTransformMtx[iTrans][2][2] * ptInXYZ->Z +
      m_atTransformMtx[iTrans][2][3];     // Z0

}

//===========================================================================
void COptoTrack::m_CalcTime( int iFrame, double * pdTimeMs){
  // Time calculation corresponds to the first frame having index 1
  // This way it is compatible with the frame counter hardware
  * pdTimeMs = (iFrame + 1) * m_dTimeC1 + m_dTimeC0;
}


//===========================================================================
int COptoTrack::ReadingFunc( ){
  unsigned int
    uFlags,
    uElements,
    uFrameNumber;
  int 
    iSensor, 
    iSensorWrite,
    nMissed;
  tfXYZ      atBufferXYZ[N_SENSORS_MAX];  // includes all sensors
  tOptoFrame atOptoFramesTmp[N_SENSORS_MAX];

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

//  CP_printf("Frame Number: %8u\r", uFrameNumber );

  nMissed = uFrameNumber - m_iPrevFrame - 1;
  if( nMissed && ( m_iReadCount > 1) ){
    m_nMissedTimes++;
    m_nMissedFrames += nMissed;
//    CP_printf("\nMissed frames:     %d     %d\n",  uFrameNumber,  nMissed);
  }
  
  // Parse the data, write into buffer
  iSensorWrite = 0;
  // go through all sensors which should be read
  for( iSensor = 0; iSensor < m_nSensorsToRead; iSensor++ ) {
    // save to the buffer if marked 
    if(m_aiWriteFlag[iSensor]){
      atOptoFramesTmp[iSensorWrite].iFrameIdx = uFrameNumber;
      //check for invalid data (enough to check just one coordinate)
      if(atBufferXYZ[iSensor].X < MAX_NEGATIVE) {  
      // Set all coordinates to bad float
        atOptoFramesTmp[iSensorWrite].tfCoord.X= BAD_FLOAT;
        atOptoFramesTmp[iSensorWrite].tfCoord.Y= BAD_FLOAT;
        atOptoFramesTmp[iSensorWrite].tfCoord.Z= BAD_FLOAT;
        atOptoFramesTmp[iSensorWrite].iDistortionLevel = ecHighDistortion;
        m_iDistirtionLevel[iSensorWrite] = ecHighDistortion;
      } // if bad data
      else {
        atOptoFramesTmp[iSensorWrite].tfCoord.X= atBufferXYZ[iSensor].X;
        atOptoFramesTmp[iSensorWrite].tfCoord.Y= atBufferXYZ[iSensor].Y;
        atOptoFramesTmp[iSensorWrite].tfCoord.Z= atBufferXYZ[iSensor].Z;
        atOptoFramesTmp[iSensorWrite].iDistortionLevel = ecNoDistortion;
        m_iDistirtionLevel[iSensorWrite] = ecNoDistortion;
      } // if not bad data
      iSensorWrite++;
    }  // if save to buffer
  } // for all sensors
  WriteData(atOptoFramesTmp, 1);  // save 1 item in the buffer
   

  m_iPrevFrame = uFrameNumber;
  m_iReadCount++;

  return 0;
}


//===========================================================================
int COptoTrack::ShutdownFunc( ){
  int iErr;

  // Shutdown the transputer message passing system.
  iErr = TransputerShutdownSystem();
  if( iErr ) {
    CP_printf("\nTransputerShutdownSystem() Failed!\n");
    return 1;
  }

  return 0;
}

//==============================================================================
int COptoTrack::m_PrintOptoError( int iError ){

  char szOptoError[MAX_OPTOERROR_LEN];

  if( OptotrakGetErrorString( szOptoError, MAX_OPTOERROR_LEN ) == 0 ) {
      CP_printfDbg(LEVEL_ERROR, "\n%s   Error: %d\n", szOptoError, iError );
  } 
  return 0;

}

