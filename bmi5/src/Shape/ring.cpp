#include "../../include/Shape/ring.h"


Ring::Ring(float innerRadius, float outerRadius, int ns) : Shape()
{
	m_ir = innerRadius;
	m_or = outerRadius;
	m_n = (ns+1)*2; //number of 2-element vertices.
	m_ns = ns;
	m_needConfig[0] = m_needConfig[1] = true;
	m_drawmode = GL_TRIANGLE_STRIP;
}

Ring::~Ring() {}

void Ring::fill(float *v)
{
	for (int i=0; i<m_ns+1; i++) {
		float t = (float)i * PI * 2 / (m_ns);
		v[i*4+0] = m_ir*sinf(t);
		v[i*4+1] = m_ir*cosf(t);
		v[i*4+2] = m_or*sinf(t);
		v[i*4+3] = m_or*cosf(t);
	}
}
