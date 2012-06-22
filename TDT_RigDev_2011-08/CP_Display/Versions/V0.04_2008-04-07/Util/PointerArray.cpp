#include "PointerArray.h"

// Limitation: there is no dynamic allocation of the storage. 
// When a truly dynamic storage is required, 
// use realloc of m_apvStorage on pointer add/delete

//------------------------------------------------
CPointerArray::CPointerArray() {
  m_nPointers = 0;
}

//------------------------------------------------
CPointerArray::~CPointerArray() {

}

//------------------------------------------------
int CPointerArray::GetN_Pointers(){
  return m_nPointers;
}

//------------------------------------------------
int CPointerArray::GetN_PointersMax(){
  return N_POINTERS_MAX;
}

//------------------------------------------------
int CPointerArray::AddPointer( void * pVoid ) {

  if( m_nPointers >= N_POINTERS_MAX ) return 1;

  m_apvStorage[m_nPointers] = pVoid;
  m_nPointers++;
  return 0;
}

//------------------------------------------------
int CPointerArray::RemovePointer ( void * pVoid ) {
  int iPtr;

  for(iPtr=0; iPtr < m_nPointers; iPtr++){
    if( m_apvStorage[iPtr] == pVoid) {
      // found the match, 
      // replace this pointer with the last one in the array
      if(m_nPointers>1) { 
        m_apvStorage[iPtr] = m_apvStorage[m_nPointers-1];
      }
      m_nPointers--;
      return 0;
    } // if found
  }  // for all pointers
  return 1;  // not found
}

//------------------------------------------------
int CPointerArray::GetPointer( int iPtr, void ** pVoid ){
  if( iPtr < 0 || iPtr >= m_nPointers ) {
    * pVoid = 0;
    return 1;
  }

  * pVoid = m_apvStorage[iPtr];
  return 0;
}

//------------------------------------------------
void CPointerArray::RemoveAllPointers() {
  m_nPointers = 0;
}
