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
		unsigned int m_drawN; 
		float	m_color[4];
		float m_scale[2]; 
		float m_trans[2]; 
	Shape(void){
		m_vao = 0; 
		m_vbo = 0; 
		m_drawN = 0; 
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
	void makeVAO(float* vertices){
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
		free(vertices);
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
		makeVAO(v); 
		m_drawmode = GL_TRIANGLE_FAN; 
		m_drawN = n+1; 
	}
	void draw(){
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(m_trans[0], m_trans[1], 0.f); 
		glScalef(m_scale[0], m_scale[1], 1.f); 
		glColor4f(m_color[0], m_color[1], m_color[2], m_color[3]);
		glBindVertexArray(m_vao);
		glDrawArrays(m_drawmode, 0, m_drawN);  
		glBindVertexArray(0);
		glPopMatrix(); 
	}
	void translate(float x, float y){
		m_trans[0] = x; m_trans[1] = y; 
	}
	void scale(float s){
		m_scale[0] = m_scale[1] = s;
	}
};
#endif
