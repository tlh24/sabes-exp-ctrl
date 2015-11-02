#ifndef TONE_SERIALIZE_H
#define TONE_SERIALIZE_H

#include "serialize.h"

class ToneSerialize : public Serialize
{
	vector<double> v_time;
	vector<float> v_freq;
	vector<float> v_pan;
	vector<float> v_scale;
	vector<float> v_duration;
	vector<char> v_play;
public:
	double m_time;
	ToneSerialize();
	~ToneSerialize();
	virtual bool store();
	virtual void clear();
	virtual int nstored();
	virtual string storeName(int indx);
	virtual int getStoreClass(int indx);
	virtual void getStoreDims(int , size_t *dims);
	virtual void *getStore(int indx, int i);
	virtual int numStores();
	virtual double *mmapRead(double *d);
};

#endif
