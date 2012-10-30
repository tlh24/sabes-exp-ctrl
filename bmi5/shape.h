// class for drawing shapes via opengl.
#ifndef __SHAPE_H__
#define __SHAPE_H__
/*
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glext.h> 
*/
#define PI 3.141592653589793
class Shape : public Serialize {
	public:
		int 	m_n; 
		unsigned int m_vao; 
		unsigned int m_vbo; 
		unsigned int m_drawmode; 
		array<float,4>	m_color;
		array<float,2> m_scale; 
		array<float,2> m_trans; 
		vector<array<unsigned char,4>> v_color; 
		vector<array<float,2>> v_scale; 
		vector<array<float,2>> v_trans; 
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
		v_color.clear(); 
		v_scale.clear(); 
		v_trans.clear();
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
	void scale(float x, float y){
		m_scale[0] = x; m_scale[1] = y; 
	}
	void setColor(float r, float g, float b){
		m_color[0] = r; 
		m_color[1] = g; 
		m_color[2] = b; 
	}
	void setAlpha(float a){
		m_color[3] = a; 
	}
	void setColor4d(double* c){
		for(int i=0; i<4; i++){
			m_color[i] = (float)c[i]; 
		}
	}
	//serialization. 
	unsigned char floatToU8(float in){
		in *= 255; 
		in = in > 255.f ? 255.f : in; 
		in = in < 0.f ? 0.f : in; 
		return (unsigned char)in; 
	}
	virtual void store(){
		array<unsigned char,4> color; 
		for(int i=0; i<4; i++)
			color[i] = floatToU8(m_color[i]); 
		v_color.push_back(color);
		v_scale.push_back(m_scale); 
		v_trans.push_back(m_trans); 
	}
	virtual int nstored(){ return v_color.size(); }
	virtual string storeName(int indx){
		switch(indx){
			case 0: return string("shape_color");
			case 1: return string("shape_scale");
			case 2: return string("shape_trans");
		} return string("none"); 
	}
	virtual int getStoreClass(int indx){
		switch(indx){ 
			case 0: return MAT_C_UINT8;
			case 1: return MAT_C_SINGLE;
			case 2: return MAT_C_SINGLE;
		} return 0; 
	}
	virtual void getStoreDims(int indx, size_t* dims){
		switch(indx){
			case 0: dims[0] = 4; dims[1] = 1; break; 
			case 1: dims[0] = 2; dims[1] = 1; break;
			case 2: dims[0] = 2; dims[1] = 1; break; 
			default: dims[0] = 0; dims[1] = 0; break;
		}
	}
	virtual void* getStore(int indx, int i){
		switch(indx){
			case 0: return (void*)&((v_color[i]))[0]; 
			case 1: return (void*)&((v_scale[i]))[0]; 
			case 2: return (void*)&((v_trans[i]))[0]; 
		} return NULL; 
	}
	virtual int numStores() {return 3;}
	virtual void* mmapRead(void* addr){
		double* d = (double*)addr; 
		int i; 
		for(i=0; i<4; i++)
			m_color[i] = *d++;
		for(i=0; i<2; i++)
			m_scale[i] = *d++; 
		for(i=0; i<2; i++)
			m_trans[i] = *d++; 
		return (void*)d; 
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
	array<float,2> m_vel; //in screen units/second. 
	double* m_age; //arb. units.
	starStruct* m_v; //vertices, backing store.
	float* m_pvel; //individual point velocities for variable coherence. 
	float	m_coherence; 
	float	m_starSize; 
	GLuint	m_colorbuffer; 
	GLuint 	m_program[2]; 
	long double m_lastTime; //oh god it's been years...
	long double m_startTime; 
	bool	m_awesome = false; 
	bool	m_fade = false; 
	vector<array<float,2>> v_vel; 
	vector<float> v_coherence; 
	// we can assume that the other parts don't change during the experiment.
	
	StarField(){
		m_vel[0] = 0.2f; 
		m_vel[1] = 0.1f; 
		m_v = NULL; 
		m_pvel = NULL; 
		m_age = 0; 
		m_coherence = 0.5f; 
		m_lastTime = 0.0; 
		m_starSize = 3.0; 
		m_startTime = gettime(); 
	}
	~StarField(){
		if(m_v) free(m_v); m_v = NULL;
		if(m_pvel) free(m_pvel); m_pvel = NULL;
		if(m_age) free(m_age); m_age = NULL; 
		if(m_program[0]) glDeleteProgram(m_program[0]);
		if(m_program[1]) glDeleteProgram(m_program[1]);
		v_vel.clear(); 
		v_coherence.clear(); 
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
		m_age = (double*)malloc(nstars * sizeof(double)); 
		for(int i=0; i<nstars; i++){
			m_v[i].position[0] = (uniform() - 0.5)*ar*2.f;
			m_v[i].position[1] = (uniform() - 0.5)*2.f; 
			if(m_awesome)
				m_v[i].color = (unsigned int)(255*uniform() + 255*255*uniform() + 255*255*255*uniform());
			else 
				m_v[i].color = 0xffffffff; 
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
			double d = time-m_age[i];
			int c = (int)(255.0 * 
				(-0.52 * cos(d) + 0.5)); 
			c = c > 255 ? 255: c; c = c < 0 ? 0 : c; 
			if(!m_fade){if(c) c = 255;}
			c &= 0xff; 
			m_v[i].color &= 0x00ffffff; 
			m_v[i].color += (c << 24); 
			// if it's completely transparent, update the position. 
			if(d > PI*2.0){
				m_age[i] += PI*2.0; 
				for(int j=0; j<2; j++){
					float f = (uniform() - 0.5)*a[j]*2.f;
					m_v[i].position[j] = f;
				}
				if(m_awesome){
					m_v[i].color = (unsigned int)(255*uniform() + 255*255*uniform() + 255*255*255*uniform());
					m_v[i].color &= 0xffff5fff; //debug!  you should not see this.
				} else {
					m_v[i].color = 0x00ffffff; 
				}
			}
		}
		m_lastTime = time; 
	}
	void draw(int index){
		//this is a little more complicated, as we need to do a memcpy and user shaders.
		glPointSize(m_starSize); 
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
	void setVel(double x, double y){ m_vel[0] = x; m_vel[1] = y; }
	void setCoherence(double c){ m_coherence = c; }
	void setStarSize(double ss){ m_starSize = ss;}
	void setAwesome(bool s){ 
		m_awesome = s; 
		if(s){ m_starSize = 30.0; m_fade = true; }
	}
	void setFade(bool s){ m_fade = s; }
	// serialization
	void store(){
		Shape::store(); 
		v_vel.push_back(m_vel); 
		v_coherence.push_back(m_coherence); 
	}
	string storeName(int indx){
		if(indx < Shape::numStores()){
			return Shape::storeName(indx); 
		}else{
			indx -= Shape::numStores(); 
			switch(indx){
				case 0: return string("vel"); 
				case 1: return string("coherence"); 
			} return string("none"); 
		}
	}
	int getStoreClass(int indx){
		if(indx < Shape::numStores()){
			return Shape::getStoreClass(indx); 
		}else{
			indx -= Shape::numStores(); 
			switch(indx){
				case 0: return MAT_C_SINGLE; 
				case 1: return MAT_C_SINGLE; 
			} return 0; 
		}
	}
	void getStoreDims(int indx, size_t* dims){
		if(indx < Shape::numStores()){
			Shape::getStoreDims(indx, dims); 
		}else{
			indx -= Shape::numStores(); 
			switch(indx){
				case 0: dims[0] = 2; dims[1] = 1; break; 
				case 1: dims[0] = 1; dims[1] = 1; break; 
			}
		}
	}
	void* getStore(int indx, int i){
		if(indx < Shape::numStores()){
			return Shape::getStore(indx, i); 
		}else{
			indx -= Shape::numStores(); 
			switch(indx){
				case 0: return (void*)&((v_vel[i]))[0]; 
				case 1: return (void*)&((v_coherence[i]));
			} return NULL; 
		}
	}
	int numStores() { return Shape::numStores() + 2; }
	void* mmapRead(void* addr){
		void* b = Shape::mmapRead(addr); 
		double* d = (double*)b; 
		for(int i=0; i<2; i++)
			m_vel[i] = *d++; 
		m_coherence = *d++; 
		return (void*)d; 
	}
};
#endif
