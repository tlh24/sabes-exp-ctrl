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

/*
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
	Shape(void) : Serialize()
	{
		m_vao[0] = m_vao[1] = 0;
		m_vbo[0] = m_vbo[1] = 0;
		m_color[0] = m_color[1] = m_color[2] = m_color[3] = 1.f;
		m_scale[0] = m_scale[1] = 1.f;
		m_trans[0] = m_trans[1] = 0.f;
		m_rot = 0.0;
		m_name = {"shape"};
		m_needConfig[0] = m_needConfig[1] = false;
		m_program[0] = m_program[1] = 0;
		m_draw = 0;
#ifdef DEBUG
		m_draw = 3; //default to 'on'
#endif
	}
	void deleteBuffers()
	{
		for (int i=0; i<2; i++) {
			if (m_vbo[i]) glDeleteBuffers(1, &(m_vbo[i]));
			m_vbo[i] = 0;
			if (m_vao[i]) glDeleteVertexArrays(1, &(m_vao[i]));
			m_vao[i] = 0;
		}
	}
	~Shape()
	{
		//if(m_program[0]) glDeleteProgram(m_program[0]); m_program[0] = 0;
		//if(m_program[1]) glDeleteProgram(m_program[1]); m_program[1] = 0;
		//deleteBuffers(); -- must be called within the OpenGL context in which they were created.
		v_color.clear();
		v_scale.clear();
		v_trans.clear();
	}
	virtual void makeVAO(float *vertices, bool del, int display)
	{
		if (m_n > 0) {
			glGenVertexArrays(1, &(m_vao[display])); // Create our Vertex Array Object
			glBindVertexArray(m_vao[display]); // Bind our Vertex Array Object so we can use it
			glGenBuffers(1, &(m_vbo[display])); // Generate our Vertex Buffer Object
			// VBOs are children of VAOs, apparently.

			glBindBuffer(GL_ARRAY_BUFFER, m_vbo[display]); // Bind our Vertex Buffer Object
			glBufferData(GL_ARRAY_BUFFER, m_n*2*sizeof(GLfloat), vertices, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
			glVertexAttribPointer((GLuint)0, 2, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer

			glEnableVertexAttribArray(0);
			glBindVertexArray(0);
			if (del) free(vertices);
		} else {
			printf("error: makeVAO: m_n < 0\n");
		}
	}
	void makeShader(int index, GLenum type, std::string source)
	{
		GLuint shader = glCreateShader(type);
		int length = source.size();
		const char *str = source.c_str();
		glShaderSource(shader, 1, (const char **)&str, &length);
		glCompileShader(shader);
		GLint result; // make sure the compilation was successful 
		glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE) {
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
			char *log = (char *)malloc(length);
			glGetShaderInfoLog(shader, length, &result, log);
			// print an error message and the info log
			fprintf(stderr, "Unable to compile shader %s\n", log);
			free(log);
			glDeleteShader(shader);
			return;
		}
		glAttachShader(m_program[index], shader);
		glDeleteShader(shader); //will not be destroyed until the referencing program is destroyed.
		return;
	}
	std::string fileToString(const char *fname)
	{
		std::ifstream t(fname); //yay stackoverflow!!
		std::string str;
		t.seekg(0, std::ios::end);
		str.reserve(t.tellg());
		t.seekg(0, std::ios::beg);
		str.assign((std::istreambuf_iterator<char>(t)),
		           std::istreambuf_iterator<char>());
		return str;
	}
	void makeShadersNamed(int index, const char *vertexName, const char *fragmentName)
	{
		m_program[index] = glCreateProgram();
		makeShader(index, GL_VERTEX_SHADER, fileToString(vertexName));
		makeShader(index, GL_FRAGMENT_SHADER, fileToString(fragmentName));
		glLinkProgram(m_program[index]);
		GLint result;
		glGetProgramiv(m_program[index], GL_LINK_STATUS, &result);
		if (result == GL_FALSE) {
			GLint length;
			glGetProgramiv(m_program[index], GL_INFO_LOG_LENGTH, &length);
			char *log = (char *)malloc(length);
			glGetProgramInfoLog(m_program[index], length, &result, log);
			fprintf(stderr, "Program linking failed %d: %s\n", length, log);
			free(log);
			// delete the program 
			glDeleteProgram(m_program[index]);
			m_program[index] = 0;
		}
	}
	virtual void makeShaders(int index)
	{
		string vertex   = g_basedirname + "/glsl/" + "vertex_flatcolor.glsl";
		string fragment = g_basedirname + "/glsl/" + "fragment.glsl";
		makeShadersNamed(index, vertex.c_str(), fragment.c_str());
	}
	virtual void fill(float *v)
	{
		for (int i=0; i<m_n; i++) {
			v[i*2+0] = i&1;
			v[i*2+1] = (i>>1)&1;
		}
	}
	virtual void configure(int display)
	{
		if (m_needConfig[display]) {
			printf("Shape: configuring display [%d]\n", display);
			float *v = (float *)malloc((m_n)*sizeof(float)*2);
			fill(v);
			makeVAO(v, true, display);
			makeShaders(display);
			m_needConfig[display] = false;
		}
	}
	void setupDrawMatrices(int display, float)
	{
		//first pre-multiply the local->world with the world->screen matrix.
		float m[4][4]; //local->world matrix.
		for (int i=0; i<4; i++) {
			for (int j=0; j<4; j++)
				m[i][j] = 0.f;
		}
		// joey has chosen to simply absorb the aspect ratio into the scale
		// parameters in the star fields -- will do the same here.
		m[0][3] = m_trans[0];
		m[1][3] = m_trans[1];
		m[0][0] = m_scale[0] * cos(m_rot);
		m[0][1] = m_scale[0] * (-1) * sin(m_rot);
		m[1][0] = m_scale[1] * sin(m_rot);
		m[1][1] = m_scale[1] * cos(m_rot);
		m[2][2] = m[3][3] = 1.f;
		float n[4][4];
		float *aff = g_affine44->data();
		// n = affine * world (in that order!)
		for (int r=0; r<4; r++) {
			for (int c=0; c<4; c++) {
				float f = 0.f;
				for (int i=0; i<4; i++)
					//g_affine in matlab order.
					f += aff[r+4*i] * m[i][c];
				n[c][r] = f; //opengl assumes fortran order (like matlab), hence transpose.
			}
		}
		//quadratic matrix from matlab -- already transposed.
		glUseProgram(m_program[display]);
		int affloc = glGetUniformLocation(m_program[display], "affine_matrix");
		if (affloc >= 0)glUniformMatrix4fv(affloc, 1, GL_FALSE, &n[0][0]);
		int quadloc = glGetUniformLocation(m_program[display], "quadratic_matrix");
		if (quadloc >= 0)glUniformMatrix4fv(quadloc, 1, GL_FALSE, g_quadratic44->data());
	}
	virtual void draw(int display, float ar)
	{
		configure(display); //if we need it.
		if (m_draw & (1<<display)) {
			setupDrawMatrices(display, ar);
			int colorloc = glGetUniformLocation(m_program[display], "uniform_color");
			if (colorloc >= 0) glUniform4f(colorloc, m_color[0], m_color[1], m_color[2], m_color[3]);

			if (m_program[display] == 0) { //boring square mode! DEBUG.
				glBegin(GL_TRIANGLE_FAN);
				float scl = 0.5;
				glVertex3f(1.f*scl, 1.f*scl, 0.f);
				glVertex3f(1.f*scl, -1.f*scl, 0.f);
				glVertex3f(-1.f*scl, -1.f*scl, 0.f);
				glVertex3f(-1.f*scl, 1.f*scl, 0.f);
				glEnd();
			} else {
				glBindVertexArray(m_vao[display]);
				glDrawArrays(m_drawmode, 0, m_n);
				glBindVertexArray(0);
				glUseProgram(0);
			}
		}
	}
	virtual void move(long double) {} //no velocity here.
	///serialization.
	unsigned char floatToU8(float in)
	{
		in *= 255;
		in = in > 255.f ? 255.f : in;
		in = in < 0.f ? 0.f : in;
		return (unsigned char)in;
	}
	virtual void clear()
	{
		v_time.clear();
		v_color.clear();
		v_scale.clear();
		v_trans.clear();
		v_rot.clear();
	}
	virtual bool store()
	{
		array<unsigned char,4> color;
		for (int i=0; i<4; i++)
			color[i] = floatToU8(m_color[i]);
		int n = nstored();
		bool same = true;
		if (n > 0) {
			same &= (m_draw == v_draw[n-1]);
			for (int i=0; i<4; i++)
				same &= (color[i] == (v_color[n-1])[i]);
			for (int i=0; i<2; i++) {
				same &= (m_scale[i] == (v_scale[n-1])[i]);
				same &= (m_trans[i] == (v_trans[n-1])[i]);
			}
			same &= (m_rot == (v_rot[n-1]));
		} else same = false;
		if (!same) {
			v_time.push_back(m_time);
			v_draw.push_back(m_draw);
			v_color.push_back(color);
			v_scale.push_back(m_scale);
			v_trans.push_back(m_trans);
			v_rot.push_back(m_rot);
		}
		return !same;
	}
	virtual int nstored()
	{
		return v_time.size();
	}
	virtual string storeName(int indx)
	{
		switch (indx) {
		case 0:
			return m_name + string("time_o");
		case 1:
			return m_name + string("draw");
		case 2:
			return m_name + string("color");
		case 3:
			return m_name + string("scale");
		case 4:
			return m_name + string("pos");
		case 5:
			return m_name + string("rot");
		}
		return string("none");
	}
	virtual int getStoreClass(int indx)
	{
		switch (indx) {
		case 0:
			return MAT_C_DOUBLE;
		case 1:
			return MAT_C_INT8;
		case 2:
			return MAT_C_UINT8;
		case 3:
			return MAT_C_SINGLE;
		case 4:
			return MAT_C_SINGLE;
		case 5:
			return MAT_C_SINGLE;
		}
		return 0;
	}
	virtual void getStoreDims(int indx, size_t *dims)
	{
		switch (indx) {
		case 0:
			dims[0] = 1;
			dims[1] = 1;
			return;
		case 1:
			dims[0] = 1;
			dims[1] = 1;
			return;
		case 2:
			dims[0] = 4;
			dims[1] = 1;
			return;
		case 3:
			dims[0] = 2;
			dims[1] = 1;
			return;
		case 4:
			dims[0] = 2;
			dims[1] = 1;
			return;
		case 5:
			dims[0] = 1;
			dims[1] = 1;
			return;
		default:
			dims[0] = 0;
			dims[1] = 0;
			return;
		}
	}
	virtual void *getStore(int indx, int i)
	{
		switch (indx) {
		case 0:
			return (void *)&((v_time[i]));
		case 1:
			return (void *)&((v_draw[i]));
		case 2:
			return (void *)&((v_color[i])[0]);
		case 3:
			return (void *)&((v_scale[i])[0]);
		case 4:
			return (void *)&((v_trans[i])[0]);
		case 5:
			return (void *)&((v_rot[i]));
		}
		return NULL;
	}
	virtual int numStores()
	{
		return 6;
	}
	virtual double *mmapRead(double *d)
	{
		int i;
		m_time = gettime();
		*d++ = m_time;
		m_draw = (char)floor(*d++);
		for (i=0; i<4; i++)
			m_color[i] = *d++;
		for (i=0; i<2; i++)
			m_scale[i] = *d++;
		for (i=0; i<2; i++)
			m_trans[i] = *d++;
		m_rot = *d++;
		return d;
	}
};

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

	StarField() : Shape()
	{
		m_vel[0] = 0.2f;
		m_vel[1] = 0.1f;
		m_v = NULL;
		m_pvel = NULL;
		m_phase = NULL;
		m_coherence = 1.0f;
		m_lifetime = 1.0f;
		m_lastTime = 0.0;
		m_starsize = 2.0;
		m_startTime = gettime();
		m_name = string {"stars"};
	}
	~StarField()
	{
		if (m_v) free(m_v);
		m_v = NULL;
		if (m_pvel) free(m_pvel);
		m_pvel = NULL;
		if (m_phase) free(m_phase);
		m_phase = NULL;
		//deleteBuffers();
		v_vel.clear();
		v_coherence.clear();
		v_lifetime.clear();
		v_starsize.clear();
	}
	virtual void makeVAO(starStruct *vertices, bool del, int display)
	{
		//this method differs from Shape::makeVAO in that each vertex has a color.
		if (m_n > 0) {
			glGenVertexArrays(1, &(m_vao[display])); // Create our Vertex Array Object
			glBindVertexArray(m_vao[display]); // Bind our Vertex Array Object so we can use it
			glGenBuffers(1, &(m_vbo[display])); // Generate our Vertex Buffer Object
			// VBOs are children of VAOs, apparently.

			glBindBuffer(GL_ARRAY_BUFFER, m_vbo[display]); // Bind our Vertex Buffer Object
			glBufferData(GL_ARRAY_BUFFER, m_n*sizeof(starStruct), vertices, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
			glVertexAttribPointer((GLuint)0, 2, GL_FLOAT, GL_FALSE, sizeof(starStruct), 0); // Set up our vertex attributes pointer
			glVertexAttribPointer((GLuint)1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(starStruct), (void *)8);

			glEnableVertexAttribArray(0); // enable our Vertex Array Object
			glEnableVertexAttribArray(1); // enable our Vertex Array Object
			glBindVertexArray(0); // disable the VBA.

			glBindBuffer(GL_ARRAY_BUFFER, 0); //disable the VBO.
			if (del) free(vertices);
		} else {
			printf("error: makeVAO: m_n < 0\n");
		}
	}
	float uniform()
	{
		return ((float)rand() / (float)RAND_MAX);
	}
	float norm(float a, float b)
	{
		return sqrtf(a*a + b*b);
	}
	virtual void makeStars(int nstars)
	{
		//distribute the stars uniformly over w, h.
		//this just requires scaling some rand() s.
		if (m_v) free(m_v);
		m_v = NULL;
		if (m_pvel) free(m_pvel);
		m_pvel = NULL;
		m_v = (starStruct *)malloc(nstars * sizeof(starStruct));
		m_pvel = (float *)malloc(nstars * 2 * sizeof(float));
		m_phase = (double *)malloc(nstars * sizeof(double));
		for (int i=0; i<nstars; i++) {
			m_v[i].position[0] = (uniform() - 0.5)*2.f;
			m_v[i].position[1] = (uniform() - 0.5)*2.f;
			m_v[i].color = 0xffffffff;
			float angle = uniform()*PI*2.f;
			m_pvel[i*2+0] = sinf(angle); // unit vector
			m_pvel[i*2+1] = cosf(angle); // not a velocity
			m_phase[i] = uniform()*PI*2.0;
		}
		m_n = nstars;
		m_needConfig[0] = m_needConfig[1] = true;
		m_drawmode = GL_POINTS;
	}
	virtual void makeShaders(int index)
	{
		string vertex   = g_basedirname + "/glsl/" + "vertex.glsl";
		string fragment = g_basedirname + "/glsl/" + "fragment.glsl";
		makeShadersNamed(index, vertex.c_str(), fragment.c_str());
	}
	virtual void configure(int display)
	{
		if (m_needConfig[display]) {
			makeVAO(m_v, false, display); //keep around the b.s.
			makeShaders(display);
			m_needConfig[display] = false;
		}
	}
	virtual void move(long double time)
	{
		if (!m_v || !m_pvel || !m_phase) return;
		unsigned int basecol = 0;
		basecol += (unsigned int)(m_color[3] * 255) & 255;
		basecol <<= 8;
		basecol += (unsigned int)(m_color[2] * 255) & 255;
		basecol <<= 8;
		basecol += (unsigned int)(m_color[1] * 255) & 255;
		basecol <<= 8;
		basecol += (unsigned int)(m_color[0] * 255) & 255;

		float dt = (float)(time - m_lastTime);
		double fq = 1/(m_lifetime+1e-6); // dot lifetime freq; protect div-0

		float scaled_vel[2];
		scaled_vel[0] = m_vel[0] / m_scale[0];
		scaled_vel[1] = m_vel[1] / m_scale[1];
		float speed = norm(scaled_vel[0], scaled_vel[1]);

		int k = (int)floor(m_n * m_coherence);
		for (int i=0; i<m_n; i++) {
			for (int j=0; j<2; j++) {
				float f = m_v[i].position[j];
				float v;
				if (i<k)	// coherent stars
					v = scaled_vel[j];
				else 		// random stars
					v = m_pvel[i*2+j] * speed;
				f += v * dt;
				if (f < 0.5f) f += 1.f;
				if (f > 0.5f) f -= 1.f;
				m_v[i].position[j] = f;
			}
			m_v[i].color = basecol;
			double d  = cos(2.0*PI*fq*time			+ m_phase[i]);
			double dp = cos(2.0*PI*fq*m_lastTime	+ m_phase[i]); // previous
			// update the position.
			// if lifetime is negative, stars live forever
			if (d > 0 && dp <= 0 && m_lifetime > 0.f) {
				for (int j=0; j<2; j++) {
					float f = uniform() - 0.5f;
					m_v[i].position[j] = f;
				}
			}
		}
		m_lastTime = time;
	}
	virtual void draw(int display, float ar)
	{
		configure(display);
		//this is a little more complicated, as we need to do a memcpy and user shaders.
		if ((m_draw & (1<<display)) && m_v && m_pvel && m_phase) {
			glPointSize(m_starsize);
			setupDrawMatrices(display, ar);

			glBindVertexArray(m_vao[display]);
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo[display]); // Bind our Vertex Buffer Object
			glBufferData(GL_ARRAY_BUFFER, m_n*sizeof(starStruct), m_v, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW

			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(starStruct), 0);
			glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(starStruct), (void *)8);

			glDrawArrays(m_drawmode, 0, m_n);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
			glUseProgram(0);
		}
	}
	void setVel(double x, double y)
	{
		m_vel[0] = x;
		m_vel[1] = y;
	}
	void setCoherence(double c)
	{
		m_coherence = c;
	}
	void setLifetime(double x)
	{
		m_lifetime = x;
	}
	void setStarSize(double ss)
	{
		m_starsize = ss;
	}
	// serialization
	virtual void clear()
	{
		Shape::clear();
		v_vel.clear();
		v_coherence.clear();
		v_lifetime.clear();
		v_starsize.clear();
	}
	virtual bool store()
	{
		array<unsigned char,4> color;
		for (int i=0; i<4; i++)
			color[i] = floatToU8(m_color[i]);
		int n = nstored();
		bool same = true;
		if (n > 0) {
			same &= (m_draw == v_draw[n-1]);
			for (int i=0; i<4; i++)
				same &= (color[i] == (v_color[n-1])[i]);
			for (int i=0; i<2; i++) {
				same &= (m_scale[i] == (v_scale[n-1])[i]);
				same &= (m_trans[i] == (v_trans[n-1])[i]);
			}
			same &= (m_rot == (v_rot[n-1]));
			for (int i=0; i<2; i++)
				same &= (m_vel[i] == (v_vel[n-1])[i]);
			same &= (m_coherence == v_coherence[n-1]);
			same &= (m_lifetime == v_lifetime[n-1]);
			same &= (m_starsize == v_starsize[n-1]);
		} else same = false;
		if (!same) {
			v_time.push_back(m_time);
			v_draw.push_back(m_draw);
			v_color.push_back(color);
			v_scale.push_back(m_scale);
			v_trans.push_back(m_trans);
			v_rot.push_back(m_rot);
			v_vel.push_back(m_vel);
			v_coherence.push_back(m_coherence);
			v_lifetime.push_back(m_lifetime);
			v_starsize.push_back(m_starsize);
		}
		return !same;
	}
	virtual string storeName(int indx)
	{
		switch (indx) {
		case 0:
			return m_name + string("vel");
		case 1:
			return m_name + string("coherence");
		case 2:
			return m_name + string("lifetime");
		case 3:
			return m_name + string("starsize");
		}
		return Shape::storeName(indx - 4);
	}
	virtual int getStoreClass(int indx)
	{
		switch (indx) {
		case 0:
			return MAT_C_SINGLE;
		case 1:
			return MAT_C_SINGLE;
		case 2:
			return MAT_C_SINGLE;
		case 3:
			return MAT_C_SINGLE;
		}
		return Shape::getStoreClass(indx - 4);
	}
	virtual void getStoreDims(int indx, size_t *dims)
	{
		switch (indx) {
		case 0:
			dims[0] = 2;
			dims[1] = 1;
			return;
		case 1:
			dims[0] = 1;
			dims[1] = 1;
			return;
		case 2:
			dims[0] = 1;
			dims[1] = 1;
			return;
		case 3:
			dims[0] = 1;
			dims[1] = 1;
			return;
		}
		return Shape::getStoreDims(indx-4, dims);
	}
	virtual void *getStore(int indx, int i)
	{
		switch (indx) {
		case 0:
			return (void *)&((v_vel[i])[0]);
		case 1:
			return (void *)&((v_coherence[i]));
		case 2:
			return (void *)&((v_lifetime[i]));
		case 3:
			return (void *)&((v_starsize[i]));
		}
		return Shape::getStore(indx-4, i);
	}
	virtual int numStores()
	{
		return Shape::numStores() + 4;
	}
	virtual double *mmapRead(double *d)
	{
		for (int i=0; i<2; i++)
			m_vel[i] = *d++;
		m_coherence = *d++;
		m_lifetime = *d++;
		m_starsize = *d++;
		return Shape::mmapRead(d);
	}
};

class StarFieldCircle : public StarField
{
public:
	StarFieldCircle() {}
	~StarFieldCircle() {}
	void makeStars(int nstars)
	{
		//distribute the stars uniformly over w, h.
		//this just requires scaling some rand() s.
		if (m_v) free(m_v);
		m_v = NULL;
		if (m_pvel) free(m_pvel);
		m_pvel = NULL;
		m_v = (starStruct *)malloc(nstars * sizeof(starStruct));
		m_pvel = (float *)malloc(nstars * 2 * sizeof(float));
		m_phase = (double *)malloc(nstars * sizeof(double));
		for (int i=0; i<nstars; i++) {

			// draw uniformly in a circle with radius 0.5
			float x = uniform()*PI*2.f;
			float u = random()+random();
			float r = u > 1 ? 2-u : u;
			m_v[i].position[0] = 0.5f*r*cosf(x);
			m_v[i].position[1] = 0.5f*r*sinf(x);

			m_v[i].color = 0xffffffff;
			float angle = uniform()*PI*2.f;
			m_pvel[i*2+0] = sinf(angle); // unit vector
			m_pvel[i*2+1] = cosf(angle); // not a velocity
			m_phase[i] = uniform()*PI*2.0;
		}
		m_n = nstars;
		m_needConfig[0] = m_needConfig[1] = true;
		m_drawmode = GL_POINTS;
	}
	virtual void move(long double time)
	{

		if (!m_v || !m_pvel || !m_phase) return;

		unsigned int basecol = 0;
		basecol += (unsigned int)(m_color[3] * 255) & 255;
		basecol <<= 8;
		basecol += (unsigned int)(m_color[2] * 255) & 255;
		basecol <<= 8;
		basecol += (unsigned int)(m_color[1] * 255) & 255;
		basecol <<= 8;
		basecol += (unsigned int)(m_color[0] * 255) & 255;

		float dt = (float)(time - m_lastTime);
		double fq = 1/(m_lifetime+1e-6); // dot lifetime freq; protect div-0

		float scaled_vel[2];
		scaled_vel[0] = m_vel[0] / m_scale[0];
		scaled_vel[1] = m_vel[1] / m_scale[1];
		float speed = norm(scaled_vel[0], scaled_vel[1]);

		int k = (int)floor(m_n * m_coherence);
		for (int i=0; i<m_n; i++) {

			float p[2];
			for (int j=0; j<2; j++) {
				p[j] = m_v[i].position[j];
				float v;
				if (i<k)	// coherent stars
					v = scaled_vel[j];
				else 		// random stars
					v = m_pvel[i*2+j] * speed;
				p[j] += v * dt;
			}
			float r = norm(m_v[i].position[0], m_v[i].position[1]);
			if (r > 0.5 && speed > 0) {
				float angle = atan2(p[1],p[0]);
				angle += PI;
				p[0] = 0.5 * cosf(angle);
				p[1] = 0.5 * sinf(angle);
			}
			m_v[i].position[0] = p[0];
			m_v[i].position[1] = p[1];

			m_v[i].color = basecol;

			double d  = cos(2.0*PI*fq*time			+ m_phase[i]);
			double dp = cos(2.0*PI*fq*m_lastTime	+ m_phase[i]); // previous

			// update the position.
			// if lifetime is negative, stars live forever
			if (d > 0 && dp <= 0 && m_lifetime > 0.f) {
				// draw uniformly in a circle with radius 0.5
				float a = uniform();
				float b = uniform();
				if (b < a) {
					float tmp = b;
					b = a;
					a = tmp;
				}
				m_v[i].position[0] = 0.5f*b*cosf(PI*2.f*a/b);
				m_v[i].position[1] = 0.5f*b*sinf(PI*2.f*a/b);
			}
		}
		m_lastTime = time;
	}
};

class Line : public Shape
{
	float m_l;
	public:
	Line(float length) : Shape()
	{
		m_l = length * 0.5f;
		m_n = 2;
		m_needConfig[0] = m_needConfig[1] = true;
		m_drawmode = GL_LINES;
	}
	~Line(){}
	virtual void fill(float *v){
		v[0] = -1.0f * m_l;
		v[1] = 0.0f;
		v[2] = 1.0f * m_l;
		v[3] = 0.0f;
	}
	
};

class Circle : public Shape
{
	float 	m_radius; // fixed!
public:
	Circle(float radius, int ns) : Shape()
	{
		m_radius = radius;
		m_n = ns+1;
		m_needConfig[0] = m_needConfig[1] = true;
		m_drawmode = GL_TRIANGLE_FAN;
	}
	~Circle() {}
	virtual void fill(float *v)
	{
		v[0] = 0.f;
		v[1] = 0.f;
		for (int i=0; i<m_n-1; i++) {
			float t = (float)i * PI * 2 / (m_n-2);
			v[i*2+2] = m_radius*sinf(t);
			v[i*2+3] = m_radius*cosf(t);
		}
	}
};

class Ring : public Shape
{
	float	m_ir; //all fixed!
	float	m_or;
	int	m_ns;
public:
	Ring(float innerRadius, float outerRadius, int ns) : Shape()
	{
		m_ir = innerRadius;
		m_or = outerRadius;
		m_n = (ns+1)*2; //number of 2-element vertices.
		m_ns = ns;
		m_needConfig[0] = m_needConfig[1] = true;
		m_drawmode = GL_TRIANGLE_STRIP;
	}
	~Ring() {}
	virtual void fill(float *v)
	{
		for (int i=0; i<m_ns+1; i++) {
			float t = (float)i * PI * 2 / (m_ns);
			v[i*4+0] = m_ir*sinf(t);
			v[i*4+1] = m_ir*cosf(t);
			v[i*4+2] = m_or*sinf(t);
			v[i*4+3] = m_or*cosf(t);
		}
	}
};

class Square : public Shape
{
public:
	float m_w;
	float m_sign[10] = {-1,-1,-1,1,1,1,1,-1,-1,-1};
	Square(float width)
	{
		m_w = width * 0.5f;
		m_n = 5;
		m_needConfig[0] = m_needConfig[1] = true;
		m_drawmode = GL_TRIANGLE_FAN;
	}
	~Square() {}
	virtual void fill(float *v)
	{
		for (int i=0; i<5; i++) {
			v[i*2+0] = m_sign[i*2+0]*m_w;
			v[i*2+1] = m_sign[i*2+1]*m_w;
		}
	}
};

class OpenSquare : public Square
{
	float m_iw;
public:
	OpenSquare(float innerWidth, float outerWidth) : Square(outerWidth)
	{
		m_iw = innerWidth*0.5f;
		m_n = 10;
		m_needConfig[0] = m_needConfig[1] = true;
		m_drawmode = GL_TRIANGLE_STRIP;
	}
	~OpenSquare() {}
	virtual void fill(float *v)
	{
		for (int i=0; i<5; i++) {
			v[i*4+0] = m_sign[i*2+0]*m_iw;
			v[i*4+1] = m_sign[i*2+1]*m_iw;
			v[i*4+2] = m_sign[i*2+0]*m_w;
			v[i*4+3] = m_sign[i*2+1]*m_w;
		}
	}
};

class DisplayText : public VectorSerialize<char>
{
public:
	string	m_text;
	char		m_draw;
	array<float,2>	m_pos; //double so the comparisons work properly.
	vector<char> v_draw;
	array<unsigned char,4>	m_color;
	vector<array<float,2>> v_pos;
	vector<array<unsigned char,4>> v_color;

	DisplayText(int size) : VectorSerialize(size, MAT_C_INT8)
	{
		m_draw = 0;
#ifdef DEBUG
		m_draw = 3;
#endif
		m_text = string("debug text!");
		m_pos[0] = 0;
		m_pos[1] = 0;
		for (int i=0; i<4; i++)
			m_color[i] = 1.f;
	}
	~DisplayText()
	{
		clear();
	}
	virtual bool store()
	{
		int n = nstored();
		bool same = true;
		if (n > 0) {
			same &= (m_draw == v_draw[n-1]);
			for (int i=0; i<2; i++)
				same &= (m_pos[i] == (v_pos[n-1])[i]);
			for (int i=0; i<4; i++)
				same &= (m_color[i] == (v_color[n-1])[i]);
		} else same = false;
		if (!same) {
			same &= !VectorSerialize::store();
			if (!same) {
				v_draw.push_back(m_draw);
				v_pos.push_back(m_pos);
				v_color.push_back(m_color);
			}
		}
		return !same;
	}
	virtual void clear()
	{
		VectorSerialize::clear();
		v_draw.clear();
		v_pos.clear();
		v_color.clear();
	}
	virtual string storeName(int indx)
	{
		switch (indx) {
		case 0:
			return m_name + string("draw");
		case 1:
			return m_name + string("pos");
		case 2:
			return m_name + string("color");
		}
		return VectorSerialize::storeName(indx - 3);

	}
	virtual int getStoreClass(int indx)
	{
		switch (indx) {
		case 0:
			return MAT_C_INT8;
		case 1:
			return MAT_C_SINGLE;
		case 2:
			return MAT_C_UINT8;
		}
		return VectorSerialize::getStoreClass(indx - 3);
	}
	virtual void getStoreDims(int indx, size_t *dims)
	{
		switch (indx) {
		case 0:
			dims[0] = 1;
			dims[1] = 1;
			return;
		case 1:
			dims[0] = 2;
			dims[1] = 1;
			return;
		case 2:
			dims[0] = 4;
			dims[1] = 1;
			return;
		}
		return VectorSerialize::getStoreDims(indx - 3, dims);
	}
	virtual void *getStore(int indx, int i)
	{
		switch (indx) {
		case 0:
			return (void *)&(v_draw[i]);
		case 1:
			return (void *)&((v_pos[i])[0]);
		case 2:
			return (void *)&((v_color[i])[0]);
		}
		return VectorSerialize::getStore(indx - 3, i);
	}
	virtual int numStores()
	{
		return VectorSerialize::numStores() + 3;
	}
	virtual double *mmapRead(double *d)
	{
		m_draw = (char)floor(*d++);
		for (int i=0; i<2; i++)
			m_pos[i] = *d++;
		for (int i=0; i<4; i++)
			m_color[i] = (char)((*d++) * 255.0);
		d = VectorSerialize::mmapRead(d);
		//copy data to string.
		m_text.reserve(m_size); //just in case..
		char *s = (char *)m_text.data();
		for (int i=0; i<m_size; i++)
			s[i] = m_stor[i];
		return d;
	}
	virtual void draw(int display, float ar)
	{
		if (m_draw & (1<<display)) {
			//need to convert world coords to screen.
			float xar = ar < 1.f ? ar : 1.f;
			float yar = ar > 1.f ? 1.f/ar : 1.f;
			float in[4], out[4];
			for (int i=0; i<4; i++) {
				in[i] = out[i] = 0.f;
			}
			in[0] = m_pos[0]*xar;
			in[1] = m_pos[1]*yar;
			float *aff = g_affine44->data(); //in matlab/openGL row major order.
			for (int r=0; r<4; r++) {
				for (int c=0; c<4; c++) {
					out[r] += aff[r+4*c] * in[c];
				}
			}
			glColor4f(m_color[0], m_color[1], m_color[2], m_color[3]);
			glRasterPos2f(out[0], out[1]);
			glPrint(m_text.c_str(), display);
		}
	}
};*/
#endif
