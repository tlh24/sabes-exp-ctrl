#include "../../include/Serialize/mouseSerialize.h"


MouseSerialize::MouseSerialize() : VectorSerialize(3, MAT_C_SINGLE)
{
	m_name = "mouse_";
}
MouseSerialize::~MouseSerialize() {}
bool MouseSerialize::store()
{
	m_stor[0] = g_mousePos[0];
	m_stor[1] = g_mousePos[1];
	m_stor[2] = 0.f;
	return VectorSerialize::store();
}
string MouseSerialize::storeName(int )
{
	return m_name + string("sensors_o");        //output.
}
double *MouseSerialize::mmapRead(double *d)
{
	*d++ = g_mousePos[0];
	*d++ = g_mousePos[1];
	*d++ = 0.f;
	return d;
}
