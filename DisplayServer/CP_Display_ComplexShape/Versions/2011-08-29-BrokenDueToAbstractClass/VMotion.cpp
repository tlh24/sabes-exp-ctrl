// VMotion.cpp : Implementation of CVMotion
#include "ATL_Defs.h"            // ATL, COM and Windows definitions
#include "resource.h"            // Resource IDs for registry
#include "CP_Display.h"
#include "VMotion.h"
#include "VComplexShape.h"

#include <stdio.h>
#include <math.h>
#include <gl\gl.h>               // Header File For The OpenGL32 Library
#include <gl\glu.h>              // Header File For The GLu32 Library
#include <sys\timeb.h>

#include "ComUtils.h"
#include "ComUtils2.h"
#include "GL_Engine.h"


#define PI 3.14159

/////////////////////////////////////////////////////////////////////////////
// CVMotion

//==============================================================================
CVMotion::CVMotion(){

  nVertices = 100;
  cirlce = TRUE;
  lifetime = 1;
  coherence = 100;
  vX=vY=0;

  c_complexShape = new CVComplexShape();

  vSetScale(10,0);  // Set Default Radius to 10
  c_complexShape.vSetScale(10,0);

}

//==============================================================================
CVMotion::~CVMotion(){
	if(m_IsVisible)		Stop();
	if(vertices)		delete vertices;
	if(c_complexShape) delete c_complexShape;
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
//#include "VObjectMethodsImpl.h"
// Unfortunately, this object is an exception, because it's not a "REAL" object
// Parameters need to be passed to object. 
// Should probably create a new kind of class -- an object container or controller
// -- rather than misuse object.... but this will do for now

//==============================================================================
STDMETHODIMP VOBJECT::GetXY( VARIANT * pvXY) { 
  return c_complexShape.vGetXY( pvXY);
}

//==============================================================================
STDMETHODIMP VOBJECT::SetXY( VARIANT vXY, long iLogID) {
  return c_complexShape.vSetXY( vXY, iLogID);
}

//==============================================================================
STDMETHODIMP VOBJECT::GetZ( double *pdZ) {
  return c_complexShape.vGetZ( pdZ);
}

//==============================================================================
STDMETHODIMP VOBJECT::SetZ( double dZ, long iLogID) {
  return c_complexShape.vSetZ(dZ, iLogID);
}

//==============================================================================
STDMETHODIMP VOBJECT::GetScale( double * pdScale) {
  return c_complexShape.vGetScale(pdScale);
}

//==============================================================================
STDMETHODIMP VOBJECT::SetScale( double dScale, long iLogIDD) {
  return c_complexShape.vSetScale( dScale, iLogIDD);
}

//==============================================================================
STDMETHODIMP VOBJECT::GetAngle( double * pdAngle) {
  return c_complexShape.vGetAngle( pdAngle);
}

//==============================================================================
STDMETHODIMP VOBJECT::SetAngle( double dAngle, long iLogID) {
  return c_complexShape.vSetAngle( dAngle, iLogID);
}

//==============================================================================
STDMETHODIMP VOBJECT::GetColor( VARIANT * pvRGB) {
  return c_complexShape.vGetColor( pvRGB);
}

//==============================================================================
STDMETHODIMP VOBJECT::SetColor( VARIANT vRGB, long iLogID ) {
  return c_complexShape.vSetColor( vRGB, iLogID );
}

//==============================================================================
STDMETHODIMP VOBJECT::GetAlpha( double *pdAlpha) {
  return c_complexShape.vGetAlpha( pdAlpha);
}

//==============================================================================
STDMETHODIMP VOBJECT::SetAlpha( double dAlpha, long iLogID ) {
  return c_complexShape.vSetAlpha( dAlpha, iLogID );
}

//==============================================================================
STDMETHODIMP VOBJECT::GetFillFlag( long * piFillFlag ) {
  return c_complexShape.vGetFillFlag( piFillFlag );
}

//==============================================================================
STDMETHODIMP VOBJECT::SetFillFlag( long iFillFlag, long iLogID ) {
  return c_complexShape.vSetFillFlag( iFillFlag, iLogID );
}

//==============================================================================
STDMETHODIMP VOBJECT::GetShowFlag( long * piShowFlag ) {
  return c_complexShape.vGetShowFlag( piShowFlag );
}

//==============================================================================
STDMETHODIMP VOBJECT::SetShowFlag( long iShowFlag, long iLogID) {
  return c_complexShape.vSetShowFlag( iShowFlag, iLogID);
}

//==============================================================================
STDMETHODIMP VOBJECT::GetGroupID( long * piGroupID ) {
  return c_complexShape.vGetGroupID( piGroupID );
}

//==============================================================================
STDMETHODIMP VOBJECT::SetGroupID( long iGroupID) {
  return c_complexShape.vSetGroupID( iGroupID);
}

//==============================================================================
STDMETHODIMP VOBJECT::GetClippedCount( long *piClippedCount) {
  return c_complexShape.vGetClippedCount( piClippedCount);
}

//==============================================================================
STDMETHODIMP VOBJECT::Move( VARIANT vXY, long iLogID ) {
  return c_complexShape.vMove( vXY, iLogID );
}

//==============================================================================
STDMETHODIMP VOBJECT::Scale( double dScale, long iLogID ) {
	vScale( dScale, iLogID );
	return c_complexShape.vScale( dScale, 0 );
}

//==============================================================================
STDMETHODIMP VOBJECT::Rotate( double dAngle, long iLogID ) {
  return c_complexShape.vRotate( dAngle, iLogID );
}

//==============================================================================
STDMETHODIMP VOBJECT::Show( long iLogID ) {
	vShow(iLogID);
	return c_complexShape.vShow( 0 );
}

//==============================================================================
STDMETHODIMP VOBJECT::Hide( long iLogID ) {
	vHide( iLogID );
	return c_complexShape.vHide( 0 );
}






//==============================================================================
//                   Motion-specific interfaces
//==============================================================================

STDMETHODIMP CVMotion::GetExact(double *pVal)
{
	return c_complexShape->GetExact(*pVal);
}
STDMETHODIMP CVMotion::SetExact(double newVal, long iLogID)
{
	return c_compleObj->SetExact(newVal,iLogID);
}


STDMETHODIMP CMVotion::IsCircle(double *pVal)
{
	if(circle)	*pVal=1.;
	else		*pVal=0.;
	return S_OK;
}
STDMETHODIMP CVMotion::UseCircle(long iLogID)
{
	if(!circle){ 
		circle = TRUE:
		resampleFlag=TRUE;
		m_RequestUpdate(iLogID);
	}
	return S_OK;
}
STDMETHODIMP CMVotion::IsSquare(double *pVal)
{
	if(circle)	*pVal=0.;
	else		*pVal=1.;
	return S_OK;
}
STDMETHODIMP CVMotion::UseSquare(long iLogID)
{
	if(circle){ 
		circle = FALSE:
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
	lifetime = (int)newVal;
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


VELOCITY!!!!


//==============================================================================
//                   The Work
//==============================================================================

void
CVMotion::m_sampleVertex(int i, double *pos, double *vel)
{
	// Sample Position uniformly in region
	if(circle){
		double a,r;
		a = rand()*2*PI;
		r = sqrt(rand());
		pos[0]=r*cos(a);
		pos[1]=r*sin(a);
	} else{
		pos[0]=2*rand()-1;
		pos[1]=2*rand()-1;
	}
	// Sample Velocity only if not a "coherent" point
	if( i < nVertices*coherence/100. ){
		vel[0]=velX;
		vel[1]=velY;
	} else{
		double speed;
		speed = sqrt(velX*velX+velY*velY);
		a = rand()*2*PI;
		vel[0]=speed*cos(a);
		vel[1]=speed*sin(a);
	}
}
}

void
CVMotion::m_sampleVertices()
{
	int dim, dimlen[2];
	int i;
	double *p,*v;

	// release old data
	FreeDoubleArray(vertices);
	FreeDoubleArray(vertexVel);
	if(vertexTimes) delete vertexTimes;
	// get new array
	dim = 2;
	dimlen[0]=2; dimlen[1]=nVertices;
	vertices = CreateDoubleArray(dim, dimlen);
	vertexVel = CreateDoubleArray(dim, dimlen);
	vertexTimes = new double[nVertices];
	
	// Sample vertices
	for (p=vertices, v=vertexVel, i=0; i<nVertices; p+=2, v+=2, ++i){
		m_sampleVertex(i,p,v);
	}

	// Sample Times between 0 and lifetime
	for(i=0; i<nVertices; i++){
		vertexTimes[i]=rand()*lifetime;
	}
	
	// Get Frame Time
	_ftime( &lastTime );
}


void
CVMotion::m_updateVertices()
{
	int i;
	BOOL iresample;
	struct _timeb thisTime;
	double dt;
	
	_ftime( &thisTime );
	dt = (thisTime.time-lastTime.time) + thisTime.millitm/1000.0 - lastTime.millitm/1000.0;
	
	// Update positions based on speed
	for (p=vertices, v=vertexVel, i=0; i<nVertices; p+=2, v+=2, ++i){
		
		iresample=FALSE;
		
		vertexTimes[i] += dt;
		
		if(vertexTimes[i]+dt>lifetime) iresample=TRUE;
		else{
			p[0] += v[0]*dt/m_dScale;
			p[1] += v[1]*dt/m_dScale;
			if(circle){
				if( sqrt(p[0]*p[0]+p[1]*p[1])>1 ) iresample=TRUE;
			} else{
				if( abs(p[0])>1 || abs(p[1])>1 ) iresample=TRUE;
			}
		}
		
		if(iresample){
			m_sampleVertex(i,p,v);
			vertexTimes[i]=0.;
		}
	}
}


void
CVMotion::Draw()
{
	// Note that CMotion is not REALLY an ojbect, it only
	// contains one.  But it still needs to be called each
	// frame in order to update the vertices.  So Draw doesn't
	// call c_complexOject->Draw.  That will happen on that 
	// object's turn (which is guaranteed to be later, since
	// the CMotion object created the CComplexObject.

	// Want to set g_blnAutoUpdate on Show()/Hide().
	// The problem is that these belong to CObject.
	// Not a big deal, though, since calls to
	// Show/Hide will trigger an update, which
	// will land you here
	if(m_IsVisible){
		// Turn on AutoUpdate
		if(!g_blnAutoUpdate) g_blnAutoUpdate=TRUE;
		// Sample or Update Points
		if(!vertices || resampleFlag) m_sampleVertices();
		else  m_updateVertices();

		// Send them to ComplexObject
		c_complexShape->SetVertices(vertices);

	} else{
		if(g_blnAutoUpdate) g_blnAutoUpdate=FALSE;
	}
	return;
}