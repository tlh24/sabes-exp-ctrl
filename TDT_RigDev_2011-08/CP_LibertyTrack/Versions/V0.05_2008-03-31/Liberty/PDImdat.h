/////////////////////////////////////////////////////////////////////
// Polhemus Inc.,  www.polhemus.com
// © 2003 Alken, Inc. dba Polhemus, All Rights Reserved
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
//
//  Filename:           $Workfile: PDImdat.h $
//
//  Project Name:       Polhemus Developer Interface  
//
//  Description:        Motion Data Output List Class
//						Class used to define motion output per sensor
//
//  VSS $Header: /PIDevTools/Inc/PDImdat.h 5     12/05/03 9:35a Sgagnon $  
//
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
#ifndef _PCIMDAT_H_
#define _PCIMDAT_H_

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
// Output motion data types
/////////////////////////////////////////////////////////////////////
typedef enum
{
    PDI_ODATA_SPACE = 0     // space
    , PDI_MODATA_CRLF         // <cr><lf>
    , PDI_MODATA_POS          // x, y, z Cartesion pos coords
    , PDI_MODATA_POS_EP       // x, y, z Cartesion pos coords, extended precision
    , PDI_MODATA_ORI          // az, el, ro Euler ori angles
    , PDI_MODATA_ORI_EP       // az, el, ro Euler ori angles, extended precision
    , PDI_MODATA_DIRCOS       // Direction Cosine Matrix
    , PDI_MODATA_QTRN         // Orientation Quarternion
    , PDI_MODATA_TIMESTAMP    // Timestamp (32-bit)
    , PDI_MODATA_FRAMECOUNT   // Frame Count (32-bit)
    , PDI_MODATA_STYLUS       // Stylus Flag (32-bit)
    , PDI_MODATA_DISTLEV      // Distortion Level (32-bit)   
    , PDI_MODATA_EXTSYNC      // External Sync (32-bit) (1 = Detected)
 
} ePDIMotionData;
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
class CPiOutputList;

/////////////////////////////////////////////////////////////////////
// CLASS CPDImdat
/////////////////////////////////////////////////////////////////////
class PDI_API CPDImdat
{
public:
	CPDImdat( VOID );
	virtual ~CPDImdat( VOID );

    CPDImdat &	operator=	( const CPDImdat & );

	VOID			Append		( ePDIMotionData ); // Appends item to end
	VOID			Remove		( INT nIndex );	   // Removes indexed item
	VOID			Insert		( ePDIMotionData, INT nIndex ); // Inserts item before index
	ePDIMotionData	ItemAt		( INT nIndex );    // Returns item at index
	VOID			Empty		( VOID );		   // Empties list
    INT             NumItems    ( VOID );          // Returns number of items

private:
	CPDImdat( const CPDImdat & );

	CPiOutputList * m_pOL;

	friend class CPDIdev;
};


/////////////////////////////////////////////////////////////////////
// END $Workfile: PDImdat.h $
/////////////////////////////////////////////////////////////////////
#endif // _PCIMDATA_H_
