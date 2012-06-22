// VisCalibrate.cpp : Implementation of CVisServerApp and DLL registration.

#include "stdafx.h"
#include "VisServer.h"
#include "VisCalibrate.h"
#include "VisWindow.h"
#include "VisDisk.h"
#include "ComUtils.h"
#include "math.h"

#include "nrutil.h"
#include "nr.h"

////////// GLOBALS

static float X,Y;
static int tN;
static int tCount = 0;
static int tReady = 0;

static int calibratedFlag = 0;

////////// The Calibration
// Using Quadratic Model:		
//   posDim == 2:   scr = a + b pX + c pY + d pXpX + e pXpY + f pYpY;  
// Start with default unity calibration:	sX = pX; sY=pY;
// Note that for now, posDim==2 always and calN=6, i.e. the 
// model above is used.  So you have to ensure that the key
// data are in the first two dimensions!
static int posDim;   // Dimensionality of Input
static int calN;     // Number of Calibration Parameters  will be 6 for now
static float Xcal[6];
static float Ycal[6];

/////////////////////////////////////////////////////////////////////////////
//

STDMETHODIMP CVisCalibrate::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IVisCalibrate,
	};

	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

/////////////////////////////////////////////////////
// CONSTR/DESTR

CVisCalibrate::CVisCalibrate()
{
	int ct,i,j,k;

	// Allocate data vectors
	tN = REPS*XPTS*YPTS;
	xscr = new float[tN];
	yscr = new float[tN];
	xpos = new float[tN];
	ypos = new float[tN];
	zpos = new float[tN];

	// Precalculate screen target positions
	for(ct=i=0;i<REPS;i++)
	{
		for(j=0;j<XPTS;j++)
		{
			X = (float)(MINX + (MAXX-MINX)*(float)j/(float)(XPTS-1));
			for(k=0;k<YPTS;k++)
			{
				Y = (float)(MINY + (MAXY-MINY)*(float)k/(float)(YPTS-1));
				xscr[ct]=X*VisWindow->width;
				yscr[ct]=Y*VisWindow->height;
				ct++;
			}
		}
	}

	// Reset to the Default Unity Calibration
	ClearCalibration();

	// Turn Logmode off its on in VisWindow
	logmode_hold = VisWindow->logmode;
	if(logmode_hold) VisWindow->put_logmode(0);

	// Create a VisDisk
	HRESULT hr;
	hr = CoInitialize(0);				// initialize COM   
	hr = CoCreateInstance(			// get the interface pointer
		CLSID_VisDisk,  // clsid
		NULL,           // outer unknown
		CLSCTX_SERVER,  // server context
		IID_IVisDisk,	// refid
		(void **)&pID);           // MULTI_QI array

	pID->put_radius((float).005*(VisWindow->width));
	pID->put_fill(0);
	pID->put_show(1);

	tCount=0;
	// posDim = 3;	
	posDim = 2; // For Now, with 2D Display, Must have 2D input
	
	presentTarget();
}


CVisCalibrate::~CVisCalibrate()
{

	pID->Release(); delete xscr; delete yscr; delete xpos; delete ypos;

	// Turn Logmode back on if needed
	VisWindow->put_logmode(logmode_hold);
}

/////////////////////////////////////////////////////
// PROPERTY I/O

STDMETHODIMP CVisCalibrate::get_count(double *pVal)
{
	*pVal = tCount;
	return S_OK;
}

STDMETHODIMP CVisCalibrate::put_count(double newVal)
{
	tCount = (int)newVal;
	return S_OK;
}

STDMETHODIMP CVisCalibrate::get_ready(double *pVal)
{
	*pVal = tReady;
	return S_OK;
}

STDMETHODIMP CVisCalibrate::get_pos(VARIANT *pVal)
{
	double tmp[2];
	if(tCount>=0 && tCount<tN){ tmp[0]=xscr[tCount]; tmp[1]=yscr[tCount]; }
	else { tmp[0]=-1; tmp[1]=-1;}
	VariantFromArray(2,tmp,pVal);
	return S_OK;
}

