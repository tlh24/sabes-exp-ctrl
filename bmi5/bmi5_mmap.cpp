#include <mex.h>
#include <string.h>
#include "../../myopen/common_host/mmaphelp.h"

#define BMI5_CTRL_MMAP	"/tmp/bmi5_control.mmap"
#define BMI5_IN_FIFO	"/tmp/bmi5_in.fifo"
#define BMI5_OUT_FIFO	"/tmp/bmi5_out.fifo"

void mexFunction( int nlhs, mxArray *plhs[ ], int nrhs, const mxArray *prhs[ ] ) {
	//matlab built-in mmap funtionality too slow (scales with # of variables). 
	//we can do better.
	//call this mex function to pass commands; returns new values; 
	//does not do synchronization (at present). 
	size_t length = 256*8;
	mmapHelp mmh(length, BMI5_CTRL_MMAP, false); // probably too much time here..
	double* b = (double*)mmh.m_addr; // but matlab does not easily support persistent data structures. 
	
	if(nrhs == 1){
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
	}else{
		mexPrintf("bmi5_mmap: please supply the b5 structure as an argument.\n"); 
	}
	//sync here, to save time.
	int pipe_in = open(BMI5_IN_FIFO, O_RDWR); 
	if(pipe_in <= 0){
		char buf[256];
		getcwd(buf, 256); 
		buf[255] = 0; 
		mexPrintf("bmi5_mmap: could not open fifo: %s; %s\n", BMI5_IN_FIFO, buf); 
	}else{
		write(pipe_in, (void*)"go.", 3); 
		close(pipe_in); 
	}
	int pipe_out = open(BMI5_OUT_FIFO, O_RDWR); 
	int ret = 0; 
	if(pipe_out <= 0){
		mexPrintf("bmi5_mmap: could not open fifo: %s\n",BMI5_OUT_FIFO); 
	}else{
		read(pipe_out, (void*)&ret, sizeof(int)); 
		close(pipe_out); 
	}
	if(nlhs == 1){
		plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
    	double* outMatrix = mxGetPr(plhs[0]);
		outMatrix[0] = (double)ret; 
	}
}
