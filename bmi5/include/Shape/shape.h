// class for drawing shapes via opengl.
#ifndef __SHAPE_H__
#define __SHAPE_H__
#include <iostream>
#include "matio.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glx.h>
#include <GL/glext.h>
#include <fstream>
#include "glInfo.h"
#include "glFont.h"
#include "../Serialize/serialize.h"
#include "../includeSerialize.h"

extern Matrix44Serialize	*g_affine44; //used for translating world->screen coordinates.
extern Matrix44Serialize	*g_quadratic44;
extern string 				g_basedirname;

#define PI 3.141592653589793
#define EPS 	1e-5

float norm(float a, float b);

/*! \class Shape */
class Shape : public Serialize
{
public:
	bool	m_needConfig[2];
	int 	m_n;
	unsigned int m_vao[2];
	unsigned int m_vbo[2];
	unsigned int m_drawmode;
	double		m_time;
	char			m_draw;
	GLuint 		m_program[2];
	array<float,4>	m_color;
	array<float,2> m_scale;
	array<float,2> m_trans;
	float				m_rot;
	vector<double> v_time;
	vector<char> v_draw;
	vector<array<unsigned char,4>> v_color;
	vector<array<float,2>> v_scale;
	vector<array<float,2>> v_trans;
	vector<float> v_rot;

	Shape(void);
	void deleteBuffers();
	virtual ~Shape();

	virtual void makeVAO(float *vertices, bool del, int display);
	void makeShader(int index, GLenum type, std::string source);
	std::string fileToString(const char *fname);
	void makeShadersNamed(int index, const char *vertexName, const char *fragmentName);
	virtual void makeShaders(int index);
	virtual void fill(float *v);
	virtual void configure(int display);
	void setupDrawMatrices(int display, float);
	virtual void draw(int display, float ar);
	virtual void move(long double);
	///serialization.
	unsigned char floatToU8(float in);
	virtual void clear();
	virtual bool store();
	virtual int nstored();
	virtual string storeName(int indx);
	virtual int getStoreClass(int indx);
	virtual void getStoreDims(int indx, size_t *dims);
	virtual void *getStore(int indx, int i);
	virtual int numStores();
	virtual double *mmapRead(double *d);
};
#endif
