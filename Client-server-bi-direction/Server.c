#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsa;
    SOCKET server_fd, new_socket;
    struct sockaddr_in server, client;
    int c;
    char buffer[1024], reply[1024];

    printf("Initializing Winsock...\n");
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("Failed. Error Code: %d\n", WSAGetLastError());
        return 1;
    }

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Socket creation failed: %d\n", WSAGetLastError());
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(9000);

    if (bind(server_fd, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR) {
        printf("Bind failed: %d\n", WSAGetLastError());
        return 1;
    }

    listen(server_fd, 3);
    printf("Server listening on port 8080...\n");

    c = sizeof(struct sockaddr_in);
    new_socket = accept(server_fd, (struct sockaddr *)&client, &c);
    if (new_socket == INVALID_SOCKET) {
        printf("Accept failed: %d\n", WSAGetLastError());
        return 1;
    }

    printf("Client connected.\n");

    while (1) {
        memset(buffer, 0, sizeof(buffer));
        recv(new_socket, buffer, sizeof(buffer), 0);

        if (strcmp(buffer, "exit\n") == 0 || strcmp(buffer, "exit") == 0) {
            printf("Client disconnected.\n");
            break;
        }

        printf("Client: %s", buffer);

        printf("You: ");
        fgets(reply, sizeof(reply), stdin);
        send(new_socket, reply, strlen(reply), 0);
    }

    closesocket(new_socket);
    closesocket(server_fd);
    WSACleanup();

    return 0;
}
