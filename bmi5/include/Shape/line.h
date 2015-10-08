#ifndef LINE_H
#define LINE_H

#include "shape.h"

class Line : public Shape
{
	float m_l;
	
	public:
	Line(float length);
	virtual ~Line();
	virtual void fill(float *v);
};


#endif
