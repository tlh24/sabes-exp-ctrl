#include <stdlib.h>
#include <stdio.h>
#include "PO8e.h"
//#include <compat.h> --why were these needed?
//#include <support.h>
#include <time.h>

long double 	g_startTime = 0.0;
extern "C" long double gettime(){ //in seconds!
	timespec pt ;
	clock_gettime(CLOCK_MONOTONIC, &pt);
	long double ret = (long double)(pt.tv_sec) ;
	ret += (long double)(pt.tv_nsec) / 1e9 ;
	return ret - g_startTime;
}


int main(int argc, char **argv)
{
    int count = 0, total;
    PO8e *cards[8] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    total = PO8e::cardCount();
    printf("Found %d card(s) in the system.\n", total);
    if (0 == total)
    {
        printf("  exiting\n");
        exit(1);
    }

    for(int x = 0; x < total; x++)
    {
        printf(" Connecting to card %d\n", x);
        cards[count] = PO8e::connectToCard(x);
        if (cards[count] == NULL)
            printf("  connection failed\n");
        else
        {
            printf("  established connection %p\n", (void*)cards[count]);
//TODO: have to expose the card ports MUCH better
            if (! cards[count]->startCollecting())
            {
                printf("  startCollecting() failed with: %d\n",
                       cards[count]->getLastError());
                PO8e::releaseCard(cards[count]);
            }
            else
            {
                printf("  card is collecting incoming data.\n");
                count++;
            }
        }
    }

    // wait for streaming to start on the first card
    printf("Waiting for the stream to start on card 0\n");
    while(cards[0]->samplesReady() == 0)
        usleep(5000);

    // start the timer used to compute the speed and set the collected bytes to 0
    long double starttime = gettime(); 
	 long long bytes = 0; 
	 unsigned int frame = 0; 
	 unsigned int bps = cards[0]->dataSampleSize(); 
		unsigned int nchan = cards[0]->numChannels(); 
    int stoppedCount = 0, pos = 0;
    while(stoppedCount < count)
    {
        //char posChar = "|/-\\"[pos];
        //pos = (pos + 1) % 4;

        // if we are working with just one card, work with it much more efficiently
        
        //printf("waiting for data ready.\n"); 
        //if (count == 1 &&
        //    ! cards[0]->waitForDataReady())
        //    break;
		
        int waitCount = 0;
        stoppedCount = 0;
        for(int x = 0; x < count; x++)
        {
            bool stopped = false;
            size_t numSamples = cards[x]->samplesReady(&stopped);
            if (stopped)
                stoppedCount++;
            else if (numSamples > 0)
            {
                short bufferB[8192];
                short temp[8192];
					 cards[x]->readBlock(temp, numSamples);
					 cards[x]->flushBufferedData(numSamples);
					 bytes += numSamples * nchan * bps; 
					 if(frame %10 == 0){
					 	printf("%d samples at %d bps of %d chan: %Lf MB/sec\n", numSamples, bps, nchan,
								 ((long double)bytes) / ((gettime() - starttime)*(1024.0*1024.0))); 
					 }
            }
            else{
					//printf("wait count %d\n", waitCount); 
                waitCount++;
				}
        }
        frame++; 
    }
    printf("\n");

    for(int x = 0; x < count; x++)
    {
        printf("Releasing card %d\n", x);
        PO8e::releaseCard(cards[x]);
    }

    return 0;
}
