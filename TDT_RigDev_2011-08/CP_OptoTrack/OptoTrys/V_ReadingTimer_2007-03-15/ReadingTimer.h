#ifndef ReadingTimer_H
#define ReadingTimer_H

#include "SlideBuf.h"
#include "TimeStamp.h"

class CReadingTimer {
  private:
    volatile bool m_blnTimerActive;
    WORD m_wTimerId;
    int m_iTimerCount;
    int m_iPeriodMs;
    CTimeStamp m_TS_TimerDelay;
    
    int m_OnTimer();
    static void CALLBACK m_TimerCallback(  
                      UINT uID,      // Identifier of the timer event (wTimerID)
                      UINT uMsg,     // Reserved; do not use
                      DWORD dwUser,  // User instance data
                      DWORD dw1,     // Reserved; do not use
                      DWORD dw2  );  // Reserved; do not use

  protected:
    int m_StartReadingTimer( int iPeriodMs );
    int m_StopReadingTimer();
  public:
    CReadingTimer( );
    ~CReadingTimer( );
    virtual int ProcessTimerEvent( int iTimerCounter ) = 0;


};

#endif // #ifndef ReadingTimer_H

