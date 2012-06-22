// Note: for OpenGL I used NeHe Tutorials, OpenGL Programming Guide and OpenGL SuperBible. SR
#include "BuildOptions.h"

#include "ATL_Defs.h"
#include "resource.h"            // Resource IDs for registry
#include "CP_Display.h"           // this file is generated by MIDL compiler

#include <gl\gl.h>               // Header File For The OpenGL32 Library
#include <gl\glu.h>              // Header File For The GLu32 Library

#include "VObject.h"             // needed for VObject calls
#include "VMouse.h"
#include "GL_Engine.h"

#include "Util\CP_printf.h"
#include "FrameCounter.h"


#define WIN_BITS_PER_PIX 32
#define WIN_FRAME_RATE_HZ 60

#define WIN_EX_STYLE_FULL  WS_EX_APPWINDOW  // Window Extended Style for full-screen
#define WIN_STYLE_FULL     WS_POPUP         // Window Style for full-screen


#define WIN_EX_STYLE_WIN  (WS_EX_APPWINDOW|WS_EX_WINDOWEDGE)  // Window Extended Style for windowed mode
#define WIN_STYLE_WIN     (WS_POPUPWINDOW |WS_CAPTION)        // Window Style for windowed mode

#define TIMER_ID 1
#define TIMER_PERIOD_MS 500    // 2 Hz rate


#define HALF_RAND_MAX  (RAND_MAX/2)


// Application globals
HDC       g_hDC=NULL;   // Private GDI Device Context
BOOL      g_blnFullScreen = 0;  // TRUE if in full-screen mode
BOOL      g_blnBatchUpdate = 0; // In this mode individual objects cannot request an update
BOOL      g_blnDoRedraw = 1;    // flag to redraw the screen
BOOL      g_blnFrameSync = 0;   // flag to wait for the frame onset

// Mouse globals
int g_iMouseShowFlag = 0;        // mouse cursor visible flag
POINTS g_tMouseXY;
int g_aiMouseEvents[3][3];

// Transform matrix
double g_adTransfMtx[TRANSF_MTX_N_1][TRANSF_MTX_N_2];

// Log-related globals 
int g_nLogEvents = 0;
int g_iLastQueuedEvent = -1;
int g_aiLogIDs[MAX_LOG_EVENTS];
double g_adEventTimes[MAX_LOG_EVENTS];

// Coeffs to convert from frames to time, ms
double g_dTimeOffset = 0;
double g_dTimeScale = 1000.0 / WIN_FRAME_RATE_HZ;


// we store the list in the global container object
CPointerArray g_ptObjectList; 


// Module globals
HGLRC     x_hRC=NULL;   // Permanent Rendering Context
HWND      x_hWnd=NULL;    // Holds Our Window Handle


float fRandPlusMinus(){
  return (float)(rand()-HALF_RAND_MAX)/float(HALF_RAND_MAX);
}
float fRandPlus(){
  return (float)(rand())/float(RAND_MAX);
}

// forward declarations
LRESULT CALLBACK x_WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void x_SetWindowedMode();

