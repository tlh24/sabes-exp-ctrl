#include <mex.h>
#include <string.h>
#include "../../myopen/common_host/mmaphelp.h"

void mexFunction( int nlhs, mxArray *plhs[ ], int nrhs, const mxArray *prhs[ ] ) {
	//matlab built-in mmap funtionality too slow (scales with # of variables). 
	//we can do better.
	//call this mex function to pass commands; returns new values; 
	//does not do synchronization (at present). 
	size_t length = 256*8; //mmapFileSize(g_objs); 
	mmapHelp mmh(length, "/tmp/bmi5_control"); 
	double* b = (double*)mmh.m_addr; 
	
	int nelements = mxGetNumberOfElements(prhs[0]); 
	int nfields = mxGetNumberOfFields(prhs[0]); 
	//mexPrintf("nelements %d nfields %d \n", nelements, nfields); 
	
	for(int f=0; f<nfields; f++){
		const char* fieldname = mxGetFieldNameByNumber(prhs[0], f); 
		int sl = strlen(fieldname); 
		bool out = false; 
		if(fieldname[sl-1] == 'o' && fieldname[sl-2] == '_')
			out = true; //output of bmi5.
		mxArray* field = mxGetFieldByNumber(prhs[0], 0, f); 
		if(field){
			int m = mxGetM(field); 
			int n = mxGetN(field);
			//mexPrintf("%s is %d by %d\n", fieldname, m, n); 
			double* data = (double*)mxGetData(field); 
			if(data){
				if(!out){
					//mexPrintf("contents: "); 
					for(int j=0; j<m*n; j++){
						*b++ = data[j]; 
						//mexPrintf("%f ", data[j]); 
					}
					//mexPrintf("\n"); 
				}else{
					for(int j=0; j<m*n; j++)
						data[j] = *b++;
				}
			}
		}
	}
	if(nlhs != 0){
		mexPrintf("nlhs = %d\n", nlhs); 
	}
}
