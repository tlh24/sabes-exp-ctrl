#include <windows.h>
#include <comdef.h>


#include "EyeTrack.h"
#include "EyeTrackGlob.h"
#include "CP_printf.h"
#include "PortTalkGrantIO.h"

#define LPT_BASE 0x378   // LPT1

#define LPT_CONTROL  (LPT_BASE + 2)

#define BIT_RESET_ON     0x00 
#define BIT_GATE_ON     0x01  
#define BIT_RESET_OFF   0x04  

#define RESET_ON       BIT_RESET_ON
#define GATE_ON       (BIT_RESET_OFF | BIT_GATE_ON)
#define GATE_OFF       BIT_RESET_OFF


#define HEADER_CHAR 0x44
#define HEADER_SHORT  0x4444

#define N_DATA_ITEMS 3
#define ISCAN_BUFFER_SIZE 100000   // number of items in the sliding buffer, about 1000 sec

#define N_COM_NAMES 10
char * x_aszComNames[N_COM_NAMES] = { "COM1", "COM2", "COM3", "COM4", "COM5", 
                                      "COM6", "COM7", "COM8", "COM9", "COM10"};

#define N_BAUD_RATES 8
int x_aiStdBaudRates[N_BAUD_RATES] = { 1200, 2400, 4800, 9600, 19200, 
                                       38400, 57600, 115200 };

#define ISCAN_FRAME_RATE_HZ 120.0
#define ISCAN_FRAME_MS     (1000.0/ISCAN_FRAME_RATE_HZ)


//==============================================================================
CEyeTrack::CEyeTrack(){

  m_iComPortIdx = 1;  //COM1
  m_iBaudRate = 57600; 
  m_iSerialParity = spNONE;

  iPortIO_Granted = 0;

  m_ReadCount = 0;
  m_iMissCount = 0;
  m_nMissedFrames = 0;
  m_iPrevFrame = 0;
  m_iReportSync = 0;

  m_dTimeC0 = 0;
  m_dTimeC1 = 1000.0/ISCAN_FRAME_RATE_HZ; 

  // Initialize to identity transform
  m_adTransformMatrix[0][0] = 0;
  m_adTransformMatrix[0][1] = 1;
  m_adTransformMatrix[0][2] = 0;
  m_adTransformMatrix[0][3] = 0;
  m_adTransformMatrix[0][4] = 0;
  m_adTransformMatrix[0][5] = 0;
  m_adTransformMatrix[1][0] = 0;
  m_adTransformMatrix[1][1] = 0;
  m_adTransformMatrix[1][2] = 1;
  m_adTransformMatrix[1][3] = 0;
  m_adTransformMatrix[1][4] = 0;
  m_adTransformMatrix[1][5] = 0;


}

//==============================================================================
CEyeTrack::~CEyeTrack(){
  DisconnectISCAN();
}

//==============================================================================
int CEyeTrack::ConnectISCAN(  ){
  int iRet;

  if( IsRunning() ) {
    CP_printf("Error in m_InitSerialThread()! Thread is already running.\n");
    return 1;
  }
  iRet = g_SysGrantIO( LPT_BASE );
  if( iRet ) {
    iPortIO_Granted = 0;
    printf("Error: Cannot grant I/O access, error: %d\n", iRet );
    return 1;
  }
 
  iPortIO_Granted = 1;
  PortOutput( LPT_CONTROL, RESET_ON);
  Sleep(1);
  PortOutput( LPT_CONTROL, GATE_OFF);
  Sleep(1);
  PortOutput( LPT_CONTROL, GATE_ON);


  CP_printf("Connecting to %s port\n", x_aszComNames[ m_iComPortIdx-1]);
  iRet = m_Serial.connect(x_aszComNames[ m_iComPortIdx-1], m_iBaudRate, m_iSerialParity);
  if(iRet) {
    CP_printf("Error in m_InitSerialThread, m_Serial.connect() failed\n");
    return 1;
  }

  m_ReadCount = 0;
  m_iMissCount = 0;
  m_nMissedFrames = 0;
  m_iPrevFrame = 0;
  m_iReportSync = 1;  // report next sync
  // Init sliding buffer
  SetBuffer(sizeof(IScanFrameStruct), ISCAN_BUFFER_SIZE);
  ResetBuffer();
  ResetTime();
  m_StartReadingThread( ); 
  if( !IsRunning() ) {
    CP_printf("Error in m_InitSerialThread()! CreateThread() failed.\n");
    PortOutput( LPT_CONTROL, GATE_OFF);
    RemoveBuffer();
    return 1;
  }
  CP_printf("Connected ISCAN\n");
  CP_printf("Expected number of parameters: %d\n", N_DATA_ITEMS);
  return 0;
}

