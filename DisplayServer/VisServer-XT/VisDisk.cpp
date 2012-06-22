// VisDisk.cpp : Implementation of CVisServerApp and DLL registration.



#include "stdafx.h"

#include "VisServer.h"

#include "VisWindow.h"

#include "VisDisk.h"

#include "ComUtils.h"

#include "VisCalibrate.h"

#include "VisWindowACtionLog.h"





// Some Disk Parameters

#define DISK_SLICES 20

#define DISK_RINGS  2



/////////////////////////////////////////////////////////////////////////////

// ERROR



STDMETHODIMP CVisDisk::InterfaceSupportsErrorInfo(REFIID riid)

{

	static const IID* arr[] = 

	{

		&IID_IVisDisk,

	};



	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)

	{

		if (InlineIsEqualGUID(*arr[i],riid))  return S_OK;

	}

	return S_FALSE;

}



/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////

// CONSTR/DESTR

CVisDisk::CVisDisk()

{

	// Default Color/Draw Values

	Color[0]=Color[1]=Color[2]=1;

#if INDEX_MODE

	ColorIndex=VisWindow->ColorRGB2I(Color);

#endif

	

	Alpha=1;

	Fill=1;

	Points=DISK_SLICES;



	// Clipped

	Clipped = VISWIN_IS_CLIPPED(X,Y);



	// Radius

	Radius=10;



	// Data Structures

	for(int i=0; i<15; i++) ROT[i]=0.;

	ROT[10]=1.;  // [3 3] of the rotation component

	ROT[15]=1.;  // Last element -- multiplies translation



	// Make the Display List

	quad=NULL;     // initial to null 

	dispList=-1;0; // Initialize to an illegal value

	makeDispList();



	// Ask VisWindow to Update

	// since VisObject() sets show=0, this is not needed here

	if(VisWindow){ 

		VisWindow->requestUpdate();

		if(VisWindow->logmode) VisWindow->logAction(tag,ACTION_CREATE,(double *)NULL,0);

	}

}



CVisDisk::~CVisDisk()

{

	Show=0;

	gluDeleteQuadric(quad);

	if(VisWindow){ 

		VisWindow->requestUpdate();

		if(VisWindow->logmode) VisWindow->logAction(tag,ACTION_DELETE,(double *)NULL,0);

	}



}





/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////

// PROPERTIES AND METHODS





/////// GETS

STDMETHODIMP CVisDisk::get_radius(double *pVal){	*pVal=Radius;	return S_OK; }

STDMETHODIMP CVisDisk::get_alpha(double *pVal){	*pVal=Alpha;	return S_OK; }

STDMETHODIMP CVisDisk::get_fill(double *pVal){	*pVal=Fill;		return S_OK;  }

STDMETHODIMP CVisDisk::get_points(double *pVal){ *pVal=Points; return S_OK; }



STDMETHODIMP CVisDisk::get_color(VARIANT *pVal)

{

	double tmp[3] = {Color[0], Color[1], Color[2]};

	VariantFromArray(3,tmp,pVal);

	return S_OK;

}





STDMETHODIMP CVisDisk::get_clipped(double *pVal){ *pVal=Clipped; return S_OK; }





/////// PUTS

STDMETHODIMP CVisDisk::put_alpha(double newVal){ 

	Alpha=(float)newVal;

	if(VisWindow && Show){ 

		VisWindow->requestUpdate();

		if(VisWindow->logmode) VisWindow->logAction(tag,ACTION_ALPHA,&newVal,1);

	}

	return S_OK;

 }

STDMETHODIMP CVisDisk::put_fill(double newVal){ 

	int oFill = Fill;

	Fill=(int)newVal; 

	if(Fill!=oFill){

		makeDispList();   // Changing the Fill requires remaking the quadratic

		if(VisWindow && Show){ 

			VisWindow->requestUpdate();

			if(VisWindow->logmode) VisWindow->logAction(tag,ACTION_FILL,&newVal,1);

		}

	}

	return S_OK; 

}



