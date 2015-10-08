#include "../../include/Serialize/polhemusSerialize.h"


PolhemusSerialize::PolhemusSerialize(int nsensors) : VectorSerialize2(nsensors * 3, MAT_C_SINGLE)
{
	m_name = "polhemus_";
	m_nsensors = nsensors;
	for (int i=0; i<m_nsensors; i++) {
		m_pp.push_back(new PolhemusPredict());
		m_pp[i]->m_nsmooth = 8;
	}
}
PolhemusSerialize::~PolhemusSerialize()
{
	clear();
	for (int i=0; i<m_nsensors; i++) {
		delete m_pp[i];
	}
}
bool PolhemusSerialize::store()
{
	return false;        // override -- called below.
}
bool PolhemusSerialize::store(float *data)   //called after serial data reception; always store.
{
	m_time = gettime();
	// assumes that there is m_nsensors * 3 floats in *data
	for (int i=0; i<m_nsensors; i++) {
		m_pp[i]->add(m_time, &(data[i*3]));
	}
	for (int i=0; i<m_nsensors*3; i++) {
		m_stor[i] = data[i];
	}
	for (int i=0; i<m_nsensors; i++) {
		for (int j=0; j<3; j++)
			m_stor2[i*3+j] = m_pp[i]->m_fit[j][1]; // vel.
	}
	VectorSerialize2::store();
	return true;
}
void PolhemusSerialize::getLoc(double now, float *out)
{
	for (int i=0; i<m_nsensors; i++) {
		m_pp[i]->predict(now, &(out[i*3]));
	}
}
string PolhemusSerialize::storeName(int indx)
{
	switch (indx) {
	case 0:
		return m_name + string("time_o");
	case 1:
		return m_name + string("sensors_o"); // default is input; override
	case 2:
		return m_name + string("sensorvel_o"); // default is input; override
	}
	return string {"none"};
}
double* PolhemusSerialize::mmapRead(double *d)
{
	*d++ = m_time; // last time the sensors were read.
	getLoc(gettime(), m_stor.data()); // sample position now.
	for (int i=0; i<3*m_nsensors; i++) {
		*d++ = m_stor[i]; //float->double.
	}
	for (int i=0; i<m_nsensors; i++) {
		for (int j=0; j<3; j++)
			*d++ = m_pp[i]->m_fit[j][1];
	}
	return d;
}
