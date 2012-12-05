#include <stdio.h>
#include <matio.h>
#include <vector>
#include <array>
#include <iostream>
#include <math.h>
#include <string.h>
#include <string>
#include <sstream>
#include <iostream>
#include "mmaphelp.h"
#include "gettime.h"
#include "timesync.h"
#include "jacksnd.h"
#include "serialize.h"

int matlabClassToType(int cls){
	switch(cls) {
		case MAT_C_SINGLE: return MAT_T_SINGLE; 
		case MAT_C_DOUBLE: return MAT_T_DOUBLE; 
		case MAT_C_UINT8: return MAT_T_UINT8;
		case MAT_C_INT8: return MAT_T_INT8; 
		case MAT_C_INT32: return MAT_T_INT32; 
	}
	return 0; 
}
int matlabClassToBytes(int cls){
	switch(cls) {
		case MAT_C_SINGLE: return 4; 
		case MAT_C_DOUBLE: return 8; 
		case MAT_C_UINT8: return 1;
		case MAT_C_INT8: return 1; 
		case MAT_C_INT32: return 4; 
	}
	return 0; 
}
	
void writeMatlab(vector<Serialize*> tosave, char* filename){
	// warning: this function requires a *lot* of memory!!!
	const char* fieldnames[256]; 
	int nfn = 0; 
	for(unsigned int j=0; j<tosave.size(); j++){
		for(int indx=0; indx < tosave[j]->numStores(); indx++){
			string stor = tosave[j]->storeName(indx); 
			char* s = (char*)malloc(stor.size()+1); 
			strcpy(s, stor.c_str()); 
			s[stor.size()] = 0; 
			fieldnames[nfn] = s; // have to be careful to free() this!
			nfn++; 
		}
	}
	mat_t* matfp = Mat_CreateVer(filename,NULL,MAT_FT_DEFAULT);
	if ( NULL == matfp ) {
		fprintf(stderr,"Error creating MAT file \"test.mat\"\n");
		return;
	}
	size_t struct_dims[2] = {1,1}; 
	int nstored = tosave[0]->nstored(); 
	struct_dims[0] = nstored; 
	// TDT calls their things tanks, which is a reservoir of water, so we can call ours tarn.
	// tarns are much cooler than tanks.
	matvar_t *field; 
	//two ways of formatting the file. 
	if(0){
		//1. in a structure. 
		// write out in chronological order ...
		matvar_t* matvar = Mat_VarCreateStruct("tarn", 2,struct_dims,fieldnames,nfn);
		if ( NULL == matvar ) {
			fprintf(stderr,"Error creating variable for ’tarn’\n");
			Mat_Close(matfp);
			return;
		}
		size_t dims[2] = {1,1}; 
		for(int i=0; i<nstored; i++){
			for(unsigned int j=0; j<tosave.size(); j++){
				for(int indx=0; indx < tosave[j]->numStores(); indx++){
					void* f = tosave[j]->getStore(indx, i); 
					int cls = tosave[j]->getStoreClass(indx); 
					tosave[j]->getStoreDims(indx, dims); 
					int typ = matlabClassToType(cls); 
					field = Mat_VarCreate(NULL, (matio_classes)cls, (matio_types)typ, 2, dims, f, 0); 
					string s = tosave[j]->storeName(indx);
					Mat_VarSetStructFieldByName(matvar, s.c_str(), i, field);
				}
			}
		}
		//write it all out. 
		Mat_VarWrite(matfp,matvar,MAT_COMPRESSION_NONE);
		Mat_VarFree(matvar);
		Mat_Close(matfp);
	} else {
		//2. individual variables. 
		// write out individual feilds, one at a time, to save memory.
		for(unsigned int j=0; j<tosave.size(); j++){
			for(int indx=0; indx < tosave[j]->numStores(); indx++){
				void* f = tosave[j]->getStore(indx, 0); //vectors are stored in a strictly linear array.
				int cls = tosave[j]->getStoreClass(indx); 
				size_t dims[2]; 
				tosave[j]->getStoreDims(indx, dims); 
				dims[1] = tosave[j]->nstored(); 
				int typ = matlabClassToType(cls); 
				string s = tosave[j]->storeName(indx);
				field = Mat_VarCreate(s.c_str(), (matio_classes)cls, (matio_types)typ, 2, dims, f, 0); 
				Mat_VarWrite(matfp,field,MAT_COMPRESSION_NONE);
				Mat_VarFree(field);
			}
		}
		Mat_Close(matfp);
	}
	while(nfn > 0){
		nfn--; 
		free((void*)fieldnames[nfn]); 
	}
}
size_t matlabFileSize(vector<Serialize*> tosave){
	size_t n = 0; 
	for(unsigned int j=0; j<tosave.size(); j++){
		for(int indx=0; indx < tosave[j]->numStores(); indx++){
			int cls = tosave[j]->getStoreClass(indx); 
			size_t dims[2]; 
			tosave[j]->getStoreDims(indx, dims); 
			n += matlabClassToBytes(cls) * dims[0] * dims[1] * 
				tosave[j]->nstored(); 
		}
	}
	return n; 
}
size_t mmapFileSize(vector<Serialize*> tosave){
	size_t n = 0; 
	for(unsigned int j=0; j<tosave.size(); j++){
		for(int indx=0; indx < tosave[j]->numStores(); indx++){
			size_t dims[2]; 
			tosave[j]->getStoreDims(indx, dims); 
			n += 8 * dims[0]; 
		}
	}
	return n; 
}