/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Jan 13 18:18:44 2006
 */
/* Compiler settings for C:\LAB\Source\OptoServer\OptoServer.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
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

const IID IID_IOptoServer = {0xB066FF86,0x7D9E,0x4C8F,{0x9A,0x34,0xF6,0x40,0xBF,0xDD,0x3B,0xE4}};


const IID LIBID_OPTOSERVERLib = {0x37967B1D,0xF5A0,0x4940,{0xB4,0x85,0xF4,0x03,0x55,0xB1,0xDC,0x1C}};


const CLSID CLSID_OptoServer = {0x858130AA,0x8F41,0x4B35,{0xB8,0xF0,0x04,0xE3,0x58,0x90,0x4B,0x48}};


#ifdef __cplusplus
}
#endif

