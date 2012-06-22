// #include "stdafx.h"

#include <malloc.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Local
#include "Matrix.h"

#define M_PI 3.14159

#pragma warning (disable: 4244)  // Don't want to see conversion warnings


///// ERROR REPORTING
extern void CommonError(char *);
char commonErrorString[200];
#define ERR2(func,p,q) {sprintf(commonErrorString,"Error in " #func ": Matrices are  %i x %i and %i x %i\n",p.row,p.col,q.row,q.col);CommonError(commonErrorString);}
#define ERR1(func,p) {sprintf(commonErrorString,"Error in " #func ": Matrix is  %i x %i\n",p.row,p.col),exit(0);CommonError(commonErrorString);}
#define ERR0(func) {sprintf(commonErrorString,#func"\n");CommonError(commonErrorString);}
#define MEMERR {sprintf(commonErrorString,"Memory Error\n");CommonError(commonErrorString);}


/******************************************************************/
/******************************************************************/
/***********************MEMORY ALLOCATION**************************/
/******************************************************************/
/******************************************************************/

/* Assigns memory for a double ** array and initialises all elements ot zero*/

double **dmatrix(int row,int col)
{
  int i,x,y;
  double **m;
  
  if(!( m=(double **) malloc((unsigned) (row+1)*sizeof(double*)))) MEMERR;
  
  for(i=0;i<=row;i++) 
    if(!(m[i]=(double *) malloc((unsigned) (col+1)*sizeof(double)))) MEMERR;;
  
  for(x=0;x<=row;x++)
    for(y=0;y<=col;y++)
      m[x][y]=0.0;
  
  return m;
}

/******************************************************************/ 
float **fmatrix(int row,int col)
{
  int i,x,y;
  float **m;
  
if(!(  m=(float **) malloc((unsigned) (row+1)*sizeof(float*))))MEMERR;
  
  for(i=0;i<=row;i++) 
if(!(    m[i]=(float *) malloc((unsigned) (col+1)*sizeof(float))))MEMERR;
  
  
  for(x=0;x<=row;x++)
    for(y=0;y<=col;y++)
      m[x][y]=0.0;
  
  return m;
}

/******************************************************************/ 
double *dvector(int row)
{
  int x;
  double *m;
  
if(!(  m=(double *) malloc((unsigned) (row+1)*sizeof(double))))MEMERR;
  
  for(x=0;x<=row;x++)      m[x]=0.0;
  
  return m;
}
/******************************************************************/ 
float *fvector(int row)
{
  int x;
  float *m;
  
  if(!(  m=(float *) malloc((unsigned) (row+1)*sizeof(float)))) MEMERR;
  
  for(x=0;x<=row;x++)      m[x]=0.0;
  
  return m;
}
/******************************************************************/ 
int *ivector(int row)
{
  int x;
  int *m;
  
  if(!(m=(int *) malloc((unsigned) (row+1)*sizeof(int))))MEMERR;
  
  for(x=0;x<=row;x++)      m[x]=0;
  
  return m;
}
/******************************************************************/ 
/******************************************************************/
/******************MATRIX ASSIGNMENT (=) ***************************/
/******************************************************************/
/******************************************************************/
void matrix::operator=(matrix& q)
{
  int i,j;

  for(i=0;i<=row;i++) delete [] m[i];
  delete [] m;

  row=q.row;
  col=q.col;
  
  m=fmatrix(row,col);
  
  
  for(i=1;i<=row;i++) 
    for(j=1;j<=col;j++) m[i][j]=q.m[i][j]; 
}

/******************************************************************/ 

matrix mat(float f)
{
  matrix d;
  d(1,1)=f;
  return d;
}
/******************************************************************/ 
matrix mat(double f)
{
  matrix d;
  d(1,1)=f;
  return d;
}
/******************************************************************/ 
matrix mat(int f)
{
  matrix d;
  d(1,1)=f;
  return d;
}

/******************************************************************/ 
void rowassign(matrix& p,int k, matrix& q)
{
  int i;
  for(i=1;i<=cols(p);i++) p(k,i)=q(1,i);
}

/******************************************************************/ 
void colassign(matrix& p,int k, matrix& q)
{
  int i;
  for(i=1;i<=rows(p);i++) p(i,k)=q(i,1);
}

/******************************************************************/ 

matrix::matrix(matrix& q)
{
  int i,j;

  row=q.row;
  col=q.col;
  
  m=fmatrix(row,col);
    
  for(i=1;i<=row;i++) 
    for(j=1;j<=col;j++) m[i][j]=q.m[i][j]; 
  
}
/******************************************************************/
/******************************************************************/
/******************MEMORY DEALLOCATION*****************************/
/******************************************************************/
/******************************************************************/
 matrix::~matrix()
{
  int i;
  for(i=0;i<=row;i++) delete [] m[i];
  delete [] m;
}
/******************************************************************/ 
void dump(double **q,int row,int col)
{
  int i;
  for(i=0;i<=row;i++) free((double*) (q[i]));
  free((double**) (q));
}
/******************************************************************/ 
void dump(float **q,int row,int col)
{
  int i;
  for(i=0;i<=row;i++) free((float*) (q[i]));
  free((float**) (q));
}
/******************************************************************/ 
void dump(double *v)
{
  free((double*)v);
}

/******************************************************************/ 
void dump(float *v)
{
  free((float*)v);
}

/******************************************************************/ 
void dump(int *v)
{
  free((int*)v);
}

/******************************************************************/
/******************************************************************/
/******************  STATISTICS   *********************************/
/******************************************************************/
/******************************************************************/
float sum(matrix& p)
{
  int i,j;
  float sum=0.0;
  for(i=1;i<=p.row;i++)
    for(j=1;j<=p.col;j++) sum+=p.m[i][j];
  return sum ;
}

/******************************************************************/ 
matrix rowsum(matrix& p)
{
  int i,j;
  matrix r(p.row,1);
  for(i=1;i<=p.row;i++) 
    for(j=1;j<=p.col;j++) r.m[i][1]+=p.m[i][j]; 
  
  
  return r;
}
/******************************************************************/ 
matrix colsum(matrix& p)
{
  int i,j;
  matrix r(1,p.col);
  for(i=1;i<=p.col;i++) 
    for(j=1;j<=p.row;j++) r.m[1][i]+=p.m[j][i] ;
  return r;
}

/******************************************************************/ 
float prod(matrix& p)
{
  int i,j;
  float x=1.0;
  
  for(i=1;i<=p.row;i++)
    for(j=1;j<=p.col;j++) x*=p.m[i][j];
  
  return x;
}

/******************************************************************/ 
float mmin(matrix& p)
{
  int i,j;
  float x=p.m[1][1];
  
  for(i=1;i<=p.row;i++)
    for(j=1;j<=p.col;j++) if(p.m[i][j]<x) x=p.m[i][j];
  return x ;
}

/******************************************************************/ 
float mmax(matrix& p)
{
  int i,j;
  float x=p.m[1][1];
  
  for(i=1;i<=p.row;i++)
    for(j=1;j<=p.col;j++) if(p.m[i][j]>x) x=p.m[i][j];
  return x ;
}

/******************************************************************/ 

float urand(float a,float b)
{
  float g;
  
  g= (float)rand()/(float)RAND_MAX;
  g=(b-a)*g;
  g+=a;
  return(g);
}
/******************************************************************/ 
int  rand(int a,int b)
{
  float g;
  
  g= urand((float)a,(float)(b+0.99999));
  g=floor(g);

  return (int)g;
}
/******************************************************************/ 
float gauss(float mean, float sd)
{
  float x1,y1,x2,y2,d,e; 
  x1=urand(0.0,1.0);
  x2=urand(0.0,1.0);
  d=urand(0.0,1.0);
  
  y1=(cos(2*M_PI*x2))*sqrt(-2*log(x1));
  y2=(sin(2*M_PI*x2))*sqrt(-2*log(x1));
  
  e=y1;
  if(d<0.5) e=y2;
  return ((e*sd)+mean);
}
/******************************************************************/ 
float mean(matrix& p)
{
  return scalar(colmean(rowmean(p)));
}
/******************************************************************/ 
matrix colmean(matrix& p)
{ 
  matrix r(1,p.col);
  
  r= colsum(p)/p.row;
  return r;
}
/****************************************************************/ 
matrix rowmean(matrix& p)
{
  matrix r(p.row,1);
  
  r= rowsum(p)/p.col;
  return r;
}
/******************************************************************/ 
float var(matrix& p)
{ 
  if(p.row==1) return scalar(rowvar(p));
  else if(p.col==1) return scalar(colvar(p));
  else   ERR1(var,p);
  return 0;
}
/******************************************************************/ 
matrix colvar(matrix& p)
{ 
  matrix r(1,p.col);
  
  r= colmean(p^p) - ( colmean(p) ^  colmean(p));
  return r;
}
/******************************************************************/ 
matrix rowvar(matrix& p)
{ 
  matrix r(p.row,1);
  
  r= rowmean(p^p) - (rowmean(p) ^ rowmean(p));
  return r;
}
/******************************************************************/ 
matrix cov(matrix& p,matrix& q)
{
  matrix r(1,1);
  
  if(p.col==q.col && p.row==q.row)
    {
      if(p.col==1) 
	{
	  r=dim(p.row,1);
	  r=colmean(p^q)- (colmean(p) ^ colmean(q));
	}
      else if(p.row==1) 
	{
	  r=dim(1,p.col);
	  r=rowmean(p^q) - (rowmean(p) ^ rowmean(q));
	}
    }
  else ERR2(cov,p,q);
  
  return r;
}
/******************************************************************/ 
matrix smooth(matrix& p,float sigma,int bins)
{
  float f,sum;
  float from,to,step;
  int i,j;
  matrix r(bins,2);
  
  from=mmin(p);
  to=mmax(p);
  step=(to-from)/(float)bins;
  
  for(i=1;i<=bins;i++)
    {
      f=from+(float)i*step;
      sum=0;
      
      for(j=1;j<=rows(p);j++) 
	sum+=exp(-0.5*sqr((p(j,1)-f)/sigma));
      
      r(i,1)=f;
      r(i,2)=sum/((float)rows(p)*sigma*sqrt(2.0*M_PI));
    }
  return r;
}

