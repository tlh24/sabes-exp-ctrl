#ifndef __COptoTRACK_H_
#define __COptoTRACK_H_

#include <windows.h>
#include "ReadingTimer.h"
#include "Opto\ndtypes.h"
#include "Opto\ndhost.h"
#include "Opto\ndopto.h"

#define N_SENSROS_MAX 32
#define CALIB_N_I     2
#define CALIB_N_J     6

#define BUFFER_SIZE_SECONDS 5
#define FRAME_RATE_HZ       100

#define btSensorInactive    0
#define btSensorRequested   1
#define btSensorActive      2

typedef struct SensorStateTag {
  int iPort;      // Port on Optotrack, ignored on Liberty
  int iSensorIdx; // Sensor index, starts from 1
  int iIsOn;      // The sensor is requested to be ON
//  int iIsActive;  // The sensor is currently active
//  int iIsIgnored; // Data from this sensor are ignored. This allows to set Optotrack sensors non-consecutively
                  // This flag is ignored on Liberty

} SensorStateStruct;

typedef struct OptoFrameTag {
	short sPreamble;                // #define LIBERTY_PREAMBLE 0x594C
	BYTE  bStation; 
	BYTE  bCmd;
	BYTE  bErr;
	BYTE  bReserved;
	short sLength;
  unsigned int uiFrameIdx;        //  int32 PDI_MODATA_FRAMECOUNT
  unsigned int uiTimeMs;          //  int32 PDI_MODATA_TIMESTAMP
  unsigned int uiExternalSync;    //  1 = detected, otherwise 0; int32 PDI_MODATA_EXTSYNC
  unsigned int uiDistortionLevel; //  0 = None, 1 = Minor, 2 = Significant;   int32 PDI_MODATA_DISTLEV
  float afCoord[3];               //  (x, y, z) Cartesian pos coords; 3floats, 12bytes PDI_MODATA_POS
  float afAngles[3];              //  (az, el, ro) Euler ori angles; 3floats, 12bytes PDI_MODATA_ORI

} tOptoFrame;

typedef struct ServerFrameTag {
  double dReceivedTimeMs;         //
  double dCalcTimeMs;
  tOptoFrame OptoFrame; 
} tServerFrame;

#define PNO_BUF_SIZE     sizeof(tOptoFrame) * 8 * 240    // 8 sensors, 1 sec


class COptoTrack: public CReadingTimer, public CSlideBuf, public CTimeStamp {

private:
  int m_IsConnected;
  int m_iIsRunning;
  int m_nSensorsMax;
  int iSensorState[N_SENSROS_MAX];
  int m_nActiveSensors;
  int iActiveSensorIdx[N_SENSROS_MAX];
  BYTE m_pPnoBuf[PNO_BUF_SIZE];
  int m_iPrevFrame;
  tServerFrame m_LatestFrames[N_SENSROS_MAX];  

  double m_adCalibrationMatrix[CALIB_N_I][CALIB_N_J];
  int m_iIsCalibrated;

  int m_PrintOptoError( int iError );

public:

  COptoTrack();
  ~COptoTrack();

  int GetN_Sensors( int * piConfigMax, int * piDeviceMax, int * piDeviceActive );
  int SetSensorsOn();
  int SetSensorsOff();
  int SetSensors( int nSensors, int iSensorOn );
  int GetSensors( int iSensor, int * piSensorOn );
  int ResetTimeAndBuffer();
  int ConnectOpto();
  int DisconnectOpto();
  virtual int ProcessTimerEvent( int iTimerCounter );
  int GetOptoState( int * piState ); 
  int GetVersion( BSTR * pbstVer);
  int GetVersion( char ** pszVer);
  int GetCalibrationMatrixPtr(  double ** pdMtx );
  int GetCalibrationFlag(   int * piIsCalibrated );
  int SetCalibrationFlag(  int iIsCalibrated );
  int CalcCalibCoordinates( double dX_Raw, double dY_Raw, double * pdX_Calib, double * pdY_Calib );
  int GetLatestFramePtr( int iSensor, tServerFrame ** ppFrame );


};

extern COptoTrack * g_pOptoTrack;

#endif //  #ifndef __COptoTRACK_H_