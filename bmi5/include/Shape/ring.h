#ifndef RING_H
#define RING_H

#include "shape.h"

class Ring : public Shape
{
	float	m_ir; //all fixed!
	float	m_or;
	int	m_ns;
public:
	Ring(float innerRadius, float outerRadius, int ns);
	virtual ~Ring();
	virtual void fill(float *v);
};
#endif
