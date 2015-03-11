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

#include "common.h"

//#define CP_printf printf
#define INVALID_SOCKET 0

int openSocket(char *strIPAddr, int port)
{
	int sockfd = INVALID_SOCKET;

	struct addrinfo hints, *servinfo, *p;
	int rv;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;

	char strPort[128];
	sprintf(strPort, "%d", port);

	if ((rv = getaddrinfo(strIPAddr, strPort, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return INVALID_SOCKET;
	}

	// connect to the first we can
	printf("UDP: Attempting to open UDP %s : %s\n", strIPAddr, strPort);
	for (p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
			perror("socket");
			continue;
		}
		int optval = 1; // turn on address reuse.
		setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

		// set timeout on these so if there is no RZ2, the rx does not block forever.
		struct timeval timeout;
		timeout.tv_sec = 1;
		timeout.tv_usec = 0;
		setsockopt(sockfd,SOL_SOCKET,SO_RCVTIMEO,(char *)&timeout,sizeof(timeout));
		setsockopt(sockfd,SOL_SOCKET,SO_SNDTIMEO,(char *)&timeout,sizeof(timeout));

		if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			perror("connect");
			continue;
		}

		break; // if we get here, we must have connected successfully
	}

	if (p == NULL) {
		// looped off the end of the list w/o connection
		fprintf(stderr, "failed to connect\n");
		return INVALID_SOCKET;
	}
	printf("... done\n");

	freeaddrinfo(servinfo);

	return sockfd;
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
	bool retval = false;

	int n = HEADER_BYTES+sizeof(float)*count;

	// Allocate packet
	char *packet = new char[n];

	// Get header and load into packet
	char header[HEADER_BYTES] = DATA_HEADER((char)count);
	for (int i=0; i<HEADER_BYTES; i++)
		packet[i]=header[i];

	// Load data (as floats)
	union floatbytes fb;
	for (int i=0; i<count; i++) {
		fb.f = data[i]; // load float
		fb.u = htonl(fb.u); // convert byte order
		for (size_t j=0; j<sizeof(float); j++) {
			packet[HEADER_BYTES+i*count+j] = fb.b[j];
		}
	}

	// send the data over the UDP connection
	if (send(sock, packet, n, 0) == n)
		retval = true;
	// Close
	free(packet);
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
