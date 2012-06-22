// ComUtils.h


int VariantToDoubleArray(double **data, VARIANT *var);
int VariantFromDoubleArray(double **data, VARIANT *var);

double *CreateDoubleArray(int dim, int *dimlen);
double *CopyDoubleArray(double *data);
double *CopyDoubleArrayStruct(double *data);
void FreeDoubleArray(double *data);
inline int GetDim(double *data)
{
    return ((int *)data)[-2];
}
inline int GetLength(double *data)
{
    return ((int *)data)[-1];
}
inline int GetLength(double *data, int dim)
{
    return ((int *)data)[-3-dim];
}
inline double &GetAt(double *data, int index0)
{
    return data[index0];
}
inline double &GetAt(double *data, int index0, int index1)
{
    return data[index0 + GetLength(data, 0) * index1];
}
inline double &GetAt(double *data, int index0, int index1, int index2)
{
    return data[index0 + GetLength(data, 0) * (index1 + GetLength(data, 1) * index2)];
}
inline double &GetAt(double *data, int index0, int index1, int index2, int index3)
{
    return data[index0 + GetLength(data, 0) * (index1 + GetLength(data, 1) * (index2 + GetLength(data, 2) * index3))];
}
inline double &GetAt(double *data, int index0, int index1, int index2, int index3, int index4)
{
    return data[index0 + GetLength(data, 0) * (index1 + GetLength(data, 1) * (index2 + GetLength(data, 2) * (index3 + GetLength(data, 3) * index4)))];
}



extern const int MAXDIM;
