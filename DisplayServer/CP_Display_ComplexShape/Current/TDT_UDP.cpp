#include "TDT_UDP.h"

#include <stdio.h>
#include <winsock2.h>
#include "Util\CP_printf.h"


int openSocket(char *strIPAddr)
{
    sockaddr_in sin;
    int sock= INVALID_SOCKET;

    // prepare the SIN to send to
    memset(&sin, 0, sizeof(sockaddr_in));

    sin.sin_family = AF_INET;
    // sin.sin_addr.S_un.S_addr = ipAddr; //inet_addr("tdt_udp_0000000");
    sin.sin_addr.S_un.S_addr = inet_addr(strIPAddr);

    sin.sin_port = htons(LISTEN_PORT);

    CP_printf("UDP: Attempting to open UDP %s\n", strIPAddr);
 
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    CP_printf("... socket created\n");
    if (sock == INVALID_SOCKET)
        CP_printf("Failed to create the UDP socket: %d\n", WSAGetLastError());
    else if (connect(sock, (struct sockaddr*)&sin, sizeof(sockaddr_in)) != 0)
    {
        closesocket(sock);
        sock = INVALID_SOCKET;
        CP_printf("Failed to connect the UDP socket: %d\n", WSAGetLastError());
    }
    CP_printf("... done\n");

    return sock;
}

bool checkRZ(int sock)
{
    char req[HEADER_BYTES] = COMMAND_HEADER(GET_VERSION), resp[1024];
    if (send(sock, req, HEADER_BYTES, 0) != HEADER_BYTES)
        fprintf(stderr, "Failed to send GET_VERSION packet: %d\n", WSAGetLastError());

    if (recv(sock, resp, 1024, 0) != 4 ||
        memcmp(req, resp, 3) != 0 ||
        resp[3] != 1)
        return false;

    char packet[HEADER_BYTES] = COMMAND_HEADER(SET_REMOTE_IP);
    if (send(sock, packet, HEADER_BYTES, 0) != HEADER_BYTES)
        fprintf(stderr, "Failed to send \"start sending\" packet: %d\n", WSAGetLastError());
    //TODO: does it reply? discard packet if it does.

    return true;
}



bool sendData(int sock, double *data, int count)
{
	char *packet;
    bool retval = false;
	int i;

	// Allocate packet
	packet = new char[4+4*count];
	
	// Get header and load into packet
	char header[4] = DATA_HEADER((unsigned char)count);
	for(i=0; i<4; i++) packet[i]=header[i];

	// Load data (as floats)
    char offset = 0;
    for(i=0; i<count; i++)
		((float*)(packet + HEADER_BYTES))[i] = (float)(data[i]);

    // match the byte ordering of the RZ communication
    uint32_t *udata = (uint32_t*)(packet + HEADER_BYTES);
    for(i=0; i<count; i++)
        udata[i] = htonl(udata[i]);

    // send the data over the UDP connection
    if (send(sock, packet, 4 + count * 4, 0) == 4 + count * 4)
        retval = true;

	// Close
    return retval;
}

void disconnectRZ(int sock)
{
    if (sock != INVALID_SOCKET)
    {
        char packet[HEADER_BYTES] = COMMAND_HEADER(FORGET_REMOTE_IP);
        if (send(sock, packet, HEADER_BYTES, 0) != HEADER_BYTES)
            fprintf(stderr, "Failed to send \"stop sending\" packet: %d\n", WSAGetLastError());

        closesocket(sock);
        sock = INVALID_SOCKET;
    }
}
