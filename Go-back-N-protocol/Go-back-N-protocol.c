#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> // for sleep()

#define TOTAL_FRAMES 10
#define WINDOW_SIZE 4

// Simulate sending a frame (randomly drops some frames)
int sendFrame(int frame) {
    int success = rand() % 100 < 80; // 80% chance of success
    if (success)
        printf("Sender: Frame %d sent successfully.\n", frame);
    else
        printf("Sender: Frame %d lost during transmission!\n", frame);
    return success;
}

// Simulate receiving ACK (randomly drops ACK)
int receiveAck(int frame) {
    int success = rand() % 100 < 85; // 85% chance ACK is received
    if (success)
        printf("Receiver: ACK %d received by sender.\n", frame);
    else
        printf("Receiver: ACK %d lost!\n", frame);
    return success;
}

int main() {
    srand(time(0)); // Seed for randomness

    int base = 0;   // base of the window
    int next_frame = 0;

    printf("Simulating Go-Back-N Sliding Window Protocol\n");
    printf("---------------------------------------------\n");

    while (base < TOTAL_FRAMES) {
        int count = 0;

        // Sending all frames within the window
        while (count < WINDOW_SIZE && next_frame < TOTAL_FRAMES) {
            printf("\nSending Frame %d...\n", next_frame);
            if (!sendFrame(next_frame)) {
                printf("Sender: Timeout occurred. Go-Back-N to frame %d\n", base);
                break; // Lost frame: break and retransmit from base
            }
            next_frame++;
            count++;
            sleep(1);
        }

        // Simulate receiving ACKs for all frames in the window
        int ack_success = 1;
        for (int i = base; i < next_frame; i++) {
            if (!receiveAck(i)) {
                ack_success = 0;
                printf("Sender: ACK for frame %d lost. Go-Back-N to frame %d\n", i, i);
                next_frame = i; // Go back to this frame
                break;
            } else {
                base++; // Move the base forward
            }
            sleep(1);
        }

        if (!ack_success) {
            printf("Sender: Resending from frame %d...\n", base);
        }
    }

    printf("\nAll frames transmitted and acknowledged successfully.\n");
    return 0;
}