STDMETHODIMP CVisCalibrate::put_pos(VARIANT newVal)
{
	// In case caller asks, you're not ready for the new target yet
	tReady = 0;

	// This is really ugly, but I wanted to remain Automation Compliant
	// so someday this could be called from matlab.
	int alen;
	double *aptr;
	if( VariantToArray(&alen,&aptr,&newVal) ) return E_INVALIDARG;
	if( alen<2 ) { delete aptr; return E_INVALIDARG; }

	// Now Store Data
	xpos[tCount]=(float)aptr[0];
	ypos[tCount]=(float)aptr[1];
	if(alen>2) zpos[tCount]=(float)aptr[2];
	else posDim = 2;
	
	delete aptr;
	tCount++;

 //HResultErrMessageBox("screw you",S_OK);

	// If done, calulate Calibration and Store
	if(tCount == tN )
	{
		// Remove the disk
		pID->Release();
		// Do the work
		compute();
	}
	// Else prepare next target
	else 
	{
		presentTarget();
	}

	return S_OK;
}



/////////////////////////////////////////////////////
// TARGETS

void
CVisCalibrate::presentTarget()
{

	HRESULT hr;
	VARIANT pVal;
	double pos[2];
	pos[0]=xscr[tCount];
	pos[1]=yscr[tCount];

	// Put Data to the VisDisk
	VariantFromArray(2,pos,&pVal);
	hr = pID->put_pos( pVal );
	VariantClear(&pVal);
	// Ready for Next Position
	tReady=1;
}



/////////////////////////////////////////////////////
// MATH and I/O


//////// Do Calibration and Write
void
CVisCalibrate::compute()
{

	int i;
	float **data,*xcal,*ycal;

	// Use A Quadratic Model
	// Create a data matrix with rows: 1 x y xx xy yy
	if(posDim==2){
		calN=6;
		data = matrix(1,tN,1,calN);
		for(i=1;i<=tN;i++){
			data[i][1]=1;
			data[i][2]=xpos[i-1];
			data[i][3]=ypos[i-1];
			data[i][4]=xpos[i-1]*xpos[i-1];
			data[i][5]=xpos[i-1]*ypos[i-1];
			data[i][6]=ypos[i-1]*ypos[i-1];
		}
	}
	else{	
		calN=10;
		data = matrix(1,tN,1,calN);
		for(i=1;i<=tN;i++){
			data[i][1]=1;
			data[i][2]=xpos[i-1];
			data[i][3]=ypos[i-1];
			data[i][4]=zpos[i-1];
			data[i][5]=xpos[i-1]*xpos[i-1];
			data[i][6]=ypos[i-1]*ypos[i-1];
			data[i][7]=zpos[i-1]*zpos[i-1];
			data[i][8]=xpos[i-1]*ypos[i-1];
			data[i][9]=ypos[i-1]*zpos[i-1];
			data[i][10]=xpos[i-1]*zpos[i-1];
		}
	}
	
	// Do Regression
	// Slow.. computes inverse twice, but that's ok
	xcal = vector(1,calN);
	ycal = vector(1,calN);
	regress(xcal,data,xscr-1,tN,calN);  // Note that NR matrices go [1,N] which xscr goes [0,N-1]
	regress(ycal,data,yscr-1,tN,calN);  // Note that NR matrices go [1,N] which xscr goes [0,N-1]


	// Put the data in the globals and set flag
	for(i=1;i<=calN;i++) { Xcal[i-1]=xcal[i]; Ycal[i-1]=ycal[i]; }
	calibratedFlag=1;

	// Finally, clean up all the NR matrices
	free_matrix(data,1,tN,1,calN);
	free_vector(xcal,1,calN);
	free_vector(ycal,1,calN);

	tReady=-1; // Done Flag

	WriteCalibration();
}


