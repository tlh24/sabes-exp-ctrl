// MyStuff.cpp

#include "nrutil.h"
#include "nr.h"

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

void
outer(float **c, float *a, float *b, int n, int m)
{
	int i,j;
	// c=matrix(1,n,1,m);
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			c[i][j] = a[i]*b[j];
}

float
inner(float *a, float *b, int n)
{
	int i;
	float c=0;
	for(i=1;i<=n;i++) c=a[i]*b[i];
	return c;
}










