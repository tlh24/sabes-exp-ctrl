// SafeArrayLib.h

// NOTE:
// Matlab accepts 2-D SAFEARRAYS only, so we have to represent
// 1-D arrays (vectors) as 2-D,  1 x N in C++


#ifndef SAFEARRAYLIB_H
#define SAFEARRAYLIB_H

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


// CHECKING SAFEARRAYS

// 2D array of ints, second dim unspecified 
int g_CheckSafeArray( int nDim1, int * pnDim2, SAFEARRAY * psaMtx, int ** ppiMtx );

// 2D array of ints, both dims unspecified 
int g_CheckSafeArray( int * pnDim1, int * pnDim2, SAFEARRAY * psaMtx, int ** ppiMtx );

// 2D array of floats 
int g_CheckSafeArray( int nDim1, int nDim2, SAFEARRAY * psaMtx, float ** ppfMtx );



#endif   //#ifndef SAFEARRAYLIB_H
