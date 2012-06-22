// ComUtils.cpp

#include "StdAfx.h"

#include <comdef.h>
#include "stdio.h"

#include "ComUtils.h"

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// DEAL WITH VARIANTS
//////////////////////////////////////////////////////////////////////////

///////////////////////////////// CREATE VARIANT FROM 1D ARRAY
// Note: Use VariantClear to free resources after call to VariantFromArray

/// TYPE INDEPENDENT IMPLEMENTATION
void
VariantFromArray(int n, void *a, VARIANT *var, int type)
{
	SAFEARRAY *psa;
	void *sap;
	int i;
	
	////// Construct the SafeArray
	psa = SafeArrayCreateVector(type,0,n);	// Create the safearray
	SafeArrayAccessData(psa, (void**)&sap);	// Access data pts
	// fill data according to type
	switch (type)
	{
	case VT_BOOL:
		for(i=0;i<n;i++) ((BOOL*)sap)[i]=((BOOL *)a)[i];
		break;
	case VT_UI1:
		for(i=0;i<n;i++) ((unsigned char*)sap)[i]=((unsigned char *)a)[i];
		break;
	case VT_I2:
		for(i=0;i<n;i++) ((short*)sap)[i]=((short *)a)[i];
		break;
	case VT_I4:
		for(i=0;i<n;i++) ((long*)sap)[i]=((long *)a)[i];
		break;
	case VT_R4:
		for(i=0;i<n;i++) ((float*)sap)[i]=((float *)a)[i];
		break;
	case VT_R8:
		for(i=0;i<n;i++) ((double*)sap)[i]=((double *)a)[i];
		break;
	}
	SafeArrayUnaccessData(psa);				// Unaccess
	// Construct the Variant
	VariantInit(var);			// Initialize the Variant
	var->vt = VT_ARRAY|type;	// Tell it to hold an array of floats
	var->parray = psa;
}

/// TYPE SPECIFIC CALLS
void VariantFromArray(int n, BOOL *a, VARIANT *var){ VariantFromArray(n,(void *)a,var,VT_BOOL); }
void VariantFromArray(int n, unsigned char *a, VARIANT *var){ VariantFromArray(n,(void *)a,var,VT_UI1); }
void VariantFromArray(int n, short *a, VARIANT *var){ VariantFromArray(n,(void *)a,var,VT_I2); }
void VariantFromArray(int n, long *a, VARIANT *var){ VariantFromArray(n,(void *)a,var,VT_I4); }
void VariantFromArray(int n, float *a, VARIANT *var){ VariantFromArray(n,(void *)a,var,VT_R4); }
void VariantFromArray(int n, double *a, VARIANT *var){ VariantFromArray(n,(void *)a,var,VT_R8); }


///////////////////////////////// CREATE VARIANT FROM 2D ARRAY
// Note: Use VariantClear to free resources after call to VariantFromArray

/// TYPE INDEPENDENT IMPLEMENTATION
void
VariantFromArray2(int *n, void **a, VARIANT *var, int type)
{
	int dim=2;
	SAFEARRAY *psa;
    SAFEARRAYBOUND *sabnd = new SAFEARRAYBOUND[dim];
	void *sap;
	int i,j,ct;
	
	////// Construct the SafeArray and total size
	for(i=0;i<dim;i++){  sabnd[i].cElements=n[i];  sabnd[i].lLbound=0; }	// Fill Bounds
	psa = SafeArrayCreate(type,dim,sabnd);									// Create the safearray
	SafeArrayAccessData(psa, (void**)&sap);									// Access data pts
	
	// fill data according to type
	switch (type)
	{
	case VT_BOOL:
		for(ct=j=0;j<n[1];j++) for(i=0;i<n[0];i++,ct++) 
			((BOOL*)sap)[ct]=((BOOL **)a)[i][j];
		break;
	case VT_UI1:
		for(ct=j=0;j<n[1];j++) for(i=0;i<n[0];i++,ct++) 
			((unsigned char*)sap)[ct]=((unsigned char **)a)[i][j];
		break;
	case VT_I2:
		for(ct=j=0;j<n[1];j++) for(i=0;i<n[0];i++,ct++) 
			((short*)sap)[ct]=((short **)a)[i][j];
		break;
	case VT_I4:
		for(ct=j=0;j<n[1];j++) for(i=0;i<n[0];i++,ct++) 
			((long*)sap)[ct]=((long **)a)[i][j];
		break;
	case VT_R4:
		for(ct=j=0;j<n[1];j++) for(i=0;i<n[0];i++,ct++) 
			((float*)sap)[ct]=((float **)a)[i][j];
		break;
	case VT_R8:
		for(ct=j=0;j<n[1];j++) for(i=0;i<n[0];i++,ct++) 
			((double*)sap)[ct]=((double **)a)[i][j];
		break;
	}
	SafeArrayUnaccessData(psa);				// Unaccess
	// Construct the Variant
	VariantInit(var);			// Initialize the Variant
	var->vt = VT_ARRAY|type;	// Tell it to hold an array of floats
	var->parray = psa;
}

