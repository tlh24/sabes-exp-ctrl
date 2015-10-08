/*#include "../../include/Shape/magneticField.h"

float norm(float a, float b)
{
	return sqrtf(a*a + b*b);
}


MagneticField::MagneticField() : Shape()
{
	m_vel[0] = 0.0f;
	m_vel[1] = 0.0f;
	m_v = NULL;
	m_phase = NULL;
	m_coherence = 1.0f;
	m_name = string {"magnetic"};
}

MagneticField::~MagneticField()
{
	if (m_v) free(m_v);
	m_v = NULL;
	if (m_phase) free(m_phase);
	m_phase = NULL;
}

void MagneticField::setTarget(float* target)
{
	if(sizeof(target) == 2){
		m_target[0] = target[0];
		m_target[1] = target[1];
	}
}

void MagneticField::makeVAO(Compass *vertices, bool del, int display)
{
	//this method differs from Shape::makeVAO in that each vertex has a color.
	if (m_n > 0) {
		glGenVertexArrays(1, &(m_vao[display])); // Create our Vertex Array Object
		glBindVertexArray(m_vao[display]); // Bind our Vertex Array Object so we can use it
		glGenBuffers(1, &(m_vbo[display])); // Generate our Vertex Buffer Object
		// VBOs are children of VAOs, apparently.

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo[display]); // Bind our Vertex Buffer Object
		glBufferData(GL_ARRAY_BUFFER, m_n*sizeof(Compass), vertices, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
		glVertexAttribPointer((GLuint)0, 2, GL_FLOAT, GL_FALSE, sizeof(Compass), 0); // Set up our vertex attributes pointer
		glVertexAttribPointer((GLuint)1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Compass), (void *)8);

		glEnableVertexAttribArray(0); // enable our Vertex Array Object
		glEnableVertexAttribArray(1); // enable our Vertex Array Object
		glBindVertexArray(0); // disable the VBA.

		glBindBuffer(GL_ARRAY_BUFFER, 0); //disable the VBO.
		if (del) free(vertices);
	} else {
		printf("error: makeVAO: m_n < 0\n");
	}
}

void MagneticField::makeCompasses(int nCompasses)
{
	GLint m_viewport[4];
	glGetIntegerv( GL_VIEWPORT, m_viewport );
	printf("Size : %f , %f, %f, %f",m_viewport[0],m_viewport[1],m_viewport[2],m_viewport[3]);
	if (m_v) free(m_v);
	m_v = NULL;
	m_v = (starStruct *)malloc(nCompasses * sizeof(starStruct));
	m_phase = (double *)malloc(nCompasses * sizeof(double));
	int k = 0;
	for (double i=0; i<1; i+=1/sqrt(nCompasses)) {
		int l = 0;
		for(double j = 0 j < 1; j += 1/sqrt(nCompasses)){
			m_v[round(k*sqrt(nCompasses)) + l].position[0] = i;
			m_v[round(k*sqrt(nCompasses)) + l].position[1] = j;
			m_v[round(k*sqrt(nCompasses)) + l].color = 0xffffffff;
			m_phase[i] = 1;
		}
	}
	m_n = nCompasses;
	m_needConfig[0] = m_needConfig[1] = true;
	m_drawmode = GL_LINES;
}
void MagneticField::makeShaders(int index)
{
	string vertex   = g_basedirname + "/glsl/" + "vertex.glsl";
	string fragment = g_basedirname + "/glsl/" + "fragment.glsl";
	makeShadersNamed(index, vertex.c_str(), fragment.c_str());
}

void MagneticField::configure(int display)
{
	if (m_needConfig[display]) {
		makeVAO(m_v, false, display); //keep around the b.s.
		makeShaders(display);
		m_needConfig[display] = false;
	}
}

void MagneticField::move(long double time)
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

	int k = (int)floor(m_n * m_coherence);
	for (int i=0; i<m_n; i++) {
		double angle;
		if(m_phase[i] != 0){
			angle = m_phase[i];
		}
		else{
			double x2 = 0.5*(m_v[i].position[0] + m_v[i].position[2]);
			double y2 = 0.5*(m_v[i].position[1] + m_v[i].position[3]);
			dot = x1*x2 + y1*y2     // dot product
			det = x1*y2 - y1*x2     // determinant
			angle = atan2(y2, x2)  	// atan2(y, x) or atan2(sin, cos)
		}
		m_v[i].position[0] = -0.5f * m_l * cos(angle);
		m_v[i].position[1] = -0.5f * m_l * sin(angle);
		m_v[i].position[2] = 0.5f * m_l * cos(angle);
		m_v[i].position[3] = 0.5f * m_l * sin(angle);
	}
}

void MagneticField::draw(int display, float ar)
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
}*/
