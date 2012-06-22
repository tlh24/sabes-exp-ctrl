
#include "CP_printf.h"
#include "ReadingThread.h"

//===========================================================================
CReadingThread::CReadingThread(){

  m_dwThreadId = 0;
  m_hReadingThread = NULL;
  m_blnThreadActive = false;

}

//===========================================================================
CReadingThread::~CReadingThread(){
  if( m_hReadingThread ) m_StopReadingThread( 1000 );
}

//===========================================================================
int CReadingThread::IsRunning(){
  if( m_hReadingThread ) {
    return 1;
  }
  return 0;
}

//===========================================================================
int CReadingThread::m_StartReadingThread( ){

  if( m_hReadingThread ) {
    CP_printf("Error in m_StartReadingThread()! Thread is already running.\n");
    return 1;
  }

  m_hReadingThread = CreateThread( NULL,  // pointer to security attributes
                                        0,  // initial thread stack size
                                        m_ReadingThread, // pointer to thread function
                                        (LPVOID) this,  // argument for new thread
                                        0,  // no specific creation flags
                                        &m_dwThreadId ); // pointer to receive thread ID

  if( !m_hReadingThread ) {
    CP_printf("Error in m_StartReadingThread()! CreateThread() failed.\n");
    return 1;
  }
  return 0;
}

//===========================================================================
int CReadingThread::m_StopReadingThread( int nMsToStop ){
  int iWait, nWait;

  if( m_hReadingThread == NULL ) {
    CP_printf("\nError in m_StopReadingThread()! Thread is not running.\n");
    return 1;
  }
  //Terminate thread
  m_blnThreadActive = false;
  nWait = nMsToStop/5 + 1;
  for( iWait = 0; iWait < nWait; iWait++){
    Sleep( 5 ); // Wait for the thread to finish
    if( m_hReadingThread == NULL ) return 0;
  }

  CP_printf("\nError in m_StopReadingThread()! Thread is still running.\n");
  return 1;
}

//===========================================================================
DWORD WINAPI CReadingThread::m_ReadingThread( LPVOID lpParameter ){
  CReadingThread * pRT;

  CP_printf( "Started Reading Thread\n"); 
  pRT =  (CReadingThread *) lpParameter;

  SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS ); 
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL );

  pRT->m_blnThreadActive = true;
  // Main loop
  while( pRT->m_blnThreadActive ) {
    pRT->ReadingFunc( ); 
  }
  SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS );
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_NORMAL );

  pRT->ShutdownFunc();
  pRT->m_hReadingThread = NULL;
  CP_printf( "\nStopped Reading Thread\n"); 
  return 0;
}