/******************************************************************/
matrix smooth(matrix& p,matrix &w,float sigma,int bins)
{
  float f,tsum;
  float from,to,step;
  int i,j;
  matrix r(bins,2);
  
  from=mmin(p);
  to=mmax(p);
  step=(to-from)/(float)bins;
  
  for(i=1;i<=bins;i++)
    {
      f=from+(float)i*step;
      tsum=0;
      
      for(j=1;j<=rows(p);j++) 
	tsum+=w(j,1)*exp(-0.5*sqr((p(j,1)-f)/sigma));
      
      r(i,1)=f;
      r(i,2)=tsum/((float)sum(w)*sigma*sqrt(2.0*M_PI));
    }
  return r;
}

/******************************************************************/
/******************************************************************/
/****************MATRIX EXTRACTION*********************************/
/******************************************************************/
/******************************************************************/

/******************************************************************/ 
float scalar(matrix& r) { return r(1,1);}

/******************************************************************/ 
matrix matrix::operator[](int c)
{
  int j;                                                           
  matrix r(row,1);
  
  for(j=1;j<=row;j++) r.m[j][1]=m[j][c];
  
  return r;
}

/******************************************************************/ 
matrix matrix::operator()(int c)
{
  int j;
  matrix r(1,col);
  
  for(j=1;j<=col;j++) r.m[1][j]=m[c][j];
  
  return r;
}

/******************************************************************/  
matrix matrix::operator()(int a,int b, int c, int d)
{
  int i,j;
  matrix r(c-a+1,d-b+1);
  
  for(i=1;i<=r.row;i++) 
    for(j=1;j<=r.col;j++) r.m[i][j]=m[a+i-1][b+j-1];
  
  return r;
}
/******************************************************************/ 
matrix matrix::colex(int a, ...)
{
  int k=1,i,j;
  int c;
  int rs[100]; 
  va_list argp;
  
  va_start(argp,a);
  rs[k]=a;
  while((c=va_arg(argp,int))!=0)      rs[++k]=c;
  
  va_end(argp);
  
  matrix r(row,k);
  
  for(i=1;i<=row;i++) 
    for(j=1;j<=k;j++) r.m[i][j]=m[i][rs[j]] ;
  
  return(r);
}

/******************************************************************/ 
int rows(matrix& p)
{
  int r;
  r=p.row;
  return r;
}
/******************************************************************/ 

int cols(matrix& p)
{
  int r;
  r=p.col;
  return r;
}
/******************************************************************/ 
matrix matrix::operator()(matrix& p)
{
  int i,j,k;
  matrix r(1,1);
  
  if((p.row==1) && (p.col==col))
    {
       /* selecting out columns*/
      j=(int)sum(abs(p)>0.0);
      
      r=dim(row,j);
      
      for(i=1,k=0;i<=p.col;i++) 
	if(p.m[1][i]) 
	  {
	    k++;
	    for(j=1;j<=r.row;j++) r.m[j][k]=m[j][i];
	  } 
    } 
  
  else if((p.row==row) && (p.col==1)) 
    {
      /* select out rows*/
      j=(int)sum(abs(p)>0.0);
      r=dim(j,col);
      
      for(i=1,k=0;i<=p.row;i++) 
	if(p.m[i][1]) 
	  {
	    k++;
	    for(j=1;j<=r.col;j++) r.m[k][j]=m[i][j];
	  } 
    }
  
  else if((p.row==row) && (p.col==col))
    {
      /* God knows what to do here??*/
      r=dim(p.row,p.col);
      for(i=1;i<=p.row;i++) 
	for(j=1;j<=r.col;j++) r.m[i][j]=m[i][j];
    } 
  else 
    {
      CommonError("Error in () operator\n");
      exit(0);
    }
   return r;
}

/******************************************************************/ 
matrix matrix::operator()(int x, matrix& p)
{
  int i,j,k;
  matrix r(1,1);
  
  if((p.row==1) && (p.col==col))
    {
      /* selecting out columns*/
      
      j=(int)sum(abs(p)>0.0);
      r=dim(1,j);
      
      for(i=1,k=0;i<=p.col;i++) 
	if(p.m[1][i]) 
	  {
	    k++;
	    r.m[1][k]=m[x][i];
	  } 
    } 
  else 
    {
      CommonError("Error in () operator\n");
      exit(0);
    }
  
   return r;
}

/******************************************************************/ 
matrix matrix::operator()(matrix& p, int y)
{
  int i,j,k;
  matrix r(1,1);

 if((p.row==row) && (p.col==1)) 
   {
     /* select out rows*/
     j=(int)sum(abs(p)>0.0);
     r=dim(j,1);
     
     for(i=1,k=0;i<=p.row;i++) 
       if(p.m[i][1]) 
	 {
	   k++;
	   r.m[k][1]=m[i][y];
	 } 
    }
 else 
   {
     CommonError("Error in () operator\n");
     exit(0);
   }
    return r;
}



/******************************************************************/
/******************************************************************/
/***************MATH ROUTINES  ************************************/
/******************************************************************/
/******************************************************************/
matrix abs(matrix& p)
{
  int i,j;
  matrix r(p.row,p.col);
  
  for(i=1;i<=p.row;i++)
    for(j=1;j<=p.col;j++) r.m[i][j]=fabs(p.m[i][j]);
  return r ;
}
/******************************************************************/ 
matrix pow(matrix& p, float n)
{
  int i,j;
  matrix r(1,1);

  if(p.col==p.row) 
    {
      r=I(p.row);
        for(i=1;i<=n;i++) r*=p;
    }
  else if(p.col!=p.row) 
    {
      r=dim(p.row,p.col);
        for(i=1;i<=p.row;i++)
	  for(j=1;j<=p.col;j++) r.m[i][j]=pow((double)p.m[i][j],(double)n); 
    }

  return r ;
}
/******************************************************************/ 
matrix pow(matrix& p, int n)
{
return pow(p,(float)n);
}
/******************************************************************/ 
float pow(float a, float b)
{
return pow((double)a,(double)b);
}
/******************************************************************/ 
int pow(int a,int b)
{
return (int)pow((double)a,(double)b);
}
/******************************************************************/ 
matrix sqrt(matrix& p)
{
  int i,j;
  matrix r(p.row,p.col);
  
  for(i=1;i<=p.row;i++)
    for(j=1;j<=p.col;j++) r.m[i][j]=sqrt(p.m[i][j]);
  
  return r ;
}
/******************************************************************/ 
matrix sgn(matrix& p)
{
  int i,j;
  matrix r(p.row,p.col);
  
  for(i=1;i<=p.row;i++)
    for(j=1;j<=p.col;j++)
      {
	if(p.m[i][j]<0)  r.m[i][j]=-1.0;
	else if (p.m[i][j]>0) r.m[i][j]=1.0;
	else r.m[i][j]=0.0;
      }
  
  return r ;
}

/******************************************************************/ 
matrix apply(matrix& p,double (*func)(double x))
{
  int i,j;
  matrix r(p.row,p.col);  
  
  for(i=1;i<=p.row;i++)
    for(j=1;j<=p.col;j++) r.m[i][j]=(*func)(p.m[i][j]);
  
  return r;
}

