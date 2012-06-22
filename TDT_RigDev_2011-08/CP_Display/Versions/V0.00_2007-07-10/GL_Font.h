#ifndef __GL_FONT_H_
#define __GL_FONT_H_

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>


#define N_FONT_CHARS  128    // 128 is enough for ASCI chars

class CGL_Font {
public:

  CGL_Font();
  ~CGL_Font();
  void CalcFontOutlines( HDC hDC, int iFillMode );
  void CalcTextSize( char * szText, float * pfWidth, float * pfHeight );

  LOGFONT c_tLogFont;
  GLint c_iDisplList0;

private:
  GLYPHMETRICSFLOAT m_atGlyphMetrics[N_FONT_CHARS];  


};

#endif //__GL_FONT_H_
