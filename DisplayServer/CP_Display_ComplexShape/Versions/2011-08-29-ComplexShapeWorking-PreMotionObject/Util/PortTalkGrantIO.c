#include <windows.h>


//---------------------------------------------
// Grants access to a specified port
// iPort - port to access (should be a mutiple of 8). 
// Actually access is granted for the range of ports:
// from iPort to iPort+7
// Returns 0 on success, non-zero on error
// Uses PortTalk driver available from
// http://www.beyondlogic.org/

int g_SysGrantIO( int iPort ){

  HANDLE hPortTalkDriver = 0; // handle for PortTalk driver
  BOOL  blnRes;                           // return from DeviceIoControl()
  DWORD dwBytesReturned;
  DWORD dwProcessID;          // current process ID

  int iOffset;   // port address divided by 8 - actual driver parameter
  int iRet = 0;  // this function's return code. success by default

  if( (iPort%8)) {
//    shp_printf("Error: port address should be a multiple of 8!\n");
//    shp_printf("  Port: %04X\n", iPort);
    return 1;
  }

  // Open PortTalk Driver
  hPortTalkDriver = CreateFile("\\\\.\\PortTalk", 
                                GENERIC_READ, 
                                0, 
                                NULL,
                                OPEN_EXISTING, 
                                FILE_ATTRIBUTE_NORMAL, 
                                NULL);

  if(hPortTalkDriver == INVALID_HANDLE_VALUE) {
//    shp_printf("Error: couldn't open PortTalk Driver!\n");
//    shp_printf("Make sure the driver is loaded.\n");
    return 2;
  }
 
  
  iOffset = iPort / 8;

  // Set IO permissions bitmap
  blnRes = DeviceIoControl( hPortTalkDriver,
                            0x18,     // IOCTL 0x18 - Set IO Permission Bitmap
                            &iOffset, // send buffer 
                            sizeof(iOffset), // send buffer size - 4 bytes (int)
                            NULL,     // receive buffer (not used)
                            0,        // receive
                            &dwBytesReturned, // n bytes returned in the receive buffer
                            NULL  );  // pointer to async structure (not used)

  if (!blnRes) {
//    shp_printf("Error %d setting permission bitmap for address 0x%04X\n",GetLastError(),iPort);
    iRet= 3;
    goto exitGrant;
  }

//  shp_printf("Set permission bitmap for addresses 0x%04X : 0x%04X (IOPM Offset 0x%03X).\n",iPort, iPort+7,iOffset);

  dwProcessID = GetCurrentProcessId( );
  blnRes = DeviceIoControl( hPortTalkDriver,
                            0x04,         // IOCTL 0x04 - Set IOPM of ProcessID
                            &dwProcessID, // send buffer
                            sizeof(dwProcessID),  // send buffer size - 4 bytes (int)
                            NULL,     // receive buffer (not used)
                            0,        // receive buffer size
                            &dwBytesReturned, // n bytes returned in the receive buffer
                            NULL  );  // pointer to async structure (not used)

  if (!blnRes) {
//    shp_printf("Error %d setting IOPM for the process.\n",GetLastError());
    iRet= 4;
    goto exitGrant;
  }

//  shp_printf("Granted permission for ProcessID %d.\n",dwProcessID);
  
exitGrant:
  CloseHandle(hPortTalkDriver);
  return iRet;
  
}