/******************************************************************/ 
matrix apply(matrix& p,matrix& q,double (*func)(double x, double y))
{
  int i,j;
  matrix r(p.row,p.col);  
  
 if(p.col==q.col && p.row==q.row)
   for(i=1;i<=p.row;i++)
    for(j=1;j<=p.col;j++) r.m[i][j]=(*func)(p.m[i][j],q.m[i][j]);
   else ERR2(apply,p,q);
  return r;
}

/******************************************************************/ 
matrix apply(matrix& p,matrix& q,float (*func)(float x, float y))
{
  int i,j;
  matrix r(p.row,p.col);  
  
  if(p.col==q.col && p.row==q.row)
    for(i=1;i<=p.row;i++)
      for(j=1;j<=p.col;j++) r.m[i][j]=(*func)(p.m[i][j],q.m[i][j]);
  else ERR2(apply,p,q);
  
  return r;
}
/******************************************************************/ 
matrix apply(matrix& p,float (*func)(float x))
{
  int i,j;
  matrix r(p.row,p.col);  
  
  for(i=1;i<=p.row;i++)
    for(j=1;j<=p.col;j++) r.m[i][j]=(*func)(p.m[i][j]);
  
  return r;
}

/******************************************************************/ 
float reciprocal(float x)
{
  return 1.0/x;
}

/******************************************************************/ 
float logistic(float x)
{
  return 1.0/(1+exp(-x));
}
/******************************************************************/ 
float sgn(float x)
{
  if(x<0) return -1.0;
  else if (x>0) return 1.0;
  else return 0.0;
}
/******************************************************************/ 
float logistic_map(float x)
{
  return 4.0*x*(1-x);
}
/******************************************************************/ 
float deriv_logistic(float x)
{
  float p;
  p=logistic(x);
  return p*(1-p);
}

/******************************************************************/
/******************************************************************/
/*****************MATRIX REORGANISATION****************************/
/******************************************************************/
/******************************************************************/
matrix operator~(matrix& p)
{
  int i,j;
  matrix r(p.col,p.row);
  
  for(i=1;i<=p.row;i++)
    for(j=1;j<=p.col;j++) r.m[j][i]=p.m[i][j];
  
  
  return r;
}


/******************************************************************/
/******************************************************************/
/****************MATRIX CREATION***********************************/
/******************************************************************/
/******************************************************************/

 matrix::matrix(int a=1,int b=1)
{
  int x,y;
  row=a;
  col=b;
  
  m=fmatrix(a,b);
  
  for(x=0;x<=row;x++)
    for(y=0;y<=col;y++)
      m[x][y]=0.0;
}
/******************************************************************/ 
 matrix::matrix(int a=1)
{
  int x,y;
  row=a;
  col=1;
  
  m=fmatrix(a,1);
  
  for(x=0;x<=row;x++)
    for(y=0;y<=col;y++)
      m[x][y]=0.0;
  }
/******************************************************************/ 
 matrix::matrix()
{
  int x,y;
  row=1;
  col=1;
  
  m=fmatrix(1,1);
  
  for(x=0;x<=row;x++)
    for(y=0;y<=col;y++)
      m[x][y]=0.0;
}
/******************************************************************/ 
matrix dim(int a=1,int b=1)
{
  matrix r(a,b);
  return r;
}
/******************************************************************/
matrix dim(int a=1)
{
matrix r(a,1);
return r;
}
/******************************************************************/ 
matrix I(int n)
{
  int i;
  
  matrix r(n,n);
  for(i=1;i<=n;i++) r.m[i][i]=1.0;
  
  return r;
}

/*****************************************************************/
matrix repeat(float f, int n)
{
  matrix r(n,1);
  set(r,f);  
  return r;
}

/*****************************************************************/
matrix repeat(int a, int n)
{
  return repeat((float)a,n);
}

/*****************************************************************/
matrix rotate(float theta)
{
matrix r(2,2);

r(1,1)=r(2,2)=cos(theta);
r(1,2)=sin(theta);
r(2,1)=-r(1,2);
return r;
}

/*****************************************************************/
matrix series(int a, int b)
{
matrix r(1,1);

  int i,x;
  if(b>a)
    {
      x=b-a+1;
      r=dim(x,1);
      for(i=1;i<=x;i++) r.m[i][1]=(float)(a+i-1);
    }
  else
    {
      x=-(b-a+1);
      matrix r(x,1);
      for(i=1;i<=x;i++) r.m[i][1]=(float)(b-i+1);
    }
  return r;
}

/*****************************************************************/
matrix series(int a, int b ,int c)
{
  return series((float)a, (float)b, (float)c);
}
/******************************************************************/ 
matrix series(float a, float b , float c)
{
  int i;
  matrix r(1,1);

  float k=a;
  int n=0;
  
  while(k<=b)
    {
      k+=c;
      n++;
    }
  
  r=dim(n,1);

  for(i=1;i<=n;i++)  r.m[i][1]=a+(float)(i-1)*c;

  return r;
}


/*****************************************************************/
matrix copy(matrix& p)
{
  int i,j;
  matrix r(p.row,p.col);
  
  for(i=1;i<=p.row;i++)
    for(j=1;j<=p.col;j++)
      r.m[i][j]=p.m[i][j];
  
  return r;
}

/******************************************************************/ 
matrix diagonal(matrix& p)
{
  int i;
  matrix r(1,1);

  if(p.col==1) 
    {
      r=dim(p.row,p.row);
      
      for(i=1;i<=p.row;i++) r.m[i][i]=p.m[i][1];
    }
  else if(p.row==1) 
    {
       r=dim(p.col,p.col);
      
      for(i=1;i<=p.col;i++) r.m[i][i]=p.m[1][i];
    }
  else if(p.row==p.col)
    { 
       r=dim(p.row,1);
      
      for(i=1;i<=p.row;i++) r.m[i][1]=p.m[i][i];
    }
  else 
    {
      ERR1(diagonal,p);
    }  
  return r;
}

/******************************************************************/
matrix offdiagonal(matrix& p)
{
  int i;
  matrix r(1,1);

  if(p.col==1) 
    {
      r=dim(p.row,p.row);
      
      for(i=1;i<=p.row;i++) r.m[i][r.col+1-i]=p.m[i][1];
    }
  else if(p.row==1) 
    {
       r=dim(p.col,p.col);
      
      for(i=1;i<=p.col;i++) r.m[i][r.col+1-i]=p.m[1][i];
    }
  else if(p.row==p.col)
    { 
       r=dim(p.row,1);
      
      for(i=1;i<=p.row;i++) r.m[i][1]=p.m[i][p.col+1-i];
    }
  else 
    {
      ERR1(diagonal,p);
    }  
  return r;
}

/******************************************************************/
matrix zeros(int n,int m)
{
  matrix r(n,m);
  
  int i,j;
  for(i=1;i<=n;i++)
    for(j=1;j<=m;j++) r.m[i][j]=0.0;
  return r;
}

/******************************************************************/
/******************************************************************/
/****************   MATRIX IO   ***********************************/
/******************************************************************/
/******************************************************************/ 
void dis(matrix& d)
{ 
dis(" ",d);
}
/******************************************************************/ 
void dis(char *s,matrix& d)
{
  int i,j;
  fprintf(stderr,"Matrix %s is %i by %i\n",s,d.row,d.col);
  for(i=1;i<=d.row;i++) 
    {
      for(j=1;j<=d.col;j++) 
	{
	  printf("% .*f\t",2,d.m[i][j]);
	}
      printf("\n");
    }  
  printf("\n");
 }

/******************************************************************/ 
void dis(char *s,matrix& d,int sig)
{
  int i,j;
  fprintf(stderr,"Matrix %s is %i by %i\n",s,d.row,d.col);
  for(i=1;i<=d.row;i++) 
    {
      for(j=1;j<=d.col;j++) 
	{
	  printf("% .*f\t",sig,d.m[i][j]);
	}
      printf("\n");
    }  
  printf("\n");
  
}

/******************************************************************/ 
void dis(char *s,float f,int sig)
{
  fprintf(stderr,"%s is % .*f\n",s,sig,f);
}

/******************************************************************/ 

void write(matrix& p,char *name)
{
  int i,j;
  FILE *strm;
  if((strm=fopen(name,"w"))==NULL){
    printf("write(): Can't open file %s\n",name);
    exit(0);
  }
  
  for(i=1;i<=p.row;i++) 
    {
      for(j=1;j<=p.col;j++) 
	{
	  fprintf(strm,"%f\t",p.m[i][j]);
	}
      fprintf(strm,"\n");
    }  
  fclose(strm);
}

