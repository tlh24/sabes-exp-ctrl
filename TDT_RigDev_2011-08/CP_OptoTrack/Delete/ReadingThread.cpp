
#include "CP_printf.h"
#include "ReadingThread.h"

//===========================================================================
CReadingThread::CReadingThread(){

  m_dwThreadId = 0;
  m_hReadingThread = NULL;
  m_blnThreadActive = false;
  m_nSleepMs = 0;

}

//===========================================================================
CReadingThread::~CReadingThread(){
  if( m_hReadingThread ) m_StopReadingThread();
}

//===========================================================================
int CReadingThread::m_StartReadingThread( int nMsToStop ){

  if( m_hReadingThread ) {
    CP_printf("Error in m_StartReadingThread()! Thread is already running.\n");
    return 1;
  }
  m_nSleepMs = nMsToStop;

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
int CReadingThread::m_StopReadingThread(){

  if( m_hReadingThread == NULL ) {
    CP_printf("\nError in m_StopReadingThread()! Thread is not running.\n");
    return 1;
  }
  //Terminate thread
  m_blnThreadActive = false;
  Sleep( m_nSleepMs ); // Wait for the thread to finish

  if( m_hReadingThread != NULL ) {
    CP_printf("\nError in m_StopReadingThread()! Thread is still running.\n");
    return 1;
  }

  return 0;
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

