// OLD MIT HOMEGROWN MATRIX HEADER

#define sqr(a) ((a)*(a))
#define mina(a,b) (a<b?a:b)
#define maxa(a,b) (a>b?a:b)

#define euc(x1,y1,x2,y2)   sqrt(sqr((x1)-(x2))+sqr((y1)-(y2)))
#define Pi  3.14159265358979323846264
#define TRUE  1
#define FALSE 0

#define display(s,d) dis("<"#s">",s,d); 
#define disp(s) dis("<"#s">",s,2); 

class matrix
{
 public:
  float **m;
  int row,col;

 ~matrix();
  matrix(int a,int b);   /* creates and a * b matrix*/
  matrix(int a); /*creates an a*1 matrix */
  matrix(void);  /*creates a 1*1 matrix*/
  matrix operator()(int x, matrix& p); /*matrix element e.g A(i,j) */ 
  matrix operator()(matrix& p,int y); /*matrix element e.g A(i,j) */ 
  
  matrix operator[](int x);  /*column x extraction*/
  matrix operator()(int x); /*row x extraction */ 
  matrix operator()(int a,int b, int c, int d); /*submatrix extraction */ 
  float& operator()(int x,int y) {return m[x][y];}  /*matrix element */
						     /*e.g A(i,j) */ 
  matrix matrix::operator()(matrix& p); /*submatrix selection by vector */ 
  
  matrix matrix::colex(int a, ...);
  void  operator=(matrix&);
  friend void operator<<(matrix& q,float& f);
  friend void operator<<(float& f,matrix& q);
  friend void operator<<(matrix& q,double& f);
  friend void operator<<(double& f,matrix& q);
  friend void operator<<(matrix& q,int& f);
  friend void operator<<(int& f,matrix& q);
  matrix(matrix& q);
  friend void colassign(matrix& p,int k, matrix& q);

  void  operator*=(matrix&);
  void  operator*=(float);
  void  operator*=(double);
  void  operator/=(double);
  void  operator/=(matrix&);
  void  operator+=(matrix&);
  void  operator-=(matrix&);
  void  operator-=(double);

  friend matrix operator~(matrix&);       /*Transpose*/
  matrix matrix::operator-();       
  
  friend  matrix operator/(matrix&,matrix&);  /*element by elemement */
					    /*divison by matrix , */
					    /*vector or 1x1 matrix*/
  friend  matrix operator/(matrix&,double);

  friend  matrix operator^(matrix&,matrix&); /*element wise matrix multiplication*/

  friend  matrix operator*(matrix&,matrix&);  
  friend  matrix operator*(double,matrix&);
  friend  matrix operator*(matrix&,double);

  friend  matrix operator|(matrix&,matrix&); /*amatrix append columns*/
  friend  matrix operator|(matrix&,double);
  friend  void operator|=(matrix&,matrix&);
  friend  void operator%=(matrix&,matrix&);


  friend  matrix operator%(matrix&,matrix&); /*matrix append rows*/
  friend  matrix operator%(matrix&,double);

  friend  matrix operator+(matrix& ,matrix&);
  friend  matrix operator+(matrix&,double);
  friend  matrix operator+(double,matrix&);

  friend  matrix operator-(matrix&,double);
  friend  matrix operator-(matrix&,matrix&);
  friend  matrix operator-(double,matrix&);

  friend  matrix operator==(matrix&,matrix&);
  friend  matrix operator==(matrix&,double);
  friend  matrix operator==(double,matrix&);
  
  friend  matrix operator||(matrix&,matrix&);
  friend  matrix operator||(matrix&,double);
  friend  matrix operator||(double,matrix&);
  
  friend  matrix operator&&(matrix&,matrix&);
  friend  matrix operator&&(matrix&,double);
  friend  matrix operator&&(double,matrix&);
  
  friend  matrix operator!=(matrix&,matrix&);
  friend  matrix operator!=(matrix&,double);
  friend  matrix operator!=(double,matrix&);

  friend  matrix operator>=(matrix&,matrix&);
  friend  matrix operator>=(matrix&,double);
  friend  matrix operator>=(double,matrix&);

  friend  matrix operator>(matrix&,matrix&);
  friend  matrix operator>(matrix&,double);
  friend  matrix operator>(double,matrix&);

  friend  matrix operator<=(matrix&,matrix&);
  friend  matrix operator<=(matrix&,double);
  friend  matrix operator<=(double,matrix&);

  friend  matrix operator<(matrix&,matrix&);
  friend  matrix operator<(matrix&,double);
  friend  matrix operator<(double,matrix&);
};

#pragma warning (disable: 4244)  // Don't want to see conversion warnings

matrix T(matrix p);  // Also Transpose

