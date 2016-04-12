#ifndef POLHEMUS_PREDICT_H
#define POLHEMUS_PREDICT_H
#include "serialize.h"

class PolhemusPredict
{
public:
	int				m_nsmooth; 	// over how many samples to average; max 8;
	int				m_dof;
	vector<double *>	m_fit;		// [0] = offset, [1] = estimate of velocity, native sensor units/sec.
protected:
	vector<float *>	m_s; 		// last 8 sensor measurements.
	double			m_tfit[8];  // used in linear fit.
	double			m_sfit[8];
	long double 	m_t[32]; 	// time of the last 32 measurements (rate should be static!)
	long double		m_avg; 		// smoothed time of the last incoming sample.
	int				m_ptr; 		// circluar, obvi.

public:
	PolhemusPredict();
	PolhemusPredict(int dof);
	~PolhemusPredict();
	void add(long double time, float *s);
	void update();
	void predict(long double time, float *s);
	void test();
};
#endif
