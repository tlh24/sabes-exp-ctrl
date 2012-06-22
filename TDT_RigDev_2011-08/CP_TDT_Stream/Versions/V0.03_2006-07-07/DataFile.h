#ifndef CP_DataFile_H
#define CP_DataFile_H

#include <windows.h>
#include "CP_TDT_Err.h"
#include "CP_Printf.h"


class TDataFile {
  private:
    HANDLE m_hFile;
    CRITICAL_SECTION m_CriticalSection;
    bool m_blnWriteToFile;
    char m_szFilePath[_MAX_PATH];
    int m_nBytesWritten;  // byte counter
  protected:
    int m_WriteBlockToFile ( const void * pvBlock,
                             int iBlockLenBytes );
    TDataFile();
    ~TDataFile();
    /**
    Opens the file and starts writing.
    Returns EN_FILE_OPEN_ERR on error.
    */
    int StartWritingFile(const char * szFileName);
    /** Stops writing and closes the file */
    int StopWritingFile();

  public:

    /** Returns true if writing */
    bool IsWritingFile();
    /** Puts the filename into the buffer */
    int GetFileName( char * pszFileName,   /// Buffer to receive the filename
                     int iMaxSize ); /// Number of chars in the buffer, including the final \0
    /**
    If writing is in progress returns current number of bytes written,
    otherwise returns number of bytes written to the last file.
    */
    int GetFileByteCounter();

};

#endif //#ifndef CP_DataFile_H



