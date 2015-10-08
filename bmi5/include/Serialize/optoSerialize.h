#ifndef OPTO_SERIALIZE_H
#define OPTO_SERIALIZE_H

#include "vectorSerialize2.h"
#include "polhemusPredict.h"


class OptoSerialize : public VectorSerialize2<float>
{
public:
	int m_nsensors; //number of sensors.
	vector<PolhemusPredict *> m_pp;

	OptoSerialize(int nsensors);
	~OptoSerialize();
	virtual bool store();
	bool store(float *data);
	void getLoc(double now, float *out);
	virtual string storeName(int indx);
	virtual double *mmapRead(double *d);
};
#endif