/******************************************************************/
void append(matrix& p,char *name)
{
  int i,j;
  FILE *strm;
  if((strm=fopen(name,"a"))==NULL){
    printf("append(): Can't open file %s\n",name);
    exit(0);
  }
  
  for(i=1;i<=p.row;i++) 
    {
      for(j=1;j<=p.col;j++) 
	{
	  fprintf(strm,"%f\t",p.m[i][j]);
	}
      fprintf(strm,"\n");
    }  
  fclose(strm);
}

/******************************************************************/
void empty(char *name)
{
  FILE *strm;
  if((strm=fopen(name,"w"))==NULL){
    printf("empty(): Can't open file %s\n",name);
    exit(0);
  }
  fclose(strm);
}

/******************************************************************/ 
void writegx(matrix& p,char *name)
{
  int i,j;
  FILE *strm;
  strm=fopen(name,"w");
  fprintf(strm,"\\x");
  for(i=1;i<p.col;i++)   fprintf(strm,"y");
  fprintf(strm,"\n");
  
  for(i=1;i<=p.row;i++) 
    {
      for(j=1;j<=p.col;j++) 
	{
	  fprintf(strm,"%f\t",p.m[i][j]);
	}
      fprintf(strm,"\n");
    }  
  fclose(strm);

}

/******************************************************************/ 
matrix read(char *name,int r, int c)
{ 
  int i,j;
  FILE *strm;
  matrix p(r,c);
  
  if((strm=fopen(name,"r"))==NULL){
    printf("read(): Unable to open file %s\n",name);
    exit(0);
  }
  
  for(i=1;i<=r;i++)
    for(j=1;j<=c;j++)
      fscanf(strm,"%f",&p.m[i][j]);
  
  return p;
}

/******************************************************************/
/******************************************************************/
/*************** MATRIX SPECIFIC MATH *****************************/
/******************************************************************/
/******************************************************************/
float det(matrix& p)
{
  float d;
  int j,i;
  float **a;
  int N;
  int *ix;
  
  
  N=p.row;
  ix=ivector(N);
  a=fmatrix(N,N);
  
  for(i=1;i<=N;i++) 
    for(j=1;j<=N;j++)  
      a[i][j]=p.m[i][j];
  
  if (singular(a,N)==1) return 0;
  ludcmp(a,N,ix,&d);
  
  for(j=1;j<=N;j++) d *= a[j][j];
  dump(a,N,N);
  dump(ix);
  
  return d;  
}
/******************************************************************/ 

matrix inv(matrix& p)
{
  float d;
  int j,i,*indx;
  float **a,*colum;
  matrix r(p.row,p.col);
  
  int N;
  
  if(p.row!=p.col) ERR1(Inverse,p);
  N=p.row;
  
  colum=fvector(N);
  indx=ivector(N);
  a=fmatrix(N,N);  
  
  for(i=1;i<=N;i++) 
    for(j=1;j<=N;j++)  a[i][j]=p.m[i][j];
  
  ludcmp(a,N,indx,&d);
  
  for(j=1;j<=N;j++)
    {
      for(i=1;i<=N;i++) colum[i]=0.0;
      colum[j]=1.0;
      lubksb(a,N,indx,colum);
      for(i=1;i<=N;i++) r.m[i][j]=colum[i];
    }
  
  dump(a,N,N); 
  dump(colum);
  dump(indx);
  
  return r;
}
/**********************************************************************/
void svd(matrix p, matrix &U, matrix &S, matrix &V)
{
  int i,j;
  float **a,*w,**v;
  int M=p.row;
  int N=p.col;

  U=dim(M,N);
  V=dim(N,N);
  S=dim(N,1);
  
  a=fmatrix(M,N);  
  
  for(i=1;i<=M;i++) 
    for(j=1;j<=N;j++)  
      a[i][j]=p(i,j);
  
  w=fvector(N);
  v=fmatrix(N,N);

  svdcmp(a,M,N,w,v);

  for(i=1;i<=M;i++) 
    for(j=1;j<=N;j++)  
      U(i,j)=a[i][j];
  
  for(i=1;i<=N;i++) 
    for(j=1;j<=N;j++)  
      V(i,j)=v[i][j];
  
  for(j=1;j<=N;j++)  
    S(j,1)=w[j];

  dump(a,N,M);
  dump(v,N,N);
  dump(w);
} 

/******************************************************************/ 
matrix eigenvec(matrix& p)
{
  int j,i,nrot;
  float **a,**v,*d;
  matrix r(p.row,p.col);
  int N;
  
  if(p.row!=p.col) ERR1(Eigenvec,p);
  if(sum(abs(p-~p))!=0) printf("Not symmetric\n"), exit(0);
  
  N=p.row;
  
  d=fvector(N);
  
  a=fmatrix(N,N);  
  v=fmatrix(N,N);  
  
  for(i=1;i<=N;i++) 
    for(j=1;j<=N;j++)  a[i][j]=p.m[i][j];
  
  jacobi(a,N,d,v,&nrot);
  
  eigsrt(d,v,N);
  
  
  for(i=1;i<=N;i++) 
    for(j=1;j<=N;j++)  r.m[i][j]=v[i][j];
  
  dump(a,N,N);
  dump(v,N,N);
  dump(d);
    
  return r;
}
/******************************************************************/ 
matrix eigenval(matrix& p)
{
  int j,i,nrot;
  float **a,**v,*d;
  matrix r(p.row,1);
  int N;
  
  if(p.row!=p.col) ERR1(Eigenval,p);
  if(sum(abs(p-~p))!=0) printf("Not symmetric\n"), exit(0);
  
  N=p.row;
  
  d=fvector(N);
  
  a=fmatrix(N,N);  
  v=fmatrix(N,N);  
  
  for(i=1;i<=N;i++) 
    for(j=1;j<=N;j++)  a[i][j]=p.m[i][j];
  
  jacobi(a,N,d,v,&nrot);
  
  eigsrt(d,v,N);
  
  for(i=1;i<=N;i++) r(i,1)=d[i];
  
  dump(a,N,N);
  dump(v,N,N);
  dump(d);
    
  return r;
}
/******************************************************************/ 
void eig(matrix&eval, matrix &evec, matrix& p)
{
  int j,i,nrot;
  float **a,**v,*d;
  int N;
  
  if(p.row!=p.col) ERR1(Eig,p);
  if(sum(abs(p-~p))!=0) printf("Not symmetric\n"), exit(0);
  
  N=p.row;
  
  d=fvector(N);
  
  a=fmatrix(N,N);  
  v=fmatrix(N,N);  
  
  for(i=1;i<=N;i++) 
    for(j=1;j<=N;j++)  a[i][j]=p.m[i][j];
  
  jacobi(a,N,d,v,&nrot);
  
  eigsrt(d,v,N);
  
  eval=dim(p.row,1);
  evec=dim(p.row,p.row);
  for(i=1;i<=N;i++) eval(i,1)=d[i];
  for(i=1;i<=N;i++) 
    for(j=1;j<=N;j++)  evec(i,j)=v[i][j];
 
  dump(a,N,N);
  dump(v,N,N);
  dump(d);
}

/******************************************************************/
/******************************************************************/
/**************** MATRIX COMPARISONS *******************************/
/******************************************************************/
/******************************************************************/ 
matrix operator==(matrix& p,matrix& q)
{
  int i,j;
  
  if((q.col!=p.col)||(q.row!=p.row))    ERR2(in comparison (==),p,q);
  
  matrix r(q.row,q.col);
  
  
  for(i=1;i<=q.row;i++)
    for(j=1;j<=q.col;j++)
      r.m[i][j]=(float)(q.m[i][j]==p.m[i][j]);
  
  return r;
}
/*****************************************************************/
matrix operator==(matrix& p,double f)
{
  int i,j;
  
  matrix r(p.row,p.col);
  
  
  for(i=1;i<=p.row;i++)
    for(j=1;j<=p.col;j++)
      r.m[i][j]=(double)(f==p.m[i][j]);
  
  
  
  return r;
}

/*****************************************************************/
matrix operator==(double f, matrix& p)
{
  int i,j;
  
  matrix r(p.row,p.col);
  
  
  for(i=1;i<=p.row;i++)
    for(j=1;j<=p.col;j++)
      r.m[i][j]=(double)(f==p.m[i][j]);
  
  return r;
}

/*****************************************************************/
matrix operator||(matrix& p,matrix& q)
{
  int i,j;
  
  if((q.col!=p.col)||(q.row!=p.row)) ERR2(in comparison (||),p,q);
  
  matrix r(q.row,q.col);
  
  
  for(i=1;i<=q.row;i++)
    for(j=1;j<=q.col;j++)
      r.m[i][j]=(float)(q.m[i][j]||p.m[i][j]);
  
  
  return r;
}
/*****************************************************************/
matrix operator||(matrix& p,double f)
{
  int i,j;
  
  matrix r(p.row,p.col);
  
  
  for(i=1;i<=p.row;i++)
    for(j=1;j<=p.col;j++)
      r.m[i][j]=(double)(f||p.m[i][j]);
  
  
  
  return r;
}