//==============================================================================
// Update window changes when the mode is switched
void x_UpdateWindowSettings( DWORD dwStyle, DWORD dwExStyle ) { 
  RECT rc;
  rc.left = 0;
  rc.right = WIN_WIDTH_PIX;
  rc.top = 0;
  rc.bottom = WIN_HEIGHT_PIX;

  // Get Window rectangle which provides requested client area
  if( !AdjustWindowRectEx(&rc, dwStyle, FALSE, dwExStyle)){
    CP_printfDbg(LEVEL_ERROR, "AdjustWindowRectEx() failed!\n");
  }   
  
  SetWindowPos( x_hWnd, HWND_TOP,
                0, 0,               // X, Y
                rc.right - rc.left, // width
                rc.bottom - rc.top, // height
                SWP_FRAMECHANGED    );
  
  ShowWindow(x_hWnd,SW_SHOW);           // Show The Window
}
//==============================================================================
// Set full-screen mode
void x_SetFullScreenMode( ) { 

  long lngRes;

  DEVMODE dmScreenSettings;               // Device Mode
  memset(&dmScreenSettings,0,sizeof(dmScreenSettings)); // Makes Sure Memory's Cleared
  dmScreenSettings.dmSize=sizeof(dmScreenSettings);   // Size Of The Devmode Structure
  dmScreenSettings.dmPelsWidth  = WIN_WIDTH_PIX;        // Selected Screen Width
  dmScreenSettings.dmPelsHeight = WIN_HEIGHT_PIX;       // Selected Screen Height
  dmScreenSettings.dmBitsPerPel = WIN_BITS_PER_PIX;         // Selected Bits Per Pixel
  dmScreenSettings.dmDisplayFrequency = WIN_FRAME_RATE_HZ;  // Selected frame rate, Hz
  // Mark fields of the structure which should be used in the mode change
  dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT|DM_DISPLAYFREQUENCY;

  // Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
  lngRes = ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN);
  if (lngRes!=DISP_CHANGE_SUCCESSFUL) {
    CP_printfDbg(LEVEL_ERROR,"Error. Could not set the video mode: %d\n", lngRes );
    x_SetWindowedMode();
  }

  SetWindowLong( x_hWnd, GWL_STYLE, WIN_STYLE_FULL );  // Windows Style
  SetWindowLong( x_hWnd, GWL_EXSTYLE, WIN_EX_STYLE_FULL );  // Window Extended Style
  x_UpdateWindowSettings(WIN_STYLE_FULL, WIN_EX_STYLE_FULL );

  CP_printfDbg(LEVEL_DEBUG,"Full-screen mode\n");
  g_blnFullScreen = TRUE;
  // Set actual mouse visibility in accordance with its state
  if(g_iMouseShowFlag) g_MouseCursorOn();                   
  else g_MouseCursorOff();
}

//==============================================================================
// Set windowed mode
void x_SetWindowedMode(){
  int iTmp;
  ChangeDisplaySettings(NULL,0);          // If So Switch Back To The Desktop

  SetWindowLong( x_hWnd, GWL_STYLE, WIN_STYLE_WIN );  // Windows Style
  SetWindowLong( x_hWnd, GWL_EXSTYLE, WIN_EX_STYLE_WIN );  // Window Extended Style
  x_UpdateWindowSettings(WIN_STYLE_WIN, WIN_EX_STYLE_WIN );
  InvalidateRect(NULL, NULL, TRUE);           // redraw the desktop
  // Save mouse state, show the mouse and restore the state
  iTmp = g_iMouseShowFlag;
  g_MouseCursorOn();  
  g_iMouseShowFlag = iTmp;
  
  CP_printfDbg(LEVEL_DEBUG,"Windowed mode\n");
  g_blnFullScreen = FALSE;
}


//==============================================================================
// Set vertical blank synchronization
// 0 == OFF, 1 == ON
// returns 0 on success
int x_SetSyncMode( int iMode ){

  typedef bool (APIENTRY *PFNWGLSWAPINTERVALFARPROC) (int);
  PFNWGLSWAPINTERVALFARPROC wglSwapIntervalEXT = NULL;

  // get the GL extension function to do the job
  wglSwapIntervalEXT = (PFNWGLSWAPINTERVALFARPROC)wglGetProcAddress("wglSwapIntervalEXT");
  if(wglSwapIntervalEXT == NULL) {
    return 1;
  }

  // this accepts one param, 0 = off and 1 = on
  wglSwapIntervalEXT(iMode);
  return 0;

}

