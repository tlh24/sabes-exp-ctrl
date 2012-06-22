#define _WIN32_DCOM

#include <windows.h>
#include <math.h>
#include "CP_printf.h"
#include "ReadingTimer.h"


#define TIMER_RESOLUTION_MS 1         // requested timer resolution
#define DATA_WAIT_MS        2         // time to wait for the OptoTrack data 

#define N_BINS 20

int x_aiHist[N_BINS]; 
//===========================================================================
CReadingTimer::CReadingTimer(){

  m_blnTimerActive = 0;
  m_wTimerId = 0;
  m_iTimerCount = 0;
  m_iPeriodMs = 100;

  timeBeginPeriod( TIMER_RESOLUTION_MS ); 

}

//===========================================================================
CReadingTimer::~CReadingTimer(){
  m_StopReadingTimer();
  timeEndPeriod( TIMER_RESOLUTION_MS ); 
}

//===========================================================================
int CReadingTimer::m_StartReadingTimer( int iPeriodMs ){

  int iRet;

  if( m_blnTimerActive || m_wTimerId ) {
    CP_printf("Error in m_StartReadingTimer()! Timer is already running.\n");
    return 1;
  }

  if( iPeriodMs < DATA_WAIT_MS ) {
    CP_printf("Error in m_StartReadingTimer()! Timer period is too short: %d\n", iPeriodMs);
    return 2;
  }
  m_iPeriodMs = iPeriodMs;

  for(int i=0; i<N_BINS; i++) x_aiHist[i] = 0; // clear the histogram
  CP_printf("Starting ReadingTimer... \n");
  m_blnTimerActive = 1;
  m_iTimerCount = 0;

  iRet = m_OnTimer(); // first call to m_OnTimer() starts the chain
  if( iRet ) { 
    CP_printf("\n\nError in m_StartReadingTimer()! m_OnTimer() failed.\n");
    return 3;
  }

  CP_printf( "\rStarted!                                                        \n"); 
  return 0;
}

//===========================================================================
int CReadingTimer::m_StopReadingTimer( ){

  //Terminate timer
  m_blnTimerActive = 0;
  Sleep( m_iPeriodMs * 5 ); // Wait for the timer to stop

  if( m_wTimerId != 0 ) {
    CP_printf("Error in m_StopReadingTimer()! Timer is still running.\n");
    CP_printf("This state is inconsistent. Please restart the application.\n");
    return 1;
  }

  CP_printf( "Stopped Reading Timer\n"); 

  for(int i=0; i<N_BINS; i++) {
	CP_printf("%2d  %d\n", i, x_aiHist[i]);
  }

  return 0;
}

//===========================================================================
// Note: this method is executed in a context of a different thread: 
// application timer thread

int CReadingTimer::m_OnTimer(){

  int iTimeMs;
  int iDelayMs;
//  int iFrame, nMissedFrames;
  
  if(!m_blnTimerActive) {  // exit requested
    m_wTimerId = 0;
    CP_printf("\n\n");
    return 0;
  }
  
    
  // measure time elapsed from the previous read
  iTimeMs = (int)ceil(m_TS_TimerDelay.TimeStampMs());
  // start next measurement
  m_TS_TimerDelay.ResetTime();
  // Next default delay
  iDelayMs = m_iPeriodMs - DATA_WAIT_MS;
  // Schedule next timer event
  // Call itself after uiDelayMs 
  m_wTimerId = timeSetEvent( 
                       (UINT)iDelayMs, // delay, ms
                       0,                // use max possible timer resolution
                       m_TimerCallback,  // callback function
                       (DWORD)this,      // user data
                       TIME_ONESHOT );   // single timer event

  if( m_wTimerId == 0 ) {
    m_blnTimerActive = 0;
    CP_printf("\n\nError in m_OnTimer: timeSetEvent() failed!\n");
    CP_printf("Reading Timer stopped!\n");
    return 1;
  }
  // Read data from OptoTrack 
  // save values into the buffer
  // Normally we should wait for the data for DATA_WAIT_MS
  ProcessTimerEvent( m_iTimerCount );

  int i = iTimeMs;
  if( i>= N_BINS) i = N_BINS - 1;
  if( m_iTimerCount > 10 ) x_aiHist[i]++;
  

/*
  nMissedFrames = 0;
  if( m_iTimerCount > 1 ) { 
    nMissedFrames = (iTimeMs / m_iPeriodMs); 
  }
  // if we are late by less then one frame period
  // new data are not available yet, 
  // so we try to correct the next delay
  if( nMissedFrames == 1) {
    // calc next requested delay
    iDelayMs = m_iPeriodMs - DATA_WAIT_MS  // next delay we want
               - ( iTimeMs - m_iPeriodMs);  // correction from this period 
    // if requested delay is long enough,
    // do not read data now
    if( iDelayMs > TIMER_RESOLUTION_MS ) nMissedFrames--; 
  }

  for( iFrame = 0; iFrame < nMissedFrames; iFrame++){
    m_iTimerCount++;
    // Read data from OptoTrack 
    // save values into the buffer
    ProcessTimerEvent( m_iTimerCount );
  }
*/

//  ProcessTimerEvent( m_iTimerCount );
//  CP_printf("\r%d   %3d     ", m_iTimerCount, iTimeMs);

  m_iTimerCount++;
  return 0;
}

//===========================================================================
void CALLBACK CReadingTimer::m_TimerCallback( 
                      UINT uID,      // Identifier of the timer event (wTimerID)
                      UINT uMsg,     // Reserved; do not use
                      DWORD dwUser,  // User instance data
                      DWORD dw1,     // Reserved; do not use
                      DWORD dw2  ){  // Reserved; do not use

  CReadingTimer * pRT;

  pRT =  (CReadingTimer *) dwUser;
  pRT->m_OnTimer(); 

}