/*****************************************************************/
matrix operator||(double f, matrix& p)
{
  int i,j;
  
  matrix r(p.row,p.col);
  
  
  for(i=1;i<=p.row;i++)
    for(j=1;j<=p.col;j++)
      r.m[i][j]=(double)(f||p.m[i][j]);
  
  return r;
}

/*****************************************************************/
matrix operator&&(matrix& p,matrix& q)
{
  int i,j;
  
  if((q.col!=p.col)||(q.row!=p.row)) ERR2(in comparison (&&),p,q);
  
  matrix r(q.row,q.col);
  
  
  for(i=1;i<=q.row;i++)
    for(j=1;j<=q.col;j++)
      r.m[i][j]=(float)(q.m[i][j]&&p.m[i][j]);
  
  
  return r;
}
/*****************************************************************/
matrix operator&&(matrix& p,double f)
{
  int i,j;
  
  matrix r(p.row,p.col);
  
  
  for(i=1;i<=p.row;i++)
    for(j=1;j<=p.col;j++)
      r.m[i][j]=(double)(f&&p.m[i][j]);
  
  
  
  return r;
}

/*****************************************************************/
matrix operator&&(double f, matrix& p)
{
  int i,j;
  
  matrix r(p.row,p.col);
  
  
  for(i=1;i<=p.row;i++)
    for(j=1;j<=p.col;j++)
      r.m[i][j]=(double)(f&&p.m[i][j]);
  
  return r;
}

/*****************************************************************/
matrix operator!=(matrix& p,matrix& q)
{
  int i,j;
  
  if((q.col!=p.col)||(q.row!=p.row)) ERR2(in comparison (!=),p,q);

  matrix r(q.row,q.col);
  
  
  for(i=1;i<=q.row;i++)
    for(j=1;j<=q.col;j++)
      r.m[i][j]=(double)(q.m[i][j]!=p.m[i][j]);
  
  
  return r;
}
/*****************************************************************/
matrix operator!=(matrix& p,double f)
{
  int i,j;
  
  matrix r(p.row,p.col);
  
  
  for(i=1;i<=p.row;i++)
    for(j=1;j<=p.col;j++)
      r.m[i][j]=(double)(f!=p.m[i][j]);
  
  
  
  return r;
}

/*****************************************************************/
matrix operator!=(double f, matrix& p)
{
  int i,j;
  
  matrix r(p.row,p.col);
  
  
  for(i=1;i<=p.row;i++)
    for(j=1;j<=p.col;j++)
      r.m[i][j]=(double)(f!=p.m[i][j]);
  
  return r;
}

/*****************************************************************/
matrix operator>=(matrix& q,matrix& p)
{
  int i,j;
  
  if((q.col!=p.col)||(q.row!=p.row)) ERR2(in comparison (>=),p,q);

  matrix r(q.row,q.col);
  
  
  for(i=1;i<=q.row;i++)
    for(j=1;j<=q.col;j++)
      r.m[i][j]=(double)(q.m[i][j]>=p.m[i][j]);
  
  
  return r;
}
/*****************************************************************/
matrix operator>=(matrix& p,double f)
{
  int i,j;
  
  matrix r(p.row,p.col);
  
  
  for(i=1;i<=p.row;i++)
    for(j=1;j<=p.col;j++)
      r.m[i][j]=(double)(p.m[i][j]>=f);
  
  
  return r;
}
/*****************************************************************/
matrix operator>=(double f,matrix& p)
{
  int i,j;
  
  matrix r(p.row,p.col);
  
  
  for(i=1;i<=p.row;i++)
    for(j=1;j<=p.col;j++)
      r.m[i][j]=(double)(f>=p.m[i][j]);
  
  
  return r;
}
/*****************************************************************/
matrix operator>(matrix& q,matrix& p)
{
  int i,j;
  
  if((q.col!=p.col)||(q.row!=p.row)) ERR2(in comparison (>),p,q);
  
  matrix r(q.row,q.col);
  
  
  for(i=1;i<=q.row;i++)
    for(j=1;j<=q.col;j++)
      r.m[i][j]=(double)(q.m[i][j]>p.m[i][j]);
  
  
  return r;
}

/*****************************************************************/
matrix operator>(double f,matrix& p)
{
  int i,j;
  
  matrix r(p.row,p.col);
  
  
  for(i=1;i<=p.row;i++)
    for(j=1;j<=p.col;j++)
      r.m[i][j]=(double)(f>p.m[i][j]);
  
  return r;
}
/*****************************************************************/
matrix operator>(matrix& p, double f)
{
  int i,j;
  
  matrix r(p.row,p.col);
  
  
  for(i=1;i<=p.row;i++)
    for(j=1;j<=p.col;j++)
      r.m[i][j]=(double)(p.m[i][j]>f);
  
  return r;
}
/*****************************************************************/
matrix operator<=(matrix& q,matrix& p)
{
  int i,j;
  
  if((q.col!=p.col)||(q.row!=p.row)) ERR2(in comparison (<=),p,q);
  
  matrix r(q.row,q.col);
  
  
  for(i=1;i<=q.row;i++)
    for(j=1;j<=q.col;j++)
      r.m[i][j]=(double)(q.m[i][j]<=p.m[i][j]);
  
  
  return r;
}
/*****************************************************************/
matrix operator<=(matrix& p,double f)
{
  int i,j;
  
  matrix r(p.row,p.col);
  
  
  for(i=1;i<=p.row;i++)
    for(j=1;j<=p.col;j++)
      r.m[i][j]=(double)(p.m[i][j]<=f);
  
  
  return r;
}
/*****************************************************************/
matrix operator<=(double f,matrix& p)
{
  int i,j;
  
  matrix r(p.row,p.col);
  
  
  for(i=1;i<=p.row;i++)
    for(j=1;j<=p.col;j++)
      r.m[i][j]=(double)(f<=p.m[i][j]);
  
  
  return r;
}
/*****************************************************************/
matrix operator<(matrix& q,matrix& p)
{
  int i,j;
  
  if((q.col!=p.col)||(q.row!=p.row)) ERR2(in comparison (<),p,q);

  matrix r(q.row,q.col);
  
  
  for(i=1;i<=q.row;i++)
    for(j=1;j<=q.col;j++)
      r.m[i][j]=(double)(q.m[i][j]<p.m[i][j]);
  
  
  return r;
}

/*****************************************************************/
matrix operator<(double f,matrix& p)
{
  int i,j;
  
  matrix r(p.row,p.col);
  
  
  for(i=1;i<=p.row;i++)
    for(j=1;j<=p.col;j++)
      r.m[i][j]=(double)(f<p.m[i][j]);
  
  return r;
}
/*****************************************************************/
matrix operator<(matrix& p, double f)
{
  int i,j;
  
  matrix r(p.row,p.col);
  
  
  for(i=1;i<=p.row;i++)
    for(j=1;j<=p.col;j++)
      r.m[i][j]=(double)(p.m[i][j]<f);
  
  return r;
}
/*****************************************************************/
/******************************************************************/
/************* MATRIX CONCATENATION *******************************/
/******************************************************************/
/******************************************************************/
matrix operator|(matrix& p, matrix& q)
{
  int i,j;
  
  matrix r(p.row,p.col+q.col);
  
 if(p.row==q.row)
    {
      for(i=1;i<=p.row;i++)
	for(j=1;j<=p.col;j++)
	  r.m[i][j]=p.m[i][j];
      
      for(i=1;i<=p.row;i++)
	for(j=p.col+1;j<=p.col+q.col;j++)
	  r.m[i][j]=q.m[i][j-p.col];
    }   
    
  else ERR2(in column concatenation,p,q);

  
  return r;
}
/*****************************************************************/
matrix operator|(matrix& p, double f)
{
  int i,j;
  
  matrix r(p.row,p.col+1);
  
  for(i=1;i<=p.row;i++)
    for(j=1;j<=p.col;j++)
      r.m[i][j]=p.m[i][j];
  
  for(i=1;i<=p.row;i++) r.m[i][p.col+1]=f;
  
  
  return r;
}
/*****************************************************************/
void operator|=(matrix&p, matrix& q)
{
  matrix r(1,1);
  
  if(p.row==q.row) r=p|q, p=r;
  else if(p.row==1&&p.col==1&&p(1,1)==0)  p=q;
  else  ERR2(in row concatenation,p,q);

}
/*****************************************************************/
void operator%=(matrix&p, matrix& q)
{
  matrix r(1,1);
  
  if(p.col==q.col) r=p%q, p=r;
  else if(p.row==1&&p.col==1&&p(1,1)==0)  p=q;
  else  ERR2(in column concatenation,p,q);
}
/*****************************************************************/
matrix operator%(matrix& p, matrix& q)
{
  int i,j;
  
  matrix r(p.row+q.row,p.col);
  
  
  if(p.col==q.col)
    {
      for(i=1;i<=p.row;i++)
	for(j=1;j<=p.col;j++)
	  r.m[i][j]=p.m[i][j];
      
      for(i=p.row+1;i<=p.row+q.row;i++)
	for(j=1;j<=q.col;j++)
	  r.m[i][j]=q.m[i-p.row][j];
    }       
  else if(p.col==1) r=q;  
  else ERR2(in row concatenation,p,q);
  return r;
}

