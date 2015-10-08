#include "../../include/Shape/openSquare.h"

OpenSquare::OpenSquare(float innerWidth, float outerWidth) : Square(outerWidth)
{
	m_iw = innerWidth*0.5f;
	m_n = 10;
	m_needConfig[0] = m_needConfig[1] = true;
	m_drawmode = GL_TRIANGLE_STRIP;
}

OpenSquare::~OpenSquare() {}

void OpenSquare::fill(float *v)
{
	for (int i=0; i<5; i++) {
		v[i*4+0] = m_sign[i*2+0]*m_iw;
		v[i*4+1] = m_sign[i*2+1]*m_iw;
		v[i*4+2] = m_sign[i*2+0]*m_w;
		v[i*4+3] = m_sign[i*2+1]*m_w;
	}
}