//==============================================================================
int x_SetupOpenGL(){
  PIXELFORMATDESCRIPTOR pfd;
  int iPixelFormat;
  int iW, iH;
  RECT rc;

//  if(g_hDC) ReleaseDC( x_hWnd, g_hDC );

  g_hDC=GetDC(x_hWnd);  // get device context of our main window
  if (!g_hDC ) {        
    MessageBox(NULL,"Can't setup OpenGL: GetDC() failed!","ERROR",MB_OK|MB_ICONEXCLAMATION);
    return 1;
  }
  
  // specify desired pixel format 
  ZeroMemory( &pfd, sizeof( pfd ) );
  pfd.nSize = sizeof( pfd );
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
  pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.cColorBits = 24;
  pfd.cAlphaBits = 8;
  pfd.cDepthBits = 16;
  pfd.iLayerType = PFD_MAIN_PLANE;

  iPixelFormat=ChoosePixelFormat(g_hDC,&pfd);  // find pixel format matching our request
  if (!iPixelFormat) {
    MessageBox(x_hWnd,"Can't setup OpenGL: GetDC() failed!",
                 g_szAppTitile, MB_OK | MB_ICONEXCLAMATION );
    return 1;
  }

  if(!SetPixelFormat(g_hDC,iPixelFormat,&pfd)) { // set matching pixel format
    MessageBox(x_hWnd,"Can't setup OpenGL: SetPixelFormat() failed!",
                 g_szAppTitile, MB_OK | MB_ICONEXCLAMATION );
    return 1;  
  }

  x_hRC=wglCreateContext(g_hDC);  // create GL rendering context
  if (!x_hRC) {     
    MessageBox(x_hWnd,"Can't setup OpenGL: wglCreateContext() failed!",
                 g_szAppTitile, MB_OK | MB_ICONEXCLAMATION );
    return 1;               
  }

  if(!wglMakeCurrent(g_hDC,x_hRC)) { // use rendering context
    MessageBox(x_hWnd,"Can't setup OpenGL: wglMakeCurrent() failed!",
                 g_szAppTitile, MB_OK | MB_ICONEXCLAMATION );
    return 1;              
  }

  // Set vertical blank synchronization (not synchronized by default)
  if(x_SetSyncMode( 0 ) ) {
    MessageBox(x_hWnd,"Can't setup OpenGL: x_SetSyncMode() failed!",
                 g_szAppTitile, MB_OK | MB_ICONINFORMATION );
  }

  // Map drawing to screen pixels
  GetClientRect(x_hWnd, &rc );
  iW = rc.right - rc.left;
  iH = rc.bottom-rc.top;

  // Map drawings to pixels. 
  glViewport( 0, 0, iW, iH);       // set clipping region
  glMatrixMode(GL_PROJECTION);     // work with projection matrix (how we look at the scene)
  glLoadIdentity();                // set ProjectionMatrix to identity
  // flat projection, no perspective,
  // viewer at the point (0,0,-1), looking along the Z- axis
  // (0,0) = bottom left corner, (iW,iH) = upper right corner
  glOrtho(0, iW, 1, iH, 0, -1);     

  glMatrixMode(GL_MODELVIEW);      // work with model matrix (how objects are positioned/rotated)
  glLoadIdentity();                // set ModelViewMatrix to identity

  glEnable(GL_DEPTH_TEST);         // Enable depth testing
  glDepthRange(0.0f, 1.0f);        // Depth range is 0 to 1, everything outside will be clipped
	glDepthFunc(GL_LEQUAL);          // Smaller Z is on top 0 = near (front), 1 = far (back)

  // Version 1: Set Alpha as a boolean: 0.0 - transparent, above - solid
  // It is useful for bitmaps/textures
  glEnable(GL_ALPHA_TEST);         // enable Alpha channel testing
  glAlphaFunc(GL_GREATER, 0.0f);   // set boolean threshold
  // Version 2: set Alpha to blending:
  // in this case we need to draw in two steps: first all solid objects and then transparent ones,
  // depth buffer write should be disabled on the second pass
//  glEnable(GL_BLEND); 
//  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glDrawBuffer(GL_BACK);           // drawing will go to the back buffer
  glShadeModel(GL_FLAT);           // Disable color interpolation between vertices

  glClearColor( 0.0f, 0.0f, 0.0f, 0.0f ); // when clearing color, set color to black, non-transparent
  glClearDepth( 1.0f);  // when clearing depth, set depth to 1.0 = far (back) 
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );  // clear the buffer - color and depth

  CP_printf("GL Version: %s\n", glGetString(GL_VERSION));
  CP_printf("GL Vendor: %s\n", glGetString(GL_VENDOR));
  CP_printf("GL Renderer: %s\n", glGetString(GL_RENDERER));
  CP_printf("GLU Version: %s\n", gluGetString(GLU_VERSION));
  CP_printf("----------------------------------------\n");

  return 0;

}

