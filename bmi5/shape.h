// class for drawing shapes via opengl.
#ifndef __SHAPE_H__
#define __SHAPE_H__
/*
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glext.h> 
*/
#define PI 3.141592653589793
class Shape{
	public:
		int 	m_n; 
		unsigned int m_vao; 
		unsigned int m_vbo; 
		unsigned int m_drawmode; 
		float	m_color[4];
		float m_scale[2]; 
		float m_trans[2]; 
	Shape(void){
		m_vao = 0; 
		m_vbo = 0; 
		m_color[0] = m_color[1] = m_color[2] = m_color[3] = 1.f; 
		m_scale[0] = m_scale[1] = 1.f; 
		m_trans[0] = m_trans[1] = 0.f; 
	}
	void deleteBuffers(){
		if(m_vbo) glDeleteBuffers(1, &m_vbo); m_vbo = 0; 
		if(m_vao) glDeleteVertexArrays(1, &m_vao); m_vao = 0; 
	}
	~Shape(){
		deleteBuffers(); 
	}
	void makeVAO(float* vertices, bool del){
		if(m_n > 0){
			deleteBuffers(); 
			glGenVertexArrays(1, &m_vao); // Create our Vertex Array Object
			glBindVertexArray(m_vao); // Bind our Vertex Array Object so we can use it
			glGenBuffers(1, &m_vbo); // Generate our Vertex Buffer Object
			// VBOs are children of VAOs, apparently.
			
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo); // Bind our Vertex Buffer Object
			glBufferData(GL_ARRAY_BUFFER, m_n*2*sizeof(GLfloat), vertices, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
			glVertexAttribPointer((GLuint)0, 2, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
			
			glEnableVertexAttribArray(0); // Disable our Vertex Array Object
			glBindVertexArray(0); // Disable our Vertex Buffer Object
			if(del) free(vertices);
		}else{
			printf("error: makeVAO: m_n < 0\n"); 	
		}
	}
	void makeCircle(int n){
		//makes a circle, diameter 1, at the origin.
		float* v = (float*)malloc((n+1)*sizeof(float)*2); 
		v[0] = 0.f; 
		v[1] = 0.f; 
		for(int i=0; i<n; i++){
			float t = (float)i * PI * 2 / (n-1); 
			v[i*2+2] = 0.5f*sinf(t); 
			v[i*2+3] = 0.5f*cosf(t); 
		}
		m_n = n+1; 
		makeVAO(v, true); 
		m_drawmode = GL_TRIANGLE_FAN; 
	}
	void draw(){
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(m_trans[0], m_trans[1], 0.f); 
		glScalef(m_scale[0], m_scale[1], 1.f); 
		glColor4f(m_color[0], m_color[1], m_color[2], m_color[3]);
		glBindVertexArray(m_vao);
		glDrawArrays(m_drawmode, 0, m_n);  
		glBindVertexArray(0);
		glPopMatrix(); 
	}
	void translate(float x, float y){
		m_trans[0] = x; m_trans[1] = y; 
	}
	void scale(float s){
		m_scale[0] = m_scale[1] = s;
	}
	void setColor(float r, float g, float b){
		m_color[0] = r; 
		m_color[1] = g; 
		m_color[2] = b; 
	}
	void setAlpha(float a){
		m_color[3] = a; 
	}
};
class StarField : public Shape {
public: //do something like the flow field common in the lab.
	float m_vel[2]; //in screen units/second. 
	float* m_v; //vertices, backing store.
	float* m_pvel; //individual point velocities for variable coherence. 
	float	m_coherence; 
	GLuint	m_colorbuffer; 
	
	StarField(){
		m_vel[0] = 0.2f; 
		m_vel[1] = 0.1f; 
		m_v = NULL; 
		m_pvel = NULL; 
		m_coherence = 0.5f; 
	}
	~StarField(){
		if(m_v) free(m_v); m_v = NULL;
		if(m_pvel) free(m_pvel); m_pvel = NULL; 
	}
	void makeStars(int nstars, float ar){
		//distribute the stars uniformly over w, h. 
		//this just requires scaling some rand() s. 
		if(m_v) free(m_v); m_v = NULL; 
		m_v = (float*)malloc(nstars * 2 * sizeof(float)); 
		m_pvel = (float*)malloc(nstars * 2 * sizeof(float)); 
		for(int i=0; i<nstars; i++){
			m_v[i*2+0] = (((float)rand() / (float)RAND_MAX) - 0.5)*ar*2.f;
			m_v[i*2+1] = (((float)rand() / (float)RAND_MAX) - 0.5)*2.f; 
			float angle = 3.141592653589793 * 2.0 * ((float)rand() / (float)RAND_MAX); 
			m_pvel[i*2+0] = sinf(angle); 
			m_pvel[i*2+1] = cosf(angle); 
		}
		m_n = nstars; 
		makeVAO(m_v, false); //keep around the b.s.
		m_drawmode = GL_POINTS; 
		//and the color buffers. 
		glGenBuffers(1, &m_colorbuffer); 
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	}
	void move(float dt, float ar){ //dt in seconds.
		float a[2]; a[0] = ar; a[1] = 1.f; 
		int j = (int)(m_n * m_coherence);
		float speed = sqrtf(m_vel[0]*m_vel[0] + m_vel[1]*m_vel[1]); 
		for(int i=0; i<j; i++){
			for(int j=0; j<2; j++){
				float f = m_v[i*2+j];
				float v = m_pvel[i*2+j]; 
				f += v * speed * dt; 
				if(f < a[j]) f += a[j]*2.f;
				if(f > a[j]) f -= a[j]*2.f; 
				m_v[i*2+j] = f;
			}
		}
		for(int i=j; i<m_n; i++){
			for(int j=0; j<2; j++){
				float f = m_v[i*2+j];
				f += m_vel[j] * dt; 
				if(f < a[j]) f += a[j]*2.f;
				if(f > a[j]) f -= a[j]*2.f; 
				m_v[i*2+j] = f;
			}
		}
	}
	void draw(){
		//this is a little more complicated, as we need to do a memcpy. 
		glPointSize(3.f); 
		glBindVertexArray(m_vao);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo); // Bind our Vertex Buffer Object
		glBufferData(GL_ARRAY_BUFFER, m_n*2*sizeof(GLfloat), m_v, GL_STATIC_DRAW);
		glColor4f(m_color[0], m_color[1], m_color[2], m_color[3]);
		glDrawArrays(m_drawmode, 0, m_n);  
		glBindVertexArray(0);
	}
};
#endif
