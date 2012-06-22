#include <windows.h>
#include <comdef.h>


#include "LibertyTrack.h"
#include "LibertyTrackGlob.h"
#include "CP_printf.h"

// the first marked frame should have index less than MAX_START_FRAME
// if it's bigger, we ignore it and keep waiting
#define MAX_START_FRAME  50   

// The object pointer, we have only one
CLibertyTrack * g_pLibertyTrack = NULL;


//==============================================================================
CLibertyTrack::CLibertyTrack(){
  int iTrans, i;

  m_IsConnected = 0;
  m_iIsRunning = 0;
  m_iLibertyFrameIdx = 0;
  m_iFirstFrameIdx = 0;
  m_iPrevFrame = 0;
  m_nMarkedFrames = 0;
  m_nMissedTimes = 0;
  m_nMissedFrames = 0;
  m_nSensorsMax = 0;
  m_dTimeC0 = 0;
  m_dTimeC1 = 1000.0/FRAME_RATE_HZ;


  ZeroMemory(m_atSensorState, sizeof(m_atSensorState) );
  // default: active sensor #1
  m_atSensorState[0].iSensor = 0;
  m_atSensorState[1].iSensor = 1;
  m_atSensorState[2].iSensor = 2;
  m_atSensorState[3].iSensor = 3;
  m_nActiveSensors = 1;

  // Set signal level indicator to OFF
  for(i =0; i < N_SENSORS_MAX; i++)
    m_iDistirtionLevel[i]= ecSensorOff;

  // Configure Liberty data request
  m_SensorDataList.Empty();
  m_SensorDataList.Append( PDI_MODATA_FRAMECOUNT );
  m_SensorDataList.Append( PDI_MODATA_TIMESTAMP );
  m_SensorDataList.Append( PDI_MODATA_EXTSYNC );
  m_SensorDataList.Append( PDI_MODATA_DISTLEV );
  m_SensorDataList.Append( PDI_MODATA_POS );
  m_SensorDataList.Append( PDI_MODATA_ORI );


  // Swap X and Z axes , invert Y axis,
  // convert from cm to mm
  for( iTrans = 0; iTrans<N_TRANSFORMS; iTrans++ ) {
    m_atTransformMtx[iTrans][0][0] = 0;     // X to X'
    m_atTransformMtx[iTrans][0][1] = 0;     // Y to X'
    m_atTransformMtx[iTrans][0][2] = 10;    // Z to X'
    m_atTransformMtx[iTrans][0][3] = 0;     // X0
    m_atTransformMtx[iTrans][1][0] = 0;     // X to Y'
    m_atTransformMtx[iTrans][1][1] = -10;   // Y to Y'
    m_atTransformMtx[iTrans][1][2] = 0;     // Z to Y'
    m_atTransformMtx[iTrans][1][3] = 0;     // Y0
    m_atTransformMtx[iTrans][2][0] = 10;    // X to Z'
    m_atTransformMtx[iTrans][2][1] = 0;     // Y to Z'
    m_atTransformMtx[iTrans][2][2] = 0;     // Z to Z'
    m_atTransformMtx[iTrans][2][3] = 0;     // Z0
  }

}

//==============================================================================
CLibertyTrack::~CLibertyTrack(){
  //TODO: Check state and unwind if necessary
  if( m_IsConnected ) FinishAndDisconnect();
}

//==============================================================================
int CLibertyTrack::GetVersion( BSTR * pbstVer){
  
  _bstr_t bscTmp(g_szVersion);
  *pbstVer =  bscTmp.copy();

  return 0;
}
//==============================================================================
int CLibertyTrack::GetVersion( char ** pszVer){
  
  * pszVer = g_szVersion;
  return 0;
}

//==============================================================================
int CLibertyTrack::GetLibertyState( int * piState ){
  
  *piState = m_IsConnected + m_iIsRunning * 2;
 
  return 0;
}