//==============================================================================
// Show Mouse Pointer
void g_MouseCursorOn(){
  // do nothing in the windowed mode, but change the state variable
  if( g_blnFullScreen ){
    while(ShowCursor(TRUE)<0){};
  }
  g_iMouseShowFlag = 1;
}

//==============================================================================
// Hide Mouse Pointer
void g_MouseCursorOff(){
  // do nothing in the windowed mode, but change the state variable
  if( g_blnFullScreen ){
    while(ShowCursor(FALSE)>=0){}; 
  }
  g_iMouseShowFlag = 0;
}

//==============================================================================
// Convert from millimiters to pixels using quadratic approximation
void g_TransformCoordinatesD( double dXmm, double dYmm, 
                              double * pdXpix, double * pdYpix ){

  double dRawMtx[TRANSF_MTX_N_2];
  int j;
  double dX, dY;

  dRawMtx[0] = 1;
  dRawMtx[1] = dXmm;
  dRawMtx[2] = dYmm;
  dRawMtx[3] = dXmm * dXmm;
  dRawMtx[4] = dXmm * dYmm;
  dRawMtx[5] = dYmm * dYmm;

  dX = 0; dY = 0;
  for(j = 0; j< TRANSF_MTX_N_2; j++ ) {
    dX += dRawMtx[j] * g_adTransfMtx[0][j];
    dY += dRawMtx[j] * g_adTransfMtx[1][j];
  }
  * pdXpix = dX;
  * pdYpix = dY;

}

//==============================================================================
// Convert from millimiters to pixels using quadratic approximation
void g_TransformCoordinatesF( double dXmm, double dYmm, 
                              float * pfXpix, float * pfYpix ){

  double dX, dY;

  g_TransformCoordinatesD( dXmm, dYmm, &dX, &dY);
  * pfXpix = (float)dX;
  * pfYpix = (float)dY;

}

//==============================================================================
void  g_ResetEventLog( ){
  g_nLogEvents = 1;
  g_iLastQueuedEvent = 0;
  g_aiLogIDs[0] = 0;
  // TODO: get time from the frame counter 
  g_adEventTimes[0] = 0.0;  
}

//==============================================================================
int  g_QueueLogEvent( int iLogID ){
  // We don't log iLogID == 0, it is reserved for this purpose
  if( iLogID == 0 ) return 0; 
  // Out of event storage?
  if( g_iLastQueuedEvent >= (MAX_LOG_EVENTS -1) ){
    return 1;
  }
  g_iLastQueuedEvent++;
  g_aiLogIDs[g_iLastQueuedEvent] = iLogID;
  g_blnFrameSync = 1;  // sync to frame on next redraw
  return 0;
}

//==============================================================================
void  x_TimestampQueuedEvents(  ){
  double dTime;
  int iEvent;
  int iFrame = 0;

  //get frame count
  g_GetFrameCounter( &iFrame );
  dTime = g_dTimeOffset + g_dTimeScale * iFrame;
  
  for( iEvent = g_nLogEvents; iEvent <= g_iLastQueuedEvent; iEvent++ ) {
    g_adEventTimes[iEvent] = dTime;
  }
  g_nLogEvents = g_iLastQueuedEvent+1;

}

