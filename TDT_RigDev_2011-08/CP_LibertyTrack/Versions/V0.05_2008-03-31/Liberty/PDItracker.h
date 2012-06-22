/////////////////////////////////////////////////////////////////////
// Polhemus Inc.,  www.polhemus.com
// © 2003 Alken, Inc. dba Polhemus, All Rights Reserved
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
//
//  Filename:           $Workfile: PDItracker.h $
//
//  Project Name:       Polhemus Developer Interface  
//
//  Description:        Tracker-Specific definitions
//
//  VSS $Header: /PIDevTools/Inc/PDItracker.h 17    7/05/05 11:00a Suzanne $  
//
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
#ifndef _PDITRACKER_H_
#define _PDITRACKER_H_

/////////////////////////////////////////////////////////////////////
// Liberty Binary Mode Header Format
/////////////////////////////////////////////////////////////////////
typedef struct _BIN_HDR_STRUCT 
{
	short preamble;              
	BYTE station;
	BYTE cmd;
	BYTE err;
	BYTE reserved;
	short length;

}*LPBINHDR,BINHDR;

#define LIBERTY_PREAMBLE 0x594C
#define PATRIOT_PREAMBLE 0x4150
#define LATUS_PREAMBLE   0x554C

/////////////////////////////////////////////////////////////////////
// Liberty WhoAmI Binary Mode Header Format
/////////////////////////////////////////////////////////////////////
typedef struct _BINWHOAMI_STRUCT
{
	BYTE ucMaxSensors;
	BYTE ucTrackerType;
	BYTE ucReserved[6];

}*LPBINWHO, BINWHO;

/////////////////////////////////////////////////////////////////////
// Tracker Types
/////////////////////////////////////////////////////////////////////
typedef enum
{
	PI_TRK_LIBERTY
	, PI_TRK_PATRIOT
	, PI_TRK_LATUS

	, PI_TRK_FASTRAK
	, PI_TRK_UNKNOWN
	, PI_TRK_MAX = PI_TRK_UNKNOWN
} ePiTrackerType;

#define LIBERTY_MAX_SENSORS	16
#define PATRIOT_MAX_SENSORS 2
#define LATUS_MAX_MARKERS	12

/////////////////////////////////////////////////////////////////////
// Liberty Error Codes
/////////////////////////////////////////////////////////////////////
typedef enum
{
	PI_DEVERR_NO_ERROR = 0				//	0   ' '

	// Command errors
	, PI_DEVERR_INVALID_COMMAND = 1		//	1	// 0x01
	, PI_DEVERR_STATION_OUT_OF_RANGE	//	2	// 0x02
	, PI_DEVERR_INVALID_PARAMETER		//	3	// 0x03
	, PI_DEVERR_TOO_FEW_PARAMETERS		//	4	// 0x04
	, PI_DEVERR_TOO_MANY_PARAMETERS		//	5	// 0x05
	, PI_DEVERR_PARAMETER_BELOW_LIMIT	//	6	// 0x06
	, PI_DEVERR_PARAMETER_ABOVE_LIMIT	//	7	// 0x07
	, PI_DEVERR_SP_COM_FAILURE			//	8	// 0x08
	, PI_DEVERR_SP1_INIT_FAILURE		//	9	// 0x09
	, PI_DEVERR_SP2_INIT_FAILURE		//	10	// 0x0a
	, PI_DEVERR_SP3_INIT_FAILURE		//	11	// 0x0b
	, PI_DEVERR_SP4_INIT_FAILURE		//	12	// 0x0c
	, PI_DEVERR_SP_NONE_DETECTED		//	13	// 0x0d
	, PI_DEVERR_SRC_INIT_FAILURE		//	14	// 0x0e
	, PI_DEVERR_MEM_ALLOC_ERROR			//	15	// 0x0f
	, PI_DEVERR_EXCESS_CMD_CHARS		//	16	// 0x10
	, PI_DEVERR_EXIT_UTH				//	17	// 0x11
	, PI_DEVERR_SOURCE_READ_ERROR		//	18	// 0x12
	, PI_DEVERR_READONLY_ERROR			//  19	// 0x13
	, PI_DEVERR_TEXT_MESSAGE			//  20	// 0x14
	, PI_DEVERR_MAP_LOAD				//  21	// 0x15
	, PI_DEVERR_SYNC_SENSORS			//  22	// 0x16
	, PI_DEVERR_FW_UPGRADE_REQ			//  23	// 0x17
	, PI_DEVERR_FW_UPGRADE_REC			//  24	// 0x18

	, PI_DEVERR_CURRENT_SET_ERROR		//  25	// 0x19
	, PI_DEVERR_ABSENT_RECEPTOR			//  26	// 0x1a
	, PI_DEVERR_RECEPTOR_ALIGN_ERROR	//  27	// 0x1b
	, PI_DEVERR_NO_MARKERS				//  28	// 0x1c
	, PI_DEVERR_LAUNCH_RECPT_NOT_ALIGNED//  29	// 0x1d
	, PI_DEVERR_WILDCARD_NOT_SUP		//  30	// 0x1e
	, PI_DEVERR_NO_MARKER_CHAR			//  31	// 0x1f
	, PI_DEVERR_ASCII_NOERROR			//  32	// 0x20
	, PI_DEVERR_NO_MARKER_FREQ_LAUNCHED	//  33	// 0x21
	, PI_DEVERR_CHAR_INSTALL_ERROR		//  34	// 0x22
	, PI_DEVERR_MARK_SER_NO_NOT_FOUND	//  35	// 0x23

	// Realtime errors 
	, PI_DEVERR_RT_SRC_FAIL_a_X			//  36 'a'
	, PI_DEVERR_RT_SRC_FAIL_b_Y			//  37 'b'
	, PI_DEVERR_RT_SRC_FAIL_c_XY		//  38 'c'
	, PI_DEVERR_RT_SRC_FAIL_d_Z			//  39 'd'
	, PI_DEVERR_RT_SRC_FAIL_e_XZ		//  40 'e'
	, PI_DEVERR_RT_SRC_FAIL_f_YZ		//  41 'f'
	, PI_DEVERR_RT_SRC_FAIL_g_XYZ		//  42 'g'

	, PI_DEVERR_RT_OUT_OF_MAP_u=49		//  49 'u'

	, PI_DEVERR_RT_SRC_FAIL_A_X			//  50 'A'
	, PI_DEVERR_RT_SRC_FAIL_B_Y			//  51 'B'
	, PI_DEVERR_RT_SRC_FAIL_C_XY		//  52 'C'
	, PI_DEVERR_RT_SRC_FAIL_D_Z			//  53 'D'
	, PI_DEVERR_RT_SRC_FAIL_E_XZ		//  54 'E'
	, PI_DEVERR_RT_SRC_FAIL_F_YZ		//  55 'F'
	, PI_DEVERR_RT_SRC_FAIL_G_XYZ		//  56 'G'

	, PI_DEVERR_RT_BITERR				//  57 'I'

	, PI_DEVERR_MAX
}ePiDevError;

/////////////////////////////////////////////////////////////////////
// END $Workfile: PDItracker.h $
/////////////////////////////////////////////////////////////////////
#endif // _PDITRACKER_H_
