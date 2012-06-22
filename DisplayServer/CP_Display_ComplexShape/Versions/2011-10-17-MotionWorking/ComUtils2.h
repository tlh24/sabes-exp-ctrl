// ComUtils.h


int VariantToDoubleArray(double **data, VARIANT *var);
int VariantFromDoubleArray(double *data, VARIANT *var);

double *CreateDoubleArray(int dim, int *dimlen);
double *CopyDoubleArray(double *data);
double *CopyDoubleArrayStruct(double *data);
void FreeDoubleArray(double *data);
int GetDim(double *data);
int GetLength(double *data);
int GetLength(double *data, int dim);
double &GetAt(double *data, int index0);
double &GetAt(double *data, int index0, int index1);
double &GetAt(double *data, int index0, int index1, int index2);
double &GetAt(double *data, int index0, int index1, int index2, int index3);
double &GetAt(double *data, int index0, int index1, int index2, int index3, int index4);



extern const int MAXDIM;
