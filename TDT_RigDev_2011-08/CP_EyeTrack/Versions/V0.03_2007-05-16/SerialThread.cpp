#define _WIN32_DCOM

#include <windows.h>
#include <objbase.h>
#include <initguid.h>
#include "CP_printf.h"
#include "tserial.h"
#include "SerialThread.h"

#define HEADER_CHAR 0x44
#define HEADER_SHORT  0x4444

#define N_DATA_ITEMS 2
#define ISCAN_BUFFER_SIZE 100000   // number of items in the sliding buffer, about 1000 sec

#define N_COM_NAMES 10
char * x_aszComNames[N_COM_NAMES] = { "COM1", "COM2", "COM3", "COM4", "COM5", 
                                      "COM6", "COM7", "COM8", "COM9", "COM10"};

#define N_BAUD_RATES 8
int x_aiStdBaudRates[N_BAUD_RATES] = { 1200, 2400, 4800, 9600, 19200, 
                                       38400, 57600, 115200 };


//===========================================================================
CSerialThread::CSerialThread(){

  m_dwThreadId = 0;
  m_hSerialThread = NULL;
  m_blnThreadActive = false;
  m_iSerialParity = spNONE;
  m_iComPortIdx = 1;  //COM1
  m_iBaudRate = 57600; 

}

//===========================================================================
CSerialThread::~CSerialThread(){
  m_CloseSerialThread();
}
//===========================================================================
int CSerialThread::ResetTimeAndBuffer(){
  ResetBuffer();
  ResetTime();
  return 0;
}

//===========================================================================
int CSerialThread::m_InitSerialThread( ){

  int iRet;

  if( m_hSerialThread ) {
    CP_printf("Error in m_InitSerialThread()! Thread is already running.\n");
    return 1;
  }

  // Init sliding buffer
  SetBuffer(sizeof(IScanData), ISCAN_BUFFER_SIZE);
  CP_printf("Connecting to %s port\n", x_aszComNames[ m_iComPortIdx-1]);
  iRet = m_Serial.connect(x_aszComNames[ m_iComPortIdx-1], m_iBaudRate, m_iSerialParity);
  if(iRet) {
    CP_printf("Error in m_InitSerialThread, m_Serial.connect() failed\n");
    return 1;
  }

  ResetTimeAndBuffer();
  m_hSerialThread = CreateThread( NULL,  // pointer to security attributes
                                        0,  // initial thread stack size
                                        m_SerialThread, // pointer to thread function
                                        (LPVOID) this,  // argument for new thread
                                        0,  // no specific creation flags
                                        &m_dwThreadId ); // pointer to receive thread ID

  if( !m_hSerialThread ) {
    CP_printf("Error in m_InitSerialThread()! CreateThread() failed.\n");
    return 1;
  }
  return 0;
}

//===========================================================================
int CSerialThread::m_CloseSerialThread( ){

  //Terminate thread
  m_blnThreadActive = false;
  Sleep(200); // Wait for the thread to finish

  if( m_hSerialThread != NULL ) {
    CP_printf("Error in m_CloseSerialThread()! Thread is still running.\n");
  }
  m_Serial.disconnect();
  RemoveBuffer();

  return 0;
}

//===========================================================================
// wait for 2 sync chars in a row
int CSerialThread::m_WaitForSync( int iReportSync ){
  char chIn;
  int nChars, nRead, nTimeouts;


  nChars = 0;
  nTimeouts = 0;
  while( TRUE ) {
    // wait for the first header byte  
    do { 
      chIn = 0;  // in case of time-out, chIn is not changed
      nRead = m_Serial.getArray( &chIn, 1 );
      if(!m_blnThreadActive) return 1;  // exit check
      if( nRead == 0)  nTimeouts++;
      nChars += nRead;
    } while( chIn != HEADER_CHAR);
    // get next char and check if it's header
    chIn = 0;  // in case of time-out, chIn is not changed
    nRead = m_Serial.getArray( &chIn, 1 );
    if(!m_blnThreadActive) return 1;  // exit check
    nChars += nRead;
    if( nRead == 0)  nTimeouts++;
    if( (nRead == 1) && (chIn == HEADER_CHAR)) {
      if( iReportSync) {   
        CP_printf("\nFound serial sync:    %d chars,     %d timeouts \n", nChars, nTimeouts);
      }
      return 0;   // got 2 sync chars in a row
    }
  }

  return 0;  // not used
}

