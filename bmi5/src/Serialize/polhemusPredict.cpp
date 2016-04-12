#include "../../include/Serialize/polhemusPredict.h"

PolhemusPredict::PolhemusPredict()
{
	m_nsmooth = 6;
	m_dof = 3;

	for (int j=0; j<m_dof; j++) {
		auto s = new float[8];
		for (int i=0; i<8; i++) {
			s[i] = 0.0;
		}
		m_s.push_back(s);
		auto fit = new double[2];
		for (int i=0; i<2; i++) {
			fit[i] = 0.0;
		}
		m_fit.push_back(fit);
	}

	for (int i=0; i<8; i++) {
		m_tfit[i] = 0.0;
		m_sfit[i] = 0.0;
	}

	for (int i=0; i<32; i++) {
		m_t[i] = 0.0;
	}

	m_avg = 0;
	m_ptr = 0;
}
PolhemusPredict::PolhemusPredict(int dof)
{
	m_nsmooth = 6;
	m_dof = dof;

	for (int j=0; j<m_dof; j++) {
		auto s = new float[8];
		for (int i=0; i<8; i++) {
			s[i] = 0.0;
		}
		m_s.push_back(s);
		auto fit = new double[2];
		for (int i=0; i<2; i++) {
			fit[i] = 0.0;
		}
		m_fit.push_back(fit);
	}

	for (int i=0; i<8; i++) {
		m_tfit[i] = 0.0;
		m_sfit[i] = 0.0;
	}

	for (int i=0; i<32; i++) {
		m_t[i] = 0.0;
	}

	m_avg = 0;
	m_ptr = 0;
}
PolhemusPredict::~PolhemusPredict()
{
	for (auto &x : m_s)
		delete[] x;
	m_s.clear();
	for (auto &x : m_fit)
		delete[] x;
	m_fit.clear();
}
void PolhemusPredict::add(long double time, float *s)
{
	m_t[m_ptr & 31] = time; // power-of-two modulo
	for (int i=0; i<m_dof; i++)
		m_s[i][m_ptr & 7] = s[i];
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
	mean /= 31; // mean period.
	//calculate the time of the most recent sample (n-1) in terms of last 32 samples.
	long double avg = 0;
	for (int i=0; i<32; i++)
		avg += m_t[(n-1-i)&31] + mean*i;
	m_avg = avg / 32;
	//fit a line to the last 8 samples.
	for (int j=0; j<m_nsmooth; j++)
		m_tfit[j] = -1.0*mean*j; //relative to the most recent sample (avg).
	double cov00, cov01, cov11, sumsq; //ignore.
	for (int i=0; i<m_dof; i++) {
		for (int j=0; j<m_nsmooth; j++)
			m_sfit[j] = m_s[i][(n-1-j)&7]; //relative to the most recent sample (avg).
		gsl_fit_linear(m_tfit, 1, m_sfit, 1, m_nsmooth, &(m_fit[i][0]), &(m_fit[i][1]),
		               &cov00, &cov01, &cov11, &sumsq);
	}
}
void PolhemusPredict::predict(long double time, float *s)
{
	time -= m_avg;
	for (int i=0; i<m_dof; i++) {
		s[i] = m_fit[i][0] + m_fit[i][1] * time;
	}
}
void PolhemusPredict::test()
{
	auto x = new float[m_dof];
	for (int i=0; i<64; i++) {
		for (int j=0; j<m_dof; j++) {
			x[j] = (float)i;
		}
		add((long double)i / 2.5, x);
	}
	for (int i=0; i<32; i++) {
		for (int j=0; j<m_dof; j++) {
			x[j] = (float)(i+64);
		}
		add((long double)(i+64) / 2.5, x);
	}
	predict(96.0/2.5, x);
	printf("PolhemusPredict::test() should be 96, is %f\n", x[0]);
	delete[] x;
}
