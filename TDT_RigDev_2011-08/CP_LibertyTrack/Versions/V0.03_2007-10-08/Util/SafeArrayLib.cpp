// SafeArrayLib.cpp
#include <windows.h>

#include "CP_printf.h"
#include "SafeArrayLib.h"

//==============================================================================
// Make standard DCOM error code
HRESULT g_ErrorToHresult( int iErr ){
   return MAKE_HRESULT( SEVERITY_ERROR,  //  Indicate that function failed
                        FACILITY_ITF,    //  Specific interface - related error 
                        iErr ); // Our own error code
}

//==============================================================================
// 1D array of ints
int g_MakeSafeArray( int nDim1, SAFEARRAY ** ppsaMtx, int ** ppiMtx ) {
  SAFEARRAY *psaMtx = NULL;
  SAFEARRAYBOUND rgsabound[1];  // 1D array
  int * piMtx;

  * ppsaMtx = NULL;
  * ppiMtx = NULL;

  rgsabound[0].lLbound = 0;
  rgsabound[0].cElements = nDim1;    

  psaMtx = SafeArrayCreate(VT_I4, 1, rgsabound); // array of floats
  if(!psaMtx) {
    return 1;
  }
  SafeArrayAccessData(psaMtx, (void **) &piMtx );  // Get data pointer
  

  * ppsaMtx = psaMtx;
  * ppiMtx = piMtx;
  return 0;
}

//==============================================================================
// 2D array of ints
int g_MakeSafeArray( int nDim1, int nDim2, SAFEARRAY ** ppsaMtx, int ** ppiMtx ) {
  SAFEARRAY *psaMtx = NULL;
  SAFEARRAYBOUND rgsabound[2];  // 2-D array
  int * piMtx;

  * ppsaMtx = NULL;
  * ppiMtx = NULL;

  rgsabound[0].lLbound = 0;
  rgsabound[0].cElements = nDim1;    
  rgsabound[1].lLbound = 0;
  rgsabound[1].cElements = nDim2;    
  psaMtx = SafeArrayCreate(VT_I4, 2, rgsabound); // array of ints
  if(!psaMtx) {
    return 1;
  }
  SafeArrayAccessData(psaMtx, (void **) &piMtx );  // Get data pointer
  

  * ppsaMtx = psaMtx;
  * ppiMtx = piMtx;
  return 0;
}

//==============================================================================
// 1D array of floats
int g_MakeSafeArray( int nDim1, SAFEARRAY ** ppsaMtx, float ** ppfMtx ) {
  SAFEARRAY *psaMtx = NULL;
  SAFEARRAYBOUND rgsabound[1];  // 1D array
  float * pfMtx;

  * ppsaMtx = NULL;
  * ppfMtx = NULL;

  rgsabound[0].lLbound = 0;
  rgsabound[0].cElements = nDim1;    

  psaMtx = SafeArrayCreate(VT_R4, 1, rgsabound); // array of floats
  if(!psaMtx) {
    return 1;
  }
  SafeArrayAccessData(psaMtx, (void **) &pfMtx );  // Get data pointer
  

  * ppsaMtx = psaMtx;
  * ppfMtx = pfMtx;
  return 0;
}

//==============================================================================
// 2D array of floats
int g_MakeSafeArray( int nDim1, int nDim2, SAFEARRAY ** ppsaMtx, float ** ppfMtx ) {
  SAFEARRAY *psaMtx = NULL;
  SAFEARRAYBOUND rgsabound[2];  // 2-D array
  float * pfMtx;

  * ppsaMtx = NULL;
  * ppfMtx = NULL;

  rgsabound[0].lLbound = 0;
  rgsabound[0].cElements = nDim1;    
  rgsabound[1].lLbound = 0;
  rgsabound[1].cElements = nDim2;    
  psaMtx = SafeArrayCreate(VT_R4, 2, rgsabound); // array of floats
  if(!psaMtx) {
    return 1;
  }
  SafeArrayAccessData(psaMtx, (void **) &pfMtx );  // Get data pointer

  * ppsaMtx = psaMtx;
  * ppfMtx = pfMtx;
  return 0;
}

