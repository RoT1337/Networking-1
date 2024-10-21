#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h> 
#include <windows.h>

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {
    // Initialize Winsock
    WSADATA wsaData;
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

    int sockfd, newsockfd, portno, n;
    char buffer[255]; //Number of chars sent to clients from server

    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen;

    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) {
        error("Error opening Socket.");
    }

    // Clear the server address structure
    memset((char *) &serv_addr, 0, sizeof(serv_addr));
    portno = atoi(argv[1]); // Convert the port number from string to integer

    // Set up the server address structure
    serv_addr.sin_family = AF_INET; // Use IPv4
    serv_addr.sin_addr.s_addr = INADDR_ANY; // Accept connections from any IP address
    serv_addr.sin_port = htons(portno); // Convert port number to network byte order

    // Bind the socket to the server address
    if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        error("Binding Failed.");
    }

    // Listen for incoming connections, with a backlog of 4
    listen(sockfd, 4);
    clilen = sizeof(cli_addr); // Get the size of the client address structure

    // Accept an incoming connection
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

    // Check if the connection was accepted successfully
    if(newsockfd < 0) {
        error("Error on Accept");
    }

    // Main loop to handle client communication
    while(1) {
    }

    // Clean up Winsock
    WSACleanup();
    
    return 0;
}