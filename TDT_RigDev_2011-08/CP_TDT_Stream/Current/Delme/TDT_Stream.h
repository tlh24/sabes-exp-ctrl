#ifndef __CTDT_STREAM_H_
#define __CTDT_STREAM_H_

#import "TDevAccX.ocx" raw_dispinterfaces no_namespace
//raw_dispinterfaces  named_guids 

#include "DataFile.h"
#include "TimerThread.h"

typedef enum iStateTag {
  ecStateCreated = 0,
  ecInitialized  = 1,
  ecStateIdle    = 2,
  ecStateArmed   = 3,
  ecStateWriting = 4  
}  StateEnum; 

typedef enum iModeTag {
  ecModeIdle    = 0,
  ecModeStandby = 1,
  ecModePreview = 2,
  ecModeRecord  = 3  
}  ModeEnum; 


class CTDT_Stream: public TDataFile, public CTimerThread  {

public:

  CTDT_Stream();
  ~CTDT_Stream();
  int Initialize( HWND hWnd );
  int ConnectServer();
  int DisconnectServer();
  int SetServerName( BSTR bstName );
  int GetServerName( BSTR  * pbstName );
  int SetDeviceName( BSTR bstName );
  int GetDeviceName( BSTR * pbstName );
  int GetSystemMode( int * piMode );
  int SetFileName( BSTR bstName );
  int GetFileName( BSTR  * pbstName );
  int SetBufferSize( int iSize );
  int GetBufferSize( int * piSize );
  int GetSampRateHz( float * pfRateHz );
  int SetBlockSize( int iSize );
  int GetBlockSize( int * piSize );
  int SetArmedState();
  int SetIdleState();
  int GetStreamState( int * piState);
  int GetN_Samples( int * pnSamples);
  int GetTimeTick( int * piTick );
  int GetVersion( BSTR * pbstVer);
  int GetVersion( char ** pszVer);
  int SetFilePath( BSTR bstPath );
  int GetFilePath( BSTR  * pbstPath );
  int SetConvertToInt16Flag( int blnFlag );
  int GetConvertToInt16Flag( int * blnFlag );
  int OkToChangeParams();

  int Uninitialize();
  int Test();

private:
  StateEnum m_iState;
  _DTDevAccXPtr m_pTDev;
  _bstr_t m_bscFilePath;
  _bstr_t m_bscFileName;
  _bstr_t m_bscTmpPath;
  char m_szTmpFname[1024];
  _bstr_t m_bscServerName;
  _bstr_t m_bscDeviceName;
  _bstr_t m_bscSampIdx;
  _bstr_t m_bscBufIdx;
  _bstr_t m_bscBuff;

  int m_iBufferSize;
  int m_iBlocksWritten;
  int m_iBlockSize;
  int m_iFileStartTick;
  int m_blnConvertToInt16;
  int m_RenameFile();
  int m_EndRecording();
  virtual int m_OnTimer(LPVOID lpOnTimerParam);

};

extern CTDT_Stream * g_pTDT_Stream;

#endif //  #ifndef __CTDT_STREAM_H_