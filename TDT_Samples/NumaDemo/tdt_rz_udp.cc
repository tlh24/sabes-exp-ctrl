#include "tdt_rz_udp.h"

#include <stdio.h>
#include <winsock2.h>
#include "owl.h"

int openSocket(uint32_t ipAddr)
{
    sockaddr_in sin;
    int sock= INVALID_SOCKET;

    // prepare the SIN to send to
    memset(&sin, 0, sizeof(sockaddr_in));

    sin.sin_family = AF_INET;
    sin.sin_addr.S_un.S_addr = ipAddr; //inet_addr("tdt_udp_0000000");
    sin.sin_port = htons(LISTEN_PORT);

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == INVALID_SOCKET)
        fprintf(stderr, "Failed to create the UDP socket: %d\n", WSAGetLastError());
    else if (connect(sock, (struct sockaddr*)&sin, sizeof(sockaddr_in)) != 0)
    {
        closesocket(sock);
        sock = INVALID_SOCKET;
        fprintf(stderr, "Failed to connect the UDP socket: %d\n", WSAGetLastError());
    }

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

bool sendData(int sock, OWLMarker *markers, int count)
{
    char packet[BUFFER_SIZE] = DATA_HEADER((unsigned char)count);
    bool retval = false;

    if (sock == INVALID_SOCKET || count > MAX_SAMPLES)
        return true;

    /* pack the data into a single packet */
    char offset = 0;
    for(int i = 0; i < count; i++)
    {2
        ((float*)(packet + HEADER_BYTES))[offset++] = (float)i;
        ((float*)(packet + HEADER_BYTES))[offset++] = markers[i].x;
        ((float*)(packet + HEADER_BYTES))[offset++] = markers[i].y;
        ((float*)(packet + HEADER_BYTES))[offset++] = markers[i].z;
    }
    packet[COUNT_OFFSET] = offset;

    // match the byte ordering of the RZ communication
    uint32_t *data = (uint32_t*)(packet + HEADER_BYTES);
    for(int z = 0; z < packet[COUNT_OFFSET]; z++)
        data[z] = htonl(data[z]);

    // send the data over the UDP connection
    if (send(sock, packet, 4 + offset * 4, 0) == 4 + offset * 4)
        retval = true;

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
