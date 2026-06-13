#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in server_addr;
    char msg[1024], reply[1024];

    printf("Initializing Winsock...\n");
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("Failed. Error Code: %d\n", WSAGetLastError());
        return 1;
    }

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Could not create socket: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        printf("Connection failed: %d\n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    printf("Connected to server.\n");

    while (1) {
        printf("You: ");
        fgets(msg, sizeof(msg), stdin);
        send(sock, msg, strlen(msg), 0);

        if (strcmp(msg, "exit\n") == 0 || strcmp(msg, "exit") == 0) {
            printf("Disconnected from server.\n");
            break;
        }

        memset(reply, 0, sizeof(reply));
        recv(sock, reply, sizeof(reply), 0);
        printf("Server: %s", reply);
    }

    closesocket(sock);
    WSACleanup();

    return 0;
}
