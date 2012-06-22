// AtlAxWinInit is implemented in Atl.dll
#pragma comment(lib, "atl.lib")
#include <atldef.h>
//#define _ATL_DLL_IMPL
#include <atliface.h> 

#include "TDT_Stream.h"
//#include "Stream_Glob.h"
#include "CP_printf.h"


// Note: don't forget to change version in the IDL file!
char * x_szVersion = "CP TDT Stream: Ver 0.03\r\n\
July 7th, 2006\r\n\
by Sergei Rebrik <rebrik@phy.ucsf.edu>";

#define SZ_SAMP_COUNT ".iBufItemCnt"
#define SZ_BUF_SIZE ".iBufSize"
#define SZ_BUF_DATA ".dBufData"
#define SZ_BUF_IDX  ".iBufIdx"

#define MAX_BLOCK_SIZE_SAMPS 100000

CTDT_Stream * g_pTDT_Stream;
short x_asBuffer[MAX_BLOCK_SIZE_SAMPS];
VARIANT x_vrtRes;


//==============================================================================
CTDT_Stream::CTDT_Stream(){
  m_iState = ecStateCreated;
  m_pTDev = NULL;
  m_bscFilePath = "C:\\";
  m_bscFileName = "Delme.raw";
  m_bscTmpPath = m_bscFilePath;
  m_bscServerName = "Local";
  m_bscDeviceName = "RP2(1)";
  m_bscSampIdx= m_bscDeviceName + SZ_SAMP_COUNT;
  m_bscBuff= m_bscDeviceName + SZ_BUF_DATA;
  m_bscBufIdx =  m_bscDeviceName + SZ_BUF_IDX;
  m_iBufferSize = 0;
  m_iBlocksWritten = 0;
  m_iBlockSize = 0;
  m_iFileStartTick = 0;
  m_blnConvertToInt16 = 0;
}

//==============================================================================
CTDT_Stream::~CTDT_Stream(){
  //TODO: Check state and unwind if necessary
  Uninitialize();
}

//==============================================================================
int CTDT_Stream::Initialize( HWND hWnd ){

  IUnknown * pUnk;
  IUnknown * pUnkCont;
  HRESULT hRet;

  // Initialize ATL control containment code.
  AtlAxWinInit(); 
  // Create ActiveX control using the window handle 
  // and get the IUnknown interface of this control
  hRet = AtlAxCreateControlEx( OLESTR("TDevAcc.X"), hWnd, NULL, 
                                      &pUnkCont, &pUnk, IID_NULL, NULL );

  // Obtain smart pointer to TDevAccX using IUnknown of the control
  m_pTDev = pUnk;
  pUnk->Release();
  m_InitTimerThread();
  m_iState = ecInitialized;
  return 0;
}

//==============================================================================
int CTDT_Stream::ConnectServer(  ){
  HRESULT hRet;
  long lRes;
  //TODO: Check for success
  hRet = m_pTDev->raw_ConnectServer( m_bscServerName, &lRes );
  //TODO: Check for valid device name here 
  hRet = m_pTDev->raw_GetDeviceStatus( m_bscDeviceName, &lRes );
  CP_printf("Connected to TDT server: %s\n", (char *) m_bscServerName);
  m_iState = ecStateIdle;
  return 0;
}

//==============================================================================
int CTDT_Stream::DisconnectServer(){
  HRESULT hRet;

  hRet = m_pTDev->raw_CloseConnection( );
  CP_printf("Disconnected from TDT server\n");

  m_iState = ecInitialized;
  return 0;
}

