/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Mar 26 17:57:13 2008
 */
/* Compiler settings for C:\users\rebrik\work\Sabes\CP_LibertyTrack\Current\CP_LibertyTrackCom.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID IID_ILibertyTrack = {0xebd33068,0xceb1,0x11d5,{0x9c,0x3e,0x00,0x50,0xda,0x2a,0x68,0xc8}};


const IID LIBID_CP_LibertyTrackLib = {0xebd33064,0xceb1,0x11d5,{0x9c,0x3e,0x00,0x50,0xda,0x2a,0x68,0xc8}};


const CLSID CLSID_CP_LibertyClass = {0xebd33060,0xceb1,0x11d5,{0x9c,0x3e,0x00,0x50,0xda,0x2a,0x68,0xc8}};


#ifdef __cplusplus
}
#endif

