#ifndef VECTOR_SERIALIZE_H
#define VECTOR_SERIALIZE_H

#include "serialize.h"

// this class is for recording arbitrary numbers, in the form of a vector,
// from matlab.  Can be used for e.g. trial#, trial type, your mommas number ...
// ... pager number, of course.
template <class T>
class VectorSerialize : public Serialize
{
public:
	int	m_size;
	int	m_type;
	double				m_time;
	vector<T> 			m_stor;
	vector<double>		v_time;
	vector<vector<T> > v_stor;
	T		*m_bs;

	VectorSerialize(int size, int matiotype);
	~VectorSerialize();
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


template <class T> VectorSerialize<T>::VectorSerialize(int size, int matiotype) : Serialize()
{
	m_time = 0;
	m_size = size;
	m_type = matiotype;
	for (int i=0; i<size; i++) {
		m_stor.push_back((T)0);
	}
	m_bs = NULL;
}
template <class T> VectorSerialize<T>::~VectorSerialize()
{
	clear();
	free(m_bs);
}
template <class T> bool VectorSerialize<T>::store()
{
	bool same = true; //delta compression.
	int n = nstored();
	if (n > 0) {
		for (int i=0; i<m_size; i++)
			same &= (m_stor[i] == v_stor[n-1][i]);
	} else same = false;
	if (!same) {
		m_time = gettime();
		v_time.push_back(m_time);
		v_stor.push_back(m_stor);
	}
	return !same;
}
template <class T> void VectorSerialize<T>::clear()
{
	v_time.clear();
	v_stor.clear();
}
template <class T> int VectorSerialize<T>::nstored()
{
	return v_stor.size();
}
template <class T> string VectorSerialize<T>::storeName(int indx)
{
	switch (indx) {
	case 0:
		return m_name + string("time_o");
	case 1:
		return m_name + string("v");
	}
	return string("none");
}
template <class T> int VectorSerialize<T>::getStoreClass(int indx)
{
	switch (indx) {
	case 0:
		return MAT_C_DOUBLE;
	case 1:
		return m_type;
	}
	return 0;
}
template <class T> void VectorSerialize<T>::getStoreDims(int indx, size_t *dims)
{
	switch (indx) {
	case 0:
		dims[0] = 1;
		dims[1] = 1;
		return;
	case 1:
		dims[0] = m_size;
		dims[1] = 1;
		return;
	}
}
template <class T> void *VectorSerialize<T>::getStore(int indx, int k)
{
	//coalesce the memory -- <vector<vector>> is non-continuous in memory.
	if (indx == 0) {
		return (void *)&(v_time[k]);
	} else if (indx == 1) {
		if (m_bs) free(m_bs);
		int n = nstored(); //atomic -- if we're not careful, may change during read!
		m_bs = (T *)malloc(sizeof(T)*(n-k)*m_size);
		for (int i=0; i<n-k; i++) {
			for (int j=0; j<m_size; j++) {
				m_bs[j + i*m_size] = v_stor[i+k][j];
			}
		}
		return (void *)(m_bs);
	} else return NULL;
}
template <class T> int VectorSerialize<T>::numStores()
{
	return 2;
}
template <class T> double *VectorSerialize<T>::mmapRead(double *d)
{
	*d++ = m_time; //when the vector was updated.
	for (int i=0; i<m_size; i++) {
		m_stor[i] = (T)(*d++); //default input.
	}
	return d;
}


#endif
