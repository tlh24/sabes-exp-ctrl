#ifndef ReadingThread_H
#define ReadingThread_H

#include <windows.h>

class CReadingThread {
  private:
    DWORD m_dwThreadId;
    HANDLE m_hReadingThread;
    volatile bool m_blnThreadActive;

    int m_nSleepMs;
    static DWORD WINAPI m_ReadingThread( LPVOID lpParameter );


  protected:
    int m_StartReadingThread( int nMsToStop );
    int m_StopReadingThread();

  public:
    CReadingThread( );
    ~CReadingThread( );
    virtual int ReadingFunc() = 0;
    virtual int ShutdownFunc( ) = 0;

};

#endif // #ifndef ReadingThread_H

