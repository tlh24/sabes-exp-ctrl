#ifndef STORE_SERIALIZE_H
#define STORE_SERIALIZE_H

#include "vectorSerialize.h"

// This class, which is derived from VectorSerialize only exists because
// I wanted VectorSerialize to do everything in mmapread (ie not doing
// reads in mmapread and writes in store)
// I wanted to do this because otherwise it takes two mmap_sync's for time_o
// to get updated when something gets changed. And unfortunately, since
// there are several classes that are derived from VectorSerialize, making
// the change directly would break things.
//
// In case you care about the details:
//
// There is generally a two-step process for servicing the mmap
// 1. New values are read out of the mmap buffer
// 2. If the read values are different than the previous value, add to vector
// Time is updated when it is confirmed that the values are different (step 2)
// so that it usefully reflects the time that the value changed.
// Unfortunately, this has the consequence of delaying time by an extra sync
//
// Consider this matlab example (of the old behavior):
//
// bmi5_cmd('make store int 1 foo');
// eval(bmi5_cmd('mmap structure'));
// b5 = bmi5_mmap(b5);
//
// b5.foo_v = 100; 		% set a value
// b5 = bmi5_mmap(b5);	% sync
// b5.foo_v 			% ie 100
// b5.foo_time_o 		% some value for time
// b5.foo_v = 101;		% different value so should "stick" and be saved w/ time
// b5 = bmi5_mmap(b5);	% sync
// b5.foo_v 			% ie 101
// b5.foo_time_o		% THE SAME TIME AS ABOVE!
// b5 = bmi5_mmap(b5);	% sync again
// b5.foo_time_o		% different time now

template <typename T>
class StoreSerialize : public VectorSerialize<T>
{
public:

	using VectorSerialize<T>::VectorSerialize;

	virtual bool store();
	virtual double *mmapRead(double *d);

};

template <typename T> bool StoreSerialize<T>::store()
{
	return false; // do it in mmapRead()
}

template <typename T> double *StoreSerialize<T>::mmapRead(double *d)
{
	VectorSerialize<T>::m_time = gettime();

	// n.b: skip time -- we'll set it below if necessary
	for (int i=0; i<VectorSerialize<T>::m_size; i++) {
		VectorSerialize<T>::m_stor[i] = (T)d[i+1];
	}

	int n = VectorSerialize<T>::nstored();
	bool different = false;
	if (n>0) {
		for (int i=0; i<VectorSerialize<T>::m_size; i++) {
			different |= (VectorSerialize<T>::m_stor[i] != VectorSerialize<T>::v_stor[n-1][i]);
		}
	} else {
		different = true;
	}

	if (different) {
		VectorSerialize<T>::v_time.push_back(VectorSerialize<T>::m_time);
		VectorSerialize<T>::v_stor.push_back(VectorSerialize<T>::m_stor);
		d[0] = VectorSerialize<T>::m_time; // set time
	}

	d += 1 + VectorSerialize<T>::m_size;
	return d;
}

#endif
