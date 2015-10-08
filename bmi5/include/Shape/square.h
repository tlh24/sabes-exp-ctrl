#ifndef SQUARE_H
#define SQUARE_H

#include "shape.h"

class Square : public Shape
{
public:
	float m_w;
	float m_sign[10] = {-1,-1,-1,1,1,1,1,-1,-1,-1};
	Square(float width);
	~Square();
	virtual void fill(float *v);
};

#endif
