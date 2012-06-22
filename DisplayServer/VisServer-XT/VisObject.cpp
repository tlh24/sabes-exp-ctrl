// VisObject.cpp: implementation of the CVisObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VisServer.h"
#include "VisWindow.h"
#include "VisObject.h"
#include "ComUtils.h"

#include "VisWindowActionLog.h"


////////////////////////////////////////////////////////////////////
//  VisObject Ptr List

VisObjectListStruct *ObjList = NULL;

void
addObjectPtr(CVisObject *obj){
	VisObjectListStruct *objptr;
	
	if(ObjList==NULL){							// IF   1st entry in list
		ObjList=new VisObjectListStruct;
		objptr=ObjList;
	}
	else{										// ELSE make a new tail item
		for(objptr=ObjList;objptr->next!=NULL;objptr=objptr->next);
		objptr->next=new VisObjectListStruct;
		objptr=objptr->next;
	}
		
	objptr->ptr=obj;		// Set disk ptr
	objptr->next=NULL;		// Mark item as tail
}

// NB: delDiskPtr only handles the Linked List
//     it's up to the VisDisk to remove itself 
//     from the screen
int
delObjectPtr(CVisObject *obj)
{
	VisObjectListStruct *objptr,*lastptr;

	lastptr=NULL;
	for(objptr=ObjList; objptr->ptr!=obj && objptr->next!=NULL; objptr=objptr->next) lastptr=objptr;
	if(objptr->ptr!=obj){ 
		// Disk Ptr not in List, Can't remove
		return 1;
	}
	else{
		// Unlink this item from linked list
		if(lastptr==NULL) ObjList=objptr->next;	// objptr is head of list
		else lastptr->next=objptr->next;		// otherwise leap over objptr
		// Then delete it
		delete objptr;
	}
	return 0;
}


////////////////////////////////////////////////////////////////////
//  CVisObject Class

CVisObject::CVisObject() { 
	// Error String
	errorString[0]=NULL;

	// Start with Object Not Showing
	Show=0;

	// Default Position Values
	// Note that R,X,Y,Z are in screen coordinates
	//    not in "real" coordinates
	float width = (VisWindow==NULL)?1000:VisWindow->width;
	X=Y=.5f*width;
	Z=0.f;

	// Add to the Object List
	addObjectPtr(this); 
	// Get an object tag
	tag = (VisWindow==NULL)?-1:VisWindow->nextTag();
}
CVisObject::~CVisObject() { 
    logToFile((f, "VisObject is to be deleted\n"));
	delObjectPtr(this); 
    logToFile((f, "VisObject has been deleted\n"));
	// if(VisWindow) VisWindow->requestUpdate();
}


/////////////////////////////////////////////////////////////////////////////
// PROPERTIES AND METHODS


/////// GETS

STDMETHODIMP CVisObject::get_tag(double *pVal){	 *pVal=tag;	 return S_OK; }
STDMETHODIMP CVisObject::get_z(double *pVal){	 *pVal=Z;	 return S_OK; }
STDMETHODIMP CVisObject::get_show(double *pVal){ *pVal=Show; return S_OK; }

STDMETHODIMP CVisObject::get_pos(VARIANT *pVal)
{
	double tmp[2]={X,Y};
	VariantFromArray(2,tmp,pVal);
	return S_OK;
}

STDMETHODIMP CVisObject::get_errstring(BSTR *pVal)
{
	*pVal=SysAllocString(errorString);
	return S_OK;
}


/////// PUTS
STDMETHODIMP CVisObject::put_show(double newVal){
	if( VisWindow && (Show != (newVal!=0)) ){ 
		VisWindow->requestUpdate();
		if(VisWindow->logmode) VisWindow->logAction(tag,ACTION_SHOW,&newVal,1);
		Show = (newVal!=0);
	}
	return S_OK;
}

STDMETHODIMP CVisObject::put_pos(VARIANT newVal)
{
	// This is really ugly, but I wanted to remain Automation Compliant
	// so it can be called matlab, e.g.

	int alen;
	double *aptr;
	if( VariantToArray(&alen,&aptr,&newVal) ) return E_INVALIDARG;
	if( alen<2 ) { delete aptr; return E_INVALIDARG; }
	X=(float)aptr[0];
	Y=(float)aptr[1];

	if(VisWindow && Show){ 
		VisWindow->requestUpdate();
		if(VisWindow->logmode) VisWindow->logAction(tag,ACTION_POS,aptr,alen);
	}
	delete aptr;
	return S_OK;
}

STDMETHODIMP CVisObject::put_z(double newVal)
{
	Z=(float)newVal;
	if(VisWindow && Show){ 
		VisWindow->requestUpdate();
		if(VisWindow->logmode) VisWindow->logAction(tag,ACTION_Z,&newVal,1);
	}
	return S_OK;
}