//==============================================================================
int CTDT_Stream::SetFileName( BSTR bstName ){

  m_bscFileName = bstName;
  return 0;
}
//==============================================================================
int CTDT_Stream::GetFileName( BSTR  * pbstName ){

  *pbstName =  m_bscFileName.copy();
  return 0;
}
//==============================================================================
int CTDT_Stream::SetServerName( BSTR bscName ){

  m_bscServerName = bscName;
  return 0;
}
//==============================================================================
int CTDT_Stream::GetServerName( BSTR * pbscName ){

  *pbscName =  m_bscServerName.copy();
  return 0;
}
//==============================================================================
int CTDT_Stream::SetDeviceName( BSTR bscName ){

  m_bscDeviceName = bscName;
  return 0;
}
//==============================================================================
int CTDT_Stream::GetDeviceName( BSTR * pbscName ){

  *pbscName =  m_bscDeviceName.copy();
  return 0;
}
//==============================================================================
int CTDT_Stream::GetSystemMode( int * piMode ){
  HRESULT hRet;
  long lRes;

  hRet = m_pTDev->raw_GetSysMode(&lRes);
  *piMode = lRes;
  return 0;
}
//==============================================================================
int CTDT_Stream::SetBlockSize( int iSize ){

  m_iBlockSize = iSize;
  return 0;
}
//==============================================================================
int CTDT_Stream::GetBlockSize( int * piSize ){

  *piSize = m_iBlockSize;
  return 0;
}
//==============================================================================
int CTDT_Stream::SetBufferSize( int iSize ){
  HRESULT hRet;
  long lRes;
  double dVal;
  _bstr_t bscTarget;

//  SetTargetVal(Target As String, Val As Double) As Long
  bscTarget = m_bscDeviceName + SZ_BUF_SIZE;  //
  dVal = (double)iSize;
  hRet = m_pTDev->raw_SetTargetVal(bscTarget, dVal, &lRes);
  m_iBufferSize = iSize;
  return 0;
}
//==============================================================================
int CTDT_Stream::GetBufferSize( int * piSize ){
  HRESULT hRet;
  double dVal;
  _bstr_t bscTarget;

  bscTarget = m_bscDeviceName + SZ_BUF_SIZE;  //
  hRet = m_pTDev->raw_GetTargetVal(bscTarget, &dVal);
  *piSize = (int)dVal;
  return 0;
}

//==============================================================================
int CTDT_Stream::GetSampRateHz( float * pfRateHz ){
  HRESULT hRet;

  hRet = m_pTDev->raw_GetDeviceSF(m_bscDeviceName, pfRateHz);
  return 0;
}

//==============================================================================
int CTDT_Stream::GetVersion( BSTR * pbstVer){
  
  _bstr_t bscTmp(x_szVersion);
  *pbstVer =  bscTmp.copy();

  return 0;
}
//==============================================================================
int CTDT_Stream::GetVersion( char ** pszVer){
  
  * pszVer = x_szVersion;
  return 0;
}

//==============================================================================
int CTDT_Stream::Uninitialize(){
  m_CloseTimerThread();
  m_pTDev = NULL; // release the smart pointer object
  m_iState = ecStateCreated;
  return 0;
}


//==============================================================================
int CTDT_Stream::SetArmedState(){
  int iRet;
  UINT uiTempID;

  m_bscSampIdx= m_bscDeviceName + SZ_SAMP_COUNT;
  m_bscBuff= m_bscDeviceName + SZ_BUF_DATA;
  m_bscBufIdx =  m_bscDeviceName + SZ_BUF_IDX;

  // do nothing if not in idle state
  if(m_iState != ecStateIdle) {
    CP_printf("Cannot set armed state - the system is not in the idle state!\n");
    return 1;
  }
  // Create file
  uiTempID = GetTempFileName( 
                 (char *)m_bscFilePath,  // directory name
                 "TS_",  // file name prefix
                  0,     // generate suffix from time
                  m_szTmpFname );   // file name buffer

  if( uiTempID == 0 ){
     CP_printf("Error in SetArmedState, GetTempFileName() failed.\n\
Make sure that the output directory exists:\n    %s \n", (char *)m_bscFilePath);
     return 1;
  }
  m_bscTmpPath = m_bscFilePath; // Save the path for future rename

  CP_printf("+++++++++++++++++++++++++++++++++++++++++++++++++\n");
  // Actually writing will start when the mode will change to ecStateWriting
  iRet = StartWritingFile(m_szTmpFname);
  if( iRet ) return iRet;

  m_iBlocksWritten = 0;
  m_iState = ecStateArmed;
  CP_printf("SetArmedState\n");
  m_StartTimer();
  return 0;
}

