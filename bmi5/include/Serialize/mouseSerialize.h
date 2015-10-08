#ifndef MOUSE_SERIALIZE_H
#define MOUSE_SERIALIZE_H

#include "vectorSerialize.h"


class MouseSerialize : public VectorSerialize<float>
{
public:
	//timing via VectorSerialize.
	MouseSerialize();
	~MouseSerialize();
	virtual bool store();
	virtual string storeName(int );
	virtual double *mmapRead(double *d);
};
#endif
