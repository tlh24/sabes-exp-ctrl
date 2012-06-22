/////////////////////////////////////////////////////////////////////////////
// CVisComplexObj

// VisComplexObj.cpp : Implementation of CVisComplexObj
#include "stdafx.h"
#include "VisServer.h"
#include "stdio.h"
#include "math.h"
#include "VisWindow.h"
#include "ComUtils.h"
#include "VisCalibrate.h"
#include "VisWindowActionLog.h"
#include "VisComplexObj.h"

const int MAXDIM = 8;

inline int GetOffset(int dim)
{
    return ((dim+2) * sizeof(int) + sizeof(double) - 1)/sizeof(double);
}

double *CreateDoubleArray(int dim, int *dimlen)
{
	int i, len = 1, offset = GetOffset(dim);
	for (i=0; i < dim; ++i) len = len * dimlen[i];
	if (len == 0) return NULL;
	double *result = new double[offset+len];
	logToFile((f, "DoubleArrayCreated: 0x%p\n", result));
	result = result + offset;
	((int *)result)[-1] = len;
    ((int *)result)[-2] = dim;
	for (i=0; i < dim; ++i)
		((int *)result)[-3-i] = dimlen[i];
	return result;
}

double *CopyDoubleArray(double *data)
{
    if (data == NULL) return NULL;
    int dim = GetDim(data), len = GetLength(data);
    int offset = GetOffset(dim);
	double *result = new double[offset+len];
	logToFile((f, "DoubleArrayCreated: 0x%p\n", result));
	result = result + offset;
    memcpy(result-offset, data-offset, sizeof(double)*(offset+len));
    return result;
}

double *CopyDoubleArrayStruct(double *data)
{
    if (data == NULL) return NULL;
    int dim = GetDim(data), len = GetLength(data);
    int offset = GetOffset(dim);
	double *result = new double[offset+len];
	logToFile((f, "DoubleArrayCreated: 0x%p\n", result));
	result = result + offset;
    memcpy(result-offset, data-offset, sizeof(double)*offset);
    return result;
}

void FreeDoubleArray(double *data)
{
    if (data != NULL)
	{
		data = data - GetOffset(GetDim(data));
		logToFile((f, "DoubleArrayFreed: 0x%p\n", data));
		delete[] data;
	}
}

int VariantToDoubleArray(double **data, VARIANT *var)
{
	long uBnd,lBnd;
	int dim, dimlen[MAXDIM];
	int err=0;
	
	// Check for ARRAY of the right type
    logToFile((f, "VaraintToDoubleArray: var = 0x%p\n", var));
	if( var==NULL )						return COMUTIL_ERR_NULL;
    logToFile((f, "VaraintToDoubleArray: var.type = %d\n", var->vt));
	if (var->vt == VT_ERROR){
		*data = NULL;
		return 0;
	}
	if( !( (var->vt) & VT_ARRAY ) )		err += COMUTIL_ERR_ARRAY;
	if( !( (var->vt) & VT_R8 ) )		err += COMUTIL_ERR_TYPE;
	if(err) return err;
	
	// Get Overall Length (number of elements, ignore shape of Safearray)
	dim = SafeArrayGetDim(var->parray);
	for(int d=1; d<=dim; d++){
		SafeArrayGetLBound(var->parray, d, &lBnd);
		SafeArrayGetUBound(var->parray, d, &uBnd);
		dimlen[d-1] = uBnd-lBnd+1;
	}
	
    logToFile((f, "VaraintToDoubleArray: %d, (%d, %d)\n", dim, dimlen[0], dimlen[1]));

	*data = CreateDoubleArray(dim, dimlen);
	if (*data != NULL)
	{
		// Get reference pointer for accessing the SafeArray
		void *sap;
		if( FAILED( SafeArrayAccessData(var->parray, (void**)&sap) )) return COMUTIL_ERR_SAFEARRAY;
		memcpy(*data, sap, sizeof(double) * GetLength(*data));
		
		// Release reference pointer
		SafeArrayUnaccessData (var->parray);
	}
	// Return Success
	return 0;
}

