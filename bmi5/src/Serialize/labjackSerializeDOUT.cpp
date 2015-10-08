#include "../../include/Serialize/labjackSerializeDOUT.h"

LabjackSerializeDOUT::LabjackSerializeDOUT(int nchannels) : VectorSerialize(nchannels, MAT_C_SINGLE)
{
	m_name = "labjackDOUT_";
	m_nchannels = nchannels;
}
LabjackSerializeDOUT::~LabjackSerializeDOUT()
{
	clear();
}
bool LabjackSerializeDOUT::store()
{
	return false;      //override -- called with argument below.
}
string LabjackSerializeDOUT::storeName(int indx)
{
	switch (indx) {
	case 0:
		return m_name + string("time_o");
	case 1:
		return m_name + string("channels"); //default is input; override.
	}
	return string("none");
}
double* LabjackSerializeDOUT::mmapRead(double *d)
{
	m_time = gettime(); //time bmi5 retreives DOUT values.
	*d = m_time;
	for (int i=0; i<m_nchannels; i++) {
		m_stor[i] = d[i+1]; //double->float, input.
	}
	d += (m_nchannels + 1);
	return d;
}
