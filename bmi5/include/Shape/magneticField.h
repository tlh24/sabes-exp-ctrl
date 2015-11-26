#ifndef MAGNETICFIELD_H
#define MAGNETICFIELD_H

#include "shape.h"
#include <set>
#include <gtk/gtk.h>

#define EPS 	1e-5

float norm(float a, float b);
void generateUniqueNumbers( set<int> *ln, int min, int max, int n);
extern GtkWindow *g_subjectWindow;

struct Compass {
	float	x, y;
	unsigned int color;
};

class MagneticField : public Shape
{
public:
	float 	*m_ghost_targets;
	Compass *m_v; //vertices, backing store.
	int 	m_num_compasses;
	float	m_coherence;
	float	m_compass_l;
	GLuint	m_colorbuffer;
	float 	m_target[2];
	float 	m_ptarget[2]; // previous target
	bool 	*m_is_coherent;
	bool	*m_clockwise; // true -> clockwise; false -> anticlockwise
	vector<float> v_coherence;
	vector <float *> v_target;
	vector <float> v_compass_l;

	MagneticField();
	~MagneticField();

	void freeMemory();
	virtual void makeVAO(Compass *vertices, bool del, int display);
	virtual void makeShaders(int index);
	virtual void makeCompasses(int nCompasses);
	virtual void configure(int display);
	//virtual void update(long double time);
	virtual void move(long double time);

	virtual void draw(int display, float ar);

	// Setters
	void setCoherence(float coherence);
	void setLinesLength(float length);
	void setTarget(double *&target);

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
