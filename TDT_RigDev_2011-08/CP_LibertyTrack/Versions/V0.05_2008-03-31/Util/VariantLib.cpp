// VariantLib.cpp
#include <windows.h>

#include "CP_printf.h"
#include "VariantLib.h"

//==============================================================================
// Make standard DCOM error code
HRESULT g_ErrorToHresult( int iErr ){
   return MAKE_HRESULT( SEVERITY_ERROR,  //  Indicate that function failed
                        FACILITY_ITF,    //  Specific interface - related error 
                        iErr ); // Our own error code
}

//==============================================================================
// 1D array of ints
int g_MakeVariantArray( int nDim1, VARIANT * pvMtx, int ** ppiMtx ) {
  SAFEARRAY * psaMtx = NULL;
  SAFEARRAYBOUND rgsabound[1];  // 1D array

  VariantInit(pvMtx);     

  rgsabound[0].lLbound = 0;
  rgsabound[0].cElements = nDim1;    

  psaMtx = SafeArrayCreate(VT_I4, 1, rgsabound); // array of floats
  if(!psaMtx) {
    return 1;
  }
  SafeArrayAccessData(psaMtx, (void **) ppiMtx );  // Get data pointer
  pvMtx->vt = VT_ARRAY|VT_I4;  
  pvMtx->parray = psaMtx;
  
  return 0;
}

//==============================================================================
// 2D array of ints
int g_MakeVariantArray( int nDim1, int nDim2, VARIANT * pvMtx, int ** ppiMtx ) {
  SAFEARRAY * psaMtx = NULL;
  SAFEARRAYBOUND rgsabound[2];  // 2-D array

  VariantInit(pvMtx);     

  rgsabound[0].lLbound = 0;
  rgsabound[0].cElements = nDim1;    
  rgsabound[1].lLbound = 0;
  rgsabound[1].cElements = nDim2;    
  psaMtx = SafeArrayCreate(VT_I4, 2, rgsabound); // array of ints
  if(!psaMtx) {
    return 1;
  }
  SafeArrayAccessData(psaMtx, (void **) ppiMtx );  // Get data pointer
  pvMtx->vt = VT_ARRAY|VT_I4;  
  pvMtx->parray = psaMtx;
  
  return 0;
}

//==============================================================================
// 1D array of doubles
int g_MakeVariantArray( int nDim1, VARIANT * pvMtx, double ** ppdMtx ) {
  SAFEARRAY * psaMtx = NULL;
  SAFEARRAYBOUND rgsabound[1];  // 1-D array

  VariantInit(pvMtx);     

  rgsabound[0].lLbound = 0;
  rgsabound[0].cElements = nDim1;    
  psaMtx = SafeArrayCreate(VT_R8, 1, rgsabound); // array of doubles
  if(!psaMtx) {
    return 1;
  }
  SafeArrayAccessData(psaMtx, (void **) ppdMtx );  // Get data pointer
  pvMtx->vt = VT_ARRAY|VT_R8;  
  pvMtx->parray = psaMtx;
  
  return 0;
}

//==============================================================================
// 2D array of doubles
int g_MakeVariantArray( int nDim1, int nDim2, VARIANT * pvMtx, double ** ppdMtx ) {
  SAFEARRAY * psaMtx = NULL;
  SAFEARRAYBOUND rgsabound[2];  // 2-D array

  VariantInit(pvMtx);     

  rgsabound[0].lLbound = 0;
  rgsabound[0].cElements = nDim1;    
  rgsabound[1].lLbound = 0;
  rgsabound[1].cElements = nDim2;    
  psaMtx = SafeArrayCreate(VT_R8, 2, rgsabound); // array of floats
  if(!psaMtx) {
    return 1;
  }
  SafeArrayAccessData(psaMtx, (void **) ppdMtx );  // Get data pointer
  pvMtx->vt = VT_ARRAY|VT_R8;  
  pvMtx->parray = psaMtx;
  
  return 0;
}



//##############################################################################
//                            CHECKING SAFEARRAYS
//##############################################################################