//==============================================================================
int CLibertyTrack::GetLibertyResult( char ** pszResult, int * piResult  ){
  
  * pszResult = (char *) m_PdiDev.GetLastResultStr();
  * piResult = m_PdiDev.GetLastResult();
  return 0;
}

//==============================================================================
int CLibertyTrack::GetSignalDistortion( int aiDistortion[N_SENSORS_MAX] ){
  int i;

  for(i =0; i < N_SENSORS_MAX; i++)
    aiDistortion[i] = m_iDistirtionLevel[i];

  return 0;
}

//==============================================================================
int CLibertyTrack::GetTransformMatrix( int iTransform, float * pfMtx ){

  if( iTransform < 0 || iTransform >= N_TRANSFORMS) return 1;
  //      dest              src
  memcpy( pfMtx, m_atTransformMtx[iTransform], sizeof(tTransformMtx)) ;
  return 0;
}

//==============================================================================
int CLibertyTrack::GetTransformMatrix( int iTransform, double * pdMtx ){
 
  int i;
  float  * pfMtx;

  if( iTransform < 0 || iTransform >= N_TRANSFORMS) return 1;

  pfMtx = (float *) m_atTransformMtx[iTransform];
  for(i = 0; i < TRANSFORM_N_I*TRANSFORM_N_J; i++)
    *pdMtx++ = (double) *pfMtx++;

  return 0;
}

//==============================================================================
int CLibertyTrack::SetTransformMatrix( int iTransform, float * pfMtx ){
  
  if( iTransform < 0 || iTransform >= N_TRANSFORMS) return 1;
  //      dest              src
  memcpy( m_atTransformMtx[iTransform], pfMtx, sizeof(tTransformMtx)) ;
  return 0;
}

//==============================================================================
int CLibertyTrack::SetTransformMatrix( int iTransform, double * pdMtx ){
  int i;
  float  * pfMtx;

  if( iTransform < 0 || iTransform >= N_TRANSFORMS) return 1;

  pfMtx = (float *) m_atTransformMtx[iTransform];
  for(i = 0; i < TRANSFORM_N_I*TRANSFORM_N_J; i++)
    *pfMtx++ = (float) *pdMtx++;

  return 0;
}
//==============================================================================
int CLibertyTrack::GetTimeScale( double *pdC0, double *pdC1){

  *pdC0 = m_dTimeC0;
  *pdC1 = m_dTimeC1;

  return 0;
}

//==============================================================================
int CLibertyTrack::SetTimeScale( double dC0, double dC1){

  m_dTimeC0 = dC0;
  m_dTimeC1 = dC1;

  return 0;
}
//==============================================================================
int CLibertyTrack::GetSensors( tSensorInfo * atSensorInfo ){
  int i;
  
  for( i = 0; i < m_nActiveSensors; i++ ){
    atSensorInfo[i].iSensor = m_atSensorState[i].iSensor;
    atSensorInfo[i].iPort = 0;
  } 
  
  return 0;
}

//==============================================================================
int CLibertyTrack::SetSensors( int nSensors, tSensorInfo * atSensorInfo ){
  int i;
  int iSensor;
  int iSensorPrev;

  if( m_IsConnected ) {
    CP_printf("Cannot set sensors. Tracker is active!\n");
    return 1;
  }

  if( nSensors < 0 || nSensors > N_SENSORS_MAX ){
    CP_printf("Cannot set sensors. Number of sensors is out of range: %d\n", nSensors);
    return 1;
  }
  // reset to zero
  ZeroMemory(m_atSensorState, sizeof(m_atSensorState) );
  m_nActiveSensors = 0;

  iSensorPrev = -1;
  for( i = 0; i < nSensors; i++) {
    iSensor = atSensorInfo[i].iSensor;  // incoming sensors start from 0
    if( iSensor <= iSensorPrev ) {
      CP_printf("Cannot set sensors. Sensors should be ordered.\n");
      return 1;
    }
    // Check sensor for valid range
    if( iSensor < 0 || iSensor >= N_SENSORS_MAX ){
      CP_printf("Cannot set sensors. Sensor out of range: %d\n", iSensor );
      return 1;
    }
    iSensorPrev = iSensor;
    m_atSensorState[i].iSensor = iSensor;
  }  

  m_nActiveSensors = nSensors;
  CP_printf("Total %d sensors to acquire.\n", m_nActiveSensors );
  
  return 0;
}

