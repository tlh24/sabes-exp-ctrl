#include "tdt_udp.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> // for inet_addr
#include <netdb.h>
#include <fcntl.h>

//#define CP_printf printf
#define INVALID_SOCKET 0

int openSocket(char *strIPAddr, int port)
{
	sockaddr_in sin;

	int sock= INVALID_SOCKET;

	//do name resolution
	hostent *targethost;
	char *ipaddr;
	targethost = gethostbyname(strIPAddr);
	if (targethost) {
		ipaddr=inet_ntoa(*(struct in_addr *)*targethost->h_addr_list);
	} else {
		printf("hahahahha!\n");
		ipaddr=strIPAddr;  //failed resolution...
	}

	// prepare the SIN to send to
	memset(&sin, 0, sizeof(sockaddr_in));

	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr(ipaddr);
	sin.sin_port = htons(port);

	printf("UDP: Attempting to open UDP %s\n", strIPAddr);

	sock = socket(AF_INET, SOCK_DGRAM, 0);
	printf("... socket created\n");
	if (sock == INVALID_SOCKET) {
		fprintf(stderr, "Failed to create the UDP socket: \n");
		perror(":");
	}
	int optval = 1; // turn on address reuse.
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
	//set timeout on these so if there is no RZ2, they rx does not block forever.
	struct timeval timeout;
	timeout.tv_sec = 1;
	timeout.tv_usec = 0;
	if (setsockopt (sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0)
		fprintf(stderr,"setsockopt failed\n");
	if (setsockopt (sock, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout)) < 0)
		fprintf(stderr,"setsockopt failed\n");

	// Flip uses connect rather than bind here -- so outgoing packets have a default endpoint.
	if (connect(sock, (struct sockaddr *)&sin, sizeof(sockaddr_in)) != 0) {
		close(sock);
		sock = INVALID_SOCKET;
		fprintf(stderr,"Failed to connect the UDP socket:\n");
		perror(":");
	}
	printf("... done\n");

	return sock;
}

bool checkRZ(int sock)
{
	char req[HEADER_BYTES] = COMMAND_HEADER(GET_VERSION), resp[1024];
	if (send(sock, req, HEADER_BYTES, 0) != HEADER_BYTES) {
		fprintf(stderr, "RZ: Failed to send GET_VERSION packet:\n");
		perror(":");
	}

	if (recv(sock, resp, 1024, 0) != 4 ||
	    memcmp(req, resp, 3) != 0 ||
	    resp[3] != 1)
		return false;

	char packet[HEADER_BYTES] = COMMAND_HEADER(SET_REMOTE_IP);
	if (send(sock, packet, HEADER_BYTES, 0) != HEADER_BYTES) {
		fprintf(stderr, "RZ: Failed to send \"start sending\" packet:\n");
		perror(":");
	}
	//TODO: does it reply? discard packet if it does.
	return true;
}

bool sendDataRZ(int sock, float *data, int count)
{
	char *packet;
	bool retval = false;

	// Allocate packet
	int n = 4+4*count;
	packet = new char[n];

	// Get header and load into packet
	char header[4] = DATA_HEADER((char)count);
	for (int i=0; i<4; i++)
		packet[i]=header[i];

	// Load data (as floats)
	float *f = (float *)(packet + HEADER_BYTES);
	for (int i=0; i<count; i++)
		f[i] = (float)(data[i]);

	// match the byte ordering of the RZ communication
	uint32_t *udata = (uint32_t *)f;
	for (int i=0; i<count; i++)
		udata[i] = htonl(udata[i]);

	// send the data over the UDP connection
	retval = send(sock, packet, n, 0) == n ? true : false;

	// Close
	delete[] packet;
	return retval;
}

void disconnectRZ(int sock)
{
	if (sock != INVALID_SOCKET) {
		char packet[HEADER_BYTES] = COMMAND_HEADER(FORGET_REMOTE_IP);
		if (send(sock, packet, HEADER_BYTES, 0) != HEADER_BYTES) {
			fprintf(stderr, "Failed to send \"stop sending\" packet.\n");
			perror(":");
		}
		close(sock);
		sock = INVALID_SOCKET;
	}
}
