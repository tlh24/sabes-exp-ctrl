#ifndef STAR_FIELD_CIRCLE_H
#define STAR_FIELD_CIRCLE_H

#include "starField.h"

class StarFieldCircle : public StarField
{
public:
	StarFieldCircle();
	virtual ~StarFieldCircle();
	void makeStars(int nstars);
	virtual void move(long double time);
};
#endif
