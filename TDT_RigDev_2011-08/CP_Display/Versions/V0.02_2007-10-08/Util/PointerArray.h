#ifndef PointerArray_H
#define PointerArray_H

#define N_POINTERS_MAX 10000

class CPointerArray {

public:
  CPointerArray();
  ~CPointerArray();

  int GetN_Pointers();
  int GetN_PointersMax();
  int AddPointer( void * pVoid );
  int RemovePointer( void * pVoid );
  int GetPointer( int iPtr, void ** pVoid );
  void RemoveAllPointers();

private:
  int m_nPointers;
  void * m_apvStorage[N_POINTERS_MAX];

};


#endif // #ifndef PointerArray_H
