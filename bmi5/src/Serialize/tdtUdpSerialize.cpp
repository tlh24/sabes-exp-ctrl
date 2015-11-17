#include "../../include/Serialize/tdtUdpSerialize.h"
#include "tdt_udp.h"

TdtUdpSerialize::TdtUdpSerialize(int sock, int size) : Serialize()
{
	//the sock should be created elsewhere -- so we can get error strings out.
	m_sock = sock;
	m_size = size;
	for (int i=0; i<size; i++) {
		m_stor.push_back(0.f);
		m_last.push_back(0.0);
	}
	m_bs = 0;
	m_name = "tdtudp_";
	m_time = 0;
}
TdtUdpSerialize::~TdtUdpSerialize()
{
	disconnectRZ(m_sock);
	clear();
	if (m_bs) free(m_bs);
}
bool TdtUdpSerialize::store()
{
	return false;        //do it in mmapRead()
}
void TdtUdpSerialize::clear()
{
	v_time.clear();
	v_stor.clear();
}
int TdtUdpSerialize::nstored()
{
	return v_stor.size();
}
string TdtUdpSerialize::storeName(int indx)
{
	switch (indx) {
	case 0:
		return m_name + string("time"); //only saved in file.
	case 1:
		return m_name + string("udp");
	}
	return string {"none"};
}
int TdtUdpSerialize::getStoreClass(int indx)
{
	switch (indx) {
	case 0:
		return MAT_C_DOUBLE;
	case 1:
		return MAT_C_SINGLE;
	}
	return 0;
}
void TdtUdpSerialize::getStoreDims(int indx, size_t *dims)
{
	switch (indx) {
	case 0:
		dims[0] = dims[1] = 1;
		return;
	case 1:
		dims[0] = m_size;
		dims[1] = 1;
		return;
	}
}
void *TdtUdpSerialize::getStore(int indx, int k)
{
	switch (indx) {
	case 0:
		return (void *)&(v_time[k]);
	case 1: {
		//coalesce the memory: <vector<vector>> is not contiguous.
		if (m_bs) free(m_bs);
		int n = nstored();
		m_bs = (float *)malloc(sizeof(float)*(n-k)*m_size);
		for (int i=0; i<n-k; i++) {
			for (int j=0; j<m_size; j++) {
				m_bs[j + i*m_size] = v_stor[i+k][j];
			}
		}
		return (void *)(m_bs);
	}
	}
	return NULL;
}
int TdtUdpSerialize::numStores()
{
	return 2;
}
double *TdtUdpSerialize::mmapRead(double *d)
{
	d += 1; //skip time -- this is only saved in the file.
	bool sames = true;
	for (int i=0; i<m_size; i++)
		sames &= m_last[i] == d[i];
	if (!sames) {
		for (int i=0; i<m_size; i++) {
			m_last[i] = d[i];
			m_stor[i] = (float)d[i];
		}
		sendDataRZ(m_sock, &(m_stor[0]), m_size); //thread-synchronous is ok?
		double time = gettime(); //save the time of TX.
		v_time.push_back(time);
		v_stor.push_back(m_stor);
	}
	d += m_size;
	return d;
}
