#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "Ws2_32.lib")

#define PORT 8080
#define MAX_PLAYERS 4
#define BUFFER_SIZE 1024

typedef struct {
    SOCKET socket;
    char name[50];
    int is_active;
    char color[10];
} Player;

void startStory(Player players[], int player_count) {
    const char *story = "You find yourself at the entrance of the dungeon. What do you do?\n"
                        "1. Go through the entrance\n"
                        "2. Examine your surroundings\n"
                        "3. Turn back\n";
    for (int i = 0; i < player_count; i++) {
        send(players[i].socket, story, strlen(story), 0);
    }
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

int main() {
    WSADATA wsaData;
    SOCKET serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    int addrLen = sizeof(clientAddr);
    Player players[MAX_PLAYERS];
    char buffer[BUFFER_SIZE];
    int player_count = 0;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed. Error Code: %d\n", WSAGetLastError());
        return 1;
    }

    // Create a server socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        printf("Could not create socket. Error Code: %d\n", WSAGetLastError());
        return 1;
    }
    printf("Server socket created.\n");

    // Prepare the sockaddr_in structure
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    // Bind
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("Bind failed. Error Code: %d\n", WSAGetLastError());
        return 1;
    }
    printf("Bind successful.\n");

    // Listen
    if (listen(serverSocket, MAX_PLAYERS) == SOCKET_ERROR) {
        printf("Listen failed. Error Code: %d\n", WSAGetLastError());
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    printf("Awaiting Adventurers...\n");

    // Accept player connections
    while (player_count < MAX_PLAYERS) {
        clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &addrLen);
        if (clientSocket == INVALID_SOCKET) {
            printf("Accept failed. Error Code: %d\n", WSAGetLastError());
            closesocket(serverSocket);
            WSACleanup();
            return 1;
        }

        players[player_count].socket = clientSocket;
        players[player_count].is_active = 1;
        snprintf(players[player_count].color, sizeof(players[player_count].color), "\033[1;%dm", 31 + player_count); // Assign different colors
        player_count++;
        printf("Player %d connected.\n", player_count);

        // Enter player name
        send(clientSocket, "Enter your name: ", 18, 0);
        int bytesRead = recv(clientSocket, players[player_count - 1].name, sizeof(players[player_count - 1].name) - 1, 0);
        if (bytesRead > 0) {
            players[player_count - 1].name[bytesRead] = '\0'; // Null-terminate the string
            printf("Player %d name: %s\n", player_count, players[player_count - 1].name);
        } else {
            printf("recv failed: %d\n", WSAGetLastError());
            closesocket(clientSocket);
            closesocket(serverSocket);
            WSACleanup();
            return 1;
        }

        // If the first player, prompt to start the game
        if (player_count == 1) {
            send(clientSocket, "Type 'start' to begin the game.\n", 32, 0);
        }
    }

    // Wait for the first player to type "start"
    while (1) {
        int bytesRead = recv(players[0].socket, buffer, BUFFER_SIZE, 0);
        if (bytesRead > 0) {
            buffer[bytesRead] = '\0'; // Null-terminate the string
            if (strcmp(buffer, "start") == 0) {
                printf("Game started by Player 1.\n");
                for (int i = 0; i < player_count; i++) {
                    send(players[i].socket, "The game has started!\n", 22, 0);
                }
                startStory(players, player_count);
                break;
            } else {
                send(players[0].socket, "Invalid command. Type 'start' to begin the game.\n", 48, 0);
            }
        } else {
            printf("recv failed: %d\n", WSAGetLastError());
            closesocket(players[0].socket);
            closesocket(serverSocket);
            WSACleanup();
            return 1;
        }
    }

    // Game Start
    int choices[MAX_PLAYERS];
    while (1) {
        for (int i = 0; i < player_count; i++) {
            int bytesRead = recv(players[i].socket, buffer, BUFFER_SIZE, 0);
            if (bytesRead > 0) {
                buffer[bytesRead] = '\0'; // Null-terminate the string
                choices[i] = atoi(buffer); // Convert choice to integer
            } else {
                printf("recv failed: %d\n", WSAGetLastError());
                closesocket(players[i].socket);
                players[i].is_active = 0;
            }
        }

        // Randomize choices and send result to players
        int result = randomizeChoices(player_count, choices);
        char resultMessage[BUFFER_SIZE];
        if (result == 99) {
            snprintf(resultMessage, sizeof(resultMessage), "A funny random event occurs!\n");
        } else {
            snprintf(resultMessage, sizeof(resultMessage), "The chosen action is: %d\n", result);
        }

        for (int i = 0; i < player_count; i++) {
            if (players[i].is_active) {
                send(players[i].socket, resultMessage, strlen(resultMessage), 0);
            }
        }
    }

    // Cleanup
    for (int i = 0; i < player_count; i++) {
        closesocket(players[i].socket);
    }
    closesocket(serverSocket);
    WSACleanup();
    return 0;
}