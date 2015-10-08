#ifndef MATRIX44_SERIALIZE_H
#define MATRIX44_SERIALIZE_H
#include "serialize.h"

//convenience class for saving 4x4 calibration matrix (affine, quadratic).
class Matrix44Serialize : public Serialize
{
public:
	array<double,16>			m_cmp;
	array<float,16>				m_x;
	vector<array<float,16> >	v_x;

	Matrix44Serialize(string name);
	~Matrix44Serialize();
	virtual void clear();
	virtual bool store();
	virtual int nstored();
	virtual string storeName(int );
	virtual int getStoreClass(int );
	virtual void getStoreDims(int, size_t *dims);
	virtual void *getStore(int , int k);
	virtual int numStores();
	virtual double *mmapRead(double *d);
	float *data();
};

#endif
