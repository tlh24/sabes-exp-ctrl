#ifndef _TDT_RZ_UDP_H_
#define _TDT_RZ_UDP_H_

enum
{
    // configuration values
    PROTOCOL_VERSION = 1,
    LISTEN_PORT = 22022,

    /* values pertaining to the protocol */
    HEADER_0         = 0x55,
    HEADER_0_RZ2     = 0x00,
    HEADER_1         = 0xAA,
    HEADER_2_RZ2     = 0x00,
    HEADER_BYTES     = 4, // max of the two headers
    COMMAND_OFFSET   = 2,
    COUNT_OFFSET     = 3,
    DATA_OFFSET      = 4,

    /* packet/command types */
    DATA_PACKET       = 0,
    GET_VERSION       = 1,
    SET_REMOTE_IP     = 2,
    FORGET_REMOTE_IP  = 3,
    RESET_TO_DEFAULTS = 0xFF, /* only valid once after FTP places a new image */

    /* maximum number of samples in a packet (determined by the sendable size) */
    MAX_SAMPLES = 244,
};

#define BUFFER_SIZE (HEADER_BYTES + MAX_SAMPLES * 4)

typedef short int16_t;
typedef int int32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

#define MAKE_HEADER(cmd, count) { (char)HEADER_0, (char)HEADER_1, cmd, count }
#define DATA_HEADER(count)      MAKE_HEADER(DATA_PACKET, count)
#define COMMAND_HEADER(cmd)     MAKE_HEADER(cmd, 0)

int openSocket(char *strIPAddr, int port);
bool checkRZ(int sock);
bool sendData(int sock, double *data, int count);
void disconnectRZ(int sock);

#endif
