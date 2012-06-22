// VisText.cpp : Implementation of CVisServerApp and DLL registration.

#include "stdafx.h"
#include "math.h"
#include "VisServer.h"
#include "VisWindow.h"
#include "VisWindowManagement.h"
#include "VisCalibrate.h"
#include "ComUtils.h"
#include "VisText.h"
#include "VisWindowActionLog.h"


/////////////////////////////////////////////////////////////////////////////
//

STDMETHODIMP CVisText::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IVisText,
	};

	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CONSTR/DESTR
CVisText::CVisText()
{
	// Default Color/Draw Values
	Color[0]=Color[1]=Color[2]=1;
#if INDEX_MODE
	ColorIndex=VisWindow->ColorRGB2I(Color);
#endif
	Alpha=1;

	// Clipped
	Clipped = VISWIN_IS_CLIPPED(X,Y);

	// Transform
	ScaleX=ScaleY= 1;
	Angle = 0;


	// FONT & STRING SETUP
	
	Fill=TRUE;
	fontUnderline=FALSE;
	fontItalic=FALSE;
	fontWeight=500;
	strcpy(fontName,VISTEXT_DEFAULT_FONT);
	listBase=-1;
	BuildFont();

	textString[0]=NULL;
	calcTextBox();
}

CVisText::~CVisText()
{
	Show=0;
	KillFont();
	if(VisWindow && Show){ 
		VisWindow->requestUpdate();
		if(VisWindow->logmode) VisWindow->logAction(tag,ACTION_DELETE,(double *)NULL,0);
	}
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// PROPERTIES AND METHODS


/////////// GETS

STDMETHODIMP CVisText::get_clipped(double *pVal) {*pVal=Clipped; return S_OK; }
STDMETHODIMP CVisText::get_alpha(double *pVal) { *pVal=Alpha; return S_OK; }
STDMETHODIMP CVisText::get_angle(double *pVal){ *pVal=Angle; return S_OK; }
STDMETHODIMP CVisText::get_fill(double *pVal){ *pVal=Fill; return S_OK; }
STDMETHODIMP CVisText::get_fontWeight(double *pVal){ *pVal=fontWeight; return S_OK; }
STDMETHODIMP CVisText::get_fontUnderline(double *pVal){ *pVal=fontUnderline; return S_OK; }
STDMETHODIMP CVisText::get_fontItalic(double *pVal){ *pVal=fontItalic; return S_OK; }

STDMETHODIMP CVisText::get_text(BSTR *pVal)
{
	wchar_t wString[200];

	// textString is ASCII, but COM wants a BSTR (i.e. WCS or unicode string)
	mbstowcs( wString, textString, strlen(textString)+1 );
	*pVal=SysAllocString(wString);
	return S_OK;
}

STDMETHODIMP CVisText::get_color(VARIANT *pVal)
{
	double tmp[3] = {Color[0], Color[1], Color[2]};
	VariantFromArray(3,tmp,pVal);
	return S_OK;
}

STDMETHODIMP CVisText::get_size(VARIANT *pVal)
{
	double tmp[2] = {Length, Height};
	VariantFromArray(2,tmp,pVal);
	return S_OK;
}

STDMETHODIMP CVisText::get_scale(VARIANT *pVal) 
{
	double tmp[2] = {ScaleX, ScaleY};
	VariantFromArray(2,tmp,pVal);
	return S_OK;
}

STDMETHODIMP CVisText::get_fontName(BSTR *pVal)
{
	wchar_t wString[200];

	// textString is ASCII, but COM wants a BSTR (i.e. WCS or unicode string)
	mbstowcs( wString, fontName, strlen(fontName)+1 );
	*pVal=SysAllocString(wString);
	return S_OK;
}

////////// PUTS

STDMETHODIMP CVisText::put_alpha(double newVal)
{
	Alpha = (float)newVal;
	if(VisWindow && Show){ 
		VisWindow->requestUpdate();
		if(VisWindow->logmode) VisWindow->logAction(tag,ACTION_ALPHA,&newVal,1);
	}
	return S_OK;
}
STDMETHODIMP CVisText::put_angle(double newVal)
{
	Angle = (float)newVal;
	if(VisWindow && Show){ 
		VisWindow->requestUpdate();
		if(VisWindow->logmode) VisWindow->logAction(tag,ACTION_ANGLE,&newVal,1);
	}
	return S_OK;
}

STDMETHODIMP CVisText::put_color(VARIANT newVal)
{
	int alen;
	double *aptr;
	if( VariantToArray(&alen,&aptr,&newVal) ) return E_INVALIDARG;
	if( alen<3 ) { delete aptr; return E_INVALIDARG; }
	Color[0]=(float)aptr[0];
	Color[1]=(float)aptr[1];
	Color[2]=(float)aptr[2];
	if( alen==4) Alpha=(float)aptr[3];

#if INDEX_MODE
	ColorIndex=VisWindow->ColorRGB2I(Color);
#endif

	if(VisWindow && Show){ 
		VisWindow->requestUpdate();
		if(VisWindow->logmode) VisWindow->logAction(tag,ACTION_COLOR,aptr,alen);
	}
	delete aptr;
	return S_OK;
}
STDMETHODIMP CVisText::put_scale(VARIANT newVal)
{
	int alen;
	double *aptr;
	if( VariantToArray(&alen,&aptr,&newVal) ) return E_INVALIDARG;
	if( alen<2 ) { delete aptr; return E_INVALIDARG; }
	ScaleX=(float)aptr[0];
	ScaleY=(float)aptr[1];
	
	if(VisWindow && Show){ 
		VisWindow->requestUpdate();
		if(VisWindow->logmode) VisWindow->logAction(tag,ACTION_SCALE,aptr,alen);
	}

	delete aptr;
	return S_OK;
}

STDMETHODIMP CVisText::put_text(BSTR newVal)
{
	// testString is ASCII, but COM sends BSTR (i.e. WCS or unicode string)
	int len = wcslen(newVal)+1;
	wcstombs( textString, newVal, len );
	calcTextBox();

	// Ask VisWindow to Update
	if(VisWindow && Show){ 
		VisWindow->requestUpdate();
		if(VisWindow->logmode) VisWindow->logAction(tag,ACTION_TEXT,&len,1);
	}
	return S_OK;
}





////// The following PUTS require a rebuilding of the font

STDMETHODIMP CVisText::put_fill(double newVal)
{
	int redo=0;
	if( fabs(newVal)<.01 && Fill ){ Fill=FALSE; redo=1; }
	else if( fabs(newVal)>.01 && !Fill ){ Fill=TRUE; redo=1;}
	if(redo){
		KillFont();	BuildFont();
	}

	if(VisWindow && Show){ 
		VisWindow->requestUpdate();
		if(VisWindow->logmode) VisWindow->logAction(tag,ACTION_FILL,&newVal,1);
	}
	return S_OK;
}

STDMETHODIMP CVisText::put_fontUnderline(double newVal)
{
	int redo=0;
	if( fabs(newVal)<.01 && fontUnderline ){ fontUnderline=FALSE; redo=1; }
	else if( fabs(newVal)>.01 && !fontUnderline ){ fontUnderline=TRUE; redo=1;}
	if(redo){
		KillFont();	BuildFont();
		calcTextBox();
	}

	if(VisWindow && Show){ 
		VisWindow->requestUpdate();
		if(VisWindow->logmode) VisWindow->logAction(tag,ACTION_UNDERLINE,&newVal,1);
	}
	return S_OK;
}

STDMETHODIMP CVisText::put_fontItalic(double newVal)
{
	int redo=0;
	if( fabs(newVal)<.01 && fontItalic ){ fontItalic=FALSE; redo=1; }
	else if( fabs(newVal)>.01 && !fontItalic ){ fontItalic=TRUE; redo=1; }
	if(redo){
		KillFont();	BuildFont();
		calcTextBox();
	}

	if(VisWindow && Show){ 
		VisWindow->requestUpdate();
		if(VisWindow->logmode) VisWindow->logAction(tag,ACTION_ITALIC,&newVal,1);
	}
	return S_OK;
}

STDMETHODIMP CVisText::put_fontWeight(double newVal)
{
	if((int)newVal!=fontWeight){
		fontWeight=(int)(floor(newVal/100)*100.);  // Weight is in set 100:100:900
		if( fontWeight<100 && fontWeight!=0)	fontWeight=100;
		if( fontWeight>900)						fontWeight=900;
	
		KillFont();	BuildFont();
		calcTextBox();
		if(VisWindow && Show){ 
			VisWindow->requestUpdate();
			if(VisWindow->logmode) VisWindow->logAction(tag,ACTION_WEIGHT,&newVal,1);
		}
	}
	return S_OK;
}

STDMETHODIMP CVisText::put_fontName(BSTR newVal)
{
	// fontName is ASCII, but COM sends BSTR (i.e. WCS or unicode string)
	wcstombs( fontName, newVal, wcslen(newVal)+1 );
	KillFont();	BuildFont();
	calcTextBox();

	// Ask VisWindow to Update
	if(VisWindow && Show){ 
		VisWindow->requestUpdate();
		if(VisWindow->logmode) VisWindow->logAction(tag,ACTION_FONT,(double *)NULL,0);
	}
	return S_OK;
}





/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// Render Font Lists
//
// Largely fron NeHe's Tutorial Lesson 14 on Outline Fonts

static GLYPHMETRICSFLOAT fontGMF[256]; 

void 
CVisText::BuildFont()								// Build Our Bitmap Font
{
	
	HFONT	font;										// Windows Font ID
	// CREATE FONT
	font = CreateFont(
		-1*20,	 						// Height Of Font (not sure what this means)
		0,								// Width Of Font
		0,								// Angle Of Escapement
		0,								// Orientation Angle
		fontWeight,						// Font Weight
		fontItalic,						// Italic
		fontUnderline,					// Underline
		FALSE,							// Strikeout
		ANSI_CHARSET,					// Character Set Identifier
		OUT_TT_PRECIS,					// Output Precision
		CLIP_DEFAULT_PRECIS,			// Clipping Precision
		ANTIALIASED_QUALITY,			// Output Quality
		FF_DONTCARE|DEFAULT_PITCH,		// Family And Pitch
		fontName);						// Font Name
	
	SelectObject(hDC, font);			// Selects The Font We Just Created

	// CREATE FONT DISPLAY LISTS
	listBase = glGenLists(256);								// Storage For 256 Characters

	int format = Fill ? WGL_FONT_POLYGONS : WGL_FONT_LINES;

	wglUseFontOutlines(	
		hDC,							// Select The Current DC
		0,								// Starting Character
		255,							// Number Of Display Lists To Build
		listBase,						// Starting Display Lists
		0.0f,							// Deviation From The True Outlines
		0.2f,							// Font Thickness In The Z Direction
		format,							// Use Polygons, Not Lines
		fontGMF);						// Address Of Buffer To Recieve Data
}

void 
CVisText::KillFont(void)									// Delete The Font
{
	glDeleteLists(listBase, 256);	// Delete All 256 Characters
}

/////////// Current Text Size
void 
CVisText::calcTextBox(void)
{
	unsigned int i;

	for (i=0,Length=Height=0;i<(strlen(textString));i++)	// Loop To Find Text Length
	{
		Length = Length+fontGMF[textString[i]].gmfCellIncX;					// Add Up Character Widths
		Height = VISWIN_MAX(Height,fontGMF[textString[i]].gmfBlackBoxY);	// Get Max Height
	}
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// Draw

void
CVisText::draw()
{
	if(Show){

		// Only get exact calibration location of center
		// and approximate the rest of the points
		float x = XPosToScreen(X,Y);
		float y = YPosToScreen(X,Y);
		
		// Only ask if center is clipped?!
		Clipped = VISWIN_IS_CLIPPED(x,y);

		// Setup Transformation
		glMatrixMode (GL_MODELVIEW);	
		glLoadIdentity();
		glTranslatef(x,y,Z);					// 4: Translate to POS
		glRotatef(Angle,0,0,1);					// 3: Rotate About Z axis
		glScalef(ScaleX,ScaleY,1);				// 2: Scale
		glTranslatef(-Length/2,-Height/2,0);	// 1: Translate to Center the Text
		
		// Set Color and Lighting Properties
#if INDEX_MODE
		glIndexi(ColorIndex);
#else
		glColor4f(Color[0],Color[1],Color[2],Alpha);
#endif
		
		//	glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
		// Indicate start of glyph display lists 
		glListBase (listBase); 
		// Now draw the characters in a string 
		glCallLists (strlen(textString), GL_UNSIGNED_BYTE, textString); 
		//	glPopAttrib();										// Pops The Display List Bits

	}
}




////////////////////////////////////////////////////////////////

// STDMETHODIMP CVisText::put_z(double newVal)
// {
// 	Z = newVal;
// 	if(VisWindow && Show) VisWindow->requestUpdate();
// 	return S_OK;
// }
// 
// STDMETHODIMP CVisText::put_show(double newVal)
// {
// 	Show = newVal;
// 	if(VisWindow) VisWindow->requestUpdate();
// 	return S_OK;
// }
// 
// STDMETHODIMP CVisText::put_pos(VARIANT newVal)
// {
// 	// This is really ugly, but I wanted to remain Automation Compliant
// 	// so it can be called matlab, e.g.
// 	
// 	int alen;
// 	double *aptr;
// 	if( VariantToArray(&alen,&aptr,&newVal) ) return E_INVALIDARG;
// 	if( alen<2 ) { delete aptr; return E_INVALIDARG; }
// 	X=(float)aptr[0];
// 	Y=(float)aptr[1];
// 	delete aptr;
// 	
// 	if(VisWindow && Show) VisWindow->requestUpdate();
// 	return S_OK;
// }
// 
// 
// STDMETHODIMP CVisText::get_z(double *pVal) { *pVal=Z; return S_OK; }
// STDMETHODIMP CVisText::get_show(double *pVal){ *pVal=Show; return S_OK; }
// STDMETHODIMP CVisText::get_errstring(BSTR *pVal)
// {
// 	*pVal=SysAllocString(errorString);
// 	return S_OK;
// }
// 
// STDMETHODIMP CVisText::get_pos(VARIANT *pVal)
// {
// 	double tmp[2]={X,Y};
// 	VariantFromArray(2,tmp,pVal);
// 	return S_OK;
// }





