#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "Ws2_32.lib")

#define PORT 8080
#define MAX_PLAYERS 4
#define BUFFER_SIZE 2048

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
        printf("Sent story to player %d\n", i + 1); // Debug
    }
}

void throughEntrance(Player players[], int player_count) {
    const char *story = "As you enter the entrance, you find yourself in a corridor that leads to 2 ways, left and right. What do you do?\n"
                        "1. Go left\n"
                        "2. Go right\n"
                        "3. Turn back\n";
    for (int i = 0; i < player_count; i++) {
        send(players[i].socket, story, strlen(story), 0);
        printf("Sent story to player %d\n", i + 1); // Debug
    }
}

void examineSurroundings(Player players[], int player_count) {
    if(player_count == 1) {
        const char *story = "You examine your surroundings and find an obsidian key. You decide to pick up the key. What do you do?\n"
                        "1. Go through the entrance\n"
                        "2. Turn back\n";
        send(players[0].socket, story, strlen(story), 0);
    } else {
        const char *story = "You examine your surroundings and find an obsidian key. The party leader decides to pick up the key. What do you do?\n"
                        "1. Go through the entrance\n"
                        "2. Turn back\n";
        for (int i = 0; i < player_count; i++) {
            send(players[i].socket, story, strlen(story), 0);
            printf("Sent story to player %d\n", i + 1); // Debug
        }
    }
}

void goLeftDoor(Player players[], int player_count) {
    const char *story = "You go through the door and all of a sudden it gets blocked by a stone wall coming up from the ground. Following that, 4 pillars rise. It seems to be a puzzle that requires the symbols within the pillar to be aligned. The roof of the room has something writ on it: 'The amount of arrows determines its face.'. What do you do?\n"
                        "1. Interact with pillar 'Eagle'\n"
                        "2. Interact with pillar 'Swan'\n"
                        "3. Interact with pillar 'Raven'\n"
                        "4. Interact with pillar 'Hawk'\n"
                        "5. Press the button to check the orientations\n";
    for (int i = 0; i < player_count; i++) {
        send(players[i].socket, story, strlen(story), 0);
        printf("Sent story to player %d\n", i + 1); // Debug
    }
}

void choseEaglePillar(Player players[], int player_count) {
    const char *story = "You interact with the Eagle pillar. An engraving on the pillar looks says this: 'North North North West'. What do you do?\n"
                        "1. Face the pillar north\n"
                        "2. Face the pillar east\n"
                        "3. Face the pillar south\n"
                        "4. Face the pillar west\n"
                        "5. Turn Back\n";
    for (int i = 0; i < player_count; i++) {
        send(players[i].socket, story, strlen(story), 0);
        printf("Sent story to player %d\n", i + 1); // Debug
    }
}

void choseSwanPillar(Player players[], int player_count) {
    const char *story = "You interact with the Swan pillar. An engraving on the pillar looks like this: 'North East East West'. What do you do?\n"
                        "1. Face the pillar north\n"
                        "2. Face the pillar east\n"
                        "3. Face the pillar south\n"
                        "4. Face the pillar west\n"
                        "5. Turn Back\n";
    for (int i = 0; i < player_count; i++) {
        send(players[i].socket, story, strlen(story), 0);
        printf("Sent story to player %d\n", i + 1); // Debug
    }
}

void choseRavenPillar(Player players[], int player_count) {
    const char *story = "You interact with the Raven pillar. An engraving on the pillar looks like this: 'North East South South'. What do you do?\n"
                        "1. Face the pillar north\n"
                        "2. Face the pillar east\n"
                        "3. Face the pillar south\n"
                        "4. Face the pillar west\n"
                        "5. Turn Back\n";
    for (int i = 0; i < player_count; i++) {
        send(players[i].socket, story, strlen(story), 0);
        printf("Sent story to player %d\n", i + 1); // Debug
    }
}

