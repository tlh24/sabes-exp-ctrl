/***************************************************************
     Name:            NDOPTO.H

     Description:
     Main OPTOTRAK API include file.

     Modified:

****************************************************************/

#ifndef INCLUDE_NDOPTO
#define INCLUDE_NDOPTO


/***************************************************************
Name:            APP_PARM.H

Description:
    Header file for APP_PARM C file.
    This module contains routines for reading and saving
    application parameters.

Modified:

****************************************************************/

#ifndef INCLUDE_APP_PARM_H
#define INCLUDE_APP_PARM_H

/****************************************************************
  Defines
****************************************************************/
#define APP_PARM_STRING     0x0001
#define APP_PARM_INT        0x0002
#define APP_PARM_UNSIGNED   0x0004
#define APP_PARM_LONG       0x0008
#define APP_PARM_ULONG      0x0010
#define APP_PARM_FLOAT      0x0020
#define APP_PARM_DOUBLE     0x0040
#define APP_PARM_BOOLEAN    0x0080
#define APP_PARM_OPTIONAL   0x1000
#define APP_PARM_COUNT      0x3000  /* Always an optional parameter */

/*
 * These are used internally by ReadAppParms().  Do not use.
 */
#define APP_PARM_TYPES      0x00ff
#define APP_PARM_NUMERIC    0x007e
#define APP_PARM_UNREAD     0x8000

/****************************************************************
  Macros
****************************************************************/

/****************************************************************
 Global Structures
****************************************************************/
typedef struct
{
    char        *pszParam;
    void        *pBuffer;
    unsigned    uBuffLen;
    unsigned    uFlags;
    float       fMinVal;
    float       fMaxVal;
} AppParmInfo;

/****************************************************************
 External Variables
****************************************************************/

/****************************************************************
 Routine Definitions
****************************************************************/
 
CPLUSPLUS_START
boolean ReadAppParms( char *pszParmFile, char *pszSection,
                      AppParmInfo *pParmInfo );
boolean SaveAppParms( char *pszParmFile, char *pszSection,
                      AppParmInfo *pParmInfo );
/*
 * SCO-98-0071
 *  added DeleteAppParms
 */
boolean DeleteAppParms( char *pszParmFile, char *pszSection );
CPLUSPLUS_END

#endif
/***************************************************************
Name: MSG_IDS    -Listing of all message ids used in OPTOTRAK
****************************************************************/

/*--------------------------------------------------------------------------
 * From: MESSINT.H
 */

/*
 * Commands sent to and from internal components of the optotrak
 * system.
 */

/*
 * Messages IDs for fast message system.
 */
#define FAST_REGISTER_SENSOR    				0
#define FAST_SENSOR_DATA        				1
#define FAST_ODAU_DATA          				2
#define FAST_FAKE_DATA          				3
#define FAST_SENSOR_SHUTDOWN    				4
#define FAST_BUFFER_DATA        				5

/*--------------------------------------------------------------------------
 * From: MESS_SYS.H
 */

/*
 * Commands required by the low level message passing routines.
 */

/*
 * Message IDs for regular messages
 */
#define ADD_NEW_NODE_MESSAGE        			1
#define ADD_NEW_PROCESS_MESSAGE     			2
#define SETUP_MONITOR_MESSAGE       			3
#define SEND_CONFIG_INFO_MESSAGE    			4
#define END_CONFIG_INFO_MESSAGE     			5
#define SETUP_LINK_MESSAGE          			6
#define ERROR_MESSAGE               			7
#define DELETE_PROCESS_MESSAGE      			8

/*
 * SCO-95-0015
 */
#define INITIALIZE_TIMEOUT_MESSAGE  			16
#define ADD_CHILD_NODE_MESSAGE					17
#define CHILD_CONFIG_COMPLETE_MESSAGE			18
#define BROADCAST_NODES_MESSAGE					19
#define BROADCAST_NODES_DONE_MESSAGE			20
#define BROADCAST_PROCS_MESSAGE					21
#define BROADCAST_PROCS_DONE_MESSAGE			22

/*--------------------------------------------------------------------------
 * From: MESSINT.H
 */

/*
 * Commands sent to and from internal components of the optotrak
 * system.
 */

/*
 * System messages
 */
#define STANDARD_ERROR_MESSAGE      			256
#define PROC_STOP_MESSAGE           			257
#define SUCCESSFUL_MESSAGE          			258
#define FAILURE_MESSAGE             			259

#define DEBUG_MESSAGE               			299

/*--------------------------------------------------------------------------
 * From: GENERAL.H
 */

/*
 * Defines for different commands shared between OPTOTRAK and OPTOSCOPE
 */
#define OPTO_ERROR_REQUEST_MESSAGE      		1000
#define OPTO_ERROR_REQUEST_COMMAND      		1001

#define OPTO_STATUS_REQUEST_MESSAGE     		1002

/*
 * SCO-95-0015
 * Added OPTO_NODE_INFO_MESSAGE
 * Message will return an OptoNodeInfoStruct for use in
 * an about box.
 */
#define OPTO_NODE_INFO_MESSAGE					1003

#define OPTO_TX_ONE_FRAME_MESSAGE       		1004

#define OPTO_TX_MANY_FRAME_MESSAGE      		1006

#define OPTO_LATEST_CENTROID_FRAME_MESSAGE      1008

#define OPTO_LATEST_FRAME_MESSAGE       		1010

/*--------------------------------------------------------------------------
 * From: DATAPROP.H
 */

/*
 * Messages specific to the OPTOTRAK data proprietor
 */
#define OPTO_LATEST_RAW_FRAME_MESSAGE   		1012

/*--------------------------------------------------------------------------
 * From: REALTIME.H
 */

/*
 * Commands specific to the OPTOTRAK data proprietor for realtime option.
 */
#define OPTO_LATEST_RIGID_FRAME_MESSAGE 		1014

/*--------------------------------------------------------------------------
 * From: DATAPROP.H
 */

/*
 * Messages specific to the OPTOTRAK data proprietor
 */
#define OPTO_TRANSFORM_DATA_MESSAGE     		1016

#define OPTO_LATEST_WAVE_FRAME_MESSAGE  		1018

/*--------------------------------------------------------------------------
 * New messages for NEXT rather than LATEST frame of data
 */

#define OPTO_NEXT_FRAME_MESSAGE					1019
#define OPTO_NEXT_RAW_FRAME_MESSAGE				1020
#define OPTO_NEXT_RIGID_FRAME_MESSAGE			1021
#define OPTO_NEXT_CENTROID_FRAME_MESSAGE		1022

/*--------------------------------------------------------------------------
 * From: GENERAL.H
 */

/*
 * Defines for different commands shared between OPTOTRAK and OPTOSCOPE
 */
#define OPTO_ERROR_MESSAGE              		1050
#define OPTO_ERROR_COMMAND              		1051

/*
 * The following are message ids you could receive from either the
 * OPTOTRAK or the OPTOSCOPE
 */
#define OPTO_SUCCESSFUL_MESSAGE         		1052
#define OPTO_SUCCESSFUL_COMMAND         		1053

#define OPTO_UNSUCCESSFUL_MESSAGE       		1054
#define OPTO_UNSUCCESSFUL_COMMAND       		1055

#define OPTO_DATA_BUFFER_MESSAGE        		1056
#define OPTO_LATEST_BUFFER_MESSAGE      		1058

/*--------------------------------------------------------------------------
 * From: REALTIME.H
 */

/*
 * Commands specific to the OPTOTRAK data proprietor for realtime option.
 */

#define OPTO_LATEST_RIGID_MESSAGE       		1060

/*--------------------------------------------------------------------------
 * From: DATAPROP.H
 */

/*
 * Messages specific to the OPTOTRAK data proprietor
 */

#define OPTO_TRANS_BUFFER_MESSAGE       		1062

/*--------------------------------------------------------------------------
 * From: REALTIME.H
 */

/*
 * Commands specific to the OPTOTRAK data proprietor for realtime option.
 */

#define OPTOTRAK_RIGID_STATUS_MESSAGE   		1064

/*--------------------------------------------------------------------------
 * From: GENERAL.H
 */

/*
 * Defines for different commands shared between OPTOTRAK and OPTOSCOPE
 */
#define OPTOTRAK_REGISTER_MESSAGE       		1102
#define OPTOTRAK_REGISTER_COMMAND       		1103

/*--------------------------------------------------------------------------
 * From: INTERNAL.H
 */

/*
 * Commands for internal messaging inside the OPTOTRAK system.
 */

#define OPTOTRAK_ADD_CAMERA_MESSAGE     		1104
#define OPTOTRAK_ADD_CAMERA_COMMAND     		1105

#define OPTOTRAK_CALIBRATE_MESSAGE      		1106
#define OPTOTRAK_CALIBRATE_COMMAND      		1107

/*--------------------------------------------------------------------------
 * From: ADMIN.H
 */

/*
 * Defines for commands to pass to the OPTOTRAK Administrator.
 */
#define OPTOTRAK_MODIFY_SYSTEM_MESSAGE  		1108
#define OPTOTRAK_MODIFY_SYSTEM_COMMAND  		1109

#define OPTOTRAK_SETUP_COLL_MESSAGE     		1110
#define OPTOTRAK_SETUP_COLL_COMMAND     		1111

#define OPTOTRAK_STOP_FIRING_MESSAGE    		1112

#define OPTOTRAK_START_FIRING_MESSAGE   		1114
#define OPTOTRAK_START_FIRING_COMMAND   		1115

#define OPTOTRAK_START_BUFF_MESSAGE     		1116
#define OPTOTRAK_START_BUFF_COMMAND     		1117

#define OPTOTRAK_STOP_BUFF_MESSAGE      		1118
#define OPTOTRAK_STOP_BUFF_COMMAND      		1119

#define OPTOTRAK_SHUTDOWN_MESSAGE       		1120
#define OPTOTRAK_SHUTDOWN_COMMAND       		1121

/*--------------------------------------------------------------------------
 * From: REALTIME.H
 */

/*
 * Commands specific to the OPTOTRAK data proprietor for realtime option.
 */
#define OPTOTRAK_ADD_RIGID_MESSAGE      		1122

