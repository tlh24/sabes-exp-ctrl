#include <mex.h>
#include <string.h>
#include "mmaphelp.h" // expects to be installed in e.g. /usr/local/include

#define BMI5_CTRL_MMAP	"/tmp/bmi5_control.mmap"
#define BMI5_IN_FIFO	"/tmp/bmi5_in.fifo"
#define BMI5_OUT_FIFO	"/tmp/bmi5_out.fifo"

#define B5_IN 1
#define B5_OUT 2
#define B5_IO (B5_IN | B5_OUT)


int doMmap(mxArray *oa, double *b, bool read, int nfields, char* out){
	int w = 0; 
	for(int f=0; f<nfields; f++){
		mxArray* field = mxGetFieldByNumber(oa, 0, f); 
		if(field){
			int m = mxGetM(field); 
			int n = mxGetN(field);
			if(0){
				const char* fieldname = mxGetFieldNameByNumber(oa, f); 
				mexPrintf("%s is %d by %d ", fieldname, m, n); 
				if(out[f]) mexPrintf("out "); 
				else mexPrintf("in "); 
			}
			double* data = (double*)mxGetData(field); 
			if(data){
				for(int j=0; j<m*n; j++){
					if(read){ //matlab -> bmi5
						if(out[f] & B5_IN)
							*b++ = data[j]; 
						else *b++; //keep pointer in sync.
					} else { //bmi5 -> matlab
						if(out[f] & B5_OUT)
							data[j] = *b++; 
						else *b++; 
					}
				}
				w += n*m; 
			}
		}
	}
	//check alignment from bmi5 -- alarmingly easy to mess this up!
	if(!read && w != (int)(*b)){
		mexPrintf("bmi5_mmap: misalignment error!\n");
		mexPrintf(" you gave %d in struture, expected %d.\n", w, (int)(*b));  
	}
}

char* getInOut(const mxArray *prhs[ ], int nfields){
	char *out = (char*)malloc(nfields * sizeof(bool)); 
	for(int f=0; f<nfields; f++){
		const char* fieldname = mxGetFieldNameByNumber(prhs[0], f); 
		out[f] = B5_IN; 
		for(int j=0; j<256 && fieldname[j]; j++){
			if(fieldname[j] == '_' && fieldname[j+1] == 'o')
				out[f] = B5_OUT; 
			if(fieldname[j] == '_' && fieldname[j+1] == 'i' && fieldname[j+2] == 'o')
				out[f] = B5_IO; 
		}
	}
	return out; 
}

void mexFunction( int nlhs, mxArray *plhs[ ], int nrhs, const mxArray *prhs[ ] ) {
	//matlab built-in mmap funtionality too slow (scales with # of variables). 
	//we can do better.
	// call bmi5_mmap(b5) to modify b5 in-place (careful, matlab sometimes copies-by-reference)
	// or b5 = bmi5_mmap(b5) to get a completely new structure (malloc, memcpy)
	size_t length = 8*1024*8;
	mxArray* oa = 0; //output array.
	int ret = 0; 
	if(nrhs == 1){
		mmapHelp mmh(length, BMI5_CTRL_MMAP, false); // probably too much time here..
		double* b = (double*)mmh.m_addr; // but matlab does not easily support persistent data structures. 
		int nfields = mxGetNumberOfFields(prhs[0]); 
		char* out = getInOut(prhs, nfields); 
		if(nlhs == 1){
			oa = mxDuplicateArray(prhs[0]); //deep copy.
		} else {
			oa = (mxArray*)prhs[0]; //shallow copy.
		}
	// INCOMING DATA!
		doMmap(oa, b, true, nfields, out); 
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
		if(pipe_out <= 0){
			mexPrintf("bmi5_mmap: could not open fifo: %s\n",BMI5_OUT_FIFO); 
		}else{
			read(pipe_out, (void*)&ret, sizeof(int)); 
			close(pipe_out); 
		}
	// OUTGOING DATA!
		doMmap(oa, b, false, nfields, out); 
		free(out); 
	}else{
		mexPrintf("bmi5_mmap: please supply the b5 structure as an argument.\n"); 
	}
	if(nlhs == 1){
		if(oa)
			plhs[0] = oa; 
		else {
			mexPrintf("bmi5_mmap: need b5 as an input argument if you want an output.\n"); 
			plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
    		double* outMatrix = mxGetPr(plhs[0]);
			outMatrix[0] = (double)ret; 
		}
	}
}

