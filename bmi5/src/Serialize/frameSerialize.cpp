#include "../../include/Serialize/frameSerialize.h"

FrameSerialize::FrameSerialize() : TimeSerialize()
{
	m_name = {"frame_"};
}
FrameSerialize::~FrameSerialize()
{
	clear();
}
// you must call store() within the opengl display thread.
bool FrameSerialize::store()
{
	return false;       //dummy.
}
bool FrameSerialize::store(int frame)
{
	long double time = 0.0;
	g_tsc->getTicks(time, m_ticks);
	m_time = (double)time;
	m_frame = frame;
	v_time.push_back(m_time);
	v_ticks.push_back(m_ticks);
	v_frame.push_back(m_frame);
	return true;
}
double* FrameSerialize::mmapRead(double *d)
{
	//this is a write, and returns the time & ticks of the last recorded frame.
	*d++ = m_time;
	*d++ = m_ticks;
	*d++ = m_frame;
	return d;
}