//==============================================================================
int CTDT_Stream::SetIdleState(){
  // do nothing if not in write or armed state
  if(!((m_iState == ecStateWriting) || (m_iState == ecStateArmed))){
    CP_printf("Cannot set idle state - the system is not armed or writing!\n");
    return 1;
  }
  m_StopTimer( );
  if (IsWritingFile( )) {
    m_EndRecording();  
  }

  CP_printf("\n\nWarning - writing interrupted by client: SetIdleState()\n");
  m_iState = ecStateIdle;
  return 0;
}
//==============================================================================
int CTDT_Stream::GetStreamState( int * piState){
  *piState = m_iState;
  return 0;
}
//==============================================================================
int CTDT_Stream::GetN_Samples( int * pnSamples){
  *pnSamples = GetFileByteCounter()/sizeof(float);
  return 0;
}
//==============================================================================
int CTDT_Stream::GetTimeTick( int * piTick ){
  HRESULT hRet;
  _bstr_t bscTarget;
  double dRes;

  bscTarget = m_bscDeviceName + SZ_SAMP_COUNT;
  hRet = m_pTDev->raw_GetTargetVal( bscTarget, &dRes );
  *piTick = int(dRes);
  return 0;
}

//==============================================================================
int CTDT_Stream::m_OnTimer(LPVOID lpOnTimerParam){
  HRESULT hRet;
  long lRes;
  int iMode;
  double dVal;
  int iSampleCount, iBlocksAcquired, iBufferOffset;
  void *pBuff;
  float * pfBuff;
  int iSamp, iBufIdx;
  static int iPrevBufIdx, nBufs;
  SAFEARRAYBOUND ArrayBounds;


  // do nothing if idle
  if(m_iState == ecStateIdle){
    return 0;
  }

  m_pTDev->raw_GetSysMode(&lRes);  //Get TDT mode
  iMode = (int) lRes;

  // if Writing and (NOT Record mode): change to Idle, close file
  if((m_iState == ecStateWriting) && ( iMode != ecModeRecord)){
    m_iState = ecStateIdle;
    m_EndRecording();
    return 0;
  }

  // if Armed and Record: change to Writing
  if((m_iState == ecStateArmed) && ( iMode == ecModeRecord)){
    CP_printf("Started writing to file.\n");
    CP_printf("Block size: %d   Buffer size: %d\n", m_iBlockSize, m_iBufferSize);
    m_iState = ecStateWriting;
    iPrevBufIdx = 0;
    nBufs = 0;
  }

  if((m_iState != ecStateWriting) || ( iMode != ecModeRecord)) {
    return 0; // still waiting, do nothing
  }

  // if Writing and Record: get a block (if available) and write it to file
  hRet = m_pTDev->raw_GetTargetVal(m_bscSampIdx, &dVal);
  iSampleCount = (int) dVal;

  hRet = m_pTDev->raw_GetTargetVal(m_bscBufIdx, &dVal);
  iBufIdx = (int) dVal;
  if( iBufIdx < iPrevBufIdx ) {  // buffer index wrap-around
    nBufs++;
  }
  iPrevBufIdx = iBufIdx;
  iBufIdx += nBufs * m_iBufferSize;
//  iBlocksAcquired = iBufIdx/m_iBlockSize;
  iBlocksAcquired = iSampleCount/m_iBlockSize;

  // TODO: check if we are too far behind and stop writing
  while( (iBlocksAcquired > m_iBlocksWritten) && ( iMode == ecModeRecord)) {
    iBufferOffset = (m_iBlocksWritten * m_iBlockSize) % m_iBufferSize;
    hRet = m_pTDev->raw_ReadTargetV(m_bscBuff, iBufferOffset, m_iBlockSize, &x_vrtRes);
    ArrayBounds = x_vrtRes.parray->rgsabound[0];
    if( ArrayBounds.cElements < 1) {
      CP_printf("Empty array from raw_ReadTargetV().\n");
      return 0;
    }
    if( m_blnConvertToInt16 ) {
      pfBuff = (float *)x_vrtRes.parray->pvData;
      for( iSamp = 0; iSamp<m_iBlockSize; iSamp++) x_asBuffer[iSamp] = (short)pfBuff[iSamp];
      m_WriteBlockToFile ( x_asBuffer, m_iBlockSize * sizeof(short) );
    }
    else {
      pBuff = x_vrtRes.parray->pvData;
      m_WriteBlockToFile ( pBuff, m_iBlockSize * sizeof(float) );
    }
    m_iBlocksWritten++;
    m_pTDev->raw_GetSysMode(&lRes); //Check the mode on every block
    iMode = (int) lRes;

  }
  CP_printf("Blocks Acquired:  %d  BlocksWritten:  %d  Sample: %d     BufIdx: %d   nBufs: %d \r", 
                iBlocksAcquired, m_iBlocksWritten, iSampleCount, iBufIdx, nBufs);

 
//  CP_printf("Mode: %d\r", iMode);
  return 0;
}

