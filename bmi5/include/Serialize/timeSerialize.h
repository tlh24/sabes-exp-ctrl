#ifndef TIME_SERIALIZE_H
#define TIME_SERIALIZE_H

#include "serialize.h"

//this class records and reports the time when matlab sends commands.
class TimeSerialize : public Serialize
{
public:
	vector<double> v_time;
	vector<double> v_ticks;
	vector<int> v_frame;

	TimeSerialize();
	~TimeSerialize();
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
