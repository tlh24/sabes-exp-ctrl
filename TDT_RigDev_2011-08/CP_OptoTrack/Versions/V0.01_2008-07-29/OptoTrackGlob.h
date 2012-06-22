// OptoTrackGlob.h
#define N_DISPL_SENSORS     4
#define N_DISPL_COORD       3


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
int g_GetLatestCoordinates( int nSensorsMax,
                            int * pnSensors,
                            int * piFrame,
                            double * pdTimeMs, 
                            double * pdXYZ );
int g_GetSignalDistortion( int aiDistortion[N_DISPL_SENSORS] );
HWND g_GetWindowHandle();
