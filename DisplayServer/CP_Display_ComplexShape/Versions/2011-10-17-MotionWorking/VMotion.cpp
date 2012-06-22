// VMotion.cpp : Implementation of CVMotion
#include "ATL_Defs.h"            // ATL, COM and Windows definitions
#include "resource.h"            // Resource IDs for registry
#include "CP_Display.h"
#include "VMotion.h"

#include <stdio.h>
#include <math.h>
#include <gl\gl.h>               // Header File For The OpenGL32 Library
#include <gl\glu.h>              // Header File For The GLu32 Library

#include "ComUtils.h"
#include "ComUtils2.h"
#include "Util\VariantLib.h"
#include "GL_Engine.h"


#define PI 3.14159

/////////////////////////////////////////////////////////////////////////////
// CVMotion

//==============================================================================
CVMotion::CVMotion(){

	nVertices = 100;
	circle = TRUE;
	lifetime = 2;
	coherence = 100;
	velX=velY=0;
	vertices = NULL;
	vertexVelOffset = NULL;
	vertexTimes = NULL;

	
	exact=0;
	pointSize   = 1.0;
	m_dScale    = 10.0;  // Set Default Radius to 10
	
	// ROT is used if not computing Exact vertex locations
	for(int i=0; i<15; i++) ROT[i]=0.;
	ROT[10]=1.;  // [3 3] of the rotation component
	ROT[15]=1.;  // Last element -- multiplies translation

}

//==============================================================================
CVMotion::~CVMotion(){
	if(g_blnAutoUpdate)	g_blnAutoUpdate=FALSE;
	if(vertices)		FreeDoubleArray(vertices);
	if(vertexVelOffset)	delete vertexVelOffset;
	if(vertexTimes)		delete vertexTimes;
}



//====================================================================
/*STDMETHODIMP CVMotion::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IVMotions
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}
*/


//==============================================================================
//                   Standard interfaces
//==============================================================================
#define VOBJECT CVMotion  // this define is needed for <VObjectMethodsImpl.h>
#include "VObjectMethodsImpl.h"


//==============================================================================
//                   Motion-specific interfaces
//==============================================================================

STDMETHODIMP CVMotion::GetExact(double *pVal)
{
	*pVal = exact;
	return S_OK;
}
STDMETHODIMP CVMotion::SetExact(double newVal, long iLogID)
{
	exact = (int)newVal;
	return S_OK;
}


STDMETHODIMP CVMotion::IsCircle(double *pVal)
{
	if(circle)	*pVal=1.;
	else		*pVal=0.;
	return S_OK;
}
STDMETHODIMP CVMotion::UseCircle(long iLogID)
{
	if(!circle){ 
		circle = TRUE;
		resampleFlag=TRUE;
		m_RequestUpdate(iLogID);
	}
	return S_OK;
}
STDMETHODIMP CVMotion::IsSquare(double *pVal)
{
	if(circle)	*pVal=0.;
	else		*pVal=1.;
	return S_OK;
}
STDMETHODIMP CVMotion::UseSquare(long iLogID)
{
	if(circle){ 
		circle = FALSE;
		resampleFlag=TRUE;
		m_RequestUpdate(iLogID);
	}
	return S_OK;
}


STDMETHODIMP CVMotion::GetNPoints(double *pVal)
{
	*pVal = nVertices;
	return S_OK;
}
STDMETHODIMP CVMotion::SetNPoints(double newVal, long iLogID)
{
	if( nVertices != (int)newVal ){
		nVertices = (int)newVal;
		resampleFlag=TRUE;
		m_RequestUpdate(iLogID);
	}
	return S_OK;
}


STDMETHODIMP CVMotion::GetLifetime(double *pVal)
{
	*pVal = lifetime;
	return S_OK;
}
STDMETHODIMP CVMotion::SetLifetime(double newVal, long iLogID)
{
	lifetime = newVal;
	resampleFlag=TRUE;
	return S_OK;
}
STDMETHODIMP CVMotion::GetCoherence(double *pVal)
{
	*pVal = coherence;
	return S_OK;
}
STDMETHODIMP CVMotion::SetCoherence(double newVal, long iLogID)
{
	if( coherence != newVal ){
		coherence = newVal;
		if(coherence<0) coherence=0;
		else if(coherence>100) coherence=100;
		resampleFlag=TRUE;
		m_RequestUpdate(iLogID);
	}
	return S_OK;
}


