#include "GL_Font.h"

//#define MIN(x,y)        ((x)<(y)?(x):(y))
//#define MAX(x,y)        ((x)>(y)?(x):(y))

//==============================================================================
CGL_Font::CGL_Font(){

  // Set logical font parameters
  // GL ignores font's point size set here, it is only used to derive outlines
  // from the font. GL uses its own font scale (relative to a default char?)
  c_tLogFont.lfHeight = -24;      // when negative, it means font's point size
	c_tLogFont.lfWidth = 0;
	c_tLogFont.lfEscapement = 0;
	c_tLogFont.lfOrientation = 0;
	c_tLogFont.lfWeight = FW_NORMAL; // 400
	c_tLogFont.lfItalic = 0;
	c_tLogFont.lfUnderline = 0;
	c_tLogFont.lfStrikeOut = 0;
	c_tLogFont.lfCharSet = ANSI_CHARSET;
	c_tLogFont.lfOutPrecision = OUT_DEFAULT_PRECIS;
	c_tLogFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	c_tLogFont.lfQuality = DEFAULT_QUALITY;
	c_tLogFont.lfPitchAndFamily = DEFAULT_PITCH;
	strcpy(c_tLogFont.lfFaceName,"Arial");

	c_iDisplList0 = glGenLists(N_FONT_CHARS);   // Get new range of display lists

}

//==============================================================================
CGL_Font::~CGL_Font(){

  glDeleteLists(c_iDisplList0, N_FONT_CHARS);
}

//==============================================================================
void CGL_Font::CalcFontOutlines( HDC hDC, int iFillFlag ){
	HFONT hFont;
  int iFillMode;
  
  iFillMode = iFillFlag ? WGL_FONT_POLYGONS : WGL_FONT_LINES;

  glDeleteLists(c_iDisplList0, N_FONT_CHARS);
	c_iDisplList0 = glGenLists(N_FONT_CHARS);   // Get new range of display lists

	hFont = CreateFontIndirect(&c_tLogFont);  // Windows create font
	SelectObject (hDC, hFont);                // Windows call

	wglUseFontOutlines(hDC, 
                     0,                   // first displ. list index
                     N_FONT_CHARS,        // N displ. lists, one list per char
                     c_iDisplList0,       // first GL's displ. list ID to use
                     0.0f,                // maximum deviation 0 = precise
                     0.0f,                // extrusion. makes font 3-D. 0 = flat
				             iFillMode,           // WGL_FONT_POLYGONS or WGL_FONT_LINES
                     m_atGlyphMetrics);   // save sizes here
	DeleteObject(hFont);  // done with Windows font, we'll use display lists from now on
}

//==============================================================================
void CGL_Font::CalcTextSize( char * szText, float * pfWidth, float * pfHeight ){
  int iChar, nChars;
  float  fWidth, fHeight;

  nChars = strlen(szText);
  fWidth = 0;
  fHeight = 0;

  for (iChar=0; iChar <nChars; iChar++ )  {
    fWidth += m_atGlyphMetrics[szText[iChar]].gmfCellIncX;  // add each character's width
  }
  // Height is calculated for the 'A' char - this provides consistent scaling
  fHeight = m_atGlyphMetrics['A'].gmfBlackBoxY;  // Get Max Height
  * pfWidth = fWidth;
  * pfHeight = fHeight;

}
