#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <process.h>

#define MAX_CLIENTS 10

void error(const char *msg) {
    char *s = NULL;
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                  NULL, WSAGetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&s, 0, NULL);
    fprintf(stderr, "%s: %s\n", msg, s);
    LocalFree(s);
    exit(1);
}

void startStory(SOCKET client_socket) {
    char buffer[255];
    strcpy(buffer, "You find yourself at the entrance of the dungeon. What do you do?\n"
                    "1. Go through the entrance\n"
                    "2. Examine your surroundings\n"
                    "3. Turn back\n");
    send(client_socket, buffer, strlen(buffer), 0);
}

int randomizeChoices(int numClients, int *choices) {
    int randomValue = rand() % 100;
    if (randomValue < 70) { // 70% chance: Select the most common choice
        int count[3] = {0, 0, 0};
        for (int i = 0; i < numClients; i++) {
            count[choices[i] - 1]++;
        }
        int commonChoice = 1;
        if (count[1] > count[0]) commonChoice = 2;
        if (count[2] > count[1]) commonChoice = 3;
        return commonChoice;
    } else if (randomValue < 95) { // 25% chance: Select a random choice made among all clients
        int randomIndex = rand() % numClients;
        return choices[randomIndex];
    } else { // 5% chance: Trigger a funny random event
        return 99; // Special code for funny random event
    }
}

unsigned __stdcall handleClient(void *arg) {
    SOCKET client_socket = *(SOCKET *)arg;
    char buffer[255];
    int n;

    // Wait for the client to send "start" to begin the game
    while (1) {
        memset(buffer, 0, sizeof(buffer));
        n = recv(client_socket, buffer, sizeof(buffer), 0);
        if (n < 0) {
            error("Error reading from socket");
        }
        if (strncmp(buffer, "start", 5) == 0) {
            printf("Game started by client.\n");
            startStory(client_socket);
            break;
        }
    }

    // Main game loop
    while (1) {
        memset(buffer, 0, sizeof(buffer));
        n = recv(client_socket, buffer, sizeof(buffer), 0);
        if (n < 0) {
            error("Error reading from socket");
        }
        int choice = atoi(buffer);
        int choices[MAX_CLIENTS] = {choice}; // Assuming single client for simplicity
        int selectedChoice = randomizeChoices(1, choices);

        switch (selectedChoice) {
            case 1:
                strcpy(buffer, "The party chose to go through the entrance.\n");
                break;
            case 2:
                strcpy(buffer, "The party chose to examine the surroundings.\n");
                break;
            case 3:
                strcpy(buffer, "The party decided to turn back.\n");
                send(client_socket, buffer, strlen(buffer), 0);
                closesocket(client_socket);
                break;
            case 99:
                strcpy(buffer, "Bad luck brought you here.\n");
                send(client_socket, buffer, strlen(buffer), 0);
                closesocket(client_socket);
                break;
            default:
                strcpy(buffer, "You cannot do that\n");
                break;
        }

        send(client_socket, buffer, strlen(buffer), 0);
    }

    closesocket(client_socket);
    return 0;
}

int main(int argc, char *argv[]) {
    WSADATA wsaData;
    SOCKET serverSocket, clientSocket;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen;
    int portNo;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        // If WSAStartup fails, print an error message and exit the program
        fprintf(stderr, "WSAStartup failed.\n");
        exit(1);
    }

    // Check if the port number is provided as a command-line argument
    if (argc < 2) {
        // If not, print an error message and exit the program
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    portNo = atoi(argv[1]);
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        error("ERROR opening socket");
    }

    memset((char *)&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portNo);

    if (bind(serverSocket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR) {
        error("Bind failed");
    }

    listen(serverSocket, 3);

    printf("Waiting for incoming connections...\n");

    clilen = sizeof(cli_addr);
    while ((clientSocket = accept(serverSocket, (struct sockaddr *)&cli_addr, &clilen)) != INVALID_SOCKET) {
        printf("Connection accepted\n");
        _beginthreadex(NULL, 0, handleClient, (void *)&clientSocket, 0, NULL);
    }

    closesocket(serverSocket);
    WSACleanup();

    return 0;
}