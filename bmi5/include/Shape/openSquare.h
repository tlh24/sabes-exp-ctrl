#ifndef OPEN_SQUARE_H
#define OPEN_SQUARE_H

#include "square.h"

class OpenSquare : public Square
{
	float m_iw;
public:
	OpenSquare(float innerWidth, float outerWidth);
	~OpenSquare();
	virtual void fill(float *v);
};

#endif
