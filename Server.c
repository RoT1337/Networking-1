#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h> 
#include <windows.h>

// Run using
// gcc -o server Server.c -lws2_32

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {
    WSADATA wsaData;
    SOCKET serverSocket, clientSocket;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen;
    int n, portNo;
    char buffer[255]; //Number of chars sent to clients from server

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        // If WSAStartup fails, print an error message and exit the program
        fprintf(stderr, "WSAStartup failed.\n");
        exit(1);
    }

    // Check if the port number is provided as a command-line argument
    if(argc < 2) {
        // If not, print an error message and exit the program
        fprintf(stderr, "Port No# not provided. Program terminated\n");
        exit(1);
    }

    // Create a socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSocket < 0) {
        error("Error opening Socket.");
    }

    // Set up the server address structure
    memset((char *)&serv_addr, 0, sizeof(serv_addr));
    portNo = atoi(argv[1]);
    serv_addr.sin_family = AF_INET; // Use IPv4
    serv_addr.sin_addr.s_addr = INADDR_ANY; // Accept connections from any IP address
    serv_addr.sin_port = htons(portNo); // Convert port number to network byte order

    // Bind the socket to the server address
    if(bind(serverSocket, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        error("Binding Failed.");
    }

    // Listen for incoming connections, with a backlog of 4
    listen(serverSocket, 4);
    clilen = sizeof(cli_addr); // Get the size of the client address structure

    printf("Awaiting Heroes.....\n");

    // Accept an incoming connection
    clientSocket = accept(serverSocket, (struct sockaddr *) &cli_addr, &clilen);

    // Check if the connection was accepted successfully
    if(clientSocket < 0) {
        error("Error on Accept");
    } else {
        printf("A Hero as joined the party!\n");
    }

    // Main loop to handle client communication
    while(1) {
        memset(buffer, 0, 255);
        n = recv(clientSocket, buffer, 255, 0);
        if (n < 0) {
            error("Error on reading");
        }

        printf("Client : %s\n", buffer);
        memset(buffer, 0, 255);
        fgets(buffer, 255, stdin);

        n = send(clientSocket, buffer, strlen(buffer), 0);
        if(n < 0) {
            error("Error on Writing");
        }

        int i = strncmp("Bye", buffer, 3);
        if (i == 0) {
            break;
        }
        
    }

    closesocket(clientSocket);
    closesocket(serverSocket);

    WSACleanup();

    return 0;
}