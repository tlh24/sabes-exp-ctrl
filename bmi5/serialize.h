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
	void perr(const char* method){
		fprintf(stderr, "\"%s\":%s must be implemented in derived classes.\n", 
			m_name.c_str(), method); }
	virtual void 	store(){ perr("store"); }
	virtual void	clear(){ perr("clear"); }
	virtual int 	nstored(){return 0;} //number of timeslices. 
	virtual string storeName(int ){ perr("storeName"); return string("none"); }
	virtual int 	getStoreClass(int ){ perr("getStoreClass"); return 0; }
	virtual void	getStoreDims(int , size_t* dims){perr("getStoreDims"); dims[0] = 0; dims[1] = 0;}
	virtual void*	getStore(int , int){ perr("getStore"); return NULL; }
	virtual int 	numStores(){ perr("numStores"); return 0; }
	virtual double* 	mmapRead(double* ){ perr("mmapRead"); return NULL;}
		//drawing routines -- opengl -- not all need implement.
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
	virtual double* mmapRead(double* d){
		//this is actually a write! 
		double time = gettime(); 
		double ticks = g_tsc->getTicks(); 
		*d++ = time; 
		*d++ = ticks; 
		*d++ = (double)g_frame; 
		return d; 
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
	virtual double* mmapRead(double* d){
		//this is a write, and returns the time & ticks of the last recorded frame.
		*d++ = m_time; 
		*d++ = m_ticks; 
		*d++ = m_frame; 
		return d; 
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
	virtual double* mmapRead(double* d){
		float out[3]; 
		double time = gettime(); 
		getLoc(time, out); 
		for(int i=0; i<3; i++){
			*d++ = out[i]; 
		}
		*d++ = time; //redundant, but keeps things consistent.
		*d++ = g_tsc->getTicks(); 
 		return d; 
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
	virtual double* mmapRead(double* d){
		//this is a one-way communication channel from matlab. 
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
		return d; 
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
	T*		m_bs; 
	
	VectorSerialize(int size, int matiotype){
		m_size = size; 
		m_type = matiotype; 
		for(int i=0; i<size; i++){
			m_stor.push_back((T)0); 
		}
		m_bs = NULL;
	}
	~VectorSerialize(){ 
		clear(); 
		free(m_bs); 
	}
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
	virtual void* getStore(int , int k){
		//coalesce the memory -- <vector<vector>> is non-continuous in memory. 
		if(m_bs) free(m_bs); 
		m_bs = (T*)malloc(sizeof(T)*nstored()*m_size); 
		for(int i=0; i<nstored(); i++){
			for(int j=0; j<m_size; j++){
				m_bs[j + i*m_size] = v_stor[i][j]; 
			}
		}
		return (void*)&(m_bs[k*m_size]); 
	}
	virtual int numStores(){ return 1; }
	virtual double* mmapRead(double* d){
		for(int i=0; i<m_size; i++){
			m_stor[i] = (T)(*d++); // will work??
		}
		return d; 
	}
}; 

//class for sending float data to TDT -- 
//exact protocol depends on the RCX file running on the RZ2.
//class saves timing information for when the packet was sent. 
class TdtUdpSerialize : public Serialize {
public: 
	int					m_sock; 
	int 					m_size; 
	double				m_time; 
	double				m_ticks; 
	vector<double>		m_last; 
	vector<float>		m_stor; 
	vector<double> 	v_time; 
	vector<double>		v_ticks; 
	vector<vector<float> > v_stor; 
	float*				m_bs; 
	
	TdtUdpSerialize(int sock, int size){
		//the sock should be created elsewhere -- so we can get error strings out.
		m_sock = sock;
		m_size = size; 
		for(int i=0; i<size; i++){
			m_stor.push_back(0.f); 
			m_last.push_back(0.0); 
		}
		m_bs = 0; 
	}
	~TdtUdpSerialize(){
		disconnectRZ(m_sock); 
		clear(); 
		if(m_bs) free(m_bs); 
	}
	virtual void store(){ } //do it in mmapRead()
	virtual void clear(){
		v_time.clear(); 
		v_ticks.clear(); 
		v_stor.clear(); 
	}
	virtual int nstored(){ return v_stor.size(); }
	virtual string storeName(int indx){
		switch(indx){
			case 0: return m_name + string("time"); 
			case 1: return m_name + string("ticks"); 
			case 2: return m_name + string("udp"); 
		} return string{"none"};
	}
	virtual int getStoreClass(int indx){
		switch(indx){
			case 0: return MAT_C_DOUBLE; 
			case 1: return MAT_C_DOUBLE; 
			case 2: return MAT_C_SINGLE; 
		} return 0; 
	}
	virtual void getStoreDims(int indx, size_t* dims){
		switch(indx){
			case 0: dims[0] = 1; dims[1] = 1; return; 
			case 1: dims[0] = 1; dims[1] = 1; return; 
			case 2: dims[0] = m_size; dims[1] = 1; return; 
		}
	}
	virtual void* getStore(int indx, int k){
		if(indx == 0)
			return (void*)&(v_time[k]); 
		else if(indx == 1)
			return (void*)&(v_ticks[k]); 
		else if(indx == 2){
			//coalesce the memory -- <vector<vector>> is non-continuous in memory. 
			if(m_bs) free(m_bs); 
			m_bs = (float*)malloc(sizeof(float)*nstored()*m_size); 
			for(int i=0; i<nstored(); i++){
				for(int j=0; j<m_size; j++){
					m_bs[j + i*m_size] = v_stor[i][j]; 
				}
			}
			return (void*)&(m_bs[k*m_size]); 
		} else return NULL; 
	}
	virtual int numStores(){return 3;}
	virtual double* mmapRead(double* d){
		d += 2; //skip ticks and time -- these are only saved in the file.
		bool sames = true; 
		for(int i=0; i<m_size; i++)
			sames &= m_last[i] == d[i]; 
		if(!sames){
			for(int i=0; i<m_size; i++){
				m_last[i] = d[i]; 
				m_stor[i] = (float)d[i]; 
			}
			sendDataRZ(m_sock, &(m_stor[0]), m_size); //thread-synchronous is ok?
			double time = gettime(); //save the time of TX.
			v_ticks.push_back(g_tsc->getTicks()); 
			v_time.push_back(time); 
			v_stor.push_back(m_stor); 
		}
		d += m_size; 
		return d;
	}
}; 

//convenience class for saving 4x4 calibration matrix (affine, quadratic). 
class Matrix44Serialize : public Serialize {
public: 
	array<double,16>				m_cmp;
	array<float,16>				m_x; 
	vector<array<float,16> >	v_x; 
	
	Matrix44Serialize(string name){
		m_name = name; 
		for(int i=0; i<16; i++){
			m_x[i] = 0; // Matlab ordering (column major -- same in openGL).
			m_cmp[i] = 0; }
		for(int i=0; i<4; i++){
			m_x[i+i*4] = 1.f; 
			m_cmp[i+i*4] = 1.f; }
	}
	~Matrix44Serialize(){
		clear(); 
	}
	virtual void clear(){
		v_x.clear(); 
	}
	virtual void store(){ /* in mmap. */}
	virtual int nstored(){return v_x.size(); }
	virtual string storeName(int ){ return m_name + string("_m44"); }
	virtual int getStoreClass(int ){ return MAT_C_SINGLE; }
	virtual void getStoreDims(int, size_t* dims){
		dims[0] = 4; dims[1] = 4; return; 
	}
	virtual void* getStore(int , int i){
		return (void*)&(v_x[i]); 
	}
	virtual int numStores(){return 1;}
	virtual double* mmapRead(double* d){
		//don't store the time here -- you should not be changing it during the exp!
		bool sames = true; 
		for(int i=0; i<16; i++)
			sames &= (d[i] == m_cmp[i]); 
		if(!sames){
			for(int i=0; i<16; i++) {
				m_x[i] = (float)d[i]; 
				m_cmp[i] = d[i]; 
			}
			v_x.push_back(m_x); 
		}
		d += 16; 
		return d; 
	}
	float* data(){ return m_x.data(); }; 
}; 

void writeMatlab(vector<Serialize*> tosave, char* filename);
size_t matlabFileSize(vector<Serialize*> tosave); 
size_t mmapFileSize(vector<Serialize*> tosave); 
#endif