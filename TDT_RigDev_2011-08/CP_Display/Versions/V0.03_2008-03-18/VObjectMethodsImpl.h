//==============================================================================
STDMETHODIMP VOBJECT::GetXY( SAFEARRAY ** ppsaXY) {
  return vGetXY( ppsaXY);
}

//==============================================================================
STDMETHODIMP VOBJECT::SetXY( SAFEARRAY * psaXY, long iLogID) {
  return vSetXY( psaXY, iLogID);
}

//==============================================================================
STDMETHODIMP VOBJECT::GetZ( double *pdZ) {
  return vGetZ( pdZ);
}

//==============================================================================
STDMETHODIMP VOBJECT::SetZ( double dZ, long iLogID) {
  return vSetZ(dZ, iLogID);
}

//==============================================================================
STDMETHODIMP VOBJECT::GetScale( double * pdScale) {
  return vGetScale(pdScale);
}

//==============================================================================
STDMETHODIMP VOBJECT::SetScale( double dScale, long iLogIDD) {
  return vSetScale( dScale, iLogIDD);
}

//==============================================================================
STDMETHODIMP VOBJECT::GetAngle( double * pdAngle) {
  return vGetAngle( pdAngle);
}

//==============================================================================
STDMETHODIMP VOBJECT::SetAngle( double dAngle, long iLogID) {
  return vSetAngle( dAngle, iLogID);
}

//==============================================================================
STDMETHODIMP VOBJECT::GetColor( SAFEARRAY ** ppsaRGB) {
  return vGetColor( ppsaRGB);
}

//==============================================================================
STDMETHODIMP VOBJECT::SetColor( SAFEARRAY * psaColors, long iLogID ) {
  return vSetColor( psaColors, iLogID );
}

//==============================================================================
STDMETHODIMP VOBJECT::GetAlpha( double *pdAlpha) {
  return vGetAlpha( pdAlpha);
}

//==============================================================================
STDMETHODIMP VOBJECT::SetAlpha( double dAlpha, long iLogID ) {
  return vSetAlpha( dAlpha, iLogID );
}

//==============================================================================
STDMETHODIMP VOBJECT::GetFillFlag( long * piFillFlag ) {
  return vGetFillFlag( piFillFlag );
}

//==============================================================================
STDMETHODIMP VOBJECT::SetFillFlag( long iFillFlag, long iLogID ) {
  return vSetFillFlag( iFillFlag, iLogID );
}

//==============================================================================
STDMETHODIMP VOBJECT::GetShowFlag( long * piShowFlag ) {
  return vGetShowFlag( piShowFlag );
}

//==============================================================================
STDMETHODIMP VOBJECT::SetShowFlag( long iShowFlag, long iLogID) {
  return vSetShowFlag( iShowFlag, iLogID);
}

//==============================================================================
STDMETHODIMP VOBJECT::GetGroupID( long * piGroupID ) {
  return vGetGroupID( piGroupID );
}

//==============================================================================
STDMETHODIMP VOBJECT::SetGroupID( long iGroupID) {
  return vSetGroupID( iGroupID);
}

//==============================================================================
STDMETHODIMP VOBJECT::GetClippedCount( long *piClippedCount) {
  return vGetClippedCount( piClippedCount);
}

//==============================================================================
STDMETHODIMP VOBJECT::Move( SAFEARRAY * psaXY, long iLogID ) {
  return vMove( psaXY, iLogID );
}

//==============================================================================
STDMETHODIMP VOBJECT::Scale( double dScale, long iLogID ) {
  return vScale( dScale, iLogID );
}

//==============================================================================
STDMETHODIMP VOBJECT::Rotate( double dAngle, long iLogID ) {
  return vRotate( dAngle, iLogID );
}

//==============================================================================
STDMETHODIMP VOBJECT::Show( long iLogID ) {
  return vShow( iLogID );
}

//==============================================================================
STDMETHODIMP VOBJECT::Hide( long iLogID ) {
  return vHide( iLogID );
}





