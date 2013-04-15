// class for serializing (matlab format) to a file 
// & read (binary format) from a mmaped file.
#ifndef __SERIALIZE_H__
#define __SERIALIZE_H__
#include <string>
#include <vector>
#include <array>
#include <gsl/gsl_fit.h>

using namespace std; 
class Serialize{
public:
	string	m_name; 
	int		m_lastBackup; //index+1 of last record saved to backup.
	Serialize(){}
	virtual ~Serialize(){
		m_lastBackup = 0; 
	}
	void perr(const char* method){
		fprintf(stderr, "\"%s\":%s must be implemented in derived classes.\n", 
			m_name.c_str(), method); }
	virtual bool 	store(){ perr("store"); return false; }
	virtual void	clear(){ perr("clear"); }
	virtual int 	nstored(){return 0;} //number of timeslices. 
	virtual string storeName(int ){ perr("storeName"); return string("none"); }
	virtual int 	getStoreClass(int ){ perr("getStoreClass"); return 0; }
	virtual void	getStoreDims(int , size_t* dims){perr("getStoreDims"); dims[0] = 0; dims[1] = 0;}
	virtual void*	getStore(int , int){ perr("getStore"); return NULL; }
	virtual int 	numStores(){ perr("numStores"); return 0; }
	virtual double* 	mmapRead(double* ){ perr("mmapRead"); return NULL;}
		//drawing routines -- opengl -- not all need implement.
	virtual void	draw(int, float) {}
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
		}
		return oss.str(); 
	}
	virtual string getStructInfo(){
		std::stringstream oss;
		size_t dims[2]; 
		for(int indx = 0; indx < numStores(); indx++){
			getStoreDims(indx, dims); 
			string stor = storeName(indx); 
			oss << "b5." << stor << " = zeros(" << dims[0] << "," << dims[1] << ");\n"; 
		}
		return oss.str(); 
	}
}; 

class TimeSyncClient; 
extern TimeSyncClient* g_tsc; 
extern int g_frame; 
extern long double gettime(); 
extern float g_mousePos[2]; 

//this class records and reports the time when matlab sends commands.
class TimeSerialize : public Serialize {
public:
	vector<double> v_time; 
	vector<double> v_ticks; 
	vector<int> v_frame; 
	
	TimeSerialize() : Serialize() {}
	~TimeSerialize(){ clear(); }
	virtual bool store(){
		double time = gettime(); 
		double ticks = g_tsc->getTicks(); 
		v_time.push_back(time); 
		v_ticks.push_back(ticks); 
		v_frame.push_back(g_frame); 
		return true; //stored!
	}
	virtual void clear(){
		v_time.clear(); 
		v_ticks.clear(); 
		v_frame.clear(); 
	}
	virtual int nstored(){return v_time.size(); }
	virtual string storeName(int indx){
		switch(indx){
			case 0: return m_name + string("time_o"); 
			case 1: return m_name + string("ticks_o"); 
			case 2: return m_name + string("frame_o"); 
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
	virtual double* mmapRead(double* d){
		//this is actually a write (all variables output) 
		double time = gettime(); 
		double ticks = g_tsc->getTicks(); 
		*d++ = time; 
		*d++ = ticks; 
		*d++ = (double)g_frame; 
		return d; 
	}
};

// this class records and reports the time when a frame was displayed 
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
	virtual bool store(){return false;} //dummy.
	virtual bool store(int frame){
		m_time = gettime(); 
		m_ticks = g_tsc->getTicks(); 
		m_frame = frame; 
		v_time.push_back(m_time); 
		v_ticks.push_back(m_ticks); 
		v_frame.push_back(m_frame); 
		return true; 
	}
	virtual double* mmapRead(double* d){
		//this is a write, and returns the time & ticks of the last recorded frame.
		*d++ = m_time; 
		*d++ = m_ticks; 
		*d++ = m_frame; 
		return d; 
	}
};

class PolhemusPredict {
public:
	float			m_s[8][3]; 	//last 8 sensor measurements. 
	double		m_tfit[8];  //used in linear fit.
	double		m_sfit[8]; 
	double		m_fit[3][2]; //[0] = offset, [1] = estimate of velocity, native sensor units/sec. 
	long double 	m_t[32]; 	//time of the last 32 measurements (rate should be static!)
	long double		m_avg; //smoothed time of the last incoming sample.
	int			m_ptr; 		//circluar, obvi.
	int			m_nsmooth; //over how many samples to average; max 8;
	
