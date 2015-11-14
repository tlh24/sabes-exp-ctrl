#ifndef TONE_SERIALIZE_H
#define TONE_SERIALIZE_H

#include "serialize.h"

class ToneSerialize : public Serialize
{
	double			m_time;
	vector<double>	v_time;
	float			m_freq;
	vector<float>	v_freq;
	float			m_pan;
	vector<float>	v_pan;
	float			m_scale;
	vector<float>	v_scale;
	float			m_duration;
	vector<float>	v_duration;
	char			m_play;
	vector<char>	v_play;
public:

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
