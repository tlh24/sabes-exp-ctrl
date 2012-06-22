// VariantLib.h

// NOTE:
// Matlab accepts 1D and 2D SAFEARRAYS only 2007/04/17 SR
// Matlab without JVM does not support SAFEARRAYs.  2008/03/24 SR

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

// 1D array of floats
//int g_MakeVariantArray( int nDim1, VARIANT ** ppvMtx, float ** ppfMtx );

// 2D array of floats
//int g_MakeVariantArray( int nDim1, int nDim2, VARIANT ** ppvMtx, float ** ppfMtx );

// 3D array of floats
//int g_MakeVariantArray( int nDim1, int nDim2, int nDim3, VARIANT ** ppvMtx, float ** ppfMtx );

// 1D array of doubles +
int g_MakeVariantArray( int nDim1, VARIANT * pvMtx, double ** ppdMtx );

// 2D array of doubles +
int g_MakeVariantArray( int nDim1, int nDim2, VARIANT * pvMtx, double ** ppdMtx );

// 3D array of doubles
//int g_MakeVariantArray( int nDim1, int nDim2, int nDim3, VARIANT ** ppvMtx, double ** ppdMtx );


// CHECKING VARIANT SAFEARRAYS

// 1D array of ints, allow Nx1 or 1xN arrays
//int g_CheckVariantArray( int nDim1, VARIANT * pvMtx, int ** ppiMtx );

// 1D array of ints, dim unspecified, also allow Nx1 or 1xN arrays +
int g_CheckVariantArray( int * pnDim1, VARIANT vMtx, int ** ppiMtx );

// 2D array of ints, second dim unspecified 
//int g_CheckVariantArray( int nDim1, int * pnDim2, VARIANT * pvMtx, int ** ppiMtx );

// 2D array of ints, both dims unspecified +
int g_CheckVariantArray( int * pnDim1, int * pnDim2, VARIANT vMtx, int ** ppiMtx );

// 1D array of floats 
//int g_CheckVariantArray( int nDim1, VARIANT * pvMtx, float ** ppfMtx );

// 2D array of floats 
//int g_CheckVariantArray( int nDim1, int nDim2, VARIANT * pvMtx, float ** ppfMtx );

// 1D array of doubles, also allow Nx1 or 1xN arrays
//int g_CheckVariantArray( int nDim1, VARIANT * pvMtx, double ** ppdMtx );

// 2D array of doubles +
int g_CheckVariantArray( int nDim1, int nDim2, VARIANT vMtx, double ** ppdMtx );

// 2D array of doubles, second dim unspecified +
int g_CheckVariantArray( int nDim1, int * pnDim2, VARIANT vMtx, double ** ppdMtx );

// 2D array of doubles, first dim unspecified 
//int g_CheckVariantArray( int * pnDim1, int nDim2, VARIANT * pvMtx, double ** ppdMtx );

// 3D array of doubles, first and second dims unspecified 
//int g_CheckVariantArray( int * pnDim1, int * pnDim2, int nDim3, VARIANT * pvMtx, double ** ppdMtx );


#endif   //#ifndef VARIANTLIB_H
