#include "ATL_Defs.h"            // ATL, COM and Windows definitions
#include "resource.h"            // Resource IDs for registry
#include "CP_Display.h"          // this file is generated by MIDL compiler
#include "VDisk.h"               // Uses ATL and IDs

#include <math.h>
#include <gl\gl.h>               // Header File For The OpenGL32 Library
#include <gl\glu.h>              // Header File For The GLu32 Library

#include "GL_Engine.h"
#include "Util\CP_printf.h"
#include "Util\VariantLib.h"


//==============================================================================
CVDisk::CVDisk(){

  m_dScale[0]=m_dScale[1]=10;  // Set default radius  = 10
  m_nVertices = 40;
  m_afScrnVtxX = NULL;
  m_afScrnVtxY = NULL;
  m_NewVertices();
}

//==============================================================================
CVDisk::~CVDisk(){
  if( m_afScrnVtxX ) delete m_afScrnVtxX;
  if( m_afScrnVtxY ) delete m_afScrnVtxY;
  // m_RequestUpdate(0) will be called in the destructor of the base object
}

#define VOBJECT CVDisk  // this define is needed for <VObjectMethodsImpl.h>
#include "VObjectMethodsImpl.h"

//==============================================================================
//                   disk-specific methods
//==============================================================================
STDMETHODIMP CVDisk::GetRadius( VARIANT *pvRadius ){
  return vGetScale(pvRadius);
}

//==============================================================================
STDMETHODIMP CVDisk::SetRadius( double dRadius, long iLogID ){
  m_dScale[0]=m_dScale[1]=dRadius;
  m_RequestUpdate(iLogID);
  return S_OK;
}

//==============================================================================
STDMETHODIMP CVDisk::GetN_Vertices( long * pnVertices){
  * pnVertices = m_nVertices;
  return S_OK;
}

//==============================================================================
STDMETHODIMP CVDisk::SetN_Vertices( long nVertices, long iLogID ){
  m_nVertices = nVertices;
  m_NewVertices();
  m_RequestUpdate(iLogID);
  return S_OK;
}

//==============================================================================
void CVDisk::Draw() {
  int iVtx;

  m_nClipped = 0;
  if(!m_IsVisible) return;
  
  m_CalcScrnVertices();

  glColor4f( m_fRGB[0], m_fRGB[1], m_fRGB[2], m_fAlpha);

  if(m_iIsFilled) 
    glPolygonMode(GL_FRONT, GL_FILL);
  else {
    glPolygonMode(GL_FRONT, GL_LINE);
    // GL_LINE_WIDTH??
  }

  glBegin(GL_POLYGON);
  for( iVtx = 0; iVtx < m_nVertices; iVtx++){
    m_nClipped += IS_OFF_WINDOW(m_afScrnVtxX[iVtx],m_afScrnVtxY[iVtx]);
    glVertex3f( m_afScrnVtxX[iVtx], m_afScrnVtxY[iVtx], (float) m_dZ);
  }
  glEnd();  
}

//==============================================================================
void CVDisk::m_CalcScrnVertices(){

  int iVtx;
  double dAngleStep, dAngle0;
  double dX, dY;
  float * p_fVtxX, * p_fVtxY;

  dAngleStep = TWO_PI/m_nVertices;
  dAngle0 = m_dAngle * DEGS_TO_RADS;

  // circle is always of radius 1
  // disk radius is represented by scale
  p_fVtxX = m_afScrnVtxX;
  p_fVtxY = m_afScrnVtxY;

  for( iVtx = 0; iVtx < m_nVertices; iVtx++){
    dX = cos(dAngleStep * iVtx + dAngle0) * m_dScale[0] + m_dX;
    dY = sin(dAngleStep * iVtx + dAngle0) * m_dScale[1] + m_dY;
    g_TransformCoordinatesF( dX, dY, p_fVtxX, p_fVtxY );
    p_fVtxX++;
    p_fVtxY++;
  }
}

//==============================================================================
void CVDisk::m_NewVertices(){

  if( m_afScrnVtxX ) delete m_afScrnVtxX;
  if( m_afScrnVtxY ) delete m_afScrnVtxY;

  m_afScrnVtxX = new float[m_nVertices];
  m_afScrnVtxY = new float[m_nVertices];
}






