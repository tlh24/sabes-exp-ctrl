#ifndef __CEYETRACK_H_
#define __CEYETRACK_H_


#include "SerialThread.h"

#define CALIB_N_I     2
#define CALIB_N_J     6

class CEyeTrack: public CSerialThread {

public:

  CEyeTrack();
  ~CEyeTrack();
  int ConnectISCAN();
  int DisconnectISCAN();
  int GetVersion( BSTR * pbstVer);
  int GetVersion( char ** pszVer);
  int GetCalibrationMatrixPtr(  double ** pdMtx );
  int GetCalibrationFlag(   int * piIsCalibrated );
  int SetCalibrationFlag(  int iIsCalibrated );
  int CalcCalibCoordinates( double dX_Raw, double dY_Raw, double * pdX_Calib, double * pdY_Calib );
  int CmdStart();
  int CmdStop();

private:
  double m_adCalibrationMatrix[CALIB_N_I][CALIB_N_J];
  int m_iIsCalibrated;
};

extern CEyeTrack * g_pEyeTrack;

#endif //  #ifndef __CEYETRACK_H_