//==============================================================================
// 3D array of floats 
int g_MakeSafeArray( int nDim1, int nDim2, int nDim3, SAFEARRAY ** ppsaMtx, float ** ppfMtx ) {
  SAFEARRAY *psaMtx = NULL;
  SAFEARRAYBOUND rgsabound[3];  // 3-D array
  float * pfMtx;

  * ppsaMtx = NULL;
  * ppfMtx = NULL;

  rgsabound[0].lLbound = 0;
  rgsabound[0].cElements = nDim1;    
  rgsabound[1].lLbound = 0;
  rgsabound[1].cElements = nDim2;    
  rgsabound[2].lLbound = 0;
  rgsabound[2].cElements = nDim3;    
  psaMtx = SafeArrayCreate(VT_R4, 2, rgsabound); // array of floats
  if(!psaMtx) {
    return 1;
  }
  SafeArrayAccessData(psaMtx, (void **) &pfMtx );  // Get data pointer

  * ppsaMtx = psaMtx;
  * ppfMtx = pfMtx;
  return 0;
}

//==============================================================================
// 1D array of doubles
int g_MakeSafeArray( int nDim1, SAFEARRAY ** ppsaMtx, double ** ppdMtx ) {
  SAFEARRAY *psaMtx = NULL;
  SAFEARRAYBOUND rgsabound[1];  // 1-D array
  double * pdMtx;

  * ppsaMtx = NULL;
  * ppdMtx = NULL;

  rgsabound[0].lLbound = 0;
  rgsabound[0].cElements = nDim1;    
  psaMtx = SafeArrayCreate(VT_R8, 1, rgsabound); // array of doubles
  if(!psaMtx) {
    return 1;
  }
  SafeArrayAccessData(psaMtx, (void **) &pdMtx );  // Get data pointer
  

  * ppsaMtx = psaMtx;
  * ppdMtx = pdMtx;
  return 0;
}

//==============================================================================
// 2D array of doubles
int g_MakeSafeArray( int nDim1, int nDim2, SAFEARRAY ** ppsaMtx, double ** ppdMtx ) {
  SAFEARRAY *psaMtx = NULL;
  SAFEARRAYBOUND rgsabound[2];  // 2-D array
  double * pdMtx;

  * ppsaMtx = NULL;
  * ppdMtx = NULL;

  rgsabound[0].lLbound = 0;
  rgsabound[0].cElements = nDim1;    
  rgsabound[1].lLbound = 0;
  rgsabound[1].cElements = nDim2;    
  psaMtx = SafeArrayCreate(VT_R8, 2, rgsabound); // array of floats
  if(!psaMtx) {
    return 1;
  }
  SafeArrayAccessData(psaMtx, (void **) &pdMtx );  // Get data pointer

  * ppsaMtx = psaMtx;
  * ppdMtx = pdMtx;
  return 0;
}

//==============================================================================
// 3D array of doubles
int g_MakeSafeArray( int nDim1, int nDim2, int nDim3, SAFEARRAY ** ppsaMtx, double ** ppdMtx ) {
  SAFEARRAY *psaMtx = NULL;
  SAFEARRAYBOUND rgsabound[3];  // 3-D array
  double * pdMtx;

  * ppsaMtx = NULL;
  * ppdMtx = NULL;

  rgsabound[0].lLbound = 0;
  rgsabound[0].cElements = nDim1;    
  rgsabound[1].lLbound = 0;
  rgsabound[1].cElements = nDim2;    
  rgsabound[2].lLbound = 0;
  rgsabound[2].cElements = nDim3;
  
  psaMtx = SafeArrayCreate(VT_R8, 3, rgsabound); // array of doubles
  if(!psaMtx) {
    return 1;
  }
  SafeArrayAccessData(psaMtx, (void **) &pdMtx );  // Get data pointer

  * ppsaMtx = psaMtx;
  * ppdMtx = pdMtx;
  return 0;
}



//##############################################################################
//                            CHECKING SAFEARRAYS
//##############################################################################

