#ifndef __COptoTRACK_H_
#define __COptoTRACK_H_


#include "SlideBuf.h"
#include "ReadingThread.h"
#include "Opto\ndtypes.h"
#include "Opto\ndhost.h"
#include "Opto\ndopto.h"

#define N_CAMERAS 3

#define N_SENSORS_AT_PORT_MAX 24
#define N_PORTS               4
#define N_SENSORS_MAX        ( N_SENSORS_AT_PORT_MAX * N_PORTS )
#define N_COORD           3     // XYZ

#define N_SENSOR_PARAMS   2     // iSensor, iPort



#define N_TRANSFORMS      2
#define TRANSFORM_N_I     3
#define TRANSFORM_N_J     4

#define BUFFER_SIZE_SECONDS 1000
#define FRAME_RATE_HZ       100.0
#define FRAME_TIME_MS       (1000.0/FRAME_RATE_HZ)

#define MAX_OPTOERROR_LEN ( MAX_ERROR_STRING_LENGTH + 1) 

#define btSensorInactive    0
#define btSensorRequested   1
#define btSensorActive      2

typedef enum etDistortionLevelTag{
  ecNoDistortion = 0,
  ecMinorDistortion = 1,
  ecHighDistortion = 2,
  ecSensorOff      = 4 
} etDistortionLevel;

// we use this structure to set sensors 
typedef struct SensorInfoTag {
  int iSensor;  // Sensor index, from 0 to N_SENSORS_AT_PORT_MAX-1
  int iPort;   // Port index, starts from 0, ignored on Liberty
} tSensorInfo;

// we use this structure to keep the state
typedef struct SensorStateTag {
  int iPort;      // Port on Optotrack, ignored on Liberty, starts from 0
  int iSensor; // Sensor index at the port, starts from 0
  int iTransformIdx;   // Transform index, starts from 0
//  int iSaveToBuffer;      // The sensor is used flag
} tSensorState;

// we use this structure to input coordinates
typedef struct tfXYZTag {
  float X;
  float Y;
  float Z;
} tfXYZ;

// we use this structure to output coordinates/angles
typedef struct tdXYZTag {
  double X;
  double Y;
  double Z;
} tdXYZ;


typedef float tTransformMtx[TRANSFORM_N_I][TRANSFORM_N_J]; 

typedef struct OptoFrameTag {
  int iFrameIdx;        //  first frame is 1
  int iDistortionLevel; //  0 = None, 1 = Minor, 2 = Significant;   
  tfXYZ tfCoord;        //  (x, y, z) Cartesian coords; 3floats

} tOptoFrame;


class COptoTrack:  public CReadingThread, public CSlideBuf {

private:
  int m_nSensorsToRead;   // number of sensors in the receiving buffer
  int m_nSensorsToWrite;  // number of sensors to save in the SlideBuffer
  int m_iReadCount;
  int m_iOptoFrameIdx;
  int m_iPrevFrame;
  int m_nMissedTimes;
  int m_nMissedFrames;
  double m_dTimeC0;
  double m_dTimeC1;
  // this array keeps track of m_nSensorsToWrite sensors
  tSensorState m_atSensorState[N_SENSORS_MAX];
  // we keep record of m_nSensorsToRead sensors in m_aiWriteFlag[]
  // Values are ordered by port/sensor, 
  // exactly as the coords are ordered in the receiving buffer
  int m_aiWriteFlag[N_SENSORS_MAX]; 
  int m_anSensorsPerPort[N_PORTS];
  int m_iDistirtionLevel[N_SENSORS_MAX];
  tTransformMtx m_atTransformMtx[N_TRANSFORMS];


  void m_CalcTime( int iFrame, double * pdTimeMs);
  void m_TransformCoordinates( int iTrans, tfXYZ * ptInXYZ,   tdXYZ * ptOutXYZ );
  int m_PrintOptoError( int iError );

  virtual int ReadingFunc( );
  virtual int ShutdownFunc( );


public:

  COptoTrack();
  ~COptoTrack();

  int GetVersion( BSTR * pbstVer);
  int GetVersion( char ** pszVer);
  int GetSensors( tSensorInfo * atSensorInfo );
  int SetSensors( int nSensors, tSensorInfo * atSensorInfo );
  int ActivateSensors();
  int DeactivateSensors();
  int GetSensorsTransformIdx( int * piTransformIdx );
  int SetSensorsTransformIdx( int nSensors, int * piTransformIdx );
  int GetTransformMatrix(  int iTransform, float * pfMtx );
  int GetTransformMatrix(  int iTransform, double * pdMtx );
  int SetTransformMatrix(  int iTransform, float * pfMtx );
  int SetTransformMatrix(  int iTransform, double * pdMtx );
  int GetFrameCount( int *pnFrames);
  int GetTimeScale( double *pdC0, double *pdC1);
  int SetTimeScale( double dC0, double dC1);
  int GetN_Sensors( int * piDeviceMax, int * piDeviceActive );
  int ConnectOpto();
  int DisconnectOpto();
  int GetOptoState( int * piState ); 
  int GetSignalDistortion( int aiDistortion[N_SENSORS_MAX] );

  int ParseBuffer(int iSensorIdx,
                  int nFrames,
                  void * pvSrcBuffer,
                  double * pdTimeStamps, 
                  tdXYZ * pdCoordinates,
                  tdXYZ * pdVelocities  );

  int ParseBuffer(int nFrames,
                  void * pvSrcBuffer,
                  double * pdTimeStamps, 
                  tdXYZ * pdCoordinates,
                  tdXYZ * pdVelocities  );

};


#endif //  #ifndef __COptoTRACK_H_
