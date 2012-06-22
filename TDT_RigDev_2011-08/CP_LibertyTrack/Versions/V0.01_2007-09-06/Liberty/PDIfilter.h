/////////////////////////////////////////////////////////////////////
// Polhemus Inc.,  www.polhemus.com
// © 2003 Alken, Inc. dba Polhemus, All Rights Reserved
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
//
//  Filename:           $Workfile: PDIfilter.h $
//
//  Project Name:       Polhemus Developer Interface  
//
//  Description:        Filter Class
//
//  VSS $Header: /PIDevTools/Inc/PDIfilter.h 5     6/11/03 2:38p Sgagnon $  
//
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
#ifndef _PDIFILTER_H_
#define _PDIFILTER_H_

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
#define PDI_FLT_OFF   1.0f // when sensitivity is set to this, filtering turned off.

// use these settings as starting point when determining optimal filter settings.
#define PDI_FLT_DEF_SENS  0.2f
#define PDI_FLT_DEF_LOW   0.2f
#define PDI_FLT_DEF_HIGH  0.8f
#define PDI_FLT_DEF_MAXT  0.8f

/////////////////////////////////////////////////////////////////////
// CLASS CPDIfilter
/////////////////////////////////////////////////////////////////////
class PSH_API CPDIfilter 
{
public:
    CPDIfilter( FLOAT s=PDI_FLT_DEF_SENS, 
				FLOAT l=PDI_FLT_OFF, 
				FLOAT h=PDI_FLT_DEF_HIGH, 
				FLOAT m=PDI_FLT_DEF_MAXT )
    { m_fSensitivity=s; m_fLowValue=l; m_fHighValue=h; m_fMaxTransRate=m; }

    CPDIfilter   ( const CPDIfilter & rv )
    { m_fSensitivity  = rv.m_fSensitivity; 
      m_fLowValue     = rv.m_fLowValue; 
      m_fHighValue    = rv.m_fHighValue; 
      m_fMaxTransRate = rv.m_fMaxTransRate; 
    }

	~CPDIfilter	( VOID ){};

    CPDIfilter & operator=   (const CPDIfilter & rv )
    { m_fSensitivity  = rv.m_fSensitivity; 
      m_fLowValue     = rv.m_fLowValue; 
      m_fHighValue    = rv.m_fHighValue; 
      m_fMaxTransRate = rv.m_fMaxTransRate;
      return *this;
    }

    BOOL    Disabled ( VOID ) const	// Returns disabled state
    { return (m_fLowValue >= PDI_FLT_OFF); }

	VOID	Disable	(VOID)			// Disables filter
	{ m_fLowValue = PDI_FLT_OFF; }

    FLOAT   m_fSensitivity;
    FLOAT   m_fLowValue;
    FLOAT   m_fHighValue;
    FLOAT   m_fMaxTransRate;
};


/////////////////////////////////////////////////////////////////////
// END $Workfile: PDIfilter.h $
/////////////////////////////////////////////////////////////////////
#endif // _PDIFILTER_H_
