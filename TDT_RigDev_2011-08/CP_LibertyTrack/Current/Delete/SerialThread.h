#ifndef SerialThread_H
#define SerialThread_H

#include "tserial.h"
#include "SlideBuf.h"
#include "TimeStamp.h"

// This is the frame format if the data structure is 
// configured properly by CPDIdev::SetSDataList

typedef enum iSerialParityTag  { 
  ecSerialParityNONE = 0,    
  ecSerialParityODD =1, 
  ecSerialParityEVEN = 2
} SerialParityEnum;

class CSerialThread: public CSlideBuf, public CTimeStamp {
  private:
    serial_parity m_iSerialParity;
    int m_iComPortIdx;
    int m_iBaudRate;
    DWORD m_dwThreadId;
    HANDLE m_hSerialThread;
    volatile bool m_blnThreadActive;

    int m_IScanReadLoop();
    static DWORD WINAPI m_SerialThread( LPVOID lpParameter );


  protected:
    Tserial m_Serial;

    int m_InitSerialThread();
    int m_CloseSerialThread();
  public:
    CSerialThread( );
    ~CSerialThread( );
    int ResetTimeAndBuffer();
    int SetBaudRate( int iRate );
    int GetBaudRate( int * piRate );
    int SetComPort( int iPortIdx);
    int GetComPort( int * piPortIdx );
//    int SetComParity( int iParity );
//    int GetComParity( int * piParity );


};

#endif // #ifndef SerialThread_H

