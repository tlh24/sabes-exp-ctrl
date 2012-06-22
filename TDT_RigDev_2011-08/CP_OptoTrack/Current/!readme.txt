Version string is in CP_OptoTrack.cpp

CP_OptoTrack.cpp - implementation of WinMain and other Windows functions
OptoTrackGlob.h, OptoTrackGlob.cpp - wrapper functions that MainDialog uses 
                                     to access CP_OptoTrack COM server and g_pOptoTrack

Main application object
COptoTrack 
  : CReadingThread
  : CSlideBuf


COptoTrack * g_pOptoTrack;   - pointer to the main object in OptoTrackGlob.cpp

OptoTrack.h, OptoTrack.cpp - implementation of COptoTrack

ReadingThread.h, ReadingThread.cpp - implementation of CSerialThread
  uses two user-defined functions:
      virtual int ReadingFunc() = 0;    // called in the loop
      virtual int ShutdownFunc( ) = 0;  // called on loop termination

SlideBuf.h, SlideBuf.cpp - implementation of CSlideBuf
                           keeps the last N items stored, 
                           item numbers are consecutive (no wrapp-arounds)

CP_OptoTrackCom.idl : IDL source for the COM interface of CP_OptoTrack.exe

CP_OptoClass.h, CP_OptoClass.cpp - implementation of COM interface

ClassFactory.h, ClassFactory.cpp - implementation of CFactory, used to 
                                   create the COM interface object

RegisterCom.h, RegisterCom.cpp - used to register/unregister COM object 

\Util
CP_printf.h, CP_printf.cpp - implementation of CP_printf()
Console.h, Console.cpp - implementation of the log window used by CP_printf
VariantLib.h, VariantLib.cpp - SafeArray in a Variant helper functions

