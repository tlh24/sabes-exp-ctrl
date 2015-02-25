#include <stdlib.h>
#include <stdio.h>
#include "PO8e.h"
#include <time.h>

#define MAX_BLOCK_SIZE 10000

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
    // count the cards in the system
    int total = PO8e::cardCount();
    printf("Found %d card(s) in the system.\n", total);
    if (0 == total)
    {
        printf("  exiting\n");
        exit(1);
    }

    // connect to the first (0) card
    printf(" Connecting to card 0\n");
    PO8e *card = PO8e::connectToCard(0);
    if (card == NULL)
        printf("  connection failed\n");
    else
    {
        printf("  established connection %p\n", (void*)card);
        // enable data collection
        if (! card->startCollecting())
        {
            printf("  startCollecting() failed with: %d\n",
                   card->getLastError());
            PO8e::releaseCard(card);
            exit(1);
        }
        else
            printf("  card is collecting incoming data.\n");
    }

    // wait for streaming to start on the first card
    printf("Waiting for the stream to start\n");
    while(card->samplesReady() == 0)
        usleep(5000);

    // start the timer used to compute the speed and set the collected bytes to 0
    long double starttime = gettime(); 
	long long bytes = 0; 
	int64_t frame = 0; 
	unsigned int bps = card->dataSampleSize(); 
	unsigned int nchan = card->numChannels(); 
    
    //int64_t pos = 0;
    bool stopped = false;
    while(!stopped)
    {
        // compute the rate in megabytes per second
        char posChar = "|/-\\"[frame % 4];

        // working with just one card, so wait efficiently
        if (!card->waitForDataReady())
            break;
		
        size_t numSamples = card->samplesReady(&stopped);
        
        if (!stopped && numSamples > 0)
        {

            bytes += numSamples * nchan * bps;
            long double mbs = (long double)bytes / 
                ((gettime()-starttime)*1024.0*1024.0);

            printf("%4lu samples (%d bps) of %4d channels (%Lf MB/s). [%c] \r", 
                numSamples, bps, nchan, mbs, posChar);
            fflush(stdout);

            short *temp = new short[MAX_BLOCK_SIZE*(nchan)];
            int64_t *offsets = new int64_t[numSamples];
					 
            if (card->readBlock(temp, numSamples, offsets) != numSamples)
                printf("\n  reading block of %4lu samples failed\n", numSamples);

            for (int i=0; i<numSamples; i++)
            {
                // checking if we've lost any data
                if (frame+1 != offsets[i])
                {
                    printf("\n  skipping %ld to frame %ld\n",
                        offsets[i] - (frame), offsets[i]);
                    frame = offsets[i];
                }
                else
                    frame++;
            }
            card->flushBufferedData(numSamples);
        }
    }
    printf("\n");

    printf("Releasing the card\n");
    PO8e::releaseCard(card);

    return 0;
}
