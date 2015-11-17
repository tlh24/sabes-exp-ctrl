#include "../../include/Serialize/polhemusPredict.h"

PolhemusPredict::PolhemusPredict()
{
	for (int i=0; i<8; i++) {
		for (int j=0; j<3; j++)
			m_s[i][j] = 0.0;
	}
	for (int i=0; i<32; i++)
		m_t[i] = 0.0;
	for (int i=0; i<3; i++) {
		for (int j=0; j<2; j++)
			m_fit[i][j] = 0.0;
	}
	m_avg = 0;
	m_ptr = 0;
	m_nsmooth = 6;
}
PolhemusPredict::~PolhemusPredict() {}
void PolhemusPredict::add(long double time, float *s)
{
	m_t[m_ptr & 31] = time;
	for (int i=0; i<3; i++)
		m_s[m_ptr & 7][i] = s[i];
	m_ptr++;
	update();
}
void PolhemusPredict::update()
{
	//update the linear model used to predict position.
	//critical assumptions: stream is actually sampled at a constant rate,
	//even if it does not come in at a constant rate.
	//also, this should be called in add() thread to prevent m_ptr contention.
	int n = m_ptr;
	if (n < 4) return;
	long double mean = m_t[(n-1)&31] - m_t[n&31];
	mean /= 31; //mean period.
	//calculate the time of the most recent sample (n-1) in terms of last 32 samples.
	long double avg = 0;
	for (int i=0; i<32; i++)
		avg += m_t[(n-1-i)&31] + mean*i;
	m_avg = avg / 32;
	//fit a line to the last 8 samples.
	for (int j=0; j<m_nsmooth; j++)
		m_tfit[j] = -1.0*mean*j; //relative to the most recent sample (avg).
	double cov00, cov01, cov11, sumsq; //ignore.
	for (int i=0; i<3; i++) {
		for (int j=0; j<m_nsmooth; j++)
			m_sfit[j] = m_s[(n-1-j)&7][i]; //relative to the most recent sample (avg).
		gsl_fit_linear(m_tfit, 1, m_sfit, 1, m_nsmooth, &(m_fit[i][0]), &(m_fit[i][1]),
		               &cov00, &cov01, &cov11, &sumsq);
	}
}
void PolhemusPredict::predict(long double time, float *s)
{
	time -= m_avg;
	for (int i=0; i<3; i++) {
		s[i] = m_fit[i][0] + m_fit[i][1] * time;
	}
}
void PolhemusPredict::test()
{
	float x[3];
	for (int i=0; i<64; i++) {
		x[0] = x[1] = x[2] = (float)i;
		add((long double)i / 2.5, x);
	}
	for (int i=0; i<32; i++) {
		x[0] = x[1] = x[2] = (float)(i+64);
		add((long double)(i+64) / 2.5, x);
	}
	predict(96.0/2.5, x);
	printf("PolhemusPredict::test() should be 96, is %f\n", x[0]);
}
