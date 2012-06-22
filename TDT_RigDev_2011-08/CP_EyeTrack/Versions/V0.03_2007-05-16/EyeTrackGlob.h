// EyeTrackGlob.h


extern char * g_szVersion;
// Here we declare functions that MainDialog uses 
// to control CP_EyeTrack COM server

int g_RegisterCOM();
int g_UnregisterCOM();
int g_Init_EyeTrack( );
int g_OkToRelease( );
int g_Release_EyeTrack();
int g_CmdStart();
int g_CmdStop();
int g_GetLatestRawCoordinates( double * pdTimeMs, int * piRawX, int * piRawY, int * piDigIn  );