//////// Write Calibration
int
CVisCalibrate::WriteCalibration()
{
	int i;
	// Store in ascii format (with raw data)

	if(!calibratedFlag) return 1;

	FILE *fp = fopen(CALIBRATION_FILENAME,"w");

	if(fp==NULL){ 
		char str[200];
		sprintf(str,"Can't open calibration file %s. Check directory permissions",CALIBRATION_FILENAME);
		MessageBox(NULL,str,"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return 1; 
	}


	// 1: Write calN and posDim
	fprintf(fp,"%d %d\n",calN,posDim);

	// 2: Write data 
	//   Xcal 1xcalN
	//   Ycal 1xcalN
	for(i=0;i<calN;i++) fprintf(fp,"%f ",Xcal[i]);
	fprintf(fp,"\n");
	for(i=0;i<calN;i++) fprintf(fp,"%f ",Ycal[i]);
	
	// 3: In case user wants to manually inspect data -- never used here
	//   xscr yscr xpos ypos
	fprintf(fp,"\n\nRawData:\n");
	for(i=0;i<tN;i++) 
		fprintf(fp,"%f\t%f\t%f\t%f\t%f\n",xscr[i],yscr[i],xpos[i],ypos[i],zpos[i]);

	fclose(fp);
	return 0;
}


/////////////////////////////////////////////////////
// EXTERNALLY USED


//////// Unset Calibration
void
ClearCalibration()
{
	calibratedFlag=0;
}


//////// Read Calibration
int
ReadCalibration()
{
	FILE *fp = fopen(CALIBRATION_FILENAME,"r");
	if(!fp){
		ClearCalibration();
		return 1;
	}

	char str[360];
	// Read 1st Line: Ndat posDim
	fgets(str,360,fp);
	if( sscanf(str,"%d %d",&calN,&posDim) < 2 )
	{
		ClearCalibration();
		return 1;
	}
	// Read 2nd Line
	fgets(str,360,fp);
	if( sscanf(str,"%f %f %f %f %f %f",Xcal,Xcal+1,Xcal+2,Xcal+3,Xcal+4,Xcal+5) < 6 )
	{
		ClearCalibration();
		return 1;
	}
	// Read 3rd Line
	fgets(str,360,fp);
	if( sscanf(str,"%f %f %f %f %f %f",Ycal,Ycal+1,Ycal+2,Ycal+3,Ycal+4,Ycal+5) < 6 )
	{
		ClearCalibration();
		return 1;
	}
	
	fclose(fp);
	// Success
	calibratedFlag=1;
	return 0;
}

///////////////

int IsCalibrated(){ return calibratedFlag; }



////////////////////////////////////////////
////   RUNTIME Conversion from Pos to Screen:
// For now, we only handle posDim==2 and Ncal==6
float
XPosToScreen(float xp, float yp)
{
	if(calibratedFlag) 
		return Xcal[0] + Xcal[1]*xp + Xcal[2]*yp + Xcal[3]*xp*xp + Xcal[4]*xp*yp + Xcal[5]*yp*yp;
	else return xp;
}

float
YPosToScreen(float xp, float yp)
{
	if(calibratedFlag)
		return Ycal[0] + Ycal[1]*xp + Ycal[2]*yp + Ycal[3]*xp*xp + Ycal[4]*xp*yp + Ycal[5]*yp*yp;
	else return yp;
}

// Jacobian for Pos->Screen
// J = dS/dX
void
DPosToDScreen(float J[][2], float xp, float yp)
{
	if(calibratedFlag)
	{
		/*
		J[0][0] = Xcal[1] + 2*Xcal[3]*xp + Xcal[4]*yp;
		J[0][1] = Xcal[2] + 2*Xcal[5]*yp + Xcal[4]*xp;
		J[1][0] = Ycal[1] + 2*Ycal[3]*xp + Ycal[4]*yp;
		J[1][1] = Ycal[2] + 2*Ycal[5]*yp + Ycal[4]*xp;
		*/
		J[0][0] = J[1][1] = sqrt(Xcal[1]*Xcal[1] + Xcal[2]*Xcal[2])/2. + sqrt(Ycal[1]*Ycal[1] + Ycal[2]*Ycal[2])/2.;
		J[0][1] = J[1][0] = 0.;
	}
	else{
		J[0][0]=J[1][1]=1.;
		J[0][1]=J[1][0]=0.;
	}
}


/////////////////////////////////////////////////////
// NumRec: Trouble Linking NR.LIB, so just include here for now
#include "math.h"

/////////// LUBKSB
void lubksb(float **a, int n, int *indx, float b[])
{
	int i,ii=0,ip,j;
	float sum;

	for (i=1;i<=n;i++) {
		ip=indx[i];
		sum=b[ip];
		b[ip]=b[i];
		if (ii)
			for (j=ii;j<=i-1;j++) sum -= a[i][j]*b[j];
		else if (sum) ii=i;
		b[i]=sum;
	}
	for (i=n;i>=1;i--) {
		sum=b[i];
		for (j=i+1;j<=n;j++) sum -= a[i][j]*b[j];
		b[i]=sum/a[i][i];
	}
}
/* (C) Copr. 1986-92 Numerical Recipes Software #.,. */

/////////// LUDCMP
#define TINY 1.0e-20;

void ludcmp(float **a, int n, int *indx, float *d)
{
	int i,imax,j,k;
	float big,dum,sum,temp;
	float *vv;

	vv=vector(1,n);
	*d=1.0;
	for (i=1;i<=n;i++) {
		big=0.0;
		for (j=1;j<=n;j++)
			if ((temp=(float)fabs(a[i][j])) > big) big=temp;
		if (big == 0.0) nrerror("Singular matrix in routine ludcmp");
		vv[i]=1.0f/big;
	}
	for (j=1;j<=n;j++) {
		for (i=1;i<j;i++) {
			sum=a[i][j];
			for (k=1;k<i;k++) sum -= a[i][k]*a[k][j];
			a[i][j]=sum;
		}
		big=0.0;
		for (i=j;i<=n;i++) {
			sum=a[i][j];
			for (k=1;k<j;k++)
				sum -= a[i][k]*a[k][j];
			a[i][j]=sum;
			if ( (dum=vv[i]*(float)fabs(sum)) >= big) {
				big=dum;
				imax=i;
			}
		}
		if (j != imax) {
			for (k=1;k<=n;k++) {
				dum=a[imax][k];
				a[imax][k]=a[j][k];
				a[j][k]=dum;
			}
			*d = -(*d);
			vv[imax]=vv[j];
		}
		indx[j]=imax;
		if (a[j][j] == 0.0) a[j][j]=(float)TINY;
		if (j != n) {
			dum=1.0f/(a[j][j]);
			for (i=j+1;i<=n;i++) a[i][j] *= dum;
		}
	}
	free_vector(vv,1,n);
}
#undef TINY
/* (C) Copr. 1986-92 Numerical Recipes Software #.,. */

// MyStuff.cpp

////////////
////////////  NOTE the NR convention seems to be that output matrices are
////////////  allocated by called.  I'm following that here, but 
////////////  including commented out allocation lines for reference.
////////////

/////////////// MATRIX INVERSE!!
void
inverse(float **ainv, float **a, int n)
{
  float d;
  int j,i,*indx;
  float *colum;

  colum=vector(1,n);
  indx=ivector(1,n);
  // ainv=matrix(1,n,1,n);  
  
  ludcmp(a,n,indx,&d);
  
  for(j=1;j<=n;j++)
    {
      for(i=1;i<=n;i++) colum[i]=0.0;
      colum[j]=1.0;
      lubksb(a,n,indx,colum);
      for(i=1;i<=n;i++) ainv[i][j]=colum[i];
    }
  
  free_vector(colum,1,n);
  free_ivector(indx,1,n);
}


/////////////// REGRESSION
/// 

void
regress(float *b, float **x, float *y, int n, int dim)
{

	float d;
	float **xt, **xx;
	int *indx;
	
	xt = matrix(1,dim,1,n);
	transpose(xt,x,n,dim);			// X'
	xx = matrix(1,dim,1,dim);
	multiply(xx,xt,x,dim,n,dim);	// X'*X
	// b  = vector(1,dim);
	multiply(b,xt,y,dim,n);			// X'*Y

	// From NR:
	//	"To summarize, this is the preferred way to solve the linear set of equations A . x = b:
	//	    float **a,*b,d;
	//	    int n,*indx;
	//		...
	//		ludcmp(a,n,indx,&d);
	//		lubksb(a,n,indx,b);
	//
	//   The answer x will be given back in b. Your original matrix A will have been destroyed."
	//
	//  In our case, we have (X'X) b = (X'Y)

	indx=ivector(1,n);
	ludcmp(xx,dim,indx,&d);
	lubksb(xx,dim,indx,b);
}


/////////////////  TRANSPOSE
void
transpose(float **at, float **a, int n, int m)
{
	int i,j;
	// at = matrix(1,m,1,n);
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			at[j][i]=a[i][j];
}



/////////////////  MATRIX MULT

void
multiply(float **c, float **a, float **b, int n, int o, int m)
{
	int i,j,k;
	// c=matrix(1,n,1,m);
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++){
			c[i][j]=0;
			for(k=1;k<=o;k++) c[i][j] += a[i][k]*b[k][j];
		}
}

