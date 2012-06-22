// ComUtils2.cpp

//#include "StdAfx.h"

#include <comdef.h>
#include "stdio.h"

#include "ComUtils.h"
#include "ComUtils2.h"


///////////////////////////////////////////////////////////////////////////
// VARIANT / ARRAY STUFF

const int MAXDIM = 8;

inline int GetOffset(int dim)
{
    return ((dim+2) * sizeof(int) + sizeof(double) - 1)/sizeof(double);
}

double *CreateDoubleArray(int dim, int *dimlen)
{
	int i, len = 1, offset = GetOffset(dim);
	for (i=0; i < dim; ++i) len = len * dimlen[i];
	if (len == 0) return NULL;
	double *result = new double[offset+len];
	// logToFile((f, "DoubleArrayCreated: 0x%p\n", result));
	result = result + offset;
	((int *)result)[-1] = len;
    ((int *)result)[-2] = dim;
	for (i=0; i < dim; ++i)
		((int *)result)[-3-i] = dimlen[i];
	return result;
}

double *CopyDoubleArray(double *data)
{
    if (data == NULL) return NULL;
    int dim = GetDim(data), len = GetLength(data);
    int offset = GetOffset(dim);
	double *result = new double[offset+len];
//	logToFile((f, "DoubleArrayCreated: 0x%p\n", result));
	result = result + offset;
    memcpy(result-offset, data-offset, sizeof(double)*(offset+len));
    return result;
}

double *CopyDoubleArrayStruct(double *data)
{
    if (data == NULL) return NULL;
    int dim = GetDim(data), len = GetLength(data);
    int offset = GetOffset(dim);
	double *result = new double[offset+len];
//	logToFile((f, "DoubleArrayCreated: 0x%p\n", result));
	result = result + offset;
    memcpy(result-offset, data-offset, sizeof(double)*offset);
    return result;
}

void FreeDoubleArray(double *data)
{
    if (data != NULL)
	{
		data = data - GetOffset(GetDim(data));
//		logToFile((f, "DoubleArrayFreed: 0x%p\n", data));
		delete[] data;
	}
}

int VariantToDoubleArray(double **data, VARIANT *var)
{
	long uBnd,lBnd;
	int dim, dimlen[MAXDIM];
	int err=0;
	
	// Check for ARRAY of the right type
    //logToFile((f, "VaraintToDoubleArray: var = 0x%p\n", var));
	if( var==NULL )						return COMUTIL_ERR_NULL;
    //logToFile((f, "VaraintToDoubleArray: var.type = %d\n", var->vt));
	if (var->vt == VT_ERROR){
		*data = NULL;
		return 0;
	}
	if( !( (var->vt) & VT_ARRAY ) )		err += COMUTIL_ERR_ARRAY;
	if( !( (var->vt) & VT_R8 ) )		err += COMUTIL_ERR_TYPE;
	if(err) return err;
	
	// Get Overall Length (number of elements, ignore shape of Safearray)
	dim = SafeArrayGetDim(var->parray);
	for(int d=1; d<=dim; d++){
		SafeArrayGetLBound(var->parray, d, &lBnd);
		SafeArrayGetUBound(var->parray, d, &uBnd);
		dimlen[d-1] = uBnd-lBnd+1;
	}
	
    //logToFile((f, "VaraintToDoubleArray: %d, (%d, %d)\n", dim, dimlen[0], dimlen[1]));

	*data = CreateDoubleArray(dim, dimlen);
	if (*data != NULL)
	{
		// Get reference pointer for accessing the SafeArray
		void *sap;
		if( FAILED( SafeArrayAccessData(var->parray, (void**)&sap) )) return COMUTIL_ERR_SAFEARRAY;
		memcpy(*data, sap, sizeof(double) * GetLength(*data));
		
		// Release reference pointer
		SafeArrayUnaccessData (var->parray);
	}
	// Return Success
	return 0;
}

int VariantFromDoubleArray(double *data, VARIANT *var)
{
	int dim;
	long len;
	SAFEARRAY *psa;
	SAFEARRAYBOUND sabnd[MAXDIM];
	void *sap;
	
	if (data != NULL)
	{
		dim = GetDim(data);
		len = GetLength(data);
		////// Construct the SafeArray and total size
		for(int i=0;i<dim;i++){  	// Fill Bounds
			sabnd[i].cElements=GetLength(data, i);  
			sabnd[i].lLbound=0; 
		}
		psa = SafeArrayCreate(VT_R8,dim,sabnd);									// Create the safearray
		SafeArrayAccessData(psa, (void**)&sap);									// Access data pts
		
		memcpy(sap, data, sizeof(double)*len);

		SafeArrayUnaccessData(psa);				// Unaccess
	} else
	{
		dim = 1;
		////// Construct the SafeArray and total size
		for(int i=0;i<dim;i++){  	// Fill Bounds
			sabnd[i].cElements=0;  
			sabnd[i].lLbound=0; 
		}
		psa = SafeArrayCreate(VT_R8,dim,sabnd);									// Create the safearray
	}
    
	// Construct the Variant
	VariantInit(var);			// Initialize the Variant
	var->vt = VT_ARRAY|VT_R8;	// Tell it to hold an array of floats
	var->parray = psa;

	return 0;
}

