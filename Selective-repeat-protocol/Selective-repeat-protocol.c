#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define TOTAL_FRAMES 10
#define WINDOW_SIZE 4

int frameStatus[TOTAL_FRAMES];  // 0 = not sent, 1 = sent, 2 = acked

// Simulate sending a frame (success rate: 80%)
int sendFrame(int frame) {
    int success = rand() % 100 < 80;
    if (success)
        printf("Sender: Frame %d sent successfully.\n", frame);
    else
        printf("Sender: Frame %d lost during transmission!\n", frame);
    return success;
}

// Simulate receiving ACK (success rate: 85%)
int receiveAck(int frame) {
    int success = rand() % 100 < 85;
    if (success)
        printf("Receiver: ACK %d received by sender.\n", frame);
    else
        printf("Receiver: ACK %d lost!\n", frame);
    return success;
}

int allAcked() {
    for (int i = 0; i < TOTAL_FRAMES; i++) {
        if (frameStatus[i] != 2)
            return 0;
    }
    return 1;
}

int main() {
    srand(time(0));

    printf("Simulating Selective Repeat Sliding Window Protocol\n");
    printf("---------------------------------------------------\n");

    int base = 0;

    while (!allAcked()) {
        // Send all unsent frames in the window
        for (int i = base; i < base + WINDOW_SIZE && i < TOTAL_FRAMES; i++) {
            if (frameStatus[i] == 0) {
                if (sendFrame(i))
                    frameStatus[i] = 1; // Mark as sent
                sleep(1);
            }
        }

        // Receive ACKs for sent frames
        for (int i = base; i < base + WINDOW_SIZE && i < TOTAL_FRAMES; i++) {
            if (frameStatus[i] == 1) {
                if (receiveAck(i)) {
                    frameStatus[i] = 2; // Mark as acknowledged
                }
                sleep(1);
            }
        }

        // Slide the window forward
        while (frameStatus[base] == 2 && base < TOTAL_FRAMES) {
            base++;
        }

        // Retransmit unacknowledged frames selectively
        for (int i = base; i < base + WINDOW_SIZE && i < TOTAL_FRAMES; i++) {
            if (frameStatus[i] == 1) {
                printf("Sender: Timeout or lost ACK. Resending Frame %d...\n", i);
                if (sendFrame(i))
                    frameStatus[i] = 1; // still sent
                sleep(1);
            }
        }

        printf("\n");
    }

    printf("All frames transmitted and acknowledged successfully.\n");
    return 0;
}
