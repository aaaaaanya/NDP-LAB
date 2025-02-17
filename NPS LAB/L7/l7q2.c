#include <stdio.h>

#define REPLENISHMENT_RATE 10  // tokens per second (10 KBps)
#define BUCKET_SIZE 50         // bucket capacity in Kbytes
#define PACKET_SIZE 15         // packet size in Kbytes
#define PACKET_INTERVAL 0.5    // time interval between packets in seconds
#define MAX_RATE 20            // maximum rate in KBps

void token_bucket_simulation() {
    double tokens_in_bucket = BUCKET_SIZE; // Initially full
    double time = 0.0;
    double time_to_queue = -1.0;

    // Step 1: Calculate tokens after 1.5 seconds
    // Replenish the tokens in the bucket at the rate of 10 Kbytes/sec
    for (time = 0.5; time <= 1.5; time += PACKET_INTERVAL) {
        // Tokens replenish every second
        tokens_in_bucket += REPLENISHMENT_RATE * PACKET_INTERVAL;
        
        // Ensure the bucket doesn't overflow beyond its capacity
        if (tokens_in_bucket > BUCKET_SIZE) {
            tokens_in_bucket = BUCKET_SIZE;
        }

        // Try to send the packet
        if (tokens_in_bucket >= PACKET_SIZE) {
            tokens_in_bucket -= PACKET_SIZE; // Send the packet and deduct the tokens
        } else {
            // If there aren't enough tokens, packets will be queued
            if (time_to_queue == -1.0) {
                time_to_queue = time; // Record when queueing starts
            }
        }
    }

    // Print tokens left after 1.5 seconds
    printf("Tokens left in bucket after 1.5 seconds: %.2f Kbytes\n", tokens_in_bucket);

    // Step 2: How long will it take until packets start to be queued or dropped?
    if (time_to_queue == -1.0) {
        printf("Packets will never be queued or dropped.\n");
    } else {
        printf("Packets will start to be queued at time: %.2f seconds\n", time_to_queue);
    }

    // Step 3: If maximum rate is 20 KBps, calculate the maximum burst size
    double max_burst_size = MAX_RATE * BUCKET_SIZE / REPLENISHMENT_RATE;
    printf("Maximum possible burst size with R = 20 KBps: %.2f Kbytes\n", max_burst_size);
}

int main() {
    // Run the simulation
    token_bucket_simulation();
    return 0;
}
