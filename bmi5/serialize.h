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
	virtual void	clear(){ fprintf(stderr, "clear must be implemented in derived classes.\n"); }
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
	virtual string getMmapInfo(){
		std::stringstream oss;
		size_t dims[2]; 
		for(int indx = 0; indx < numStores(); indx++){
			getStoreDims(indx, dims); 
			string stor = storeName(indx); 
			oss << "\t'double' [" << dims[0] << " " << dims[1] << "] '" << stor << "';...\n"; 
			//printf("\t'double' [%ld %ld] '%s';...\n", dims[0], dims[1], stor.c_str()); 
		}
		return oss.str(); 
	}
}; 

class TimeSyncClient; 
extern TimeSyncClient* g_tsc; 
extern int g_frame; 
extern long double gettime(); 

//this class records the time when matlab sends commands.
class TimeSerialize : public Serialize {
public:
	vector<double> v_time; 
	vector<double> v_ticks; 
	vector<int> v_frame; 
	
	TimeSerialize(){}
	~TimeSerialize(){ clear(); }
	virtual void store(){
		double time = gettime(); 
		double ticks = g_tsc->getTicks(); 
		v_time.push_back(time); 
		v_ticks.push_back(ticks); 
		v_frame.push_back(g_frame); 
	}
	virtual void clear(){
		v_time.clear(); 
		v_ticks.clear(); 
		v_frame.clear(); 
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
		std::cout << "getStore called, " << m_name << " size " << nstored() << std::endl; 
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

// this class records the time when a frame was displayed 
// (minus any buffering in the projector/display)
class FrameSerialize : public TimeSerialize {
public:
	double m_time; 
	double m_ticks; 
	int m_frame; 
	
	FrameSerialize() : TimeSerialize() {
		m_name = {"frame_"}; 
	}
	~FrameSerialize(){ clear(); }
	// you must call store() within the opengl display thread.
	virtual void store(){} //dummy.
	virtual void store(int frame){
		m_time = gettime(); 
		m_ticks = g_tsc->getTicks(); 
		m_frame = frame; 
		v_time.push_back(m_time); 
		v_ticks.push_back(m_ticks); 
		v_frame.push_back(m_frame); 
	}
	virtual void* mmapRead(void* addr){
		//this is a write, and returns the time & ticks of the last recorded frame.
		double * d = (double*)addr; 
		*d++ = m_time; 
		*d++ = m_ticks; 
		*d++ = m_frame; 
		return (void*)d; 
	}
};

// this one's a bit different, 
// since the polhemus thread runs *asynchronously* from the display thread.
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
	~PolhemusSerialize(){ clear(); }
	void store(float* data){
		double time = gettime(); 
		//update the velocity.
		double vv[3]; 
		for(int i=0; i<3; i++){
			double v = (data[i] - m_sensors[i]) / (time - m_time); 
			vv[i] = 0.8*m_vel[i] + 0.2*v; // in mm/sec, slightly smoothed.
			// smoothing should be ok given source b/w & sampling rate. 
		}
		m_time = time; 
		m_ticks = g_tsc->getTicks(); 
		v_time.push_back(m_time); 
		v_ticks.push_back(m_ticks); 
		for(int i=0; i<3; i++)
			m_sensors[i] = data[i]; 
		for(int i=0; i<3; i++)
			m_vel[i]  = vv[i];
		v_sensors.push_back(m_sensors); 
	}
	virtual void clear(){
		v_sensors.clear(); 
		v_time.clear(); 
		v_ticks.clear(); 
	}
	void getLoc(double now, float* out){
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
		float out[3]; 
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

class ToneSerialize : public Serialize {
	vector<double> v_time; 
	vector<double> v_ticks; 
	vector<float> v_freq; 
	vector<float> v_pan; 
	vector<float> v_scale; 
	vector<float> v_duration; 
public:
	ToneSerialize(){
		m_name = "tone_"; 
	}
	~ToneSerialize(){
	}
	virtual void store(){} //done in mmapread().
	virtual void clear(){
		v_time.clear(); 
		v_ticks.clear();
		v_freq.clear(); 
		v_pan.clear();
		v_scale.clear(); 
		v_duration.clear(); 
	}
	virtual int nstored(){return v_time.size();}
	virtual string storeName(int indx){
		switch(indx){
			case 0: return m_name + string("time");
			case 1: return m_name + string("ticks"); 
			case 2: return m_name + string("freq"); 
			case 3: return m_name + string("pan"); 
			case 4: return m_name + string("scale"); 
			case 5: return m_name + string("duration"); 
		} return string("none"); 
	}
	virtual int getStoreClass(int indx){
		switch(indx){
			case 0: return MAT_C_DOUBLE;
			case 1: return MAT_C_DOUBLE;
			case 2: return MAT_C_SINGLE;
			case 3: return MAT_C_SINGLE; 
			case 4: return MAT_C_SINGLE; 
			case 5: return MAT_C_SINGLE; 
		} return 0; 
	}
	virtual void getStoreDims(int , size_t* dims){
		dims[0] = dims[1] = 1; 
	}
	virtual void* getStore(int indx, int i){
		switch(indx){
			case 0: return (void*)&(v_time[i]);
			case 1: return (void*)&(v_ticks[i]); 
			case 2: return (void*)&(v_freq[i]); 
			case 3: return (void*)&(v_pan[i]); 
			case 4: return (void*)&(v_scale[i]); 
			case 5: return (void*)&(v_duration[i]); 
		} return NULL; 
	}
	virtual int numStores(){return 6;}
	virtual void* mmapRead(void* addr){
		//this is a one-way communication channel from matlab. 
		double* d = (double*)addr; 
		d += 2; //skip ticks and time -- these are only saved in the file.
		if(d[0] > 0.0){
			float freq = d[0]; 
			float pan = d[1]; 
			float scale = d[2]; 
			float duration = d[3]; 
			jackAddToneP(freq, pan, scale, duration); 
			double time = gettime();
			v_time.push_back(time); 
			v_ticks.push_back(g_tsc->getTicks()); 
			v_freq.push_back(freq); 
			v_pan.push_back(pan); 
			v_scale.push_back(scale); 
			v_duration.push_back(duration); 
			d[0] = 0.0; 
		}
		d += 4; 
		return (void*)d; 
	}
};

//this class is for recording arbitrary numbers, in the form of a vector, 
//from matlab.  Can be used for e.g. trial#, trial type, your mommas number ... 
template <class T> 
class VectorSerialize : public Serialize {
public:
	int	m_size; 
	int	m_type; 
	vector<T> m_stor; 
	vector<vector<T> > v_stor; 
	
	VectorSerialize(int size, int matiotype){
		m_size = size; 
		m_type = matiotype; 
	}
	~VectorSerialize(){ clear(); }
	virtual void store(){
		v_stor.push_back(m_stor); 
	}
	virtual void clear(){
		v_stor.clear(); 
	}
	virtual int nstored(){ return v_stor.size(); }
	virtual string storeName(int ){ return m_name; }
	virtual int getStoreClass(int ){ return m_type; }
	virtual void getStoreDims(int, size_t* dims){
		dims[0] = m_size; dims[1] = 1; return;
	}
	virtual void* getStore(int , int i){
		return (void*)&(v_stor[i]); 
	}
	virtual int numStores(){ return 1; }
	virtual void* mmapRead(void* addr){
		double* d = (double*)addr; 
		for(int i=0; i<m_size; i++){
			m_stor[i] = (T)(*d++); // will work??
		}
		return (void*)d; 
	}
}; 

void writeMatlab(vector<Serialize*> tosave, char* filename);
size_t matlabFileSize(vector<Serialize*> tosave); 
size_t mmapFileSize(vector<Serialize*> tosave); 
#endif