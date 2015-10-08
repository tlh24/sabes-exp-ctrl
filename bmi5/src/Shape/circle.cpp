#include "../../include/Shape/circle.h"

Circle::Circle(float radius, int ns) : Shape()
{
	m_radius = radius;
	m_n = ns+1;
	m_needConfig[0] = m_needConfig[1] = true;
	m_drawmode = GL_TRIANGLE_FAN;
}

Circle::~Circle() {}

void Circle::fill(float *v)
{
	v[0] = 0.f;
	v[1] = 0.f;
	for (int i=0; i<m_n-1; i++) {
		float t = (float)i * PI * 2 / (m_n-2);
		v[i*2+2] = m_radius*sinf(t);
		v[i*2+3] = m_radius*cosf(t);
	}
}
