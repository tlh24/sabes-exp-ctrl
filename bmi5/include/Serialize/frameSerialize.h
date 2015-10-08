#ifndef FRAME_SERIALIZE_H
#define FRAME_SERIALIZE_H
#include "timeSerialize.h"

// this class records and reports the time when a frame was displayed
// (minus any buffering in the projector/display)
class FrameSerialize : public TimeSerialize
{
public:
	double m_time;
	double m_ticks;
	int m_frame;

	FrameSerialize();
	~FrameSerialize();
	// you must call store() within the opengl display thread.
	virtual bool store();
	virtual bool store(int frame);
	virtual double *mmapRead(double *d);
};


#endif
