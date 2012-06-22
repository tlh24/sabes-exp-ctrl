// VisPolygon.cpp : Implementation of CVisPolygon

#include "stdafx.h"

#include "stdio.h"

#include "math.h"



#include "VisServer.h"

#include "VisWindow.h"

#include "VisPolygon.h"

#include "ComUtils.h"

#include "VisCalibrate.h"

#include "VisWindowActionLog.h"



void CALLBACK tessCombineVtx(GLdouble coords[3], GLdouble *vtx_data[4],GLfloat wt[4], GLdouble **out);

//void CALLBACK tessCombineVtx(GLdouble coords[3], void *vtx_data[4], GLfloat wt[4], void **out);

	

/////////////////////////////////////////////////////////////////////////////

// CVisPolygon





/////////////////////////////////////////////////////////////////////////////

// ERROR



STDMETHODIMP CVisPolygon::InterfaceSupportsErrorInfo(REFIID riid)

{

	static const IID* arr[] = 

	{

		&IID_IVisPolygon,

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

CVisPolygon::CVisPolygon()

{

	// Default Color/Draw Values

	Color[0]=Color[1]=Color[2]=1;

#if INDEX_MODE

	ColorIndex=VisWindow->ColorRGB2I(Color);

#endif

	Alpha=1;

	Fill=0;

	Exact=1;



	// Clipped

	Clipped = VISWIN_IS_CLIPPED(X,Y);



	// Transform

	Scale = 1;

	Angle = 0;



	// Texture

	textureFlag=0;



	// No Points Yet...

	NPoints = 0;

	Points = NULL;

	ScrPoints = NULL;



	// Data Structures

	// ROT is used if not computing Exact vertex locations

	for(int i=0; i<15; i++) ROT[i]=0.;

	ROT[10]=1.;  // [3 3] of the rotation component

	ROT[15]=1.;  // Last element -- multiplies translation



	// GLU TESSELATION

	// Allocate the Tesselator Structure and 

	// set some if its properties

	tess=gluNewTess();	

	//	gluTessCallback(tess,GLU_TESS_VERTEX,(void(CALLBACK*)()) &tessVertexCallback);

	//	gluTessCallback(tess,GLU_TESS_BEGIN, (void(CALLBACK*)()) &tessBeginCallback);

	//	gluTessCallback(tess,GLU_TESS_END, (void(CALLBACK*)()) &tessEndCallback);

	gluTessCallback(tess, GLU_TESS_BEGIN, (void(CALLBACK*)()) &glBegin);  

	gluTessCallback(tess, GLU_TESS_VERTEX, (void(CALLBACK*)()) &glVertex3dv);  

	gluTessCallback(tess, GLU_TESS_END, (void(CALLBACK*)()) &glEnd);  

	gluTessCallback(tess, GLU_TESS_COMBINE, (void(CALLBACK*)()) &tessCombineVtx );

	//gluTessCallback(tess, GLU_TESS_COMBINE, (void (CALLBACK *) ()) tessCombineVtx );

	//gluTessCallback(tess, GLU_TESS_COMBINE, (void (__stdcall *) (void))tessCombineVtx );

	// ??? can get this to compile gluTessCallback(tess, GLU_TESS_ERROR, (void(CALLBACK*)()) &tessErrorCallback);

}



CVisPolygon::~CVisPolygon()

{

	Show=0;

	gluDeleteTess(tess);

	if(VisWindow){

		VisWindow->requestUpdate();

		if(VisWindow->logmode) VisWindow->logAction(tag,ACTION_DELETE,(double *)NULL,0);

	}

}





/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////

// PROPERTIES AND METHODS





/////////// GETS



STDMETHODIMP CVisPolygon::get_clipped(double *pVal) {*pVal=Clipped; return S_OK; }

STDMETHODIMP CVisPolygon::get_scale(double *pVal) { *pVal=Scale; return S_OK; }

STDMETHODIMP CVisPolygon::get_alpha(double *pVal) { *pVal=Alpha; return S_OK; }

STDMETHODIMP CVisPolygon::get_angle(double *pVal){ *pVal=Angle; return S_OK; }

STDMETHODIMP CVisPolygon::get_fill(double *pVal) { *pVal=Fill; return S_OK; }

STDMETHODIMP CVisPolygon::get_exact(double *pVal) { *pVal=Exact; return S_OK; }



STDMETHODIMP CVisPolygon::get_color(VARIANT *pVal)

{

	double tmp[3] = {Color[0], Color[1], Color[2]};

	VariantFromArray(3,tmp,pVal);

	return S_OK;

}



STDMETHODIMP CVisPolygon::get_points(VARIANT *pVal)

{



	if(NPoints>0){

		int n[2] = {NPoints, 2};

		VariantFromArray2(n,Points,pVal);

	}

	else{

		double tmp[1] = {0};

		VariantFromArray(1,tmp,pVal);

	}

	return S_OK;

	

}









////////// PUTS



STDMETHODIMP CVisPolygon::put_alpha(double newVal)

{

	Alpha = (float)newVal;

	if(VisWindow && Show){ 

		VisWindow->requestUpdate();

		if(VisWindow->logmode) VisWindow->logAction(tag,ACTION_ALPHA,&newVal,1);

	}

	return S_OK;

}

STDMETHODIMP CVisPolygon::put_scale(double newVal)

{

	Scale = (float)newVal;

	if(VisWindow && Show){ 

		VisWindow->requestUpdate();

		if(VisWindow->logmode) VisWindow->logAction(tag,ACTION_SCALE,&newVal,1);

	}

	return S_OK;

}

STDMETHODIMP CVisPolygon::put_angle(double newVal)

{

	Angle = (float)newVal;

	if(VisWindow && Show){ 

		VisWindow->requestUpdate();

		if(VisWindow->logmode) VisWindow->logAction(tag,ACTION_ANGLE,&newVal,1);

	}

	return S_OK;

}



STDMETHODIMP CVisPolygon::put_fill(double newVal)

{

	Fill = (int)newVal;



	// Changing Fill Requires a ReRendering, so 

	// remake the Display List (if you don't Xform each vtx separately)

	if(!Exact) makeDispList();	



	if(VisWindow && Show){ 

		VisWindow->requestUpdate();

		if(VisWindow->logmode) VisWindow->logAction(tag,ACTION_FILL,&newVal,1);

	}

	return S_OK;

}



STDMETHODIMP CVisPolygon::put_exact(double newVal)

{

	Exact = (int)newVal;



	// If you are now going to Xform only the center (POS), then

	// go ahead and make a display list 

	if(!Exact) makeDispList();	



	if(VisWindow && Show){ 

		VisWindow->requestUpdate();

		if(VisWindow->logmode) VisWindow->logAction(tag,ACTION_EXACT,&newVal,1);

	}

	return S_OK;

}



STDMETHODIMP CVisPolygon::put_color(VARIANT newVal)

{

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



STDMETHODIMP CVisPolygon::put_points(VARIANT newVal)

{

	

	int *alen;

	double **aptr;

	int i,j;



	if( VariantToArray2(&alen,&aptr,&newVal) ) return E_INVALIDARG;

	if( alen[1]<2 || alen[1]>3 ) { 

		for(i=0;i<alen[0];i++) delete aptr[i]; 

		delete aptr;

		delete alen; 

		return E_INVALIDARG; 

	}



	// If number of points has changes, reallocate the space

	if(NPoints!=alen[0]){

		if(Points!=NULL){

			for(i=0;i<NPoints;i++){ delete Points[i]; delete ScrPoints[i]; }

			delete Points; delete ScrPoints;

		}

		NPoints=alen[0];

		Points = new double*[NPoints];

		ScrPoints = new double*[NPoints];

		for(i=0;i<NPoints;i++){ 

			Points[i] = new double[3];

			ScrPoints[i] = new double[3];

		}

	}

	

	// Finally copy the data

	for(i=0;i<NPoints;i++){

		for(j=0;j<2;j++){ Points[i][j]=aptr[i][j]; }

		Points[i][2]=0;

	}

	

	// Clear Up alen, aptr

	delete alen;

	for(i=0;i<alen[0];i++) delete aptr[i]; 

	delete aptr;

	

	// Remake the Display List (if you don't Xform each vtx separately)

	if(!Exact) makeDispList();	



	// Ask VisWindow to Update

	if(VisWindow && Show){ 

		VisWindow->requestUpdate();

		if(VisWindow->logmode) VisWindow->logAction(tag,ACTION_POINTS,&NPoints,1);

	}

	return S_OK;

}





///////////////////	IMAGES



STDMETHODIMP CVisPolygon::get_image(VARIANT *pVal)

{

	if(textureFlag){

		int i,j;

		int n[2] = {textureW, textureH};

		

		double **tmp = new double*[textureW];

		for(i=0;i<textureW;i++) 

		{	

			tmp[i]=new double[textureH];

			for(j=0;j<textureH;j++){

				tmp[i][j]=textureImage[i][j][1];

			}

		}



		VariantFromArray2(n,tmp,pVal);

			

		for(i=0;i<textureW;i++) delete tmp[i]; 

		delete tmp;

		

	}

	else if(textureFlag){

		double tmp[2]={textureH,textureW};

		VariantFromArray(2,tmp,pVal);

		return S_OK;

	}

	else{

		double tmp[1] = {textureFlag};

		VariantFromArray(1,tmp,pVal);

	}

	return S_OK;

}



STDMETHODIMP CVisPolygon::put_image(VARIANT newVal)

{

	int *alen;

	// unsigned char ***aptr;

	double ***aptr;

	int i,j,k;



	// Send a 0, for example, to turn texture off

	if( VariantToArray3(&alen,&aptr,&newVal) ){

		textureFlag=0;

		makeDispList();

		return S_OK;

		// return E_INVALIDARG;

	}



	if( alen[2]!=3 ) { 

		for(i=0;i<alen[0];i++) {

			for(j=0;j<alen[1];j++) delete aptr[i][j]; 

			delete aptr[i];

		}

		delete aptr;

		delete alen; 

		return E_INVALIDARG; 

	}



	// Finally copy the data

	textureW = VISWIN_MIN(alen[0],VISPOLYGON_MAXTEXW);

	textureH = VISWIN_MIN(alen[1],VISPOLYGON_MAXTEXH);

	

	for(i=0;i<textureW;i++){

		for(j=0;j<textureH;j++){

			for(k=0;k<3;k++){ 

				textureImage[i][j][k]=(GLubyte)aptr[i][j][k]; 

			}

		}

	}

	

	// Clear Up alen, aptr

	for(i=0;i<alen[0];i++) {

		for(j=0;j<alen[1];j++) delete aptr[i][j]; 

		delete aptr[i];

	}

	delete aptr;

	delete alen; 

	

	// Do The Texture Map!!

	textureFlag=1;

	glPixelStorei(GL_UNPACK_ALIGNMENT,1);

	// Setup Typical 2D Texture Map

	glGenTextures(1, &textureId);	// Create The Texture

	glBindTexture(GL_TEXTURE_2D, textureId);

	

	// glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	// Linear Filtering

	// glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	// Linear Filtering

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);	

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);	

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);	

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);	



    // Generate The Texture

	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,textureW,textureH,0,GL_RGB,GL_UNSIGNED_BYTE,textureImage);





	makeDispList();	



	// Ask VisWindow to Update

	if(VisWindow && Show){ 

		VisWindow->requestUpdate();

		if(VisWindow->logmode) VisWindow->logAction(tag,ACTION_IMAGE,alen,2);

	}

	return S_OK;

}