//==============================================================================
// 1D array of ints, allow Nx1 or 1xN arrays
int g_CheckSafeArray( int nDim1, SAFEARRAY * psaMtx, int ** ppiMtx ){
  int nDims;
  long iDim1, iDim2;
  VARTYPE tSaType;

  *ppiMtx = NULL;

  SafeArrayGetVartype( psaMtx, &tSaType );
  if( tSaType != VT_I4 ){
    CP_printf("\ng_CheckSafeArray(): wrong array type, expecting array of ints!\n");
    return 1;
  }

  nDims = SafeArrayGetDim( psaMtx );
  if( nDims !=2 && nDims !=1 ) {    // Allow Nx1 or 1xN arrays
    CP_printf("\ng_CheckSafeArray(): wrong array dimensions, expecting %d - long array!\n", 
                                                            nDim1 );
    return 1;
  }
  SafeArrayGetLBound( psaMtx, 1, &iDim1 );
  if( iDim1 != 0) {
    CP_printf("\ng_CheckSafeArray(): wrong array dimensions, expecting %d - long array!\n", 
                                                            nDim1 );
    return 1;
  }
  SafeArrayGetUBound( psaMtx, 1, &iDim1 );

  if( nDims == 2 ) {
    SafeArrayGetLBound( psaMtx, 2, &iDim2 );
    if( iDim2 != 0) {
      CP_printf("\ng_CheckSafeArray(): wrong array dimensions, expecting %d - long array!\n", 
                                                            nDim1 );
      return 1;
    }
    SafeArrayGetUBound( psaMtx, 2, &iDim2 );
  }
  else 
    iDim2 = 0;

  // stupid hack allowing any 2D array with one redundant dim
  if( (iDim2 != 0) && (iDim1 != 0)) {
    CP_printf("\ng_CheckSafeArray(): wrong array dimensions, expecting %d - long array!\n", 
                                                            nDim1 );
    return 1;
  }

  if( nDim1 != (iDim1 + iDim2 + 1)) { // one of two is zero
    CP_printf("\ng_CheckSafeArray(): wrong array dimensions, expecting %d - long array!\n", 
                                                            nDim1 );
    return 1;
  }
  SafeArrayAccessData(psaMtx, (void **) ppiMtx);  // Get data pointer

  return 0;
}



//==============================================================================
// 1D array of ints, dim unspecified, allow Nx1 or 1xN arrays
int g_CheckSafeArray( int * pnDim1, SAFEARRAY * psaMtx, int ** ppiMtx ){
  int nDims;
  long iDim1, iDim2;
  VARTYPE tSaType;

  *pnDim1 = 0;
  *ppiMtx = NULL;

  SafeArrayGetVartype( psaMtx, &tSaType );
  if( tSaType != VT_I4 ){
    CP_printf("\ng_CheckSafeArray(): wrong array type, expecting array of ints!\n");
    return 1;
  }

  nDims = SafeArrayGetDim( psaMtx );
  if( nDims !=2 && nDims !=1 ) {    // Allow Nx1 or 1xN arrays
    CP_printf("\ng_CheckSafeArray(): wrong array dimensions, expecting 1xN, or Nx1 array!\n");
    return 1;
  }
  SafeArrayGetLBound( psaMtx, 1, &iDim1 );
  if( iDim1 != 0) {
    CP_printf("\ng_CheckSafeArray(): wrong array dimensions, expecting 1xN, or Nx1 array!\n");
    return 1;
  }
  SafeArrayGetUBound( psaMtx, 1, &iDim1 );

  if( nDims == 2 ) {
    SafeArrayGetLBound( psaMtx, 2, &iDim2 );
    if( iDim2 != 0) {
      CP_printf("\ng_CheckSafeArray(): wrong array dimensions, expecting 1xN, or Nx1 array!\n");
      return 1;
    }
    SafeArrayGetUBound( psaMtx, 2, &iDim2 );
  }
  else 
    iDim2 = 0;

  // stupid Matlab hack allowing any 2D array with one redundant dim
  if( (iDim2 != 0) && (iDim1 != 0)) {
    CP_printf("\ng_CheckSafeArray(): wrong array dimensions, expecting 1xN, or Nx1 array!\n");
    return 1;
  }

  *pnDim1 = iDim1 + iDim2 + 1;  // if we get here, one size is always zero
  SafeArrayAccessData(psaMtx, (void **) ppiMtx);  // Get data pointer

  return 0;
}

