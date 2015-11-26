#include "../../include/Shape/magneticField.h"
#include "random.h"

float norm(float a, float b)
{
	return sqrtf(a*a + b*b);
}

void generateUniqueNumbers( set<int> *ln, int min, int max, int n)
{
	while ( ln->size() < n ) {
		ln->insert( rand()%max + min );
	}
}

MagneticField::MagneticField() : Shape()
{
	m_v = NULL;
	m_ghost_targets = NULL;
	m_is_coherent = NULL;
	m_clockwise = NULL;
	m_num_compasses = 0;
	m_coherence = 1.0f;
	m_compass_l = 0.02f;
	m_target[0] = 0.0f;
	m_target[1] = 0.0f;
	m_ptarget[0] = 0.0f;
	m_ptarget[1] = 0.0f;
	m_name = string {"magnetic"};
}

MagneticField::~MagneticField()
{
	freeMemory();
}

void MagneticField::freeMemory()
{
	if (m_v) free(m_v);
	if (m_ghost_targets) free(m_ghost_targets);
	if (m_is_coherent) free(m_is_coherent);
	if (m_clockwise) free(m_clockwise);
	m_v = NULL;
	m_ghost_targets = NULL;
	m_is_coherent = NULL;
	m_clockwise = NULL;
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
	freeMemory();

	m_num_compasses = nCompasses;

	float ratio = m_scale[0]/m_scale[1];
	int ncolumns = ceil(sqrt(nCompasses * ratio) ) ;
	int nrows = ceil(sqrt(nCompasses / ratio) ) ;

	m_v = (Compass *)malloc(2*nrows*ncolumns*sizeof(Compass)); // 2 points each
	m_ghost_targets = (float *)malloc(2*nrows*ncolumns*sizeof(double));
	m_is_coherent = (bool *)malloc(nrows*ncolumns*sizeof(bool));
	m_clockwise = (bool *)malloc(nrows*ncolumns*sizeof(bool));

	float i = 0;
	for (int k=0; k < ncolumns; k++) {
		float j = 0;
		for (int l = 0; l < 2*nrows ; l+=2) {
			// first point in line
			m_v[(int)(k*2*nrows) + l].x = i;
			m_v[(int)(k*2*nrows) + l].y = j;
			m_v[(int)(k*2*nrows) + l].color = 0xffffffff;
			// second point in line
			m_v[(int)(k*2*nrows) + l + 1].x = i;
			m_v[(int)(k*2*nrows) + l + 1].y = j;
			m_v[(int)(k*2*nrows) + l + 1].color = 0xffffffff;

			j += 1/(double)nrows;
		}
		i += 1/(double)ncolumns;
	}

	// now compute and remove the mean position of the line array
	// to center it on the screen
	// note that at first both the x and y have the same value (the center)
	// later we make them a true line
	float xmean = 0.5 * (m_v[2*ncolumns*nrows-1].x + m_v[0].x);
	float ymean = 0.5 * (m_v[2*ncolumns*nrows-1].y + m_v[0].y);

	for (int i(0); i < 2*nrows * ncolumns; ++i) {
		m_v[i].x -= xmean;
		m_v[i].y -= ymean;
		m_ghost_targets[i] = 0.0;
		m_clockwise[i/2] = uniform() > 0.5;
	}

	m_n = 2 * nrows * ncolumns;

	setCoherence(m_coherence);

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
	if (!m_v || !m_ghost_targets) return;

	unsigned int basecol = 0;
	basecol += (unsigned int)(m_color[3] * 255) & 255;
	basecol <<= 8;
	basecol += (unsigned int)(m_color[2] * 255) & 255;
	basecol <<= 8;
	basecol += (unsigned int)(m_color[1] * 255) & 255;
	basecol <<= 8;
	basecol += (unsigned int)(m_color[0] * 255) & 255;

	float dposition[2];
	dposition[0] = m_target[0] - m_ptarget[0];
	dposition[1] = m_target[1] - m_ptarget[1];
	m_ptarget[0] 	= m_target[0];
	m_ptarget[1] 	= m_target[1];

	for (int i(0); i<m_n; i+=2) {
		float the_target[2];
		if (!m_is_coherent[i/2]) {
			if (m_clockwise[i/2]) {
				m_ghost_targets[i] += dposition[0];
				m_ghost_targets[i+1] += dposition[1];
			} else {
				m_ghost_targets[i] -= dposition[0];
				m_ghost_targets[i+1] -= dposition[1];
			}
			the_target[0] = m_ghost_targets[i];
			the_target[1] = m_ghost_targets[i+1];
		} else {
			the_target[0] = m_target[0];
			the_target[1] = m_target[1];
		}

		double x = 0.5 * (m_v[i].x + m_v[i+1].x) - (the_target[0]-m_trans[0])/m_scale[0];
		double y = 0.5 * (m_v[i].y + m_v[i+1].y) - (the_target[1]-m_trans[1])/m_scale[1];

		double angle = atan2(y, x); // atan2(y, x) or atan2(sin, cos)
		if (abs(x) < EPS && abs(y) < EPS) { // XXX do we still need this?
			angle = 0.0;
		}

		// we scale the length of the compas by the  xxx
		float cx = 0.5 * (m_v[i].x + m_v[i+1].x);
		float cy = 0.5 * (m_v[i].y + m_v[i+1].y);

		m_v[i].x 	= cx - (0.5*m_compass_l/m_scale[0]) * cos(angle);
		m_v[i].y 	= cy - (0.5*m_compass_l/m_scale[1]) * sin(angle);

		m_v[i+1].x 	= cx + (0.5*m_compass_l/m_scale[0]) * cos(angle);
		m_v[i+1].y 	= cy + (0.5*m_compass_l/m_scale[1]) * sin(angle);

		m_v[i].color = basecol;
		m_v[i+1].color = basecol;
	}
}

