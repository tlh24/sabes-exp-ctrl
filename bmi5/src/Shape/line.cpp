#include "../../include/Shape/line.h"

Line::Line(float length) : Shape()
{
	m_l = length * 0.5f;
	m_n = 2;
	m_needConfig[0] = m_needConfig[1] = true;
	m_drawmode = GL_LINES;
}

Line::~Line(){}

void Line::fill(float *v){
	v[0] = -1.0f * m_l;
	v[1] = 0.0f;
	v[2] = 1.0f * m_l;
	v[3] = 0.0f;
}