/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////

// Render Polygon Display List





////////////

// Tesselation Callback Functions

//

// callback functions for GLU tesselation



void CALLBACK CVisPolygon::tessBeginCallback(GLenum which){ glBegin(which); }

void CALLBACK CVisPolygon::tessEndCallback(void){ glEnd(); }

void CALLBACK CVisPolygon::tessVertexCallback(GLdouble *vtx){ glVertex3dv(vtx); }

void CALLBACK CVisPolygon::tessErrorCallback(GLenum errorCode)

{

	swprintf(errorString,L"%s::Tess Error: %d",errorString,errorCode);

}





////////////

// makeTess

//

// Create the Tesselation

void

CVisPolygon::makeTess(double **pts)

{

	double vtx[3];

    glShadeModel(GL_FLAT);

	gluTessProperty(tess,GLU_TESS_BOUNDARY_ONLY, Fill?GL_FALSE:GL_TRUE );

	gluTessProperty(tess,GLU_TESS_WINDING_RULE, GLU_TESS_WINDING_NONZERO );

	

	if(NPoints>0){

		gluTessBeginPolygon(tess,NULL);	

		gluTessBeginContour(tess); 

		for(int i=0;i<NPoints;i++){

			vtx[0]=pts[i][0]; vtx[1]=pts[i][1]; vtx[2]=pts[i][2];

			gluTessVertex(tess,vtx,pts[i]);  // ?!?!  got this from DejaNews

		}

		gluTessEndContour(tess);

		gluTessEndPolygon(tess);

	}

}





