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
    long long totalBytes;
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
    totalBytes = 0;
	 
	 int sum[96] = {0}; 

    int stoppedCount = 0, pos = 0;
    while(stoppedCount < count)
    {
        // compute the rate in megabytes per second
        long double t = gettime(); 
        double rate = totalBytes / (t - starttime) / (1024 * 1024);
        char posChar = "|/-\\"[pos];
        pos = (pos + 1) % 4;

        // if we are working with just one card, work with it much more efficiently
        if (count == 1 &&
            ! cards[0]->waitForDataReady())
            break;

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
                int channel = 0; //random() % cards[x]->numChannels();

               // printf("Card %d has %4d samples of %4d channels.  Current rate: %.2lf MB/s %c \n", x, numSamples, cards[x]->numChannels(), rate, posChar);
                fflush(stdout);

                int bufferA[8192] = {42};
                if (cards[x]->readChannel(channel,
                                          bufferA, (int)numSamples) != numSamples)
                    printf("  reading %d samples from channel %d failed\n",
                           numSamples, channel);
					printf("channel 0[0]: %d\n", bufferA[0]); 
                totalBytes += numSamples * cards[x]->numChannels() * cards[x]->dataSampleSize();

                int bufferB[8192];
                int temp[1024];
					 cards[x]->readBlock(temp, numSamples);
					 cards[x]->flushBufferedData(numSamples);
                for(int i = 0; i < (int)numSamples; i++){
						  printf("%d\t%d \t %d \t %d\n", numSamples, temp[0], temp[1], cards[x]->numChannels()); 
                		for(int j=0; j<96; j++){
								sum[j] += temp[j+4]; 
								printf(" %02x", sum[j] & 0xff);
							}
						 	printf("\n"); 
					}

                // print a comparison of the two ways of reading data
                /*for(int y = 0; y < (int)numSamples; y++)
                {
                    short a, b;
                    a = bufferA[y];
                    b = bufferB[y];
                    if (a != b)
                        fprintf(stderr, "Sample mismatch on channel %d! %d\t!=\t%d\t\n", channel, a, b);
                }*/
            }
            else
                waitCount++;
        }
    }
    printf("\n");

    for(int x = 0; x < count; x++)
    {
        printf("Releasing card %d\n", x);
        PO8e::releaseCard(cards[x]);
    }

    return 0;
}