VOID CALLBACK TimerProc(
  HWND hwnd,         // handle to window
  UINT uMsg,         // WM_TIMER message
  UINT_PTR idEvent,  // timer identifier
  DWORD dwTime       // current system time
  ){

  CP_printf("callback\n");
}


//==============================================================================
// Create main application window
// Start GL_Engine
int g_StartGL_Engine( HINSTANCE  hInstance, int nShowCmd ) { 
  WNDCLASSEX wc;
  UINT uiTimerID; 
  int i, j;

  if( g_InitFrameCounter() ) {
    MessageBox( NULL, "Failed to initialize Frame Counter.\nMake sure that PortTalk driver is installed.", g_szAppTitile, MB_OK | MB_ICONERROR );
    return 1;
  }

  if( g_StartFrameCounter() ) {
    MessageBox( NULL, "Failed to start Frame Counter.\n", g_szAppTitile, MB_OK | MB_ICONERROR );
    return 1;
  }

  // register window class
  wc.cbSize = sizeof(wc);  
  wc.style = CS_OWNDC|CS_DBLCLKS;
  wc.lpfnWndProc = x_WndProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = hInstance;
  wc.hIcon = LoadIcon( NULL, IDI_APPLICATION );
  wc.hCursor = LoadCursor( NULL, IDC_CROSS );
  wc.hbrBackground = (HBRUSH)GetStockObject( BLACK_BRUSH );
  wc.lpszMenuName = NULL;
  wc.lpszClassName = g_szAppTitile;
  wc.hIconSm = LoadIcon( NULL, IDI_APPLICATION );
  RegisterClassEx( &wc );

  // create main window
  x_hWnd = CreateWindowEx(
    WIN_EX_STYLE_WIN,  // Extended style
    g_szAppTitile,     // Class name
    g_szAppTitile,     // Window title
    WIN_STYLE_WIN,     // Style
    0, 0, WIN_WIDTH_PIX, WIN_HEIGHT_PIX,  // position and size
    NULL, NULL, hInstance, NULL );

  // create timer for frame counter updates
  uiTimerID = SetTimer( x_hWnd,  TIMER_ID,  TIMER_PERIOD_MS,  NULL); //(TIMERPROC)TimerProc ); 
  if ( uiTimerID == 0){ 
    CP_printf("Error: could not create timer!"); // don't exit we are still functional
  }
  
  ShowWindow(x_hWnd, nShowCmd);
  UpdateWindow(x_hWnd);
  SetForegroundWindow(x_hWnd);      // Slightly Higher Priority
  SetFocus(x_hWnd);                 // Sets Keyboard Focus To The Window

#if  SET_FULLSCREEN_MODE
  x_SetFullScreenMode();
#else
  x_SetWindowedMode();
#endif


  if( x_SetupOpenGL()) {
    return 1;  // error messages are displayed in x_SetupOpenGL()
  }

  // Initialize global variables
  // clear mouse events
  for(i=0; i<3; i++) for(j=0; j<3; j++) g_aiMouseEvents[i][j]=0;
  g_tMouseXY.x = 0; 
  g_tMouseXY.y = 0; 

  // Initialize to identity transform
  // to X
  g_adTransfMtx[0][0] = 0;    // X - shift
  g_adTransfMtx[0][1] = 1;    // X
  g_adTransfMtx[0][2] = 0;    // Y
  g_adTransfMtx[0][3] = 0;    // X^2
  g_adTransfMtx[0][4] = 0;    // X*Y
  g_adTransfMtx[0][5] = 0;    // Y^2
  // to Y 
  g_adTransfMtx[1][0] = 0;    // Y - shift
  g_adTransfMtx[1][1] = 0;    // X
  g_adTransfMtx[1][2] = 1;    // Y
  g_adTransfMtx[1][3] = 0;    // X^2
  g_adTransfMtx[1][4] = 0;    // X*Y
  g_adTransfMtx[1][5] = 0;    // Y^2

  g_ResetEventLog( );

  return 0;
}