//==============================================================================
// 2D array of ints, second dim unspecified 
int g_CheckSafeArray( int nDim1, int * pnDim2, SAFEARRAY * psaMtx, int ** ppiMtx ){
  int nDims;
  long iDim;
  VARTYPE tSaType;

  *pnDim2 = 0;
  *ppiMtx = NULL;

  SafeArrayGetVartype( psaMtx, &tSaType );
  if( tSaType != VT_I4 ){
    CP_printf("\ng_CheckSafeArray(): wrong array type, expecting array of 4-byte integers!\n");
    return 1;
  }

  nDims = SafeArrayGetDim( psaMtx );
  if( nDims !=2 ) {
    CP_printf("\ng_CheckSafeArray(): wrong array dimensions, expecting %dxN array!\n", nDim1 );
    return 1;
  }
  SafeArrayGetLBound( psaMtx, 1, &iDim );
  if( iDim != 0) {
    CP_printf("\ng_CheckSafeArray(): wrong array dimensions, expecting %dxN array!\n", nDim1 );
    return 1;
  }
  SafeArrayGetUBound( psaMtx, 1, &iDim );
  if( iDim+1 != nDim1) {
    CP_printf("\ng_CheckSafeArray(): wrong array dimensions, expecting %dxN array!\n", nDim1 );
    return 1;
  }
  SafeArrayGetLBound( psaMtx, 2, &iDim );
  if( iDim != 0) {
    CP_printf("\ng_CheckSafeArray(): wrong array dimensions, expecting %dxN array!\n", nDim1 );
    return 1;
  }
  SafeArrayGetUBound( psaMtx, 2, &iDim );
  iDim++;   // we return the size, which is upperbound +1
  * pnDim2 = iDim; 
  SafeArrayAccessData(psaMtx, (void **) ppiMtx);  // Get data pointer

  return 0;
}


//==============================================================================
// 2D array of ints, both dims unspecified 
int g_CheckSafeArray( int * pnDim1, int * pnDim2, SAFEARRAY * psaMtx, int ** ppiMtx ){
  int nDims;
  long iDim;
  VARTYPE tSaType;

  *pnDim1 = 0;
  *pnDim2 = 0;
  *ppiMtx = NULL;

  SafeArrayGetVartype( psaMtx, &tSaType );
  if( tSaType != VT_I4 ){
    CP_printf("\ng_CheckSafeArray(): wrong array type, expecting array of 4-byte integers!\n");
    return 1;
  }

  nDims = SafeArrayGetDim( psaMtx );
  if( nDims !=2 ) {
    CP_printf("\ng_CheckSafeArray(): wrong array dimensions\n" );
    return 1;
  }
  SafeArrayGetLBound( psaMtx, 1, &iDim );
  if( iDim != 0) {
    CP_printf("\ng_CheckSafeArray(): wrong array dimensions!\n" );
    return 1;
  }
  SafeArrayGetLBound( psaMtx, 2, &iDim );
  if( iDim != 0) {
    CP_printf("\ng_CheckSafeArray(): wrong array dimensions\n" );
    return 1;
  }
  SafeArrayGetUBound( psaMtx, 1, &iDim );
  iDim++;   // we return the size, which is upperbound +1
  * pnDim1 = iDim; 
  SafeArrayGetUBound( psaMtx, 2, &iDim );
  iDim++;   // we return the size, which is upperbound +1
  * pnDim2 = iDim; 
  SafeArrayAccessData(psaMtx, (void **) ppiMtx);  // Get data pointer

  return 0;
}

//==============================================================================
// 1D array of floats 
int g_CheckSafeArray( int nDim1, SAFEARRAY * psaMtx, float ** ppfMtx ){
  int nDims;
  long iDim;
  VARTYPE tSaType;

  *ppfMtx = NULL;

  SafeArrayGetVartype( psaMtx, &tSaType );
  if( tSaType != VT_R4 ){
    CP_printf("\ng_CheckSafeArray(): wrong array type, expecting array of 4-byte floats!\n");
    return 1;
  }

  nDims = SafeArrayGetDim( psaMtx );
  if( nDims !=1 ) {
    CP_printf("\ng_CheckSafeArray(): wrong array dimensions, expecting %d - long array!\n", 
                                                            nDim1 );
    return 1;
  }
  SafeArrayGetLBound( psaMtx, 1, &iDim );
  if( iDim != 0) {
    CP_printf("\ng_CheckSafeArray(): wrong array dimensions, expecting %d - long array!\n", 
                                                            nDim1 );
    return 1;
  }
  SafeArrayGetUBound( psaMtx, 1, &iDim );
  if( iDim+1 != nDim1) {
    CP_printf("\ng_CheckSafeArray(): wrong array dimensions, expecting %d - long array!\n", 
                                                            nDim1 );
    return 1;
  }
  SafeArrayAccessData(psaMtx, (void **) ppfMtx);  // Get data pointer

  return 0;
}

