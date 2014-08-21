#include <stdlib.h>
#include <stdio.h>
#include "../../PO8e.h"
#include "../../compat.h"

#define BLOCK_SIZE 1

int main(int argc, char **argv)
{
    // count the cards in the system
    int total = PO8e::cardCount();
    printf("Found %d card(s) in the system.\n", total);
    if (0 == total)
    {
        printf("  exiting\n");
        exit(0);
    }

    // connect to the first (0) card
    printf(" Connecting to card\n");
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

    // wait for streaming to start
    printf("Waiting for the stream to start\n");
    while(card->samplesReady() == 0)
        compatUSleep(5000);

    // loop over reading data and print a progress line to show we're still running
    int64_t pos = 0;
    bool stopped = false;
    while(! stopped)
    {
        // compute the rate in megabytes per second
        char posChar = "|/-\\"[pos % 4];

        // working with just one card, so wait efficiently
        if (! card->waitForDataReady())
            break;

        size_t numSamples = card->samplesReady(&stopped);
        if (! stopped && numSamples > 0)
        {
            int channel = random() % card->numChannels();

            printf("Card has %4d samples of %4d channels. %c \r", numSamples, card->numChannels(), posChar);
            fflush(stdout);

            short buffer[8192];

// We can read a channel of data at a time...
#if READ_BY_CHANNEL
            if (card->readChannel(channel,
                                  buffer, (int)numSamples) != numSamples)
                printf("  reading %d samples from channel %d failed\n",
                       numSamples, channel);

            // once we're done reading the data into our own buffers, discard those samples
            card->flushBufferedData(numSamples);
#else
// ... or read samples from every channel iteratively.  This is more efficient if you need to read multiple channels
            short temp[1024];
            for(int i = 0; i < (int)numSamples; i++)
            {
                // reading more than one sample at a time would be more efficient
                int64_t offsets[BLOCK_SIZE];
                if (card->readBlock(temp, BLOCK_SIZE, offsets) != BLOCK_SIZE)
                    printf("  reading block of %d samples failed\n", numSamples);
                buffer[i] = temp[channel];

                // checking if we've lost any data
                if (pos + BLOCK_SIZE != offsets[BLOCK_SIZE - 1])
                {
                    printf("\n  skipping %lld to position %lld\n", offsets[BLOCK_SIZE - 1] - (pos + BLOCK_SIZE), offsets[BLOCK_SIZE - 1]);
                    pos = offsets[BLOCK_SIZE - 1];
                }
                else
                    pos += BLOCK_SIZE;

                // once we're done reading the data into our own buffers, discard those samples
                card->flushBufferedData(BLOCK_SIZE);
            }
#endif

            // TODO: do something with the data in buffer?
        }
    }
    printf("\n");

    printf("Releasing the card\n");
    PO8e::releaseCard(card);

    return 0;
}