//==============================================================================
int CEyeTrack::DisconnectISCAN(){


  if( iPortIO_Granted ) {
    PortOutput( LPT_CONTROL, GATE_OFF);
  }
  //Terminate thread
  m_StopReadingThread( 500 ); // thread stop time msec
  m_Serial.disconnect();
  RemoveBuffer();

  CP_printf("Disconnected ISCAN\n");

  return 0;
}

//==============================================================================
int CEyeTrack::GetVersion( BSTR * pbstVer){
  
  _bstr_t bscTmp(g_szVersion);
  *pbstVer =  bscTmp.copy();

  return 0;
}
//==============================================================================
int CEyeTrack::GetVersion( char ** pszVer){
  
  * pszVer = g_szVersion;
  return 0;
}

//==============================================================================
int CEyeTrack::GetTransformMatrix( double * pdMtx ){

  //      dest              src
  memcpy( pdMtx, m_adTransformMatrix, sizeof(m_adTransformMatrix)) ;
  return 0;
}

//==============================================================================
int CEyeTrack::SetTransformMatrix( double * pdMtx ){
  
  //      dest              src
  memcpy( m_adTransformMatrix, pdMtx, sizeof(m_adTransformMatrix)) ;
  return 0;
}

//==============================================================================
int CEyeTrack::GetTimeScale( double *pdC0, double *pdC1){

  *pdC0 = m_dTimeC0;
  *pdC1 = m_dTimeC1;

  return 0;
}

//==============================================================================
int CEyeTrack::SetTimeScale( double dC0, double dC1){

  m_dTimeC0 = dC0;
  m_dTimeC1 = dC1;

  return 0;
}
//===========================================================================
int CEyeTrack::SetBaudRate( int iRate ){
  int i;

  if( IsRunning() ) {
    CP_printf( "Error: Cannot change COM port baud rate while COM is active.\n"); 
    return 1;
  }
  // Check if the baud rate is valid
  for(i=0; i<N_BAUD_RATES; i++) {
    if ( x_aiStdBaudRates[i] == iRate) goto ExitSuccess;
  }
  
  CP_printf( "Error: Invalid COM port baud rate: %d\n", iRate); 
  return 3;

ExitSuccess:
  m_iBaudRate = iRate;
  return 0;
}

//===========================================================================
int CEyeTrack::GetBaudRate( int * piRate ){

  * piRate = m_iBaudRate;
  return 0;
}

//===========================================================================
int CEyeTrack::SetComPort( int iPortIdx){

  if( IsRunning() ) {
    CP_printf( "Error: Cannot change COM port index while COM is active.\n"); 
    return 1;
  }
  if( iPortIdx < 1 || iPortIdx > N_COM_NAMES ){
    CP_printf( "Error: Invalid COM port index: %d\n", iPortIdx); 
    return 2;
  }

  m_iComPortIdx = iPortIdx;

  return 0;
}

//===========================================================================
int CEyeTrack::GetComPort( int * piPortIdx ){

  * piPortIdx = m_iComPortIdx;
  return 0;
}


//==============================================================================
int CEyeTrack::TransformCoordinates( double dX_Raw, double dY_Raw, double * pdX_t, double * pdY_t ){

  double dRawMtx[TRANSF_MTX_N_2];
  int j;
  double dX, dY;

  dRawMtx[0] = 1;
  dRawMtx[1] = dX_Raw;
  dRawMtx[2] = dY_Raw;
  dRawMtx[3] = dX_Raw * dX_Raw;
  dRawMtx[4] = dX_Raw * dY_Raw;
  dRawMtx[5] = dY_Raw * dY_Raw;

  dX = 0; dY = 0;
  for(j = 0; j< TRANSF_MTX_N_2; j++ ) {
    dX += dRawMtx[j] * m_adTransformMatrix[0][j];
    dY += dRawMtx[j] * m_adTransformMatrix[1][j];
  }
  * pdX_t = dX;
  * pdY_t = dY;

  return 0;
}

//===========================================================================
void CEyeTrack::CalcTime( int iFrame, double * pdTimeMs){

  * pdTimeMs = iFrame * m_dTimeC1 + m_dTimeC0;
}

//===========================================================================
int CEyeTrack::ParseBuffer( int nFrames,
                             void * pvSrcBuffer,
                             double * pdTimeStamps, 
                             double * pdCoord ){

  IScanFrameStruct * pFrame;
  int i;
  double dRawX, dRawY, dX, dY;

  pFrame = (IScanFrameStruct *) pvSrcBuffer;
  for( i = 0; i < nFrames; i++ ) {

    CalcTime( pFrame->iFrame, pdTimeStamps);
    pdTimeStamps++;

    dRawX = pFrame->iRawX;;
    dRawY = pFrame->iRawY;
    TransformCoordinates( dRawX, dRawY, &dX, &dY );
    *pdCoord++ = dX;
    *pdCoord++ = dY;

    pFrame++;
  }

  return 0;
}

