/////////////////////////////////////////////////////
// NumRec: Trouble Linking NR.LIB, so just include here for now
#include "stdafx.h"
#include "math.h"
#include "nrutil_for_regression.h"

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

int ludcmp(float **a, int n, int *indx, float *d)
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
		if (big == 0.0) return 1;
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
	return 0;
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
int
inverse(float **ainv, float **a, int n)
{
  float d;
  int j,i,*indx;
  float *colum;

  colum=vector(1,n);
  indx=ivector(1,n);
  // ainv=matrix(1,n,1,n);  
  
  if( ludcmp(a,n,indx,&d) ) return 1;
  
  for(j=1;j<=n;j++)
    {
      for(i=1;i<=n;i++) colum[i]=0.0;
      colum[j]=1.0;
      lubksb(a,n,indx,colum);
      for(i=1;i<=n;i++) ainv[i][j]=colum[i];
    }
  
  free_vector(colum,1,n);
  free_ivector(indx,1,n);
  return 0;
}


/////////////// REGRESSION
/// 

int
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
	if( ludcmp(xx,dim,indx,&d) ) return 1;
	lubksb(xx,dim,indx,b);

	free_matrix(xt,1,dim,1,n);
	free_matrix(xx,1,dim,1,dim);
	free_ivector(indx,1,n);
	return 0;
}

int
regress(float *b, float **x, float *y, float *w, int n, int dim)
{

	float d;
	float **xt, **xx;
	int *indx,i,j;
	
	xt = matrix(1,dim,1,n);
	transpose(xt,x,n,dim);			// X'
	for(i=1;i<=dim;i++)
		for(j=1;j<=n;j++) 
			xt[i][j] *= w[j];       // X'*W

	xx = matrix(1,dim,1,dim);
	multiply(xx,xt,x,dim,n,dim);	// X'*W*X
	// b  = vector(1,dim);
	multiply(b,xt,y,dim,n);			// X'*W*Y

	//  Here we have  (X'*W*X) b = (X'*W*Y)
	//   where W is diagonal matrix with diagonal elements w

	indx=ivector(1,n);
	if( ludcmp(xx,dim,indx,&d) ) return 1;
	lubksb(xx,dim,indx,b);

	free_matrix(xt,1,dim,1,n);
	free_matrix(xx,1,dim,1,dim);
	free_ivector(indx,1,n);
	return 0;
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

float *vector(long nl, long nh)
/* allocate a float vector with subscript range v[nl..nh] */
{
	float *v;

	v=(float *)malloc((size_t) ((nh-nl+1+NR_END)*sizeof(float)));
	if (!v) return NULL;
	return v-nl+NR_END;
}

int *ivector(long nl, long nh)
/* allocate an int vector with subscript range v[nl..nh] */
{
	int *v;

	v=(int *)malloc((size_t) ((nh-nl+1+NR_END)*sizeof(int)));
	if (!v) return NULL;
	return v-nl+NR_END;
}


float **matrix(long nrl, long nrh, long ncl, long nch)
/* allocate a float matrix with subscript range m[nrl..nrh][ncl..nch] */
{
	long i, nrow=nrh-nrl+1,ncol=nch-ncl+1;
	float **m;

	/* allocate pointers to rows */
	m=(float **) malloc((size_t)((nrow+NR_END)*sizeof(float*)));
	if (!m) return NULL;
	m += NR_END;
	m -= nrl;

	/* allocate rows and set pointers to them */
	m[nrl]=(float *) malloc((size_t)((nrow*ncol+NR_END)*sizeof(float)));
	if (!m[nrl]) return NULL;
	m[nrl] += NR_END;
	m[nrl] -= ncl;

	for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;

	/* return pointer to array of pointers to rows */
	return m;
}

int **imatrix(long nrl, long nrh, long ncl, long nch)
/* allocate an int matrix with subscript range m[nrl..nrh][ncl..nch] */
{
	long i, nrow=nrh-nrl+1,ncol=nch-ncl+1;
	int **m;

	/* allocate pointers to rows */
	m=(int **) malloc((size_t)((nrow+NR_END)*sizeof(int*)));
	if (!m) return NULL;
	m += NR_END;
	m -= nrl;

	/* allocate rows and set pointers to them */
	m[nrl]=(int *) malloc((size_t)((nrow*ncol+NR_END)*sizeof(int)));
	if (!m[nrl]) return NULL;
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

void free_imatrix(int **m, long nrl, long nrh, long ncl, long nch)
/* free an int matrix allocated by matrix() */
{
	free((FREE_ARG) (m[nrl]+ncl-NR_END));
	free((FREE_ARG) (m+nrl-NR_END));
}

/* (C) Copr. 1986-92 Numerical Recipes Software #.,. */