//==============================================================================
void g_RequestUpdate( int iLogID ) {
   g_QueueLogEvent( iLogID );
  // g_blnDoRedraw flag gets the program out of the message loop into drawing
  // After drawing it's set to 0 and we are in the message loop again
  // In batch mode individual objects cannot request an update
  if( !g_blnBatchUpdate ) g_blnDoRedraw = 1;

}

//==============================================================================
//// Here's Where We Do All The Drawing
void x_DrawWindow(void) {
  int iObj, nObjects;
  CVObject *pObj;

  nObjects = g_ptObjectList.GetN_Pointers();
  
  for( iObj = 0; iObj<nObjects; iObj++){
    g_ptObjectList.GetPointer( iObj, (void **) &pObj);
    glPushMatrix();
    glPushAttrib(GL_POLYGON_BIT);  // to avoid polygon interference (filled/hollow)
    pObj->Draw();
    glPopAttrib();
    glPopMatrix();
  }
}



//==============================================================================
void g_MainLoop(){
  MSG msg;
  BOOL blnQuit;

  blnQuit = FALSE;
  // program main loop
  while ( 1 ) {

    // Process mouse-move messages before processing others
    // This way we make sure that we get the latest mouse coordinates
    // mouse-event-accelleration was used for testing, not needed in the final version
//    while( PeekMessage(&msg, NULL, WM_MOUSEMOVE, WM_MOUSEMOVE, PM_REMOVE)){ 
//      TranslateMessage( &msg ); 
//      DispatchMessage( &msg );
//    }

    // Process messages
    // Note: all DCOM calls are made via the message loop
    while ( GetMessage( &msg, NULL, 0, 0 )  ) {
      TranslateMessage( &msg ); 
      DispatchMessage( &msg );   // This also processes DCOM
      // This flag is set by g_RequestUpdate() or CVMain::FinishBatchDraw()
      if( g_blnDoRedraw ) goto lblStartRedraw;
    } // while( GetMessage())

    // Get out on the WM_QUIT message
    if ( msg.message == WM_QUIT ) return;

lblStartRedraw:     // get here when redraw is requested

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the buffer
    // if we want to log an event, we sync to the next frame,
    // otherwise flip the buffers asynchroniously - affects glFinish()
    x_SetSyncMode( g_blnFrameSync );
    x_DrawWindow();
    glFlush();
    SwapBuffers( g_hDC );
    if ( g_blnFrameSync ) {
      glFinish();                 // wait wor the blank if requested by x_SetSyncMode()
      x_TimestampQueuedEvents();  // get frame counter and tag the pending events
    }

    g_blnDoRedraw = 0;  // reset the flag, we are done with the screen redraw
    g_blnFrameSync = 0;     // reset the flag, we did the sync

  }  // while( 1 )
} 

//==============================================================================
void  g_StopGL_Engine( ){

  KillTimer( x_hWnd, TIMER_ID);
  x_SetWindowedMode();
  // shutdown OpenGL
  wglMakeCurrent( NULL, NULL );
  wglDeleteContext( x_hRC );
  ReleaseDC( x_hWnd, g_hDC );

  DestroyWindow( x_hWnd );
  g_CloseFrameCounter();
  
}