#define OPTOTRAK_DEL_RIGID_MESSAGE      		1124

#define OPTOTRAK_SET_RIGID_MESSAGE      		1126

#define OPTOTRAK_ROTATE_RIGIDS_MESSAGE  		1128

#define OPTOTRAK_STOP_ROTATING_MESSAGE  		1130

/*--------------------------------------------------------------------------
 * From: ADMIN.H
 */

/*
 * Defines for commands to pass to the OPTOTRAK Administrator.
 */
#define OPTOTRAK_UNREGISTER_MESSAGE     		1132
#define OPTOTRAK_UNREGISTER_COMMAND     		1133

#define OPTOTRAK_TRIGGER_COLLECTION_MESSAGE 	1134
#define OPTOTRAK_TRIGGER_COLLECTION_COMMAND 	1135

/*--------------------------------------------------------------------------
 * From: INTERNAL.H
 */

/*
 * Commands for internal messaging inside the OPTOTRAK system.
 */

#ifdef NEVER
#define OPTOTRAK_SYSTEM_CFG_MESSAGE     		1134		 <--- Conflict
#define OPTOTRAK_SYSTEM_CFG_COMMAND     		1135         <--- Conflict
#endif

#define OPTOTRAK_CAMERA_NAMES_MESSAGE   		1136
#define OPTOTRAK_CAMERA_NAMES_COMMAND   		1137

/*--------------------------------------------------------------------------
 * From: REALTIME.H
 */

/*
 * Commands specific to the OPTOTRAK data proprietor for realtime option.
 */
#define OPTOTRAK_ADD_NORMALS_MESSAGE    		1138

#define OPTOTRAK_GET_RIG_STATUS_MESSAGE    		1140

/*--------------------------------------------------------------------------
 * From: ADMIN.H
 */

/*
 * Defines for commands to pass to the OPTOTRAK Administrator.
 */
#define OPTOTRAK_STROBER_TABLE_MESSAGE      	1142

/*--------------------------------------------------------------------------
 * From: INTERNAL.H
 */

/*
 * Commands for internal messaging inside the OPTOTRAK system.
 */

#define OPTOTRAK_CALIBRATING_MESSAGE    		1150
#define OPTOTRAK_CALIBRATING_COMMAND    		1151

#define OPTOTRAK_DONE_CALIB_MESSAGE     		1152
#define OPTOTRAK_DONE_CALIB_COMMAND     		1153

/*--------------------------------------------------------------------------
 * From: ADMIN.H
 */

/*
 * Defines for commands to pass to the OPTOTRAK Administrator.
 */
#define OPTOTRAK_STATUS_MESSAGE         		1154
#define OPTOTRAK_STATUS_COMMAND         		1155


#define OPTOTRAK_STATUS_CHANGED_MESSAGE 		1158
#define OPTOTRAK_STATUS_CHANGED_COMMAND 		1159

/*--------------------------------------------------------------------------
 * From: INTERNAL.H
 */

/*
 * Commands for internal messaging inside the OPTOTRAK system.
 */
#define OPTOTRAK_FAKE_DATA_MESSAGE      		1160
#define OPTOTRAK_FAKE_DATA_COMMAND      		1161

#define OPTOTRAK_END_FAKE_DATA_MESSAGE  		1162
#define OPTOTRAK_END_FAKE_DATA_COMMAND  		1163

#define OPTOTRAK_SETUP_DRC_MESSAGE      		1166
#define OPTOTRAK_SETUP_DRC_COMMAND      		1167

#define OPTOTRAK_MARKER_RATIO_MESSAGE   		1168
#define OPTOTRAK_MARKER_RATIO_COMMAND   		1169

#define OPTOTRAK_SET_DDC_PARMS_MESSAGE  		1170

/*
 * Messages for flash rom stuff.
 */
#define OPTOTRAK_ERASE_ROM_MESSAGE      		1172
#define OPTOTRAK_ERASE_ROM_COMMAND      		1173
#define OPTOTRAK_READ_ROM_MESSAGE       		1174
#define OPTOTRAK_READ_ROM_COMMAND       		1175
#define OPTOTRAK_WRITE_ROM_MESSAGE      		1176
#define OPTOTRAK_WRITE_ROM_COMMAND      		1177
#define OPTOTRAK_VPP_ROM_MESSAGE        		1178
#define OPTOTRAK_VPP_ROM_COMMAND        		1179

/*
 * SCO-95-0015
 * Message back from ODAU II or other device to update
 * OPTOTRAK Frame rate according to what can be generated.
 */
#define OPTOTRAK_ACTUAL_RATE_MESSAGE			1180

/*--------------------------------------------------------------------------
 * From: MESSINT.H
 */

/*
 * Commands sent to and from internal components of the optotrak
 * system.
 */
#define OPTO_REGISTER_EVENT_MESSAGE     		1190

/*--------------------------------------------------------------------------
 * From: ODAU.H
 */

/*
 * Commands for interfacing with the ODAU unit.
 */
#define OPTOSCOPE_SETUP_COLL_MESSAGE        	1202
#define OPTOSCOPE_SETUP_COLL_COMMAND        	1203

/*--------------------------------------------------------------------------
 * From: INTERNAL.H
 */

/*
 * Commands for internal messaging inside the OPTOTRAK system.
 */
#define OPTOSCOPE_START_BSYNC_MESSAGE       	1204
#define OPTOSCOPE_START_BSYNC_COMMAND       	1205

/*--------------------------------------------------------------------------
 * From: ODAU.H
 */

/*
 * Commands for interfacing with the ODAU unit.
 */
#define OPTOSCOPE_START_BUFF_MESSAGE        	1206
#define OPTOSCOPE_START_BUFF_COMMAND        	1207

#define OPTOSCOPE_STOP_BUFF_MESSAGE         	1208
#define OPTOSCOPE_STOP_BUFF_COMMAND         	1209

/*--------------------------------------------------------------------------
 * From: INTERNAL.H
 */

/*
 * Commands for internal messaging inside the OPTOTRAK system.
 */
#define OPTOSCOPE_STOP_BSYNC_MESSAGE        	1210
#define OPTOSCOPE_STOP_BSYNC_COMMAND        	1211

/*--------------------------------------------------------------------------
 * From: ODAU.H
 */

/*
 * Commands for interfacing with the ODAU unit.
 */
#define OPTOSCOPE_SHUTDOWN_MESSAGE          	1212
#define OPTOSCOPE_SHUTDOWN_COMMAND          	1213

/*
 * SCO 95-0015
 * New Messages for ODAU II
 */
#define OPTOSCOPE_ANALOG_OUT_MESSAGE			1214
#define OPTOSCOPE_DIGITAL_OUT_MESSAGE			1216

/*
 * SCO-97-0020
 * New Messages
 */
#define OPTOSCOPE_SET_TIMER_MESSAGE                     1217
#define OPTOSCOPE_LOAD_FIFO_MESSAGE                     1218

#define OPTOSCOPE_STATUS_MESSAGE        		1250

/*--------------------------------------------------------------------------
 * From: MESSINT.H
 */

/*
 * Commands sent to and from internal components of the optotrak
 * system.
 */

/*
 * These are the message id's used to communicate with
 * the sensor subsystem
 */
#define SENSOR_INITIALIZED_MESSAGE              2000
#define SENSOR_SETUP_COLL_MESSAGE               2001
#define SENSOR_START_GEN_MESSAGE                2002
#define SENSOR_STOP_GEN_MESSAGE                 2003
#define SENSOR_SETUP_COMPLETE_MESSAGE           2004
#define SENSOR_GEN_COMPLETE_MESSAGE             2005
#define SENSOR_CALIBRATE_MESSAGE                2006
#define SENSOR_TEST_CCD_CHARGE_MESSAGE          2007
#define SENSOR_EX_ONE_MARKER_MESSAGE            2008
#define SENSOR_ROUTE_DATA_MESSAGE               2009
#define SENSOR_ROUTE_COMPLETE_MESSAGE           2010
#define SENSOR_CENTROID_DATA_MESSAGE            2011
#define SENSOR_CALIB_COMPLETE_MESSAGE           2012
#define SENSOR_TERM_DATA_MESSAGE                2013
#define SENSOR_ROUTE2_DATA_MESSAGE              2014
#define SENSOR_CALIB_REQUIRED_MESSAGE           2015

/*
 * These are general internal messages
 */
#define INTL_ROUTE_SETUP_FAILED                 2050
#define INTL_ROUTE_TYPE_UNKNOWN                 2051
#define INTL_UNRECOGNIZED_COMMAND               2052
#define INTL_SETUP_ZERO_MARKERS                 2053
#define INTL_SETUP_FAILED                       2054
#define INTL_OUT_OF_MEMORY                      2055

/*
 * These are the message id's used to communicate with
 * a data buffer/consolidator process.
 */
#define DATABUFF_INITIALIZED_MESSAGE            2200
#define DATABUFF_TX_STATUS_MESSAGE              2201
#define DATABUFF_STATUS_MESSAGE                 2202
#define DATABUFF_DATA_PACKET_MESSAGE            2203
#define DATABUFF_DATA_BUFFER_MESSAGE            2204
#define DATABUFF_TX_ONE_FRAME_MESSAGE           2205
#define DATABUFF_TX_MANY_FRAME_MESSAGE          2206
#define DATABUFF_TX_ALL_FRAME_MESSAGE           2207
#define DATABUFF_TX_STREAM_MESSAGE              2208
#define DATABUFF_TERM_STREAM_MESSAGE            2209
#define DATABUFF_TERM_TX_MESSAGE                2210
#define DATABUFF_FLUSH_MESSAGE                  2211
#define DATABUFF_TERMINATE_MESSAGE              2212
#define DATABUFF_SETUP_COLL_MESSAGE             2213
#define DATABUFF_SETUP_COMPLETE_MESSAGE         2214
#define DATABUFF_START_COLL_MESSAGE             2215
#define DATABUFF_START_COMPLETE_MESSAGE         2216
#define DATABUFF_STOP_COLL_MESSAGE              2217
#define DATABUFF_COLL_COMPLETE_MESSAGE          2218