//==============================================================================
int CLibertyTrack::GetSensorsTransformIdx( int * piTransformIdx ){

  int i;
  
  for( i = 0; i < m_nActiveSensors; i++ ){
    piTransformIdx[i] = m_atSensorState[i].iTransformIdx;
  } 

  return 0;
} 

//==============================================================================
int CLibertyTrack::SetSensorsTransformIdx(  int nSensors, int * piTransformIdx ){

  int i, iTrans;

  if( nSensors < m_nActiveSensors ){
    CP_printf("\nWarning: wrong input number of sensors: %d", nSensors);
    CP_printf("      Should be: %d\n", m_nActiveSensors);
    return 1;
  }

  // we allow input longer than actual m_nActiveSensors
  // it's a hack to set a single sensor transform idx
  // Matlab will not send a single number as a SAFEARRAY
  if( nSensors > m_nActiveSensors ){
    CP_printf("\nWarning: wrong input number of sensors: %d", nSensors);
    CP_printf("      Using first %d values.\n", m_nActiveSensors);
  }

  for( i = 0; i < m_nActiveSensors; i++ ){
    iTrans = piTransformIdx[i]; 
    // Check transform for valid range
    if( iTrans < 0 || iTrans >= N_TRANSFORMS ){
      CP_printf("\nCannot set transform. Transfrom index out of range: %d\n", iTrans );
      return 1;
    }
  } 

  for( i = 0; i < m_nActiveSensors; i++ ){
    m_atSensorState[i].iTransformIdx = piTransformIdx[i];
  } 
  
  return 0;
} 
  
//==============================================================================
int CLibertyTrack::GetN_Sensors( int * piDeviceMax, 
                                 int * piDeviceActive ){

  *piDeviceMax = m_nSensorsMax;
  *piDeviceActive = m_nActiveSensors;

  return 0;
} 
  
