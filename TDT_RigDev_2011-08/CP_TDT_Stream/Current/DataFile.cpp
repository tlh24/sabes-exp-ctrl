#include "DataFile.h"


int TDataFile::m_WriteBlockToFile ( const void * pvBlock,
                                       int iBlockLenBytes ){
  unsigned long ulBytesWritten;
  EnterCriticalSection( &m_CriticalSection );
  int blnSuccess =
    WriteFile( m_hFile,	// handle to file to write to
               pvBlock,	// pointer to data to write to file
               iBlockLenBytes,	// number of bytes to write
               &ulBytesWritten,	// pointer to number of bytes written
               NULL );	// pointer to structure needed for overlapped I/O
  if(!blnSuccess ) {
    CP_printf("Error writing to the file!");
    LeaveCriticalSection( &m_CriticalSection );
    return FILE_WRITE_ERR;
  }

  if( iBlockLenBytes != (int)ulBytesWritten) {
    CP_printf("Error writing to the file! Block size: %d  bytes written: %d\n",
               iBlockLenBytes, ulBytesWritten);
    LeaveCriticalSection( &m_CriticalSection );
    return FILE_WRITE_ERR;
  }
  m_nBytesWritten += iBlockLenBytes;
  LeaveCriticalSection( &m_CriticalSection );
  return 0;
}
//---------------------------------------------------------------------------
TDataFile::TDataFile() {
  m_hFile = NULL;
  m_blnWriteToFile = false;
  m_nBytesWritten = 0;
  strcpy(m_szFilePath, "C:\\Delme.now");
  InitializeCriticalSection(&m_CriticalSection);

}
//---------------------------------------------------------------------------
TDataFile::~TDataFile() {
  DeleteCriticalSection( &m_CriticalSection );
}
//---------------------------------------------------------------------------
int TDataFile::StartWritingFile( const char * szFileName ){
  // check the flags first
  EnterCriticalSection( &m_CriticalSection );
  if (m_blnWriteToFile){
    LeaveCriticalSection( &m_CriticalSection );
    CP_printf("Error: the server is already writing to a file!\n");
    return FILE_OPEN_ERR;
  }

  strcpy( m_szFilePath, szFileName);

  m_hFile=CreateFile(
    m_szFilePath,	// pointer to name of the file
    GENERIC_WRITE,	// write-only mode
    0,	// 0=not-shared mode
    NULL,	// NULL=default security attributes
    CREATE_ALWAYS,	// overwrite if exists
    FILE_FLAG_WRITE_THROUGH,   // don't use cache
    NULL 	// handle to file with attributes to copy
  );

  LeaveCriticalSection( &m_CriticalSection );
  if( m_hFile==INVALID_HANDLE_VALUE) {
    CP_printf(">Error: cannot open file: %s\n", m_szFilePath);
    return FILE_OPEN_ERR;
  }
  m_blnWriteToFile = true;
  m_nBytesWritten=0;
  CP_printf("Opened file for writing: %s\n", m_szFilePath);
  return 0;
}
//---------------------------------------------------------------------------
int TDataFile::StopWritingFile(){
  EnterCriticalSection( &m_CriticalSection );
  if ( ! m_blnWriteToFile ) {
    LeaveCriticalSection( &m_CriticalSection );
    CP_printf("Error: the server is not writing to file!\n");
    return NO_OPEN_FILE_ERR;
  }
  CloseHandle(m_hFile);
  m_hFile=NULL;
  m_blnWriteToFile = false;
  LeaveCriticalSection( &m_CriticalSection );
  CP_printf("Closed file. % d bytes written.\n", m_nBytesWritten);
  return 0;
}
//---------------------------------------------------------------------------
bool TDataFile::IsWritingFile( ){
  return m_blnWriteToFile;
}
//---------------------------------------------------------------------------
int TDataFile::GetFileName( char * pszFileName, int iMaxSize){

  strncpy( pszFileName, m_szFilePath, iMaxSize);
  return 0;
}
//---------------------------------------------------------------------------
int TDataFile::GetFileByteCounter( ){
  return m_nBytesWritten;
}

