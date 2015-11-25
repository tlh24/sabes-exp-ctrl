#ifndef DISPLAY_TEXT_H
#define DISPLAY_TEXT_H

#include "../Serialize/vectorSerialize.h"

class DisplayText : public VectorSerialize<char>
{
public:
	string	m_text;
	char		m_draw;
	array<float,2>	m_pos; //double so the comparisons work properly.
	vector<char> v_draw;
	array<unsigned char,4>	m_color;
	vector<array<float,2>> v_pos;
	vector<array<unsigned char,4>> v_color;

	DisplayText(int size);
	~DisplayText();

	virtual bool store();
	virtual void clear();
	virtual string storeName(int indx);
	virtual int getStoreClass(int indx);
	virtual void getStoreDims(int indx, size_t *dims);
	virtual void *getStore(int indx, int i);
	virtual int numStores();
	virtual double *mmapRead(double *d);
	virtual void draw(int display, float ar);
};

#endif
