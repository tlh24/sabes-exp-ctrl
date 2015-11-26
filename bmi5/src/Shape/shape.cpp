#include "../../include/Shape/shape.h"

float norm(float a, float b)
{
	return sqrtf(a*a + b*b);
}
Shape::Shape(void) : Serialize()
{
	m_vao[0] = m_vao[1] = 0;
	m_vbo[0] = m_vbo[1] = 0;
	m_color[0] = m_color[1] = m_color[2] = m_color[3] = 1.f;
	m_scale[0] = m_scale[1] = 1.f;
	m_trans[0] = m_trans[1] = 0.f;
	m_rot = 0.0;
	m_name = "shape";
	m_needConfig[0] = m_needConfig[1] = false;
	m_program[0] = m_program[1] = 0;
	m_draw = 0;
#ifdef DEBUG
	m_draw = 3; //default to 'on'
#endif
}
void Shape::deleteBuffers()
{
	for (int i=0; i<2; i++) {
		if (m_vbo[i]) glDeleteBuffers(1, &(m_vbo[i]));
		m_vbo[i] = 0;
		if (m_vao[i]) glDeleteVertexArrays(1, &(m_vao[i]));
		m_vao[i] = 0;
	}
}
Shape::~Shape()
{
	//if(m_program[0]) glDeleteProgram(m_program[0]); m_program[0] = 0;
	//if(m_program[1]) glDeleteProgram(m_program[1]); m_program[1] = 0;
	//deleteBuffers(); -- must be called within the OpenGL context in which they were created.
	v_color.clear();
	v_scale.clear();
	v_trans.clear();
}
void Shape::makeVAO(float *vertices, bool del, int display)
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
void Shape::makeShader(int index, GLenum type, std::string source)
{
	GLuint shader = glCreateShader(type);
	int length = source.size();
	const char *str = source.c_str();
	glShaderSource(shader, 1, (const char **)&str, &length);
	glCompileShader(shader);
	GLint result; /* make sure the compilation was successful */
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		char *log = (char *)malloc(length);
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
std::string Shape::fileToString(const char *fname)
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
void Shape::makeShadersNamed(int index, const char *vertexName, const char *fragmentName)
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
		/* delete the program */
		glDeleteProgram(m_program[index]);
		m_program[index] = 0;
	}
}
void Shape::makeShaders(int index)
{
	string vertex   = g_basedirname + "/glsl/" + "vertex_flatcolor.glsl";
	string fragment = g_basedirname + "/glsl/" + "fragment.glsl";
	makeShadersNamed(index, vertex.c_str(), fragment.c_str());
}
void Shape::fill(float *v)
{
	for (int i=0; i<m_n; i++) {
		v[i*2+0] = i&1;
		v[i*2+1] = (i>>1)&1;
	}
}
void Shape::configure(int display)
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
void Shape::setupDrawMatrices(int display, float)
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
void Shape::draw(int display, float ar)
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
void Shape::move(long double) {} //no velocity here.
///serialization.
unsigned char Shape::floatToU8(float in)
{
	in *= 255;
	in = in > 255.f ? 255.f : in;
	in = in < 0.f ? 0.f : in;
	return (unsigned char)in;
}
void Shape::clear()
{
	v_time.clear();
	v_color.clear();
	v_scale.clear();
	v_trans.clear();
	v_rot.clear();
}
bool Shape::store()
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
int Shape::nstored()
{
	return v_time.size();
}
string Shape::storeName(int indx)
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
int Shape::getStoreClass(int indx)
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
void Shape::getStoreDims(int indx, size_t *dims)
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
void *Shape::getStore(int indx, int i)
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
int Shape::numStores()
{
	return 6;
}
double *Shape::mmapRead(double *d)
{
	m_time = gettime();
	*d++ = m_time;
	m_draw = (char)floor(*d++);
	for (int i=0; i<4; i++)
		m_color[i] = *d++;
	for (int i=0; i<2; i++)
		m_scale[i] = *d++;
	for (int i=0; i<2; i++)
		m_trans[i] = *d++;
	m_rot = *d++;
	return d;
}
