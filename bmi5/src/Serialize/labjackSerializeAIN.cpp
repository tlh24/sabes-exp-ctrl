#include "../../include/Serialize/labjackSerializeAIN.h"

LabjackSerializeAIN::LabjackSerializeAIN(int nsensors) : VectorSerialize(nsensors, MAT_C_SINGLE)
{
	m_name = "labjackAIN_";
	m_nsensors = nsensors;
}
LabjackSerializeAIN::~LabjackSerializeAIN()
{
	clear();
}
bool LabjackSerializeAIN::store()
{
	return false;      //override -- called with argument below.
}
bool LabjackSerializeAIN::store(float *data)
{
	m_time = gettime();
	for (int i=0; i<m_nsensors; i++) {
		m_stor[i] = data[i];
	}
	VectorSerialize::store();
	return true;
}
string LabjackSerializeAIN::storeName(int indx)
{
	switch (indx) {
	case 0:
		return m_name + string("time_o");
	case 1:
		return m_name + string("sensors_o"); //default is input; override.
	}
	return string("none");
}
double* LabjackSerializeAIN::mmapRead(double *d)
{
	*d++ = m_time; //last time the sensors were read.
	for (int i=0; i<m_nsensors; i++) {
		*d++ = m_stor[i]; //float->double, output.
	}
	return d;
}
