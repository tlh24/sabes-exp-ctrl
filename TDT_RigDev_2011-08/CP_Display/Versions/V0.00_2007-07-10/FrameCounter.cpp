#include <windows.h>
#include "FrameCounter.h"
#include "Util\PortTalkGrantIO.h"
#include "Util\CP_printf.h"


#define LPT_BASE 0x378   // LPT1

#define LPT_DATA      LPT_BASE
#define LPT_STATUS   (LPT_BASE + 1)
#define LPT_CONTROL  (LPT_BASE + 2)

#define ECP_AFIFO    (LPT_BASE + 0x400)
#define ECP_DFIFO    (LPT_BASE + 0x401)
#define ECP_ECTRL    (LPT_BASE + 0x402)

// bit 5 =1 : data port to input, bit 1 = 1 enable output on the board
#define CTL_BIDIR_OUT    0x20
#define CTRL_GATE_ON     0x01  
#define CTRL_OUT_ENABLE  0x02  
#define CTRL_RESET_OFF   0x04  

#define RESET_ON      (CTL_BIDIR_OUT | CTRL_OUT_ENABLE)
#define GATE_ON       (CTL_BIDIR_OUT | CTRL_OUT_ENABLE | CTRL_RESET_OFF | CTRL_GATE_ON)
#define GATE_OFF      (CTL_BIDIR_OUT | CTRL_OUT_ENABLE | CTRL_RESET_OFF)

#define LPT_CTL_DFLT      0xCC
#define ECP_ECTL_DFLT     0x15


int x_iPortIO_Granted = 0;
int x_iCounterStarted = 0;
int x_iCtlSave;
int x_iEcpSave;
int x_iPrevFrame = 0;

//------------------------------------------------------------------------------
int x_GetFrameCount(){
  int iFrame8bit, iFrame;

  iFrame8bit = PortInput(LPT_BASE);  // read from the port
  iFrame = (x_iPrevFrame & 0xFFFFFF00) + iFrame8bit;
  if( iFrame < x_iPrevFrame ) iFrame += 0x100;
  x_iPrevFrame = iFrame;
//  CP_printf("Port in = %d\n", iFrame8bit );
  return iFrame;
}

//==============================================================================
int g_InitFrameCounter(){
  int iValue;

  if( g_SysGrantIO( LPT_BASE ) ) return 1;
  if( g_SysGrantIO( ECP_AFIFO ) ) return 1;

  x_iCtlSave = PortInput(LPT_CONTROL);
  x_iEcpSave = PortInput(ECP_ECTRL);

  iValue = x_iEcpSave & 0x1F;  // keep lower 5 bits, clear upper 3
  iValue = iValue | 0x20;    // set mode 1 - bidirectional, PS2
  PortOutput( ECP_ECTRL, iValue);

  x_iPortIO_Granted = 1;
  x_iCounterStarted = 0;

  g_ResetFrameCounter();
  return 0;
}

//==============================================================================
int g_StartFrameCounter(){

  if( !x_iPortIO_Granted ) return 1;
  if( x_iCounterStarted ) return 2;
  g_ResetFrameCounter();
  Sleep(1);
  PortOutput( LPT_CONTROL, GATE_ON);
  x_iCounterStarted = 1;

  return 0;
}

//==============================================================================
int g_StopFrameCounter(){
  if( !x_iPortIO_Granted ) return 1;
  if( !x_iCounterStarted ) return 2;
  PortOutput( LPT_CONTROL, GATE_OFF);
  Sleep(20);  // enough to finish 60Hz frames
  CP_printf("Frame counter stopped. Total N frames = %d\n", x_GetFrameCount() );
  x_iCounterStarted = 0;
  return 0;
}


//==============================================================================
int g_GetFrameCounter( int * piFrame ){
  * piFrame = 0;
  if( !x_iPortIO_Granted ) return 1;
  if( !x_iCounterStarted ) return 2;
  * piFrame = x_GetFrameCount();
  return 0;
}

//==============================================================================
int g_ResetFrameCounter(){
  if( !x_iPortIO_Granted ) return 1;
  PortOutput( LPT_CONTROL, RESET_ON);
  Sleep(1);
  PortOutput( LPT_CONTROL, GATE_OFF);
  x_iCounterStarted = 0;
  x_iPrevFrame = 0;
  return 0;
}

//==============================================================================
int g_UpdateFrameCounter(){
  if( !x_iPortIO_Granted ) return 1;
  if( !x_iCounterStarted ) return 2;
  x_GetFrameCount();
  return 0;
}

//==============================================================================
int g_CloseFrameCounter(){
  if( !x_iPortIO_Granted ) return 1;
  // restore the state
  x_iPortIO_Granted = 0;
  // It is safer to output fixed (not saved) values in case the program
  // did not exit normally on the previous run
  PortOutput( LPT_CONTROL, LPT_CTL_DFLT);
  PortOutput( ECP_ECTRL, ECP_ECTL_DFLT);
//  PortOutput( LPT_CONTROL, x_iCtlSave);
//  PortOutput( ECP_ECTRL, x_iEcpSave);

  x_iCounterStarted = 0;
  return 0;
}
  
