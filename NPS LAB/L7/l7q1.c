#include <stdio.h>

#define MAX_BUCKET_SIZE 10 // Maximum capacity of the bucket (in bytes)
#define OUTGOING_RATE 1    // 1 byte per second

// Function to simulate the leaky bucket algorithm
void leaky_bucket_method(int packet_times[], int num_packets, int packet_size, int bucket_size, int outgoing_rate) {
    int current_time = 0;
    int bucket = 0; // Initialize bucket with 0
    int i = 0;

    printf("Packet Arrival Times (in seconds):\n");
    for (int i = 0; i < num_packets; i++) {
        printf("%d ", packet_times[i]);
    }
    printf("\n\n");

    printf("Time | Incoming Packet | Bucket Status | Conforming/Non-conforming\n");
    printf("-------------------------------------------------------------\n");

    for (current_time = 1; current_time <= packet_times[num_packets - 1] + 5; current_time++) {
        // Empty the bucket based on the outgoing rate
        if (current_time > 1) {
            bucket -= outgoing_rate;
            if (bucket < 0) {
                bucket = 0; // Bucket cannot go below 0
            }
        }

        // Check for incoming packets at this time
        while (i < num_packets && packet_times[i] == current_time) {
            if (bucket + packet_size <= bucket_size) {
                // The packet fits into the bucket
                bucket += packet_size;
                printf("%d   |   %d          |   %d          |   Conforming\n", current_time, packet_size, bucket);
            } else {
                // The packet does not fit into the bucket
                printf("%d   |   %d          |   %d          |   Non-conforming\n", current_time, packet_size, bucket);
            }
            i++;
        }
    }
}

int main() {
    // Packet arrival times (in seconds)
    int packet_times[] = {1, 2, 3, 5, 6, 8, 11, 12, 15, 16, 19};
    int num_packets = sizeof(packet_times) / sizeof(packet_times[0]);
    int packet_size = 4; // Packet size in bytes
    int bucket_size = MAX_BUCKET_SIZE;

    leaky_bucket_method(packet_times, num_packets, packet_size, bucket_size, OUTGOING_RATE);
    return 0;
}