/// TYPE SPECIFIC CALLS
void VariantFromArray2(int *n, BOOL **a, VARIANT *var){ VariantFromArray2(n,(void **)a,var,VT_BOOL); }
void VariantFromArray2(int *n, unsigned char **a, VARIANT *var){ VariantFromArray2(n,(void **)a,var,VT_UI1); }
void VariantFromArray2(int *n, short **a, VARIANT *var){ VariantFromArray2(n,(void **)a,var,VT_I2); }
void VariantFromArray2(int *n, long **a, VARIANT *var){ VariantFromArray2(n,(void **)a,var,VT_I4); }
void VariantFromArray2(int *n, float **a, VARIANT *var){ VariantFromArray2(n,(void **)a,var,VT_R4); }
void VariantFromArray2(int *n, double **a, VARIANT *var){ VariantFromArray2(n,(void **)a,var,VT_R8); }


///////////////////////////////// CREATE VARIANT FROM 3D ARRAY
// Note: Use VariantClear to free resources after call to VariantFromArray

/// TYPE INDEPENDENT IMPLEMENTATION
void
VariantFromArray3(int *n, void ***a, VARIANT *var, int type)
{
	int dim=3;
	SAFEARRAY *psa;
    SAFEARRAYBOUND *sabnd = new SAFEARRAYBOUND[dim];
	void *sap;
	int i,j,k,ct;
	
	////// Construct the SafeArray and total size
	for(i=0;i<dim;i++){  sabnd[i].cElements=n[i];  sabnd[i].lLbound=0; }	// Fill Bounds
	psa = SafeArrayCreate(type,dim,sabnd);									// Create the safearray
	SafeArrayAccessData(psa, (void**)&sap);									// Access data pts
	
	// fill data according to type
	switch (type)
	{
	case VT_BOOL:
		for(ct=k=0;k<n[2];k++) for(j=0;j<n[1];j++) for(i=0;i<n[0];i++,ct++) 
			((BOOL*)sap)[ct]=((BOOL ***)a)[i][j][k];
		break;
	case VT_UI1:
		for(ct=k=0;k<n[2];k++) for(j=0;j<n[1];j++) for(i=0;i<n[0];i++,ct++) 
			((unsigned char*)sap)[ct]=((unsigned char ***)a)[i][j][k];
		break;
	case VT_I2:
		for(ct=k=0;k<n[2];k++) for(j=0;j<n[1];j++) for(i=0;i<n[0];i++,ct++) 
			((short*)sap)[ct]=((short ***)a)[i][j][k];
		break;
	case VT_I4:
		for(ct=k=0;k<n[2];k++) for(j=0;j<n[1];j++) for(i=0;i<n[0];i++,ct++) 
			((long*)sap)[ct]=((long ***)a)[i][j][k];
		break;
	case VT_R4:
		for(ct=k=0;k<n[2];k++) for(j=0;j<n[1];j++) for(i=0;i<n[0];i++,ct++) 
			((float*)sap)[ct]=((float ***)a)[i][j][k];
		break;
	case VT_R8:
		for(ct=k=0;k<n[2];k++) for(j=0;j<n[1];j++) for(i=0;i<n[0];i++,ct++) 
			((double*)sap)[ct]=((double ***)a)[i][j][k];
		break;
	}
	SafeArrayUnaccessData(psa);				// Unaccess
	// Construct the Variant
	VariantInit(var);			// Initialize the Variant
	var->vt = VT_ARRAY|type;	// Tell it to hold an array of floats
	var->parray = psa;
}

/// TYPE SPECIFIC CALLS
void VariantFromArray3(int *n, BOOL ***a, VARIANT *var){ VariantFromArray3(n,(void ***)a,var,VT_BOOL); }
void VariantFromArray3(int *n, unsigned char ***a, VARIANT *var){ VariantFromArray3(n,(void ***)a,var,VT_UI1); }
void VariantFromArray3(int *n, short ***a, VARIANT *var){ VariantFromArray3(n,(void ***)a,var,VT_I2); }
void VariantFromArray3(int *n, long ***a, VARIANT *var){ VariantFromArray3(n,(void ***)a,var,VT_I4); }
void VariantFromArray3(int *n, float ***a, VARIANT *var){ VariantFromArray3(n,(void ***)a,var,VT_R4); }
void VariantFromArray3(int *n, double ***a, VARIANT *var){ VariantFromArray3(n,(void ***)a,var,VT_R8); }



