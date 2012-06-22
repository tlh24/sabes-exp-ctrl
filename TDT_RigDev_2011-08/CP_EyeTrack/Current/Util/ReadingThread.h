#ifndef ReadingThread_H
#define ReadingThread_H

#include <windows.h>

class CReadingThread {
  private:
    DWORD m_dwThreadId;
    HANDLE m_hReadingThread;
    volatile bool m_blnThreadActive;
    static DWORD WINAPI m_ReadingThread( LPVOID lpParameter );

  protected:
    int m_StartReadingThread( );
    int m_StopReadingThread(int nMsToStop);

  public:
    CReadingThread( );
    ~CReadingThread( );
    int IsRunning();
    int IsActive(){ return m_blnThreadActive; };
    virtual int ReadingFunc() = 0;
    virtual int ShutdownFunc( ) = 0;

};

#endif // #ifndef ReadingThread_H

