#ifndef __JACKSND_H__
#define __JACKSND_H__

#define TABLE_SIZE   (200)
#define SAMPFREQ		48000.0

extern long g_jackSample; 

class Tone{
public:
	float		m_s1; 
	float		m_s2; 
	double	m_phase; 
	double	m_pincr; 
	double	m_poff; 
	long		m_start; //in samples
	long		m_duration; // in samples; 
	long		m_attack; 
	long		m_release; 
	float		m_distortion; 
	bool		m_dead; 
	
	Tone(float freq, float pan, float scale, long start, long duration){
		pan = pan > 1.f ? 1.f : pan; 
		pan = pan < -1.f ? -1.f : pan; 
		m_s1 = 1.f - pan; 
		m_s2 = pan + 1;
		if(m_s1 > 1.f) m_s1 = 1.f; 
		if(m_s2 > 1.f) m_s2 = 1.f; 
		m_s1 *= scale; 
		m_s2 *= scale; 
		m_phase = 0.0; 
		m_pincr = (double)freq / SAMPFREQ; 
		m_dead = false; 
		m_start = start; 
		m_duration = duration; 
		m_attack = 1000; 
		m_release = 1000; 
		m_distortion = 0.f; 
		m_poff = 0.0;
	}
	~Tone(){}
	
	void sample(long s, float* d1, float* d2, float* sine){
		if(m_start == -1) m_start = s; 
		if(m_dead || s > m_start + m_duration + m_release){
			m_dead = true; 
		} else {
			if(m_start <= s){
				float env = 1.f;
				if(s-m_start < m_attack)
					env = (float)(s-m_start) / (float)m_attack; 
				else if(s-m_start >= m_duration)
					env = 1.f - (float)(s-m_start-m_duration) / (float)m_release; 
				env = env < 0.f ? 0.f : env; 
				env = env > 1.f ? 1.f : env; 
				double phase = m_phase * TABLE_SIZE; 
				int bot = (int)floor(phase); 
				if(bot > TABLE_SIZE-1) bot = TABLE_SIZE-1; 
				int top = bot+1; 
				double lerp = phase - floor(phase); 
				float a = (1-lerp)*sine[bot] + lerp*sine[top]; 
				if(m_distortion > 0.f)
					a = atan(a * (1 + m_distortion)) / atan(1+m_distortion); 
				*d1 += a * m_s1 * env; 
				*d2 += a * m_s2 * env; 
				m_phase += m_pincr; 
				if(m_phase > 1.0) m_phase -= 1.0; 
			}
		}
	}
};

void jackClose(int sig); 
int jackInit(); 
void jackDemo(); 
void jackAddTone(Tone* t); 
void jackAddToneP(float freq, float pan, float scale, float duration); 
#endif