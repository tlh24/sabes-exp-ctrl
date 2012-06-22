//#define _WIN32_DCOM
#include "TimerThread.h"


#include <objbase.h>
#include <initguid.h>
#include "CP_printf.h"


//===========================================================================
CTimerThread::CTimerThread(){

  m_hTimer = CreateWaitableTimer( NULL, // default security
                                  FALSE, // no manual reset
                                  NULL );  // object name
  if( !m_hTimer ){
    CP_printf("Error in: CTimerThread()! CreateWaitableTimer() failed\n");
  }
  m_hStopThreadEvent = CreateEvent( NULL, // default security attributes
                                    FALSE,  // auto-reset event
                                    FALSE, // flag for initial state
                                    NULL );  // pointer to event-object name
  if(!m_hStopThreadEvent) {
    CP_printf("Error in m_StartNotificationThread()! CreateEvent() failed\n");
  }

  InitializeCriticalSection( &m_CriticalSection );
  m_dwThreadId = 0;
  m_hNotificationThread = NULL;
  m_iTimerIntervalMs = 200;  // 5Hz rate by default
  m_blnTimerOn = false;

}

//===========================================================================
CTimerThread::~CTimerThread(){
   // TODO: stop timer and thread
  m_StopTimer();
  m_CloseTimerThread();
  CloseHandle( m_hTimer );
  CloseHandle(m_hStopThreadEvent);
  DeleteCriticalSection( &m_CriticalSection );
}

//===========================================================================
int CTimerThread::m_InitTimerThread( ){
  
  m_hNotificationThread = CreateThread( NULL,  // pointer to security attributes
                                        0,  // initial thread stack size
                                        m_NotificationThread, // pointer to thread function
                                        (LPVOID) this,  // argument for new thread
                                        0,  // no specific creation flags
                                        &m_dwThreadId ); // pointer to receive thread ID

  if( !m_hNotificationThread ) {
    CP_printf("Error in m_StartTimerThread()! CreateThread() failed.\n");
    return 1;
  }
  return 0;
}

//===========================================================================
int CTimerThread::m_CloseTimerThread( ){
  m_StopTimer();

  //Terminate thread
  if( !SetEvent(m_hStopThreadEvent)) {
    CP_printf("Error in m_StopNotificationThread()! SetEvent() failed.\n");
  }

  return 0;
}


//===========================================================================
DWORD WINAPI CTimerThread::m_NotificationThread( LPVOID lpParameter ){
  HRESULT hr;
  DWORD dw;
  BOOL blnOk;
  LARGE_INTEGER liDueTime;
  CTimerThread * pTT;

  // Init COM using multi-threaded model
  hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);    //COINIT_APARTMENTTHREADED
  if( hr != S_OK) { 
    CP_printf( "Error in m_NotificationThread( ): CoInitializeEx() failed \n"); 
    return 1;
  }
  CP_printf( "Started Notification Thread\n"); 
  pTT =  (CTimerThread *) lpParameter;

  
  liDueTime.QuadPart = -10000;  //Call in 1 ms
  blnOk = SetWaitableTimer(pTT->m_hTimer,  // handle to timer
                           &liDueTime, // timer due time
                           pTT->m_iTimerIntervalMs,  // timer interval
                           pTT->m_TimerCallback,  // completion routine
                           lpParameter,  // completion routine parameter
                           FALSE);  // resume state
  if(!blnOk) {
    CP_printf("Error in: m_StartNotificationThread():SetWaitableTimer()\n");
    return 1;
  }

  // Wait for the stop thread event in alertable state
  do {
    dw = WaitForSingleObjectEx( pTT->m_hStopThreadEvent,  
                                INFINITE,  // time-out interval
                                TRUE );       // alertable option
  } while( dw == WAIT_IO_COMPLETION  ); // Don't exit on timer callbacks
  if( !CancelWaitableTimer(pTT->m_hTimer)) {
    CP_printf("Error in  m_NotificationThread()! CancelWaitableTimer() failed\n");
  }

  CP_printf( "Stopped Notification Thread\n"); 
  pTT->m_hNotificationThread = NULL;
  CoUninitialize();
  return 0;
}
//===========================================================================
int CTimerThread::m_StartTimer( ){

  if( m_hNotificationThread == NULL ){
    CP_printf( "Error in m_StartTimer( ): thread is not running \n"); 
    return 1;
  }

  CP_printf("Timer enabled\n");
  m_blnTimerOn = true;

  return 0;
}  

//===========================================================================
int CTimerThread::m_StopTimer( ){
  m_blnTimerOn = false;
  return 0;
}

//===========================================================================
VOID CALLBACK CTimerThread::m_TimerCallback( LPVOID lpParameter,   // data value
                                            DWORD dwTimerLowValue, // timer low value
                                            DWORD dwTimerHighValue ){ // timer high value

  CTimerThread * pTT;

  pTT =  (CTimerThread *) lpParameter;

  EnterCriticalSection( &pTT->m_CriticalSection );
  if( pTT->m_blnTimerOn ){
    pTT->m_OnTimer( lpParameter );
  }
  LeaveCriticalSection( &pTT->m_CriticalSection );

}







