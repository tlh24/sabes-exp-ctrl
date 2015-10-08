#ifndef LABJACK_SERIALIZE_AIN_H
#define LABJACK_SERIALIZE_AIN_H

#include "vectorSerialize.h"

class LabjackSerializeAIN : public VectorSerialize<float>
{
public:
	int m_nsensors; //number of sensors (analog inputs)

	LabjackSerializeAIN(int nsensors);
	~LabjackSerializeAIN();
	virtual bool store();
	bool store(float *data);
	virtual string storeName(int indx);
	virtual double *mmapRead(double *d);
};
#endif