/*
 * These are the message id's used to communicate with
 * a courier process.
 */
#define COURIER_READY_MESSAGE                   2300

/*
 * These are the message id's used to communicate with the
 * data proprietor process.
 */
#define DATAPROP_INITIALIZED_MESSAGE            2400
#define DATAPROP_NEW_NODE_MESSAGE               2401
#define DATAPROP_ADD_CAMERA_MESSAGE             2402
#define DATAPROP_SEND_DATA_MESSAGE              2403
#define DATAPROP_STREAM_DATA_MESSAGE            2404

/*
 * These are the message id's used to communicate with
 * a null data consumer process.
 */
#define NULLDATA_INITIALIZED_MESSAGE            2500
#define NULLDATA_START_COLL_MESSAGE             2501
#define NULLDATA_COLL_COMPLETE_MESSAGE          2502
#define NULLDATA_TERMINATE_MESSAGE              2503

/*
 * These are the message id's used to communicate with a data
 * worker process
 */
#define DATAWORK_INITIALIZED_MESSAGE            2600
#define DATAWORK_START_COLL_MESSAGE             2601
#define DATAWORK_START_COMPLETE_MESSAGE         2602
#define DATAWORK_STOP_COLL_MESSAGE              2603
#define DATAWORK_COLL_COMPLETE_MESSAGE          2604
#define DATAWORK_TERMINATE_MESSAGE              2605
#define DATAWORK_SETUP_COLL_MESSAGE             2606
#define DATAWORK_SETUP_COMPLETE_MESSAGE         2607
#define DATAWORK_SHUTDOWN_MESSAGE               2608

/*
 * These are the message id's used to communicate with a notifier
 * process
 */
#define NOTIFIER_INITIALIZED_MESSAGE            2700
#define NOTIFIER_SET_TIME_MESSAGE               2701
#define NOTIFIER_TIME_OUT_MESSAGE               2702

/*
 * These are the message id's used for communication between the OPTOTRAK
 * Administrator and the OPTOSCOPE Administrator.
 */
#define OSCOPE_INITIALIZED_MESSAGE              2800
#define OSCOPE_SETUP_INFO_MESSAGE               2801

/*
 * SCO-95-0015
 * New Messages for ODAU II
 */
#define OSCOPE2_INITIALIZED_MESSAGE             2802
#define OSCOPE2_START_GEN_MESSAGE               2803
#define OSCOPE2_SET_SYNC_RATE_MESSAGE           2804

/*
 * These are general internal messages
 */
#define INTERNAL_HEAP_DUMP_MESSAGE              3000
#define INTERNAL_CHECK_STACK_MESSAGE            3001
#define SETUP_COLL_MESSAGE                      3002
#define SHUTDOWN_COLL_MESSAGE                   3003

/*--------------------------------------------------------------------------
 * From: INTERNAL.H
 */

/*
 * Commands for internal messaging inside the OPTOTRAK system.
 */

/*
 * Waveform messages.
 */
#define OPTOTRAK_WAVEFORM_REQUEST       		5001
#define OPTOTRAK_SET_WAVEFORM_MESSAGE   		5002
#define OPTOTRAK_ALTER_WAVEFORM_MESSAGE 		5003
#define OPTOTRAK_SENSOR_WAVEFORM_DATA   		5004
#define OPTOTRAK_DETERMINE_CENTROID     		5005
#define OPTOTRAK_SENSOR_DATA_MESSAGE    		5006
#define SET_SIGNAL_INJECTOR             		5007
#define UNSET_SIGNAL_INJECTOR           		5008

/*--------------------------------------------------------------------------
 * From: GENSTAT.H
 */

/*
 * Commands for general statistics a process wants to return
 * and have printed.
 */

#define GEN_STAT_REQUEST_MESSAGE  				7800
#define GEN_STAT_DATA_MESSAGE     				7801

/*--------------------------------------------------------------------------
 * From: STR_STAT.H
 */

/*
 * Commands for obtaining strober statistics.
 */

#define STROBER_STAT_MESSAGE         			8000
#define STROBER_SET_BUSYWAIT_MESSAGE 			8001

/*
 *--------------------------------------------------------------------------
 */

/*************************************************************************
Name:            MESSAGE.H

Description:

This include file defines what a message header looks like and various
message passing routines
**************************************************************************/
/*
 * System maximums
 */
#define MAX_PROCESSES       32
#define MAX_NODES           64
#define MAX_SYSTEM_MESSAGE  255
#define UNKNOWN_PROCESS     MAX_PROCESSES
#define STRING_LENGTH       81
#define MAX_NAME_LENGTH 40

/*
 * System flag defines for message.SystemFlags
 */
#define ALLOCATED_MESSAGE       1      /* If AllocMessage used */
#define EXTERNAL_MESSAGE        2
#define MULTIPLE_DATA_MESSAGE   8       /* If there are multiple data ptr's */
#define TRANSPUTER_BOOTER "TransputerBooter"

/*
 * The following structure holds all of the routing information for a
 * process located on some processor
 */
typedef struct AddressStruct
    {
    unsigned char
                node,               /* Processor node which message should go to */
                dummy,              /* Not currently used */
                process,            /* Process within node */
                dummy1;             /* Not currently used */
    }Address;

/*
 * The following is the header passed with every message.
 */
typedef struct MessageHeaderStruct
    {
    struct AddressStruct
        dest,          /* Process to which message is routed */
        source;        /* Process which message originated from */

    long int
        flags,              /* Any flags for this message */
        MessageId,          /* Identifies type of message being passed */
        MessageSize,        /* Size of data in message. Always multiple of 4 */
		SystemStatusFlags,  /* Currently Unused */
		HeaderCheckSum,     /* Checksum of Message Header - Unused */
		DataCheckSum;       /* Checksum of Message Data   - Unused */
    } MessageHeader;

#define MESSAGE_HEADER_SIZE     (8*4)

/*
 * The following is the message.
 */
typedef struct MessageStruct
    {
    struct MessageHeaderStruct
                header;             /* Header for data being passed */
    unsigned char
                *data;              /* Actual data being passed */
    unsigned long
                *size;              /* Sizes of data buffers if more than one */
    unsigned
                SystemFlags;       /* Sets parameters for this message */
    }Message;



/*
 * Definitions for the various types of messages passed around the system
 */
struct ProcessSetupStruct
    {
    long int
        distance;           /* Distance message has travelled */
    unsigned char           /* Name of process */
        name[MAX_NAME_LENGTH];
    struct AddressStruct
        address;
    };

struct NodeSetupStruct
    {
    long int
        distance,           /* Distance message has travelled */
        NodeNumber,        /* Node number for the new node being added to system */
        SendSetupInfo;    /* If TRUE then send setup information */
    unsigned char           /* Name of new node */
        name[MAX_NAME_LENGTH];
    };

CPLUSPLUS_START
extern  void FreeMessage(struct MessageStruct *message);
CPLUSPLUS_END
/***************************************************************
Name: GENERAL    -General section describing OPTOTRAK interface

Note when passing messages to the OPTOTRAK, ASCII message types end in
COMMAND, while normal C type structures end in MESSAGE.
****************************************************************/
/*
 * SCO-97-0050: Added MAX_HOST_RIGID_BODIES to define the maximum
 * number of rigid bodies supported for on-host transformations.
 * The limit was set to 1/3 of OPTOTRAK_MAX_MARKERS.
 */

/*
 * Constants defining limits on certain objects in the OPTOTRAK system.
 */
#define MAX_SENSORS                      10
#define MAX_OPTOSCOPES                    4
#define MAX_RIGID_BODIES                 10
#define MAX_HOST_RIGID_BODIES            85
#define MAX_SENSOR_NAME_LENGTH           20
#define OPTOTRAK_MAX_MARKERS            256

/*
 * Defines for different commands shared between OPTOTRAK and OPTOSCOPE
 */

/* OPTO_ERROR_REQUEST_MESSAGE
 * OPTO_ERROR_REQUEST_COMMAND
 *
 * OPTO_STATUS_REQUEST_MESSAGE
 *
 * OPTO_TX_ONE_FRAME_MESSAGE
 *
 * OPTO_TX_MANY_FRAME_MESSAGE
 *
 * OPTO_LATEST_FRAME_MESSAGE
 *
 * OPTO_ERROR_MESSAGE
 * OPTO_ERROR_COMMAND
 *
 * OPTOTRAK_REGISTER_MESSAGE
 * OPTOTRAK_REGISTER_COMMAND
 */

struct OptotrakRegisterStruct
{
	long int    monitor;            /* TRUE if this is a simple monitor */
									/* and not a controlling application */
	long int    AsciiResponse;      /* TRUE if responses to application */
};                                  /* should be in ascii (not binary) */


/*
 * SCO-95-0015
 * Added struct OptoNodeInfoStruct
 * Returned in receipt of the OPTO_NODE_INFO_MESSAGE
 */
#define OPTO_HW_TYPE_SENSOR		0x4D41435FL		/* '_CAM' */
#define OPTO_HW_TYPE_SU			0x55535953L		/* 'SYSU' */
#define OPTO_HW_TYPE_ODAU		0x5541444FL		/* 'ODAU' */
#define OPTO_HW_TYPE_REALTIME	0x5D544C52L		/* 'RLTM' */

struct OptoNodeInfoStruct
{
	unsigned long	ulHWType,
					ulHWRev,
					ulMemSize;
	char			szFreezeId[ 80 ],
					szSwDesc[ 80 ],
					szSerialNo[ 32 ];
};

/*
 * The following are message ids you could receive from either the
 * OPTOTRAK or the OPTOSCOPE
 */

/* OPTO_SUCCESSFUL_MESSAGE
 * OPTO_SUCCESSFUL_COMMAND
 *
 * OPTO_UNSUCCESSFUL_MESSAGE
 * OPTO_UNSUCCESSFUL_COMMAND
 */

struct OptoUnsuccessfulStruct
{
	long int        ErrorCode;          /* Error code if not successful */
	unsigned char   message[80];        /* String describing the error */
};


/* OPTO_DATA_BUFFER_MESSAGE
 * OPTO_LATEST_BUFFER_MESSAGE
 */

