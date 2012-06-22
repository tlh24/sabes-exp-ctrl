#include <windows.h>
#include <comdef.h>


#include "EyeTrack.h"
#include "EyeTrackGlob.h"
#include "CP_printf.h"



// The object pointer, we have only one
CEyeTrack * g_pEyeTrack;
//float x_afBuffer[100000];
VARIANT x_vrtRes;



//==============================================================================
CEyeTrack::CEyeTrack(){
 
  // Initialize to identity transform
  m_adCalibrationMatrix[0][0] = 0;
  m_adCalibrationMatrix[0][1] = 1;
  m_adCalibrationMatrix[0][2] = 0;
  m_adCalibrationMatrix[0][3] = 0;
  m_adCalibrationMatrix[0][4] = 0;
  m_adCalibrationMatrix[0][5] = 0;
  m_adCalibrationMatrix[1][0] = 0;
  m_adCalibrationMatrix[1][1] = 0;
  m_adCalibrationMatrix[1][2] = 1;
  m_adCalibrationMatrix[1][3] = 0;
  m_adCalibrationMatrix[1][4] = 0;
  m_adCalibrationMatrix[1][5] = 0;

  m_iIsCalibrated = 0;

}

//==============================================================================
CEyeTrack::~CEyeTrack(){
  //TODO: Check state and unwind if necessary
  DisconnectISCAN();
}

//==============================================================================
int CEyeTrack::ConnectISCAN(  ){
  m_InitSerialThread( );
  CP_printf("ConnectISCAN\n");
  return 0;
}

//==============================================================================
int CEyeTrack::DisconnectISCAN(){
//  HRESULT hRet;

  m_CloseSerialThread( );
  CP_printf("DisconnectISCAN\n");

  return 0;
}

//==============================================================================
int CEyeTrack::GetVersion( BSTR * pbstVer){
  
  _bstr_t bscTmp(g_szVersion);
  *pbstVer =  bscTmp.copy();

  return 0;
}
//==============================================================================
int CEyeTrack::GetVersion( char ** pszVer){
  
  * pszVer = g_szVersion;
  return 0;
}

//==============================================================================
int CEyeTrack::GetCalibrationMatrixPtr(  double ** pdMtx ){
  
  * pdMtx = (double *) m_adCalibrationMatrix;
  return 0;
}

//==============================================================================
int CEyeTrack::GetCalibrationFlag(   int * piIsCalibrated ){
  
  * piIsCalibrated = m_iIsCalibrated;
  return 0;
}

//==============================================================================
int CEyeTrack::SetCalibrationFlag(  int iIsCalibrated ){
  
  m_iIsCalibrated = iIsCalibrated;
  return 0;
}
//==============================================================================
int CEyeTrack::CalcCalibCoordinates( double dX_Raw, double dY_Raw, double * pdX_Calib, double * pdY_Calib ){

  double dRawMtx[CALIB_N_J];
  int j;
  double dX, dY;

  dRawMtx[0] = 1;
  dRawMtx[1] = dX_Raw;
  dRawMtx[2] = dY_Raw;
  dRawMtx[3] = dX_Raw * dX_Raw;
  dRawMtx[4] = dX_Raw * dY_Raw;
  dRawMtx[5] = dY_Raw * dY_Raw;

  dX = 0; dY = 0;
  for(j = 0; j< CALIB_N_J; j++ ) {
    dX += dRawMtx[j] * m_adCalibrationMatrix[0][j];
    dY += dRawMtx[j] * m_adCalibrationMatrix[1][j];
  }
  * pdX_Calib = dX;
  * pdY_Calib = dY;

  return 0;
}
//==============================================================================
int CEyeTrack::CmdStart(){
  CP_printf("CEyeTrack::CmdStart()\n");

  ConnectISCAN();

  return 0;
}

//==============================================================================
int CEyeTrack::CmdStop(){
  CP_printf("CEyeTrack::CmdStop()\n");

  DisconnectISCAN();

  return 0;
}