STDMETHODIMP CVisDisk::put_points(double newVal)

{

	int oPoints = Points;

	Points=(int)newVal; 

	if(Points!=oPoints){

		makeDispList();   // Changing the Fill requires remaking the quadratic

		if(VisWindow && Show){ 

			VisWindow->requestUpdate();

			if(VisWindow->logmode) VisWindow->logAction(tag,ACTION_POINTS,&newVal,1);

		}

	}

	return S_OK; 

}







STDMETHODIMP CVisDisk::put_radius(double newVal){ 

	Radius=(float)newVal;

	if(VisWindow && Show){ 

		VisWindow->requestUpdate();

		if(VisWindow->logmode) VisWindow->logAction(tag,ACTION_RADIUS,&newVal,1);

	}

	return S_OK;

}





STDMETHODIMP CVisDisk::put_color(VARIANT newVal)

{

	// This is really ugly, but I wanted to remain Automation Compliant

	// so it can be called matlab, e.g.



	int alen;

	double *aptr;

	if( VariantToArray(&alen,&aptr,&newVal) ) return E_INVALIDARG;

	if( alen<3 ) { delete aptr; return E_INVALIDARG; }

	Color[0]=(float)aptr[0];

	Color[1]=(float)aptr[1];

	Color[2]=(float)aptr[2];

	if( alen==4) Alpha=(float)aptr[3];



#if INDEX_MODE

	ColorIndex=VisWindow->ColorRGB2I(Color);

#endif



	if(VisWindow && Show){ 

		VisWindow->requestUpdate();

		if(VisWindow->logmode) VisWindow->logAction(tag,ACTION_COLOR,aptr,alen);

	}

	delete aptr;

	return S_OK;

}





/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////



////////////

// makeDispList

//

// If you want to create the disk DisplayList, you need

// to set FILL (DrawStyle). Radius could be done with a Scale command 

// later.  Color could be later.  Etc... 

void

CVisDisk::makeDispList()

{

	// Display List Management

	if(glIsList(dispList)) glDeleteLists(dispList,1);	// If previous list exists, delete it

	dispList=glGenLists(1);										// Get an unused disp list id



	// Allocate the Quadric Structure

	if(quad!=NULL) gluDeleteQuadric(quad);

	quad=gluNewQuadric();	



	// Fill?

	if(Fill) gluQuadricDrawStyle(quad,GLU_FILL);

	else	 gluQuadricDrawStyle(quad,GLU_SILHOUETTE);

	// Normals (for lighting)

	gluQuadricNormals(quad,GLU_FLAT); // which is not an approximation for a flat disk



	// DRAW

	glNewList(dispList,GL_COMPILE);					// Start List

	gluDisk(quad,0,1,Points,DISK_RINGS);		// Draw Shape, 0 is inner radius, 1 outer

	glEndList();									// End List

}



/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////

// Draw



void

CVisDisk::draw()

{

	if(Show){

		// Set Color and Lighting Properties

    

#if INDEX_MODE

		glIndexi(ColorIndex);

#else

		glColor4f(Color[0],Color[1],Color[2],Alpha);

#endif

		// Set Position

		float x = XPosToScreen(X,Y);

		float y = YPosToScreen(X,Y);



		Clipped = VISWIN_IS_CLIPPED(x,y);



		DPosToDScreen(JAC,x,y);

		// Rot 4x4, allocated by column, as in matlab

		// Jac, though, is only the 2x2 Jacobian

		ROT[0]=Radius*JAC[0][0]; ROT[1]=Radius*JAC[1][0];

		ROT[4]=Radius*JAC[0][1]; ROT[5]=Radius*JAC[1][1];

		ROT[12]=x; ROT[13]=y; ROT[14]=Z;



		glMatrixMode (GL_MODELVIEW);	

		// glLoadIdentity();

		// glTranslatef(x,y,Z);

		// glScalef(dx,dy,1);

		glLoadMatrixf(ROT);



		// Call List

		glCallList(dispList);

	}

}



