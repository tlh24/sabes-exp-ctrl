// OptoTrackGlob.h


extern char * g_szVersion;
extern HWND g_hWnd;

// Here we declare functions that MainDialog uses 
// to control CP_OptoTrack COM server

int g_RegisterCOM();
int g_UnregisterCOM();
int g_Init_OptoTrack( );
int g_OkToRelease( );
int g_Release_OptoTrack();
int g_CmdStart();
int g_CmdStop();
int g_GetLatestRawCoordinates( int iIdx, double * pdTimeMs, 
                               float * pfRawX, float * pfRawY,  float * pfRawZ);
HWND g_GetWindowHandle();
