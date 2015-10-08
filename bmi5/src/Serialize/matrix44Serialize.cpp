#include "../../include/Serialize/matrix44Serialize.h"


Matrix44Serialize::Matrix44Serialize(string name) : Serialize()
{
	m_name = name;
	for (int i=0; i<16; i++) {
		m_x[i] = 0; // Matlab ordering (column major -- same in openGL).
		m_cmp[i] = 0;
	}
	for (int i=0; i<4; i++) {
		m_x[i+i*4] = 1.f;
		m_cmp[i+i*4] = 1.f;
	}
}
Matrix44Serialize::~Matrix44Serialize()
{
	clear();
}
void Matrix44Serialize::clear()
{
	v_x.clear();
}
bool Matrix44Serialize::store()
{
	return false; /* in mmap. */
}
int Matrix44Serialize::nstored()
{
	return v_x.size();
}
string Matrix44Serialize::storeName(int )
{
	return m_name + string("_m44");
}
int Matrix44Serialize::getStoreClass(int )
{
	return MAT_C_SINGLE;
}
void Matrix44Serialize::getStoreDims(int, size_t *dims)
{
	dims[0] = 4;
	dims[1] = 4;
	return;
}
void* Matrix44Serialize::getStore(int , int k)
{
	return (void *)&(v_x[k]);
}
int Matrix44Serialize::numStores()
{
	return 1;
}
double* Matrix44Serialize::mmapRead(double *d)
{
	//don't store the time here, as an incentive to not change it during the exp!
	bool sames = true;
	for (int i=0; i<16; i++)
		sames &= (d[i] == m_cmp[i]);
	if (!sames) {
		for (int i=0; i<16; i++) {
			m_x[i] = (float)d[i];
			m_cmp[i] = d[i];
		}
		v_x.push_back(m_x);
	}
	d += 16;
	return d;
}
float* Matrix44Serialize::data()
{
	return m_x.data();
};
