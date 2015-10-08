#ifndef TDT_UDP_SERIALIZE_H
#define TDT_UDP_SERIALIZE_H
#include "serialize.h"

//class for sending float data to TDT --
//exact protocol depends on the RCX file running on the RZ2.
//class saves timing information for when the packet was sent.
class TdtUdpSerialize : public Serialize
{
public:
	int					m_sock;
	int 				m_size;
	double				m_time;
	vector<double>		m_last; // note double.
	vector<float>		m_stor;
	vector<double> 		v_time;
	vector<vector<float> > v_stor;
	float				*m_bs; // for coalescing memory

	TdtUdpSerialize(int sock, int size);
	~TdtUdpSerialize();
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
#endif