//==============================================================================
// 1D array of ints, dim unspecified, allow Nx1 or 1xN arrays
int g_CheckVariantArray( int * pnDim1, VARIANT vMtx, int ** ppiMtx ){
  SAFEARRAY * psaMtx;
  int nDims;
  long iDim1, iDim2;
  VARTYPE tSaType;

  psaMtx = vMtx.parray;
  *pnDim1 = 0;

  if( vMtx.vt != (VT_ARRAY|VT_I4)){
    CP_printf("\ng_CheckVariantArray(): wrong VARIANT type, expecting array of ints!\n");
    return 1;
  }

  SafeArrayGetVartype( psaMtx, &tSaType );
  if( tSaType != VT_I4 ){
    CP_printf("\ng_CheckVariantArray(): wrong array type, expecting array of ints!\n");
    return 1;
  }

  nDims = SafeArrayGetDim( psaMtx );
  if( nDims !=2 && nDims !=1 ) {    // Allow Nx1 or 1xN arrays
    CP_printf("\ng_CheckVariantArray(): wrong array dimensions, expecting 1xN, or Nx1 array!\n");
    return 1;
  }
  SafeArrayGetLBound( psaMtx, 1, &iDim1 );
  if( iDim1 != 0) {
    CP_printf("\ng_CheckVariantArray(): wrong array dimensions, expecting 1xN, or Nx1 array!\n");
    return 1;
  }
  SafeArrayGetUBound( psaMtx, 1, &iDim1 );

  if( nDims == 2 ) {
    SafeArrayGetLBound( psaMtx, 2, &iDim2 );
    if( iDim2 != 0) {
      CP_printf("\ng_CheckVariantArray(): wrong array dimensions, expecting 1xN, or Nx1 array!\n");
      return 1;
    }
    SafeArrayGetUBound( psaMtx, 2, &iDim2 );
  }
  else 
    iDim2 = 0;

  // stupid Matlab hack allowing any 2D array with one redundant dim
  if( (iDim2 != 0) && (iDim1 != 0)) {
    CP_printf("\ng_CheckVariantArray(): wrong array dimensions, expecting 1xN, or Nx1 array!\n");
    return 1;
  }

  *pnDim1 = iDim1 + iDim2 + 1;  // if we get here, one size is always zero
  SafeArrayAccessData(psaMtx, (void **) ppiMtx);  // Get data pointer

  return 0;
}

