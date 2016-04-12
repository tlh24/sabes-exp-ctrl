#ifndef POLHEMUS_SERIALIZE_H
#define POLHEMUS_SERIALIZE_H

#include "vectorSerialize2.h"
#include "polhemusPredict.h"

// this one's a bit different,
// since the polhemus thread runs *asynchronously* from the display thread.
// ideally we want to keep an estimate of velocity, and forward-project position
// to prevent temporal noise from coupling into spatial noise.
class PolhemusSerialize : public VectorSerialize2<float>
{
public:
	int 						m_nsensors; // number of sensors
	int							m_dof; 		// DoF to receive from Liberty
	vector<PolhemusPredict *>	m_pp;

	PolhemusSerialize(int nsensors);
	PolhemusSerialize(int nsensors, int dof);
	~PolhemusSerialize();
	virtual bool store();
	bool store(float *data);
	void getLoc(double now, float *out);
	virtual string storeName(int indx);
	virtual double *mmapRead(double *d);
};

#endif
