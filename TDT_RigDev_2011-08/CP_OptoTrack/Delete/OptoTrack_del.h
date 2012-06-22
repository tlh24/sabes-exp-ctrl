#ifndef __COptoTRACK_H_
#define __COptoTRACK_H_

#include <windows.h>
//#include "ReadingTimer.h"
#include "ReadingThread.h"
#include "SlideBuf.h"
#include "TimeStamp.h"

#include "Opto\ndtypes.h"
#include "Opto\ndhost.h"
#include "Opto\ndopto.h"

#define N_CAMERAS 3

#define N_SENSROS_AT_PORT_MAX 24
#define N_PORTS               4
#define N_SENSROS_MAX        ( N_SENSROS_AT_PORT_MAX * N_PORTS )
#define N_COORD               3      // X,Y,Z
#define N_SENSOR_PARAMS       3      // iSensor, iTransform, iPort

#define N_TRANSFORMS      2
#define TRANSFORM_N_I     3
#define TRANSFORM_N_J     4

#define BUFFER_SIZE_SECONDS 100
#define FRAME_RATE_HZ       100.0f
#define FRAME_TIME_MS       (1000.0f/FRAME_RATE_HZ)

#define btSensorInactive    0
#define btSensorRequested   1
#define btSensorActive      2


// we use this structure to set/get the sensor state only
typedef struct SensorPortTag {
  int iSensor;        // Sensor index at the port, starts from 0
  int iTransform;     // which transform to use, starts from 0
  int iPort;          // Port on Optotrack, ignored on Liberty, starts from 0
} SensorInfo;

// we use this structure to keep the state
typedef struct SensorStateTag {
  int iSensor; // Sensor index at the port, starts from 0
  int iTransform;   // Transform index, starts from 0
  int iPort;      // Port on Optotrack, ignored on Liberty, starts from 0
  int iSaveToBuffer;      // The sensor is used flag
} SensorStateStruct;

typedef float tTransformMtx[TRANSFORM_N_I][TRANSFORM_N_J]; // afTransformMtx;

typedef struct FrameHeaderTag {
  double dMeasurementTimeMs;      // Calculated time of actual measurement
  int    iFrame;                  // OptoTrak frame idx
  int    nSensors;                // Number of sensor data to follow
} FrameHeaderStruct;

typedef struct OptoFrameTag {
  FrameHeaderStruct tHeader;
  Position3d        atXYZ[N_SENSROS_MAX];
} OptoFrameStruct;

class COptoTrack: public CReadingThread, public CSlideBuf {

private:
  int m_IsConnected;
  int m_nSensorsToRead;
  int m_nSensorsToWrite;
  int m_anSensorsPerPort[N_PORTS];
  SensorStateStruct m_atSensorState[N_SENSROS_MAX];
  int m_ReadCount;
  int m_nMissedCount;
  int m_nMissedFrames;
  int m_iPrevFrame;
  int m_iFrameSize;

  tTransformMtx m_atTransformMtx[N_TRANSFORMS];
  int m_PrintOptoError( int iError );

  virtual int ReadingFunc( );
  virtual int ShutdownFunc( );

public:

  COptoTrack();
  ~COptoTrack();

  int GetVersion( BSTR * pbstVer);
  int GetVersion( char ** pszVer);
  int GetSensors( SensorInfo * ptSensorInfo );
  int SetSensors( int nSensors, SensorInfo * ptSensorInfo );
  int GetTransformMatrix(  int iTransform, float * pfMtx );
  int SetTransformMatrix(  int iTransform, float * pfMtx );
  int GetN_Sensors( int * piConfigMax, int * pnSensorsToRead, int * pnSensorsToWrite );
  int ConnectOpto();
  int DisconnectOpto();
  int GetOptoState( int * piState ); 
  int ActivateSensors();
  int DeactivateSensors();

  int GetLatestData( double * pdTimeMs,
                     int * piFrame,
                     int * pnMissedFrames,
                     int * pnMissedCount,
                     int nSensors,
                     float * pfXYZ ) ;

  int ParseBuffer( int nFrames,
                   void * pvSrcBuffer, 
                   double * pdTimeStamps, 
                   float * pfCoordinates,
                   float *pfVelocities );

  int ParseBuffer( int iSensor,
                   int nFrames,
                   void * pvSrcBuffer, 
                   double * pdTimeStamps, 
                   float * pfCoordinates,
                   float *pfVelocities );

};

extern COptoTrack * g_pOptoTrack;

#endif //  #ifndef __COptoTRACK_H_