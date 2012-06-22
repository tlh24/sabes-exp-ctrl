#include "TimeStamp.h"

//===========================================================================
CTimeStamp::CTimeStamp(){
  LARGE_INTEGER m_liFreq;

  QueryPerformanceCounter(  &m_liZeroTime );
  QueryPerformanceFrequency( &m_liFreq );

  m_dCountFrequency_kHz = (double)m_liFreq.QuadPart/1000.0;
  ResetTime();
}

//===========================================================================
CTimeStamp::~CTimeStamp(){

}

//===========================================================================
void CTimeStamp::ResetTime(){
  QueryPerformanceCounter(  &m_liZeroTime );
}

//===========================================================================
double CTimeStamp::TimeStampMs(){
  LARGE_INTEGER liCurrTime;

  QueryPerformanceCounter(  &liCurrTime );
  return  double(liCurrTime.QuadPart - m_liZeroTime.QuadPart)/m_dCountFrequency_kHz;
}