//==============================================================================
// 2D array of floats 
int g_CheckSafeArray( int nDim1, int nDim2, SAFEARRAY * psaMtx, float ** ppfMtx ){
  int nDims;
  long iDim;
  VARTYPE tSaType;

  *ppfMtx = NULL;

  SafeArrayGetVartype( psaMtx, &tSaType );
  if( tSaType != VT_R4 ){
    CP_printf("\ng_CheckSafeArray(): wrong array type, expecting array of 4-byte floats!\n");
    return 1;
  }

  nDims = SafeArrayGetDim( psaMtx );
  if( nDims !=2 ) {
    CP_printf("\ng_CheckSafeArray(): wrong array dimensions, expecting %dx%d array!\n", 
                                                            nDim1, nDim2 );
    return 1;
  }
  SafeArrayGetLBound( psaMtx, 1, &iDim );
  if( iDim != 0) {
    CP_printf("\ng_CheckSafeArray(): wrong array dimensions, expecting %dx%d array!\n", 
                                                            nDim1, nDim2 );
    return 1;
  }
  SafeArrayGetUBound( psaMtx, 1, &iDim );
  if( iDim+1 != nDim1) {
    CP_printf("\ng_CheckSafeArray(): wrong array dimensions, expecting %dx%d array!\n",
                                                            nDim1, nDim2 );
    return 1;
  }
  SafeArrayGetLBound( psaMtx, 2, &iDim );
  if( iDim != 0) {
    CP_printf("\ng_CheckSafeArray(): wrong array dimensions, expecting %dx%d array!\n", 
                                                            nDim1, nDim2 );
    return 1;
  }
  SafeArrayGetUBound( psaMtx, 2, &iDim );
  if( iDim+1 != nDim2) {
    CP_printf("\ng_CheckSafeArray(): wrong array dimensions, expecting %dx%d array!\n",
                                                            nDim1, nDim2 );
    return 1;
  }
  SafeArrayAccessData(psaMtx, (void **) ppfMtx);  // Get data pointer

  return 0;
}


//==============================================================================
// 1D array of doubles, also allow Nx1 or 1xN arrays
int g_CheckSafeArray( int nDim1, SAFEARRAY * psaMtx, double ** ppdMtx ){
  int nDims;
  long iDim1, iDim2;
  VARTYPE tSaType;

  *ppdMtx = NULL;

  SafeArrayGetVartype( psaMtx, &tSaType );
  if( tSaType != VT_R8 ){
    CP_printf("\ng_CheckSafeArray(): wrong array type, expecting array of doubles!\n");
    return 1;
  }

  nDims = SafeArrayGetDim( psaMtx );
  if( nDims !=2 && nDims !=1 ) {    // Allow Nx1 or 1xN arrays
    CP_printf("\ng_CheckSafeArray(): wrong array dimensions, expecting %d, 1x%d, or %dx1 array!\n", 
                                                                    nDim1, nDim1, nDim1 );
    return 1;
  }
  SafeArrayGetLBound( psaMtx, 1, &iDim1 );
  if( iDim1 != 0) {
    CP_printf("\ng_CheckSafeArray(): wrong array dimensions, expecting %d, 1x%d, or %dx1 array!\n", 
                                                                    nDim1, nDim1, nDim1 );
    return 1;
  }
  SafeArrayGetUBound( psaMtx, 1, &iDim1 );

  if( nDims == 2 ) {
    SafeArrayGetLBound( psaMtx, 2, &iDim2 );
    if( iDim2 != 0) {
      CP_printf("\ng_CheckSafeArray(): wrong array dimensions, expecting %d, 1x%d, or %dx1 array!\n", 
                                                                      nDim1, nDim1, nDim1 );
      return 1;
    }
    SafeArrayGetUBound( psaMtx, 2, &iDim2 );
  }
  else 
    iDim2 = 0;

  if( (iDim2+1 != nDim1) && (iDim1+1 != nDim1)) {
    CP_printf("\ng_CheckSafeArray(): wrong array dimensions, expecting %d, 1x%d, or %dx1 array!\n", 
                                                                    nDim1, nDim1, nDim1 );
    return 1;
  }
  // stupid Matlab hacks allowing any 2D array with one redundant dim
  if( (iDim2 != 0) && (iDim1 != 0)) {
    CP_printf("\ng_CheckSafeArray(): wrong array dimensions, expecting %d, 1x%d, or %dx1 array!\n", 
                                                                    nDim1, nDim1, nDim1 );
    return 1;
  }
  SafeArrayAccessData(psaMtx, (void **) ppdMtx);  // Get data pointer

  return 0;
}