void
multiply(float *c, float **a, float *b, int n, int m)
{
	int i,j;
	// c=vector(1,n);
	for(i=1;i<=n;i++){
		c[i]=0;
		for(j=1;j<=m;j++) c[i] += a[i][j]*b[j];
	}

}


void
multiply(float *c, float *a, float **b, int n, int m)
{
	int i,j;
	// c=vector(1,m);
	for(j=1;j<=m;j++){
		c[j]=0;
		for(i=1;i<=n;i++) c[j] += a[i]*b[i][j];
	}

}



/* CAUTION: This is the ANSI C (only) version of the Numerical Recipes
   utility file nrutil.c.  Do not confuse this file with the same-named
   file nrutil.c that is supplied in the same subdirectory or archive
   as the header file nrutil.h.  *That* file contains both ANSI and
   traditional K&R versions, along with #ifdef macros to select the
   correct version.  *This* file contains only ANSI C.               */
#define NR_END 1
#define FREE_ARG char*

void nrerror(char error_text[])
/* Numerical Recipes standard error handler */
{
	fprintf(stderr,"Numerical Recipes run-time error...\n");
	fprintf(stderr,"%s\n",error_text);
	fprintf(stderr,"...now exiting to system...\n");
	exit(1);
}

float *vector(long nl, long nh)
/* allocate a float vector with subscript range v[nl..nh] */
{
	float *v;

	v=(float *)malloc((size_t) ((nh-nl+1+NR_END)*sizeof(float)));
	if (!v) nrerror("allocation failure in vector()");
	return v-nl+NR_END;
}

