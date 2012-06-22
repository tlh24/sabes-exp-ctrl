// This buffer is like a sliding window that follows the write pointer.
// The size of the buffer deterimines how far you can go back in history 
// relative to the current write point.
// The buffer pointer has a limit of MAX_INT total bytes ~2GB since 
// the write offset is stored as an absolute position.
// bool functions return true on success

#include <stdlib.h> 
#include <malloc.h>
#include <memory.h>

#include "SlideBuf2.h"

//----------------------------------------------------------------
CSlideBuf2::CSlideBuf2(){
  m_nChannels = 1;
  m_nItemBytes = 1;
  m_nBufBytes = 0;
  m_iWritePos = 0;
  m_lpBuf = NULL;
  InitializeCriticalSection( &m_CriticalSection );

}

//----------------------------------------------------------------
CSlideBuf2::~CSlideBuf2(){
  RemoveBuffer();
  DeleteCriticalSection( &m_CriticalSection );
}

//----------------------------------------------------------------
bool CSlideBuf2::SetBuffer(int iItemSize, int nItems, int nChannels ){

  if(m_lpBuf) return false;

  m_iWritePos = 0;
  m_nItemBytes = iItemSize;
  m_nChannels = nChannels; 
  m_nBufBytes = iItemSize * nItems * nChannels;

  m_lpBuf = malloc(m_nBufBytes);
  if(!m_lpBuf) return false;
  return true;
}

//----------------------------------------------------------------
void CSlideBuf2::ResetBuffer(){
  m_iWritePos = 0;
}

//----------------------------------------------------------------
void CSlideBuf2::RemoveBuffer(){
  if(m_lpBuf) {
    free(m_lpBuf);

    m_nItemBytes = 1;
    m_lpBuf = NULL;
    m_nBufBytes = 0;
    m_iWritePos = 0;
  }
}

//----------------------------------------------------------------
bool CSlideBuf2::GetLatestItemIdx( int * piIdx ){
  int iWritePos;
  iWritePos = m_iWritePos; // thread-safe
  * piIdx = -1;
  if(!m_lpBuf || !iWritePos) return false;
  * piIdx = (iWritePos / m_nItemBytes) -1;
  return  true;
}

//----------------------------------------------------------------
int CSlideBuf2::GetBufferSizeInItems(){
  if(!m_lpBuf) return 0;
  return m_nBufBytes/m_nItemBytes;
}

//----------------------------------------------------------------
bool CSlideBuf2::WriteData(void *lpWriteBuf, int nItems){
  int nBytes = m_nItemBytes * nItems;
  return(m_Write(lpWriteBuf, nBytes));
}

//----------------------------------------------------------------
bool CSlideBuf2::ReadData(void *lpReadBuf, int iStartItemIdx, int nItems ){
    
  return m_Read(lpReadBuf,  iStartItemIdx * m_nItemBytes, nItems * m_nItemBytes );
}

//----------------------------------------------------------------
bool CSlideBuf2::ReadLatestItem(int * piIdx, void *lpReadBuf ){
  int iIdx;

  * piIdx = 0;
  if( !GetLatestItemIdx( &iIdx)) return false;
  * piIdx = iIdx;
  return m_Read(lpReadBuf,  iIdx * m_nItemBytes, m_nItemBytes );
}
//----------------------------------------------------------------
bool CSlideBuf2::m_Read(void *lpReadBuf, int iReadPos, int nBytes){
  int nBytesDelay;
  int iPhysReadPos;
  int i2BufEnd;
  
  EnterCriticalSection( &m_CriticalSection);

  nBytesDelay = m_iWritePos - iReadPos;
  if((!m_lpBuf) || (nBytes<=0) || (iReadPos<0) ||
      ( nBytesDelay > m_nBufBytes) ||  // data is lost already
      ( nBytesDelay < nBytes ) ) {  // don't have that many     

    LeaveCriticalSection( &m_CriticalSection );
    return false;
  }
  else {

    iPhysReadPos = iReadPos % m_nBufBytes;
    i2BufEnd = m_nBufBytes - iPhysReadPos;

    if( nBytes < i2BufEnd ) {
      // no wrap-around
      memcpy(lpReadBuf, (char*)m_lpBuf + iPhysReadPos, nBytes);
    }
    else  {
      // process wrap-around in two steps
      memcpy(lpReadBuf, (char*)m_lpBuf+ iPhysReadPos, i2BufEnd);
      memcpy((char*)lpReadBuf+i2BufEnd, m_lpBuf, nBytes-i2BufEnd);
    }
  }

  LeaveCriticalSection( &m_CriticalSection );
  return true;
}


//----------------------------------------------------------------
bool CSlideBuf2::m_Write(void *lpWriteBuf, int nBytes){
  bool blnRet;
  int iPhysWritePos;
  int i2BufEnd;
  
  EnterCriticalSection( &m_CriticalSection);
  if( (!m_lpBuf) || (!nBytes) || (nBytes<0) || (nBytes>m_nBufBytes)){
    blnRet = false; 
  }
  else {

    iPhysWritePos = m_iWritePos % m_nBufBytes;
    i2BufEnd = m_nBufBytes - iPhysWritePos;


    if( nBytes < i2BufEnd ) {
      // no wrap-around
      memcpy((char*)m_lpBuf + iPhysWritePos, lpWriteBuf, nBytes);
    }
    else {
      // process wrap-around in two steps
      memcpy((char*)m_lpBuf + iPhysWritePos, lpWriteBuf, i2BufEnd);
      memcpy(m_lpBuf, (char*)lpWriteBuf + i2BufEnd, nBytes-i2BufEnd);
    }
    m_iWritePos+=nBytes;
    blnRet = true;
  }

  LeaveCriticalSection( &m_CriticalSection );
  return blnRet;
}

