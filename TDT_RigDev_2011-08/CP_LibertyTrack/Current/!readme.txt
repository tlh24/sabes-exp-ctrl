Liberty 
  configure data request
  data are stored in Liberty frame format (set by the configuration)
  conversion is performed on external data request
  change in sensor setup requires Disconnect/Connect
  change in TransformMatrix can be done any time. All data conversions will use this matrix afterwards
  change in time-scale can also be done at any time and will affect all data (including already buffered data)




Version string is in CP_LibertyTrack.cpp

CP_LibertyTrack.cpp - implementation of WinMain and other Windows functions
LibertyTrackGlob.cpp - wrapper functions that MainDialog uses to access g_pLibertyTrack




CLibertyTrack * g_pLibertyTrack;   - pointer to the main object in LibertyTrack.cpp
CLibertyTrack 
	-> CSlideBuf
	-> CTimeStamp (not used now)
Data are collected on Windows events: WM_PI_RAWDATA_READY in the message loop, mapped to OnNewData() 

LibertyTrack.h, LibertyTrack.cpp - implementation of CLibertyTrack

SlideBuf.h, SlideBuf.cpp - implementation of CSlideBuf
TimeStamp.h, TimeStamp.cpp - implementation of CTimeStamp (not used)

CP_LibertyTrackCom.idl : IDL specs of the COM interface
CP_LibertyClass.h, CP_LibertyClass.cpp - implementation of COM interface

ClassFactory.h, ClassFactory.cpp - implementation of CFactory, used to 
                                   create the COM interface object

RegisterCom.h, RegisterCom.cpp - used to register/unregister COM object 

CP_printf.h, CP_printf.cpp - implementation of CP_printf()
Console.h, Console.cpp - implementation of the log window