//==============================================================================
int CTDT_Stream::Test(){
  HRESULT hRet;
  long lRes;
  VARIANT vrtRes;
  float *pf;

  hRet = m_pTDev->raw_ConnectServer( m_bscServerName, &lRes );

  hRet = m_pTDev->raw_ReadTargetV(m_bscBuff, 0, 10, &vrtRes);
  pf = (float *)vrtRes.parray->pvData;

  for( int i = 0; i<10; i++) CP_printf("%f\n", pf[i]);

  return 0;
}

//==============================================================================
int CTDT_Stream::SetFilePath( BSTR bstPath ){
  char * pchStr;
  int iLen;
  m_bscFilePath = bstPath;


  // Add trailing backslash if needed
  iLen = m_bscFilePath.length();
  pchStr = (char *) m_bscFilePath;

  if( iLen > 0) {
    if( pchStr[iLen-1] != '\\'){
      m_bscFilePath = m_bscFilePath + "\\";
    }
  }
  else {
    m_bscFilePath = "\\";
  }

  return 0;
}
//==============================================================================
int CTDT_Stream::GetFilePath( BSTR  * pbstPath ){

  *pbstPath =  m_bscFilePath.copy();
  return 0;
}

//==============================================================================
int CTDT_Stream::m_RenameFile(){
  _bstr_t bstNewName;
  int iRes;

  bstNewName = m_bscTmpPath + m_bscFileName;

  iRes =  MoveFile( m_szTmpFname, (char *) bstNewName);
  if ( ! iRes ){
    CP_printf("Error in RenameFile: MoveFile() failed. \nOld name: %s   \nNew name: %s \n",
                m_szTmpFname, (char *) bstNewName );
    return 1;
  }

  CP_printf("Renamed file. \nOld name: %s   \nNew name: %s \n",
                m_szTmpFname, (char *) bstNewName );
  CP_printf("-------------------------------------------------\n");
  
  return 0;
}


//==============================================================================
int CTDT_Stream::m_EndRecording(){

  CP_printf("\nStopped writing, closing file.\n");
  StopWritingFile();
  m_RenameFile();

  return 0;
}

//==============================================================================
int CTDT_Stream::SetConvertToInt16Flag( int blnFlag ){
  m_blnConvertToInt16 = blnFlag;
  return 0;
}
//==============================================================================
int CTDT_Stream::GetConvertToInt16Flag( int * blnFlag ){
  *blnFlag = m_blnConvertToInt16;
  return 0;
}
//==============================================================================
int CTDT_Stream::OkToChangeParams(){

  if(m_iState == ecStateIdle) return TRUE;

  return FALSE;
}