//===========================================================================
// item is a short (2 bytes)
int CSerialThread::m_ReadDataItem( int * piItem ){
  int nRead;
  short shtItem;
  
  *piItem = 0;

  nRead = m_Serial.getArray( (char *)&shtItem, sizeof(shtItem) );
  if(!m_blnThreadActive) return 1;  // exit check
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
int CSerialThread::m_WriteData( int * piItems, int nItems ){
  IScanData isdTmp;

  isdTmp.dLocalTimeMs = TimeStampMs();
  isdTmp.iRawX = piItems[0];
  isdTmp.iRawY = piItems[1]; 
  if( nItems > 2 ) {
    // for some reason the data in ISCAN serial output are multiplied by 10
    isdTmp.iDigIn = piItems[2]/10; 
    // TODO: process synchro timestamps
    // Check time elapsed
    // Check if rollover occured 
    // Update actuall frame counter
    // Calc synchro timestamp
    isdTmp.dSyncTimeMs = 0;  
  }
  else {
    isdTmp.iDigIn = 0;
    isdTmp.dSyncTimeMs = 0;  
  }

  // save values into the buffer
  WriteData(&isdTmp, 1);
  return 0;
}
//===========================================================================
int CSerialThread::m_IScanReadLoop(){
  int iErr, iItem, iReportSync;
  int aiData[N_DATA_ITEMS];  
  
  iReportSync = 1;  // report next sync
  while(TRUE){
    iErr = m_WaitForSync( iReportSync );
    if( iErr) goto LoopExit;  // exit check
    for( iItem=0; iItem<N_DATA_ITEMS; iItem++) {
      iErr = m_ReadDataItem( &aiData[iItem]);
      if(!m_blnThreadActive) goto LoopExit;  // exit check
      if( iErr) break;
    }
    if( iErr ) {
      iReportSync = 1;  // report next sync
    }
    else {
      m_WriteData( aiData, N_DATA_ITEMS );
      iReportSync = 0;  // don't report next sync
    }
  }

LoopExit:
  CP_printf("\n\n");
  return 0;
}

//===========================================================================
DWORD WINAPI CSerialThread::m_SerialThread( LPVOID lpParameter ){
  HRESULT hr;
  CSerialThread * pST;

  // Init COM using multi-threaded model
  hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);    //COINIT_APARTMENTTHREADED
  if( hr != S_OK) { 
    CP_printf( "Error in m_SerialThread( ): CoInitializeEx() failed \n"); 
    return 1;
  }
  CP_printf( "Started Serial Thread\n"); 
  pST =  (CSerialThread *) lpParameter;

  pST->m_blnThreadActive = true;
  
  pST->m_IScanReadLoop(); // Main loop


  CoUninitialize();
  CP_printf( "Stopped Serial Thread\n"); 
  pST->m_hSerialThread = NULL;
  return 0;
}

//===========================================================================
int CSerialThread::SetBaudRate( int iRate ){
  int i;

  if( m_hSerialThread ) {
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
int CSerialThread::GetBaudRate( int * piRate ){

  * piRate = m_iBaudRate;
  return 0;
}

//===========================================================================
int CSerialThread::SetComPort( int iPortIdx){

  if( m_hSerialThread ) {
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
int CSerialThread::GetComPort( int * piPortIdx ){

  * piPortIdx = m_iComPortIdx;
  return 0;
}