//==============================================================================
int CLibertyTrack::ConnectLiberty(  ){
  BOOL bRes;
  int iError = 0;
  LPCSTR szWhoAmI = NULL;
  int i;
  DWORD dwStationMap;
  int iBitMask;


  CP_printf("ConnectLiberty...");
  if( m_IsConnected ) {
    CP_printf(" Liberty is already connected!\n");
    return 1;
  }
  bRes = m_PdiDev.ConnectUSB ( ); 
  if( !bRes ) {
    CP_printf(" Failed!\n");
    return 2;
  }
  CP_printf(" Ok!\n");
  m_iLibertyFrameIdx = 0;
  m_iFirstFrameIdx = 0;
  m_iPrevFrame = 0;   
  m_nMarkedFrames = 0;
  m_nMissedTimes = 0;
  m_nMissedFrames = 0;
  m_IsConnected = 1;

  bRes = m_PdiDev.WhoAmI ( szWhoAmI ); 
  CP_printf("=========== Liberty info =============");
  CP_printf("%s", szWhoAmI);
  CP_printf("======================================\n");

  
  bRes = m_PdiDev.SetBinary( TRUE );  // Set binary mode
  bRes = m_PdiDev.SetMetric( TRUE );  // Set metric units (cm)
  bRes = m_PdiDev.SetFrameRate( PI_FRATE_240 ); // 240 Hz
// TODO: ?? BOOL SetSourceFrame ( const PDIori & ); // rotate ref. frame

  m_nSensorsMax = m_PdiDev.MaxSensors();
  CP_printf("Max number of sensors:  %d\n", m_nSensorsMax);
  
  // setup bitmask for requested sensors
  dwStationMap = 0;
  for( i = 0; i<m_nActiveSensors; i++ ) {
    iBitMask = 1 << m_atSensorState[i].iSensor;
    dwStationMap |= iBitMask;
  }
  // Enable/disable sensors specified dy the bits
  bRes = m_PdiDev.SetStationMap ( dwStationMap ); 

  // Check actual active sensors
  bRes = m_PdiDev.GetStationMap ( dwStationMap ); 

  // Determine which sensors have been actually activated
  // Get the number of active sensors
  // Warn if a requested sensor was not activated
  for( i = 0; i<m_nActiveSensors; i++ ) {
    iBitMask = 1 << m_atSensorState[i].iSensor;
    if( !(dwStationMap & iBitMask) ) {
      m_PdiDev.SetStationMap ( 0 ); // disable all sensors
      CP_printf("Error: no active sensors found!\n");
      iError = 4;
      goto errExit;
    }
  }

  CP_printf("Number of active sensors: %d \n", m_nActiveSensors);
  CP_printf("List of active sensors:   ");
  for( i = 0; i<m_nActiveSensors; i++ ) {
    CP_printf("%d    ", m_atSensorState[i].iSensor +1);
  }
  CP_printf("\n");

  // Set default signal level to OFF
  for(i =0; i < N_SENSORS_MAX; i++)
    m_iDistirtionLevel[i]= ecSensorOff;

  // set output vars for ALL sensors
  bRes = m_PdiDev.SetSDataList ( -1, m_SensorDataList );

  // set data buffer
  bRes = m_PdiDev.SetPnoBuffer ( m_pPnoBuf, PNO_BUF_SIZE ); 

  // create sliding buffer
  bRes = SetBuffer( sizeof(tLibertyFrame) * m_nActiveSensors, // Item size
                    BUFFER_SIZE_SECONDS * FRAME_RATE_HZ );   // N items
  if( !bRes ) {
    CP_printf("Error: SetBuffer() failed!\n");
    iError = 5;
    goto errExit;
  }

//  CP_printf("Raw frame size: %d \n\n", sizeof(tLibertyFrame));


// SetAttFilter
// SetPosFilter

  // Boost application and thread priority
  // Note: if we set it too high, we might miss DCOM commands
  SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS ); 
//	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL );

  
  // Start cont. acquisition
  bRes = m_PdiDev.StartContPno( g_GetWindowHandle() );
  m_iIsRunning = 1;
  // Give PnO threads time to start, no calls to PDI during this time
  Sleep(100);  
  // Reset device counters
  bRes = m_PdiDev.ResetTimeStamp();
  bRes = m_PdiDev.ResetFrameCount();
  bRes = m_PdiDev.ResetHostFrameCount();

  Sleep(100);
  bRes = m_PdiDev.SetSyncEnabled ( TRUE ); // Enable output TTL sync 
  return 0;

errExit:
    m_DisconnectLiberty();
    return iError;
}

//==============================================================================
int CLibertyTrack::FinishAndDisconnect(){
  // Stop acquisition if needed
  if( m_iIsRunning ) {
    m_iIsRunning = 0;
  }
  else{
    CP_printf("Cannot disconnect Liberty: it is not connected.\n");
  }
  return 0;
}
//==============================================================================
int CLibertyTrack::m_DisconnectLiberty(){
  BOOL bRes;
  int i, nLibertyFrames;


  bRes = m_PdiDev.StopContPno( );

  // Return application and thread priority to normal
  SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS );
//	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_NORMAL );

  Sleep(200);  // 
  CP_printf("\n\nAcquisition stopped.\n");

  // release the buffers
  RemoveBuffer();

  if( !m_IsConnected ) {
    CP_printf("Error in m_DisconnectLiberty(): Liberty is not connected!\n");
    return 1;
  }
  bRes = m_PdiDev.Disconnect(); 
  if( !bRes ) {
    CP_printf("Error in m_DisconnectLiberty(). p->Disconnect() failed!\n");
    goto errExit;
  }

  // Set signal level indicator to OFF
  for(i =0; i < N_SENSORS_MAX; i++)
    m_iDistirtionLevel[i]= ecSensorOff;

  CP_printf("Liberty disconnected.\n");
  CP_printf("Collected %d frames.\n", m_nMarkedFrames);
  nLibertyFrames =  m_iLibertyFrameIdx - m_iFirstFrameIdx + 1;
  CP_printf("Number of Liberty frames: %d\n", nLibertyFrames);
  CP_printf("Number of missed frames (total): %d\n", nLibertyFrames - m_nMarkedFrames);
  CP_printf("Number of missed frames (incremental): %d\n", m_nMissedFrames);
  CP_printf("Number of missed times: %d\n", m_nMissedTimes);
  
  CP_printf("++++++++++++++++++++++++++++++++++++++\n");
  m_IsConnected = 0;
  return 0;

