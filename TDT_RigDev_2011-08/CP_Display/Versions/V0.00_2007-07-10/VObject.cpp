#include <windows.h>
#include "VObject.h"
#include "GL_Engine.h"
#include "Util\SafeArrayLib.h"


//==============================================================================
CVObject::CVObject() { 

  m_dX = 0;
  m_dY = 0;
  m_dZ = 0;
  m_dScale = 1; 
  m_dAngle = 0;
  m_fRGB[0]=1;
  m_fRGB[1]=1;
  m_fRGB[2]=1;
  m_fAlpha = 1;
  m_iIsFilled = 1;
  m_IsVisible = 0; 
  m_iGroupID = 0;  
  m_nClipped = 0; // will be calculated in the drawing routine

  g_ptObjectList.AddPointer(this);  // Add to the Object List
}

//==============================================================================
CVObject::~CVObject() { 
  
  g_ptObjectList.RemovePointer(this); // remove from the object list
  m_RequestUpdate(0); // we do it here, not in the derived object
}

//==============================================================================
HRESULT CVObject::vGetXY( SAFEARRAY ** ppsaXY){
  SAFEARRAY *psaMtx;
  double * pdData;

  * ppsaXY = NULL;
  if( g_MakeSafeArray( 2, &psaMtx, &pdData ) ){
    return g_ErrorToHresult(1);
  }
  pdData[0] = m_dX;
  pdData[1] = m_dY;
  SafeArrayUnaccessData( psaMtx );
  * ppsaXY = psaMtx;
  
  return S_OK;
}

//==============================================================================
HRESULT CVObject::vSetXY( SAFEARRAY * psaXY, long iLogID){
  double * pdData;
 
  // We expect 2-long array of doubles
  if( g_CheckSafeArray( 2, psaXY, &pdData )) {
    return g_ErrorToHresult( 1 );
  }
  m_dX = pdData[0];
  m_dY = pdData[1];

  SafeArrayUnaccessData( psaXY );
  m_RequestUpdate(iLogID);
  return S_OK;
}

//==============================================================================
HRESULT CVObject::vGetZ( double *pdZ){
  *pdZ = m_dZ;
  return S_OK;
}

//==============================================================================
HRESULT CVObject::vSetZ( double dZ, long iLogID){
  m_dZ = dZ;
  m_RequestUpdate(iLogID);
  return S_OK;
}

//==============================================================================
HRESULT CVObject::vGetScale(double * pdScale){
  *pdScale = m_dScale;
  return S_OK;
}

//==============================================================================
HRESULT CVObject::vSetScale(double dScale, long iLogID){
  m_dScale = dScale;
  m_RequestUpdate(iLogID);
  return S_OK;
}

//==============================================================================
HRESULT CVObject::vGetAngle(double * pdAngle){
  *pdAngle = m_dAngle;
  return S_OK;
}

//==============================================================================
HRESULT CVObject::vSetAngle(double dAngle, long iLogID){
  m_dAngle = dAngle;
  m_RequestUpdate(iLogID);
  return S_OK;
}
  
//==============================================================================
HRESULT CVObject::vGetColor( SAFEARRAY ** ppsaRGB){
  SAFEARRAY *psaMtx;
  double * pdData;

  * ppsaRGB = NULL;
  if( g_MakeSafeArray( 3, &psaMtx, &pdData ) ){
    return g_ErrorToHresult(1);
  }
  pdData[0] = m_fRGB[0];
  pdData[1] = m_fRGB[1];
  pdData[2] = m_fRGB[2];

  SafeArrayUnaccessData( psaMtx );
  * ppsaRGB = psaMtx;
  
  return S_OK;
}

//==============================================================================
HRESULT CVObject::vSetColor( SAFEARRAY * psaColors, long iLogID ){
  double * pdData;
 
  // We expect 3-long array of doubles
  if( g_CheckSafeArray( 3, psaColors, &pdData )) {
    return g_ErrorToHresult( 1 );
  }
  m_fRGB[0] = (float)pdData[0];
  m_fRGB[1] = (float)pdData[1];
  m_fRGB[2] = (float)pdData[2];

  SafeArrayUnaccessData( psaColors );
  m_RequestUpdate(iLogID);
  return S_OK;
}

