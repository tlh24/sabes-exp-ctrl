// TimerThread.h

#ifndef TimerThread_H
#define TimerThread_H

#define _WIN32_WINDOWS 0x0500 //Needed for the timer functions

#include <windows.h>

//we wait for a timer event and for the StopThreadEvent
#define N_WAIT_OBJS 2

class CTimerThread {
  private:
    HANDLE m_hStopThreadEvent; 
    CRITICAL_SECTION m_CriticalSection; 
    DWORD m_dwThreadId;
    HANDLE m_hNotificationThread;
    HANDLE m_hTimer;
    bool m_blnTimerOn;

    void  m_CloseHandles( );
    static DWORD WINAPI m_NotificationThread( LPVOID lpParameter );
    static VOID CALLBACK m_TimerCallback( LPVOID lpParameter,   // data value
                                          DWORD dwTimerLowValue, // timer low value
                                          DWORD dwTimerHighValue ); // timer high value

  protected:
    int m_iTimerIntervalMs;
    int m_InitTimerThread();
    int m_StartTimer();
    int m_StopTimer();
    int m_CloseTimerThread();
  public:
    CTimerThread( );
    ~CTimerThread( );
    virtual int  m_OnTimer(LPVOID lpOnTimerParam) = 0;

};

#endif // #ifndef TimerThread_H

