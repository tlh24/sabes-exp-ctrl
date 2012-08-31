// Abstract Base Class for graph object interface classes

#ifndef __VOBJECT_H_
#define __VOBJECT_H_

#define N_COLORS 3

class CVObject {

public:
  CVObject();
  ~CVObject();

  HRESULT vGetXY( VARIANT * pvXY);
  HRESULT vSetXY( VARIANT vXY, long iLogID);
  HRESULT vGetZ( double *pfZ);
  HRESULT vSetZ( double fZ, long iLogID);
  HRESULT vGetScale(VARIANT * pvScale);
  HRESULT vSetScale(double dScale, long iLogID);
  HRESULT vSetScaleV(VARIANT vScale, long iLogID);
  HRESULT vGetAngle(double * pfAngle);
  HRESULT vSetAngle(double fAngle, long iLogID);
  HRESULT vGetColor( VARIANT * pvRGB);
  HRESULT vSetColor( VARIANT pvColors, long iLogID );
  HRESULT vGetAlpha( double *pfAlpha);
  HRESULT vSetAlpha( double fAlpha, long iLogID );
  HRESULT vGetFillFlag( long * piFillFlag );
  HRESULT vSetFillFlag( long iFillFlag, long iLogID );
  HRESULT vGetShowFlag( long * piShowFlag );
  HRESULT vSetShowFlag( long iShowFlag, long iLogID);
  HRESULT vGetGroupID(long * piGroupID );
  HRESULT vSetGroupID(long iGroupID );
  HRESULT vGetClippedCount( long *piClippedCount);
  HRESULT vMove( VARIANT vXY, long iLogID);
  HRESULT vScale( VARIANT vScale, long iLogID );
  HRESULT vRotate( double fAngle, long iLogID );
  HRESULT vShow(long iLogID );
  HRESULT vHide(long iLogID );


  void Move( double fDX, double fDY );
  void Scale( double fScaleX, double fScaleY );
  void Rotate( double fAngle );
  void Hide();
  void Show();
  void Move( double fDX, double fDY, int iGroupID );
  void Scale( double fScaleX, double fScaleY, int iGroupID );
  void Rotate( double fAngle, int iGroupID );
  void Hide( int iGroupID);
  void Show( int iGroupID);
  
  virtual void Draw() = 0;  // Object-specific implementation

protected:
  double m_dX, m_dY, m_dZ;
  double m_dScale[2]; 
  double m_dAngle;
  float m_fRGB[N_COLORS];
  float m_fAlpha;
  int   m_iGroupID;
  int   m_iIsFilled;
  int   m_IsVisible;
  int   m_nClipped;

  void m_RequestUpdate( long iLogID );

};

#endif //__VOBJECT_H_
