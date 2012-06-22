// Stream_Glob.h



// Here we declare functions that MainDialog uses 
// to control CP_TDT_Stream COM server

int g_RegisterCOM();
int g_UnregisterCOM();
int g_InitStream( HWND hWnd );
int g_OkToRelease( );
char * g_GetVersion();
int g_ReleaseStream();
int g_Test();
