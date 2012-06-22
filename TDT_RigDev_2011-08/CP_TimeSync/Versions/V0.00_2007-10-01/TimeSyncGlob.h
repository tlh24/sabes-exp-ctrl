
#import "RPcoX.ocx" raw_dispinterfaces no_namespace

extern _DRPcoXPtr g_pRPcoX;

// Here we declare functions that MainDialog uses 
// to talk to the COM server

extern int g_RegisterCOM();
extern int g_UnregisterCOM();
extern int g_InitActX_Control( HWND hWnd );
extern int g_ReleaseActX_Control();
extern int g_Test();

extern float g_GetValue( char * szTag );