//==============================================================================
// 2D array of ints, both dims unspecified 
int g_CheckVariantArray( int * pnDim1, int * pnDim2, VARIANT vMtx, int ** ppiMtx ){
  SAFEARRAY * psaMtx;
  int nDims;
  long iDim;
  VARTYPE tSaType;

  psaMtx = vMtx.parray;
  *pnDim1 = 0;
  *pnDim2 = 0;

  if( vMtx.vt != (VT_ARRAY|VT_I4)){
    CP_printf("\ng_CheckVariantArray(): wrong VARIANT type, expecting array of ints!\n");
    return 1;
  }

  SafeArrayGetVartype( psaMtx, &tSaType );
  if( tSaType != VT_I4 ){
    CP_printf("\ng_CheckVariantArray(): wrong array type, expecting array of 4-byte integers!\n");
    return 1;
  }

  nDims = SafeArrayGetDim( psaMtx );
  if( nDims !=2 ) {
    CP_printf("\ng_CheckVariantArray(): wrong array dimensions\n" );
    return 1;
  }
  SafeArrayGetLBound( psaMtx, 1, &iDim );
  if( iDim != 0) {
    CP_printf("\ng_CheckVariantArray(): wrong array dimensions!\n" );
    return 1;
  }
  SafeArrayGetLBound( psaMtx, 2, &iDim );
  if( iDim != 0) {
    CP_printf("\ng_CheckVariantArray(): wrong array dimensions\n" );
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
// 2D array of doubles 
int g_CheckVariantArray( int nDim1, int nDim2, VARIANT vMtx, double ** ppdMtx ){
  SAFEARRAY * psaMtx;
  int nDims;
  long iDim;
  VARTYPE tSaType;

  psaMtx = vMtx.parray;

  if( vMtx.vt != (VT_ARRAY|VT_R8)){
    CP_printf("\ng_CheckVariantArray(): wrong VARIANT type, expecting array of doubles!\n");
    return 1;
  }

  SafeArrayGetVartype( psaMtx, &tSaType );
  if( tSaType != VT_R8 ){
    CP_printf("\ng_CheckVariantArray(): wrong array type, expecting array of doubles!\n");
    return 1;
  }

  nDims = SafeArrayGetDim( psaMtx );
  if( nDims !=2 ) {
    CP_printf("\ng_CheckVariantArray(): wrong array dimensions, expecting %dx%d array!\n", 
                                                            nDim1, nDim2 );
    return 1;
  }
  SafeArrayGetLBound( psaMtx, 1, &iDim );
  if( iDim != 0) {
    CP_printf("\ng_CheckVariantArray(): wrong array dimensions, expecting %dx%d array!\n", 
                                                            nDim1, nDim2 );
    return 1;
  }
  SafeArrayGetUBound( psaMtx, 1, &iDim );
  if( iDim+1 != nDim1) {
    CP_printf("\ng_CheckVariantArray(): wrong array dimensions, expecting %dx%d array!\n",
                                                            nDim1, nDim2 );
    return 1;
  }
  SafeArrayGetLBound( psaMtx, 2, &iDim );
  if( iDim != 0) {
    CP_printf("\ng_CheckVariantArray(): wrong array dimensions, expecting %dx%d array!\n", 
                                                            nDim1, nDim2 );
    return 1;
  }
  SafeArrayGetUBound( psaMtx, 2, &iDim );
  if( iDim+1 != nDim2) {
    CP_printf("\ng_CheckVariantArray(): wrong array dimensions, expecting %dx%d array!\n",
                                                            nDim1, nDim2 );
    return 1;
  }
  SafeArrayAccessData(psaMtx, (void **) ppdMtx);  // Get data pointer

  return 0;
}

//==============================================================================
// 2D array of doubles, second dim unspecified 
int g_CheckVariantArray( int nDim1, int * pnDim2, VARIANT vMtx, double ** ppdMtx ){
  SAFEARRAY * psaMtx;
  int nDims;
  long iDim;
  VARTYPE tSaType;

  psaMtx = vMtx.parray;
  *pnDim2 = 0;

  if( vMtx.vt != (VT_ARRAY|VT_R8)){
    CP_printf("\ng_CheckVariantArray(): wrong VARIANT type, expecting array of doubles!\n");
    return 1;
  }

  SafeArrayGetVartype( psaMtx, &tSaType );
  if( tSaType != VT_R8 ){
    CP_printf("\ng_CheckVariantArray(): wrong array type, expecting array of doubles!\n");
    return 1;
  }

  nDims = SafeArrayGetDim( psaMtx );
  if( nDims !=2 ) {
    CP_printf("\ng_CheckVariantArray(): wrong number of dimensions, expecting 2D array!\n" );
    return 1;
  }
  SafeArrayGetLBound( psaMtx, 1, &iDim );
  if( iDim != 0) {
    CP_printf("\ng_CheckVariantArray(): wrong array dimensions, expecting %dxN array!\n", nDim1 );
    return 1;
  }
  SafeArrayGetUBound( psaMtx, 1, &iDim );
  if( iDim+1 != nDim1) {
    CP_printf("\ng_CheckVariantArray(): wrong array dimensions, expecting %dxN array!\n", nDim1 );
    return 1;
  }
  SafeArrayGetLBound( psaMtx, 2, &iDim );
  if( iDim != 0) {
    CP_printf("\ng_CheckVariantArray(): wrong array dimensions, expecting %dxN array!\n", nDim1 );
    return 1;
  }
  SafeArrayGetUBound( psaMtx, 2, &iDim );
  iDim++;   // we return the size, which is upperbound +1
  * pnDim2 = iDim; 
  SafeArrayAccessData(psaMtx, (void **) ppdMtx);  // Get data pointer

  return 0;
}




