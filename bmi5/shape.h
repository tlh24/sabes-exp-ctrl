// class for drawing shapes via opengl.
#ifndef __SHAPE_H__
#define __SHAPE_H__
class Shape{
	public:
		int 	m_n; 
		unsigned int m_vao; 
		unsigned int m_vbo; 
		unsigned int m_drawmode; 
		unsigned int m_drawN; 
	Shape(void){
		m_vao = NULL; 
		m_vbo = NULL; 
		m_drawN = 0; 
	}
	~Shape(){
		if(m_vbo) glDeleteBuffers(1, &m_vbo); 
		if(m_vao) glDeleteVertexArrays(1, &m_vao); 
	}
	void makeVAO(float* vertices){
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
		//makes a circle, radius 1, at the origin.
		float* v = (float*)malloc((n+1)*sizeof(float)*2); 
		m_v[0] = 0.f; 
		m_v[1] = 0.f; 
		for(int i=0; i<n; i++){
			float t = (float)i * PI * 2 / (n-1); 
			m_v[i*2+2] = r*sinf(t); 
			m_v[i*2+3] = r*cosf(t); 
		}
		m_n = n+1; 
		makeVAO(v); 
		m_drawmode = GL_POLYGON; 
		m_drawN = n+1; 
	}
	void draw(){
		glBindVertexArray(m_vao);
		glDrawArrays(GL_POLYGON, 0, m_drawN);  
		glBindVertexArray(0);
	}
}
#endif