///////////////////////////////// CREATE 1D ARRAY FROM VARIANT
// Note: Use "delete a" to free resources after a call to VariantToArray

/// TYPE INDEPENDENT IMPLEMENTATION
int
VariantToArray(int *n, void **a, VARIANT *var, int type)
{
	long uBnd,lBnd,dim;
	int err=0;
	
	// Check for ARRAY of the right type
	if( var==NULL )						return COMUTIL_ERR_NULL;
	if( !( (var->vt) & VT_ARRAY ) )		err += COMUTIL_ERR_ARRAY;
	if( !( (var->vt) & type ) )			err += COMUTIL_ERR_TYPE;
	if(err) return err;
	
	// Get Overall Length (number of elements, ignore shape of Safearray)
	dim = SafeArrayGetDim(var->parray);
	*n=1;
	for(int d=1; d<=dim; d++){ 
		SafeArrayGetLBound(var->parray, d, &lBnd);
		SafeArrayGetUBound(var->parray, d, &uBnd);
		(*n) *= uBnd-lBnd+1;
	}
	
	
	// Get reference pointer for accessing the SafeArray
	void *sap;
	int i;
	if( FAILED( SafeArrayAccessData(var->parray, (void**)&sap) )) return COMUTIL_ERR_SAFEARRAY;
	// Copy data to SafeArray according to type
	switch (type)
	{
	case VT_BOOL:
		*a=(void *)new BOOL[*n];
		for(i=0;i<(*n);i++) ((BOOL*)*a)[i]=((BOOL*)sap)[i];
		break;
	case VT_I2:
		*a=(void *)new short[*n];
		for(i=0;i<(*n);i++) ((short*)*a)[i]=((short*)sap)[i];
		break;
	case VT_I4:
		*a=(void *)new long[*n];
		for(i=0;i<(*n);i++) ((long*)*a)[i]=((long*)sap)[i];
		break;
	case VT_R4:
		*a=(void *)new float[*n];
		for(i=0;i<(*n);i++) ((float*)*a)[i]=((float*)sap)[i];
		break;
	case VT_R8:
		*a=(void *)new double[*n];
		for(i=0;i<(*n);i++) ((double*)*a)[i]=((double*)sap)[i];
		break;
	}
	
	// Release reference pointer
	SafeArrayUnaccessData (var->parray);
	// Return Success
	return 0;
}

/// TYPE SPECIFIC CALLS
int VariantToArray(int *n, BOOL **a, VARIANT *var){ return VariantToArray(n,(void **)a,var, VT_BOOL); }  
int VariantToArray(int *n, unsigned char **a, VARIANT *var){ return VariantToArray(n,(void **)a,var, VT_UI1); }  
int VariantToArray(int *n, short **a, VARIANT *var){ return VariantToArray(n,(void **)a,var, VT_I2); }  
int VariantToArray(int *n, long **a, VARIANT *var){ return VariantToArray(n,(void **)a,var, VT_I4); }  
int VariantToArray(int *n, float **a, VARIANT *var){ return VariantToArray(n,(void **)a,var, VT_R4); }  
int VariantToArray(int *n, double **a, VARIANT *var){ return VariantToArray(n,(void **)a,var, VT_R8); }  




///////////////////////////////// CREATE 2D ARRAY FROM VARIANT
// Note: Use "delete a" to free resources after a call to VariantToArray