#define OPTO_DATA_HEADER_SIZE             24
struct OptoDataHeaderStruct
{
	long int DataId;           /* Identifier sent with each data packet. */
	long int StartFrameNumber; /* Collection frame number for first frame in message */
	long int NumberOfFrames;   /* Number of frames in this message */
	long int NumberOfElements; /* Number of elements in each frame */
	long int FramesLeft;       /* Number of frames left to retrieve for collection */
	long int flags;            /* Flags indicating status of buffer etc. */
};

/*
 * These are flags and constants used by OPTOTRAK and OPTOSCOPE for any of
 * the buffer messages
 */
#define OPTO_BUFFER_OVERRUN_FLAG        0x0001
#define OPTO_FRAME_OVERRUN_FLAG         0x0002
#define OPTO_NO_PRE_FRAMES_FLAG         0x0004
/***************************************************************
Name: DATAPROP   -Details general interface to the data proprietor
****************************************************************/

/*
 * Messages specific to the OPTOTRAK data proprietor
 */

/* OPTO_LATEST_RAW_FRAME_MESSAGE
 * DATAPROP_SEND_DATA_MESSAGE
 * OPTO_LATEST_WAVE_FRAME_MESSAGE
 */

struct optotrak_wave_head_struct
{
	float       centroid;        /* Calculated centroid */
	char        peak_value;      /* Peak value at peak pixel */
	char        gain;            /* Gain setting for this collection */
	char        error;           /* Error in centtroid calculation */
	char        dummy;
	char        peak_offset[2];  /* Pixel Number of peak */
	char        start_pixel[2];  /* Pixel number of first pixel in wave */
};

/* OPTO_TRANSFORM_DATA_MESSAGE
 */

#define OPTO_TRANSFORM_DATA_SIZE           8
struct OptoTransformDataStruct
{
	long int markers;       /* Total # of markers to convert */
	long int FullDataInfo;  /* Data contains peak info as well */
};


/*
 * Data ids you can receive back from the OPTOTRAK
 */

/* OPTO_TRANS_BUFFER_MESSAGE
 */
/***************************************************************
Name: ODAU       -Section detailing interfacing with the ODAU unit
****************************************************************/
#define OPTOSCOPE_MAX_CHANNELS_IN       16
#define OPTOSCOPE_MIN_CHANNEL_NUM        1
#define OPTOSCOPE_MAX_TABLE_ENTRIES     OPTOSCOPE_MAX_CHANNELS_IN + 1

/*
 * SCO-95-0015
 * Added    ODAU_DIGITAL_OFFB_MUXA
 *          ODAU_DIGITAL_INPB_MUXA
 *          ODAU_DIGITAL_OUTPB_MUXA
 * Changed constants to act as 2 4bit flags fields:
 *      Hex     Binary      Meaning
 *      x00     0000        Port off
 *      x01     0001        Port set to Input
 *      x02     0010        Port set to output
 *      x04     0100        Port set for MUXER
 *          
 */
#define ODAU_DIGITAL_PORT_OFF     0x00
#define ODAU_DIGITAL_INPB_INPA    0x11
#define ODAU_DIGITAL_OUTPB_INPA   0x21
#define ODAU_DIGITAL_OUTPB_OUTPA  0x22
#define ODAU_DIGITAL_OFFB_MUXA    0x04
#define ODAU_DIGITAL_INPB_MUXA    0x14
#define ODAU_DIGITAL_OUTPB_MUXA   0x24

/*
 * SCO-97-0020
 * New constants for user timer mode
 */
#define ODAU_TIMER_ONE_SHOT     1
#define ODAU_TIMER_RATE_GEN     2
#define ODAU_TIMER_SQUARE_WAVE  3
#define ODAU_TIMER_RETRIGGER    4

/*
 * SCO-97-0020
 *  New constants for selecting which timer to set
 */
#define ODAU_TIMER2             2

/*
 * Constants used to test ODAU digital port bits
 */
#define ODAU_DGTL_PT_OFF          0x00
#define ODAU_DGTL_PT_IN           0x01
#define ODAU_DGTL_PT_OUT          0x02
#define ODAU_DGTL_PT_MUX          0x04
#define ODAU_DGTL_INPUT           0x11

/* OPTOSCOPE_SETUP_COLL_MESSAGE
 * OPTOSCOPE_SETUP_COLL_COMMAND
 * SCO-95-0015
 * Added ulFlags field
 *      Flag ODAU_DIFFERENTIAL_FLAG defined
 * Added fScanFrequency field.
 */

struct OptoscopeSetupCollStruct
{
    long int        DataId;
    float           fFrameFrequency;
    float           fScanFrequency;
    long int        AnalogChannels;
    long int        AnalogGain;
    long int        DigitalMode;
    float           CollectionTime;
    float           PreTriggerTime;
    long int        StreamData;
    unsigned long   ulFlags;
};

#define ODAU_DIFFERENTIAL_FLAG  0x0001

/*
 * The following is a global structure is passed from the OPTOSCOPE the the
 * OPTOTRAK so that it may record the required collection information.
 */
struct ScopeCollectionParmsStruct
{
    long int    DataId;
    float       fFrequency;
    long int    PacketSize;
};

/* OPTOSCOPE_START_BUFF_MESSAGE
 * OPTOSCOPE_START_BUFF_COMMAND
 *
 * OPTOSCOPE_STOP_BUFF_MESSAGE
 * OPTOSCOPE_STOP_BUFF_COMMAND
 *
 * OPTOSCOPE_SHUTDOWN_MESSAGE
 * OPTOSCOPE_SHUTDOWN_COMMAND
 */

struct OptoscopeSetChnlAllStruct
{
    long int    status;
    long int    gain;
};

struct OptoscopeSetChnlSglStruct
{
    long int    status;
    long int    gain;
    long int    channel;
};

struct OptoscopeSetGainAllStruct
{
    long int    gain;
};

struct OptoscopeSetGainSglStruct
{
    long int    gain;
    long int    channel;
};

/* OPTOSCOPE_STATUS_MESSAGE
 * SCO-95-0015
 * Added ulFlags field
 * Added fScanFrequency field.
 */

struct OptoscopeStatusStruct
{
    long int        DataId;
    float           fFrameFrequency;
    float           fScanFrequency;
    long int        AnalogGain;
    long int        AnalogChannels;
    long int        DigitalMode;
    float           CollectionTime;
    float           PreTriggerTime;
    long int        StreamData;
    long int        ErrorFlags;
    unsigned long   ulFlags;
};

/*
 * SCO-95-0015
 * OPTOSCOPE_ANALOG_OUT_MESSAGE
 */
struct OptoscopeAnalogOutStruct
{
    float           fCh1Volts,
                    fCh2Volts;
    unsigned long   ulUpdateMask;
};

/*
 * SCO-95-0015
 * OPTOSCOPE_DIGITAL_OUT_MESSAGE
 */
struct OptoscopeDigitalOutStruct
{
    unsigned long   ulDigitalOut,
                    ulUpdateMask;
};

/*
 * SCO-97-0020
 * OPTOSCOPE_SET_TIMER_MESSAGE
 */
struct OptoscopeTimerDataStruct
{
    unsigned long   ulTimer,
                    ulMode,
                    ulVal;
};

/*
 * SCO-97-0020
 *  OPTOSCOPE_LOAD_FIFO_MESSAGE
 */
struct OptoscopeFiFoDataStruct
{
    unsigned long   ulEntries,
                    grulEntries[256];
};

/*
 * SCO-97-0020
 *   New data structure for OdauLoadControlFiFo()
 */
struct OdauControlWordStruct
{
    boolean         bDigitalInput,
                    bDifferential;
    unsigned        uGain,
                    uMuxer,
                    uChannel;
};
/***************************************************************
Name: REALTIME   -Details advanced data properitor calls for realtime option
****************************************************************/
/*
 * These are flags which are used with rigid bodies and the determination
 * of their transformations.
 *
 * SCO-99-0010: Added the flag OPTOTRAK_RIGID_ERR_MKR_SPREAD.
 */
#define OPTOTRAK_UNDETERMINED_FLAG      0x0001
#define OPTOTRAK_STATIC_XFRM_FLAG       0x0002
#define OPTOTRAK_STATIC_RIGID_FLAG      0x0004
#define OPTOTRAK_CONSTANT_RIGID_FLAG    0x0008
#define OPTOTRAK_NO_RIGID_CALCS_FLAG    0x0010
#define OPTOTRAK_DO_RIGID_CALCS_FLAG    0x0020
#define OPTOTRAK_QUATERN_RIGID_FLAG     0x0040
#define OPTOTRAK_ITERATIVE_RIGID_FLAG   0x0080
#define OPTOTRAK_SET_QUATERN_ERROR_FLAG 0x0100
#define OPTOTRAK_SET_MIN_MARKERS_FLAG   0x0200
#define OPTOTRAK_RIGID_ERR_MKR_SPREAD   0x0400
#define OPTOTRAK_RETURN_QUATERN_FLAG    0x1000
#define OPTOTRAK_RETURN_MATRIX_FLAG     0x2000
#define OPTOTRAK_RETURN_EULER_FLAG      0x4000
/*
 * Messages specific to the OPTOTRAK data proprietor
 */

/* OPTO_LATEST_RIGID_FRAME_MESSAGE
 *
 * OPTOTRAK_ADD_RIGID_MESSAGE
 */

struct OptotrakAddRigidStruct
{
    long int lnRigidId;         /* Unique identifier for rigid body. */
    long int lnStartMarker;     /* Start marker for rigid body. */
    long int lnNumberOfMarkers; /* Number of markers in rigid body. */
    long int lnMinimumMarkers;  /* Minimum number of markers for calcs. */
    float    fMax3dError;       /* Max allowable quaternion error. */
    long int lnFlags;           /* Flags for this rigid body. */
};

/* OPTOTRAK_DEL_RIGID_MESSAGE
 */

struct OptotrakDelRigidStruct
{
    long int lnRigidId;     /* Unique identifier for rigid body. */
};

/* OPTOTRAK_SET_RIGID_MESSAGE
 */

