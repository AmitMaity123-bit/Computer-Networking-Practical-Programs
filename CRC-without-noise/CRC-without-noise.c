#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include<time.h>

// Function to perform XOR between dividend and divisor
void xor_op(char *dividend, char *divisor, int len) {
    for (int i = 1; i < len; i++)
        dividend[i] = dividend[i] == divisor[i] ? '0' : '1'; // XOR logic
}

// Function to calculate CRC using binary division (XOR)
void crc(char data[], char gen[], char crc[]) {
    int dlen = strlen(data);
    int glen = strlen(gen);
    char temp[100];

    // Step 1: Append (glen - 1) zeros to data
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

    printf("Transmitted Codeword: %s\n", transmit);

    char received[120];
    printf("\nEnter received data: ");
    scanf("%s", received);

    char recv_crc[20];
    crc(received, gen, recv_crc);

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