void choseHawkPillar(Player players[], int player_count) {
    const char *story = "You interact with the Hawk pillar. An engraving on the pillar looks like this: 'West West West West'. What do you do?\n"
                        "1. Face the pillar north\n"
                        "2. Face the pillar east\n"
                        "3. Face the pillar south\n"
                        "4. Face the pillar west\n"
                        "5. Turn Back\n";
    for (int i = 0; i < player_count; i++) {
        send(players[i].socket, story, strlen(story), 0);
        printf("Sent story to player %d\n", i + 1); // Debug
    }
}

void goRightDoor(Player players[], int player_count) {
    const char *story = "The path leads to a small, square room with a single pedestal in the center. On the pedestal, there is a set of three glowing orbs: red, blue, and green. The walls are inscribed with faint glowing text, hinting at the solution. What do you do?\n"
                        "1. Interact with the first wall.\n"
                        "2. Interact with the second wall.\n"
                        "3. Interact with the third wall.\n"
                        "4. Touch the large orb to check the orb's placements.\n";
    for (int i = 0; i < player_count; i++) {
        send(players[i].socket, story, strlen(story), 0);
        printf("Sent story to player %d\n", i + 1); // Debug
    }
}

void firstWallInteract(Player players[], int player_count) {
    const char *story = "You interact with the first wall. You noticed the wall has texts on it. It says: 'Passion opens the way but does not go last. What do you do?'\n"
                        "1. Place the red orb here.\n"
                        "2. Place the blue orb here.\n"
                        "3. Place the green orb here.\n"
                        "4. Return for a full view of the walls.\n";
    for (int i = 0; i < player_count; i++) {
        send(players[i].socket, story, strlen(story), 0);
        printf("Sent story to player %d\n", i + 1); // Debug
    }
}

void secondWallInteract(Player players[], int player_count) {
    const char *story = "You interact with the second wall. You noticed the wall has texts on it. It says: 'The color of envy follows the sea. What do you do?'\n"
                        "1. Place the red orb here.\n"
                        "2. Place the blue orb here.\n"
                        "3. Place the green orb here.\n"
                        "4. Return for a full view of the walls.\n";
    for (int i = 0; i < player_count; i++) {
        send(players[i].socket, story, strlen(story), 0);
        printf("Sent story to player %d\n", i + 1); // Debug
    }
}

void thirdWallInteract(Player players[], int player_count) {
    const char *story = "You interact with the third wall. You noticed the wall has texts on it. It says: 'The calm ocean's hue leads. What do you do?'\n"
                        "1. Place the red orb here.\n"
                        "2. Place the blue orb here.\n"
                        "3. Place the green orb here.\n"
                        "4. Return for a full view of the walls.\n";
    for (int i = 0; i < player_count; i++) {
        send(players[i].socket, story, strlen(story), 0);
        printf("Sent story to player %d\n", i + 1); // Debug
    }
}

void finish(Player players[], int player_count) {
     const char *story = "As you reach the bottom of the stairs, you are greeted by a treasure chest with which gold and splendor is stored inside. You finished your short quest!.\n";
    for (int i = 0; i < player_count; i++) {
        send(players[i].socket, story, strlen(story), 0);
        printf("Sent story to player %d\n", i + 1); // Debug
    }   
}