/// TYPE INDEPENDENT IMPLEMENTATION
int
VariantToArray2(int **n, void ***a, VARIANT *var, int type)
{
	long *ub,*lb,dim;
	int i,j,ct,err=0;
	
	// Check for ARRAY of the right type
	if( var==NULL )									return COMUTIL_ERR_NULL;
	if( !( (var->vt) & VT_ARRAY ) )					err += COMUTIL_ERR_ARRAY;
	if( !( (var->vt) & type ) )						err += COMUTIL_ERR_TYPE;
	if( (dim = SafeArrayGetDim(var->parray))!=2 )	err += COMUTIL_ERR_DIM;
	if(err) return err;
	
	// Get Overall Length (number of elements, ignore shape of Safearray)
	(*n) = new int[dim];
	ub   = new long[dim];
	lb   = new long[dim];
	for(i=0; i<dim; i++){ 
		SafeArrayGetLBound(var->parray, i+1, &(lb[i]));
		SafeArrayGetUBound(var->parray, i+1, &(ub[i]));
		(*n)[i] = (int)(ub[i]-lb[i]+1);
	}
	
	
	// Get reference pointer for accessing the SafeArray
	void *sap;
	if( FAILED( SafeArrayAccessData(var->parray, (void**)&sap) )) return COMUTIL_ERR_SAFEARRAY;
	// Copy data to SafeArray according to type
	switch (type)
	{
	case VT_BOOL:
		{
			// Create Array
			*a=(void **)new BOOL*[(*n)[0]];
			for(i=0;i<(*n)[0];i++) (*a)[i]=(void *)new BOOL[(*n)[1]];
			// Load It
			BOOL **av=(BOOL **)(*a);
			for(ct=j=0;j<(*n)[1];j++) for(i=0;i<(*n)[0];i++,ct++) av[i][j]=((BOOL*)sap)[ct];
		}
		break;
	case VT_UI1:
		{
			// Create Array
			*a=(void **)new unsigned char*[(*n)[0]];
			for(i=0;i<(*n)[0];i++) (*a)[i]=(void *)new unsigned char[(*n)[1]];
			// Load It
			unsigned char **av=(unsigned char **)(*a);
			for(ct=j=0;j<(*n)[1];j++) for(i=0;i<(*n)[0];i++,ct++) av[i][j]=((unsigned char*)sap)[ct];
		}
		break;
	case VT_I2:
		{
			// Create Array
			*a=(void **)new short*[(*n)[0]];
			for(i=0;i<(*n)[0];i++) (*a)[i]=(void *)new short[(*n)[1]];
			// Load It
			short **av=(short **)(*a);
			for(ct=j=0;j<(*n)[1];j++) for(i=0;i<(*n)[0];i++,ct++) av[i][j]=((short*)sap)[ct];
		}
		break;
	case VT_I4:
		{
			// Create Array
			*a=(void **)new long*[(*n)[0]];
			for(i=0;i<(*n)[0];i++) (*a)[i]=(void *)new long[(*n)[1]];
			// Load It
			long **av=(long **)(*a);
			for(ct=j=0;j<(*n)[1];j++) for(i=0;i<(*n)[0];i++,ct++) av[i][j]=((long*)sap)[ct];
		}
		break;
	case VT_R4:
		{
			// Create Array
			*a=(void **)new float*[(*n)[0]];
			for(i=0;i<(*n)[0];i++) (*a)[i]=(void *)new float[(*n)[1]];
			// Load It
			float **av=(float **)(*a);
			for(ct=j=0;j<(*n)[1];j++) for(i=0;i<(*n)[0];i++,ct++) av[i][j]=((float*)sap)[ct];
		}
		break;
	case VT_R8:
		{
			// Create Array
			*a=(void **)new double*[(*n)[0]];
			for(i=0;i<(*n)[0];i++) (*a)[i]=(void *)new double[(*n)[1]];
			// Load It
			double **av=(double **)(*a);
			for(ct=j=0;j<(*n)[1];j++) for(i=0;i<(*n)[0];i++,ct++) av[i][j]=((double*)sap)[ct];
		}
		break;
	}
	
	// Release reference pointer
	SafeArrayUnaccessData (var->parray);
	// Return Success
	return 0;
}

/// TYPE SPECIFIC CALLS
int VariantToArray2(int **n, BOOL ***a, VARIANT *var){ return VariantToArray2(n,(void ***)a,var, VT_BOOL); }  
int VariantToArray2(int **n, unsigned char ***a, VARIANT *var){ return VariantToArray2(n,(void ***)a,var, VT_UI1); }  
int VariantToArray2(int **n, short ***a, VARIANT *var){ return VariantToArray2(n,(void ***)a,var, VT_I2); }  
int VariantToArray2(int **n, long ***a, VARIANT *var){ return VariantToArray2(n,(void ***)a,var, VT_I4); }  
int VariantToArray2(int **n, float ***a, VARIANT *var){ return VariantToArray2(n,(void ***)a,var, VT_R4); }  
int VariantToArray2(int **n, double ***a, VARIANT *var){ return VariantToArray2(n,(void ***)a,var, VT_R8); }  



///////////////////////////////// CREATE 3D ARRAY FROM VARIANT
// Note: Use "delete a" to free resources after a call to VariantToArray

