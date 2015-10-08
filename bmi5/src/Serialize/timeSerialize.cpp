#include "../../include/Serialize/timeSerialize.h"

TimeSerialize::TimeSerialize() : Serialize() {}
TimeSerialize::~TimeSerialize()
{
	clear();
}
bool TimeSerialize::store()
{
	long double time = 0.0;
	double ticks;
	g_tsc->getTicks(time, ticks);
	v_time.push_back((double)time);
	v_ticks.push_back(ticks);
	v_frame.push_back(g_frame);
	return true; //stored!
}
void TimeSerialize::clear()
{
	v_time.clear();
	v_ticks.clear();
	v_frame.clear();
}
int TimeSerialize::nstored()
{
	return v_time.size();
}
string TimeSerialize::storeName(int indx)
{
	switch (indx) {
	case 0:
		return m_name + string("time_o");
	case 1:
		return m_name + string("ticks_o");
	case 2:
		return m_name + string("frame_o");
	}
	return string("none");
}
int TimeSerialize::getStoreClass(int indx)
{
	switch (indx) {
	case 0:
		return MAT_C_DOUBLE;
	case 1:
		return MAT_C_DOUBLE;
	case 2:
		return MAT_C_INT32;
	}
	return 0;
}
void TimeSerialize::getStoreDims(int , size_t *dims)
{
	dims[0] = 1;
	dims[1] = 1;
}
void* TimeSerialize::getStore(int indx, int i)
{
	switch (indx) {
	case 0:
		return (void *)&(v_time[i]);
	case 1:
		return (void *)&(v_ticks[i]);
	case 2:
		return (void *)&(v_frame[i]);
	}
	return NULL;
}
int TimeSerialize::numStores()
{
	return 3;
}
double* TimeSerialize::mmapRead(double *d)
{
	//this is actually a write (all variables output)
	long double time = 0.0;
	double ticks = 0.0;
	g_tsc->getTicks(time, ticks);
	*d++ = (double)time;
	*d++ = ticks;
	*d++ = (double)g_frame;
	return d;
}