errExit: 
    m_IsConnected = 0;
    return 2;

}

//===========================================================================
int CLibertyTrack::ParseBuffer(int iSensorIdx,
                               int nFrames,
                               void * pvSrcBuffer,
                               double * pdTimeStamps, 
                               tdXYZ * pdCoordinates,
                               tdXYZ * pfVelocities  ){

  tLibertyFrame * ptFrame;
  int iFrame, iSensor, iTrans;


  ptFrame = (tLibertyFrame *) pvSrcBuffer;
  for( iFrame = 0; iFrame < nFrames; iFrame++ ) {
    for (iSensor = 0; iSensor < m_nActiveSensors; iSensor++){

      if(iSensor == iSensorIdx){
        m_CalcTime(ptFrame->uiFrameIdx, pdTimeStamps++);
        iTrans = m_atSensorState[iSensor].iTransformIdx;
        m_TransformCoordinates( iTrans, &ptFrame->tfCoord, pdCoordinates++); // coordinates
        m_TransformAngles(iTrans, &ptFrame->tfAngles, pdCoordinates++);   // angles
        ZeroMemory(pfVelocities++, sizeof(tdXYZ));
      }
      ptFrame++;
    }
  }

  return 0;
}
//===========================================================================
int CLibertyTrack::ParseBuffer(int nFrames,
                               void * pvSrcBuffer,
                               double * pdTimeStamps, 
                               tdXYZ * pdCoordinates,
                               tdXYZ * pfVelocities  ){

  tLibertyFrame * ptFrame;
  int iFrame, iSensor, iTrans;


  ptFrame = (tLibertyFrame *) pvSrcBuffer;
  for( iFrame = 0; iFrame < nFrames; iFrame++ ) {
    m_CalcTime(ptFrame->uiFrameIdx, pdTimeStamps++);
    for (iSensor = 0; iSensor < m_nActiveSensors; iSensor++){
      iTrans = m_atSensorState[iSensor].iTransformIdx;
      m_TransformCoordinates( iTrans, &ptFrame->tfCoord, pdCoordinates++);  // coordinates 
      m_TransformAngles(iTrans, &ptFrame->tfAngles, pdCoordinates++);   // angles
      ZeroMemory(pfVelocities++, sizeof(tdXYZ));
      ptFrame++;
    }
  }

  return 0;
}

