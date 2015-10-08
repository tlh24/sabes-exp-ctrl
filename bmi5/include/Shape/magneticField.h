/*#ifndef MAGNETICFIELD_H
#define MAGNETICFIELD_H

#include "shape.h"

float norm(float a, float b);

struct Compass{
	float	line[4];
	unsigned int color;
};

class MagneticField : public Shape{
	public:
	double *m_phase; // each stars phase
	starStruct *m_v; //vertices, backing store.
	float	m_coherence;
	float	m_compass_l;
	GLuint	m_colorbuffer;
	float 	m_target[2];
	
	MagneticField();
	~MagneticField()
	
	void setTarget(float* target);
	
	virtual void makeVAO(Compass *vertices, bool del, int display);
	virtual void makeShaders(int index);
	virtual void makeCompasses(int nCompasses);
	virtual void configure(int display);
	virtual void update(long double time);
	
	virtual void draw(int display, float ar);
	
};

#endif
*/
