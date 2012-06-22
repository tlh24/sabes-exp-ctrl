#ifndef SlideBuf_H
#define SlideBuf_H

#include <windows.h>

class CSlideBuf
{
public:
  CSlideBuf();
  ~CSlideBuf();

  bool SetBuffer(int iItemSize, int nItems);
  void RemoveBuffer();
  void ResetBuffer();

  int GetBufferSizeInItems();
  int GetItemSizeInBytes() { return m_nItemBytes; };
  bool GetLatestItemIdx( int * piIdx );
  bool ReadLatestItem(int * piIdx, void *lpReadBuf );
  bool ReadData(void *lpReadBuf, int iStartItemIdx, int nItems);

protected:
  bool WriteData(void* lpWriteBuf, int nItems);

private:
  int m_nItemBytes;
  int m_nBufBytes;
  int m_iWritePos;
  void* m_lpBuf;
  CRITICAL_SECTION m_CriticalSection; 

  bool m_Read(void* lpReadBuf, int iReadPos, int iBytes);
  bool m_Write(void* lpWriteBuf, int iBytes);

};


#endif // #ifndef SlideBuf_H
