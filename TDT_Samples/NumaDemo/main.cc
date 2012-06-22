/* example1.cc
   simple point tracking program modified to relay that information to RZ UDP ports
 */
#include <stdio.h>
#include <winsock2.h>
#include "owl.h"

#include "tdt_rz_udp.h"

// change these to match your configuration
#define MARKER_COUNT 10
#define SERVER_NAME "132.204.227.52"
#define INIT_FLAGS 0

static void owl_print_error(const char *s, int n)
{
    if (n < 0)
        printf("%s: %d\n", s, n);
    else if (n == OWL_NO_ERROR)
        printf("%s: No Error\n", s);
    else if (n == OWL_INVALID_VALUE)
        printf("%s: Invalid Value\n", s);
    else if (n == OWL_INVALID_ENUM)
        printf("%s: Invalid Enum\n", s);
    else if (n == OWL_INVALID_OPERATION)
        printf("%s: Invalid Operation\n", s);
    else
        printf("%s: 0x%x\n", s, n);
}

int main()
{
    OWLMarker markers[32];
    int tracker, sock = INVALID_SOCKET;

    // open a UDP socket to the RZ unit
    sock = openSocket(inet_addr("10.10.10.141"));

    // confirm remote version and configure the remote IP for the RZ (i.e. this machine)
    if (! checkRZ(sock))
    {
        printf("Error communicating with the RZ.\n");
        exit(1);
    }

    if (owlInit(SERVER_NAME, INIT_FLAGS) < 0)
        return 0;

    // create tracker 0
    tracker = 0;
    owlTrackeri(tracker, OWL_CREATE, OWL_POINT_TRACKER);

    // set markers
    for(int i = 0; i < MARKER_COUNT; i++)
        owlMarkeri(MARKER(tracker, i), OWL_SET_LED, i);

    // activate tracker
    owlTracker(tracker, OWL_ENABLE);

    // flush requests and check for errors
    if (!owlGetStatus())
    {
        owl_print_error("error in point tracker setup", owlGetError());
        return 0;
    }

    // set default frequency
    owlSetFloat(OWL_FREQUENCY, OWL_MAX_FREQUENCY);

    // start streaming
    owlSetInteger(OWL_STREAMING, OWL_ENABLE);

    // main loop
    while(true)
    {
        int err;

        // get some markers
        int n = owlGetMarkers(markers, 32);

        // check for error
        if ((err = owlGetError()) != OWL_NO_ERROR)
        {
            owl_print_error("error", err);
            break;
        }

        // no data yet
        if (n == 0)
            continue;

        if (n > 0)
        {
            printf("%d marker(s):\n", n);
            for(int i = 0; i < n; i++)
                if (markers[i].cond > 0)
                    printf("%d) %f %f %f\n", i, markers[i].x, markers[i].y, markers[i].z);
            printf("\n");

            sendData(sock, markers, n);
        }
    }

    // cleanup
    owlDone();
    disconnectRZ(sock);
}