/*****************************************************************/
matrix operator%(matrix& p, double f)
{
  int i,j;
  
  matrix r(p.row+1,p.col);
  
  for(i=1;i<=p.row;i++)
    for(j=1;j<=p.col;j++)
      r.m[i][j]=p.m[i][j];
  
  for(i=1;i<=p.col;i++) r.m[p.row+1][i]=f;
  
  
  return r;
}
/*****************************************************************/
/******************************************************************/
/*************** MATRIX OPERATOR MULTIPLICATION *******************/
/******************************************************************/
/******************************************************************/ 

matrix operator*(matrix& q,matrix& p)
{
  int i,j,k;
  
  matrix r(q.row,p.col);
  
  if(q.col!=p.row) ERR2(Multiplication,q,p);
  
  for(i=1;i<=q.row;i++)
    for(j=1;j<=p.col;j++)
      for(k=1;k<=p.row;k++) 
	r.m[i][j]+=q.m[i][k]*p.m[k][j];
  
  
  return r;
}

/*****************************************************************/
void matrix::operator*=(matrix& p)
{
  int i,j,k;
  
  matrix r(row,p.col);
  
  if(col!=p.row || p.row!=p.col)
    {
      sprintf(commonErrorString,"*= product error :  rows and columns do not match\n");
      sprintf(commonErrorString,"%s\nFirst is %i by %i while second is %i by %i\n",
	     commonErrorString,row,col,p.row,p.col);
	  CommonError(commonErrorString);
      exit(0);
    }
  
  
  for(i=1;i<=row;i++)
    for(j=1;j<=p.col;j++)
      for(k=1;k<=p.row;k++) 
	r.m[i][j]+=m[i][k]*p.m[k][j];
  
  for(i=1;i<=row;i++)
    for(j=1;j<=p.col;j++) m[i][j]=r.m[i][j];
  
}

/*****************************************************************/
void matrix::operator*=(float f)
{
  int i,j;
  
  for(i=1;i<=row;i++)
    for(j=1;j<=col;j++)
      	m[i][j]*=f;
}

/*****************************************************************/
void matrix::operator*=(double f)
{
  int i,j;
  
  for(i=1;i<=row;i++)
    for(j=1;j<=col;j++)
      	m[i][j]*=f;
}

/*****************************************************************/
matrix operator^(matrix& q,matrix& p)
{
  int i,j;
  matrix r(1,1);
  
  if(p.col==1 && p.row==q.row) 
    {
      r=dim(q.row,q.col);
      for(i=1;i<=q.row;i++)
	for(j=1;j<=q.col;j++)
	  r.m[i][j]=q.m[i][j]*p.m[i][1];
    }
  else if(q.col==1 && p.row==q.row) 
    {
      r=dim(p.row,p.col);
      for(i=1;i<=p.row;i++)
	for(j=1;j<=p.col;j++)
	  r.m[i][j]=p.m[i][j]*q.m[i][1];
    }
  else if(p.col==q.col && p.row==1) 
    {
      r=dim(q.row,q.col);
      for(i=1;i<=q.row;i++)
	for(j=1;j<=q.col;j++)
	  r.m[i][j]=q.m[i][j]*p.m[1][j];
    }
 else if(p.col==q.col && q.row==1) 
    {
      r=dim(p.row,p.col);
      for(i=1;i<=p.row;i++)
	for(j=1;j<=p.col;j++)
	  r.m[i][j]=p.m[i][j]*q.m[1][j];
    }
  else if(p.col==q.col && p.row==q.row)
    {
      r=dim(q.row,q.col);
      for(i=1;i<=q.row;i++)
	for(j=1;j<=q.col;j++)
	  r.m[i][j]=q.m[i][j]*p.m[i][j];
    }
  else if(p.col==1 && p.row==1) 
    {
      r=dim(q.row,q.col);
      for(i=1;i<=q.row;i++)
	for(j=1;j<=q.col;j++)
	  r.m[i][j]=q.m[i][j]*p.m[1][1];
    }
  else      ERR2(Elementwise multiplication,q,p); ;

  return r;
}

/******************************************************************/ 
matrix operator*(double p,matrix& q)
{
  int i,j;
  matrix r(q.row,q.col);
  
  
  for(i=1;i<=q.row;i++)
    for(j=1;j<=q.col;j++)
      r.m[i][j]=q.m[i][j]*p;
  
  
  return r;
}
/******************************************************************/ 
matrix operator*(matrix& q,double p)
{
  int i,j;
  matrix r(q.row,q.col);
  
  
  for(i=1;i<=q.row;i++)
    for(j=1;j<=q.col;j++)
      r.m[i][j]=q.m[i][j]*p;
  
  
  return r;
}
/******************************************************************/
/******************************************************************/
/***************** MATRIX DIVISION ********************************/
/******************************************************************/
/******************************************************************/

matrix operator/(matrix& q,double p)
{
  int i,j;
  matrix r(q.row,q.col);
  
  if(p==0.0)  ERR0(Attempted divsion by zero);
  
  for(i=1;i<=q.row;i++)
    for(j=1;j<=q.col;j++)
      r.m[i][j]=q.m[i][j]/p;
  return r;
}

/******************************************************************/
void matrix::operator/=(double p)
{
  int i,j;
  
  if(p==0.0)  ERR0(Attempted divsion by zero);
  
  for(i=1;i<=row;i++)
    for(j=1;j<=col;j++)
      m[i][j]/=p;
}

/******************************************************************/
matrix operator/(matrix& q,matrix& p)
{
  int i,j;
  matrix r(q.row,q.col);
  
  if(p.col==1 && p.row==q.row) 
    {
      for(i=1;i<=q.row;i++)
	for(j=1;j<=q.col;j++)
	  r.m[i][j]=q.m[i][j]/p.m[i][1];
    }
  else if(p.col==q.col && p.row==1) 
    {
      for(i=1;i<=q.row;i++)
	for(j=1;j<=q.col;j++)
	  r.m[i][j]=q.m[i][j]/p.m[1][j];
    }
  else if(p.col==q.col && p.row==q.row)
    {
      for(i=1;i<=q.row;i++)
	for(j=1;j<=q.col;j++)
	  r.m[i][j]=q.m[i][j]/p.m[i][j];
    }
  else if(p.col==1 && p.row==1) 
    {
      for(i=1;i<=q.row;i++)
	for(j=1;j<=q.col;j++)
	  r.m[i][j]=q.m[i][j]/p.m[1][1];
    }
  else 
    {
      matrix r(1,1);
      
      ERR2(elementwise matrix division,q,p);
    }
  return r;
}

/******************************************************************/ 
void matrix::operator/=(matrix& p)
{
  int i,j;
  
  if(p.col==1 && p.row==row) 
    {
      for(i=1;i<=row;i++)
	for(j=1;j<=col;j++)
	  m[i][j]/=p.m[i][1];
    }
  else if(p.col==col && p.row==1) 
    {
      for(i=1;i<=row;i++)
	for(j=1;j<=col;j++)
	  m[i][j]/=p.m[1][j];
    }
  else if(p.col==col && p.row==row)
    {
      for(i=1;i<=row;i++)
	for(j=1;j<=col;j++)
	  m[i][j]/=p.m[i][j];
    }
  else if(p.col==1 && p.row==1) 
    {
      for(i=1;i<=row;i++)
	for(j=1;j<=col;j++)
	  m[i][j]/=p.m[1][1];
    }
  else exit(0);
}

/******************************************************************/ 
/******************************************************************/
/******************************************************************/
/**************** MATRIX SUBTRACTION ******************************/
/******************************************************************/
/******************************************************************/

matrix operator-(matrix& p,matrix& q)
{
  int i,j;
  matrix r(p.row,p.col);  
  
  
  if((q.col==p.col)&&(q.row==p.row))
    {
      for(i=1;i<=r.row;i++)
	for(j=1;j<=r.col;j++)
	  r.m[i][j]=p.m[i][j]-q.m[i][j];
    }
  else if((q.col==p.col)&&(q.row==1))
    {
      for(i=1;i<=r.row;i++)
	for(j=1;j<=r.col;j++)
	  r.m[i][j]=p.m[i][j]-q.m[1][j];
    }
  else if((q.col==1)&&(p.row==q.row))
    {
      for(i=1;i<=r.row;i++)
	for(j=1;j<=r.col;j++)
	  r.m[i][j]=p.m[i][j]-q.m[i][1];
    }
  else ERR2(in matrix subtraction,p,q);
  
  return r;
}
/******************************************************************/ 