struct OptotrakSetRigidStruct
{
    long int lnRigidId;            /* Unique identifier for rigid body. */
    long int lnMarkerAngle;
    long int lnMinimumMarkers;     /* Minimum number of markers for calcs. */
    float    fMax3dError;
    float    fMaxSensorError;
    float    fMax3dRmsError;
    float    fMaxSensorRmsError;
    long int lnFlags;              /* New status flags for this rigid body. */
};

/* OPTOTRAK_ROTATE_RIGIDS_MESSAGE
 */

struct OptotrakRotateRigidsStruct
{
    long int        lnRotationMethod; /* Flags to control xfrm rotations. */
    long int        lnRigidId;        /* Rigid body to base xfrm rotations on. */
    transformation  dtEulerXfrm;      /* XFRM to base xfrm rotations on. */
};

/* OPTOTRAK_STOP_ROTATING_MESSAGE
 *
 * OPTOTRAK_ADD_NORMALS_MESSAGE
 */

struct OptotrakAddNormalsStruct
{
    long int lnRigidId;         /* Unique identifier for rigid body. */
};

/* OPTOTRAK_GET_RIG_STATUS_MESSAGE
 */

/*
 * Data ids you can receive back from the OPTOTRAK data proprietor
 */

/* OPTOTRAK_RIGID_STATUS_MESSAGE
 */

struct OptotrakRigidStatusStruct
{
    long int lnRigidBodies;     /* Number of rigid bodies in use */
};

/* OPTO_LATEST_RIGID_MESSAGE
 */

#define OPTO_RIGID_HEADER_SIZE            12
struct OptotrakRigidHeaderStruct
{
    long int    NumberOfRigids;   /* number of transforms following header */
    long int    StartFrameNumber; /* frame number of 3D data used */
    long int    flags;            /* current flag settings for OPTOTRAK */
};

union TransformationUnion
{
    RotationTransformation          rotation;
    transformation                  euler;
    QuatTransformation              quaternion;
};

struct OptotrakRigidStruct
{
    long int                    RigidId;         /* rigid body id xfrm is for */
    long int                    flags;           /* flags for this rigid body */
    float                       QuaternionError; /* quat rms error for xfrm */
    float                       IterativeError;  /* iter rms error for xfrm */
    union TransformationUnion   transformation;  /* latest calculated xfrm */
};
/***************************************************************
Name: ADMIN      -Section detailing interfacing with the OPTOTRAK Administrator
****************************************************************/
/*
 * Defines for commands to pass to the OPTOTRAK Administrator.
 */

/* OPTOTRAK_MODIFY_SYSTEM_MESSAGE
 * OPTOTRAK_MODIFY_SYSTEM_COMMAND
 */
struct OptotrakModifySystemStruct
{
	long int    threshold;
	float       fMarkerFrequency;
	float       DutyCycle;
	float       voltage;
	long int    MinimumGain;
};

/* OPTOTRAK_SETUP_COLL_MESSAGE
 * OPTOTRAK_SETUP_COLL_COMMAND
 */

/*
 * Flag definitions used in the OPTOTRAK_SETUP_COLL_MESSAGE.
 * Note: don't use the flag 0x1000 as it is taken by the constant
 *       OPTOTRAK_REALTIME_PRESENT_FLAG.
 */
#define OPTOTRAK_NO_INTERPOLATION_FLAG  0x0001
#define OPTOTRAK_FULL_DATA_FLAG         0x0002
#define OPTOTRAK_PIXEL_DATA_FLAG        0x0004
#define OPTOTRAK_MARKER_BY_MARKER_FLAG  0x0008
#define OPTOTRAK_ECHO_CALIBRATE_FLAG    0x0010
#define OPTOTRAK_BUFFER_RAW_FLAG        0x0020
#define OPTOTRAK_NO_FIRE_MARKERS_FLAG   0x0040
#define OPTOTRAK_STATIC_THRESHOLD_FLAG  0x0080
#define OPTOTRAK_WAVEFORM_DATA_FLAG     0x0100
#define OPTOTRAK_AUTO_DUTY_CYCLE_FLAG   0x0200
#define OPTOTRAK_EXTERNAL_CLOCK_FLAG    0x0400
#define OPTOTRAK_EXTERNAL_TRIGGER_FLAG  0x0800
#define OPTOTRAK_GET_NEXT_FRAME_FLAG    0x2000

/*
 * The following flags are set by the OPTOTRAK system itself.
 * They indicate (1) if the system has revision D/E Sensors,
 *               (2) if the system can perform real-time rigid bodies.
 *               (3) if the markers are on in the system.
 */
#define OPTOTRAK_REVISIOND_FLAG         0x80000000
#define OPTOTRAK_RIGID_CAPABLE_FLAG     0x08000000
#define OPTOTRAK_MARKERS_ACTIVE         0x04000000

struct OdauSetupStruct
{
	float       fOdauFrequency;
	long int    OdauChannels;
	long int    OdauGain;
	long int    OdauFlags;
};

struct OptotrakSetupCollStruct
{
	long int    DataId;
	long int    NumMarkers;
	float       fFrameFrequency;
	float       CollectionTime;
	float       PreTriggerTime;
	long int    StreamData;
	long int    flags;
	float       fOdauFrequency;
	long int    OdauChannels;
	long int    OdauGain;
	long int    OdauFlags;
};


/* OPTOTRAK_STOP_FIRING_MESSAGE
 *
 * OPTOTRAK_START_FIRING_MESSAGE
 * OPTOTRAK_START_FIRING_COMMAND
 *
 * OPTOTRAK_START_BUFF_MESSAGE
 * OPTOTRAK_START_BUFF_COMMAND
 *
 * OPTOTRAK_STOP_BUFF_MESSAGE
 * OPTOTRAK_STOP_BUFF_COMMAND
 *
 * OPTOTRAK_SHUTDOWN_MESSAGE
 * OPTOTRAK_SHUTDOWN_COMMAND
 *
 * OPTOTRAK_UNREGISTER_MESSAGE
 * OPTOTRAK_UNREGISTER_COMMAND
 *
 * OPTOTRAK_TRIGGER_COLLECTION_MESSAGE
 * OPTOTRAK_TRIGGER_COLLECTION_COMMAND
 *
 * OPTOTRAK_STROBER_TABLE_MESSAGE
 */
struct OptotrakStroberTableStruct
	{
	long int    Port1;
	long int    Port2;
	long int    Port3;
	long int    Port4;
	};

/*
 * Messages you can receive from the adminstrator.
 */

/* OPTOTRAK_STATUS_MESSAGE
 * OPTOTRAK_STATUS_COMMAND
 */

/*
 * Definitions for mode
 */
#define OPTOTRAK_NOTHING_MODE           0   /* No data generation */
#define OPTOTRAK_IDLING_MODE            1   /* Raw data generation in progress */
#define OPTOTRAK_GENERATING_MODE        2   /* Reconstructed data generation in progress */
#define OPTOTRAK_COLLECTING_MODE        3   /* Data collection in progress */
/*
 * The following structure is returned when asking for status
 * all the required system parameters. The only thing not included is the
 * file bufferring information.
 */
struct SystemCollectionParmsStruct
	{
	long int                                BufferSize;
	long int                                NumSensors;
	long int                                NumOptoscopes;
	long int                                NumControllers;
	long int                                CollectionType;
	struct OptotrakSetupCollStruct       CollParms;
	struct OptotrakModifySystemStruct    SysParms;
	struct ScopeCollectionParmsStruct    ScopeData[ MAX_OPTOSCOPES];
	struct AddressStruct                   WorkerAddress;
	};

/* OPTOTRAK_STATUS_CHANGED_MESSAGE
 * OPTOTRAK_STATUS_CHANGED_COMMAND
 */
/*****************************************************************

Name:               CENTPROD.H


*****************************************************************/
#define CENTPROD_INCLUDE

#define MAX_BUFFER_SIZE                 512
#define OPTIMAL_PEAK                    200

#ifndef CENTROID_OK
#define CENTROID_OK                     0
#define CENTROID_WAVEFORM_TOO_WIDE      1
#define CENTROID_PEAK_TOO_SMALL         2
#define CENTROID_PEAK_TOO_LARGE         3
#define CENTROID_WAVEFORM_OFF_DEVICE    4
#define CENTROID_FELL_BEHIND            5
#define CENTROID_LAST_CENTROID_BAD      6
#define CENTROID_BUFFER_OVERFLOW        7
#define CENTROID_MISSED_CCD             8
#endif

/*****************************************************************
External Variables and Routines
*****************************************************************/
struct  CentroidBufferStruct
{
    float       centroid;             /* Calculated centroid */
    char        Peak;                 /* Peak value 0 to 255 */
    char        gain;                 /* Gain setting for this collection */
    char        ErrorCode;            /* Error in centtroid calculation */
    char        PeakNibble;           /* Low Nibble of Peak value (Revd only) */
};
/*************************************************************************
OPTOLIB     -Describes calls to OPTOLIB routines.

**************************************************************************/

/**************************************************************************
  Defines
**************************************************************************/

#define DEFAULT_LINK_ADDRESS 784

/*
 * The error codes that exist
 */
#define OPTO_NO_ERROR_CODE          0
#define OPTO_SYSTEM_ERROR_CODE      1000
#define OPTO_USER_ERROR_CODE        2000

/*
 * Flags for controlling the setup of the message passing layer on the
 * PC side.
 */
#define OPTO_LOG_ERRORS_FLAG          0x0001
#define OPTO_SECONDARY_HOST_FLAG      0x0002
#define OPTO_ASCII_RESPONSE_FLAG      0x0004
#define OPTO_LOG_MESSAGES_FLAG        0x0008
#define OPTO_LOG_DEBUG_FLAG           0x0010

/*
 * Constants for raw files which can be converted.
 */
#define OPTOTRAK_RAW    1
#define ANALOG_RAW      2

/*
 * Constants for modes in which files can be opened.
 */
#define OPEN_READ       1
#define OPEN_WRITE      2

/*
 * Maximum constants for the processes we will have to keep track
 * of in the optoappl software.  Make room for one address per node,
 * and an extra for our data proprietor.
 */
