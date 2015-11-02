#include "../../include/Serialize/serialize.h"

Serialize::Serialize()
{
	m_lastBackup = 0;
}
Serialize::~Serialize()
{
	m_lastBackup = 0;
}
void Serialize::perr(const char *method)
{
	fprintf(stderr, "\"%s\":%s must be implemented in derived classes.\n",
			m_name.c_str(), method);
}
bool Serialize::store()
{
	perr("store");
	return false;
}
void Serialize::clear()
{
	perr("clear");
}
int Serialize::nstored()
{
	return 0;       //number of timeslices.
}
string Serialize::storeName(int )
{
	perr("storeName");
	return string("none");
}
int Serialize::getStoreClass(int )
{
	perr("getStoreClass");
	return 0;
}
void Serialize::getStoreDims(int , size_t *dims)
{
	perr("getStoreDims");
	dims[0] = 0;
	dims[1] = 0;
}
void* Serialize::getStore(int , int)
{
	perr("getStore");
	return NULL;
}
int Serialize::numStores()
{
	perr("numStores");
	return 0;
}
double* Serialize::mmapRead(double *)
{
	perr("mmapRead");
	return NULL;
}
//drawing routines -- opengl -- not all need implement.
void Serialize::draw(int, float) {}
void Serialize::move(long double) {}
// reads/writes parameters from a mmaped file (address).
// all mmap variables are doubles, for convenience.
string Serialize::getMmapInfo()
{
	std::stringstream oss;
	size_t dims[2];
	for (int indx = 0; indx < numStores(); indx++) {
		getStoreDims(indx, dims);
		string stor = storeName(indx);
		oss << "\t'double' [" << dims[0] << " " << dims[1] << "] '" << stor << "';...\n";
	}
	return oss.str();
}
string Serialize::getStructInfo()
{
	std::stringstream oss;
	size_t dims[2];
	for (int indx = 0; indx < numStores(); indx++) {
		getStoreDims(indx, dims);
		string stor = storeName(indx);
		oss << "b5." << stor << " = zeros(" << dims[0] << "," << dims[1] << ");\n";
	}
	return oss.str();
}
