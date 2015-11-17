#include "../../include/Shape/starField.h"

StarField::StarField() : Shape()
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
StarField::~StarField()
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
void StarField::makeVAO(starStruct *vertices, bool del, int display)
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
float StarField::uniform()
{
	return ((float)rand() / (float)RAND_MAX);
}
float StarField::norm(float a, float b)
{
	return sqrtf(a*a + b*b);
}
void StarField::makeStars(int nstars)
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
void StarField::makeShaders(int index)
{
	string vertex   = g_basedirname + "/glsl/" + "vertex.glsl";
	string fragment = g_basedirname + "/glsl/" + "fragment.glsl";
	makeShadersNamed(index, vertex.c_str(), fragment.c_str());
}
void StarField::configure(int display)
{
	if (m_needConfig[display]) {
		makeVAO(m_v, false, display); //keep around the b.s.
		makeShaders(display);
		m_needConfig[display] = false;
	}
}
void StarField::move(long double time)
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
void StarField::draw(int display, float ar)
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
void StarField::setVel(double x, double y)
{
	m_vel[0] = x;
	m_vel[1] = y;
}
void StarField::setCoherence(double c)
{
	if (c < 0) {
		m_coherence = 0.f;
	} else {
		m_coherence = c;
	}
}
void StarField::setLifetime(double x)
{
	if (x < 0) {
		m_lifetime = 0.f;
	} else {
		m_lifetime = x;
	}
}
void StarField::setStarSize(double ss)
{
	if (ss < 0) {
		m_starsize = 0;
	} else {
		m_starsize = ss;
	}
}
// serialization
void StarField::clear()
{
	Shape::clear();
	v_vel.clear();
	v_coherence.clear();
	v_lifetime.clear();
	v_starsize.clear();
}
bool StarField::store()
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
string StarField::storeName(int indx)
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
int StarField::getStoreClass(int indx)
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
void StarField::getStoreDims(int indx, size_t *dims)
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
void *StarField::getStore(int indx, int i)
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
int StarField::numStores()
{
	return Shape::numStores() + 4;
}
double *StarField::mmapRead(double *d)
{
	for (int i=0; i<2; i++)
		m_vel[i] = *d++;
	setCoherence(*d++);
	setLifetime(*d++);
	setStarSize(*d++);
	return Shape::mmapRead(d);
}
