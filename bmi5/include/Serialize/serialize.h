// class for serializing (matlab format) to a file
// & read (binary format) from a mmaped file.
#ifndef __SERIALIZE_H__
#define __SERIALIZE_H__
#include <string>
#include <vector>
#include <array>
#include "matio.h"
#include <gsl/gsl_fit.h>
#include <string.h>
#include "gettime.h"
#include "timesync.h"

class TimeSyncClient;
extern TimeSyncClient *g_tsc;
extern int g_frame;
extern long double gettime();
extern float g_mousePos[2];

using namespace std;
class Serialize
{
public:
	string	m_name;
	int		m_lastBackup; //index+1 of last record saved to backup.

	Serialize();
	virtual ~Serialize();
	void perr(const char *method);
	virtual bool 	store();
	virtual void	clear();
	virtual int 	nstored();
	virtual string 	storeName(int );
	virtual int 	getStoreClass(int );
	virtual void	getStoreDims(int , size_t *dims);
	virtual void	*getStore(int , int);
	virtual int 	numStores();
	virtual double 	*mmapRead(double *);
	//drawing routines -- opengl -- not all need implement.
	virtual void	draw(int, float);
	virtual void	move(long double);
	// reads/writes parameters from a mmaped file (address).
	// all mmap variables are doubles, for convenience.
	virtual string getMmapInfo();
	virtual string getStructInfo();
};

void writeMatlab(vector<Serialize *> tosave, char *filename, bool backup);
size_t matlabFileSize(vector<Serialize *> tosave);
size_t mmapFileSize(vector<Serialize *> tosave);
bool matlabHasNewData(vector<Serialize *> tosave);
#endif
