// VisObject.h: interface for the CVisObject class.
//
// Abstract Base Class for VisServer graphical objects
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VISOBJECT_H__36827A84_2300_413A_8C97_4C5D9300237C__INCLUDED_)
#define AFX_VISOBJECT_H__36827A84_2300_413A_8C97_4C5D9300237C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


// CVisObject

class CVisObject  
{
public:
	CVisObject();
	~CVisObject();
	

	// REQUIRED PROPERTIES WITH VARIABLE IMPLEMENTATION
	virtual STDMETHOD(get_clipped)(/*[out, retval]*/ double *pVal) = 0;
	virtual void draw() = 0;

	// REQUIRED PROPERTIES WITH STANDARD IMPLEMENTATION
	STDMETHOD(get_tag)(/*[out, retval]*/ double *pVal);
	STDMETHOD(get_show)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_show)(/*[in]*/ double newVal);
	STDMETHOD(get_pos)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_pos)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_z)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_z)(/*[in]*/ double newVal);
	STDMETHOD(get_errstring)(/*[out, retval]*/ BSTR *pVal);

	// Error String
	wchar_t errorString[200];
	
protected:
	int   tag;
	int	  Show;
	float X,Y;
	float Z;
	int   Clipped;

};


// Object List

// A Linked list of CVisObjects
struct VisObjectListStruct { 
	void *ptr;
	VisObjectListStruct *next;
};
extern VisObjectListStruct *ObjList;

void addObjectPtr(CVisObject *);
int delObjectPtr(CVisObject *);



#endif // !defined(AFX_VISOBJECT_H__36827A84_2300_413A_8C97_4C5D9300237C__INCLUDED_)

