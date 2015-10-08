#ifndef LABJACK_SERIALIZE_DOUT_H
#define LABJACK_SERIALIZE_DOUT_H

#include "vectorSerialize.h"


class LabjackSerializeDOUT : public VectorSerialize<float>
{
public:
	int m_nchannels; //number of sensors (analog inputs)

	LabjackSerializeDOUT(int nchannels);
	~LabjackSerializeDOUT();
	virtual bool store();
	virtual string storeName(int indx);
	virtual double *mmapRead(double *d);
};
#endif
