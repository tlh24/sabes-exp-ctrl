// ComUtils.h



////////// DEAL WITH VARIANTS

//////////////  ARRAY FROM VARIANT
// Note: Use "VariantClear(var)" to free resources after call to VariantFromArrayF
// 1D
void VariantFromArray(int n, void *a, VARIANT *var, int type);
void VariantFromArray(int n, BOOL *a, VARIANT *var);
void VariantFromArray(int n, unsigned char *a, VARIANT *var);
void VariantFromArray(int n, short *a, VARIANT *var);
void VariantFromArray(int n, long *a, VARIANT *var);
void VariantFromArray(int n, float *a, VARIANT *var);
void VariantFromArray(int n, double *a, VARIANT *var);
// 2D
void VariantFromArray2(int *n, void **a, VARIANT *var, int type);
void VariantFromArray2(int *n, BOOL **a, VARIANT *var);
void VariantFromArray2(int *n, unsigned char **a, VARIANT *var);
void VariantFromArray2(int *n, short **a, VARIANT *var);
void VariantFromArray2(int *n, long **a, VARIANT *var);
void VariantFromArray2(int *n, float **a, VARIANT *var);
void VariantFromArray2(int *n, double **a, VARIANT *var);
// 3D
void VariantFromArray3(int *n, void ***a, VARIANT *var, int type);
void VariantFromArray3(int *n, BOOL ***a, VARIANT *var);
void VariantFromArray3(int *n, unsigned char ***a, VARIANT *var);
void VariantFromArray3(int *n, short ***a, VARIANT *var);
void VariantFromArray3(int *n, long ***a, VARIANT *var);
void VariantFromArray3(int *n, float ***a, VARIANT *var);
void VariantFromArray3(int *n, double ***a, VARIANT *var);

//////////////  VARIANT FROM SIMPLE ARRAY
// Note: Use "delete a" to free resources after a call to VariantToArray*
// 1D
int  VariantToArray(int *n, void **a, VARIANT *var, int type);
int  VariantToArray(int *n, BOOL **a, VARIANT *var);
int  VariantToArray(int *n, unsigned char **a, VARIANT *var);
int  VariantToArray(int *n, short **a, VARIANT *var);
int  VariantToArray(int *n, long **a, VARIANT *var);
int  VariantToArray(int *n, float **a, VARIANT *var);
int  VariantToArray(int *n, double **a, VARIANT *var);
// 2D
int  VariantToArray2(int **n, void ***a, VARIANT *var, int type);
int  VariantToArray2(int **n, BOOL ***a, VARIANT *var);
int  VariantToArray2(int **n, unsigned char ***a, VARIANT *var);
int  VariantToArray2(int **n, short ***a, VARIANT *var);
int  VariantToArray2(int **n, long ***a, VARIANT *var);
int  VariantToArray2(int **n, float ***a, VARIANT *var);
int  VariantToArray2(int **n, double ***a, VARIANT *var);
// 3D
//int  VariantToArray3(int **n, void ****a, VARIANT *var, int type);
//int  VariantToArray3(int **n, BOOL ****a, VARIANT *var);
int  VariantToArray3(int **n, unsigned char ****a, VARIANT *var);
//int  VariantToArray3(int **n, short ****a, VARIANT *var);
//int  VariantToArray3(int **n, long ****a, VARIANT *var);
//int  VariantToArray3(int **n, float ****a, VARIANT *var);
int  VariantToArray3(int **n, double ****a, VARIANT *var);

////////// ERRORS

void HResultErrMessageBox( char *userMessage, HRESULT hr );


//////////////////
#define COMUTIL_ERR_NULL		1
#define COMUTIL_ERR_ARRAY		2
#define COMUTIL_ERR_TYPE		4
#define COMUTIL_ERR_DIM			8
#define COMUTIL_ERR_SAFEARRAY	16