//==============================================================================
// Window Procedure
// returns 0 on processed messages, other messages are processed by DefWindowProc()
// 
LRESULT CALLBACK x_WndProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam){

  switch (uiMsg){

    // Check if WM_SYSCOMMAND actually works
    case WM_SYSCOMMAND:             // Intercept System Commands
      switch (wParam)  {            // Check System Calls
        case SC_SCREENSAVE:         // Screensaver Trying To Start?
        case SC_MONITORPOWER:       // Monitor Trying To Enter Powersave?
        return 0;                   // Prevent From Happening
      }
      break;                  
      
    case WM_CLOSE:  // when we press <x> button on the window frame
      PostQuitMessage( 0 );
      return 0;
      
    case WM_DESTROY:
      PostQuitMessage( 0 );
      return 0;

    case WM_TIMER:
//      CP_printf("On timer\n");
      g_UpdateFrameCounter();
      return 0;

/*
//    case WM_SIZE:
//    case WM_MOVE:
//    case WM_DISPLAYCHANGE:
//    case WM_PAINT:
// if I put "return 0;" or "return 1;" after WM_PAINT, WM_TIMER messages are NOT generated!!! Wow! SR
*/
    case WM_ERASEBKGND:
      g_blnDoRedraw = 1;
      return 0;
    case WM_ACTIVATE:
      if( wParam == WA_ACTIVE || wParam == WA_CLICKACTIVE ) g_blnDoRedraw = 1;
      return 0;     
    // Keyboard events
    case WM_KEYDOWN:
      switch ( wParam ) {
        
        case VK_ESCAPE:
          PostQuitMessage(0);
          break;
          return 0;
        case VK_TAB:
          if( !g_blnFullScreen ) {
            x_SetFullScreenMode();
          }
          else {
            x_SetWindowedMode();
          }
          return 0;
        case VK_SPACE:
          g_blnDoRedraw = 1;  // redraw on space press
          return 0;
      } // switch ( wParam )

    // Mouse events
    case WM_LBUTTONDOWN:
      g_tMouseXY = MAKEPOINTS(lParam); 
      g_aiMouseEvents[MOUSE_LEFT][MOUSE_DOWN] = 1;
      break;
    case WM_MBUTTONDOWN:
      g_tMouseXY = MAKEPOINTS(lParam); 
      g_aiMouseEvents[MOUSE_MIDDLE][MOUSE_DOWN] = 1;
      break;
    case WM_RBUTTONDOWN:
      g_tMouseXY = MAKEPOINTS(lParam); 
      g_aiMouseEvents[MOUSE_RIGHT][MOUSE_DOWN] = 1;
      break;

    case WM_LBUTTONUP:
      g_tMouseXY = MAKEPOINTS(lParam); 
      g_aiMouseEvents[MOUSE_LEFT][MOUSE_UP] = 1;
      break;
    case WM_MBUTTONUP:
      g_tMouseXY = MAKEPOINTS(lParam); 
      g_aiMouseEvents[MOUSE_MIDDLE][MOUSE_UP] = 1;
      break;
    case WM_RBUTTONUP:
      g_tMouseXY = MAKEPOINTS(lParam); 
      g_aiMouseEvents[MOUSE_RIGHT][MOUSE_UP] = 1;
      break;
    case WM_LBUTTONDBLCLK:
      g_tMouseXY = MAKEPOINTS(lParam); 
      g_aiMouseEvents[MOUSE_LEFT][MOUSE_DBLCLICK] = 1;
      break;
    case WM_MBUTTONDBLCLK:
      g_tMouseXY = MAKEPOINTS(lParam); 
      g_aiMouseEvents[MOUSE_MIDDLE][MOUSE_DBLCLICK] = 1;
      break;
    case WM_RBUTTONDBLCLK:
      g_tMouseXY = MAKEPOINTS(lParam); 
      g_aiMouseEvents[MOUSE_RIGHT][MOUSE_DBLCLICK] = 1;
      break;
    case WM_MOUSEMOVE:
      g_tMouseXY = MAKEPOINTS(lParam); 
      break;  
      
  }  // switch (message)

  // process unhandled messages
  // COM is not processed in DefWindowProc(), it is processed in DispatchMessage()
  return DefWindowProc( hWnd, uiMsg, wParam, lParam );
  
}

