#ifndef __CEYETRACK_H_
#define __CEYETRACK_H_


#include "ReadingThread.h"
#include "tserial.h"
#include "SlideBuf.h"
#include "TimeStamp.h"

#define TRANSF_MTX_N_1     2
#define TRANSF_MTX_N_2     6

typedef struct IScanFrameStructTag {
  double dLocalTimeMs;
  int    iRawX;
  int    iRawY;
  int    iFrame;
} IScanFrameStruct;


typedef enum iSerialParityTag  { 
  ecSerialParityNONE = 0,    
  ecSerialParityODD =1, 
  ecSerialParityEVEN = 2
} SerialParityEnum;


class CEyeTrack: public CReadingThread, public CSlideBuf, public CTimeStamp {

  public:

    CEyeTrack();
    ~CEyeTrack();
    int ConnectISCAN();
    int DisconnectISCAN();
    int GetVersion( BSTR * pbstVer);
    int GetVersion( char ** pszVer);
    int GetTransformMatrix( double * pdMtx );
    int SetTransformMatrix( double * pdMtx );
    int GetTimeScale( double *pdC0, double *pdC1);
    int SetTimeScale( double dC0, double dC1);
    int SetBaudRate( int iRate );
    int GetBaudRate( int * piRate );
    int SetComPort( int iPortIdx);
    int GetComPort( int * piPortIdx );
//    int SetComParity( int iParity );
//    int GetComParity( int * piParity );

    int TransformCoordinates( double dX_Raw, double dY_Raw, 
                              double * pdX_t, double * pdY_t );
    void CalcTime( int iFrame, double * pdTimeMs);
    int ParseBuffer( int nFrames,
                     void * pvSrcBuffer,
                     double * pdTimeStamps, 
                     double * pdCoord );
    void GetMissedCount( int * pnMissedFrames, int * piMissCount);


  private:
    Tserial m_Serial;
    int m_iComPortIdx;
    int m_iBaudRate;
    serial_parity m_iSerialParity;

    int iPortIO_Granted;

    int m_ReadCount;
    int m_iMissCount;
    int m_nMissedFrames;
    int m_iPrevFrame;
    int m_iReportSync;

    double m_dTimeC0;
    double m_dTimeC1;
    double m_adTransformMatrix[TRANSF_MTX_N_1][TRANSF_MTX_N_2];

    int m_WaitForSync( );
    int m_ReadDataItem( int * piItem );
    int m_WriteData( int * piItems, int nItems );
    virtual int ReadingFunc( );
    virtual int ShutdownFunc( );

};

#endif //  #ifndef __CEYETRACK_H_