#include "../../include/Serialize/toneSerialize.h"

ToneSerialize::ToneSerialize() : Serialize()
{
	m_name = "tone_";
}
ToneSerialize::~ToneSerialize()
{
}
bool ToneSerialize::store()
{
	return false;       //done in mmapread().
}
void ToneSerialize::clear()
{
	v_time.clear();
	v_freq.clear();
	v_pan.clear();
	v_scale.clear();
	v_duration.clear();
	v_play.clear();
}
int ToneSerialize::nstored()
{
	return v_time.size();
}
string ToneSerialize::storeName(int indx)
{
	switch (indx) {
	case 0:
		return m_name + string("time_o"); // these are not output--
	case 1:
		return m_name + string("freq");
	case 2:
		return m_name + string("pan");
	case 3:
		return m_name + string("scale");
	case 4:
		return m_name + string("duration");
	case 5:
		return m_name + string("play_io"); // bidirectional.
	}
	return string("none");
}
int ToneSerialize::getStoreClass(int indx)
{
	switch (indx) {
	case 0:
		return MAT_C_DOUBLE;
	case 1:
		return MAT_C_SINGLE;
	case 2:
		return MAT_C_SINGLE;
	case 3:
		return MAT_C_SINGLE;
	case 4:
		return MAT_C_SINGLE;
	case 5:
		return MAT_C_INT8;
	}
	return 0;
}
void ToneSerialize::getStoreDims(int , size_t *dims)
{
	dims[0] = dims[1] = 1;
}
void* ToneSerialize::getStore(int indx, int i)
{
	switch (indx) {
	case 0:
		return (void *)&(v_time[i]);
	case 1:
		return (void *)&(v_freq[i]);
	case 2:
		return (void *)&(v_pan[i]);
	case 3:
		return (void *)&(v_scale[i]);
	case 4:
		return (void *)&(v_duration[i]);
	case 5:
		return (void *)&(v_play[i]);
	}
	return NULL;
}
int ToneSerialize::numStores()
{
	return 6;
}
double* ToneSerialize::mmapRead(double *d)
{
	float freq = d[1];
	float pan = d[2];
	float scale = d[3];
	float duration = d[4];
	if (d[5] > 0) {
#ifdef JACK
		jackAddToneP(freq, pan, scale, duration);
#endif
		m_time  = gettime();
		v_time.push_back(m_time);
		v_freq.push_back(freq);
		v_pan.push_back(pan);
		v_scale.push_back(scale);
		v_duration.push_back(duration);
		v_play.push_back((float)d[5]);
		d[0] = m_time;	// { xxx this isnt working!
		d[5] = 0.0;		// reset play
	}
	d += 6;
	return d;
}
