#define _WIN32_DCOM

#include <windows.h>
#include <objbase.h>
#include <initguid.h>
#include "CP_printf.h"
#include "tserial.h"
#include "SerialThread.h"

#define HEADER_CHAR 0x44
#define N_DATA_VALS 2
#define ISCAN_BUFFER_SIZE 1000   // number of items in the sliding buffer

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
  SetBuffer(sizeof(LibertyFrame), ISCAN_BUFFER_SIZE);
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
int CSerialThread::m_IScanReadLoop(){
  char c;
  short shtData;
  short shtHeaderVal;
  int iaData[N_DATA_VALS];  
  int iCount;
  int nRead;
  LibertyFrame isdTmp;
  
  // value of header if read as short
  shtHeaderVal = HEADER_CHAR + HEADER_CHAR * 256;  

  while(TRUE){
    // wait for the first header byte  
    do { 
      c = 0;  // in case of getChar() time-out, c is not changed
      m_Serial.getArray( &c, 1 );
      if(!m_blnThreadActive) goto LoopExit;  // exit check

    } while( c != HEADER_CHAR);
      
    // if the next char is also a header, read the data (8 chars)
    c = 0;  // in case of getChar() time-out, c is not changed
    m_Serial.getArray( &c, 1 );
    if(!m_blnThreadActive) goto LoopExit;  // exit check

    if( c == HEADER_CHAR) {  // second header byte OK

      // Read 2 bytes, compare to a header 
      // Read no more that 16 x 2 bytes total

      CP_printf("\nGot serial sync\n");
      iCount =0;
      while(TRUE){

        shtData = 0;  // in case of getArray() time-out, shtData is not changed
        nRead = m_Serial.getArray( (char *)&shtData, sizeof(shtData) );
        if(!m_blnThreadActive) goto LoopExit;  // exit check

        if( nRead != sizeof(shtData)) {
          CP_printf("\nCOM read error. Restarting sync search. \n");
          break;
        }


        if(shtData == shtHeaderVal){
          if( iCount != N_DATA_VALS ){
            // if we received unexpected number of values,
            // it is junk, we are out of sync, search for the header again
            CP_printf("\nLost serial sync, restatring sync search\n");
            break;
          }
/*
          isdTmp.dTimeStampMs = TimeStampMs();
          isdTmp.iRawX = iaData[0];
          isdTmp.iRawY = iaData[1]; 
*/
          // save values into the buffer
          WriteData(&isdTmp, 1);
          // we found the header, process the data received 
          // and start the loop over 
//          for( int i=0; i<N_DATA_VALS; i++){
//            CP_printf("%d\t", iaData[i]);
//          }
//          CP_printf("\r");
          iCount =0;  
        }
        else {
          iaData[iCount] = shtData;
          iCount++;
          if( iCount > N_DATA_VALS ){
            // if we received more than N_DATA_VALS values,
            // it is junk, we are out of sync, search for the header again
            CP_printf("\nLost serial sync, restatring sync search\n");
            break;
          }
        }

     } // while(TRUE)
    } // if( c == HEADER_CHAR)
  } // while(TRUE) 
//      CP_printf("%s\n", achInBuff);

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






