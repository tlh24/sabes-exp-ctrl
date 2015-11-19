#ifndef STAR_FIELD_H
#define STAR_FIELD_H

#include "shape.h"

struct starStruct {
	float	position[2];
	unsigned int color;
};

class StarField : public Shape
{
public: //do something like the flow field common in the lab.
	array<float,2> m_vel; //in screen units/second.
	double *m_phase; // each stars phase
	starStruct *m_v; //vertices, backing store.
	float *m_pvel; //individual point velocities for variable coherence.
	float	m_coherence;
	float	m_starsize;
	float 	m_lifetime; // how long before a star is drawn elsewhere
	GLuint	m_colorbuffer;
	long double m_lastTime; //oh god it's been years...
	long double m_startTime;
	vector<array<float,2>> v_vel;
	vector<float> v_coherence;
	vector <float> v_lifetime;
	vector <float> v_starsize;
	// we can assume that the other parts don't change during the experiment.

	StarField();
	~StarField();
	virtual void makeVAO(starStruct *vertices, bool del, int display);
	virtual void makeStars(int nstars);
	virtual void makeShaders(int index);
	virtual void configure(int display);
	virtual void move(long double time);
	virtual void draw(int display, float ar);
	void setVel(double x, double y);
	void setCoherence(double c);
	void setLifetime(double x);
	void setStarSize(double ss);
	// serialization
	virtual void clear();
	virtual bool store();
	virtual string storeName(int indx);
	virtual int getStoreClass(int indx);
	virtual void getStoreDims(int indx, size_t *dims);
	virtual void *getStore(int indx, int i);
	virtual int numStores();
	virtual double *mmapRead(double *d);
};

#endif
