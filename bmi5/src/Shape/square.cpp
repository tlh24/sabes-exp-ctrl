#include "../../include/Shape/square.h"

Square::Square(float width)
{
	m_w = width * 0.5f;
	m_n = 5;
	m_needConfig[0] = m_needConfig[1] = true;
	m_drawmode = GL_TRIANGLE_FAN;
}

Square::~Square() {}

void Square::fill(float *v)
{
	for (int i=0; i<5; i++) {
		v[i*2+0] = m_sign[i*2+0]*m_w;
		v[i*2+1] = m_sign[i*2+1]*m_w;
	}
}
