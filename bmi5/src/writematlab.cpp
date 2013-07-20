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
#include "tdt_udp.h"
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
	
void writeMatlab(vector<Serialize*> tosave, char* filename, bool backup){
	// warning: this function requires (potentially) a *lot* of memory!!!
	mat_t* matfp = Mat_CreateVer(filename,NULL,MAT_FT_MAT73);
	if ( NULL == matfp ) {
		fprintf(stderr,"Error creating MAT file \"test.mat\"\n");
		return;
	}
	matvar_t *field; 
	//method 2 of writing files: individual variables. 
	// (method 1 depreciated)
	// write out individual feilds, one at a time, to save memory.
	for(unsigned int j=0; j<tosave.size(); j++){
		int n = tosave[j]->nstored(); 
		int k = backup ? tosave[j]->m_lastBackup : 0; 
		if(k < 0){
			printf("m_lastBackup < 0, %s\n", tosave[j]->m_name.c_str()); 
		}
		for(int indx=0; indx < tosave[j]->numStores(); indx++){
			int cls = tosave[j]->getStoreClass(indx); 
			//get dims *before* pointer for when things are still growing!
			size_t dims[2]; 
			tosave[j]->getStoreDims(indx, dims); 
			if(n > k && k >= 0){
				dims[0] *= dims[1]; //for matrices.
				dims[1] = n-k; 
				void* f = tosave[j]->getStore(indx, k); //vectors are stored in a strictly linear array.
				int typ = matlabClassToType(cls); 
				string s = tosave[j]->storeName(indx);
				size_t dims2[2]; 
				dims2[0] = dims[0]; dims2[1] = dims[1]; 
				field = Mat_VarCreate(s.c_str(), (matio_classes)cls, (matio_types)typ, 2, dims2, f, 0); 
				Mat_VarWrite(matfp,field,MAT_COMPRESSION_NONE);
				Mat_VarFree(field);
			}
		}
		if(backup) tosave[j]->m_lastBackup = n; 
	}
	Mat_Close(matfp);
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
bool matlabHasNewData(vector<Serialize*> tosave){
	for(unsigned int j=0; j<tosave.size(); j++){
		int n = tosave[j]->nstored(); 
		int k = tosave[j]->m_lastBackup; 
		if( n > k ) return true; 
	}
	return false; 
}