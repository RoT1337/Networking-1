#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_PLAYERS 4

void handle_client(int client_socket, int player_id, int *choices) {
    char buffer[1024] = {0};
    int valread;

    valread = read(client_socket, buffer, 1024);
    if (valread > 0) {
        int choice = atoi(buffer);
        choices[player_id] = choice;
        printf("Player %d choice: %d\n", player_id + 1, choice);
    }

    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    int choices[MAX_PLAYERS] = {0};

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, MAX_PLAYERS) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Waiting for players to connect...\n");

    for (int i = 0; i < MAX_PLAYERS; i++) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        printf("Player %d connected\n", i + 1);
        if (fork() == 0) {
            handle_client(new_socket, i, choices);
            exit(0);
        }
    }

    // Wait for all players to make their choices
    sleep(5);

    // Determine majority choice
    int count[4] = {0};
    for (int i = 0; i < MAX_PLAYERS; i++) {
        count[choices[i]]++;
    }

    int majority_choice = 1;
    for (int i = 2; i <= 3; i++) {
        if (count[i] > count[majority_choice]) {
            majority_choice = i;
        }
    }

    printf("Majority choice: %d\n", majority_choice);

    close(server_fd);
    return 0;
}