void matrix::operator-=(matrix& p)
{
  int i,j;
  
  if((col!=p.col)||(row!=p.row))
    {
      sprintf(commonErrorString,"Decrement Sum error :  rows and columns do not match\n");
      sprintf(commonErrorString,"%s\nFirst is %i by %i while second is %i by %i\n",
	     commonErrorString,row,col,p.row,p.col);
	  CommonError(commonErrorString);
      exit(0);
    }  
  for(i=1;i<=row;i++)
    for(j=1;j<=col;j++)
      m[i][j]-=p.m[i][j];
  
  
}
/******************************************************************/ 

void matrix::operator-=(double q)
{
  int i,j;
  
  for(i=1;i<=row;i++)
    for(j=1;j<=col;j++)
      m[i][j]-=q;
}

/******************************************************************/ 
matrix operator-(matrix& p,double q)
{
  int i,j;
  
  matrix r(p.row,p.col);
  
  
  for(i=1;i<=p.row;i++)
    for(j=1;j<=p.col;j++)
      r.m[i][j]=p.m[i][j]-q;
  
  
  return r;
}

/******************************************************************/ 
matrix operator-(double q,matrix& p)
{
  int i,j;
  
  matrix r(p.row,p.col);
  
  
  for(i=1;i<=p.row;i++)
    for(j=1;j<=p.col;j++)
      r.m[i][j]=-p.m[i][j]+q;
  
  return r;
}
/******************************************************************/ 

matrix matrix::operator-()
{
  int i,j;
  matrix p(row,col);
  
  for(i=1;i<=row;i++)
    for(j=1;j<=col;j++) p.m[i][j]=-m[i][j];
  
  return p;
}


/******************************************************************/
/******************************************************************/
/*************** MATRIX ADDITION **********************************/
/******************************************************************/
/******************************************************************/
void matrix::operator+=(matrix& p)
{
  int i,j;
  
  if((col!=p.col)||(row!=p.row))
    {
      sprintf(commonErrorString,"Increment Sum error :  rows and columns do not match\n");
      sprintf(commonErrorString,"%s/nFirst is %i by %i while second is %i by %i\n",
	     commonErrorString,row,col,p.row,p.col);
	  CommonError(commonErrorString);
      exit(0);
    }  
  for(i=1;i<=row;i++)
    for(j=1;j<=col;j++)
      m[i][j]+=p.m[i][j];
  
}

/******************************************************************/
matrix operator+(matrix& p,double q)
{
  int i,j;
  
  matrix r(p.row,p.col);
  
  
  for(i=1;i<=p.row;i++)
    for(j=1;j<=p.col;j++)
      r.m[i][j]=p.m[i][j]+q;
  
  return r;
}

/******************************************************************/ 
matrix operator+(double q,matrix& p)
{
  int i,j;
  
  matrix r(p.row,p.col);
  
  
  for(i=1;i<=p.row;i++)
    for(j=1;j<=p.col;j++)
      r.m[i][j]=p.m[i][j]+q;
  
  return r;
}

/******************************************************************/ 

matrix operator+(matrix&  p,matrix&  q)
{
  int i,j;
  matrix r(p.row,p.col);  
 
  if((q.col==p.col)&&(q.row==p.row))
    {
      for(i=1;i<=r.row;i++)
	for(j=1;j<=r.col;j++)
	  r.m[i][j]=p.m[i][j]+q.m[i][j];
    }
  else if((q.col==p.col)&&(q.row==1))
    {
      for(i=1;i<=r.row;i++)
	for(j=1;j<=r.col;j++)
	  r.m[i][j]=p.m[i][j]+q.m[1][j];
    }
  else if((q.col==1)&&(p.row==q.row))
    {
      for(i=1;i<=r.row;i++)
	for(j=1;j<=r.col;j++)
	  r.m[i][j]=p.m[i][j]+q.m[i][1];
    }
  else  ERR2(sum,p,q);
  
  
  return r;
}

/******************************************************************/
/******************************************************************/
/************* MATRIX INITIALISATION ******************************/
/******************************************************************/
/******************************************************************/

void zeros(matrix& p)
{
  int i,j;
  for(i=1;i<=p.row;i++)
    for(j=1;j<=p.col;j++) p.m[i][j]=0.0;
}
/******************************************************************/ 
void set(matrix& q,float p)
{
  int i,j;
  for(i=1;i<=q.row;i++)
    for(j=1;j<=q.col;j++) q.m[i][j]=p;
}
/******************************************************************/ 
void set(matrix& q,int a)
{
  set(q,(float)a);
}
/******************************************************************/ 
void rand(matrix& w,float p, float q)
{
  int i,j;
  for(i=1;i<=w.row;i++)
    for(j=1;j<=w.col;j++) w.m[i][j]=urand(p,q);
}

/******************************************************************/ 
void gauss(matrix& w,float m, float sd)
{
  int i,j;
  for(i=1;i<=w.row;i++)
    for(j=1;j<=w.col;j++) w.m[i][j]=gauss(m,sd);
}
/******************************************************************/ 


int singular(float **a,int n)
{
  int i,j;
  float big,temp;
  
  for (i=1;i<=n;i++) 
    {
      big=0.0;
      for (j=1;j<=n;j++) if ((temp=fabs(a[i][j])) > big) big=temp;
      if (big == 0.0) return 1;
    }
  return 0;
}

/******************************************************************/ 
matrix T(matrix p)
{
  return ~p;
}





/******************************************************************/
/******************************************************************/
/***********************NUM REC**************************/
/******************************************************************/
/******************************************************************/
// For Error Handling
extern void ExptError(char *);

//////////////////////////////////// UNTILS
#define NR_END 1
#define FREE_ARG char*
#define SIGN(a,b) ((b) >= 0.0 ? fabs(a) : -fabs(a))

static float maxarg1,maxarg2;
#define FMAX(a,b) (maxarg1=(a),maxarg2=(b),(maxarg1) > (maxarg2) ? (maxarg1) : (maxarg2))
static int iminarg1,iminarg2;
#define IMIN(a,b) (iminarg1=(a),iminarg2=(b),(iminarg1) < (iminarg2) ? (iminarg1) : (iminarg2))

float *vector(long nl, long nh)
/* allocate a float vector with subscript range v[nl..nh] */
{
  float *v;
  v=(float *)malloc((size_t) ((nh-nl+1+NR_END)*sizeof(float)));
  if (!v) { CommonError("allocation failure in vector()"); return NULL;}
  return v-nl+NR_END;
}

void free_vector(float *v, long nl, long nh)
/* free a float vector allocated with vector() */
{
  free((FREE_ARG) (v+nl-NR_END));
}


//////////////////////////////////// ROUTINES

/* (C) Copr. 1986-92 Numerical Recipes Software #.,. */
#define NRANSI

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
			if ((temp=fabs(a[i][j])) > big) big=temp;
			if (big == 0.0) {CommonError("Singular matrix in routine ludcmp"); return;}
		vv[i]=1.0/big;
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
			if ( (dum=vv[i]*fabs(sum)) >= big) {
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
			dum=1.0/(a[j][j]);
			for (i=j+1;i<=n;i++) a[i][j] *= dum;
		}
	}
	free_vector(vv,1,n);
}
#undef TINY
/////////////////////////////////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////////////

