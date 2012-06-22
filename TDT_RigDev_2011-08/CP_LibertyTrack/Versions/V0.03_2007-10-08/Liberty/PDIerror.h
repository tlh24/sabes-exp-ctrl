/////////////////////////////////////////////////////////////////////
// Polhemus Inc.,  www.polhemus.com
// © 2003 Alken, Inc. dba Polhemus, All Rights Reserved
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
//
//  Filename:           $Workfile: PDIerror.h $
//
//  Project Name:       Polhemus Developer Interface  
//
//  Description:        Error Codes
//
//  VSS $Header: /PIDevTools/Inc/PDIerror.h 7     12/16/04 12:15p Sgagnon $  
//
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
#ifndef _PDIERROR_H_
#define _PDIERROR_H_

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

#define PI_ERROR_BAND_MASK      0xffff0000
#define PI_ERROR_LEVEL_MASK		0x0000f000
#define PI_HOST_SYS_ERROR_BAND  0x20010000
#define PI_HOST_ERROR_BAND      0x20020000
#define PI_DEVICE_ERROR_BAND    0x20040000
#define PI_API_ERROR_BAND       0x20080000

#define IS_PI_SYS_ERROR( e )	(( e & PI_ERROR_BAND_MASK ) == PI_HOST_SYS_ERROR_BAND)
#define IS_PI_HOST_ERROR( e )	(( e & PI_ERROR_BAND_MASK ) == PI_HOST_ERROR_BAND)
#define IS_PI_DEVICE_ERROR( e )	(( e & PI_ERROR_BAND_MASK ) == PI_DEVICE_ERROR_BAND)
#define IS_PI_API_ERROR( e )	(( e & PI_ERROR_BAND_MASK ) == PI_API_ERROR_BAND)
#define ERR_LEVEL( e )			(( e & PI_ERROR_LEVEL_MASK ) >> 12)

typedef enum 
{
    PI_NOERROR=0     // equivalent results, success & noerror
    , PI_HOST_SYS_ERROR = PI_HOST_SYS_ERROR_BAND
    , PI_HOST_SYS_CNX_USB_CREATE_ERROR
    , PI_HOST_SYS_CNX_SER_CREATE_ERROR
    , PI_HOST_SYS_WRITE_ERROR
    , PI_HOST_SYS_WAIT_WRITE_ERROR
    , PI_HOST_SYS_WAIT_READ_ERROR
    , PI_HOST_SYS_READ_ERROR
    , PI_HOST_SYS_CLOSE_ERROR
    , PI_HOST_SYS_PIPE_CREATE_ERROR
    , PI_HOST_SYS_PIPE_DISC_ERROR
    , PI_HOST_SYS_PIPE_WRITE_ERROR
    , PI_HOST_SYS_CREATE_THREAD_ERROR
    , PI_HOST_SYS_GET_THREAD_STATUS_ERROR
	, PI_HOST_SYS_TERM_THREAD_ERROR
    , PI_HOST_SYS_DEVIO_ERROR

    , PI_HOST_ERROR   = PI_HOST_ERROR_BAND 
    , PI_HOST_NOCNX_ERROR
    , PI_HOST_BUILD_CMD_ERROR
    , PI_HOST_PARSE_RSP_ERROR
	, PI_HOST_STATE_ERROR
	, PI_HOST_NO_RESP
	, PI_HOST_FRAME_ERROR
	, PI_HOST_ASYNCINPROG_ERROR
	, PI_HOST_OVERFLOW_ERROR
	, PI_HOST_FRAME_IGNORED
	, PI_HOST_SERNUM_NOT_FOUND
	, PI_HOST_CONT_CMD_SENT = PI_HOST_ERROR_BAND + 0x1001

    , PI_DEVICE_ERROR = PI_DEVICE_ERROR_BAND
	, PI_DEVICE_NOT_DETECTED
    , PI_DEVICE_ERROR_FLAG
    , PI_DEVICE_CMD_FAILED
	, PI_DEVICE_NOT_RECOG
	, PI_DEVICE_NOT_FOUND
	, PI_DEVICE_INFO = PI_DEVICE_ERROR_BAND + 0x1001

    , PI_API_ERROR = PI_API_ERROR_BAND
    , PI_API_INVALID_ARGS
	, PI_API_NO_HWND_PROVIDED

}ePiErrCode;

/////////////////////////////////////////////////////////////////////
// END $Workfile: PDIerror.h $
/////////////////////////////////////////////////////////////////////
#endif // _PDIERROR_H_