//==============================================================================
// 2D array of doubles 
int g_CheckSafeArray( int nDim1, int nDim2, SAFEARRAY * psaMtx, double ** ppdMtx ){
  int nDims;
  long iDim;
  VARTYPE tSaType;

  *ppdMtx = NULL;

  SafeArrayGetVartype( psaMtx, &tSaType );
  if( tSaType != VT_R8 ){
    CP_printf("\ng_CheckSafeArray(): wrong array type, expecting array of doubles!\n");
    return 1;
  }

  nDims = SafeArrayGetDim( psaMtx );
  if( nDims !=2 ) {
    CP_printf("\ng_CheckSafeArray(): wrong array dimensions, expecting %dx%d array!\n", 
                                                            nDim1, nDim2 );
    return 1;
  }
  SafeArrayGetLBound( psaMtx, 1, &iDim );
  if( iDim != 0) {
    CP_printf("\ng_CheckSafeArray(): wrong array dimensions, expecting %dx%d array!\n", 
                                                            nDim1, nDim2 );
    return 1;
  }
  SafeArrayGetUBound( psaMtx, 1, &iDim );
  if( iDim+1 != nDim1) {
    CP_printf("\ng_CheckSafeArray(): wrong array dimensions, expecting %dx%d array!\n",
                                                            nDim1, nDim2 );
    return 1;
  }
  SafeArrayGetLBound( psaMtx, 2, &iDim );
  if( iDim != 0) {
    CP_printf("\ng_CheckSafeArray(): wrong array dimensions, expecting %dx%d array!\n", 
                                                            nDim1, nDim2 );
    return 1;
  }
  SafeArrayGetUBound( psaMtx, 2, &iDim );
  if( iDim+1 != nDim2) {
    CP_printf("\ng_CheckSafeArray(): wrong array dimensions, expecting %dx%d array!\n",
                                                            nDim1, nDim2 );
    return 1;
  }
  SafeArrayAccessData(psaMtx, (void **) ppdMtx);  // Get data pointer

  return 0;
}

//==============================================================================
// 2D array of doubles, second dim unspecified 
int g_CheckSafeArray( int nDim1, int * pnDim2, SAFEARRAY * psaMtx, double ** ppdMtx ){
  int nDims;
  long iDim;
  VARTYPE tSaType;

  *pnDim2 = 0;
  *ppdMtx = NULL;

  SafeArrayGetVartype( psaMtx, &tSaType );
  if( tSaType != VT_R8 ){
    CP_printf("\ng_CheckSafeArray(): wrong array type, expecting array of doubles!\n");
    return 1;
  }

  nDims = SafeArrayGetDim( psaMtx );
  if( nDims !=2 ) {
    CP_printf("\ng_CheckSafeArray(): wrong number of dimensions, expecting 2D array!\n" );
    return 1;
  }
  SafeArrayGetLBound( psaMtx, 1, &iDim );
  if( iDim != 0) {
    CP_printf("\ng_CheckSafeArray(): wrong array dimensions, expecting %dxN array!\n", nDim1 );
    return 1;
  }
  SafeArrayGetUBound( psaMtx, 1, &iDim );
  if( iDim+1 != nDim1) {
    CP_printf("\ng_CheckSafeArray(): wrong array dimensions, expecting %dxN array!\n", nDim1 );
    return 1;
  }
  SafeArrayGetLBound( psaMtx, 2, &iDim );
  if( iDim != 0) {
    CP_printf("\ng_CheckSafeArray(): wrong array dimensions, expecting %dxN array!\n", nDim1 );
    return 1;
  }
  SafeArrayGetUBound( psaMtx, 2, &iDim );
  iDim++;   // we return the size, which is upperbound +1
  * pnDim2 = iDim; 
  SafeArrayAccessData(psaMtx, (void **) ppdMtx);  // Get data pointer

  return 0;
}

