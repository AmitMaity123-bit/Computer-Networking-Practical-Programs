#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// XOR operation
void xor_op(char *dividend, char *divisor, int len) {
    for (int i = 1; i < len; i++)
        dividend[i] = dividend[i] == divisor[i] ? '0' : '1';
}

// CRC calculation
void crc(char data[], char gen[], char crc[]) {
    int dlen = strlen(data);
    int glen = strlen(gen);
    char temp[100];

    strcpy(temp, data);
    for (int i = 0; i < glen - 1; i++)
        temp[dlen + i] = '0';
    temp[dlen + glen - 1] = '\0';

    char remainder[100];
    strncpy(remainder, temp, glen);
    remainder[glen] = '\0';

    for (int i = 0; i < dlen; i++) {
        if (remainder[0] == '1')
            xor_op(remainder, gen, glen);

        for (int j = 0; j < glen - 1; j++)
            remainder[j] = remainder[j + 1];
        remainder[glen - 1] = temp[glen + i];
    }

    strncpy(crc, remainder, glen - 1);
    crc[glen - 1] = '\0';
}

// Function to flip a bit at random position to simulate noise
void introduce_error(char *data) {
    int len = strlen(data);
    srand(time(NULL));
    int pos = rand() % len; // Random bit position
    data[pos] = data[pos] == '0' ? '1' : '0'; // Flip bit
    printf("Noise introduced at bit position %d\n", pos);
}

int main() {
    char data[100], gen[20], transmit[120], crcCode[20];

    printf("Enter data bits: ");
    scanf("%s", data);
    printf("Enter generator polynomial: ");
    scanf("%s", gen);

    crc(data, gen, crcCode);

    printf("\nCRC bits: %s\n", crcCode);

    strcpy(transmit, data);
    strcat(transmit, crcCode);

    printf("Original Transmitted Codeword: %s\n", transmit);

    // Simulate noise
    introduce_error(transmit);

    printf("Received Codeword (after noise): %s\n", transmit);

    char recv_crc[20];
    crc(transmit, gen, recv_crc);

    int error = 0;
    for (int i = 0; i < strlen(gen) - 1; i++) {
        if (recv_crc[i] != '0') {
            error = 1;
            break;
        }
    }

    if (error)
        printf("Error detected in received data!\n");
    else
        printf("No error detected. Data is intact.\n");

    return 0;
}