//==============================================================================
void CLibertyTrack::m_TransformCoordinates( int iTrans, 
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

//==============================================================================
void CLibertyTrack::m_TransformAngles( int iTrans, 
                                            tfXYZ * ptInXYZ,   
                                            tdXYZ * ptOutXYZ ){

  //TODO: recalc angles using the transform
  ptOutXYZ->X = ptInXYZ->X;
  ptOutXYZ->Y = ptInXYZ->Y;
  ptOutXYZ->Z = ptInXYZ->Z;
  
}

//===========================================================================
void CLibertyTrack::m_CalcTime( int iFrame, double * pdTimeMs){
  // Time calculation corresponds to the first frame having index 1
  // This way it is compatible with the frame counter hardware
  * pdTimeMs = (iFrame - m_iFirstFrameIdx + 1) * m_dTimeC1 + m_dTimeC0;
}

//===========================================================================
void CLibertyTrack::OnNewData( CLibertyTrack * pLT, 
                                       WPARAM wParam, 
                                       LPARAM lParam ){
  PBYTE pBuf = (PBYTE)lParam;
  long lngN_Bytes = (DWORD)wParam;
  pLT->m_GetNewData( pBuf, lngN_Bytes); 

}

//===========================================================================
int CLibertyTrack::m_GetNewData( PBYTE pBuf, long lngN_Bytes){
  tLibertyFrame * pLibertyFrame;
  int nFrameSize;
  int i, iSensor;
  PBYTE  pBuffer;
  int  nBytes;
  int nMissed;

  pBuffer = pBuf;
  nBytes = lngN_Bytes;

  // for whatever reason we can get a frame of size 0 - catch that
  if(nBytes == 0) {
    CP_printf("\n\nWarning: zero-size frame at input.\n");
    return 0;
  }
  // check if the size is right
  nFrameSize = (int)sizeof(tLibertyFrame);
  if( nBytes != nFrameSize * m_nActiveSensors ){
    CP_printf("\n\nError! Data size mismatch:\n");
    CP_printf("Expected block size: %d   Actual block size: %d\n",  
                             nFrameSize * m_nActiveSensors, nBytes);
    CP_printf("Stopping acquisition.\n");
    m_DisconnectLiberty();
    return 2;
  }
  pLibertyFrame = (tLibertyFrame *) pBuffer;  // pointer to the first frame

  if(!m_iIsRunning) {  // no more marked frames, stop DAQ
    m_PdiDev.SetSyncEnabled ( FALSE ); // Disable output TTL sync 
    // if we have no more marked frames, stop DAQ, disconnect Liberty
    if( !pLibertyFrame->uiExternalSync ) {
      m_DisconnectLiberty();
    }
  }

  // We can get unmarked frames in the beginning, skip them
  if( !pLibertyFrame->uiExternalSync ) {
    return 0;
  }

  if( m_nMarkedFrames == 0 ) {
    // Sometimes there is a marked frame with large index in the very beginnig,
    // it probably comes from the old buffer, we have to skip it to avoid
    // negative number of missing frames on the next frame which has small index
    if( pLibertyFrame->uiFrameIdx > MAX_START_FRAME) {
      CP_printf("Spurious first frame index: %d   - skipping\n", m_iLibertyFrameIdx);
      return 0;
    }
    m_iFirstFrameIdx = pLibertyFrame->uiFrameIdx;
    CP_printf("First frame index: %d\n", m_iFirstFrameIdx);
  }
  m_nMarkedFrames++;

  // Check that the frames are consecutive
  m_iLibertyFrameIdx = pLibertyFrame->uiFrameIdx;
  nMissed = (m_iLibertyFrameIdx - m_iPrevFrame) -1;
  if( (nMissed != 0) && m_nMarkedFrames && (m_nMarkedFrames>1)) {
    CP_printf("\nN missed: %d\n", nMissed);
    m_nMissedFrames += nMissed;
    m_nMissedTimes++;
  }

  m_iPrevFrame = m_iLibertyFrameIdx;
  // Sanity check - is the data from the requested sensor?
  for( i = 0; i <  m_nActiveSensors; i++ ){
    iSensor = pLibertyFrame->bStation - 1;  // Stations are 1-based

    if( iSensor != m_atSensorState[i].iSensor ){
      CP_printf("\n\nError! sensor mismatch:\n");
      CP_printf("Expected: %d   Actual: %d\n", 
                          m_atSensorState[i].iSensor, iSensor);
      CP_printf("Stopping acquisition.\n");
      m_DisconnectLiberty();
      return 3;
    }
    
    m_iDistirtionLevel[i] = pLibertyFrame->uiDistortionLevel;
    pLibertyFrame++;
  }

  // Copy frames from Liberty buffer to the sliding buffer, 
  // all sensor frames in the Liberty buffer make one buffer item
  WriteData( (void*) pBuffer, 1);

//  if( (iFrame % 100) == 0 ){
//    CP_printf("%d     %d    \r",  iFrame, m_nMarkedFrames);
//  }
  return 0;
}

