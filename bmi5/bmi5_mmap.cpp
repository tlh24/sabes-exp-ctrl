#include <mex.h>
#include <string.h>
#include "../../myopen/common_host/mmaphelp.h"

void mexFunction( int nlhs, mxArray *plhs[ ], int nrhs, const mxArray *prhs[ ] ) {
	//matlab built-in mmap funtionality too slow (scales with # of variables). 
	//we can do better.
	//call this mex function to pass commands; returns new values; 
	//does not do synchronization (at present). 
	size_t length = 256*8;
	mmapHelp mmh(length, "/tmp/bmi5_control", false); // probably too much time here..
	double* b = (double*)mmh.m_addr; // but matlab does not easily support persistent data structures. 
	
	int nfields = mxGetNumberOfFields(prhs[0]); 
	
	for(int f=0; f<nfields; f++){
		const char* fieldname = mxGetFieldNameByNumber(prhs[0], f); 
		bool out = false; 
		for(int j=0; j<256 && fieldname[j]; j++){
			if(fieldname[j] == '_' && fieldname[j+1] == 'o')
				out = true; 
		}
		mxArray* field = mxGetFieldByNumber(prhs[0], 0, f); 
		if(field){
			int m = mxGetM(field); 
			int n = mxGetN(field);
			//mexPrintf("%s is %d by %d\n", fieldname, m, n); 
			double* data = (double*)mxGetData(field); 
			if(data){
				if(!out){
					for(int j=0; j<m*n; j++){
						*b++ = data[j]; 
					}
				}else{
					for(int j=0; j<m*n; j++)
						data[j] = *b++;
				}
			}
		}
	}
	//sync here, to save time.
	int pipe_in = open("bmi5_in", O_RDWR); 
	if(pipe_in <= 0){
		char buf[256];
		getcwd(buf, 256); 
		buf[255] = 0; 
		mexPrintf("could not open ./bmi5_in (make with mkfifo); %s\n", buf); 
	}else{
		write(pipe_in, (void*)"go.", 3); 
		close(pipe_in); 
	}
	int pipe_out = open("bmi5_out", O_RDWR); 
	int ret = 0; 
	if(pipe_out <= 0){
		mexPrintf("could not open ./bmi5_out (make with mkfifo)\n"); 
	}else{
		read(pipe_out, (void*)&ret, sizeof(int)); 
		close(pipe_out); 
	}
	if(nlhs != 1){
		mexPrintf("nlhs = %d, should be 1.\n", nlhs); 
	}else{
		plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
    	double* outMatrix = mxGetPr(plhs[0]);
		outMatrix[0] = (double)ret; 
	}
}