void svdcmp(float **a, int m, int n, float w[], float **v)
{
	float pythag(float a, float b);
	int flag,i,its,j,jj,k,l,nm;
	float anorm,c,f,g,h,s,scale,x,y,z,*rv1;

	rv1=vector(1,n);
	g=scale=anorm=0.0;
	for (i=1;i<=n;i++) {
		l=i+1;
		rv1[i]=scale*g;
		g=s=scale=0.0;
		if (i <= m) {
			for (k=i;k<=m;k++) scale += fabs(a[k][i]);
			if (scale) {
				for (k=i;k<=m;k++) {
					a[k][i] /= scale;
					s += a[k][i]*a[k][i];
				}
				f=a[i][i];
				g = -SIGN(sqrt(s),f);
				h=f*g-s;
				a[i][i]=f-g;
				for (j=l;j<=n;j++) {
					for (s=0.0,k=i;k<=m;k++) s += a[k][i]*a[k][j];
					f=s/h;
					for (k=i;k<=m;k++) a[k][j] += f*a[k][i];
				}
				for (k=i;k<=m;k++) a[k][i] *= scale;
			}
		}
		w[i]=scale *g;
		g=s=scale=0.0;
		if (i <= m && i != n) {
			for (k=l;k<=n;k++) scale += fabs(a[i][k]);
			if (scale) {
				for (k=l;k<=n;k++) {
					a[i][k] /= scale;
					s += a[i][k]*a[i][k];
				}
				f=a[i][l];
				g = -SIGN(sqrt(s),f);
				h=f*g-s;
				a[i][l]=f-g;
				for (k=l;k<=n;k++) rv1[k]=a[i][k]/h;
				for (j=l;j<=m;j++) {
					for (s=0.0,k=l;k<=n;k++) s += a[j][k]*a[i][k];
					for (k=l;k<=n;k++) a[j][k] += s*rv1[k];
				}
				for (k=l;k<=n;k++) a[i][k] *= scale;
			}
		}
		anorm=FMAX(anorm,(fabs(w[i])+fabs(rv1[i])));
	}
	for (i=n;i>=1;i--) {
		if (i < n) {
			if (g) {
				for (j=l;j<=n;j++)
					v[j][i]=(a[i][j]/a[i][l])/g;
				for (j=l;j<=n;j++) {
					for (s=0.0,k=l;k<=n;k++) s += a[i][k]*v[k][j];
					for (k=l;k<=n;k++) v[k][j] += s*v[k][i];
				}
			}
			for (j=l;j<=n;j++) v[i][j]=v[j][i]=0.0;
		}
		v[i][i]=1.0;
		g=rv1[i];
		l=i;
	}
	for (i=IMIN(m,n);i>=1;i--) {
		l=i+1;
		g=w[i];
		for (j=l;j<=n;j++) a[i][j]=0.0;
		if (g) {
			g=1.0/g;
			for (j=l;j<=n;j++) {
				for (s=0.0,k=l;k<=m;k++) s += a[k][i]*a[k][j];
				f=(s/a[i][i])*g;
				for (k=i;k<=m;k++) a[k][j] += f*a[k][i];
			}
			for (j=i;j<=m;j++) a[j][i] *= g;
		} else for (j=i;j<=m;j++) a[j][i]=0.0;
		++a[i][i];
	}
	for (k=n;k>=1;k--) {
		for (its=1;its<=30;its++) {
			flag=1;
			for (l=k;l>=1;l--) {
				nm=l-1;
				if ((float)(fabs(rv1[l])+anorm) == anorm) {
					flag=0;
					break;
				}
				if ((float)(fabs(w[nm])+anorm) == anorm) break;
			}
			if (flag) {
				c=0.0;
				s=1.0;
				for (i=l;i<=k;i++) {
					f=s*rv1[i];
					rv1[i]=c*rv1[i];
					if ((float)(fabs(f)+anorm) == anorm) break;
					g=w[i];
					h=pythag(f,g);
					w[i]=h;
					h=1.0/h;
					c=g*h;
					s = -f*h;
					for (j=1;j<=m;j++) {
						y=a[j][nm];
						z=a[j][i];
						a[j][nm]=y*c+z*s;
						a[j][i]=z*c-y*s;
					}
				}
			}
			z=w[k];
			if (l == k) {
				if (z < 0.0) {
					w[k] = -z;
					for (j=1;j<=n;j++) v[j][k] = -v[j][k];
				}
				break;
			}
			if (its == 30) {CommonError("no convergence in 30 svdcmp iterations"); return;}
			x=w[l];
			nm=k-1;
			y=w[nm];
			g=rv1[nm];
			h=rv1[k];
			f=((y-z)*(y+z)+(g-h)*(g+h))/(2.0*h*y);
			g=pythag(f,1.0);
			f=((x-z)*(x+z)+h*((y/(f+SIGN(g,f)))-h))/x;
			c=s=1.0;
			for (j=l;j<=nm;j++) {
				i=j+1;
				g=rv1[i];
				y=w[i];
				h=s*g;
				g=c*g;
				z=pythag(f,h);
				rv1[j]=z;
				c=f/z;
				s=h/z;
				f=x*c+g*s;
				g = g*c-x*s;
				h=y*s;
				y *= c;
				for (jj=1;jj<=n;jj++) {
					x=v[jj][j];
					z=v[jj][i];
					v[jj][j]=x*c+z*s;
					v[jj][i]=z*c-x*s;
				}
				z=pythag(f,h);
				w[j]=z;
				if (z) {
					z=1.0/z;
					c=f*z;
					s=h*z;
				}
				f=c*g+s*y;
				x=c*y-s*g;
				for (jj=1;jj<=m;jj++) {
					y=a[jj][j];
					z=a[jj][i];
					a[jj][j]=y*c+z*s;
					a[jj][i]=z*c-y*s;
				}
			}
			rv1[l]=0.0;
			rv1[k]=f;
			w[k]=x;
		}
	}
	free_vector(rv1,1,n);
}

////////////////////////////////////////////////////////////////////////

void eigsrt(float d[], float **v, int n)
{
	int k,j,i;
	float p;

	for (i=1;i<n;i++) {
		p=d[k=i];
		for (j=i+1;j<=n;j++)
			if (d[j] >= p) p=d[k=j];
		if (k != i) {
			d[k]=d[i];
			d[i]=p;
			for (j=1;j<=n;j++) {
				p=v[j][i];
				v[j][i]=v[j][k];
				v[j][k]=p;
			}
		}
	}
}


////////////////////////////////////////////////////////////////////////
#define ROTATE(a,i,j,k,l) g=a[i][j];h=a[k][l];a[i][j]=g-s*(h+g*tau);\
	a[k][l]=h+s*(g-h*tau);

void jacobi(float **a, int n, float d[], float **v, int *nrot)
{
	int j,iq,ip,i;
	float tresh,theta,tau,t,sm,s,h,g,c,*b,*z;

	b=vector(1,n);
	z=vector(1,n);
	for (ip=1;ip<=n;ip++) {
		for (iq=1;iq<=n;iq++) v[ip][iq]=0.0;
		v[ip][ip]=1.0;
	}
	for (ip=1;ip<=n;ip++) {
		b[ip]=d[ip]=a[ip][ip];
		z[ip]=0.0;
	}
	*nrot=0;
	for (i=1;i<=50;i++) {
		sm=0.0;
		for (ip=1;ip<=n-1;ip++) {
			for (iq=ip+1;iq<=n;iq++)
				sm += fabs(a[ip][iq]);
		}
		if (sm == 0.0) {
			free_vector(z,1,n);
			free_vector(b,1,n);
			return;
		}
		if (i < 4)
			tresh=0.2*sm/(n*n);
		else
			tresh=0.0;
		for (ip=1;ip<=n-1;ip++) {
			for (iq=ip+1;iq<=n;iq++) {
				g=100.0*fabs(a[ip][iq]);
				if (i > 4 && (float)(fabs(d[ip])+g) == (float)fabs(d[ip])
					&& (float)(fabs(d[iq])+g) == (float)fabs(d[iq]))
					a[ip][iq]=0.0;
				else if (fabs(a[ip][iq]) > tresh) {
					h=d[iq]-d[ip];
					if ((float)(fabs(h)+g) == (float)fabs(h))
						t=(a[ip][iq])/h;
					else {
						theta=0.5*h/(a[ip][iq]);
						t=1.0/(fabs(theta)+sqrt(1.0+theta*theta));
						if (theta < 0.0) t = -t;
					}
					c=1.0/sqrt(1+t*t);
					s=t*c;
					tau=s/(1.0+c);
					h=t*a[ip][iq];
					z[ip] -= h;
					z[iq] += h;
					d[ip] -= h;
					d[iq] += h;
					a[ip][iq]=0.0;
					for (j=1;j<=ip-1;j++) {
						ROTATE(a,j,ip,j,iq)
					}
					for (j=ip+1;j<=iq-1;j++) {
						ROTATE(a,ip,j,j,iq)
					}
					for (j=iq+1;j<=n;j++) {
						ROTATE(a,ip,j,iq,j)
					}
					for (j=1;j<=n;j++) {
						ROTATE(v,j,ip,j,iq)
					}
					++(*nrot);
				}
			}
		}
		for (ip=1;ip<=n;ip++) {
			b[ip] += z[ip];
			d[ip]=b[ip];
			z[ip]=0.0;
		}
	}
	CommonError("Too many iterations in routine jacobi");
}	



static float sqrarg;
#define SQR(a) ((sqrarg=(a)) == 0.0 ? 0.0 : sqrarg*sqrarg)


float pythag(float a, float b)
{
	float absa,absb;
	absa=fabs(a);
	absb=fabs(b);
	if (absa > absb) return absa*sqrt(1.0+SQR(absb/absa));
	else return (absb == 0.0 ? 0.0 : absb*sqrt(1.0+SQR(absa/absb)));
}


