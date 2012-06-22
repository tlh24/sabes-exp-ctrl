#include <windows.h>
#include "VObject.h"
#include "GL_Engine.h"
#include "Util\VariantLib.h"


//==============================================================================
CVObject::CVObject() { 

  m_dX = 0;
  m_dY = 0;
  m_dZ = 0;
  m_dScale[0] = 1; 
  m_dScale[1] = 1; 
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
HRESULT CVObject::vGetXY( VARIANT * pvXY){
  double * pdData;

  if( g_MakeVariantArray( 2, pvXY, &pdData ) ){
    return g_ErrorToHresult(1);
  }
  pdData[0] = m_dX;
  pdData[1] = m_dY;
  SafeArrayUnaccessData( pvXY->parray );

  return S_OK;
}

//==============================================================================
HRESULT CVObject::vSetXY( VARIANT vXY, long iLogID){
  double * pdData;
 
  // We expect 2-long array of doubles
  if( g_CheckVariantArray( 2, vXY, &pdData )) {
    return g_ErrorToHresult( 1 );
  }
  m_dX = pdData[0];
  m_dY = pdData[1];

  SafeArrayUnaccessData( vXY.parray );
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
HRESULT CVObject::vGetScale(VARIANT * pvScale){
  double * pdData;

  if( g_MakeVariantArray( 2, pvScale, &pdData ) ){
    return g_ErrorToHresult(1);
  }
  pdData[0] = m_dScale[0];
  pdData[1] = m_dScale[1];
  SafeArrayUnaccessData( pvScale->parray );

  return S_OK;
}

//==============================================================================
HRESULT CVObject::vSetScale(double dScale, long iLogID){
  m_dScale[0] = dScale;
  m_dScale[1] = dScale;
  m_RequestUpdate(iLogID);
  
  return S_OK;
}

//==============================================================================
HRESULT CVObject::vSetScaleV(VARIANT vScale, long iLogID){
  double * pdData;
  int dim;
 
  // We expect 1- or 2-long array of doubles
  if( g_CheckVariantArray( &dim, vScale, &pdData )) {
	  return g_ErrorToHresult( 1 );
  }
  if(dim==1){
	  m_dScale[0] = m_dScale[1] = pdData[0];
  }
  else if(dim==2){
	  m_dScale[0] = pdData[0];
	  m_dScale[1] = pdData[1];
  } 
  else{
	  return g_ErrorToHresult( 1 );
  }
  
  SafeArrayUnaccessData( vScale.parray );
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
HRESULT CVObject::vGetColor( VARIANT * pvRGB){

  double * pdData;

  if( g_MakeVariantArray( 3, pvRGB, &pdData ) ){
    return g_ErrorToHresult(1);
  }
  pdData[0] = m_fRGB[0];
  pdData[1] = m_fRGB[1];
  pdData[2] = m_fRGB[2];

  SafeArrayUnaccessData( pvRGB->parray );

  return S_OK;
}

//==============================================================================
HRESULT CVObject::vSetColor( VARIANT vRGB, long iLogID ){
  double * pdData;
 
  // We expect 3-long array of doubles
  if( g_CheckVariantArray( 3, vRGB, &pdData )) {
    return g_ErrorToHresult( 1 );
  }
  m_fRGB[0] = (float)pdData[0];
  m_fRGB[1] = (float)pdData[1];
  m_fRGB[2] = (float)pdData[2];

  SafeArrayUnaccessData( vRGB.parray );
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
HRESULT CVObject::vMove( VARIANT vXY, long iLogID){
  double * pdData;
 
  // We expect 2-long array of doubles
  if( g_CheckVariantArray( 2, vXY, &pdData )) {
    return g_ErrorToHresult( 1 );
  }
  Move(pdData[0], pdData[1]);
  SafeArrayUnaccessData( vXY.parray );
  m_RequestUpdate(iLogID);

  return S_OK;
}

//==============================================================================
HRESULT CVObject::vScale( VARIANT vScale, long iLogID ){
  double * pdData, dScale[2];
  int dim;
 
  // We expect 1- or 2-long array of doubles
  if( g_CheckVariantArray( &dim, vScale, &pdData )) {
	  return g_ErrorToHresult( 1 );
  }
  if(dim==1){
	  dScale[0] = dScale[1] = pdData[0];
  }
  else if(dim==2){
	  dScale[0] = pdData[0];
	  dScale[1] = pdData[1];
  } 
  else{
	  return g_ErrorToHresult( 1 );
  }
  
  Scale( dScale[0],dScale[1]);
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
void CVObject::Scale( double dScaleX, double dScaleY ){
  m_dScale[0] *= dScaleX;
  m_dScale[1] *= dScaleY;
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
void CVObject::Scale( double dScaleX, double dScaleY, int iGroupID ){
  if(iGroupID != m_iGroupID) return;
  m_dScale[0] *= dScaleX;
  m_dScale[1] *= dScaleY;
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

