#include "../../include/Shape/starFieldCircle.h"
#include "random.h"

StarFieldCircle::StarFieldCircle() {}
StarFieldCircle::~StarFieldCircle() {}
void StarFieldCircle::makeStars(int nstars)
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

		// draw uniformly in a circle with radius 0.5
		float x = uniform()*PI*2.f;
		float u = uniform()+uniform();
		float r = u > 1 ? 2-u : u;
		m_v[i].position[0] = 0.5f*r*cosf(x);
		m_v[i].position[1] = 0.5f*r*sinf(x);

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

void StarFieldCircle::move(long double time)
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

		float p[2];
		for (int j=0; j<2; j++) {
			p[j] = m_v[i].position[j];
			float v;
			if (i<k)	// coherent stars
				v = scaled_vel[j];
			else 		// random stars
				v = m_pvel[i*2+j] * speed;
			p[j] += v * dt;
		}
		float r = norm(m_v[i].position[0], m_v[i].position[1]);
		if (r > 0.5 && speed > 0) {
			float angle = atan2(p[1],p[0]);
			angle += PI;
			p[0] = 0.5 * cosf(angle);
			p[1] = 0.5 * sinf(angle);
		}
		m_v[i].position[0] = p[0];
		m_v[i].position[1] = p[1];

		m_v[i].color = basecol;

		double d  = cos(2.0*PI*fq*time			+ m_phase[i]);
		double dp = cos(2.0*PI*fq*m_lastTime	+ m_phase[i]); // previous

		// update the position.
		// if lifetime is negative, stars live forever
		if (d > 0 && dp <= 0 && m_lifetime > 0.f) {
			// draw uniformly in a circle with radius 0.5
			float a = uniform();
			float b = uniform();
			if (b < a) {
				float tmp = b;
				b = a;
				a = tmp;
			}
			m_v[i].position[0] = 0.5f*b*cosf(PI*2.f*a/b);
			m_v[i].position[1] = 0.5f*b*sinf(PI*2.f*a/b);
		}
	}
	m_lastTime = time;
}