#define MAX_OPTOTRAKS         1
#define MAX_DATA_PROPRIETORS  1
#define MAX_ODAUS             4
#define MAX_PROCESS_ADDRESSES (MAX_NODES + 1)

/*
 * Constants for keeping track of whick process the application wants to
 * communicate with.
 *
 * SCO-00-0001: Added data buffer overwrite flag.
 */
#define OPTOTRAK                            0
#define DATA_PROPRIETOR                     1
#define ODAU1                               2
#define ODAU2                               3
#define ODAU3                               4
#define ODAU4                               5
#define SENSOR_PROP1                        6
#define OPTOTRAK_DATA_BUFFER_OVERWRITE_FLAG 0x8000

/*
 * Flags for controlling the put message modules.
 */
#define OPTO_PROCESS_BITS       0x007F
#define OPTO_NO_REPLY_FLAG      0x0080

/*
 * Pointer definitions for spooling to memory.
 */
#if IBMPC
typedef void huge *         SpoolPtrType;
#else
typedef void *              SpoolPtrType;
#endif

/*
 * SCO-98-0023: added flag assignments for controlling blocking in
 * real-time data retrieval routines and for on-host 3D and 6D
 * conversions
 */

#define OPTO_LIB_POLL_REAL_DATA    0x0001
#define OPTO_CONVERT_ON_HOST       0x0002
#define OPTO_RIGID_ON_HOST         0x0004
#define OPTO_USE_INTERNAL_NIF      0x0008

/**************************************************************************
 External Variables
**************************************************************************/

/*
 * String for returning error messages.
 * SCO-97-0020
 *  Exported by changing extern to NDIEXPORT
 * SCO-97-0050
 *  Unexported; now accessed by exported function OptotrakGetErrorString().
 *  Increased the size to accomodate PutMsg() strings.
 */
#define MAX_ERROR_STRING_LENGTH 2047
extern char
    szNDErrorString[MAX_ERROR_STRING_LENGTH + 1];

/**************************************************************************
 Routine Definitions
**************************************************************************/

CPLUSPLUS_START

/*
 * Routines in assembler module.
 */
boolean far
    SendBlock( int offset, void far *buffer, unsigned size );

boolean far
    ReceiveBlock( int offset, void far *buffer, unsigned size );

int far
    DSEG( void );

/*
 * SCO-97-0050:
 * Moved Low Level communications driver routine prototypes to NDLink.h
 */

/*
 * Message Based Interface prototypes.
 */
extern int
    OptoGetError( int nSourceProcess, char *pszErrorStr, int *pnErrorCode ),
    OptoSetupMessageSystem( unsigned int uOffset, unsigned int uFlags ),
    OptoInputMessageAvailable( void ),
    OptoGetMessageData( void *pData, double dTimeoutTime ),
    OptoPutMessage( int           nDestination,
                    unsigned int  uMessageId,
                    void         *pMessageData,
                    unsigned int  uDataSize,
                    void         *pRetPtr ),
    OptoShutdownMessageSystem( void );

/*
 * Routine Based Interface prototypes.
 * SCO-97-0033
 *  changed prototype from extern int NDIEXPORT
 * SCO-97-0050
 *  changed prototype to the more general NDI_DECL1 type NDI_DECL2 name
 */
NDI_DECL1 int
    NDI_DECL2 TransputerLoadSystem( char *pszNifFile ),
    NDI_DECL2 TransputerInitializeSystem( unsigned int uFlags ),
    NDI_DECL2 TransputerShutdownSystem( void ),
    NDI_DECL2 TransputerDetermineSystemCfg( char *pszInputLogFile );
/*
 * SCO-97-0033
 *  changed prototype from extern int NDIEXPORT
 * SCO-97-0050
 *  changed prototype to the more general NDI_DECL1 type NDI_DECL2 name
 */
NDI_DECL1 int
    NDI_DECL2 OptotrakLoadCameraParameters( char *pszCamFile ),
    NDI_DECL2 OptotrakSetupCollectionFromFile( char *pszCollectFile ),
    NDI_DECL2 OptotrakSetupCollection( int   nMarkers,
                                       float fFrameFrequency,
                                       float fMarkerFrequency,
                                       int   nThreshold,
                                       int   nMinimumGain,
                                       int   nStreamData,
                                       float fDutyCycle,
                                       float fVoltage,
                                       float fCollectionTime,
                                       float fPreTriggerTime,
                                       int   nFlags ),
    NDI_DECL2 OptotrakActivateMarkers( void ),
    NDI_DECL2 OptotrakDeActivateMarkers( void ),
    NDI_DECL2 OptotrakGetStatus( int   *pnNumSensors,
                                 int   *pnNumOdaus,
                                 int   *pnNumRigidBodies,
                                 int   *pnMarkers,
                                 float *pfFrameFrequency,
                                 float *pfMarkerFrequency,
                                 int   *pnThreshold,
                                 int   *pnMinimumGain,
                                 int   *pnStreamData,
                                 float *pfDutyCycle,
                                 float *pfVoltage,
                                 float *pfCollectionTime,
                                 float *pfPreTriggerTime,
                                 int   *pnFlags ),
    NDI_DECL2 OptotrakChangeCameraFOR( char       *pszInputCamFile,
                                       int         nNumMarkers,
                                       Position3d *pdtMeasuredPositions,
                                       Position3d *pdtAlignedPositions,
                                       char       *pszAlignedCamFile,
                                       Position3d *pdt3dErrors,
                                       float      *pfRmsError ),
    NDI_DECL2 OptotrakSetStroberPortTable( int nPort1,
                                           int nPort2,
                                           int nPort3,
                                           int nPort4 ),
    NDI_DECL2 OptotrakSaveCollectionToFile( char *pszCollectFile ),
    /*
     * SCO-97-0050
     *  Added OptotrakGetErrorString()
     *        OptotrakSetProcessingFlags()
     *
     * SCO-98-0023
     *  Changed OptotrakSetProcessingFlags() to a single argument routine
     */
    NDI_DECL2 OptotrakGetErrorString( char* szErrorString, int nBufferSize ),
    NDI_DECL2 OptotrakSetProcessingFlags( unsigned int uFlags ),
    /*
     * SCO-99-0010
     *  Added OptotrakConvertRawTo3D()
     *        OptotrakConvertTransforms()
     *        OptotrakGetNodeInfo()
     */
    NDI_DECL2 OptotrakConvertRawTo3D( unsigned int *puElements,
                                      void         *pSensorReadings,
                                      Position3d   *pdt3DPositions ),
    NDI_DECL2 OptotrakConvertTransforms( unsigned int               *puElements,
                                         struct OptotrakRigidStruct *pDataDest6D,
                                         Position3d                 *pDataDest3 ),
    NDI_DECL2 OptotrakGetNodeInfo( int   nNodeId,
                                   struct OptoNodeInfoStruct *pdtNodeInfo ),
    /*
     * SCO-00-0001
     *  Added OptotrakSetCameraParameters()
     *        OptotrakGetCameraParameterStatus()
     *        OptotrakReadAppParms()
     *        OptotrakSaveAppParms()
     *        OptotrakDeleteAppParms()
     */
    NDI_DECL2 OptotrakSetCameraParameters( int nMarkerType,
                                           int nWaveLength,
                                           int nModelType ),
    NDI_DECL2 OptotrakGetCameraParameterStatus( int  *pnCurrentMarkerType,
                                                int  *pnCurrentWaveLength,
                                                int  *pnCurrentModelType,
                                                char *szStatus,
                                                int   nStatusLength ),
    NDI_DECL2 OptotrakReadAppParms( char        *pszParmFile,
                                    char        *pszSection,
                                    AppParmInfo *pParmInfo ),
    NDI_DECL2 OptotrakSaveAppParms( char        *pszParmFile,
                                    char        *pszSection,
                                    AppParmInfo *pParmInfo ),
    NDI_DECL2 OptotrakDeleteAppParms( char *pszParmFile,
                                      char *pszSection ),
    NDI_DECL2 OdauSaveCollectionToFile( char *pszCollectFile ),
    NDI_DECL2 OdauSetupCollectionFromFile( char *pszCollectFile ),
    /*
     * SCO-97-0020
     *  Added OdauSetTimer()
     *        OdauLoadCtlFiFo()
     */
    NDI_DECL2 OdauSetTimer( int           nOdauId,
                            unsigned      uTimer,
                            unsigned      uMode,
                            unsigned long ulVal ),
    NDI_DECL2 OdauLoadControlFiFo( int                           nOdauId,
                                   unsigned                      uEntries,
                                   struct OdauControlWordStruct *pCtlWords ),
    NDI_DECL2 OdauSetAnalogOutputs( int       nOdauId,
                                    float    *pfVoltage1,
                                    float    *pfVoltage2,
                                    unsigned  uChangeMask ),
    NDI_DECL2 OdauSetDigitalOutputs( int       nOdauId,
                                     unsigned *puDigitalOut,
                                     unsigned  uUpdateMask ),
    NDI_DECL2 OdauSetupCollection( int      nOdauId,
                                   int      nChannels,
                                   int      nGain,
                                   int      nDigitalMode,
                                   float    fFrameFrequency,
                                   float    fScanFrequency,
                                   int      nStreamData,
                                   float    fCollectionTime,
                                   float    fPreTriggerTime,
                                   unsigned uFlags ),
    NDI_DECL2 OdauGetStatus( int       nOdauId,
                             int      *pnChannels,
                             int      *pnGain,
                             int      *pnDigitalMode,
                             float    *pfFrameFrequency,
                             float    *pfScanFrequency,
                             int      *pnStreamData,
                             float    *pfCollectionTime,
                             float    *pfPreTriggerTime,
                             unsigned *puCollFlags,
                             int      *pnFlags ),
    NDI_DECL2 RigidBodyAdd( int    nRigidBodyId,
                            int    nStartMarker,
                            int    nNumMarkers,
                            float *pRigidCoordinates,
                            float *pNormalCoordinates,
                            int    nFlags ),
    NDI_DECL2 RigidBodyAddFromFile( int   nRigidBodyId,
                                    int   nStartMarker,
                                    char *pszRigFile,
                                    int   nFlags ),
    NDI_DECL2 RigidBodyChangeSettings( int   nRigidBodyId,
                                       int   nMinMarkers,
                                       int   nMaxMarkersAngle,
                                       float fMax3dError,
                                       float fMaxSensorError,
                                       float fMax3dRmsError,
                                       float fMaxSensorRmsError,
                                       int   nFlags ),
    NDI_DECL2 RigidBodyDelete( int nRigidBodyId ),
    NDI_DECL2 RigidBodyChangeFOR( int nRigidId, int nRotationMethod ),
    NDI_DECL2 DataGetLatest3D( unsigned int *puFrameNumber,
                               unsigned int *puElements,
                               unsigned int *puFlags,
                               void         *pDataDest ),
    NDI_DECL2 DataGetLatestCentroid( unsigned int *puFrameNumber,
                               unsigned int *puElements,
                               unsigned int *puFlags,
                               void         *pDataDest ),
    NDI_DECL2 DataGetLatestRaw( unsigned int *puFrameNumber,
                                unsigned int *puElements,
                                unsigned int *puFlags,
                                void         *pDataDest ),
    NDI_DECL2 DataGetLatestTransforms( unsigned int *puFrameNumber,
                                       unsigned int *puElements,
                                       unsigned int *puFlags,
                                       void         *pDataDest ),
    NDI_DECL2 DataGetLatestOdauRaw( int nOdauId,
                                    unsigned int *puFrameNumber,
                                    unsigned int *puElements,
                                    unsigned int *puFlags,
                                    void         *pDataDest ),
    NDI_DECL2 RequestLatest3D( void ),
    NDI_DECL2 RequestLatestRaw( void ),
    NDI_DECL2 RequestLatestCentroid( void ),
    NDI_DECL2 RequestLatestTransforms( void ),
    NDI_DECL2 RequestLatestOdauRaw( int nOdauId ),
    NDI_DECL2 DataIsReady( void ),
    NDI_DECL2 ReceiveLatestData( unsigned int *uFrameNumber,
                                 unsigned int *uElements,
                                 unsigned int *uFlags,
                                 void         *pDataDest ),
    NDI_DECL2 DataReceiveLatest3D( unsigned int *puFrameNumber,
                                   unsigned int *puElements,
                                   unsigned int *puFlags,
                                   Position3d   *pDataDest ),
    NDI_DECL2 DataReceiveLatestRaw( unsigned int *puFrameNumber,
                                    unsigned int *puElements,
                                    unsigned int *puFlags,
                                    void         *pDataDest ),
    NDI_DECL2 DataReceiveLatestCentroid( unsigned int *puFrameNumber,
                                    unsigned int *puElements,
                                    unsigned int *puFlags,
                                    void         *pDataBuff ),
    NDI_DECL2 DataReceiveLatestTransforms( unsigned int *puFrameNumber,
                                           unsigned int *puElements,
                                           unsigned int *puFlags,
                                           void         *pDataDest ),
    NDI_DECL2 DataReceiveLatestOdauRaw( unsigned int *puFrameNumber,
                                        unsigned int *puElements,
                                        unsigned int *puFlags,
                                        int          *pDataDest ),
    NDI_DECL2
        DataGetLatestTransforms2( unsigned int               *puFrameNumber,
                                  unsigned int               *puElements,
                                  unsigned int               *puFlags,
                                  struct OptotrakRigidStruct *pDataDest6D,
                                  Position3d                 *pDataDest3D ),
    NDI_DECL2
        DataReceiveLatestTransforms2( unsigned int               *puFrameNumber,
                                      unsigned int               *puElements,
                                      unsigned int               *puFlags,
                                      struct OptotrakRigidStruct *pDataDest6D,
                                      Position3d                 *pDataDest3D );

