#ifndef VECTOR_SERIALIZE2_H
#define VECTOR_SERIALIZE2_H
#include "serialize.h"

// same as VectorSerialize, except two variables -- position and velocity e.g.
// yea, copypasta. sorry.
template <class T>
class VectorSerialize2 : public Serialize
{
public:
	int	m_size;
	int	m_type;
	double				m_time;
	vector<T> 			m_stor;
	vector<T> 			m_stor2;
	vector<double>		v_time;
	vector<vector<T> > v_stor;
	vector<vector<T> > v_stor2;
	T		*m_bs;

	VectorSerialize2(int size, int matiotype);
	~VectorSerialize2();
	virtual bool store();
	virtual void clear();
	virtual int nstored();
	virtual string storeName(int indx);
	virtual int getStoreClass(int indx);
	virtual void getStoreDims(int indx, size_t *dims);
	virtual void *getStore(int indx, int k);
	virtual int numStores();
	virtual double *mmapRead(double *d);
};


template <class T> VectorSerialize2<T>::VectorSerialize2(int size, int matiotype) : Serialize()
{
	m_size = size;
	m_type = matiotype;
	for (int i=0; i<size; i++) {
		m_stor.push_back((T)0);
		m_stor2.push_back((T)0);
	}
	m_bs = NULL;
}
template <class T> VectorSerialize2<T>::~VectorSerialize2()
{
	clear();
	free(m_bs);
}
template <class T> bool VectorSerialize2<T>::store()
{
	bool same = true; //delta compression.
	int n = nstored();
	if (n > 0) {
		for (int i=0; i<m_size; i++) {
			same &= (m_stor[i] == v_stor[n-1][i]);
			same &= (m_stor2[i] == v_stor2[n-1][i]);
		}
	} else same = false;
	if (!same) {
		m_time = gettime();
		v_time.push_back(m_time);
		v_stor.push_back(m_stor);
		v_stor2.push_back(m_stor2);
	}
	return !same;
}
template <class T> void VectorSerialize2<T>::clear()
{
	v_time.clear();
	v_stor.clear();
	v_stor2.clear();
}
template <class T> int VectorSerialize2<T>::nstored()
{
	return v_stor.size();
}
template <class T> string VectorSerialize2<T>::storeName(int indx)
{
	switch (indx) {
	case 0:
		return m_name + string("time_o");
	case 1:
		return m_name + string("v");
	case 2:
		return m_name + string("v2");
	}
	return string("none");
}
template <class T> int VectorSerialize2<T>::getStoreClass(int indx)
{
	switch (indx) {
	case 0:
		return MAT_C_DOUBLE;
	case 1:
	case 2:
		return m_type;
	}
	return 0;
}
template <class T> void VectorSerialize2<T>::getStoreDims(int indx, size_t *dims)
{
	switch (indx) {
	case 0:
		dims[0] = 1;
		dims[1] = 1;
		return;
	case 1:
	case 2:
		dims[0] = m_size;
		dims[1] = 1;
		return;
	}
}
template <class T> void* VectorSerialize2<T>::getStore(int indx, int k)
{
	//coalesce the memory -- <vector<vector>> is non-continuous in memory.
	if (indx == 0) {
		return (void *)&(v_time[k]);
	} else if (indx == 1 || indx == 2) {
		if (m_bs) free(m_bs);
		int n = nstored(); //atomic -- if we're not careful, may change during read!
		m_bs = (T *)malloc(sizeof(T)*(n-k)*m_size);
		for (int i=0; i<n-k; i++) {
			if (indx == 1) {
				for (int j=0; j<m_size; j++)
					m_bs[j + i*m_size] = v_stor[i+k][j];
			} else {
				for (int j=0; j<m_size; j++)
					m_bs[j + i*m_size] = v_stor2[i+k][j];
			}

		}
		return (void *)(m_bs);
	} else return NULL;
}
template <class T> int VectorSerialize2<T>::numStores()
{
	return 3;
}
template <class T> double* VectorSerialize2<T>::mmapRead(double *d)
{
	*d++ = m_time; //when the vector was updated.
	for (int i=0; i<m_size; i++) {
		m_stor[i] = (T)(*d++);
	}
	for (int i=0; i<m_size; i++) {
		m_stor2[i] = (T)(*d++);
	}
	return d;
}

#endif
