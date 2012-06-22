


/* ------------------------------------------------------------------------ --
--                                                                          --
--                        PC serial port connection object                  --
--                           for non-event-driven programs                  --
--                                                                          --
--                                                                          --
--                                                                          --
--  Copyright @ 2001          Thierry Schneider                             --
--                            thierry@tetraedre.com                         --
--                                                                          --
--                                                                          --
--                                                                          --
-- ------------------------------------------------------------------------ --
--                                                                          --
--  Filename : tserial.cpp                                                  --
--  Author   : Thierry Schneider                                            --
--  Created  : April 4th 2000                                               --
--  Modified : April 8th 2001                                               --
--  Plateform: Windows 95, 98, NT, 2000 (Win32)                             --
-- ------------------------------------------------------------------------ --
--                                                                          --
--  This software is given without any warranty. It can be distributed      --
--  free of charge as long as this header remains, unchanged.               --
--                                                                          --
-- modified by Sergei Rebrik
-- ------------------------------------------------------------------------ */



/* ---------------------------------------------------------------------- */
#define STRICT
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <process.h>
#include <conio.h>
#include <windows.h>

#include "Tserial.h"

#define PER_CHAR_TIMEOUT_MS 10   // per-char timeout used in read
#define INTER_CHAR_TIMEOUT_MS 100   // between-char timeout used in read


/* -------------------------------------------------------------------- */
/* -------------------------    Tserial   ----------------------------- */
/* -------------------------------------------------------------------- */
Tserial::Tserial()
{
    parityMode       = spNONE;
    port[0]          = 0;
    rate             = 0;
    serial_handle    = INVALID_HANDLE_VALUE;
}

/* -------------------------------------------------------------------- */
/* --------------------------    ~Tserial     ------------------------- */
/* -------------------------------------------------------------------- */
Tserial::~Tserial()
{
    if (serial_handle!=INVALID_HANDLE_VALUE)
        CloseHandle(serial_handle);
    serial_handle = INVALID_HANDLE_VALUE;
}
/* -------------------------------------------------------------------- */
/* --------------------------    disconnect   ------------------------- */
/* -------------------------------------------------------------------- */
void Tserial::disconnect(void)
{
    if (serial_handle!=INVALID_HANDLE_VALUE)
        CloseHandle(serial_handle);
    serial_handle = INVALID_HANDLE_VALUE;
}
/* -------------------------------------------------------------------- */
/* --------------------------    connect      ------------------------- */
/* -------------------------------------------------------------------- */

int  Tserial::connect(char *port_arg, int rate_arg, serial_parity parity_arg) {
  int erreur;
  DCB  dcb;
  COMMTIMEOUTS cto;
  BOOL bSuccess;

  // Close port if it was open
  if (serial_handle!=INVALID_HANDLE_VALUE)  CloseHandle(serial_handle);
  serial_handle = INVALID_HANDLE_VALUE;

  erreur = 0;

  if (port_arg==NULL){
    erreur = 1;
    goto errExit;
  }

  strncpy(port, port_arg, 10);
  rate      = rate_arg;
  parityMode= parity_arg;

  serial_handle = CreateFile(
            port,
            GENERIC_READ | GENERIC_WRITE,
            0,    // comm devices must be opened w/exclusive-access 
            NULL, // no security attrs 
            OPEN_EXISTING, // comm devices must use OPEN_EXISTING 
            NULL,    // not overlapped I/O 
            NULL  // hTemplate must be NULL for comm devices
  );

  if (serial_handle == INVALID_HANDLE_VALUE) {
    erreur = 2;
    goto errExit;
  }

  // Get the current configuration.
  bSuccess = GetCommState(serial_handle, &dcb);
  if (!bSuccess) {
    erreur = 3;
    goto errExit;
  }

  dcb.BaudRate        = rate;

  switch(parityMode)  {
    case spNONE:
      dcb.Parity      = NOPARITY;
      break;
    case spEVEN:
      dcb.Parity      = EVENPARITY;
      break;
    case spODD:
      dcb.Parity      = ODDPARITY;
      break;
  }
  dcb.StopBits = ONESTOPBIT;

  bSuccess = SetCommState(serial_handle, &dcb);
  if (!bSuccess) {
    erreur = 4;
    goto errExit;
  }

  bSuccess=GetCommTimeouts( serial_handle, &cto );
  if (!bSuccess) {
    erreur = 5;
    goto errExit;
  }


  // set timeouts on read, wrtie = no timeouts
  // max inter-char interval in ms, 0==unused
  cto.ReadIntervalTimeout = INTER_CHAR_TIMEOUT_MS;
  // max per-char delay (ms) in array reads
  cto.ReadTotalTimeoutMultiplier = PER_CHAR_TIMEOUT_MS;
  cto.ReadTotalTimeoutConstant = 0;     // extra per read in ms
  cto.WriteTotalTimeoutMultiplier = 0;  
  cto.WriteTotalTimeoutConstant = 0;
   
  bSuccess=SetCommTimeouts( serial_handle, &cto );
  if (!bSuccess) {
    erreur = 6;
    goto errExit;
  }

  bSuccess = PurgeComm( serial_handle, PURGE_RXCLEAR);
  if (!bSuccess) {
    erreur = 7;
    goto errExit;
  }

  return 0;

errExit:
  if (serial_handle != INVALID_HANDLE_VALUE) {
    CloseHandle(serial_handle);
    serial_handle = INVALID_HANDLE_VALUE;
  }
  return(erreur);
}
   

/* -------------------------------------------------------------------- */
/* --------------------------    sendChar     ------------------------- */
/* -------------------------------------------------------------------- */
void Tserial::sendChar(char data)
{
    sendArray(&data, 1);
}

/* -------------------------------------------------------------------- */
/* --------------------------    sendArray    ------------------------- */
/* -------------------------------------------------------------------- */
void Tserial::sendArray(char *buffer, int len)
{
    unsigned long result;

    if (serial_handle!=INVALID_HANDLE_VALUE)
        WriteFile(serial_handle, buffer, len, &result, NULL);
}

/* -------------------------------------------------------------------- */
/* --------------------------    getChar      ------------------------- */
/* -------------------------------------------------------------------- */
char Tserial::getChar(void)
{
    char c;
    getArray(&c, 1);
    return(c);
}

/* -------------------------------------------------------------------- */
/* --------------------------    getArray     ------------------------- */
/* -------------------------------------------------------------------- */
int  Tserial::getArray         (char *buffer, int len)
{
    unsigned long read_nbr;
    BOOL bSuccess;

    read_nbr = 0;
    if (serial_handle!=INVALID_HANDLE_VALUE){
       bSuccess = ReadFile(serial_handle, buffer, len, &read_nbr, NULL);
    }
    if (!bSuccess) {
      return -1;
    }


    return((int) read_nbr);
}
/* -------------------------------------------------------------------- */
/* --------------------------    getNbrOfBytes ------------------------ */
/* -------------------------------------------------------------------- */
int Tserial::getNbrOfBytes    (void)
{
    struct _COMSTAT status;
    int             n;
    unsigned long   etat;

    n = 0;

    if (serial_handle!=INVALID_HANDLE_VALUE)
    {
        ClearCommError(serial_handle, &etat, &status);
        n = status.cbInQue;
    }


    return(n);
}



