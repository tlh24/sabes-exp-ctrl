#ifndef SlideBuf2_H
#define SlideBuf2_H

#include <windows.h>

class CSlideBuf2 {
public:
  CSlideBuf2();
  ~CSlideBuf2();

  bool SetBuffer(int iItemSize, int nItems);
  void RemoveBuffer();
  void ResetBuffer();

  int GetBufferSizeInItems();
  bool GetLatestItemIdx( int * piIdx );
  bool ReadLatestItem(int * piIdx, void *lpReadBuf );
  bool ReadData(void *lpReadBuf, int iStartItemIdx, int nItems);

protected:
  bool WriteData(void* lpWriteBuf, int nItems);

private:
  int m_nChannels;
  int m_nItemBytes;
  int m_nBufBytes;
  int m_iWritePos;
  void* m_lpBuf;
  CRITICAL_SECTION m_CriticalSection; 

  bool m_Read(void* lpReadBuf, int iReadPos, int iBytes);
  bool m_Write(void* lpWriteBuf, int iBytes);

};


#endif // #ifndef SlideBuf2_H