	PolhemusPredict(){
		for(int i=0; i<24; i++)
			m_s[0][i] = 0.f; 
		for(int i=0; i<32; i++)
			m_t[i] = 0.0; 
		for(int i=0; i<6; i++)
			m_fit[0][i] = 0.0; 
		m_ptr = 0; 
		m_nsmooth = 6; 
	}
	~PolhemusPredict(){}
	void add(long double time, float* s){
		m_t[m_ptr & 31] = time; 
		for(int i=0; i<3; i++)
			m_s[m_ptr & 7][i] = s[i]; 
		m_ptr++; 
		update(); 
	}
	void update(){
		//update the linear model used to predict position. 
		//critical assumptions: stream is actually sampled at a constant rate, 
		//even if it does not come in at a constant rate. 
		//also, this should be called in add() thread to prevent m_ptr contention.
		int n = m_ptr; 
		long double mean = m_t[(n-1)&31] - m_t[n&31];
		mean /= 31; //mean period.
		//calculate the time of the most recent sample (n-1) in terms of last 32 samples.
		long double avg = 0; 
		for(int i=0; i<32; i++)
			avg += m_t[(n-1-i)&31] + mean*i; 
		m_avg = avg / 32; 
		//fit a line to the last 8 samples.
		for(int j=0; j<m_nsmooth; j++)
			m_tfit[j] = -1.0*mean*j; //relative to the most recent sample (avg). 
		double cov00, cov01, cov11, sumsq; //ignore.
		for(int i=0; i<3; i++){
			for(int j=0; j<m_nsmooth; j++)
				m_sfit[j] = m_s[(n-1-j)&7][i]; //relative to the most recent sample (avg). 
			gsl_fit_linear(m_tfit, 1, m_sfit, 1, m_nsmooth, &(m_fit[i][0]), &(m_fit[i][1]),
								&cov00, &cov01, &cov11, &sumsq);
		}
	}
	void predict(long double time, float* s){
		time -= m_avg; 
		for(int i=0; i<3; i++){
			s[i] = m_fit[i][0] + m_fit[i][1] * time; 
		}
	}
	void test(){
		float x[3]; 
		for(int i=0; i<64; i++){
			x[0] = x[1] = x[2] = (float)i;
			add((long double)i / 2.5, x); 
		}
		for(int i=0; i<32; i++){
			x[0] = x[1] = x[2] = (float)(i+64);
			add((long double)(i+64) / 2.5, x); 
		}
		predict(96.0/2.5, x); 
		printf("PolhemusPredict::test() should be 96, is %f\n", x[0]); 
	}
};


class ToneSerialize : public Serialize {
	vector<double> v_time; 
	vector<float> v_freq; 
	vector<float> v_pan; 
	vector<float> v_scale; 
	vector<float> v_duration;
	vector<char> v_play; 
public:
	double m_time; 
	ToneSerialize() : Serialize() {
		m_name = "tone_"; 
	}
	~ToneSerialize(){
	}
	virtual bool store(){return false;} //done in mmapread().
	virtual void clear(){
		v_time.clear(); 
		v_freq.clear(); 
		v_pan.clear();
		v_scale.clear(); 
		v_duration.clear(); 
		v_play.clear();
	}
	virtual int nstored(){return v_time.size();}
	virtual string storeName(int indx){
		switch(indx){
			case 0: return m_name + string("time_o"); // these are not output--
			case 1: return m_name + string("freq");
			case 2: return m_name + string("pan"); 
			case 3: return m_name + string("scale"); 
			case 4: return m_name + string("duration");
			case 5: return m_name + string("play_io"); // bidirectional.
		} return string("none");
	}
	virtual int getStoreClass(int indx){
		switch(indx){
			case 0: return MAT_C_DOUBLE;
			case 1: return MAT_C_SINGLE;
			case 2: return MAT_C_SINGLE; 
			case 3: return MAT_C_SINGLE; 
			case 4: return MAT_C_SINGLE;
			case 5: return MAT_C_INT8;
		} return 0; 
	}
	virtual void getStoreDims(int , size_t* dims){
		dims[0] = dims[1] = 1; 
	}
	virtual void* getStore(int indx, int i){
		switch(indx){
			case 0: return (void*)&(v_time[i]);
			case 1: return (void*)&(v_freq[i]); 
			case 2: return (void*)&(v_pan[i]); 
			case 3: return (void*)&(v_scale[i]); 
			case 4: return (void*)&(v_duration[i]); 
			case 5: return (void*)&(v_play[i]);
		} return NULL; 
	}
	virtual int numStores(){return 6;}
	virtual double* mmapRead(double* d){
		float freq = d[1]; 
		float pan = d[2]; 
		float scale = d[3]; 
		float duration = d[4];
		if (d[5] > 0) {
			#ifdef JACK
			jackAddToneP(freq, pan, scale, duration);
			#endif
			m_time  = gettime();
			v_time.push_back(m_time); 
			v_freq.push_back(freq); 
			v_pan.push_back(pan); 
			v_scale.push_back(scale); 
			v_duration.push_back(duration);
			v_play.push_back((float)d[5]);
			d[0] = m_time;	// { xxx this isnt working!
			d[5] = 0.0;		// reset play
		}
		d += 6; 
		return d; 
	}
};

//this class is for recording arbitrary numbers, in the form of a vector, 
//from matlab.  Can be used for e.g. trial#, trial type, your mommas number ... 
// ... pager number, of course. 
template <class T> 
class VectorSerialize : public Serialize {
public:
	int	m_size; 
	int	m_type; 
	double				m_time; 
	vector<T> 			m_stor; 
	vector<double>		v_time; 
	vector<vector<T> > v_stor; 
	T*		m_bs; 
	
