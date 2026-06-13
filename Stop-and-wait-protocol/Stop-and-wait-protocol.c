#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> // for sleep()

#define TOTAL_FRAMES 5

// Simulate sending frame (0 or 1 success)
int sendFrame(int frame) {
    printf("Sender: Sending Frame %d...\n", frame);
    // Randomly simulate frame loss
    int success = rand() % 2; // 0 = lost, 1 = delivered
    if (success)
        printf("Channel: Frame %d Delivered Successfully.\n", frame);
    else
        printf("Channel: Frame %d Lost!\n", frame);
    return success;
}

// Simulate receiving acknowledgment (0 or 1 success)
int receiveAck(int frame) {
    // Randomly simulate ACK loss
    int success = rand() % 2; // 0 = lost, 1 = received
    if (success)
        printf("Receiver: ACK %d Received by Sender.\n", frame);
    else
        printf("Receiver: ACK %d Lost!\n", frame);
    return success;
}

int main() {
    srand(time(0)); // Seed for randomness
    int frame = 0;

    printf("Simulating Stop and Wait Protocol (Noisy Channel)\n");
    printf("-------------------------------------------------\n");

    while (frame < TOTAL_FRAMES) {
        printf("\n--- Sending Frame %d ---\n", frame);
        int sent = sendFrame(frame);
        if (!sent) {
            printf("Sender: Timeout! Retransmitting Frame %d...\n", frame);
            sleep(2);
            continue; // Retransmit same frame
        }

        printf("Receiver: Frame %d Received. Sending ACK %d...\n", frame, frame);
        int ack = receiveAck(frame);
        if (!ack) {
            printf("Sender: ACK %d Not Received. Timeout! Retransmitting Frame %d...\n", frame, frame);
            sleep(2);
            continue; // Retransmit same frame
        }

        // Frame and ACK successfully delivered
        printf("Sender: ACK %d Received. Sending Next Frame.\n", frame);
        frame++; // Move to next frame
        sleep(1);
    }

    printf("\nAll frames sent and acknowledged successfully.\n");
    return 0;
}