/*
 * SCO-97-0050
 *  Exported the get next routines
 * SCO-99-0062
 *  Added RequestNextCentroid, and DataGetNextCentroid
 */
NDI_DECL1 int
    NDI_DECL2 RequestNext3D( void ),
    NDI_DECL2 RequestNextCentroid( void ),
    NDI_DECL2 RequestNextRaw( void ),
    NDI_DECL2 RequestNextTransforms( void ),
    NDI_DECL2 RequestNextOdauRaw( int nOdauId ),
    NDI_DECL2 DataGetNext3D( unsigned int *puFrameNumber,
                             unsigned int *puElements,
                             unsigned int *puFlags,
                             void         *pDataDest ),
    NDI_DECL2 DataGetNextCentroid( unsigned int *puFrameNumber,
                                   unsigned int *puElements,
                                   unsigned int *puFlags,
                                   void         *pDataDest ),
    NDI_DECL2 DataGetNextRaw( unsigned int *puFrameNumber,
                              unsigned int *puElements,
                              unsigned int *puFlags,
                              void         *pDataDest ),
    NDI_DECL2 DataGetNextTransforms( unsigned int *puFrameNumber,
                                     unsigned int *puElements,
                                     unsigned int *puFlags,
                                     void         *pDataDest ),
    NDI_DECL2
        DataGetNextTransforms2( unsigned int               *puFrameNumber,
                                unsigned int               *puElements,
                                unsigned int               *puFlags,
                                struct OptotrakRigidStruct *pDataDest6D,
                                Position3d                 *pDataDest3D ),
    NDI_DECL2 DataGetNextOdauRaw( int nOdauId,
                                  unsigned int *puFrameNumber,
                                  unsigned int *puElements,
                                  unsigned int *puFlags,
                                  void         *pDataDest );

/*
 * SCO-97-0033
 *  changed prototype from extern int NDIEXPORT
 * SCO-97-0050
 *  changed prototype to the more general NDI_DECL1 type NDI_DECL2 name
 */
NDI_DECL1 int
    NDI_DECL2 DataBufferInitializeFile( unsigned int  uDataId,
                                        char         *pszFileName ),
    NDI_DECL2 DataBufferInitializeMem( unsigned int uDataId,
                                       SpoolPtrType pMemory ),
    NDI_DECL2 DataBufferStart( void ),
    NDI_DECL2 DataBufferStop( void ),
    NDI_DECL2 DataBufferSpoolData( unsigned int  *puSpoolStatus ),
    NDI_DECL2 DataBufferWriteData( unsigned int  *puRealtimeData,
                                   unsigned int  *puSpoolComplete,
                                   unsigned int  *puSpoolStatus,
                                   unsigned long *pulFramesBuffered ),
    NDI_DECL2 DataBufferAbortSpooling( void );

/*
 * SCO-97-0033
 *  changed prototype from extern int NDIEXPORT
 * SCO-97-0050
 *  changed prototype to the more general NDI_DECL1 type NDI_DECL2 name
 */
NDI_DECL1 int
    NDI_DECL2 FileConvert( char         *pszInputFilename,
                           char         *pszOutputFilename,
                           unsigned int  uFileType ),
    NDI_DECL2 FileOpen( char          *pszFilename,
                        unsigned int   uFileId,
                        unsigned int   uFileMode,
                        int           *pnItems,
                        int           *pnSubItems,
                        long int      *plnFrames,
                        float         *pfFrequency,
                        char          *pszComments,
                        void         **pFileHeader ),
    NDI_DECL2 FileRead( unsigned int  uFileId,
                        long int      lnStartFrame,
                        unsigned int  uNumberOfFrames,
                        void         *pDataDest ),
    NDI_DECL2 FileWrite( unsigned int  uFileId,
                         long int      lnStartFrame,
                         unsigned int  uNumberOfFrames,
                         void         *pDataSrc ),
    NDI_DECL2 FileClose( unsigned int uFileId ),
    NDI_DECL2 FileOpenAll( char          *pszFilename,
                           unsigned int   uFileId,
                           unsigned int   uFileMode,
                           int           *pnItems,
                           int           *pnSubItems,
                           int           *pnCharSubItems,
                           int           *pnIntSubItems,
                           int           *pnDoubleSubItems,
                           long int      *plnFrames,
                           float         *pfFrequency,
                           char          *pszComments,
                           void         **pFileHeader ),
    NDI_DECL2 FileReadAll( unsigned int  uFileId,
                           long int      lnStartFrame,
                           unsigned int  uNumberOfFrames,
                           void         *pDataDestFloat,
                           void         *pDataDestChar,
                           void         *pDataDestInt,
                           void         *pDataDestDouble ),
    NDI_DECL2 FileWriteAll( unsigned int  uFileId,
                            long int      lnStartFrame,
                            unsigned int  uNumberOfFrames,
                            void         *pDataSrcFloat,
                            void         *pDataSrcChar,
                            void         *pDataSrcInt,
                            void         *pDataSrcDouble ),
    NDI_DECL2 FileCloseAll( unsigned int uFileId );

/*
 * SCO-97-0050: Exported the following routines from zcammath.h.
 */
NDI_DECL1 void
    NDI_DECL2 CombineXfrms( transformation *xfrm1_ptr,
                            transformation *xfrm2_ptr,
                            transformation *NewXfrmPtr ),
    NDI_DECL2 CvtQuatToRotationMatrix( struct QuatRotationStruct *QuatPtr,
                                       RotationMatrixType         r ),
    NDI_DECL2 CvtRotationMatrixToQuat( struct QuatRotationStruct *QuatPtr,
                                       RotationMatrixType         r ),
    NDI_DECL2 DetermineEuler( RotationMatrixType  r,
                              rotation           *RotationAnglePtr ),
    NDI_DECL2 DetermineR( rotation *RotationAnglePtr,
                          RealType ( *RotationMatrix )[ 3] ),
    NDI_DECL2 InverseXfrm( transformation *InputXfrmPtr,
                           transformation *OutputXfrmPtr ),
    NDI_DECL2 TransformPoint( RealType   ( *RotationMatrix )[ 3],
                              Position3d *translation,
                              Position3d *OriginalPositionPtr,
                              Position3d *RotatedPositionPtr );

