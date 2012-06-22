/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Jun 01 13:20:32 2006
 */
/* Compiler settings for C:\Lab\src\LibertyServer\LibertyServer.idl:
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

const IID IID_ILiberty = {0x705CFB61,0x77AF,0x4DC8,{0xA8,0x27,0xCA,0xB7,0x14,0xF9,0xEE,0x42}};


const IID LIBID_LIBERTYSERVERLib = {0x3CD16022,0x9D9F,0x4E00,{0xA8,0x1D,0x81,0x14,0xD9,0x24,0xB8,0xF1}};


const CLSID CLSID_Liberty = {0x76066C59,0x8458,0x4251,{0xAA,0x8B,0x1B,0x76,0x1B,0xEC,0x5E,0x29}};


#ifdef __cplusplus
}
#endif