void CALLBACK tessCombineVtx(GLdouble coords[3], GLdouble *vtx_data[4],GLfloat wt[4], GLdouble **out)

//void CALLBACK tessCombineVtx(GLdouble coords[3], GLvoid *vtx_data[4],GLfloat wt[4], GLvoid **out)

{

	GLdouble *vtx;

// int i;

	

	vtx = (GLdouble *) malloc(6*sizeof(GLdouble));



	/*

	vtx[0]=((GLdouble *)coords)[0];

	vtx[1]=((GLdouble *)coords)[1];

	vtx[2]=((GLdouble *)coords)[2];

	*/

	vtx[0]=coords[0];

	vtx[1]=coords[1];

	vtx[2]=coords[2];

	

//	for ( i=3; i<6; i++ )

		

/*

		vtx[i] = 

		wt[0]*((GLdouble **)vtx_data)[0][i] + 

		wt[1]*((GLdouble **)vtx_data)[1][i] + 

		wt[2]*((GLdouble **)vtx_data)[2][i] + 

		wt[3]*((GLdouble **)vtx_data)[3][i];

*/		

		

//		vtx[i] = 

//		wt[0]*vtx_data[0][i] + 

//		wt[1]*vtx_data[1][i] + 

//		wt[2]*vtx_data[2][i] + 

//		wt[3]*vtx_data[3][i];

	

	*out = vtx;

}





