// VComplexShape.cpp : Implementation of CVComplexShape
//#include "stdafx.h"
#include "ATL_Defs.h"            // ATL, COM and Windows definitions
#include "resource.h"            // Resource IDs for registry
#include "CP_Display.h"
#include "VComplexShape.h"

#include <stdio.h>
#include <math.h>
#include <gl\gl.h>               // Header File For The OpenGL32 Library
#include <gl\glu.h>              // Header File For The GLu32 Library


#include "ComUtils.h"
#include "GL_Engine.h"


///////////////////////////////////////////////////////////////////////////
// VARIANT / ARRAY STUFF

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
	// logToFile((f, "DoubleArrayCreated: 0x%p\n", result));
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
//	logToFile((f, "DoubleArrayCreated: 0x%p\n", result));
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
//	logToFile((f, "DoubleArrayCreated: 0x%p\n", result));
	result = result + offset;
    memcpy(result-offset, data-offset, sizeof(double)*offset);
    return result;
}

void FreeDoubleArray(double *data)
{
    if (data != NULL)
	{
		data = data - GetOffset(GetDim(data));
//		logToFile((f, "DoubleArrayFreed: 0x%p\n", data));
		delete[] data;
	}
}

int VariantToDoubleArray(double **data, VARIANT *var)
{
	long uBnd,lBnd;
	int dim, dimlen[MAXDIM];
	int err=0;
	
	// Check for ARRAY of the right type
    //logToFile((f, "VaraintToDoubleArray: var = 0x%p\n", var));
	if( var==NULL )						return COMUTIL_ERR_NULL;
    //logToFile((f, "VaraintToDoubleArray: var.type = %d\n", var->vt));
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
	
    //logToFile((f, "VaraintToDoubleArray: %d, (%d, %d)\n", dim, dimlen[0], dimlen[1]));

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
// CVComplexShape

STDMETHODIMP CVComplexShape::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IVComplexShape
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CONSTR/DESTR

CVComplexShape::CVComplexShape()
{
    int i;
	for (i=0; i<aiTopIndex; ++i)  arrays[i] = NULL;
    scrVertices = NULL;
    lineStipple = 0;
    lineStippleFactor = 1;
    lineWidth   = 1.0f;
    pointSize   = 1.0f;
    drawMode    = odmPoints;
	exact=0;

	// ROT is used if not computing Exact vertex locations
	for(i=0; i<15; i++) ROT[i]=0.;
	ROT[10]=1.;  // [3 3] of the rotation component
	ROT[15]=1.;  // Last element -- multiplies translation
}

CVComplexShape::~CVComplexShape()
{
	int i;
	for (i=0; i<aiTopIndex; ++i) FreeDoubleArray(arrays[i]);
	FreeDoubleArray(scrVertices);
}

void CVComplexShape::updateScrVertices(void)
{
    if(exact){
        // Do the transformations by hand for each point
        // and then use the exact calibration

        double co,si,x,y, *p = m_getVertices(), *d = scrVertices;
        int m, dim0 = GetLength(p, 0);

        co = cos(m_dAngle*(3.1415926535/180.0));
        si = sin(m_dAngle*(3.1415926535/180.0));
        m_nClipped = 0;
        for(m=GetLength(p, 1)-1; m >= 0; --m, p+=dim0, d+=dim0){
            // 1: Rotate
            x = co*p[0] - si*p[1];
            y = si*p[0] + co*p[1];
            // 2: Scale
            x *= m_dScale;
            y *= m_dScale;
            // 3: Translate
            x += m_dX;
            y += m_dY;
            /* Old VisWin
			// Remap Through Calibration
            d[0] = XPosToScreen((float)x,(float)y);
            d[1] = YPosToScreen((float)x,(float)y);
            if (dim0 > 2) d[2] = p[2];
            // Clipped if any vtx is off screen
            if( VISWIN_IS_CLIPPED(d[0],d[1]) ) Clipped = 1;
			*/
			g_TransformCoordinatesD( x, y, d, d+1 );
			m_nClipped += IS_OFF_WINDOW(d[0],d[1]);
            if (dim0 > 2) d[2] = p[2];
        }
    }
}


//////////////////////////////
//  COMMON METHODS
#define VOBJECT CVComplexShape  // this define is needed for <VObjectMethodsImpl.h>
#include "VObjectMethodsImpl.h"


/////////////////////////////////////////////////////////////////////////////
// Get/Set Parameters Specific to VComplexObject



STDMETHODIMP CVComplexShape::GetVertices(VARIANT *pVal)
{
    VariantFromDoubleArray(m_getVertices(), pVal);
	return S_OK;
}

STDMETHODIMP CVComplexShape::SetVertices(VARIANT newVal, long iLogID)
{
	double *data;
	HRESULT result = VariantToDoubleArray(&data, &newVal);
	if (result) return E_INVALIDARG;
    if (data != NULL)
    {
        if (GetDim(data) < 2) return E_INVALIDARG;
        if (GetLength(data, 0) != 2 && GetLength(data, 0) != 3) return E_INVALIDARG;
    }
	setArray(aiVertices,data);
    FreeDoubleArray(scrVertices);
    scrVertices = CopyDoubleArrayStruct(m_getVertices());
    updateScrVertices();

    m_RequestUpdate(iLogID);
	return S_OK;
}

STDMETHODIMP CVComplexShape::GetColors(VARIANT *pVal)
{
    VariantFromDoubleArray(m_getColors(), pVal);
	return S_OK;
}

STDMETHODIMP CVComplexShape::SetColors(VARIANT newVal, long iLogID)
{
	double *data;
	if (VariantToDoubleArray(&data, &newVal)) return E_INVALIDARG;
	setArray(aiColors,data);
    
	m_RequestUpdate(iLogID);
	return S_OK;
}

STDMETHODIMP CVComplexShape::GetEdgeFlags(VARIANT *pVal)
{
    VariantFromDoubleArray(m_getEdgeFlags(), pVal);
	return S_OK;
}

STDMETHODIMP CVComplexShape::SetEdgeFlags(VARIANT newVal, long iLogID)
{
	double *data;
	if (VariantToDoubleArray(&data, &newVal)) return E_INVALIDARG;
	setArray(aiEdgeFlags,data);

	m_RequestUpdate(iLogID);
	return S_OK;
}

STDMETHODIMP CVComplexShape::GetIndices(VARIANT *pVal)
{
    double *data = m_getIndices();
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

STDMETHODIMP CVComplexShape::SetIndices(VARIANT newVal, long iLogID)
{
	double *data;
	if (VariantToDoubleArray(&data, &newVal)) return E_INVALIDARG;
	if (data)
	{
		int len = GetLength(data);
		for (int i=0; i<len; ++i)
			((unsigned int *)data)[i] = (unsigned int)data[i];
	}
	setArray(aiIndices,data);

	m_RequestUpdate(iLogID);
	return S_OK;
}

STDMETHODIMP CVComplexShape::GetPolygonStipple(VARIANT *pVal)
{
    double *data = m_getPolygonStipple();
    double *newdata = CopyDoubleArrayStruct(data);
	if (newdata)
		for (int i=0; i<32; ++i)
			newdata[i] = ((unsigned int *)data)[i];
    VariantFromDoubleArray(newdata, pVal);
    FreeDoubleArray(newdata);
	return S_OK;
}

STDMETHODIMP CVComplexShape::SetPolygonStipple(VARIANT newVal, long iLogID)
{
	double *data;
	if (VariantToDoubleArray(&data, &newVal)) return E_INVALIDARG;
    if (GetLength(data) != 32) return E_INVALIDARG;
    for (int i=0; i<32; ++i)
        ((unsigned int *)data)[i] = (unsigned int)data[i];
	setArray(aiPolygonStipple,data);

	m_RequestUpdate(iLogID);
	return S_OK;
}

STDMETHODIMP CVComplexShape::GetLineStipple(double *pVal)
{
	*pVal = lineStipple;
	return S_OK;
}

STDMETHODIMP CVComplexShape::SetLineStipple(double newVal, long iLogID)
{
	lineStipple = (int)newVal;

	m_RequestUpdate(iLogID);
	return S_OK;
}

STDMETHODIMP CVComplexShape::GetLineStippleFactor(double *pVal)
{
	*pVal = lineStippleFactor;
	return S_OK;
}

STDMETHODIMP CVComplexShape::SetLineStippleFactor(double newVal, long iLogID)
{
	lineStippleFactor = (int)newVal;

	m_RequestUpdate(iLogID);
	return S_OK;
}

STDMETHODIMP CVComplexShape::GetLineWidth(double *pVal)
{
	*pVal = lineWidth;
	return S_OK;
}

STDMETHODIMP CVComplexShape::SetLineWidth(double newVal, long iLogID)
{
	lineWidth = newVal;

	m_RequestUpdate(iLogID);
	return S_OK;
}

STDMETHODIMP CVComplexShape::GetPointSize(double *pVal)
{
	*pVal = pointSize;
	return S_OK;
}

STDMETHODIMP CVComplexShape::SetPointSize(double newVal, long iLogID)
{
	pointSize = newVal;

	m_RequestUpdate(iLogID);
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

STDMETHODIMP CVComplexShape::GetDrawMode(BSTR *pVal)
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

STDMETHODIMP CVComplexShape::SetDrawMode(BSTR newVal, long iLogID)
{
    bool found = false;
    for (int i=0; drawModeStringMap[i].name != NULL; ++i)
    {
      if (wcscmp(drawModeStringMap[i].name, newVal) == 0)
      {
        found = true;
        drawMode = (VOpglDrawMode)drawModeStringMap[i].val;
        break;
      }
	}

	if(found) m_RequestUpdate(iLogID);

    return found ? S_OK : E_INVALIDARG;
}

STDMETHODIMP CVComplexShape::GetExact(double *pVal)
{
	*pVal = exact;
	return S_OK;
}

STDMETHODIMP CVComplexShape::SetExact(double newVal, long iLogID)
{
	exact = (int)newVal;

	m_RequestUpdate(iLogID);
	return S_OK;
}


//////////////////////////////
// Draw
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
CVComplexShape::Draw()
{
//	logToFile((f, "CVComplexShape Draw\n"));
	if(!m_IsVisible) return;
    double *vertices = exact ? scrVertices : m_getVertices();
    if (arrays[aiIndices] != 0 && GetLength(arrays[aiIndices], 1) == 0 ||
        vertices == 0 || GetLength(vertices, 1) == 0)
        return;

    glPushMatrix();

    if(exact){
        glMatrixMode (GL_MODELVIEW);
        glLoadIdentity();
        glTranslated(0.0, 0.0, m_dZ);
    }
    else {
        // Only get exact calibration location of center
        // and approximate the rest of the points
        /*
		float x = XPosToScreen((float)X,(float)Y);
        float y = YPosToScreen((float)X,(float)Y);

        m_nClipped = VISWIN_IS_CLIPPED(x,y);
		*/
		float pix[2];
		g_TransformCoordinatesF( m_dX, m_dY, pix, pix+1 );
		m_nClipped = IS_OFF_WINDOW(pix[0],pix[1]);

        g_TransformGradientD(JAC,m_dX,m_dY);
		/* DPosToDScreen(JAC,x,y); */
        // Rot 4x4, allocated by column, as in matlab
        // Jac, though, is only the 2x2 Jacobian
        ROT[0]=m_dScale*JAC[0][0]; ROT[1]=m_dScale*JAC[1][0];
        ROT[4]=m_dScale*JAC[0][1]; ROT[5]=m_dScale*JAC[1][1];
        ROT[12]=pix[0]; ROT[13]=pix[1]; ROT[14]=m_dZ;



        glMatrixMode (GL_MODELVIEW);
        // glLoadIdentity();
        // glTranslatef((float)x,(float)y,Z);      // 3: Translate
        // glScalef((float)scx,(float)scy,1);      // 2: Scale
        glLoadMatrixd(ROT);              // 2: Translate and Scale
        glRotatef((float)m_dAngle,0,0,1);   // 1: Rotate About Z axis
    }

	glColor4d(m_fRGB[0],m_fRGB[1],m_fRGB[2],m_fAlpha);

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
    if (arrays[aiColors   ] != 0)   glEnableClientState(GL_COLOR_ARRAY);
    if (arrays[aiEdgeFlags] != 0)   glEnableClientState(GL_EDGE_FLAG_ARRAY);

	if (arrays[aiIndices] != 0)
	{
		
		if (vertices != 0)
			glVertexPointer(GetLength(vertices, 0), GL_DOUBLE, 0, vertices);
		if (arrays[aiColors] != 0)
			glColorPointer (GetLength(arrays[aiColors], 0), GL_DOUBLE, 0, arrays[aiColors]);
//		if (arrays[aiEdgeFlags] != 0)
//			glEdgeFlagPointer(0, arrays[aiEdgeFlags]);

		if (GetDim(arrays[aiIndices]) == 1 || GetLength(arrays[aiIndices], 0) == 1)
		    glDrawElements(glDrawModeMap[drawMode], GetLength(arrays[aiIndices]), GL_UNSIGNED_INT, arrays[aiIndices]);
		else
		{
			int len0 = GetLength(arrays[aiIndices], 0);
			int len1 = GetLength(arrays[aiIndices], 1);
			for (int i=0; i < len1; ++i)
				glDrawElements(glDrawModeMap[drawMode], len0, GL_UNSIGNED_INT, ((unsigned int *)arrays[aiIndices]) + len0 * i);
		}
	}
	else if (vertices != 0)
	{
		int len2 = GetDim(vertices) <= 2 ? 1 : GetLength(vertices, 2);
		for (int i=0; i < len2; ++i)
		{
			if (vertices != 0)
				glVertexPointer(GetLength(vertices, 0), GL_DOUBLE, 0, vertices + GetLength(vertices, 0) * GetLength(vertices, 1) * i);
			if (arrays[aiColors] != 0)
				glColorPointer (GetLength(arrays[aiColors], 0), GL_DOUBLE, 0, arrays[aiColors] + GetLength(arrays[aiColors], 0) * GetLength(arrays[aiColors], 1) * i);
//			if (arrays[aiEdgeFlags] != 0)
//				glEdgeFlagPointer(0, arrays[aiEdgeFlags]);
			glDrawArrays(glDrawModeMap[drawMode], 0, GetLength(vertices, 1));
		}
	}

    if (vertices            != 0)   glDisableClientState(GL_VERTEX_ARRAY);
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