//==============================================================================
HRESULT CVObject::vGetAlpha( double *pdAlpha){
  *pdAlpha = (float)m_fAlpha;
  return S_OK;
}

//==============================================================================
HRESULT CVObject::vSetAlpha( double dAlpha, long iLogID ){
  m_fAlpha = (float)dAlpha;
  m_RequestUpdate(iLogID);
  return S_OK;
}

//==============================================================================
HRESULT CVObject::vGetFillFlag( long * piFillFlag ){
  * piFillFlag = m_iIsFilled;
  return S_OK;
}

//==============================================================================
HRESULT CVObject::vSetFillFlag( long iFillFlag, long iLogID ){
  m_iIsFilled = iFillFlag;
  m_RequestUpdate(iLogID);
  return S_OK;
}

//==============================================================================
HRESULT CVObject::vGetShowFlag( long * piShowFlag ){
  *piShowFlag = m_IsVisible;
  return S_OK;
}

//==============================================================================
HRESULT CVObject::vSetShowFlag( long iShowFlag, long iLogID){
  m_IsVisible = iShowFlag;
  g_RequestUpdate(iLogID);
  return S_OK;
}

//==============================================================================
  HRESULT CVObject::vGetGroupID( long * piGroupID ){

  *piGroupID = m_iGroupID;
  return S_OK;
}

//==============================================================================
HRESULT CVObject::vSetGroupID( long iGroupID ){
  
  m_iGroupID = iGroupID;
  return S_OK;
}

//==============================================================================
HRESULT CVObject::vGetClippedCount( long *piClippedCount){
  *piClippedCount = m_nClipped; // calculated on draw
  return S_OK;
}

//==============================================================================
HRESULT CVObject::vMove( SAFEARRAY * psaXY, long iLogID){
  double * pdData;
 
  // We expect 2-long array of doubles
  if( g_CheckSafeArray( 2, psaXY, &pdData )) {
    return g_ErrorToHresult( 1 );
  }
  Move(pdData[0], pdData[1]);
  SafeArrayUnaccessData( psaXY );
  m_RequestUpdate(iLogID);
  return S_OK;
}

//==============================================================================
HRESULT CVObject::vScale( double dScale, long iLogID ){
  Scale( dScale);
  m_RequestUpdate(iLogID);
  return S_OK;
}

//==============================================================================
HRESULT CVObject::vRotate( double dAngle, long iLogID ){
  Rotate(dAngle);
  m_RequestUpdate(iLogID);
  return S_OK;
}

//==============================================================================
HRESULT CVObject::vShow( long iLogID ){
  Show();
  g_RequestUpdate(iLogID);
  return S_OK;
}

//==============================================================================
HRESULT CVObject::vHide( long iLogID ){
  Hide();
  g_RequestUpdate(iLogID);
  return S_OK;
}

//==============================================================================
void CVObject::Move( double dDX, double dDY ){
  m_dX += dDX;
  m_dY += dDY;
}

//==============================================================================
void CVObject::Scale( double dScale ){
  m_dScale *= dScale;
}

//==============================================================================
void CVObject::Rotate( double dAngle ){
  m_dAngle += dAngle;
}

//==============================================================================
void CVObject::Hide( ){
  m_IsVisible = 0;
}

//==============================================================================
void CVObject::Show( ){
  m_IsVisible = 1;
}
//==============================================================================
void CVObject::Move( double dDX, double dDY, int iGroupID ){
  if(iGroupID != m_iGroupID) return;
  m_dX += dDX;
  m_dY += dDY;
}

//==============================================================================
void CVObject::Scale( double dScale, int iGroupID ){
  if(iGroupID != m_iGroupID) return;
  m_dScale *= dScale;
}

//==============================================================================
void CVObject::Rotate( double dAngle, int iGroupID ){
  if(iGroupID != m_iGroupID) return;
  m_dAngle += dAngle;
}

//==============================================================================
void CVObject::Hide( int iGroupID ){
  if(iGroupID != m_iGroupID) return;
  m_IsVisible = 0;
}

//==============================================================================
void CVObject::Show( int iGroupID ){
  if(iGroupID != m_iGroupID) return;
  m_IsVisible = 1;
}

//==============================================================================
void CVObject::m_RequestUpdate( long iLogID ){
  if(m_IsVisible) g_RequestUpdate(iLogID);
}

