// class for drawing shapes via opengl.
#ifndef __SHAPE_H__
#define __SHAPE_H__

extern Matrix44Serialize*	g_affine44; //used for translating world->screen coordinates.
extern Matrix44Serialize*	g_quadratic44;

#define PI 3.141592653589793
class Shape : public Serialize {
	public:
		bool	m_needConfig[2]; 
		int 	m_n; 
		unsigned int m_vao[2]; 
		unsigned int m_vbo[2]; 
		unsigned int m_drawmode; 
		char			m_draw; 
		GLuint 		m_program[2]; 
		array<float,4>	m_color;
		array<float,2> m_scale; 
		array<float,2> m_trans;
		vector<char> v_draw; 
		vector<array<unsigned char,4>> v_color; 
		vector<array<float,2>> v_scale; 
		vector<array<float,2>> v_trans; 
	Shape(void) : Serialize(){
		m_vao[0] = m_vao[1] = 0; 
		m_vbo[0] = m_vbo[1] = 0; 
		m_color[0] = m_color[1] = m_color[2] = m_color[3] = 1.f; 
		m_scale[0] = m_scale[1] = 1.f; 
		m_trans[0] = m_trans[1] = 0.f; 
		m_name = {"shape_"}; 
		m_needConfig[0] = m_needConfig[1] = false; 
		m_program[0] = m_program[1] = 0; 
		m_draw = 0; 
#ifdef DEBUG
		m_draw = 1; 
#endif
	}
	void deleteBuffers(){
		for(int i=0; i<2; i++){
			if(m_vbo[i]) glDeleteBuffers(1, &(m_vbo[i])); m_vbo[i] = 0; 
			if(m_vao[i]) glDeleteVertexArrays(1, &(m_vao[i])); m_vao[i] = 0; 
		}
	}
	~Shape(){
		if(m_program[0]) glDeleteProgram(m_program[0]);
		if(m_program[1]) glDeleteProgram(m_program[1]);
		deleteBuffers(); 
		v_color.clear(); 
		v_scale.clear(); 
		v_trans.clear();
	}
	virtual void makeVAO(float* vertices, bool del, int display){
		if(m_n > 0){
			glGenVertexArrays(1, &(m_vao[display])); // Create our Vertex Array Object
			glBindVertexArray(m_vao[display]); // Bind our Vertex Array Object so we can use it
			glGenBuffers(1, &(m_vbo[display])); // Generate our Vertex Buffer Object
			// VBOs are children of VAOs, apparently.
			
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo[display]); // Bind our Vertex Buffer Object
			glBufferData(GL_ARRAY_BUFFER, m_n*2*sizeof(GLfloat), vertices, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
			glVertexAttribPointer((GLuint)0, 2, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
			
			glEnableVertexAttribArray(0); 
			glBindVertexArray(0); 
			if(del) free(vertices);
		}else{
			printf("error: makeVAO: m_n < 0\n"); 	
		}
	}
	void makeShader(int index, GLenum type, std::string source){
		GLuint shader = glCreateShader(type);
		int length = source.size();
		const char* str = source.c_str();
		glShaderSource(shader, 1, (const char **)&str, &length);
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
	std::string fileToString(const char* fname){
		std::ifstream t(fname); //yay stackoverflow!!
		std::string str;
		t.seekg(0, std::ios::end);   
		str.reserve(t.tellg());
		t.seekg(0, std::ios::beg);
		str.assign((std::istreambuf_iterator<char>(t)),
						std::istreambuf_iterator<char>());
		return str; 
	}
	void makeShadersNamed(int index, const char* vertexName, const char* fragmentName){
		m_program[index] = glCreateProgram();
		makeShader(index, GL_VERTEX_SHADER, fileToString(vertexName)); 
		makeShader(index, GL_FRAGMENT_SHADER, fileToString(fragmentName)); 
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
	virtual void makeShaders(int index){
		makeShadersNamed(index, "vertex_flatcolor.glsl", "fragment.glsl"); 
	}
	void makeCircle(int n){
		m_n = n+1; 
		m_needConfig[0] = m_needConfig[1] = true; 
	}
	virtual void configure(int display){
		if(m_needConfig[display]){
			printf("Shape: configuring display [%d]\n", display); 
			//makes a circle, diameter 1, at the origin.
			float* v = (float*)malloc((m_n)*sizeof(float)*2); 
			v[0] = 0.f; 
			v[1] = 0.f; 
			for(int i=0; i<m_n-1; i++){
				float t = (float)i * PI * 2 / (m_n-2); 
				v[i*2+2] = 0.5f*sinf(t); 
				v[i*2+3] = 0.5f*cosf(t); 
			}
			makeVAO(v, true, display); 
			makeShaders(display); 
			m_drawmode = GL_TRIANGLE_FAN; 
			m_needConfig[display] = false; 
		}
	}
	void setupDrawMatrices(int display){
		//first pre-multiply the local->world with the world->screen matrix. 
		float m[4][4]; //world matrix.
		for(int i=0; i<16; i++) m[0][i] = 0.f; 
		m[0][3] = m_trans[0]; 
		m[1][3] = m_trans[1]; 
		m[0][0] = m_scale[0]; 
		m[1][1] = m_scale[1]; 
		m[2][2] = m[3][3] = 1.f; 
		float n[4][4]; 
		float* aff = g_affine44->data(); 
		// n = affine * world (in that order!)
		for(int r=0; r<4; r++){
			for(int c=0; c<4; c++){
				float f = 0.f; 
				for(int i=0; i<4; i++)
					//g_affine in matlab order.
					f += aff[r+4*i] * m[i][c]; 
				n[c][r] = f; //opengl assumes fortran order (like matlab), hence transpose.
			}
		}
		//quadratic matrix from matlab -- already transposed.
		glUseProgram(m_program[display]); 
		int affloc = glGetUniformLocation(m_program[display], "affine_matrix"); 
		if(affloc >= 0)glUniformMatrix4fv(affloc, 1, GL_FALSE, &n[0][0]);
		int quadloc = glGetUniformLocation(m_program[display], "quadratic_matrix"); 
		if(quadloc >= 0)glUniformMatrix4fv(quadloc, 1, GL_FALSE, g_quadratic44->data());
	}
	virtual void draw(int display){
		configure(display); //if we need it.
		if(m_draw){
			setupDrawMatrices(display); 
			int colorloc = glGetUniformLocation(m_program[display], "uniform_color"); 
			if(colorloc >= 0)glUniform4f(colorloc, m_color[0], m_color[1], m_color[2], m_color[3]);
			
			glBindVertexArray(m_vao[display]);
			glDrawArrays(m_drawmode, 0, m_n);  
			glBindVertexArray(0);
		}
	}
	virtual void move(float, long double){} //no velocity here.
	void enable(bool d){
		if(d) m_draw = 1; else m_draw = 0; 
	}
	void translate(float x, float y){ //in real-world coordinates. 
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
	virtual void clear(){
		v_color.clear();
		v_scale.clear(); 
		v_trans.clear(); 
	}
	virtual void store(){
		v_draw.push_back(m_draw); 
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
			case 0: return m_name + string("draw"); 
			case 1: return m_name + string("color");
			case 2: return m_name + string("scale");
			case 3: return m_name + string("trans");
		} return string("none"); 
	}
	virtual int getStoreClass(int indx){
		switch(indx){ 
			case 0: return MAT_C_INT8; 
			case 1: return MAT_C_UINT8;
			case 2: return MAT_C_SINGLE;
			case 3: return MAT_C_SINGLE;
		} return 0; 
	}
	virtual void getStoreDims(int indx, size_t* dims){
		switch(indx){
			case 0: dims[0] = 1; dims[1] = 1; break; 
			case 1: dims[0] = 4; dims[1] = 1; break; 
			case 2: dims[0] = 2; dims[1] = 1; break;
			case 3: dims[0] = 2; dims[1] = 1; break; 
			default: dims[0] = 0; dims[1] = 0; break;
		}
	}
	virtual void* getStore(int indx, int i){
		switch(indx){
			case 0: return (void*)&((v_draw[i])); 
			case 1: return (void*)&((v_color[i])[0]); 
			case 2: return (void*)&((v_scale[i])[0]); 
			case 3: return (void*)&((v_trans[i])[0]); 
		} return NULL; 
	}
	virtual int numStores() {return 4;}
	virtual double* mmapRead(double* d){
		int i; 
		m_draw = *d++ > 0.0 ? 1 : 0; 
		for(i=0; i<4; i++)
			m_color[i] = *d++;
		for(i=0; i<2; i++)
			m_scale[i] = *d++; 
		for(i=0; i<2; i++)
			m_trans[i] = *d++; 
		return d; 
	}
};
struct starStruct {
	float	position[2]; 
	unsigned int color; 
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
	long double m_lastTime; //oh god it's been years...
	long double m_startTime; 
	bool	m_awesome = false; 
	bool	m_fade = false; 
	vector<array<float,2>> v_vel; 
	vector<float> v_coherence; 
	// we can assume that the other parts don't change during the experiment.
	
	StarField() : Shape() {
		m_vel[0] = 0.2f; 
		m_vel[1] = 0.1f; 
		m_v = NULL; 
		m_pvel = NULL; 
		m_age = 0; 
		m_coherence = 0.5f; 
		m_lastTime = 0.0; 
		m_starSize = 3.0; 
		m_startTime = gettime(); 
		m_name = string{"stars_"};
	}
	~StarField(){
		if(m_v) free(m_v); m_v = NULL;
		if(m_pvel) free(m_pvel); m_pvel = NULL;
		if(m_age) free(m_age); m_age = NULL; 
		deleteBuffers(); 
		v_vel.clear(); 
		v_coherence.clear(); 
	}
	virtual void makeVAO(starStruct* vertices, bool del, int display){
		//this method differs from Shape::makeVAO in that each vertex has a color.
		if(m_n > 0){
			glGenVertexArrays(1, &(m_vao[display])); // Create our Vertex Array Object
			glBindVertexArray(m_vao[display]); // Bind our Vertex Array Object so we can use it
			glGenBuffers(1, &(m_vbo[display])); // Generate our Vertex Buffer Object
			// VBOs are children of VAOs, apparently.
			
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo[display]); // Bind our Vertex Buffer Object
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
		m_needConfig[0] = m_needConfig[1] = true; 
		m_drawmode = GL_POINTS; 
	}
	virtual void makeShaders(int index){
		makeShadersNamed(index, "vertex.glsl", "fragment.glsl"); 
	}
	virtual void configure(int display){
		if(m_needConfig[display]){
			makeVAO(m_v, false, display); //keep around the b.s.
			makeShaders(display); 
			m_needConfig[display] = false; 
		}
	}
	virtual void move(float ar, long double time){
		//will need to update this to permit
		float dt = (float)(time - m_lastTime); 
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
			if(!m_fade){if(c) c = 255;}//saturate.
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
	virtual void draw(int display){
		configure(display); 
		//this is a little more complicated, as we need to do a memcpy and user shaders.
		if(m_draw){
			glPointSize(m_starSize); 
			setupDrawMatrices(display); 
			
			glBindVertexArray(m_vao[display]);
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo[display]); // Bind our Vertex Buffer Object
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
	virtual void clear(){
		Shape::clear(); 
		v_vel.clear(); 
		v_coherence.clear(); 
	}
	virtual void store(){
		Shape::store(); 
		v_vel.push_back(m_vel); 
		v_coherence.push_back(m_coherence); 
	}
	virtual string storeName(int indx){
		if(indx < Shape::numStores()){
			return Shape::storeName(indx); 
		}else{
			indx -= Shape::numStores(); 
			switch(indx){
				case 0: return m_name + string("vel"); 
				case 1: return m_name + string("coherence"); 
			} return string("none"); 
		}
	}
	virtual int getStoreClass(int indx){
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
	virtual void getStoreDims(int indx, size_t* dims){
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
	virtual void* getStore(int indx, int i){
		if(indx < Shape::numStores()){
			return Shape::getStore(indx, i); 
		}else{
			indx -= Shape::numStores(); 
			switch(indx){
				case 0: return (void*)&((v_vel[i])[0]); 
				case 1: return (void*)&((v_coherence[i]));
			} return NULL; 
		}
	}
	virtual int numStores() { return Shape::numStores() + 2; }
	virtual double* mmapRead(double* d){
		d = Shape::mmapRead(d); 
		for(int i=0; i<2; i++)
			m_vel[i] = *d++; 
		m_coherence = *d++; 
		return d; 
	}
};
#endif
