// Regression, weighted or not
int  regress(float *b, float **x, float *y, int n, int dim);
int  regress(float *b, float **x, float *y, float *w, int n, int dim);

// Inverse
int  inverse(float **ainv, float **a, int n);

// Helper Math Functions
void lubksb(float **a, int n, int *indx, float b[]);
int  ludcmp(float **a, int n, int *indx, float *d);

// Helper Matrix Manipulation
void transpose(float **at, float **a, int n, int m);
void multiply(float **c, float **a, float **b, int n, int o, int m);
void multiply(float *c, float **a, float *b, int n, int m);
void multiply(float *c, float *a, float **b, int n, int m);

// [1:n] Vector and Matrix Allocation
float *vector(long nl, long nh);
int   *ivector(long nl, long nh);
float **matrix(long nrl, long nrh, long ncl, long nch);
int   **imatrix(long nrl, long nrh, long ncl, long nch);
void  free_vector(float *v, long nl, long nh);
void  free_ivector(int *v, long nl, long nh);
void  free_matrix(float **m, long nrl, long nrh, long ncl, long nch);
void  free_imatrix(int **m, long nrl, long nrh, long ncl, long nch);