STDMETHODIMP CVMotion::GetPointSize(double *pVal)
{
	*pVal = pointSize;
	return S_OK;
}
STDMETHODIMP CVMotion::SetPointSize(double newVal, long iLogID)
{
	pointSize = newVal;
	return S_OK;
}


STDMETHODIMP CVMotion::GetVelocity( VARIANT * pVal)
{
	double * pdData;
	int dim, *dimlen;
	
	dim = 2;
	dimlen = new int[2];
	dimlen[0]=1; dimlen[1]=2;
	pdData = CreateDoubleArray(dim,dimlen);
	
	pdData[0] = velX;
	pdData[1] = velY;
	
	if (VariantFromDoubleArray(pdData, pVal)) return E_INVALIDARG;
	
	FreeDoubleArray(pdData);

	return S_OK;
}
STDMETHODIMP CVMotion::SetVelocity( VARIANT newVal, long iLogID)
{
	double * pdData;
	
	// We expect 2-long array of doubles
	if (VariantToDoubleArray(&pdData, &newVal)) return E_INVALIDARG;
	if (GetLength(pdData) < 2) return E_INVALIDARG;
	
	velX = pdData[0];
	velY = pdData[1];
	
	return S_OK;
}


// for diagnostic/debugging puposes
STDMETHODIMP CVMotion::GetVertices(VARIANT *pVal)
{
	if(vertices) VariantFromDoubleArray(vertices, pVal);
	else{
		double *d = new double[3]; 
		d[0]=1; d[1]=1; d[2]=0; 
		VariantFromDoubleArray(d, pVal);
		delete d;
	}
	return S_OK;
}



// UDP
STDMETHODIMP CVMotion::StartUDPSync(long iLogID)
{
	if(!g_UDPsetupFlag) return E_INVALIDARG;

	UDPsyncFlag = TRUE;
	g_RequestUpdate(iLogID);
	return S_OK;
}

// UDP
STDMETHODIMP CVMotion::StopUDPSync(long iLogID)
{
	if(!g_UDPsetupFlag) return S_OK;

	UDPsyncFlag = FALSE;
	g_RequestUpdate(iLogID);
	return S_OK;
}


//==============================================================================
//                   The Work
//==============================================================================

void
CVMotion::m_sampleVertex(int i, double *pos, double *v)
{
	// Sample Position uniformly in region
	if(circle){
		double a,r;
		a = 2*PI*(double)rand()/(double)RAND_MAX;
		r = sqrt((double)rand()/(double)RAND_MAX);
		pos[0]=r*cos(a);
		pos[1]=r*sin(a);
	} else{
		pos[0]=2*(double)rand()/(double)RAND_MAX-1;
		pos[1]=2*(double)rand()/(double)RAND_MAX-1;
	}

	// Sample velocity if it's a "non-coherent" point
	if( i < nVertices*(coherence/100.) )  
		*v = 0;
	else 
		*v = 2*PI*(double)rand()/(double)RAND_MAX;
}


void
CVMotion::m_sampleVertices()
{
	int dim, dimlen[2];
	int i;
	double *p, *v;

	// release old data
	FreeDoubleArray(vertices);
	if(vertexTimes) delete vertexTimes;
	// get new array
	dim = 2;
	dimlen[0]=2; dimlen[1]=nVertices;
	vertices = CreateDoubleArray(dim, dimlen);
	vertexVelOffset = new double[nVertices];
	vertexTimes = new double[nVertices];
	
	// Sample vertices
	for (p=vertices, v=vertexVelOffset, i=0; i<nVertices; p+=2, ++v, ++i){
		m_sampleVertex(i,p,v);
	}

	// Sample Times between 0 and lifetime
	for(i=0; i<nVertices; i++){
		vertexTimes[i]=lifetime*((double)rand()/(double)RAND_MAX);
	}
	
	// Get Frame Time
	_ftime( &lastTime );
}