#ifdef PACK_UNPACK
extern unsigned
    PackAddress( struct AddressStruct *p,
                 unsigned char        *pchBuff,
                 unsigned              uBuffSize ),
    UnPackAddress( struct AddressStruct *p,
                   unsigned char        *pchBuff,
                   unsigned              uBuffSize ),
    PackMessageHeader( struct MessageHeaderStruct *p,
                       unsigned char              *pchBuff,
                       unsigned                    uBuffSize ),
    UnPackMessageHeader( struct MessageHeaderStruct *p,
                         unsigned char              *pchBuff,
                         unsigned                    uBuffSize ),
    PackMessage( struct MessageStruct *p,
                 unsigned char        *pchBuff,
                 unsigned              uBuffSize ),
    UnPackMessage( struct MessageStruct *p,
                   unsigned char        *pchBuff,
                   unsigned              uBuffSize ),
    PackProcessSetup( struct ProcessSetupStruct *p,
                      unsigned char             *pchBuff,
                      unsigned                   uBuffSize ),
    UnPackProcessSetup( struct ProcessSetupStruct *p,
                        unsigned char             *pchBuff,
                        unsigned                   uBuffSize ),
    PackNodeSetup( struct NodeSetupStruct *p,
                   unsigned char          *pchBuff,
                   unsigned                uBuffSize ),
    UnPackNodeSetup( struct NodeSetupStruct *p,
                     unsigned char          *pchBuff,
                     unsigned                uBuffSize ),
    PackOptotrakRegister( struct OptotrakRegisterStruct *p,
                          unsigned char                 *pchBuff,
                          unsigned                       uBuffSize ),
    UnPackOptotrakRegister( struct OptotrakRegisterStruct *p,
                            unsigned char                 *pchBuff,
                            unsigned                       uBuffSize ),
    PackOptoUnsuccessful( struct OptoUnsuccessfulStruct *p,
                          unsigned char                 *pchBuff,
                          unsigned                       uBuffSize ),
    UnPackOptoUnsuccessful( struct OptoUnsuccessfulStruct *p,
                            unsigned char                 *pchBuff,
                            unsigned                       uBuffSize ),
    PackOptoDataHeader( struct OptoDataHeaderStruct *p,
                        unsigned char               *pchBuff,
                        unsigned                     uBuffSize ),
    UnPackOptoDataHeader( struct OptoDataHeaderStruct *p,
                          unsigned char               *pchBuff,
                          unsigned                     uBuffSize ),
    PackOptotrak_wave_head_( struct optotrak_wave_head_struct *p,
                             unsigned char                    *pchBuff,
                             unsigned                          uBuffSize ),
    UnPackOptotrak_wave_head_( struct optotrak_wave_head_struct *p,
                               unsigned char                    *pchBuff,
                               unsigned                          uBuffSize ),
    PackOptoTransformData( struct OptoTransformDataStruct *p,
                           unsigned char                  *pchBuff,
                           unsigned                        uBuffSize ),
    UnPackOptoTransformData( struct OptoTransformDataStruct *p,
                             unsigned char                  *pchBuff,
                             unsigned                        uBuffSize ),
    PackOptoscopeSetupColl( struct OptoscopeSetupCollStruct *p,
                            unsigned char                   *pchBuff,
                            unsigned                         uBuffSize ),
    UnPackOptoscopeSetupColl( struct OptoscopeSetupCollStruct *p,
                              unsigned char                   *pchBuff,
                              unsigned                         uBuffSize ),
    PackScopeCollectionParms( struct ScopeCollectionParmsStruct *p,
                              unsigned char                     *pchBuff,
                              unsigned                           uBuffSize ),
    UnPackScopeCollectionParms( struct ScopeCollectionParmsStruct *p,
                                unsigned char                     *pchBuff,
                                unsigned                           uBuffSize ),
    PackOptoscopeSetChnlAll( struct OptoscopeSetChnlAllStruct *p,
                             unsigned char                    *pchBuff,
                             unsigned                          uBuffSize ),
    UnPackOptoscopeSetChnlAll( struct OptoscopeSetChnlAllStruct *p,
                               unsigned char                    *pchBuff,
                               unsigned                          uBuffSize ),
    PackOptoscopeSetChnlSgl( struct OptoscopeSetChnlSglStruct *p,
                             unsigned char                    *pchBuff,
                             unsigned                          uBuffSize ),
    UnPackOptoscopeSetChnlSgl( struct OptoscopeSetChnlSglStruct *p,
                               unsigned char                    *pchBuff,
                               unsigned                          uBuffSize ),
    PackOptoscopeSetGainAll( struct OptoscopeSetGainAllStruct *p,
                             unsigned char                    *pchBuff,
                             unsigned                          uBuffSize ),
    UnPackOptoscopeSetGainAll( struct OptoscopeSetGainAllStruct *p,
                               unsigned char                    *pchBuff,
                               unsigned                          uBuffSize ),
    PackOptoscopeSetGainSgl( struct OptoscopeSetGainSglStruct *p,
                             unsigned char                    *pchBuff,
                             unsigned                          uBuffSize ),
    UnPackOptoscopeSetGainSgl( struct OptoscopeSetGainSglStruct *p,
                               unsigned char                    *pchBuff,
                               unsigned                          uBuffSize ),
    PackOptoscopeStatus( struct OptoscopeStatusStruct *p,
                         unsigned char                *pchBuff,
                         unsigned                      uBuffSize ),
    UnPackOptoscopeStatus( struct OptoscopeStatusStruct *p,
                           unsigned char                *pchBuff,
                           unsigned                      uBuffSize ),
    PackOptotrakAddRigid( struct OptotrakAddRigidStruct *p,
                          unsigned char                 *pchBuff,
                          unsigned                       uBuffSize ),
    UnPackOptotrakAddRigid( struct OptotrakAddRigidStruct *p,
                            unsigned char                 *pchBuff,
                            unsigned                       uBuffSize ),
    PackOptotrakDelRigid( struct OptotrakDelRigidStruct *p,
                          unsigned char                 *pchBuff,
                          unsigned                       uBuffSize ),
    UnPackOptotrakDelRigid( struct OptotrakDelRigidStruct *p,
                            unsigned char                 *pchBuff,
                            unsigned                       uBuffSize ),
    PackOptotrakSetRigid( struct OptotrakSetRigidStruct *p,
                          unsigned char                 *pchBuff,
                          unsigned                       uBuffSize ),
    UnPackOptotrakSetRigid( struct OptotrakSetRigidStruct *p,
                            unsigned char                 *pchBuff,
                            unsigned                       uBuffSize ),
    PackOptotrakRotateRigids( struct OptotrakRotateRigidsStruct *p,
                              unsigned char                     *pchBuff,
                              unsigned                           uBuffSize ),
    UnPackOptotrakRotateRigids( struct OptotrakRotateRigidsStruct *p,
                                unsigned char                     *pchBuff,
                                unsigned                           uBuffSize ),
    PackOptotrakAddNormals( struct OptotrakAddNormalsStruct *p,
                            unsigned char                   *pchBuff,
                            unsigned                         uBuffSize ),
    UnPackOptotrakAddNormals( struct OptotrakAddNormalsStruct *p,
                              unsigned char                   *pchBuff,
                              unsigned                         uBuffSize ),
    PackOptotrakRigidStatus( struct OptotrakRigidStatusStruct *p,
                             unsigned char                    *pchBuff,
                             unsigned                          uBuffSize ),
    UnPackOptotrakRigidStatus( struct OptotrakRigidStatusStruct *p,
                               unsigned char                    *pchBuff,
                               unsigned                          uBuffSize ),
    PackOptotrakRigidHeader( struct OptotrakRigidHeaderStruct *p,
                             unsigned char                    *pchBuff,
                             unsigned                          uBuffSize ),
    UnPackOptotrakRigidHeader( struct OptotrakRigidHeaderStruct *p,
                               unsigned char                    *pchBuff,
                               unsigned                          uBuffSize ),
    PackOptotrakRigid( struct OptotrakRigidStruct *p,
                       unsigned char              *pchBuff,
                       unsigned                    uBuffSize ),
    UnPackOptotrakRigid( struct OptotrakRigidStruct *p,
                         unsigned char              *pchBuff,
                         unsigned                    uBuffSize ),
    PackOptotrakModifySystem( struct OptotrakModifySystemStruct *p,
                              unsigned char                     *pchBuff,
                              unsigned                           uBuffSize ),
    UnPackOptotrakModifySystem( struct OptotrakModifySystemStruct *p,
                                unsigned char                     *pchBuff,
                                unsigned                           uBuffSize ),
    PackOdauSetup( struct OdauSetupStruct *p,
                   unsigned char          *pchBuff,
                   unsigned                uBuffSize ),
    UnPackOdauSetup( struct OdauSetupStruct *p,
                     unsigned char          *pchBuff,
                     unsigned                uBuffSize ),
    PackOptotrakStroberTable( struct OptotrakStroberTableStruct *p,
                              unsigned char                     *pchBuff,
                              unsigned                           uBuffSize ),
    PackOptotrakSetupColl( struct OptotrakSetupCollStruct *p,
                           unsigned char                  *pchBuff,
                           unsigned                        uBuffSize ),
    UnPackOptotrakStroberTable( struct OptotrakStroberTableStruct *p,
                                unsigned char                     *pchBuff,
                                unsigned                           uBuffSize ),
    UnPackOptotrakSetupColl( struct OptotrakSetupCollStruct *p,
                             unsigned char                  *pchBuff,
                             unsigned                        uBuffSize ),
    PackSystemCollectionParms( struct SystemCollectionParmsStruct *p,
                               unsigned char                      *pchBuff,
                               unsigned                            uBuffSize ),
    UnPackSystemCollectionParms( struct SystemCollectionParmsStruct *p,
                                 unsigned char                      *pchBuff,
                                 unsigned                            uBuffSize ),
    PackCentroidBuffer( struct CentroidBufferStruct *p,
                        unsigned char               *pchBuff,
                        unsigned                     uBuffSize ),
    UnPackCentroidBuffer( struct CentroidBufferStruct *p,
                          unsigned char               *pchBuff,
                          unsigned                     uBuffSize ),
    UnPackOptoNodeInfo( struct OptoNodeInfoStruct *p,
                          unsigned char           *pchBuff,
                          unsigned                 uBuffSize );
#endif
CPLUSPLUS_END

#endif /* INCLUDE_NDOPTO */

