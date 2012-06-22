#ifndef GL_ENGINE_H
#define GL_ENGINE_H

#include "Util\PointerArray.h"

#define WIN_WIDTH_PIX 1024
#define WIN_HEIGHT_PIX 768
#define IS_OFF_WINDOW(x,y) ( ((x)<0 || (x)>WIN_WIDTH_PIX || (y)<0 || (y)>WIN_HEIGHT_PIX) ? 1:0 )

// Mouse event indexes for storing in g_aiMouseEvents
#define MOUSE_LEFT      0
#define MOUSE_MIDDLE    1
#define MOUSE_RIGHT     2

#define MOUSE_DOWN      0
#define MOUSE_UP        1
#define MOUSE_DBLCLICK  2

#define TRANSF_MTX_N_1     2
#define TRANSF_MTX_N_2     6

#define MAX_LOG_EVENTS     50000

#define TWO_PI  (3.1415926535 * 2.0)
#define DEGS_TO_RADS (TWO_PI/360.0)

extern char    g_szVersion[];
extern char    g_szAppTitile[];
extern HDC		 g_hDC;		// Private GDI Device Context
extern BOOL    g_blnFullScreen;  // TRUE if in full-screen mode
extern BOOL    g_blnBatchUpdate; // In this mode individual objects cannot request an update
extern BOOL    g_blnDoRedraw;    // flag to redraw the screen
extern BOOL    g_blnFrameSync;   // flag to wait for the frame onset

extern int g_iMouseShowFlag;        // mouse cursor visible flag
extern POINTS g_tMouseXY;           // current mouse coordinates
extern int g_aiMouseEvents[3][3];   // mouse events

extern double g_adTransfMtx[TRANSF_MTX_N_1][TRANSF_MTX_N_2];

// Log-related globals 
extern int g_nLogEvents;
extern int g_iLastQueuedEvent;
extern int g_aiLogIDs[MAX_LOG_EVENTS];
extern double g_adEventTimes[MAX_LOG_EVENTS];

// Coeffs to convert from frames to time, ms
extern double g_dTimeOffset;
extern double g_dTimeScale;

// we store the list in the global container
extern CPointerArray g_ptObjectList;

void g_MouseCursorOn();
void g_MouseCursorOff();
// Convert from millimiters to pixels using quadratic approximation
void g_TransformCoordinatesD( double dXmm, double dYmm, 
                              double * pdXpix, double * pdYpix );
// Convert from millimiters to pixels using quadratic approximation
void g_TransformCoordinatesF( double dXmm, double dYmm, 
                              float * pfXpix, float * pfYpix );
// Gradient of conversion from millimiters to pixels using quadratic approximation
void g_TransformGradientD( double J[][2], double xp, double yp );


void g_ResetEventLog( );
int  g_QueueLogEvent( int iLogID );
void g_RequestUpdate( int iLogID );

int g_StartGL_Engine( HINSTANCE hInstance, int nShowCmd ); 
void g_MainLoop();
void g_StopGL_Engine();

#endif   //#ifndef GL_ENGINE_H