int VariantFromDoubleArray(double *data, VARIANT *var)
{
	int dim;
	long len;
	SAFEARRAY *psa;
	SAFEARRAYBOUND sabnd[MAXDIM];
	void *sap;
	
	if (data != NULL)
	{
		dim = GetDim(data);
		len = GetLength(data);
		////// Construct the SafeArray and total size
		for(int i=0;i<dim;i++){  	// Fill Bounds
			sabnd[i].cElements=GetLength(data, i);  
			sabnd[i].lLbound=0; 
		}
		psa = SafeArrayCreate(VT_R8,dim,sabnd);									// Create the safearray
		SafeArrayAccessData(psa, (void**)&sap);									// Access data pts
		
		memcpy(sap, data, sizeof(double)*len);

		SafeArrayUnaccessData(psa);				// Unaccess
	} else
	{
		dim = 1;
		////// Construct the SafeArray and total size
		for(int i=0;i<dim;i++){  	// Fill Bounds
			sabnd[i].cElements=0;  
			sabnd[i].lLbound=0; 
		}
		psa = SafeArrayCreate(VT_R8,dim,sabnd);									// Create the safearray
	}
    
	// Construct the Variant
	VariantInit(var);			// Initialize the Variant
	var->vt = VT_ARRAY|VT_R8;	// Tell it to hold an array of floats
	var->parray = psa;

	return 0;
}


/////////////////////////////////////////////////////////////////////////////
// CVisComplexObj
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// ERROR


STDMETHODIMP CVisComplexObj::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IVisComplexObj,
	};

	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))  return S_OK;
	}
	return S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CONSTR/DESTR

CVisComplexObj::CVisComplexObj()
{
    int i;
	for (i = 0; i < aiTopIndex; ++i)
        arrays[i] = NULL;
    scrVertices = NULL;
    lineStipple = 0;
    lineStippleFactor = 1;
    lineWidth   = 1.0f;
    pointSize   = 1.0f;
    drawMode    = odmPoints;
    color[0] = color[1] = color[2] = 1.0;
#if INDEX_MODE
	ColorIndex=VisWindow->ColorRGB2I(color);
#endif
	alpha=1;
	exact=0;

	// Clipped
	Clipped = VISWIN_IS_CLIPPED(X,Y);

	// Transform
    scale = 1;
	angle = 0;

	// Data Structures

	// ROT is used if not computing Exact vertex locations
	for(i=0; i<15; i++) ROT[i]=0.;
	ROT[10]=1.;  // [3 3] of the rotation component
	ROT[15]=1.;  // Last element -- multiplies translation
}

CVisComplexObj::~CVisComplexObj()
{
	logToFile((f, "VisComplexObj is to be deleted\n"));
	int i;
	for (i = 0; i < aiTopIndex; ++i) 
	{
        logToFile((f, "arrays[%d]: 0x%p\n", i, arrays[i]));
		FreeDoubleArray(arrays[i]);
    }
    logToFile((f, "scrVertices: 0x%p\n", scrVertices));
	FreeDoubleArray(scrVertices);
	Show=0;
	update(ACTION_DELETE, (double *)NULL, 0);
    logToFile((f, "VisComplexObj has been deleted\n"));
}

void CVisComplexObj::updateScrVertices(void)
{
    if(exact){
        // Do the transformations by hand for each point
        // and then use the exact calibration

        double co,si,x,y, *p = getVertices(), *d = scrVertices;
        int m, dim0 = GetLength(p, 0);

        co = cos(angle*(3.1415926535/180.0));
        si = sin(angle*(3.1415926535/180.0));
        Clipped = 0;
        for(m=GetLength(p, 1)-1; m >= 0; --m, p+=dim0, d+=dim0){
            // 1: Rotate
            x = co*p[0] - si*p[1];
            y = si*p[0] + co*p[1];
            // 2: Scale
            x *= scale;
            y *= scale;
            // 3: Translate
            x += X;
            y += Y;
            // Remap Through Calibration
            d[0] = XPosToScreen((float)x,(float)y);
            d[1] = YPosToScreen((float)x,(float)y);
            if (dim0 > 2) d[2] = p[2];
            // Clipped if any vtx is off screen
            if( VISWIN_IS_CLIPPED(d[0],d[1]) ) Clipped = 1;
        }
    }
}

STDMETHODIMP CVisComplexObj::get_clipped(double *pVal)
{
	*pVal = Clipped;
	return S_OK;
}

STDMETHODIMP CVisComplexObj::get_scale(double *pVal)
{
	*pVal = scale;
	return S_OK;
}

STDMETHODIMP CVisComplexObj::put_scale(double newVal)
{
	scale = newVal;
    updateScrVertices();
	update(ACTION_SCALE, &newVal, 1);
	return S_OK;
}

STDMETHODIMP CVisComplexObj::get_angle(double *pVal)
{
	*pVal = angle;
	return S_OK;
}

STDMETHODIMP CVisComplexObj::put_angle(double newVal)
{
	angle = newVal;
    updateScrVertices();
	update(ACTION_ANGLE, &newVal, 1);
	return S_OK;
}

