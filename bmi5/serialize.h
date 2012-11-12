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
	virtual int 	nstored(){return 0;} //number of timeslices. 
	virtual string storeName(int ){ return string("none"); }
	virtual int 	getStoreClass(int ){ return 0; }
	virtual void	getStoreDims(int , size_t* dims){dims[0] = 0; dims[1] = 0;}
	virtual void*	getStore(int , int){ return NULL; }
	virtual int 	numStores(){ return 0; }
	virtual void* 	mmapRead(void* ){ return NULL;}
		//drawing routines -- opengl.
	virtual void	draw(int) {}
	virtual void	move(float, long double){}
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

// this one's a bit different, 
// since the polhemus thread runs asynchronously from the display thread.
// ideally we want to keep an estimate of velocity, and forward-project position
// to prevent temporal noise from coupling into spatial noise. 
class PolhemusSerialize : public Serialize {
public: 
	array<float,3>	m_sensors; //these here for copying to mmap.
	double			m_time;
	double			m_ticks; 
	array<double,3> m_vel; 
	vector<array<float,3>> v_sensors; 
	vector<double>	v_time; 
	vector<double> v_ticks; 
	
	PolhemusSerialize(){
		m_name = "polhemus_"; 
		m_sensors[0] = m_sensors[1] = m_sensors[2] = 0.0; 
		m_vel[0] = m_vel[1] = m_vel[2] = 0.0; 
		m_time = 0; 
		m_ticks = 0; 
	}
	~PolhemusSerialize(){
		v_sensors.clear(); 
		v_time.clear(); 
		v_ticks.clear(); 
	}
	void store(float* data){
		double time = gettime(); 
		//update the velocity.
		for(int i=0; i<3; i++){
			double v = (data[i] - m_sensors[i]) / (time - m_time); 
			m_vel[i] = 0.8*m_vel[i] + 0.2*v; // in mm/sec, slightly smoothed.
			// smoothing should be ok given source b/w & sampling rate. 
		}
		m_time = time; 
		m_ticks = g_tsc->getTicks(); 
		v_time.push_back(m_time); 
		v_ticks.push_back(m_ticks); 
		for(int i=0; i<3; i++)
			m_sensors[i] = data[i]; 
		v_sensors.push_back(m_sensors); 
	}
	void getLoc(double now, array<float,3> out){
		//gets the current location, with forward estimation. 
		//the update operations to the relevant variables (m_sensors, m_vel)
		//are non-atomic, but a mutex here seems like a bit much. 
		double dt = now - m_time; 
		for(int i=0; i<3; i++)
			out[i] = m_sensors[i] + m_vel[i] * dt; 
	}
	virtual void store(){
		//printf("error: you must call store(float*)\n"); 
	}
	virtual int nstored(){return v_sensors.size();}
	virtual string storeName(int indx){
		switch(indx){
			case 0: return m_name + string("sensors"); 
			case 1: return m_name + string("time"); 
			case 2: return m_name + string("ticks"); 
		} return string{"none"};
	}
	virtual int getStoreClass(int indx){
		switch(indx){
			case 0: return MAT_C_SINGLE; 
			case 1: return MAT_C_DOUBLE; 
			case 2: return MAT_C_DOUBLE; 
		} return 0; 
	}
	virtual void getStoreDims(int indx, size_t* dims){
		switch(indx){
			case 0: dims[0] = 3; dims[1] = 1; return; 
			case 1: dims[0] = 1; dims[1] = 1; return; 
			case 2: dims[0] = 1; dims[1] = 1; return; 
		}
	}
	virtual void* getStore(int indx, int i){
		switch(indx){
			case 0: return (void*)&(v_sensors[i]); 
			case 1: return (void*)&(v_time[i]); 
			case 2: return (void*)&(v_ticks[i]); 
		} return NULL; 
	}
	virtual int numStores(){return 3;}
	virtual void* mmapRead(void* addr){
		double* d = (double*)addr; 
		array<float,3> out; 
		double time = gettime(); 
		getLoc(time, out); 
		for(int i=0; i<3; i++){
			*d++ = out[i]; 
		}
		*d++ = time; //redundant, but keeps things consistent.
		*d++ = g_tsc->getTicks(); 
 		return (void*)d; 
	}
}; 

void writeMatlab(vector<Serialize*> tosave, char* filename);
size_t matlabFileSize(vector<Serialize*> tosave); 
size_t mmapFileSize(vector<Serialize*> tosave); 
#endif