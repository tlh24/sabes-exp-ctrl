#include <windows.h>
#include <conio.h>
#include <stdio.h>


void main(int argc, char *argv[]) {
  DWORD dwBytesRead, dwBytesWritten;
  char  chInput;

  // char *szComPortName="COM2";

  DCB dcb;
  COMMTIMEOUTS comTimeOuts;
  HANDLE hCom;
  HANDLE hFile;
  DWORD dwError;
  BOOL bSuccess;

  if( argc!=3 ) {
    printf("Usage: %s <COM_NAME: COM1, COM2, ...> <filename> \n", argv[0]);
    exit(0);
  }

  hCom = CreateFile(
    argv[1],
    GENERIC_READ | GENERIC_WRITE,
    0,    /* comm devices must be opened w/exclusive-access */
    NULL, /* no security attrs */
    OPEN_EXISTING, /* comm devices must use OPEN_EXISTING */
    0,    /* not overlapped I/O */
    NULL  /* hTemplate must be NULL for comm devices */
  );

  if (hCom == INVALID_HANDLE_VALUE) {
    dwError = GetLastError();
    printf("Error opening COM port, error#: %ld \n", dwError);
    exit(0);
  }


   hFile = CreateFile(argv[2],           // filename
               GENERIC_WRITE,                // open for writing 
               0,                            // do not share 
               NULL,                         // no security 
               CREATE_ALWAYS,                // overwrite existing 
               FILE_ATTRIBUTE_NORMAL,        // normal file 
               NULL);                        // no attr. template 

  if (hFile == INVALID_HANDLE_VALUE) { 
    printf("Could not open file."); 
    exit (1);// process error 
  }

   /*
  * Omit the call to SetupComm to use the default queue sizes.
  * Get the current configuration.
  */

  bSuccess = GetCommState(hCom, &dcb);
  if (!bSuccess) {
    printf("Error reading COM state! \n");
    exit(0);
  }

  /* Fill in the DCB: baud=9600, 8 data bits, no parity, 1 stop bit. */
  dcb.BaudRate = 57600;
  dcb.ByteSize = 8;
  dcb.Parity = NOPARITY;
 // dcb.Parity = ODDPARITY ;
  dcb.StopBits = ONESTOPBIT;

  bSuccess = SetCommState(hCom, &dcb);

  if (!bSuccess) {
    printf("Error setting COM state! \n");
    exit(0);
  }

  bSuccess=GetCommTimeouts( hCom, &comTimeOuts );
  if (!bSuccess) {
    printf("Error reading COM timeouts! \n");
    exit(0);
  }
  // if the read interval time-out parameter is the MAXDWORD value 
  // and both read total time-out parameters are zero, 
  // a read operation is completed immediately after 
  // reading whatever characters are available in the input buffer, 
  // even if it is empty. 
   
  comTimeOuts.ReadIntervalTimeout=100; //wait for no more than 100 ms between byte receive
  comTimeOuts.ReadTotalTimeoutMultiplier=100; //spend not more than 100ms per byte read
  comTimeOuts.ReadTotalTimeoutConstant=0; // addtional time per each read

  bSuccess=SetCommTimeouts( hCom, &comTimeOuts );
  if (!bSuccess) {
    printf("Error setting COM timeouts! \n");
    exit(0);
  }

  printf("\nEntered terminal loop ( Type any char to exit )\n");
  /* enter main loop */
  while(TRUE) {
    // attempt a synchronous read operation 
    bSuccess = ReadFile(hCom, &chInput, 1, &dwBytesRead, NULL) ; 
    if (! bSuccess ) {
      printf("Error reading from COM! \n");
      exit(0);
    }
    if( dwBytesRead ) { 
      bSuccess =  WriteFile( hFile, &chInput, 1, &dwBytesWritten, NULL);
    
      if (! bSuccess ) {
        printf("Error writing to file! \n");
        exit(0);
      }
	  }
  
    if(_kbhit()) break;
  } /* end while */

  CloseHandle(hCom);
  CloseHandle(hFile);

} /* end main */


