// VisText.h: Definition of the VisText class
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VISTEXT_H__299FB3B4_C44B_43B5_8E56_9CC9D0EC21D1__INCLUDED_)
#define AFX_VISTEXT_H__299FB3B4_C44B_43B5_8E56_9CC9D0EC21D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"       // main symbols
#include "VisObject.h"

/////////////////////////////////////////////////////////////////////////////
// VisText

class CVisText : 
	public IDispatchImpl<IVisText, &IID_IVisText, &LIBID_VISSERVERLib>, 
	public ISupportErrorInfo,
	public CComObjectRoot,
	public CComCoClass<CVisText,&CLSID_VisText>,
	public CVisObject

{
public:
	CVisText();
	~CVisText();
	BEGIN_COM_MAP(CVisText)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IVisText)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()
//DECLARE_NOT_AGGREGATABLE(CVisText) 
// Remove the comment from the line above if you don't want your object to 
// support aggregation. 

DECLARE_REGISTRY_RESOURCEID(IDR_VisText)
// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IVisText
public:

	// For Some Reason, the DCOM Interface Doesn't See the Inherited Functions, so I'll
	// Make Reimplmented Wrappers (ughhh):

	//STDMETHOD(get_show)(/*[out, retval]*/ double *pVal);
	//STDMETHOD(put_show)(/*[in]*/ double newVal);
	//STDMETHOD(get_pos)(/*[out, retval]*/ VARIANT *pVal);
	//STDMETHOD(put_pos)(/*[in]*/ VARIANT newVal);
	//STDMETHOD(get_z)(/*[out, retval]*/ double *pVal);
	//STDMETHOD(put_z)(/*[in]*/ double newVal);
	//STDMETHOD(get_errstring)(/*[out, retval]*/ BSTR *pVal);

	STDMETHOD(get_show)(/*[out, retval]*/ double *pVal)		{ return CVisObject::get_show(pVal); };
	STDMETHOD(put_show)(/*[in]*/ double newVal)				{ return CVisObject::put_show(newVal); };
	STDMETHOD(get_pos)(/*[out, retval]*/ VARIANT *pVal)		{ return CVisObject::get_pos(pVal); };
	STDMETHOD(put_pos)(/*[in]*/ VARIANT newVal)				{ return CVisObject::put_pos(newVal); };
	STDMETHOD(get_z)(/*[out, retval]*/ double *pVal)		{ return CVisObject::get_z(pVal); };
	STDMETHOD(put_z)(/*[in]*/ double newVal)				{ return CVisObject::put_z(newVal); };
	STDMETHOD(get_tag)(/*[out, retval]*/ double *pVal)	    { return CVisObject::get_tag(pVal); };
	STDMETHOD(get_errstring)(/*[out, retval]*/ BSTR *pVal)	{ return CVisObject::get_errstring(pVal); };


	STDMETHOD(get_fontName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_fontName)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_fontItalic)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_fontItalic)(/*[in]*/ double newVal);
	STDMETHOD(get_fontUnderline)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_fontUnderline)(/*[in]*/ double newVal);
	STDMETHOD(get_fontWeight)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_fontWeight)(/*[in]*/ double newVal);
	STDMETHOD(get_fill)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_fill)(/*[in]*/ double newVal);

	STDMETHOD(get_color)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_color)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_alpha)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_alpha)(/*[in]*/ double newVal);
	STDMETHOD(get_text)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_text)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_angle)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_angle)(/*[in]*/ double newVal);
	STDMETHOD(get_scale)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_scale)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_size)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(get_clipped)(/*[out, retval]*/ double *pVal);
	
	void draw();

private:
	
	float Length;				// Pre-Scaling String Width
	float Height;				// Pre-Scaling String Height
	float ScaleX;				// Scaling of Width 
	float ScaleY;				// Scaling of Height 
	float Angle;				// Rotation of Text (about center)
	float Color[3];				// Color
#if INDEX_MODE
	int   ColorIndex;
#endif
	float Alpha;
	int   Fill;					// Fill
	char  textString[200];
	int   fontWeight;			// Font Weight: 100-900 in 100 steps??? (500 is normal)
	int   fontItalic;			// BOOL Italic
	int   fontUnderline;		// BOOL Underline
	char  fontName[30];			// Font Name


//	int   clipped;				// Clipped Flag (off edge of screen)
//	double X,Y;					// X,Y of Origin
//	double Z;					// Depth (for obstruction between objects)
//	int	  Show;					// Show Flag
//	wchar_t errorString[200];

	int listBase;					// 1st of the character Call List IDs
	GLYPHMETRICSFLOAT fontGMF[256];	// Storage For Information About Our Outline Font Characters
	void BuildFont(void);
	void KillFont(void);
	void calcTextBox(void);
	
};


#define VISTEXT_BITMAPPED_FONT 1				// Boolean Flag:  Bitmapped or Outlined (Polygon) Fonts
#define VISTEXT_DEFAULT_FONT   "Arial"          // Boolean Flag:  Bitmapped or Outlined (Polygon) Fonts


#endif // !defined(AFX_VISTEXT_H__299FB3B4_C44B_43B5_8E56_9CC9D0EC21D1__INCLUDED_)