////////////

// makeDispList

//

// Make the display list which executes the tessilation.

// This is only called if the Exact flag is not set.  Otherwise,

// the vertices must be recalculated every time the object

// moves, so there is no point in making a dispList.

void

CVisPolygon::makeDispList()

{

	// Display List Management

	if(glIsList(dispList)) glDeleteLists(dispList,1);	// If previous list exists, delete it

	dispList=glGenLists(1);										// Get an unused disp list id

	

	glNewList(dispList,GL_COMPILE);  // Begin List





	if(textureFlag){

		double vtx[3];

		glBegin(GL_QUADS);

		vtx[0]=Points[0][0]; vtx[1]=Points[0][1]; vtx[2]=Points[0][2];

		glTexCoord2f(0.0f,1.0f); glVertex3dv(vtx);



		vtx[0]=Points[1][0]; vtx[1]=Points[1][1]; vtx[2]=Points[1][2];

		glTexCoord2f(1.0f,1.0f); glVertex3dv(vtx);



		vtx[0]=Points[2][0]; vtx[1]=Points[2][1]; vtx[2]=Points[2][2];

		glTexCoord2f(1.0f,0.0f); glVertex3dv(vtx);



		vtx[0]=Points[3][0]; vtx[1]=Points[3][1]; vtx[2]=Points[3][2];

		glTexCoord2f(0.0f,0.0f); glVertex3dv(vtx);

		glEnd();

	}

	else makeTess(Points);

//	 makeTess(Points);



	glEndList();	// End List

}





/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////

// Draw



void

CVisPolygon::draw()

{

	if(NPoints>0 && Show){

		

		// Set Color and Lighting Properties

		if(textureFlag){

			glEnable(GL_TEXTURE_2D);

			glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);

			glBindTexture(GL_TEXTURE_2D,textureId);

		}

		else{

#if INDEX_MODE

			glIndexi(ColorIndex);

#else

			glColor4f(Color[0],Color[1],Color[2],Alpha);

#endif

		}

			

		if(Exact){

			// Do the transformations by hand for each point

			// and then use the exact calibration

			

			int m;

			double co,si,x,y;

			

			co = cos(Angle*3.14159/180.0);

			si = sin(Angle*3.14159/180.0);

			Clipped = 0;

			for(m=0;m<NPoints;m++){

				// 1: Rotate

				x = co*Points[m][0] - si*Points[m][1];

				y = si*Points[m][0] + co*Points[m][1];

				// 2: Scale

				x *= Scale;

				y *= Scale;

				// 3: Translate

				x += X;

				y += Y;

				// Remap Through Calibration

				ScrPoints[m][0] = XPosToScreen((float)x,(float)y);

				ScrPoints[m][1] = YPosToScreen((float)x,(float)y);

				ScrPoints[m][2] = Z;

				// Clipped if any vtx is off screen

				if( VISWIN_IS_CLIPPED(ScrPoints[m][0],ScrPoints[m][1]) ) Clipped = 1;

			}



			glMatrixMode (GL_MODELVIEW);	

			glLoadIdentity();



			makeTess(ScrPoints);

			

		} 

		else {

			// Only get exact calibration location of center

			// and approximate the rest of the points

			float x = XPosToScreen((float)X,(float)Y);

			float y = YPosToScreen((float)X,(float)Y);

			

			Clipped = VISWIN_IS_CLIPPED(x,y);



			

			

			DPosToDScreen(JAC,x,y);

			// Rot 4x4, allocated by column, as in matlab

			// Jac, though, is only the 2x2 Jacobian

			ROT[0]=(float)Scale*JAC[0][0]; ROT[1]=(float)Scale*JAC[1][0];

			ROT[4]=(float)Scale*JAC[0][1]; ROT[5]=(float)Scale*JAC[1][1];

			ROT[12]=x; ROT[13]=y; ROT[14]=Z;

			

			glMatrixMode (GL_MODELVIEW);	

			// glLoadIdentity();

			// glTranslatef((float)x,(float)y,Z);      // 3: Translate

			// glScalef((float)scx,(float)scy,1);      // 2: Scale

			glLoadMatrixf(ROT);              // 2: Translate and Scale

			glRotatef((float)Angle,0,0,1);   // 1: Rotate About Z axis

			

			

			// Call List

			glCallList(dispList);

		}

					

		if(textureFlag) glDisable(GL_TEXTURE_2D);

	}

}

