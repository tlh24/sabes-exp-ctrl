#ifndef SerialThread_H
#define SerialThread_H

#include "tserial.h"
#include "SlideBuf.h"
#include "TimeStamp.h"

typedef struct IScanDataTag {
  double dLocalTimeMs;
  double dSyncTimeMs;
  int    iRawX;
  int    iRawY;
  int    iDigIn;
} IScanData;


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
    int m_WaitForSync( int iReportSync );
    int m_ReadDataItem( int * piItem );
    int m_WriteData( int * piItems, int nItems );
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

