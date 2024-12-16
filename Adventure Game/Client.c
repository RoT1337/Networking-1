#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "Ws2_32.lib")

#define SERVER_IP "127.0.0.1"
#define PORT 8080
#define BUFFER_SIZE 1024

void printHeader() {
    const char *green = "\033[32m";
    const char *reset = "\033[0m";

    // clear screen
    system("cls");

    printf("%s", green);
    printf(" __      __       .__                                  __             __  .__               ________      .__.__       .___\n");
    printf("/  \\    /  \\ ____ |  |   ____  ____   _____   ____   _/  |_  ____   _/  |_|  |__   ____    /  _____/ __ __|__|  |    __| _/\n");
    printf("\\   \\/\\/   // __ \\|  | _/ ___\\/  _ \\ /     \\_/ __ \\  \\   __\\/  _ \\  \\   __\\  |  \\_/ __ \\  /   \\  ___|  |  \\  |  |   / __ | \n");
    printf(" \\        /\\  ___/|  |_\\  \\__(  <_> )  Y Y  \\  ___/   |  | (  <_> )  |  | |   Y  \\  ___/  \\    \\_\\  \\  |  /  |  |__/ /_/ | \n");
    printf("  \\__/\\  /  \\___  >____/\\___  >____/|__|_|  /\\___  >  |__|  \\____/   |__| |___|  /\\___  >  \\______  /____/|__|____/\\____ | \n");
    printf("       \\/       \\/          \\/            \\/     \\/                            \\/     \\/          \\/                    \\/ \n");
    printf("Awaiting your comrades or preparing to go solo into the dungeon?\n");
    printf("Grab a drink before you head out!\n");
    printf("%s", reset);
}

void error_exit(const char *message) {
    printf("%s. Error Code: %d\n", message, WSAGetLastError());
    WSACleanup();
    exit(1);
}

int main() {
    WSADATA wsaData;
    SOCKET clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[BUFFER_SIZE];
    int bytesRead;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        error_exit("Failed to initialize Winsock");
    }

    // Create socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        error_exit("Socket creation failed");
    }

    // Setup server address structure
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
    serverAddr.sin_port = htons(PORT);

    // Connect to server
    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        error_exit("Connection to server failed");
    }

    printf("Connected to server.\n");
    printHeader();

    // Receive player name prompt from server
    bytesRead = recv(clientSocket, buffer, BUFFER_SIZE, 0);
    if (bytesRead > 0) {
        buffer[bytesRead] = '\0'; // Null-terminate the string
        printf("\033[1;34m\nGame Master:\n\033[0m");\
        printf("\033[1;33m%s\n\033[0m", buffer); 

        // Send player name to server
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character
        send(clientSocket, buffer, strlen(buffer), 0);
    } else {
        error_exit("Failed to receive player name prompt from server");
    }

    // Game loop
    while (1) {
        // Receive message from server
        bytesRead = recv(clientSocket, buffer, BUFFER_SIZE, 0);
        if (bytesRead > 0) {
            buffer[bytesRead] = '\0'; // Null-terminate the string
            printf("\033[1;34m\nGame Master:\n\033[0m");
            printf("\033[1;33m%s\n\033[0m", buffer); 

            // Check if the server is prompting for an action
            if (strstr(buffer, "What do you do?") != NULL) {
                // Get player action
                printf("Enter your action: ");
                fgets(buffer, BUFFER_SIZE, stdin);
                buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character

                // Send action to server
                send(clientSocket, buffer, strlen(buffer), 0);
                printf("Sent action to server: %s\n", buffer);
            }
        } else if (bytesRead == 0) {
            printf("Connection closed by server.\n");
            break; // Exit loop if connection closed
        } else {
            error_exit("recv failed");
        }
    }

    // Clean up
    closesocket(clientSocket);
    WSACleanup();
    return 0;
}