int *ivector(long nl, long nh)
/* allocate an int vector with subscript range v[nl..nh] */
{
	int *v;

	v=(int *)malloc((size_t) ((nh-nl+1+NR_END)*sizeof(int)));
	if (!v) nrerror("allocation failure in ivector()");
	return v-nl+NR_END;
}


float **matrix(long nrl, long nrh, long ncl, long nch)
/* allocate a float matrix with subscript range m[nrl..nrh][ncl..nch] */
{
	long i, nrow=nrh-nrl+1,ncol=nch-ncl+1;
	float **m;

	/* allocate pointers to rows */
	m=(float **) malloc((size_t)((nrow+NR_END)*sizeof(float*)));
	if (!m) nrerror("allocation failure 1 in matrix()");
	m += NR_END;
	m -= nrl;

	/* allocate rows and set pointers to them */
	m[nrl]=(float *) malloc((size_t)((nrow*ncol+NR_END)*sizeof(float)));
	if (!m[nrl]) nrerror("allocation failure 2 in matrix()");
	m[nrl] += NR_END;
	m[nrl] -= ncl;

	for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;

	/* return pointer to array of pointers to rows */
	return m;
}


void free_vector(float *v, long nl, long nh)
/* free a float vector allocated with vector() */
{
	free((FREE_ARG) (v+nl-NR_END));
}

void free_ivector(int *v, long nl, long nh)
/* free an int vector allocated with ivector() */
{
	free((FREE_ARG) (v+nl-NR_END));
}


void free_matrix(float **m, long nrl, long nrh, long ncl, long nch)
/* free a float matrix allocated by matrix() */
{
	free((FREE_ARG) (m[nrl]+ncl-NR_END));
	free((FREE_ARG) (m+nrl-NR_END));
}

/* (C) Copr. 1986-92 Numerical Recipes Software #.,. */


