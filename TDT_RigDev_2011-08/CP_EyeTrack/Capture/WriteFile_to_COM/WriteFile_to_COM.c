#include <windows.h>
#include <conio.h>
#include <stdio.h>

#define FRAME_SIZE  6     // DD XX YY FF
#define BUF_SIZE  1000000   // ~ 1MB

char x_acFileBuf[BUF_SIZE];


int main(int argc, char *argv[]) {
  HANDLE hFile;
  int iFileSize;
  BOOL bSuccess;
  int iBytesRead;

  HANDLE hCom;
  DCB dcb;
  COMMTIMEOUTS comTimeOuts;

  DWORD dwBytesWritten;
  DWORD dwError;
  int iCharCount;

  if( argc!=3 ) {
    printf("Usage: %s <COM_NAME: COM1, COM2, ...> <filename> \n", argv[0]);
    exit(0);
  }


   hFile = CreateFile(argv[2],           // filename
               GENERIC_READ,                 // open for reading 
               0,                            // do not share 
               NULL,                         // no security 
               OPEN_EXISTING,                // only existing file
               FILE_ATTRIBUTE_NORMAL,        // normal file 
               NULL);                        // no attr. template 

  if (hFile == INVALID_HANDLE_VALUE) { 
    printf("Could not open file.\n"); 
    exit (1);
  }

  iFileSize = GetFileSize (hFile, NULL) ; 
  if ((iFileSize == -1) || ( iFileSize > BUF_SIZE))  { 
    printf("The file is too big. Max size: %d\n", BUF_SIZE); 
    exit (1); 
  }

  printf("Reading the file...   ");
  bSuccess = ReadFile(hFile, x_acFileBuf, iFileSize, &iBytesRead, NULL) ; 
  if ((! bSuccess ) || ( iBytesRead != iFileSize )) {
    printf("Error reading file: %s \n", argv[2]);
    exit(1);
  }
  CloseHandle(hFile);
  printf("OK\n"); 

  hCom = CreateFile(
    argv[1],
    GENERIC_READ | GENERIC_WRITE,
    0,    // comm devices must be opened w/exclusive-access 
    NULL, // no security attrs 
    OPEN_EXISTING, // comm devices must use OPEN_EXISTING 
    0,    // not overlapped I/O 
    NULL  // hTemplate must be NULL for comm devices
  );

  if (hCom == INVALID_HANDLE_VALUE) {
    dwError = GetLastError();
    printf("Error opening COM port, error#: %ld \n", dwError);
    exit(1);
  }

 
  // Get the current configuration.
  bSuccess = GetCommState(hCom, &dcb);
  if (!bSuccess) {
    printf("Error reading COM state! \n");
    exit(1);
  }

  // Fill in the DCB: baud=9600, 8 data bits, no parity, 1 stop bit.
  dcb.BaudRate = 57600;
  dcb.ByteSize = 8;
  dcb.Parity = NOPARITY;
 // dcb.Parity = ODDPARITY ;
  dcb.StopBits = ONESTOPBIT;

  bSuccess = SetCommState(hCom, &dcb);
  if (!bSuccess) {
    printf("Error setting COM state! \n");
    exit(1);
  }

  bSuccess=GetCommTimeouts( hCom, &comTimeOuts );
  if (!bSuccess) {
    printf("Error reading COM timeouts! \n");
    exit(1);
  }
   
  comTimeOuts.WriteTotalTimeoutMultiplier=10; //spend not more than 10ms per byte write
  comTimeOuts.WriteTotalTimeoutConstant=0; // addtional time per each read

  bSuccess=SetCommTimeouts( hCom, &comTimeOuts );
  if (!bSuccess) {
    printf("Error setting COM timeouts! \n");
    exit(1);
  }

  printf("\nWriting to %s... ( Press any key to exit )\n", argv[1]);

  iCharCount = 0;
  //  main loop
  while(TRUE) {
    bSuccess =  WriteFile( hCom, &x_acFileBuf[iCharCount], FRAME_SIZE, &dwBytesWritten, NULL);
  
    if ((! bSuccess ) || (dwBytesWritten != FRAME_SIZE )){
      printf("Error writing to COM! \n");
      exit(1);
    }
    iCharCount += FRAME_SIZE;
    if( (iCharCount + FRAME_SIZE) > iFileSize){
      iCharCount = 0;
      printf("\nRestarted the sequence\n");
    }
    printf("%d\r", iCharCount);
    Sleep(10);   // < 100 Hz frame rate
  
    if(_kbhit()) break;
  } // end while(TRUE)

  CloseHandle(hCom);
  printf("\n");
  return 0;

}