void
CVMotion::m_updateVertices()
{
	int i;
	struct _timeb thisTime;
	double dt, *p;
	double speed, vang, ivelX, ivelY;

	// Get new time
	_ftime( &thisTime );
	// Compute elapsed time
	dt = (thisTime.time-lastTime.time) + thisTime.millitm/1000.0 - lastTime.millitm/1000.0;
	// Store new time
	lastTime.time = thisTime.time;
	lastTime.millitm = thisTime.millitm;

	
	// Update positions based on speed
	for (p=vertices, i=0; i<nVertices; p+=2, ++i){
		
		/*
		// Non-coherent points are sampled randomly
		if(i>=nVertices*coherence/100){
			m_sampleVertex(p);
			continue;
		}
		*/

		vertexTimes[i] += dt;

		speed = sqrt(velX*velX+velY*velY);
		vang = atan2(velY,velX);

		if( lifetime>0 && vertexTimes[i]>lifetime ){
			// Timeout on this vertex - resample
			m_sampleVertex(i,p,vertexVelOffset+i);
			vertexTimes[i]=0.;
		} else{
			if(vertexVelOffset[i]==0){
				ivelX = velX; 
				ivelY = velY;
			} else {
				ivelX = speed*cos(vang+vertexVelOffset[i]);
				ivelY = speed*sin(vang+vertexVelOffset[i]);
			}
			p[0] += ivelX * dt/m_dScale;
			p[1] += ivelY * dt/m_dScale;
			if(circle){
				double r = sqrt(p[0]*p[0]+p[1]*p[1]); 
				while(r>1){
					// If outside circle, come back at other side of 
					// chord defined by velocity vector!
					double vvecX, vvecY, dbisect, dpos, dchord;
					
					vvecX = ivelX/speed;
					vvecY = ivelY/speed;

					dbisect = -p[0]*vvecY + p[1]*vvecX;  // From center to point, along perp (bisect point)
					dpos  = p[0]*vvecX + p[1]*vvecY;     // From center to point, along vel  
					dchord = 2*sqrt(1-dbisect*dbisect);  // Length of chord
					
					p[0] = p[0] - dchord*vvecX; 
					p[1] = p[1] - dchord*vvecY; 

					r = sqrt(p[0]*p[0]+p[1]*p[1])-0.0001;  // worried about inf loop near r=1 
				}
			} else{
				if( fabs(p[0])>1 ) p[0]=fmod(p[0]+1,2)-1;
				if( fabs(p[1])>1 ) p[1]=fmod(p[1]+1,2)-1;
			}
		}
		
	}
}


void
CVMotion::Draw()
{
	static double ovelX = -99999;
	static double ovelY = -99999;

	// Want to set g_blnAutoUpdate on Show()/Hide().
	// The problem is that these belong to CObject.
	// Not a big deal, though, since calls to
	// Show/Hide will trigger an update, which
	// will land you here
	if(!m_IsVisible || nVertices<=0){
		if(g_blnAutoUpdate) g_blnAutoUpdate=FALSE;
		return;
	}
	if(!g_blnAutoUpdate) g_blnAutoUpdate=TRUE;


	// Sync New Vel Values to TDT via UDP
	if(UDPsyncFlag && (velX!=ovelX || velY!=ovelY) ){
		ovelX=velX; ovelY=velY;
		double *data = new double[2];
		data[0]=velX;  data[1]=velY;
		g_requestUDP(data,2);
	}

	// Sample or Update Points
	if(!vertices || resampleFlag) { 
		m_sampleVertices();
		resampleFlag=0;
	}
	else  m_updateVertices();

	////////////////////////
	// Now really do the Drawing

    glPushMatrix();
	
    if(0){ // exact is disabled because I didn't add the per-vertex 
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
	
    if (pointSize != 1.0) glPointSize((float)pointSize);
	
    glEnableClientState(GL_VERTEX_ARRAY);
	
	glVertexPointer(GetLength(vertices, 0), GL_DOUBLE, 0, vertices);
	glDrawArrays(GL_POINTS, 0, GetLength(vertices, 1));
	
	glDisableClientState(GL_VERTEX_ARRAY);
	
	if (pointSize != 1.0) glPointSize(1.0);
	
	glPopMatrix();
}