//===========================================================================
void CEyeTrack::GetMissedCount( int * pnMissed, int * piMissCount){
  * pnMissed = m_nMissedFrames;
  * piMissCount = m_iMissCount;
}

//===========================================================================
// wait for 2 sync chars in a row
int CEyeTrack::m_WaitForSync( ){
  char chIn;
  int nChars, nRead, nTimeouts;


  nChars = 0;
  nTimeouts = 0;
  while( TRUE ) {
    // wait for the first header byte  
    do { 
      chIn = 0;  // in case of time-out, chIn is not changed
      nRead = m_Serial.getArray( &chIn, 1 );
      if( !IsActive() ) return 1;  // exit check
      if( nRead == 0)  nTimeouts++;
      nChars += nRead;
    } while( chIn != HEADER_CHAR);
    // get next char and check if it's header
    chIn = 0;  // in case of time-out, chIn is not changed
    nRead = m_Serial.getArray( &chIn, 1 );
    if( !IsActive() ) return 1;  // exit check
    nChars += nRead;
    if( nRead == 0)  nTimeouts++;
    if( (nRead == 1) && (chIn == HEADER_CHAR)) {
      if( m_iReportSync) {   
        CP_printf("\nFound serial sync:    %d chars,     %d timeouts \n", nChars, nTimeouts);
      }
      return 0;   // got 2 sync chars in a row
    }
  }

  return 0;  // not used
}

//===========================================================================
// item is a short (2 bytes)
int CEyeTrack::m_ReadDataItem( int * piItem ){
  int nRead;
  short shtItem;
  
  *piItem = 0;

  nRead = m_Serial.getArray( (char *)&shtItem, sizeof(shtItem) );
  if( !IsActive() ) return 1;  // exit check
  if( nRead != sizeof(shtItem)) {
    CP_printf("\nTimeout in  m_ReadDataItem()\n");
    return 2;
  }
  if(shtItem == HEADER_SHORT) {
    CP_printf("\nData length mismatch in m_ReadDataItem()\n");
    return 3;   // actuall number of items is shorter?
  }
  *piItem = shtItem;

  return 0;
}

//===========================================================================
int CEyeTrack::m_WriteData( int * piItems, int nItems ){
  IScanFrameStruct isdTmp;
  int iFrame, iDigIn, nMissed;

  isdTmp.dLocalTimeMs = TimeStampMs();
  isdTmp.iRawX = piItems[0];
  isdTmp.iRawY = piItems[1]; 
  if( nItems > 2 ) {
    // for some reason the data in ISCAN serial output are multiplied by 10
    iDigIn = ( piItems[2]/10 ); 
    // use all but the last 4 bits of the previous frame, last 4 bits are taken from iDigIn
    iFrame = (m_iPrevFrame & 0xFFFFFFF0) + iDigIn;
    if( iFrame < m_iPrevFrame ) iFrame += 0x10;
    if( iFrame == m_iPrevFrame ) { // no frame input on DigIn ?
      nMissed = 0;  
    }
    else {
      nMissed = iFrame - m_iPrevFrame -1;
    }
    if( nMissed ){
      m_iMissCount++;
      m_nMissedFrames += nMissed;
    }
    isdTmp.iFrame = iFrame;  
    m_iPrevFrame = iFrame;

  }
  else {
    isdTmp.iFrame = 0;  
  }

  // save values into the buffer
  WriteData(&isdTmp, 1);
  m_ReadCount++;

  return 0;
}

//===========================================================================
int CEyeTrack::ReadingFunc( ){
  int iErr, iItem;
  int aiData[N_DATA_ITEMS];  
  
  iErr = m_WaitForSync();
  if( iErr) goto LoopExit;  // exit check
  for( iItem=0; iItem<N_DATA_ITEMS; iItem++) {
    iErr = m_ReadDataItem( &aiData[iItem]);
    if( !IsActive()) goto LoopExit;  // exit check
    if( iErr) break;
  }

  if( iErr ) {
    m_iReportSync = 1;  // report next sync
  }
  else {
    m_WriteData( aiData, N_DATA_ITEMS );
    m_iReportSync = 0;  // don't report next sync

  }

LoopExit:
  return 0;
}

//===========================================================================
int CEyeTrack::ShutdownFunc( ){
  return 0;
}