void dis(matrix& d);
void dis(char *s,matrix& d);   /*display matrix to screen */
void dis(char *s,matrix& d,int sig); /*as above with d decimal places*/
void dis(char *s,float f,int sig); /*as above with d decimal places*/

int pow(int,int);
matrix pow(matrix&,int);
matrix pow(matrix&,float);
float pow(float,float);

void dump(float *);
void dump(double *);
void dump(int *);
void dump(double **,int,int);
void dump(float **,int,int);
int *ivector(int);

matrix sort(matrix&); /*need clarification*/

void set(matrix&,float);  /*set each element of matrix to value*/
void set(matrix&,int);  /*set each element of matrix to value*/
matrix dim(int,int);  /*set dimensions of matrix*/
matrix dim(int);  /*set dimensions of matrix*/
matrix copy(matrix&); /*copy one matrix to other as permanet copy*/

void append(matrix&,char *);  /*wries a matrix into an ascii file*/
void write(matrix&,char *);  /*wries a matrix into an ascii file*/
void writegx(matrix&,char *);  /*wries a matrix into an ascii file*/

matrix read(char *,int,int);  /*reads a matrix from an ascii file*/
void empty(char *);

void rand(matrix&,float,float); /*randomise the elements of a matrix*/
int rand(int,int); /*randomise the elements of a matrix*/

float scalar(matrix&);

matrix inv(matrix&);                                     /*Inverse*/
matrix eigenval(matrix&);                               /*Eigenvectors*/
matrix eigenvec(matrix&);                               /*Eigenvalues*/
void eig(matrix& val, matrix& vec, matrix& p);            /*Both*/
float det(matrix&);                                     /*determinant  */
void svd(matrix p, matrix &U, matrix &S, matrix &V);

matrix apply(matrix&,double (*func)(double x));
matrix apply(matrix&,float (*func)(float x));
matrix apply(matrix&,matrix&,double (*func)(double x, double y));
matrix apply(matrix&,matrix&,float (*func)(float x, float y));

/*Applies function func to each element of a matrix*/

float sum(matrix&);       /* sum of all elements in a matrix*/
float prod(matrix&);       /* sum of all elements in a matrix*/
float mmin(matrix&);       /* minimum of all elements in a matrix*/
float mmax(matrix&);       /* maximum of all elements in a matrix*/
int rows(matrix&);     /*returns the number of rows of the matrix*/
int cols(matrix&); /*returns the number of columns of the matrix*/
float mean(matrix&);  /*produces a vector of the row means*/
matrix rowmean(matrix&);  /*produces a vector of the row means*/
matrix colmean(matrix&);  /*produces a vector of the col means*/
float var(matrix&);  /*produces a vector of the row vars*/
matrix rowvar(matrix&);  /*produces a vector of the row vars*/
matrix colvar(matrix&);  /*produces a vector of the col vars*/
matrix cov(matrix&,matrix&);  /*produces a 1x1 matrix of cov*/
matrix rowsum(matrix&);  /*produces a vector of the row sums*/
matrix colsum(matrix&);   /*produces a vector of the column sums*/

matrix smooth(matrix& p,float sigma,int bins);
matrix smooth(matrix& p,matrix &w,float sigma,int bins);
matrix smooth(matrix& p,matrix &s,float sigma, int bins);
matrix zeros(int,int);    /* An n by m zero matrix*/
matrix diagonal(matrix&); /*Produce a diagonal matrix from a vector*/
matrix offdiagonal(matrix&); /*Produce a diagonal matrix from a vector*/
void zeros(matrix&); /*Zero all elements in vector*/

matrix repeat(float,int);     /*Identity matrix n x n*/
matrix repeat(int,int);     /*Identity matrix n x n*/

matrix series(int,int);     /*Identity matrix n x n*/
matrix series(int,int,int);     /*Identity matrix n x n*/
matrix series(float,float,float);     /*Identity matrix n x n*/
matrix I(int);     /*Identity matrix n x n*/
matrix rotate(float);     /*rotation matrix*/

matrix abs(matrix&);  /*element absolute value oeprator*/

float logistic(float);
float sgn(float);  /*element absolute value operator*/

extern "C"
{
  void ludcmp(float **,int,int *,float *);
  void lubksb(float **,int,int *,float *);
  void eigsrt(float *,float **, int);
  void jacobi(float **,int,float *,float **,int *);
  void  svdcmp(float **,int,int,float*,float **);
}

float urand(float a,float b);

void gauss(matrix&,float,float);
float gauss(float mean, float sd);

void rowassign(matrix&,int, matrix&);
matrix mat(int);
matrix mat(float);
matrix mat(float);

matrix sqrt(matrix&);

matrix sgn(matrix&);

float **fmatrix (int,int);
float *fvector(int);
int singular(float **a,int n);


#pragma warning (default: 4244)  // Don't want to see conversion warnings
