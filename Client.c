#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h> 
#include <windows.h>

// Run using
// gcc -o client Client.c -lws2_32

// For connecting, get ipconfig of server
// get IPV4

// If connecting on the same system use
// client [127.0.0.1] [port]

void error(const char *msg) {
    char *s = NULL;
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                  NULL, WSAGetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&s, 0, NULL);
    fprintf(stderr, "%s: %s\n", msg, s);
    LocalFree(s);
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

    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[255];
    if (argc < 3) {
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        exit(1);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("ERROR opening socket");
    }

    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr, "Error, no such host");
    }

    memset((char *) &serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    memcpy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
    if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        error("Connection Failed");
    }

    while(1) {
        memset(buffer, 0, 255);
        fgets(buffer, 255, stdin);
        n = send(sockfd, buffer, strlen(buffer), 0);
        if (n < 0) {
            error("Error on writing");
        }

        memset(buffer, 0, 255);
        n = recv(sockfd, buffer, 255, 0);
        if (n < 0) {
            error("Error on reading");
        }
        printf("Server: %s", buffer);

        int i = strncmp("Bye", buffer, 3);
        if (i == 0) {
            break;
        }
    }

    closesocket(sockfd);

    WSACleanup();
    
    return 0;
}