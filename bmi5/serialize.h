// class for serializing (matlab format) to a file 
// & read (binary format) from a mmaped file.
#ifndef __SERIALIZE_H__
#define __SERIALIZE_H__
#include <string>
#include <vector>
#include <array>

using namespace std; 
class Serialize{
public:
	string	m_name; 
	Serialize(){}
	virtual ~Serialize(){ }
	virtual void 	store(){ fprintf(stderr, "store must be implemented in derived classes.\n"); }
	virtual int 	nstored(){return 0;}
	virtual string storeName(int ){ return string("none"); }
	virtual int 	getStoreClass(int ){ return 0; }
	virtual void	getStoreDims(int , size_t* dims){dims[0] = 0; dims[1] = 0;}
	virtual void*	getStore(int , int){ return NULL; }
	virtual int 	numStores(){ return 0; }
	virtual void* 	mmapRead(void* ){ return NULL;}
		// reads/writes parameters from a mmaped file (address).
		// all mmap variables are doubles, for convenience.
	virtual void printMmapInfo(){
		size_t dims[2]; 
		for(int indx = 0; indx < numStores(); indx++){
			getStoreDims(indx, dims); 
			string stor = storeName(indx); 
			printf("\t'double' [%ld %ld] '%s';...\n", dims[0], dims[1], stor.c_str()); 
		}
	}
}; 

class TimeSyncClient; 
extern TimeSyncClient* g_tsc; 
extern int g_frame; 
extern long double gettime(); 

class TimeSerialize : public Serialize {
public:
	vector<double> v_time; 
	vector<double> v_ticks; 
	vector<int> v_frame; 
	
	TimeSerialize(){}
	~TimeSerialize(){ 
		v_time.clear(); 
		v_ticks.clear(); 
	}
	virtual void store(){
		double time = gettime(); 
		double ticks = g_tsc->getTicks(); 
		v_time.push_back(time); 
		v_ticks.push_back(ticks); 
		v_frame.push_back(g_frame); 
	}
	virtual int nstored(){return v_time.size(); }
	virtual string storeName(int indx){
		switch(indx){
			case 0: return m_name + string("time"); 
			case 1: return m_name + string("ticks"); 
			case 2: return m_name + string("frame"); 
		} return string("none"); 
	}
	virtual int getStoreClass(int indx){
		switch(indx){
			case 0: return MAT_C_DOUBLE; 
			case 1: return MAT_C_DOUBLE; 
			case 2: return MAT_C_INT32; 
		} return 0; 
	}
	virtual void getStoreDims(int , size_t* dims){
		dims[0] = 1; dims[1] = 1; 
	}
	virtual void* getStore(int indx, int i){
		switch(indx){
			case 0: return (void*)&(v_time[i]);
			case 1: return (void*)&(v_ticks[i]); 
			case 2: return (void*)&(v_frame[i]); 
		} return NULL; 
	}
	virtual int numStores(){ return 3; }
	virtual void* mmapRead(void* addr){
		//this is actually a write! 
		double * d = (double*)addr; 
		double time = gettime(); 
		double ticks = g_tsc->getTicks(); 
		*d++ = time; 
		*d++ = ticks; 
		*d++ = (double)g_frame; 
		return (void*)d; 
	}
};

void writeMatlab(vector<Serialize*> tosave);
#endif