STDMETHODIMP CVisComplexObj::get_exact(double *pVal)
{
	*pVal = exact;
	return S_OK;
}

STDMETHODIMP CVisComplexObj::put_exact(double newVal)
{
	exact = (int)newVal;
	update(ACTION_EXACT, &newVal, 1);
	return S_OK;
}

STDMETHODIMP CVisComplexObj::get_color(VARIANT *pVal)
{
    struct { int desc[4];  double data[3];  }
	temp = {  { 0, 3, 1, 3 }, { color[0], color[1], color[2] }  };
	VariantFromDoubleArray(temp.data, pVal);
	return S_OK;
}

STDMETHODIMP CVisComplexObj::put_color(VARIANT newVal)
{
	double *data;
	if (VariantToDoubleArray(&data, &newVal)) return E_INVALIDARG;
	if (data == NULL) return E_INVALIDARG;
	if (GetLength(data) < 3) return E_INVALIDARG;
	color[0] = (float)data[0];
	color[1] = (float)data[1];
	color[2] = (float)data[2];

	if (GetLength(data)>=4) alpha = data[3];
    
#if INDEX_MODE
	ColorIndex=VisWindow->ColorRGB2I(color);
#endif

	return S_OK;
}

STDMETHODIMP CVisComplexObj::get_vertices(VARIANT *pVal)
{
    VariantFromDoubleArray(getVertices(), pVal);
	logToFile((f, "getVertices: %d\n", getVertices() ? GetDim(getVertices()) : 0));
	return S_OK;
}

STDMETHODIMP CVisComplexObj::put_vertices(VARIANT newVal)
{
	double *data;
	HRESULT result = VariantToDoubleArray(&data, &newVal);
	logToFile((f, "putVertices: %d\n", result));
	if (result) return E_INVALIDARG;
    if (data != NULL)
    {
        if (GetDim(data) != 2) return E_INVALIDARG;
        if (GetLength(data, 0) != 2 && GetLength(data, 0) != 3) return E_INVALIDARG;
    }
	setVertices(data);
    FreeDoubleArray(scrVertices);
    scrVertices = CopyDoubleArrayStruct(getVertices());
    updateScrVertices();
	return S_OK;
}

/*
STDMETHODIMP CVisComplexObj::get_normals(VARIANT *pVal)
{
    VariantFromDoubleArray(getNormals(), pVal);
	return S_OK;
}

STDMETHODIMP CVisComplexObj::put_normals(VARIANT newVal)
{
	double *data;
	if (VariantToDoubleArray(&data, &newVal)) return E_INVALIDARG;
	setNormals(data);
	return S_OK;
}
*/

STDMETHODIMP CVisComplexObj::get_colors(VARIANT *pVal)
{
    VariantFromDoubleArray(getColors(), pVal);
	return S_OK;
}

STDMETHODIMP CVisComplexObj::put_colors(VARIANT newVal)
{
	double *data;
	if (VariantToDoubleArray(&data, &newVal)) return E_INVALIDARG;
	setColors(data);
	return S_OK;
}

/*
STDMETHODIMP CVisComplexObj::get_texCoords(VARIANT *pVal)
{
    VariantFromDoubleArray(getTexCoords(), pVal);
	return S_OK;
}

STDMETHODIMP CVisComplexObj::put_texCoords(VARIANT newVal)
{
	double *data;
	if (VariantToDoubleArray(&data, &newVal)) return E_INVALIDARG;
	setTexCoords(data);
	return S_OK;
}
*/

STDMETHODIMP CVisComplexObj::get_edgeFlags(VARIANT *pVal)
{
    VariantFromDoubleArray(getEdgeFlags(), pVal);
	return S_OK;
}

STDMETHODIMP CVisComplexObj::put_edgeFlags(VARIANT newVal)
{
	double *data;
	if (VariantToDoubleArray(&data, &newVal)) return E_INVALIDARG;
	setEdgeFlags(data);
	return S_OK;
}

STDMETHODIMP CVisComplexObj::get_indices(VARIANT *pVal)
{
    double *data = getIndices();
    double *newdata = CopyDoubleArrayStruct(data);
	if (newdata)
	{
		int len = GetLength(data);
		for (int i=0; i<len; ++i)
			newdata[i] = ((unsigned int *)data)[i];
    }
	VariantFromDoubleArray(newdata, pVal);
    FreeDoubleArray(newdata);
	return S_OK;
}

