#ifndef __VTEXT_H_
#define __VTEXT_H_

#include "Vobject.h"
#include "comdef.h"   // _bstr_t
#include "GL_Font.h"

class CVText : 
  public IDispatchImpl<IVText, &IID_IVText, &LIBID_CP_DISPLAYLib>, 
  public CComObjectRoot,
  public CComCoClass<CVText,&CLSID_VText>,
  public CVObject

{
public:
BEGIN_COM_MAP(CVText)
  COM_INTERFACE_ENTRY(IDispatch)
  COM_INTERFACE_ENTRY(IVText)
END_COM_MAP()

DECLARE_NOT_AGGREGATABLE(CVText) 
DECLARE_REGISTRY_RESOURCEID(IDR_VText)

  CVText();
  ~CVText();

// common methods
#include "VObjectMethodsDecl.h"
  
// text-specific methods
  STDMETHOD(GetText)(BSTR * pbstText);
  STDMETHOD(SetText)(BSTR bstText, long iLogID );
  STDMETHOD(GetFontName)(BSTR *pbstFont);
  STDMETHOD(SetFontName)(BSTR bstFont, long iLogID );
  STDMETHOD(GetFontWeight)(long  * iWeight);
  STDMETHOD(SetFontWeight)(long  iWeight, long iLogID );
  STDMETHOD(GetFontUnderlineFlag)(long *piUnderlineFlag);
  STDMETHOD(SetFontUnderlineFlag)(long iUnderlineFlag, long iLogID );
  STDMETHOD(GetFontItalicFlag)(long *piItalicFlag);
  STDMETHOD(SetFontItalicFlag)(long iItalicFlag, long iLogID );
  
  void Draw();

private:

  CGL_Font m_tGL_Font;
  _bstr_t m_bscText;
  HRESULT vSetFillFlag( long iFillFlag, long iLogID );
/*  
  float Length;       // Pre-Scaling String Width
  float Height;       // Pre-Scaling String Height
  float ScaleX;       // Scaling of Width 
  float ScaleY;       // Scaling of Height 
  float Angle;        // Rotation of Text (about center)
  float Color[3];       // Color
  float Alpha;
  int   Fill;         // Fill
  char  textString[200];
  int   fontWeight;     // Font Weight: 100-900 in 100 steps??? (500 is normal)
  int   fontItalic;     // BOOL Italic
  int   fontUnderline;    // BOOL Underline
  char  fontName[30];     // Font Name

  int listBase;         // 1st of the character Call List IDs
  GLYPHMETRICSFLOAT fontGMF[256]; // Storage For Information About Our Outline Font Characters
  void BuildFont(void);
  void KillFont(void);
  void calcTextBox(void);
*/  
};

#endif //__VTEXT_H_