void MagneticField::draw(int display, float ar)
{
	configure(display);
	//this is a little more complicated, as we need to do a memcpy and user shaders.
	if ((m_draw & (1<<display)) && m_v ) {
		glLineWidth(1.0f);
		setupDrawMatrices(display, ar);

		glBindVertexArray(m_vao[display]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo[display]); // Bind our Vertex Buffer Object
		glBufferData(GL_ARRAY_BUFFER, m_n*sizeof(Compass), m_v, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Compass), 0);
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Compass), (void *)8);

		glDrawArrays(m_drawmode, 0, m_n);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glUseProgram(0);
	}
}

// serialization
void MagneticField::clear()
{
	Shape::clear();
	v_coherence.clear();
	v_compass_l.clear();
	v_target.clear();
}

bool MagneticField::store()
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
			same &= (m_target[i] == (v_target[n-1])[i]);
		}
		same &= (m_rot == (v_rot[n-1]));
		same &= (m_coherence == v_coherence[n-1]);
		same &= (m_compass_l == v_compass_l[n-1]);
	} else same = false;
	if (!same) {
		v_time.push_back(m_time);
		v_draw.push_back(m_draw);
		v_color.push_back(color);
		v_scale.push_back(m_scale);
		v_trans.push_back(m_trans);
		v_rot.push_back(m_rot);

		v_coherence.push_back(m_coherence);
		v_target.push_back(m_target);
		v_compass_l.push_back(m_compass_l);
	}
	return !same;
}

string MagneticField::storeName(int indx)
{
	switch (indx) {
	case 0:
		return m_name + string("coherence");
	case 1:
		return m_name + string("compassL");
	case 2:
		return m_name + string("target");
	}
	return Shape::storeName(indx - 3);
}

int MagneticField::getStoreClass(int indx)
{
	switch (indx) {
	case 0:
		return MAT_C_SINGLE;
	case 1:
		return MAT_C_SINGLE;
	case 2:
		return MAT_C_SINGLE;
	}
	return Shape::getStoreClass(indx - 3);
}

void MagneticField::getStoreDims(int indx, size_t *dims)
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
		dims[0] = 2;
		dims[1] = 1;
		return;
	}
	return Shape::getStoreDims(indx-3, dims);
}

void *MagneticField::getStore(int indx, int i)
{
	switch (indx) {
	case 0:
		return (void *)&((v_coherence[i]));
	case 1:
		return (void *)&((v_compass_l[i]));
	case 2:
		return (void *)&((v_target[i]));
	}
	return Shape::getStore(indx-3, i);
}

int MagneticField::numStores()
{
	return Shape::numStores() + 3;
}

double *MagneticField::mmapRead(double *d)
{
	float c = *d++;
	if (c != m_coherence) {
		setCoherence(c);
	}
	setLinesLength(*d++);
	setTarget(d);

	// see the base shape mmap read
	// we are duplicating it's functionality
	// but overriding scaling

	m_time = gettime();
	*d++ = m_time;
	m_draw = (char)floor(*d++);
	for (int i(0); i<4; i++)
		m_color[i] = *d++;

	float scale_x, scale_y;
	scale_x = *d++;
	scale_y = *d++;
	if ((abs(scale_x - m_scale[0]) > EPS) ||
	    (abs(scale_y - m_scale[1]) > EPS)) {
		m_scale[0] = scale_x;
		m_scale[1] = scale_y;
		makeCompasses(m_num_compasses);
	}

	for (int i(0); i<2; i++)
		m_trans[i] = *d++;
	m_rot = *d++;
	return d;

	return Shape::mmapRead(d);
}

void MagneticField::setTarget(double *(&target))
{
	m_target[0] 	= (*target++);
	m_target[1] 	= (*target++);
}

void MagneticField::setCoherence(float coherence)
{
	if (coherence < 0) {
		m_coherence = 0.f;
	} else if (coherence > 1) {
		m_coherence = 1.f;
	} else {
		m_coherence = coherence;
	}

	set<int> index;
	generateUniqueNumbers(&index, 0, m_n / 2, (int)((1.0f - m_coherence) * m_n / 2));
	if (index.size() != 0) {
		std::set<int>::iterator it = index.begin();
		for (int i(0); i < m_n; i+=2) {
			if (i == 2*(*it)) {
				m_is_coherent[i/2] = false;
				m_ghost_targets[i] = m_scale[0]/2.f - uniform() * m_scale[0] + m_trans[0];
				m_ghost_targets[i+1] = m_scale[1]/2.f - uniform() * m_scale[1] + m_trans[1];
				++it;
			} else {
				m_is_coherent[i/2] = true;
				m_ghost_targets[i] = 0;
				m_ghost_targets[i+1] = 0;
			}
		}
	} else {
		for (int i(0); i < m_n; ++i) {
			m_is_coherent[i/2] = true;
			m_ghost_targets[i] = 0;
		}
	}
}

void MagneticField::setLinesLength(float length)
{
	m_compass_l = length < 0 ? 0 : length;
}