	VectorSerialize(int size, int matiotype) : Serialize(){
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
	virtual bool store(){
		bool same = true; //delta compression.
		int n = nstored(); 
		if(n > 0){
			for(int i=0; i<m_size; i++)
				same &= (m_stor[i] == v_stor[n-1][i]); 
		} else same = false; 
		if(!same){
			m_time = gettime(); 
			v_time.push_back(m_time); 
			v_stor.push_back(m_stor); 
		}
		return !same; 
	}
	virtual void clear(){
		v_time.clear(); 
		v_stor.clear(); 
	}
	virtual int nstored(){ return v_stor.size(); }
	virtual string storeName(int indx){ 
		switch(indx){
			case 0: return m_name + string("time_o"); 
			case 1: return m_name + string("v"); 
		} return string("none"); 
	}
	virtual int getStoreClass(int indx){ 
		switch(indx){
			case 0: return MAT_C_DOUBLE; 
			case 1: return m_type; 
		} return 0; 
	}
	virtual void getStoreDims(int indx, size_t* dims){
		switch(indx){
			case 0: dims[0] = 1; dims[1] = 1; return; 
			case 1: dims[0] = m_size; dims[1] = 1; return;
		}
	}
	virtual void* getStore(int indx, int k){
		//coalesce the memory -- <vector<vector>> is non-continuous in memory. 
		if(indx == 0){
			return (void*)&(v_time[k]); 
		} else if(indx == 1){
			if(m_bs) free(m_bs); 
			int n = nstored(); //atomic -- if we're not careful, may change during read!
			m_bs = (T*)malloc(sizeof(T)*(n-k)*m_size); 
			for(int i=0; i<n-k; i++){
				for(int j=0; j<m_size; j++){
					m_bs[j + i*m_size] = v_stor[i+k][j]; 
				}
			}
			return (void*)(m_bs); 
		} else return NULL;
	}
	virtual int numStores(){ return 2; }
	virtual double* mmapRead(double* d){
		*d++ = m_time; //when the vector was updated.
		for(int i=0; i<m_size; i++){
			m_stor[i] = (T)(*d++); 
		}
		return d; 
	}
}; 

//same as VectorSerialize, except two variables -- position and velocity e.g.
//yea, copypasta.  sorry.
template <class T> 
class VectorSerialize2 : public Serialize {
public:
	int	m_size; 
	int	m_type; 
	double				m_time; 
	vector<T> 			m_stor;
	vector<T> 			m_stor2; 
	vector<double>		v_time; 
	vector<vector<T> > v_stor;
	vector<vector<T> > v_stor2; 
	T*		m_bs; 