STDMETHODIMP CVisComplexObj::put_indices(VARIANT newVal)
{
	double *data;
	if (VariantToDoubleArray(&data, &newVal)) return E_INVALIDARG;
	if (data)
	{
		int len = GetLength(data);
		for (int i=0; i<len; ++i)
			((unsigned int *)data)[i] = (unsigned int)data[i];
	}
	setIndices(data);
	return S_OK;
}

STDMETHODIMP CVisComplexObj::get_polygonStipple(VARIANT *pVal)
{
    double *data = getPolygonStipple();
    double *newdata = CopyDoubleArrayStruct(data);
	if (newdata)
		for (int i=0; i<32; ++i)
			newdata[i] = ((unsigned int *)data)[i];
    VariantFromDoubleArray(newdata, pVal);
    FreeDoubleArray(newdata);
	return S_OK;
}

STDMETHODIMP CVisComplexObj::put_polygonStipple(VARIANT newVal)
{
	double *data;
	if (VariantToDoubleArray(&data, &newVal)) return E_INVALIDARG;
    if (GetLength(data) != 32) return E_INVALIDARG;
    for (int i=0; i<32; ++i)
        ((unsigned int *)data)[i] = (unsigned int)data[i];
	setPolygonStipple(data);
	return S_OK;
}

STDMETHODIMP CVisComplexObj::get_lineStipple(double *pVal)
{
	*pVal = lineStipple;
	return S_OK;
}

STDMETHODIMP CVisComplexObj::put_lineStipple(double newVal)
{
	lineStipple = (int)newVal;
	update(ACTION_LINESTIPPLE, &newVal, 1);
	return S_OK;
}

STDMETHODIMP CVisComplexObj::get_lineStippleFactor(double *pVal)
{
	*pVal = lineStippleFactor;
	return S_OK;
}

STDMETHODIMP CVisComplexObj::put_lineStippleFactor(double newVal)
{
	lineStippleFactor = (int)newVal;
	update(ACTION_LINESTIPPLEFACTOR, &newVal, 1);
	return S_OK;
}

STDMETHODIMP CVisComplexObj::get_lineWidth(double *pVal)
{
	*pVal = lineWidth;
	return S_OK;
}

STDMETHODIMP CVisComplexObj::put_lineWidth(double newVal)
{
	lineWidth = newVal;
	update(ACTION_LINEWIDTH, &newVal, 1);
	return S_OK;
}

STDMETHODIMP CVisComplexObj::get_pointSize(double *pVal)
{
	*pVal = pointSize;
	return S_OK;
}

STDMETHODIMP CVisComplexObj::put_pointSize(double newVal)
{
	pointSize = newVal;
	update(ACTION_POINTSIZE, &newVal, 1);
	return S_OK;
}

struct VDrawModeStringMap
{ 
	const wchar_t	*name;
	int				 val;
};

const struct VDrawModeStringMap drawModeStringMap[] =
{
	{   L"Points",        odmPoints           },
    {   L"Lines",         odmLines            },
    {   L"LineStrip",     odmLineStrip        },
    {   L"LineLoop",      odmLineLoop         },
    {   L"Triangles",     odmTriangles        },
    {   L"TriangleStrip", odmTriangleStrip    },
    {   L"TriangleFan",   odmTriangleFan      },
    {   L"Quads",         odmQuads            },
    {   L"QuadStrip",     odmQuadStrip        },
    {   L"Polygon",       odmPolygon          },
    {   NULL,             0                   },
};

STDMETHODIMP CVisComplexObj::get_drawMode(BSTR *pVal)
{
    for (int i=0; drawModeStringMap[i].name != NULL; ++i)
    {
      if (drawModeStringMap[i].val == drawMode)
      {
        *pVal = ::SysAllocString(drawModeStringMap[i].name);
        break;
      }
	}
    return S_OK;
}

STDMETHODIMP CVisComplexObj::put_drawMode(BSTR newVal)
{
    bool found = false;
    for (int i=0; drawModeStringMap[i].name != NULL; ++i)
    {
      if (wcscmp(drawModeStringMap[i].name, newVal) == 0)
      {
        found = true;
        drawMode = (VOpglDrawMode)drawModeStringMap[i].val;
        update(ACTION_DRAWMODE, (int *)&drawMode, 1);
        break;
      }
	}
    return found ? S_OK : E_INVALIDARG;
}

/////////////////////////////////////////////////////////////////////////////
// Draw
/////////////////////////////////////////////////////////////////////////////
const GLenum glDrawModeMap[] = {
    GL_POINTS          ,
    GL_LINES           ,
    GL_LINE_STRIP      ,
    GL_LINE_LOOP       ,
    GL_TRIANGLES       ,
    GL_TRIANGLE_STRIP  ,
    GL_TRIANGLE_FAN    ,
    GL_QUADS           ,
    GL_QUAD_STRIP      ,
    GL_POLYGON         ,
};

