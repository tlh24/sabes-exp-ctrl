#include "../../include/Shape/magneticField.h"



float norm(float a, float b)
{
	return sqrtf(a*a + b*b);
}

void generateUniqueNumbers( set<int> *ln, int min, int max, int n){
	while( ln->size() < n ){
		ln->insert( rand()%max + min );
	}
}


MagneticField::MagneticField() : Shape()
{
	m_v = NULL;
	m_phase = NULL;
	m_coherence = 1.0f;
	m_compass_l = 0.02f;
	m_target[0] = 0.0f;
	m_target[1] = 0.0f;
	m_name = string {"magnetic"};
}

MagneticField::~MagneticField()
{
	if (m_v) free(m_v);
	m_v = NULL;
	if (m_phase) free(m_phase);
	m_phase = NULL;
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
	if (m_v) free(m_v);
	if (m_phase) free(m_phase);
	m_v = NULL;
	m_phase = NULL;
	
	int width(1);
	int height(1);
	gtk_window_get_size ((GtkWindow *)g_subjectWindow, &width, &height);
	float ratio = width/(double)height;
	
	int ncolumns = ceil(sqrt(nCompasses * ratio) ) ;
	int nrows = ceil(sqrt(nCompasses / ratio) ) ;
	m_v = (Compass *)malloc(2 * nrows * ncolumns * sizeof(Compass));
	m_phase = (double *)malloc(nrows * ncolumns * sizeof(double));
	int size = 2;
	float offset = 1/sqrt(nCompasses) / 2 - 0.5f*size;

	std::cerr << "Ratio : "<< ratio << std::endl;
	
	float i = offset;
	for (int k=0; k < ncolumns ; k += 1) {
		float j = offset;
		for(int l = 0; l < 2 * nrows ; l += 2){
			m_v[(int)(k*2*nrows) + l].x1 = i;
			m_v[(int)(k*2*nrows) + l].y1 = j;
			m_v[(int)(k*2*nrows) + l].color1 = 0xffffffff;
			m_v[(int)(k*2*nrows) + l + 1].x1 = i;
			m_v[(int)(k*2*nrows) + l + 1].y1 = j;
			m_v[(int)(k*2*nrows) + l + 1].color1 = 0xffffffff;
			
			j += size/(double)nrows;
		}
		i += size/(double)ncolumns;
	}
	for(int i(0); i < nrows * ncolumns; ++i){
		m_phase[i] = 0; 
	}
	m_n = 2 * nrows * ncolumns;
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
	if (!m_v || !m_phase) return;
	
	unsigned int basecol = 0;
	basecol += (unsigned int)(m_color[3] * 255) & 255;
	basecol <<= 8;
	basecol += (unsigned int)(m_color[2] * 255) & 255;
	basecol <<= 8;
	basecol += (unsigned int)(m_color[1] * 255) & 255;
	basecol <<= 8;
	basecol += (unsigned int)(m_color[0] * 255) & 255;
	int width(1);
	int height(1);
	gtk_window_get_size ((GtkWindow *)g_subjectWindow, &width, &height);
	float ratio = width/(double)height;
	
	for (int i=0; i<m_n; i += 2) {
		double angle;
		if(m_phase[i/2] > 0){
			angle = m_phase[i/2];
		}
		else{
			double x2 = 0.5 * (m_v[i].x1 + m_v[i+1].x1) - m_target[0];
			double y2 = 0.5 * (m_v[i].y1 + m_v[i+1].y1) - m_target[1];
			angle = atan2(y2, x2);  	// atan2(y, x) or atan2(sin, cos)
		}

		m_v[i].x1 = 0.5 * (m_v[i].x1 + m_v[i+1].x1 - m_compass_l / ratio * cos(angle));
		m_v[i].y1 = 0.5 * (m_v[i].y1 + m_v[i+1].y1 - m_compass_l * sin(angle));
		m_v[i+1].x1 = 0.5 * (m_v[i].x1 + m_v[i+1].x1 + m_compass_l / ratio * cos(angle));
		m_v[i+1].y1 = 0.5 * (m_v[i].y1 + m_v[i+1].y1 + m_compass_l * sin(angle));
		m_v[i].color1 = basecol;
		m_v[i+1].color1 = basecol;
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

void* MagneticField::getStore(int indx, int i)
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

double* MagneticField::mmapRead(double *d)
{
	setCoherence(*d++);
	m_compass_l = *d++;
	for (int i=0; i<2; i++)
		m_target[i] = *d++;
		
	return Shape::mmapRead(d);
}

void MagneticField::setCoherence(float coherence)
{	
	if(coherence != m_coherence){
		if(coherence < 0){
			m_coherence = 0.f;
		}
		else{
			m_coherence = coherence;
		}
		set<int> index;
		generateUniqueNumbers(&index, 0, m_n / 2, (int)((1.0f - m_coherence) * m_n / 2));
		if(index.size() != 0){
			std::set<int>::iterator it = index.begin();
			for(int i(0); i < m_n / 2; ++i){
				if(i == *it){
					m_phase[i] = rand() / (double)RAND_MAX * M_PI;
					++it;
				}
				else{
					m_phase[i] = 0;
				}
			}
		}
		else{
			for(int i(0); i < m_n / 2; ++i){
				m_phase[i] = 0;
			}
		}
	}
}

void MagneticField::setTarget(float* target)
{
	m_target[0] = target[0];
	m_target[1] = target[1];
}

void MagneticField::setLinesLength(float length)
{
	if(length < 0){
		m_compass_l = 0;
	}
	else{
		m_compass_l = length;
	}
}