int randomizeChoices(int numClients, int *choices) {
    int randomValue = rand() % 100;
    if (randomValue < 70) { // 70% chance: Select the most common choice
        int count[5] = {0, 0, 0, 0, 0};
        for (int i = 0; i < numClients; i++) {
            count[choices[i] - 1]++;
        }
        int commonChoice = 1;
        if (count[1] > count[0]) commonChoice = 2;
        if (count[2] > count[1]) commonChoice = 3;
        if (count[3] > count[2]) commonChoice = 4;
        if (count[4] > count[3]) commonChoice = 5;
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
    int game_started = 0;

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
    serverAddr.sin_addr.s_addr = inet_addr("192.168.0.2");
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

    // Accept first player connection
    while (!game_started) {
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(serverSocket, &readfds);
        if (player_count > 0) {
            FD_SET(players[0].socket, &readfds);
        }

        struct timeval timeout;
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;

        int activity = select(0, &readfds, NULL, NULL, &timeout);

        if (activity == SOCKET_ERROR) {
            printf("select call failed with error code: %d\n", WSAGetLastError());
            closesocket(serverSocket);
            WSACleanup();
            return 1;
        }

        // Check if we need to accept more players
        if (FD_ISSET(serverSocket, &readfds) && player_count < MAX_PLAYERS) {
            clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &addrLen);
            if (clientSocket != INVALID_SOCKET) {
                players[player_count].socket = clientSocket;
                players[player_count].is_active = 1;
                snprintf(players[player_count].color, sizeof(players[player_count].color), "\033[1;%dm", 31 + player_count); // Assign different colors
                player_count++;
                printf("Player %d connected.\n", player_count);

                send(players[player_count - 1].socket, "Enter your name: ", 18, 0);
                int bytesRead = recv(players[player_count - 1].socket, players[player_count - 1].name, sizeof(players[player_count - 1].name) - 1, 0);
                if (bytesRead > 0) {
                    players[player_count - 1].name[bytesRead] = '\0'; // Null-terminate the string
                    printf("Player %d name: %s\n", player_count, players[player_count - 1].name);
                } else {
                    printf("recv failed: %d\n", WSAGetLastError());
                    closesocket(players[player_count - 1].socket);
                    players[player_count - 1].is_active = 0;
                }

                // If the first player, prompt to start the game
                if (player_count == 1) {
                    send(clientSocket, "Type 'start' to begin the game.\n", 32, 0);
                }
            }
        }

        // Check if the first player has typed "start"
        if (player_count > 0 && FD_ISSET(players[0].socket, &readfds)) {
            int bytesRead = recv(players[0].socket, buffer, BUFFER_SIZE, 0);
            if (bytesRead > 0) {
                buffer[bytesRead] = '\0'; // Null-terminate the string
                printf("Received from player: %s\n", buffer); // Debug print
                if (strcmp(buffer, "start") == 0) {
                    printf("Game started by Player 1.\n");
                    game_started = 1;
                } else {
                    send(players[0].socket, "Invalid command. Type 'start' to begin the game.\n", 48, 0);
                    printf("Sent invalid command message to player 1\n"); // Debug print
                    // Debug Cleanup
                    for (int i = 0; i < player_count; i++) {
                        closesocket(players[i].socket);
                    }
                    
                    closesocket(serverSocket);
                    WSACleanup();
                }
            } else if (bytesRead == SOCKET_ERROR) {
                printf("recv failed: %d\n", WSAGetLastError());
                closesocket(players[0].socket);
                players[0].is_active = 0;
            }
        }
    }

    // Game loop
    int game_over = 0;
    int level = 0; // Maybe add save file through this variable
    int groupChoice = 0;
    int choices[MAX_PLAYERS];
    char resultMessage[BUFFER_SIZE];

    // Items
    int obsidianKey = 0;
    int weaponAndArmor = 0;

    //For Level 1
    int choseLeftDoor = 0;
    int choseRightDoor = 0;
    int doorState = 0;
    // 1 North, 2 East, 3 South, 4 West
    int eagleFace = 0;
    int swanFace = 0;
    int ravenFace = 0;
    int hawkFace = 0;
    // Left Door Option Picked
    int eagle = 0;
    int swan = 0;
    int raven = 0;
    int hawk = 0;
    int pillarDone = 0;
    // 1 First Wall, 2 Second Wall, 3 Third Wall
    int redOrb = 0;
    int blueOrb = 0;
    int greenOrb = 0;
    // Right Door Option Picked
    int firstWall = 0;
    int secondWall = 0;
    int thirdWall = 0;
    int wallsDone = 0;

    while (game_over == 0) {
        switch (level) {
            case 0:
                if (groupChoice == 2) {
                    examineSurroundings(players, player_count);
                    obsidianKey = 1;
                    printf("Obsidian Key Get\n");
                } else {
                    startStory(players, player_count);
                }
                break; // Works!
            case 1:
                if (groupChoice == 1) {
                    if (choseLeftDoor == 1 && doorState == 1) {
                        if (eagle == 1) {
                            choseEaglePillar(players, player_count);
                        } else if (swan == 1) {
                            choseSwanPillar(players, player_count);
                        } else if (raven == 1) {
                            choseRavenPillar(players, player_count);
                        } else if (hawk == 1) {
                            choseHawkPillar(players, player_count);
                        } else {
                            goLeftDoor(players, player_count);
                        }
                    } else if (choseRightDoor == 1 && doorState == 1) {
                        if (firstWall == 1) {
                            firstWallInteract(players, player_count);
                        } else if (secondWall == 1) {
                            secondWallInteract(players, player_count);
                        } else if (thirdWall == 1) {
                            thirdWallInteract(players, player_count);
                        } else {
                            goRightDoor(players, player_count);
                        }
                    } else {
                        throughEntrance(players, player_count);
                    }
                } else if (groupChoice == 4) { 
                    if (wallsDone == 1) {
                        const char *story = "The orbs glow and the barriers are lowered. This also reveals a pathway heading downwards.\n\n";
                        for (int i = 0; i < player_count; i++) {
                            send(players[i].socket, story, strlen(story), 0);
                            printf("Sent story to player %d\n", i + 1); // Debug
                        }
                        finish(players, player_count);
                        game_over = 0;
                    } else {
                        const char *story = "Nothing Happens\n\n";
                        for (int i = 0; i < player_count; i++) {
                            send(players[i].socket, story, strlen(story), 0);
                            printf("Sent story to player %d\n", i + 1); // Debug
                        }
                        groupChoice = 1;
                        goRightDoor(players, player_count);
                    }

                } else if (groupChoice == 5) {
                    if (pillarDone == 1) {
                        const char *story = "The button clicks as the stone blocking the door is lowered. This also reveals a pathway heading downwards.\n\n";
                        for (int i = 0; i < player_count; i++) {
                            send(players[i].socket, story, strlen(story), 0);
                            printf("Sent story to player %d\n", i + 1); // Debug
                        }
                        finish(players, player_count);
                        game_over = 0;
                    } else {
                        const char *story = "Nothing Happens\n\n";
                        for (int i = 0; i < player_count; i++) {
                            send(players[i].socket, story, strlen(story), 0);
                            printf("Sent story to player %d\n", i + 1); // Debug
                        }
                        groupChoice = 1;
                        goLeftDoor(players, player_count);
                    }
                }
                break;
            case 2:
                finish(players, player_count);
                break;
            default:
                snprintf(resultMessage, sizeof(resultMessage), "Unexpected error, contact a programmer!\n");
                break;
        }
        
        for (int i = 0; i < player_count; i++) {
            int bytesRead = recv(players[i].socket, buffer, BUFFER_SIZE, 0);
            if (bytesRead > 0) {
                buffer[bytesRead] = '\0'; 
                choices[i] = atoi(buffer); 
            } else {
                printf("recv failed: %d\n", WSAGetLastError());
                closesocket(players[i].socket);
                players[i].is_active = 0;
            }
        }

        // Randomize choices and send result to players
        int result = randomizeChoices(player_count, choices);

        if (level == 0) { // Good!
            if (obsidianKey == 0) {
                switch(result) { //startStory
                    case 1:
                        snprintf(resultMessage, sizeof(resultMessage), "You go through the entrance.\n");
                        groupChoice = 1;
                        level = 1;
                        break;
                    case 2:
                        snprintf(resultMessage, sizeof(resultMessage), "You examine your surroundings.\n");
                        groupChoice = 2;
                        break;
                    case 3:
                        snprintf(resultMessage, sizeof(resultMessage), "You turn back.\n");
                        game_over = 1;
                        break;
                    case 99:
                        snprintf(resultMessage, sizeof(resultMessage), "Bad luck brought you here.\n");
                        game_over = 1;
                        break;
                    default:
                        snprintf(resultMessage, sizeof(resultMessage), "If you get this message, contact a programmer\n");
                        game_over = 1;
                        break;
                }
            } else {
                switch(result) { //examineSurroundings
                    case 1:
                        snprintf(resultMessage, sizeof(resultMessage), "You go through the entrance.\n");
                        groupChoice = 1;
                        level = 1;
                        break;
                    case 2:
                        snprintf(resultMessage, sizeof(resultMessage), "You turn back.\n");
                        game_over = 1;
                        break;
                    default:
                        snprintf(resultMessage, sizeof(resultMessage), "If you get this message, contact a programmer\n");
                        game_over = 1;
                        break;
                }
            }
        // ============================================================================================================
        } else if (level == 1) {
            if (groupChoice == 1) {
                if (choseLeftDoor == 1 && doorState == 1) { // goLeftDoor
                    printf("Eagle: %d, Swan: %d, Raven: %d, Hawk: %d\n", eagleFace, swanFace, ravenFace, hawkFace); // Debug
                    if (eagle == 0 && swan == 0 && raven == 0 && hawk == 0 ) {
                        switch(result) {
                            case 1: // Eagle
                                snprintf(resultMessage, sizeof(resultMessage), "You choose the 'Eagle' pillar\n");
                                eagle = 1;
                                break;
                            case 2: // Swan
                                snprintf(resultMessage, sizeof(resultMessage), "You choose the 'Swan' pillar\n");
                                swan = 1;
                                break;
                            case 3:
                                snprintf(resultMessage, sizeof(resultMessage), "You choose the 'Raven' pillar\n");
                                raven = 1;
                                break;
                            case 4:
                                snprintf(resultMessage, sizeof(resultMessage), "You choose the 'Hawk' pillar\n");
                                hawk = 1;
                                break;
                            case 5:
                                snprintf(resultMessage, sizeof(resultMessage), "You press the button\n");
                                groupChoice = 5;
                                if(eagleFace == 1 && swanFace == 2 && ravenFace == 3 && hawkFace == 4) {
                                    pillarDone = 1;
                                    level = 2;
                                } 
                                break;
                            default: 
                                snprintf(resultMessage, sizeof(resultMessage), "If you somehow get this message, contact a programmer\n");
                                game_over = 1;
                                break;
                        }
                    } else if (eagle == 1) {
                        switch(result) {
                            case 1: // North
                                snprintf(resultMessage, sizeof(resultMessage), "You face the 'Eagle' pillar north.\n");
                                eagleFace = 1;
                                break;
                            case 2: // East
                                snprintf(resultMessage, sizeof(resultMessage), "You face the 'Eagle' pillar east.\n");
                                eagleFace = 2;
                                break;
                            case 3: // South
                                snprintf(resultMessage, sizeof(resultMessage), "You face the 'Eagle' pillar south.\n");
                                eagleFace = 3;
                                break;
                            case 4: // West
                                snprintf(resultMessage, sizeof(resultMessage), "You face the 'Eagle' pillar west.\n");
                                eagleFace = 4;
                                break;
                            case 5: // Turn Back
                                snprintf(resultMessage, sizeof(resultMessage), "You return to look at the 4 pillars.\n");
                                eagle = 0;
                                break;
                            default:
                                snprintf(resultMessage, sizeof(resultMessage), "If you get this message, contact a programmer\n");
                                game_over = 1;
                                break;                                
                        }
                    } else if (swan == 1) {
                        switch(result) {
                            case 1: // North
                                snprintf(resultMessage, sizeof(resultMessage), "You face the 'Swan' pillar north.\n");
                                swanFace = 1;
                                break;
                            case 2: // East
                                snprintf(resultMessage, sizeof(resultMessage), "You face the 'Swan' pillar east.\n");
                                swanFace = 2;
                                break;
                            case 3: // South
                                snprintf(resultMessage, sizeof(resultMessage), "You face the 'Swan' pillar south.\n");
                                swanFace = 3;
                                break;
                            case 4: // West
                                snprintf(resultMessage, sizeof(resultMessage), "You face the 'Swan' pillar west.\n");
                                swanFace = 4;
                                break;
                            case 5: // Turn Back
                                snprintf(resultMessage, sizeof(resultMessage), "You return to look at the 4 pillars.\n");
                                swan = 0;
                                break;
                            default:
                                snprintf(resultMessage, sizeof(resultMessage), "If you get this message, contact a programmer\n");
                                game_over = 1;
                                break;  
                        }
                    } else if (raven == 1) {
                        switch(result) {
                            case 1: // North
                                snprintf(resultMessage, sizeof(resultMessage), "You face the 'Raven' pillar north.\n");
                                ravenFace = 1;
                                break;
                            case 2: // East
                                snprintf(resultMessage, sizeof(resultMessage), "You face the 'Raven' pillar east.\n");
                                ravenFace = 2;
                                break;
                            case 3: // South
                                snprintf(resultMessage, sizeof(resultMessage), "You face the 'Raven' pillar south.\n");
                                ravenFace = 3;
                                break;
                            case 4: // West
                                snprintf(resultMessage, sizeof(resultMessage), "You face the 'Raven' pillar west.\n");
                                ravenFace = 4;
                                break;
                            case 5: // Turn Back
                                snprintf(resultMessage, sizeof(resultMessage), "You return to look at the 4 pillars.\n");
                                raven = 0;
                                break;
                            default:
                                snprintf(resultMessage, sizeof(resultMessage), "If you get this message, contact a programmer\n");
                                game_over = 1;
                                break;  
                        }
                    } else if (hawk == 1) {
                        switch(result) {
                            case 1: // North
                                snprintf(resultMessage, sizeof(resultMessage), "You face the 'Hawk' pillar north.\n");
                                hawkFace = 1;
                                break;
                            case 2: // East
                                snprintf(resultMessage, sizeof(resultMessage), "You face the 'Hawk' pillar east.\n");
                                hawkFace = 2;
                                break;
                            case 3: // South
                                snprintf(resultMessage, sizeof(resultMessage), "You face the 'Hawk' pillar south.\n");
                                hawkFace = 3;
                                break;
                            case 4: // West
                                snprintf(resultMessage, sizeof(resultMessage), "You face the 'Hawk' pillar west.\n");
                                hawkFace = 4;
                                break;
                            case 5: // Turn Back
                                snprintf(resultMessage, sizeof(resultMessage), "You return to look at the 4 pillars.\n");
                                hawk = 0;
                                break;
                            default:
                                snprintf(resultMessage, sizeof(resultMessage), "If you get this message, contact a programmer\n");
                                game_over = 1;
                                break;  
                        }
                    }
                } else if (choseRightDoor == 1 && doorState == 1) { // goRightDoor
                    printf("Red Orb: %d, Blue Orb: %d, Green Orb: %d\n", redOrb, blueOrb, greenOrb); // Debug
                    if (firstWall == 0 && secondWall == 0 && thirdWall == 0) {
                        switch(result) {
                            case 1:
                                snprintf(resultMessage, sizeof(resultMessage), "You interact with the first wall\n");
                                firstWall = 1;
                                break;
                            case 2:
                                snprintf(resultMessage, sizeof(resultMessage), "You interact with the second wall\n");
                                secondWall = 1;
                                break;
                            case 3:
                                snprintf(resultMessage, sizeof(resultMessage), "You interact with the third wall\n");
                                thirdWall = 1;
                                break;
                            case 4:
                                snprintf(resultMessage, sizeof(resultMessage), "You touch the large orb to check the placements\n");
                                groupChoice = 4;
                                if(redOrb == 1 && greenOrb == 2 && blueOrb == 3) {
                                    wallsDone = 1;
                                    level = 2;
                                } 
                                break;
                            default:
                                snprintf(resultMessage, sizeof(resultMessage), "If you get this message, contact a programmer\n");
                                game_over = 1;
                                break;  
                        }
                    } else if (firstWall == 1) {
                        switch(result) {
                            case 1:
                                snprintf(resultMessage, sizeof(resultMessage), "You place the red orb here\n");
                                redOrb = 1;
                                break;
                            case 2:
                                snprintf(resultMessage, sizeof(resultMessage), "You place the blue orb here\n");
                                blueOrb = 1;
                                break;
                            case 3:
                                snprintf(resultMessage, sizeof(resultMessage), "You place the green orb here\n");
                                greenOrb = 1;
                                break;
                            case 4:
                                snprintf(resultMessage, sizeof(resultMessage), "You return for a full view of the walls\n");
                                firstWall = 0;
                                break;
                            default:
                                snprintf(resultMessage, sizeof(resultMessage), "If you get this message, contact a programmer\n");
                                game_over = 1;
                                break;  
                        }
                    } else if (secondWall == 1) {
                        switch(result) {
                            case 1:
                                snprintf(resultMessage, sizeof(resultMessage), "You place the red orb here\n");
                                redOrb = 2;
                                break;
                            case 2:
                                snprintf(resultMessage, sizeof(resultMessage), "You place the blue orb here\n");
                                blueOrb = 2;
                                break;
                            case 3:
                                snprintf(resultMessage, sizeof(resultMessage), "You place the green orb here\n");
                                greenOrb = 2;
                                break;
                            case 4:
                                snprintf(resultMessage, sizeof(resultMessage), "You return for a full view of the walls\n");
                                secondWall = 0;
                                break;
                            default:
                                snprintf(resultMessage, sizeof(resultMessage), "If you get this message, contact a programmer\n");
                                game_over = 1;
                                break;  
                        }
                    } else if (thirdWall = 1) {
                        switch(result) {
                            case 1:
                                snprintf(resultMessage, sizeof(resultMessage), "You place the red orb here\n");
                                redOrb = 3;
                                break;
                            case 2:
                                snprintf(resultMessage, sizeof(resultMessage), "You place the blue orb here\n");
                                blueOrb = 3;
                                break;
                            case 3:
                                snprintf(resultMessage, sizeof(resultMessage), "You place the green orb here\n");
                                greenOrb = 3;
                                break;
                            case 4:
                                snprintf(resultMessage, sizeof(resultMessage), "You return for a full view of the walls\n");
                                thirdWall = 0;
                                break;
                            default:
                                snprintf(resultMessage, sizeof(resultMessage), "If you get this message, contact a programmer\n");
                                game_over = 1;
                                break;  
                        }
                    }
                } else {
                    switch(result) { //goThroughEntrance
                        case 1:
                            snprintf(resultMessage, sizeof(resultMessage), "You go left.\n");
                            choseLeftDoor = 1;
                            doorState = 1;
                            break;
                        case 2:
                            snprintf(resultMessage, sizeof(resultMessage), "You go right.\n");
                            choseRightDoor = 1;
                            doorState = 1;
                            break;
                        case 3:
                            snprintf(resultMessage, sizeof(resultMessage), "You turn back.\n");
                            game_over = 1;
                            break;
                        case 99:
                            snprintf(resultMessage, sizeof(resultMessage), "Bad luck for level 1 depth is kinda L bro no skibidi.\n");
                            game_over = 1;
                            break;
                        default:
                            snprintf(resultMessage, sizeof(resultMessage), "If you somehow get this message, contact a programmer\n");
                            game_over = 1;
                            break;

                    }
                }
                printf("Level: %d, GroupChoice: %d, Result: %d\n", level, groupChoice, result); // Debug output
            }
        // ============================================================================================================    
        } 
        for (int i = 0; i < player_count; i++) {
            if (players[i].is_active) {
                send(players[i].socket, resultMessage, strlen(resultMessage), 0);
                printf("Sent result to player %d\n", i + 1); // Debug
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