void
CVisComplexObj::draw()
{
	logToFile((f, "VisComplexObj Draw\n"));
	if(!Show) return;
    double *vertices = exact ? scrVertices : getVertices();
    if (arrays[aiIndices] != 0 && GetLength(arrays[aiIndices], 1) == 0 ||
        vertices == 0 || GetLength(vertices, 1) == 0)
        return;

    glPushMatrix();

    if(exact){
        glMatrixMode (GL_MODELVIEW);
        glLoadIdentity();
        glTranslated(0.0, 0.0, Z);
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
        ROT[0]=(float)scale*JAC[0][0]; ROT[1]=(float)scale*JAC[1][0];
        ROT[4]=(float)scale*JAC[0][1]; ROT[5]=(float)scale*JAC[1][1];
        ROT[12]=x; ROT[13]=y; ROT[14]=Z;

        glMatrixMode (GL_MODELVIEW);
        // glLoadIdentity();
        // glTranslatef((float)x,(float)y,Z);      // 3: Translate
        // glScalef((float)scx,(float)scy,1);      // 2: Scale
        glLoadMatrixf(ROT);              // 2: Translate and Scale
        glRotatef((float)angle,0,0,1);   // 1: Rotate About Z axis
    }

#if INDEX_MODE
    glIndexi(ColorIndex);
#else
	glColor4d(color[0],color[1],color[2],alpha);
#endif

    if (drawMode >= odmLines && drawMode <= odmLineLoop)
    {
        if (lineStipple != 0)
        {
            glLineStipple(lineStippleFactor, lineStipple);
            glEnable(GL_LINE_STIPPLE);
        }

        if (lineWidth != 1.0) glLineWidth((float)lineWidth);
    }

    if (drawMode == odmPoints && pointSize != 1.0) glPointSize((float)pointSize);

    if (drawMode >= odmTriangles && drawMode <= odmPolygon)
    {
        if (arrays[aiPolygonStipple] != 0)
        {
            glEnable(GL_POLYGON_STIPPLE);
            glPolygonStipple((unsigned char *)arrays[aiPolygonStipple]);
        }
    }

    if (vertices            != 0)   glEnableClientState(GL_VERTEX_ARRAY);
    if (arrays[aiNormals  ] != 0)   glEnableClientState(GL_NORMAL_ARRAY);
    if (arrays[aiColors   ] != 0)   glEnableClientState(GL_COLOR_ARRAY);
    if (arrays[aiEdgeFlags] != 0)   glEnableClientState(GL_EDGE_FLAG_ARRAY);

    if (vertices != 0)
        glVertexPointer(GetLength(vertices, 0), GL_DOUBLE, 0, vertices);
    if (arrays[aiNormals] != 0)
        glNormalPointer(GL_DOUBLE, 0, arrays[aiNormals]);
    if (arrays[aiColors] != 0)
        glColorPointer (GetLength(arrays[aiColors], 0), GL_DOUBLE, 0, arrays[aiColors]);
    if (arrays[aiEdgeFlags] != 0)
        glEdgeFlagPointer(0, arrays[aiEdgeFlags]);

    if (arrays[aiIndices] != 0)
        glDrawElements(glDrawModeMap[drawMode], GetLength(arrays[aiIndices]), GL_UNSIGNED_INT, arrays[aiIndices]);
    else
        glDrawArrays(glDrawModeMap[drawMode], 0, GetLength(vertices, 1));

    if (vertices            != 0)   glDisableClientState(GL_VERTEX_ARRAY);
    if (arrays[aiNormals  ] != 0)   glDisableClientState(GL_NORMAL_ARRAY);
    if (arrays[aiColors   ] != 0)   glDisableClientState(GL_COLOR_ARRAY);
    if (arrays[aiEdgeFlags] != 0)   glDisableClientState(GL_EDGE_FLAG_ARRAY);

    if (drawMode >= odmTriangles && drawMode <= odmPolygon)
    {
        if (arrays[aiPolygonStipple] != 0) glDisable(GL_POLYGON_STIPPLE);
    }

    if (drawMode >= odmLines && drawMode <= odmLineLoop)
    {
        if (lineStipple != 0) glDisable(GL_LINE_STIPPLE);
        if (lineWidth != 1.0) glLineWidth(1.0);
    }

    if (drawMode == odmPoints && pointSize != 1.0) glPointSize(1.0);

    glPopMatrix();
}

