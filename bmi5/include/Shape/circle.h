#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"

class Circle : public Shape
{
	float 	m_radius; // fixed!
public:
	Circle(float radius, int ns);
	virtual ~Circle();
	virtual void fill(float *v);
};

#endif
