// VariantLib.h

// NOTE:
// Matlab does not work with SAFEARRAYs
// Matlab 7.1 (R14 SP3) is the only known version of Matlab 
// which supports SAFEARRAYs, but only with JVM.  2008/04/02 SR

#ifndef VARIANTLIB_H
#define VARIANTLIB_H

//-------------------------------------------------------
// Make standard DCOM error code
HRESULT g_ErrorToHresult( int iErr );

// MAKING VARIANT SAFEARRAYS

// 1D array of ints +
int g_MakeVariantArray( int nDim1, VARIANT * pvMtx, int ** ppiMtx );

// 2D array of ints +
int g_MakeVariantArray( int nDim1, int nDim2, VARIANT * pvMtx, int ** ppiMtx );

// 1D array of doubles +
int g_MakeVariantArray( int nDim1, VARIANT * pvMtx, double ** ppdMtx );

// 2D array of doubles +
int g_MakeVariantArray( int nDim1, int nDim2, VARIANT * pvMtx, double ** ppdMtx );


// CHECKING VARIANT SAFEARRAYS

// 1D array of ints, dim unspecified, also allow Nx1 or 1xN arrays +
int g_CheckVariantArray( int * pnDim1, VARIANT vMtx, int ** ppiMtx );

// 2D array of ints, both dims unspecified +
int g_CheckVariantArray( int * pnDim1, int * pnDim2, VARIANT vMtx, int ** ppiMtx );

// 1D array of doubles, also allow Nx1 or 1xN arrays (CP_Display only)
int g_CheckVariantArray( int nDim1, VARIANT vMtx, double ** ppdMtx );

// 1D array of doubles, dim unspecified, also allow Nx1 or 1xN arrays (CP_Display only)
int g_CheckVariantArray( int * pnDim1, VARIANT vMtx, double ** ppdMtx );

// 2D array of doubles +
int g_CheckVariantArray( int nDim1, int nDim2, VARIANT vMtx, double ** ppdMtx );

// 2D array of doubles, second dim unspecified +
int g_CheckVariantArray( int nDim1, int * pnDim2, VARIANT vMtx, double ** ppdMtx );

// 3D array of doubles, first and second dims unspecified (CP_Display only) 
int g_CheckVariantArray( int * pnDim1, int * pnDim2, int nDim3, VARIANT vMtx, double ** ppdMtx );

#endif   //#ifndef VARIANTLIB_H
