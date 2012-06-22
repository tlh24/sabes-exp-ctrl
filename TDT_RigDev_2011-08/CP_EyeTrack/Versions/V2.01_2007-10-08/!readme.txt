Version string is in EyeTrackGlob.cpp

CP_EyeTrack.cpp - implementation of WinMain and other Windows functions
EyeTrackGlob.h, EyeTrackGlob.cpp - wrapper functions that MainDialog uses 
                                   to access CP_EyeTrack COM server and g_pEyeTrack
BuildOptions.h - defines DEBUG_THRESHOLD and LPT - related options

Main application object
CEyeTrack 
  -(has)  Tserial
  -> CReadingThread
  -> CSlideBuf
  -> CTimeStamp


CEyeTrack * g_pEyeTrack;   - pointer to the main object in EyeTrack.cpp

EyeTrack.h, EyeTrack.cpp - implementation of CEyeTrack

ReadingThread.h, ReadingThread.cpp - implementation of CSerialThread (generic class for thread creation/looping/stopping)
SlideBuf.h, SlideBuf.cpp - implementation of CSlideBuf
TimeStamp.h, TimeStamp.cpp - implementation of CTimeStamp
tserial.h, tserial.cpp - implementation of Tserial

CP_EyeTrackCom.idl : IDL source for the COM interface of CP_EyeTrack.exe
CP_ET_Class.h, CP_ET_Class.cpp - implementation of COM interface

ClassFactory.h, ClassFactory.cpp - implementation of CFactory, used to 
                                   create the COM interface object

RegisterCom.h, RegisterCom.cpp - used to register/unregister COM object 

CP_printf.h, CP_printf.cpp - implementation of CP_printf()
Console.h, Console.cpp - implementation of the log window