//==============================================================================
// 2D array of doubles, first dim unspecified 
int g_CheckSafeArray( int * pnDim1, int nDim2, SAFEARRAY * psaMtx, double ** ppdMtx ){
  int nDims;
  long iDim;
  VARTYPE tSaType;

  *pnDim1 = 0;
  *ppdMtx = NULL;

  SafeArrayGetVartype( psaMtx, &tSaType );
  if( tSaType != VT_R8 ){
    CP_printf("\ng_CheckSafeArray(): wrong array type, expecting array of doubles!\n");
    return 1;
  }

  nDims = SafeArrayGetDim( psaMtx );
  if( nDims !=2 ) {
    CP_printf("\ng_CheckSafeArray(): wrong number of dimensions, expecting 2D array!\n" );
    return 1;
  }
  SafeArrayGetLBound( psaMtx, 2, &iDim );
  if( iDim != 0) {
    CP_printf("\ng_CheckSafeArray(): wrong array dimensions, expecting N x %d array!\n", nDim2 );
    return 1;
  }
  SafeArrayGetUBound( psaMtx, 2, &iDim );
  if( iDim+1 != nDim2) {
    CP_printf("\ng_CheckSafeArray(): wrong array dimensions, expecting N x %d array!\n", nDim2 );
    return 1;
  }
  SafeArrayGetLBound( psaMtx, 1, &iDim );
  if( iDim != 0) {
    CP_printf("\ng_CheckSafeArray(): wrong array dimensions, expecting N x %d array!\n", nDim2 );
    return 1;
  }
  SafeArrayGetUBound( psaMtx, 1, &iDim );
  iDim++;   // we return the size, which is upperbound +1
  * pnDim1 = iDim; 
  SafeArrayAccessData(psaMtx, (void **) ppdMtx);  // Get data pointer

  return 0;
}

//==============================================================================
// 3D array of doubles, first and second dims unspecified 
int g_CheckSafeArray( int * pnDim1, int * pnDim2, int nDim3, SAFEARRAY * psaMtx, double ** ppdMtx ){
  int nDims;
  long iDim;
  VARTYPE tSaType;

  *pnDim1 = 0;
  *pnDim2 = 0;
  *ppdMtx = NULL;

  SafeArrayGetVartype( psaMtx, &tSaType );
  if( tSaType != VT_R8 ){
    CP_printf("\ng_CheckSafeArray(): wrong array type, expecting array of doubles!\n");
    return 1;
  }

  nDims = SafeArrayGetDim( psaMtx );
  if( nDims !=3 ) {
    CP_printf("\ng_CheckSafeArray(): wrong array dimensions, expecting 3D array!\n" );
    return 1;
  }
  SafeArrayGetLBound( psaMtx, 3, &iDim );
  if( iDim != 0) {
    CP_printf("\ng_CheckSafeArray(): wrong array dimensions, expecting N x N x %d array!\n", nDim3 );
    return 1;
  }
  SafeArrayGetUBound( psaMtx, 3, &iDim );
  if( iDim+1 != nDim3) {
    CP_printf("\ng_CheckSafeArray(): wrong array dimensions, expecting N x N x %d array!\n", nDim3 );
    return 1;
  }
  SafeArrayGetLBound( psaMtx, 1, &iDim );
  if( iDim != 0) {
    CP_printf("\ng_CheckSafeArray(): wrong array dimensions, expecting N x N x %d array!\n", nDim3 );
    return 1;
  }
  SafeArrayGetLBound( psaMtx, 2, &iDim );
  if( iDim != 0) {
    CP_printf("\ng_CheckSafeArray(): wrong array dimensions, expecting N x N x %d array!\n", nDim3 );
    return 1;
  }
  SafeArrayGetUBound( psaMtx, 1, &iDim );
  iDim++;   // we return the size, which is upperbound +1
  * pnDim1 = iDim; 
  SafeArrayGetUBound( psaMtx, 2, &iDim );
  iDim++;   // we return the size, which is upperbound +1
  * pnDim2 = iDim; 
  SafeArrayAccessData(psaMtx, (void **) ppdMtx);  // Get data pointer

  return 0;
}








