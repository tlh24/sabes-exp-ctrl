// LibertyTrackGlob.h

#define N_DISPL_SENSORS     4
#define N_DISPL_COORD       3
#define N_COORD_ANGL        6     // XYZ and 3 angles

extern char * g_szVersion;
extern HWND g_hWnd;

// Here we declare functions that MainDialog uses 
// to control CP_LibertyTrack COM server

int g_RegisterCOM();
int g_UnregisterCOM();
int g_Init_LibertyTrack( );
int g_OkToRelease( );
int g_Release_LibertyTrack();
void g_OnNewData( WPARAM wParam, LPARAM lParam );
int g_CmdStart();
int g_CmdStop();
int g_GetLatestCoordinates( int * pnSensors,
                            double * pdTimeMs, 
                            double pdXYZ[N_DISPL_SENSORS][N_COORD_ANGL]);
int g_GetSignalDistortion( int aiDistortion[N_DISPL_SENSORS] );
HWND g_GetWindowHandle();
void g_GetLibertyResult( char ** pszResult, int * piResult );