/// TYPE INDEPENDENT IMPLEMENTATION
int
VariantToArray3(int **n, void ****a, VARIANT *var, int type)
{
	long *ub,*lb,dim;
	int i,j,k,ct,err=0;
	
	// Check for ARRAY of the right type
	if( var==NULL )									return COMUTIL_ERR_NULL;
	if( !( (var->vt) & VT_ARRAY ) )					err += COMUTIL_ERR_ARRAY;
	if( !( (var->vt) & type ) )						err += COMUTIL_ERR_TYPE;
	if( (dim = SafeArrayGetDim(var->parray))!=3 )	err += COMUTIL_ERR_DIM;
	if(err) return err;
	
	// Get Overall Length (number of elements, ignore shape of Safearray)
	(*n) = new int[dim];
	ub   = new long[dim];
	lb   = new long[dim];
	for(i=0; i<dim; i++){ 
		SafeArrayGetLBound(var->parray, i+1, &(lb[i]));
		SafeArrayGetUBound(var->parray, i+1, &(ub[i]));
		(*n)[i] = (int)(ub[i]-lb[i]+1);
	}
	
	
	// Get reference pointer for accessing the SafeArray
	void *sap;
	if( FAILED( SafeArrayAccessData(var->parray, (void**)&sap) )) return COMUTIL_ERR_SAFEARRAY;
	// Copy data to SafeArray according to type
	switch (type)
	{
	case VT_UI1:
		{
			// Create Array
			*a=(void ***)new unsigned char**[(*n)[0]];
			for(i=0;i<(*n)[0];i++) 
			{	
				(*a)[i]=(void **)new unsigned char*[(*n)[1]];
				for(j=0;j<(*n)[1];j++) (*a)[i][j]=(void *)new unsigned char[(*n)[2]];
				
			}
			// Load It
			unsigned char ***av=(unsigned char ***)(*a);
			for(ct=k=0;k<(*n)[2];k++) 
				for(j=0;j<(*n)[1];j++) 
					for(i=0;i<(*n)[0];i++,ct++) 
						av[i][j][k]=((unsigned char*)sap)[ct];
		}	
		break;
	case VT_R8:
		{
			// Create Array
			*a=(void ***)new double**[(*n)[0]];
			for(i=0;i<(*n)[0];i++) 
			{	
				(*a)[i]=(void **)new double*[(*n)[1]];
				for(j=0;j<(*n)[1];j++) (*a)[i][j]=(void *)new double[(*n)[2]];
				
			}
			// Load It
			double ***av=(double ***)(*a);
			for(ct=k=0;k<(*n)[2];k++) 
				for(j=0;j<(*n)[1];j++) 
					for(i=0;i<(*n)[0];i++,ct++) 
						av[i][j][k]=((double*)sap)[ct];
		}
		break;
	}
	
	// Release reference pointer
	SafeArrayUnaccessData (var->parray);
	// Return Success
	return 0;
}

/// TYPE SPECIFIC CALLS
int VariantToArray3(int **n, unsigned char ****a, VARIANT *var){ return VariantToArray3(n,(void ****)a,var, VT_UI1); }  
int VariantToArray3(int **n, double ****a, VARIANT *var){ return VariantToArray3(n,(void ****)a,var, VT_R8); }  



////////////////////////////////////////////////////
///// HRESULT Error Status...

void
HResultErrMessageBox( char *userMessage, HRESULT hr )
{
	
	if(SUCCEEDED(hr)) return; // Only Put A Message in Case of Error
	
	// construct a _com_error using the HRESULT
	_com_error e(hr);
	
	/////////////////////////
	// construct the Message String
	char mstr[200];
	
	sprintf(mstr,"%s\n\n",userMessage);
	
	// convert to hexidecimal string and display
	sprintf(mstr,"%s\nError:   \t0x%x", mstr, hr );
	sprintf(mstr,"%s\nDecimal: \t%x",   mstr, hr );
	sprintf(mstr,"%s\nFacility:\t%d\n", mstr, hr );
	sprintf(mstr,"%s\nSCODE   :\t%d",   mstr, HRESULT_CODE(hr));
	sprintf(mstr,"%s\nFacility:\t%d",   mstr, HRESULT_FACILITY(hr));
	sprintf(mstr,"%s\nSeverity:\t%d",   mstr, HRESULT_SEVERITY(hr));
	// Use the _com_error object to format a message string. This is 
	// Much easier then using ::FormatMessage
	sprintf(mstr,"%s\n%s",  mstr, e.ErrorMessage());
	///////////////////////////
	
	// Make the Message Box
	MessageBox(NULL, mstr, "VisServer", MB_OK | MB_ICONINFORMATION);
}
