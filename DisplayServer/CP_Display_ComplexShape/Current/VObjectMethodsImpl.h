//==============================================================================
STDMETHODIMP VOBJECT::GetXY( VARIANT * pvXY) {
  return vGetXY( pvXY);
}

//==============================================================================
STDMETHODIMP VOBJECT::SetXY( VARIANT vXY, long iLogID) {
  return vSetXY( vXY, iLogID);
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
STDMETHODIMP VOBJECT::GetScale( VARIANT * pvScale) {
  return vGetScale(pvScale);
}

//==============================================================================
STDMETHODIMP VOBJECT::SetScale( double dScale, long iLogIDD) {
  return vSetScale( dScale, iLogIDD);
}

//==============================================================================
STDMETHODIMP VOBJECT::SetScaleV( VARIANT vScale, long iLogIDD) {
  return vSetScaleV( vScale, iLogIDD);
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
STDMETHODIMP VOBJECT::GetColor( VARIANT * pvRGB) {
  return vGetColor( pvRGB);
}

//==============================================================================
STDMETHODIMP VOBJECT::SetColor( VARIANT vRGB, long iLogID ) {
  return vSetColor( vRGB, iLogID );
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
STDMETHODIMP VOBJECT::Move( VARIANT vXY, long iLogID ) {
  return vMove( vXY, iLogID );
}

//==============================================================================
STDMETHODIMP VOBJECT::Scale( VARIANT vvScale, long iLogID ) {
  return vScale( vvScale, iLogID );
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





