#include "../../include/Shape/displayText.h"
#include "../../include/Shape/shape.h"


DisplayText::DisplayText(int size) : VectorSerialize(size, MAT_C_INT8)
{
	m_draw = 0;
#ifdef DEBUG
	m_draw = 3;
#endif
	m_text = string("debug text!");
	m_pos[0] = 0;
	m_pos[1] = 0;
	for (int i=0; i<4; i++)
		m_color[i] = 1.f;
}
DisplayText::~DisplayText()
{
	clear();
}
bool DisplayText::store()
{
	int n = nstored();
	bool same = true;
	if (n > 0) {
		same &= (m_draw == v_draw[n-1]);
		for (int i=0; i<2; i++)
			same &= (m_pos[i] == (v_pos[n-1])[i]);
		for (int i=0; i<4; i++)
			same &= (m_color[i] == (v_color[n-1])[i]);
	} else same = false;
	if (!same) {
		same &= !VectorSerialize::store();
		if (!same) {
			v_draw.push_back(m_draw);
			v_pos.push_back(m_pos);
			v_color.push_back(m_color);
		}
	}
	return !same;
}
void DisplayText::clear()
{
	VectorSerialize::clear();
	v_draw.clear();
	v_pos.clear();
	v_color.clear();
}
string DisplayText::storeName(int indx)
{
	switch (indx) {
	case 0:
		return m_name + string("draw");
	case 1:
		return m_name + string("pos");
	case 2:
		return m_name + string("color");
	}
	return VectorSerialize::storeName(indx - 3);

}
int DisplayText::getStoreClass(int indx)
{
	switch (indx) {
	case 0:
		return MAT_C_INT8;
	case 1:
		return MAT_C_SINGLE;
	case 2:
		return MAT_C_UINT8;
	}
	return VectorSerialize::getStoreClass(indx - 3);
}
void DisplayText::getStoreDims(int indx, size_t *dims)
{
	switch (indx) {
	case 0:
		dims[0] = 1;
		dims[1] = 1;
		return;
	case 1:
		dims[0] = 2;
		dims[1] = 1;
		return;
	case 2:
		dims[0] = 4;
		dims[1] = 1;
		return;
	}
	return VectorSerialize::getStoreDims(indx - 3, dims);
}
void *DisplayText::getStore(int indx, int i)
{
	switch (indx) {
	case 0:
		return (void *)&(v_draw[i]);
	case 1:
		return (void *)&((v_pos[i])[0]);
	case 2:
		return (void *)&((v_color[i])[0]);
	}
	return VectorSerialize::getStore(indx - 3, i);
}
int DisplayText::numStores()
{
	return VectorSerialize::numStores() + 3;
}
double *DisplayText::mmapRead(double *d)
{
	m_draw = (char)floor(*d++);
	for (int i=0; i<2; i++)
		m_pos[i] = *d++;
	for (int i=0; i<4; i++)
		m_color[i] = (char)((*d++) * 255.0);
	d = VectorSerialize::mmapRead(d);
	//copy data to string.
	m_text.reserve(m_size); //just in case..
	char *s = (char *)m_text.data();
	for (int i=0; i<m_size; i++)
		s[i] = m_stor[i];
	return d;
}
void DisplayText::draw(int display, float ar)
{
	if (m_draw & (1<<display)) {
		//need to convert world coords to screen.
		float xar = ar < 1.f ? ar : 1.f;
		float yar = ar > 1.f ? 1.f/ar : 1.f;
		float in[4], out[4];
		for (int i=0; i<4; i++) {
			in[i] = out[i] = 0.f;
		}
		in[0] = m_pos[0]*xar;
		in[1] = m_pos[1]*yar;
		float *aff = g_affine44->data(); //in matlab/openGL row major order.
		for (int r=0; r<4; r++) {
			for (int c=0; c<4; c++) {
				out[r] += aff[r+4*c] * in[c];
			}
		}
		glColor4f(m_color[0], m_color[1], m_color[2], m_color[3]);
		glRasterPos2f(out[0], out[1]);
		glPrint(m_text.c_str(), display);
	}
}