	VectorSerialize2(int size, int matiotype) : Serialize(){
		m_size = size; 
		m_type = matiotype; 
		for(int i=0; i<size; i++){
			m_stor.push_back((T)0);
			m_stor2.push_back((T)0); 
		}
		m_bs = NULL;
	}
	~VectorSerialize2(){ 
		clear(); 
		free(m_bs);
	}
	virtual bool store(){
		bool same = true; //delta compression.
		int n = nstored(); 
		if(n > 0){
			for(int i=0; i<m_size; i++){ 
				same &= (m_stor[i] == v_stor[n-1][i]);
				same &= (m_stor2[i] == v_stor2[n-1][i]); 
			}
		} else same = false; 
		if(!same){
			m_time = gettime(); 
			v_time.push_back(m_time); 
			v_stor.push_back(m_stor);
			v_stor2.push_back(m_stor2); 
		}
		return !same; 
	}
	virtual void clear(){
		v_time.clear(); 
		v_stor.clear();
		v_stor2.clear(); 
	}
	virtual int nstored(){ return v_stor.size(); }
	virtual string storeName(int indx){ 
		switch(indx){
			case 0: return m_name + string("time_o"); 
			case 1: return m_name + string("v");
			case 2: return m_name + string("v2"); 
		} return string("none"); 
	}
	virtual int getStoreClass(int indx){ 
		switch(indx){
			case 0: return MAT_C_DOUBLE; 
			case 1: case 2: return m_type;
		} return 0; 
	}
	virtual void getStoreDims(int indx, size_t* dims){
		switch(indx){
			case 0: dims[0] = 1; dims[1] = 1; return; 
			case 1: case 2: dims[0] = m_size; dims[1] = 1; return;
		}
	}
	virtual void* getStore(int indx, int k){
		//coalesce the memory -- <vector<vector>> is non-continuous in memory. 
		if(indx == 0){
			return (void*)&(v_time[k]); 
		} else if(indx == 1 || indx == 2){
			if(m_bs) free(m_bs); 
			int n = nstored(); //atomic -- if we're not careful, may change during read!
			m_bs = (T*)malloc(sizeof(T)*(n-k)*m_size); 
			for(int i=0; i<n-k; i++){
				if(indx == 1){
					for(int j=0; j<m_size; j++)
						m_bs[j + i*m_size] = v_stor[i+k][j]; 
				}else{
					for(int j=0; j<m_size; j++)
						m_bs[j + i*m_size] = v_stor2[i+k][j]; 
				}
				
			}
			return (void*)(m_bs); 
		} else return NULL;
	}
	virtual int numStores(){ return 3; }
	virtual double* mmapRead(double* d){
		*d++ = m_time; //when the vector was updated.
		for(int i=0; i<m_size; i++){
			m_stor[i] = (T)(*d++); 
		}
		for(int i=0; i<m_size; i++){
			m_stor2[i] = (T)(*d++); 
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
	vector<double>		m_last; // note double.
	vector<float>		m_stor; 
	vector<double> 	v_time; 
	vector<vector<float> > v_stor;
	float*				m_bs; // for coalescing memory
	
	TdtUdpSerialize(int sock, int size) : Serialize(){
		//the sock should be created elsewhere -- so we can get error strings out.
		m_sock = sock;
		m_size = size; 
		for(int i=0; i<size; i++){
			m_stor.push_back(0.f); 
			m_last.push_back(0.0); 
		}
		m_bs = 0;
		m_name = "tdtudp_";
	}
	~TdtUdpSerialize(){
		disconnectRZ(m_sock); 
		clear(); 
		if(m_bs) free(m_bs); 
	}
	virtual bool store(){ return false; } //do it in mmapRead()
	virtual void clear(){
		v_time.clear(); 
		v_stor.clear();
	}
	virtual int nstored(){ return v_stor.size(); }
	virtual string storeName(int indx){
		switch(indx){
			case 0: return m_name + string("time"); //only saved in file.
			case 1: return m_name + string("udp");
		} return string{"none"};
	}
	virtual int getStoreClass(int indx){
		switch(indx){
			case 0: return MAT_C_DOUBLE; 
			case 1: return MAT_C_SINGLE;
		} return 0; 
	}
	virtual void getStoreDims(int indx, size_t* dims){
		switch(indx){
			case 0: dims[0] = dims[1] = 1; return; 
			case 1: dims[0] = m_size; dims[1] = 1; return;
		}
	}
	virtual void* getStore(int indx, int k){
		switch(indx) {
			case 0: return (void*)&(v_time[k]);
			case 1: {
					//coalesce the memory: <vector<vector>> is not contiguous. 
					if(m_bs) free(m_bs); 
					int n = nstored(); 
					m_bs = (float*)malloc(sizeof(float)*(n-k)*m_size); 
					for(int i=0; i<n-k; i++) {
						for(int j=0; j<m_size; j++) {
							m_bs[j + i*m_size] = v_stor[i+k][j]; 
						}
					}
					return (void*)(m_bs); }
		} return NULL;
	}
	virtual int numStores(){return 2;}
	virtual double* mmapRead(double* d){
		d += 1; //skip time -- this is only saved in the file.
		bool sames = true; 
		for(int i=0; i<m_size; i++)
			sames &= m_last[i] == d[i]; 
		if(!sames){
			for (int i=0; i<m_size; i++) {
				m_last[i] = d[i]; 
				m_stor[i] = (float)d[i];
			}
			sendDataRZ(m_sock, &(m_stor[0]), m_size); //thread-synchronous is ok?
			double time = gettime(); //save the time of TX.
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
	array<double,16>			m_cmp;
	array<float,16>				m_x; 
	vector<array<float,16> >	v_x; 
	
	Matrix44Serialize(string name) : Serialize(){
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
	virtual bool store(){ return false; /* in mmap. */}
	virtual int nstored(){return v_x.size(); }
	virtual string storeName(int ){ return m_name + string("_m44"); }
	virtual int getStoreClass(int ){ return MAT_C_SINGLE; }
	virtual void getStoreDims(int, size_t* dims){
		dims[0] = 4; dims[1] = 4; return; 
	}
	virtual void* getStore(int , int k){
		return (void*)&(v_x[k]); 
	}
	virtual int numStores(){return 1;}
	virtual double* mmapRead(double* d){
		//don't store the time here, as an incentive to not change it during the exp! 
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
// this one's a bit different, 
// since the polhemus thread runs *asynchronously* from the display thread.
// ideally we want to keep an estimate of velocity, and forward-project position
// to prevent temporal noise from coupling into spatial noise. 
class PolhemusSerialize : public Serialize {
public: 
	PolhemusPredict*	m_pp; 
	double				m_time;
	array<float,3>		m_sensors; //these here for copying to mmap.
	array<float,3>		m_vel; 
	vector<double>		v_time; 
	vector<array<float,3>> v_sensors;
	vector<array<float,3>> v_vel; 
	
	PolhemusSerialize() : Serialize() {
		m_name = "polhemus_"; 
		m_sensors[0] = m_sensors[1] = m_sensors[2] = 0.0;
		m_vel[0] = m_vel[1] = m_vel[2] = 0.0; 
		m_time = 0; 
		m_pp = new PolhemusPredict(); 
	}
	~PolhemusSerialize(){ clear(); delete m_pp;}
	bool store(float* data){ //called after serial data reception; always store.
		double time = gettime(); 
		m_pp->add(time, data); 
		m_time = time; 
		v_time.push_back(m_time); 
		update(data); //copies into member variables.
		v_sensors.push_back(m_sensors); 
		v_vel.push_back(m_vel); 
		return true;
	}
	void update(float* data){ //used for status, etc -- does not store anything in the vectors.
		for(int i=0; i<3; i++)
			m_sensors[i] = data[i]; 
		m_pp->add(gettime(), data); 
		for(int i=0; i<3; i++) //copy the velocity.
			m_vel[i] = m_pp->m_fit[i][1]; 
	}
	void getLoc(double now, float* out){
		m_pp->predict(now, out); 
	}
	virtual void clear(){
		v_sensors.clear(); 
		v_vel.clear(); 
		v_time.clear(); 
	}
	virtual bool store(){
		//printf("error: you must call store(float*)\n"); 
		return false;
	}
	virtual int nstored(){return v_sensors.size();}
	virtual string storeName(int indx){
		switch(indx){
			case 0: return m_name + string("time_o"); 
			case 1: return m_name + string("sensors_o");
			case 2: return m_name + string("sensorvel_o"); 
		} return string{"none"};
	}
	virtual int getStoreClass(int indx){
		switch(indx){
			case 0: return MAT_C_DOUBLE; 
			case 1: return MAT_C_SINGLE;
			case 2: return MAT_C_SINGLE; 
		} return 0; 
	}
	virtual void getStoreDims(int indx, size_t* dims){
		switch(indx){
			case 0: dims[0] = 1; dims[1] = 1; return; 
			case 1: dims[0] = 3; dims[1] = 1; return; 
			case 2: dims[0] = 3; dims[1] = 1; return; 
		}
	}
	virtual void* getStore(int indx, int i){
		switch(indx){
			case 0: return (void*)&(v_time[i]); 
			case 1: return (void*)&(v_sensors[i]);
			case 2: return (void*)&(v_vel[i]); 
		} return NULL; 
	}
	virtual int numStores(){return 3;}
	virtual double* mmapRead(double* d){
		float out[3]; 
		double time = gettime(); 
		*d++ = time; 
		getLoc(time, out); // this will change on every update, so no delta compression.
		for(int i=0; i<3; i++)
			*d++ = out[i]; 
		for(int i=0; i<3; i++)
			*d++ = m_vel[i]; // n.b: not interpolated. 
 		return d; 
	}
}; 

class OptoSerialize : public VectorSerialize2<float> {
public:
	int m_nsensors; //number of sensors. 
	vector<PolhemusPredict*> m_pp; 
	
	OptoSerialize(int nsensors) : VectorSerialize2(nsensors * 3, MAT_C_SINGLE){
		m_name = "optotrak_";
		m_nsensors = nsensors; 
		for(int i=0; i<m_nsensors; i++){
			m_pp.push_back(new PolhemusPredict()); 
		}
	}
	~OptoSerialize(){
		clear(); 
		for(int i=0; i<m_nsensors; i++){
			delete m_pp[i]; 
		}
		m_pp.clear(); 
	}
	virtual bool store(){ return false; } //override -- called below.
	bool store(float* data){
		//assumes there is m_nsensors * 3 floats in *data. 
		m_time = gettime(); 
		for(int i=0; i<m_nsensors; i++){
			m_pp[i]->add(m_time, &(data[i*3])); 
		}
		for(int i=0; i<m_nsensors*3; i++){
			m_stor[i] = data[i]; 
		}
		for(int i=0; i<m_nsensors; i++){
			for(int j=0; j<3; j++)
				m_stor2[i*3+j] = m_pp[i]->m_fit[j][1]; //vel. 
		}
		VectorSerialize2::store(); 
		return true; 
	}
	void getLoc(double now, float* out){
		for(int i=0; i<m_nsensors; i++){
			m_pp[i]->predict(now, &(out[i*3])); 
		}
	}
	virtual string storeName(int indx){
		switch(indx){
			case 0: return m_name + string("time_o"); 
			case 1: return m_name + string("sensors_o"); //default is input; override.
			case 2: return m_name + string("sensorvel_o"); //default is input; override.
		} return string("none"); 
	}
	virtual double* mmapRead(double* d){
		*d++ = m_time; //last time the sensors were read. 
		getLoc(gettime(), m_stor.data()); //sample position now.
		for(int i=0; i<3*m_nsensors; i++){
			*d++ = m_stor[i]; //float->double.
		}
		for(int i=0; i<m_nsensors; i++){
			for(int j=0; j<3; j++)
				*d++ = m_pp[i]->m_fit[j][1]; 
		}
 		return d; 
	}
}; 

class MouseSerialize : public VectorSerialize<float> {
public:
	//timing via VectorSerialize.
	MouseSerialize() : VectorSerialize(3, MAT_C_SINGLE){
		m_name = "mouse_";
	}
	~MouseSerialize(){}
	virtual bool store(){
		m_stor[0] = g_mousePos[0]; 
		m_stor[1] = g_mousePos[1];
		m_stor[2] = 0.f;
		return VectorSerialize::store(); 
	}
	virtual string storeName(int ){ return m_name + string("sensors_o"); } //output.
	virtual double* mmapRead(double* d){
		*d++ = g_mousePos[0];
		*d++ = g_mousePos[1];
		*d++ = 0.f; 
		return d; 
	}
};


void writeMatlab(vector<Serialize*> tosave, char* filename, bool backup);
size_t matlabFileSize(vector<Serialize*> tosave); 
size_t mmapFileSize(vector<Serialize*> tosave); 
bool matlabHasNewData(vector<Serialize*> tosave); 
#endif

