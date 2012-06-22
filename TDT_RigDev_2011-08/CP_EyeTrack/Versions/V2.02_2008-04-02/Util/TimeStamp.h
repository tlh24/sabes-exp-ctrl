#ifndef TimeStamp_H
#define TimeStamp_H

#include <windows.h>

class CTimeStamp {
  public:
    CTimeStamp();
    ~CTimeStamp();

    void ResetTime();
    double TimeStampMs();

  private:
    LARGE_INTEGER m_liZeroTime;
    double m_dCountFrequency_kHz;  

};


#endif // #ifndef TimeStamp_H
