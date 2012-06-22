// SafeArrayLib.h

// NOTE:
// Matlab accepts 1D and 2D SAFEARRAYS only 2007/04/17 SR

#ifndef SAFEARRAYLIB_H
#define SAFEARRAYLIB_H

//-------------------------------------------------------
// Make standard DCOM error code
HRESULT g_ErrorToHresult( int iErr );

// 1D array of ints
int g_MakeSafeArray( int nDim1, SAFEARRAY ** ppsaMtx, int ** ppiMtx );

// 2D array of ints
int g_MakeSafeArray( int nDim1, int nDim2, SAFEARRAY ** ppsaMtx, int ** ppiMtx );

// 1D array of floats
int g_MakeSafeArray( int nDim1, SAFEARRAY ** ppsaMtx, float ** ppfMtx );

// 2D array of floats
int g_MakeSafeArray( int nDim1, int nDim2, SAFEARRAY ** ppsaMtx, float ** ppfMtx );

// 3D array of floats
int g_MakeSafeArray( int nDim1, int nDim2, int nDim3, SAFEARRAY ** ppsaMtx, float ** ppfMtx );

// 1D array of doubles
int g_MakeSafeArray( int nDim1, SAFEARRAY ** ppsaMtx, double ** ppdMtx );

// 2D array of doubles
int g_MakeSafeArray( int nDim1, int nDim2, SAFEARRAY ** ppsaMtx, double ** ppdMtx );


// CHECKING SAFEARRAYS

// 2D array of ints, second dim unspecified 
int g_CheckSafeArray( int nDim1, int * pnDim2, SAFEARRAY * psaMtx, int ** ppiMtx );

// 2D array of ints, both dims unspecified 
int g_CheckSafeArray( int * pnDim1, int * pnDim2, SAFEARRAY * psaMtx, int ** ppiMtx );

// 2D array of floats 
int g_CheckSafeArray( int nDim1, int nDim2, SAFEARRAY * psaMtx, float ** ppfMtx );

// 2D array of doubles 
int g_CheckSafeArray( int nDim1, int nDim2, SAFEARRAY * psaMtx, double ** ppdMtx );


#endif   //#ifndef SAFEARRAYLIB_H
