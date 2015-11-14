#include "../../include/Serialize/toneSerialize.h"
#include "jacksnd.h"

ToneSerialize::ToneSerialize() : Serialize()
{
	m_name = "tone_";
	m_time = 0;
	m_freq = 0;
	m_pan  = 0;
	m_scale = 0;
	m_duration = 0;
	m_play = 0;
}
ToneSerialize::~ToneSerialize()
{
	clear();
}
bool ToneSerialize::store()
{
	return false;        //do it in mmapRead()
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
void ToneSerialize::getStoreDims(int, size_t *dims)
{
	// dims for all stores for tones are 1x1
	dims[0] = dims[1] = 1;
}
void* ToneSerialize::getStore(int indx, int k)
{
	switch (indx) {
	case 0:
		return (void *)&(v_time[k]);
	case 1:
		return (void *)&(v_freq[k]);
	case 2:
		return (void *)&(v_pan[k]);
	case 3:
		return (void *)&(v_scale[k]);
	case 4:
		return (void *)&(v_duration[k]);
	case 5:
		return (void *)&(v_play[k]);
	}
	return NULL;
}
int ToneSerialize::numStores()
{
	return 6;
}
double* ToneSerialize::mmapRead(double *d)
{
	m_time = gettime();

	m_freq		= d[1];
	m_pan  		= d[2];
	m_scale 	= d[3];
	m_duration 	= d[4];
	m_play 		= d[5];

	int n = nstored();
	bool different = false;
	if (n>0) {
		different |= (m_freq != v_freq[n-1]);
		different |= (m_pan != v_pan[n-1]);
		different |= (m_scale != v_scale[n-1]);
		different |= (m_duration != v_duration[n-1]);
	}

	if (different || m_play) {
		v_time.push_back(m_time);
		v_freq.push_back(m_freq);
		v_pan.push_back(m_pan);
		v_scale.push_back(m_scale);
		v_duration.push_back(m_duration);
		v_play.push_back(m_play);
		d[0] = m_time;
	}

	if (m_play > 0) {
		#ifdef JACK
		jackAddToneP(m_freq, m_pan, m_scale, m_duration);
		#endif
		d[5] = 0;
	}

	d += 6;
	return d;
}
