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
			
			glEnableVertexAttribArray(0); // enable our Vertex Array Object
			glBindVertexArray(0); // bind our Vertex Buffer Object
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
struct starStruct {
	float	position[2]; 
	unsigned int color; 
}; 
static const char *vertex_source = {
"#version 330\n"
"layout (location = 0) in vec4 position;\n"
"layout (location = 1) in vec4 color;\n"
"smooth out vec4 theColor;\n"
"void main(){\n"
"    gl_Position = position;\n"
"    theColor = color;\n"
"}\n"
};
static const char *fragment_source = {
"#version 330\n"
"smooth in vec4 theColor;\n"
"out vec4 outputColor;\n"
"void main(){\n"
"    outputColor = theColor;\n"
"}\n"
}; 
class StarField : public Shape {
public: //do something like the flow field common in the lab.
	float m_vel[2]; //in screen units/second. 
	float* m_age; //arb. units.
	starStruct* m_v; //vertices, backing store.
	float* m_pvel; //individual point velocities for variable coherence. 
	float	m_coherence; 
	GLuint	m_colorbuffer; 
	GLuint 	m_program[2]; 
	long double m_lastTime; //oh god it's been years...
	long double m_startTime; 
	
	StarField(){
		m_vel[0] = 0.2f; 
		m_vel[1] = 0.1f; 
		m_v = NULL; 
		m_pvel = NULL; 
		m_age = 0; 
		m_coherence = 0.5f; 
		m_lastTime = 0.0; 
		m_startTime = gettime(); 
	}
	~StarField(){
		if(m_v) free(m_v); m_v = NULL;
		if(m_pvel) free(m_pvel); m_pvel = NULL;
		if(m_age) free(m_age); m_age = NULL; 
		if(m_program[0]) glDeleteProgram(m_program[0]);
		if(m_program[1]) glDeleteProgram(m_program[1]);
	}
	void makeVAO(starStruct* vertices, bool del){
		if(m_n > 0){
			deleteBuffers(); 
			glGenVertexArrays(1, &m_vao); // Create our Vertex Array Object
			glBindVertexArray(m_vao); // Bind our Vertex Array Object so we can use it
			glGenBuffers(1, &m_vbo); // Generate our Vertex Buffer Object
			// VBOs are children of VAOs, apparently.
			
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo); // Bind our Vertex Buffer Object
			glBufferData(GL_ARRAY_BUFFER, m_n*sizeof(starStruct), vertices, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
			glVertexAttribPointer((GLuint)0, 2, GL_FLOAT, GL_FALSE, sizeof(starStruct), 0); // Set up our vertex attributes pointer
			glVertexAttribPointer((GLuint)1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(starStruct), (void*)8); 
			
			glEnableVertexAttribArray(0); // enable our Vertex Array Object
			glEnableVertexAttribArray(1); // enable our Vertex Array Object
			glBindVertexArray(0); // disable the VBA. 
			
			glBindBuffer(GL_ARRAY_BUFFER, 0); //disable the VBO.
			if(del) free(vertices);
		}else{
			printf("error: makeVAO: m_n < 0\n"); 	
		}
	}
	void makeShader(int index, GLenum type, const char* source){
		GLuint shader = glCreateShader(type);
		int length = strlen(source);
		glShaderSource(shader, 1, (const char **)&source, &length);
		glCompileShader(shader);
		GLint result; /* make sure the compilation was successful */
		glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
		if(result == GL_FALSE) {
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
			char* log = (char*)malloc(length);
			glGetShaderInfoLog(shader, length, &result, log);
			/* print an error message and the info log */
			fprintf(stderr, "Unable to compile shader %s\n", log);
			free(log);
			glDeleteShader(shader);
			return;
		}
		glAttachShader(m_program[index], shader); 
		glDeleteShader(shader); //will not be destroyed until the referencing program is destroyed.
		return; 
	}
	void makeShaders(int index){
		m_program[index] = glCreateProgram();
		makeShader(index, GL_VERTEX_SHADER , vertex_source); 
		makeShader(index, GL_FRAGMENT_SHADER , fragment_source); 
		glLinkProgram(m_program[index]);
		GLint result; 
		glGetProgramiv(m_program[index], GL_LINK_STATUS, &result);
		if(result == GL_FALSE) {
			GLint length;
			glGetProgramiv(m_program[index], GL_INFO_LOG_LENGTH, &length);
			char* log = (char*)malloc(length);
			glGetProgramInfoLog(m_program[index], length, &result, log);
			fprintf(stderr, "Program linking failed %d: %s\n", length, log);
			free(log);
			/* delete the program */
			glDeleteProgram(m_program[index]);
			m_program[index] = 0;
		}
	}
	float uniform(){ return ((float)rand() / (float)RAND_MAX);}
	void makeStars(int nstars, float ar){
		//distribute the stars uniformly over w, h. 
		//this just requires scaling some rand() s. 
		if(m_v) free(m_v); m_v = NULL;
		if(m_pvel) free(m_pvel); m_pvel = NULL; 
		m_v = (starStruct*)malloc(nstars * sizeof(starStruct)); 
		m_pvel = (float*)malloc(nstars * 2 * sizeof(float));
		m_age = (float*)malloc(nstars * sizeof(float)); 
		for(int i=0; i<nstars; i++){
			m_v[i].position[0] = (uniform() - 0.5)*ar*2.f;
			m_v[i].position[1] = (uniform() - 0.5)*2.f; 
			m_v[i].color = (unsigned int)(255*uniform() + 255*255*uniform() + 255*255*255*uniform());
			float angle = PI * 2.0 * ((float)rand() / (float)RAND_MAX); 
			m_pvel[i*2+0] = sinf(angle); 
			m_pvel[i*2+1] = cosf(angle); 
			m_age[i] = uniform()*PI*2.0;
		}
		m_n = nstars; 
		makeVAO(m_v, false); //keep around the b.s.
		m_drawmode = GL_POINTS; 
		//and the GLSL shaders. 
	}
	void move(float ar){
		long double time = gettime(); 
		float dt = (float)(gettime() - m_lastTime); 
		float a[2]; a[0] = ar*1.1f; a[1] = 1.1f; 
		int k = (int)(m_n * (1.0-m_coherence));
		float speed = sqrtf(m_vel[0]*m_vel[0] + m_vel[1]*m_vel[1]); 
		for(int i=0; i<k; i++){
			for(int j=0; j<2; j++){
				float f = m_v[i].position[j];
				f += m_vel[j] * dt; 
				if(f < a[j]) f += a[j]*2.0f;
				if(f > a[j]) f -= a[j]*2.0f; 
				m_v[i].position[j] = f;
			}
		}
		for(int i=k; i<m_n; i++){ //draw randoms second. not that they need be in order..
			for(int j=0; j<2; j++){
				float f = m_v[i].position[j];
				float v = m_pvel[i*2+j]; 
				f += v * speed * dt; 
				if(f < a[j]) f += a[j]*2.0f;
				if(f > a[j]) f -= a[j]*2.0f; 
				m_v[i].position[j] = f;
			}
		}
		for(int i=0; i<m_n; i++){
			double d = fmod(time+m_age[i], PI*2.0);
			unsigned int c = (unsigned int)(255.0 * 
				(-0.5 * cos(d) + 0.5)); 
			c &= 0xff; 
			m_v[i].color &= 0x00ffffff; 
			m_v[i].color += (c << 24); 
			// if it's completely transparent, update the position. 
			if(d < 0.01){
				for(int j=0; j<2; j++){
					float f = (uniform() - 0.5)*a[j]*2.f;
					m_v[i].position[j] = f;
				}
				m_v[i].color &= 0xffff5fff; //debug!  you should not see this.
			}
		}
		m_lastTime = time; 
	}
	void draw(int index){
		//this is a little more complicated, as we need to do a memcpy and user shaders.
		glPointSize(30.f); 
		glUseProgram(m_program[index]); 
		glBindVertexArray(m_vao);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo); // Bind our Vertex Buffer Object
		glBufferData(GL_ARRAY_BUFFER, m_n*sizeof(starStruct), m_v, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
		
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(starStruct), 0);
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(starStruct), (void*)8);
		
		glDrawArrays(m_drawmode, 0, m_n);  
		glBindBuffer(GL_ARRAY_BUFFER, 0); 
		glBindVertexArray(0);
		glUseProgram(0); 
	}
};
#endif
