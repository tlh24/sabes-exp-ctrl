#ifndef __CLibertyTRACK_H_
#define __CLibertyTRACK_H_


#include "SlideBuf.h"
// #include "TimeStamp.h"
#include "Liberty\PDI.h"

#define N_SENSORS_MAX     4
#define N_COORD           3     // XYZ

#define N_SENSOR_PARAMS   2     // iSensor, iPort



#define N_TRANSFORMS      2
#define TRANSFORM_N_I     3
#define TRANSFORM_N_J     4

#define BUFFER_SIZE_SECONDS 1000
#define FRAME_RATE_HZ       240

typedef enum etDistortionLevelTag{
  ecNoDistorsion = 0,
  ecMinorDistorsion = 1,
  ecHighDistortion = 2,
  ecSensorOff      = 4 
} etDistortionLevel;

// we use this structure to set sensors to keep it Optotrack-compatible
typedef struct SensorInfoTag {
  int iSensor;  // Sensor index, starts from 0
  int iPort;   // Port index, starts from 0, ignored on Liberty
} tSensorInfo;

// we use this structure to keep the state
typedef struct SensorStateTag {
  int iSensor;         // Sensor index, starts from 0
  int iTransformIdx;   // Transform index, starts from 0
} tSensorState;

// we use this structure to transfer coordinates/angles
typedef struct tfXYZTag {
  float X;
  float Y;
  float Z;
} tfXYZ;


typedef float tTransformMtx[TRANSFORM_N_I][TRANSFORM_N_J]; 

typedef struct LibertyFrameTag {
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
  tfXYZ tfCoord;               //  (x, y, z) Cartesian pos coords; 3floats, 12bytes PDI_MODATA_POS
  tfXYZ tfAngles;              //  (az, el, ro) Euler ori angles; 3floats, 12bytes PDI_MODATA_ORI

} tLibertyFrame;

// = 1 sec
#define PNO_BUF_SIZE  (sizeof(tLibertyFrame) * N_SENSORS_MAX * FRAME_RATE_HZ) 


class CLibertyTrack: public CSlideBuf {

private:
  CPDIdev m_PdiDev;
  int m_IsConnected;
  volatile  int m_iIsRunning;   // flag to stop acquision 
  int m_iLibertyFrameIdx;
  int m_iFirstFrameIdx;
  int m_iPrevFrame;
  int m_nMarkedFrames;
  int m_nSensorsMax;
  int m_nActiveSensors;
  CPDImdat m_SensorDataList;  // used to configure Liberty output
  tTransformMtx m_atTransformMtx[N_TRANSFORMS];
  double m_dTimeC0;
  double m_dTimeC1;
  tSensorState m_atSensorState[N_SENSORS_MAX];
  int m_iDistirtionLevel[N_SENSORS_MAX];
  BYTE m_pPnoBuf[PNO_BUF_SIZE];  // used by Liberty library
//  tLibertyFrame m_LatestFrames[N_SENSORS_MAX]; // Liberty->SlideBuffer tmp storage 


  void m_CalcTime( int iFrame, double * pdTimeMs);
  void m_TransformCoordinates( int iTrans, tfXYZ * ptInXYZ,   tfXYZ * ptOutXYZ );
  int m_DisconnectLiberty();
  int m_GetNewData( PBYTE pBuf, long lngN_Bytes);

public:

  CLibertyTrack();
  ~CLibertyTrack();

  int GetVersion( BSTR * pbstVer);
  int GetVersion( char ** pszVer);
  int GetSensors( tSensorInfo * atSensorInfo );
  int SetSensors( int nSensors, tSensorInfo * atSensorInfo );
  int GetSensorsTransformIdx( int * piTransformIdx );
  int SetSensorsTransformIdx( int nSensors, int * piTransformIdx );
  int GetTransformMatrix(  int iTransform, float * pfMtx );
  int GetTransformMatrix(  int iTransform, double * pdMtx );
  int SetTransformMatrix(  int iTransform, float * pfMtx );
  int SetTransformMatrix(  int iTransform, double * pdMtx );
  int GetTimeScale( double *pdC0, double *pdC1);
  int SetTimeScale( double dC0, double dC1);
  int GetN_Sensors( int * piDeviceMax, int * piDeviceActive );
  int ConnectLiberty();
  int FinishAndDisconnect();
  int GetLibertyState( int * piState ); 
  int GetSignalDistortion( int aiDistortion[N_SENSORS_MAX] );

  static void OnNewData( CLibertyTrack * pLT, 
                         WPARAM wParam, 
                         LPARAM lParam );

  int ParseBuffer(int iSensorIdx,
                  int nFrames,
                  void * pvSrcBuffer,
                  double * pdTimeStamps, 
                  tfXYZ * pfCoordinates,
                  tfXYZ * pfVelocities  );

  int ParseBuffer(int nFrames,
                  void * pvSrcBuffer,
                  double * pdTimeStamps, 
                  tfXYZ * pfCoordinates,
                  tfXYZ * pfVelocities  );

};

extern CLibertyTrack * g_pLibertyTrack;

#endif //  #ifndef __CLibertyTRACK_H_