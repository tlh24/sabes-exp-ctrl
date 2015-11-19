#ifndef MAGNETICFIELD_H
#define MAGNETICFIELD_H

#include "shape.h"
#include <set>
#include <gtk/gtk.h>

void generateUniqueNumbers( set<int> *ln, int min, int max, int n);
extern GtkWindow * g_subjectWindow;

struct Compass{
	float	x, y;
	unsigned int color;
};

class MagneticField : public Shape{
	public:
	double *m_phase; // angular offset; coherent lines have zero
	Compass *m_v; //vertices, backing store.
	int 	m_num_compasses;
	float	m_coherence;
	float	m_compass_l;
	GLuint	m_colorbuffer;
	float 	m_target[2];
	vector<float> v_coherence;
	vector <float*> v_target;
	vector <float> v_compass_l;

	MagneticField();
	~MagneticField();

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
