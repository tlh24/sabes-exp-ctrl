// EyeTrackGlob.h

extern char * g_szVersion;
// Here we declare functions that MainDialog uses 
// to control CP_EyeTrack COM server

typedef struct ET_StructTag {
  double pdTimeMs;
  int iRawX;
  int iRawY;
  double dX;
  double dY;
  int iFrame;
  int nMissed;
  int iMissCount;
} ET_Struct;


int g_RegisterCOM();
int g_UnregisterCOM();
int g_Init_EyeTrack( );
int g_OkToRelease( );
int g_Release_EyeTrack();
int g_CmdStart();
int g_CmdStop();
int g_GetLatestData( ET_Struct * ptET_Data );

