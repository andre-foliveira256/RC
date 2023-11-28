#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_BUFFER_SIZE 1024
#define AS_ip "tejo.tecnico.ulisboa.pt"
#define AS_port "58011"

void client_login(const char *userID, const char *password, const char *ASip, const char *ASport) {
    int sockfd, errcode;
    ssize_t n;
    struct addrinfo hints, *res;

    // Create message
    char msg[256];
    snprintf(msg, sizeof(msg), "LIN %s %s", userID, password);

    // Create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        printf("Error creating socket\n");
        exit(1);
    }

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET; // IPv4
    hints.ai_socktype = SOCK_DGRAM; // UDP socket

    // Get server
    errcode = getaddrinfo(AS_ip, AS_port, &hints, &res);
    if (errcode == -1) {
        printf("Error getting address info\n");
        exit(1);
    }

    n = sendto(sockfd, msg, strlen(msg), 0, res->ai_addr, res->ai_addrlen);
    if (n == -1) {
        printf("Error sending message\n");
        exit(1);
    }

    char buffer2[128];
    n = recvfrom(sockfd, buffer2, sizeof(buffer2), 0, NULL, NULL);
    if (n == -1) {
        printf("Error receiving message\n");
        exit(1);
    }

    printf("%s\n", buffer2);
    freeaddrinfo(res);
    close(sockfd);
}

void myauctions(const char *userID, const char *ASip, const char *ASport) {
    int clientSocket;
    struct sockaddr_in serverAddr;
    socklen_t addrSize = sizeof(serverAddr);

    clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (clientSocket < 0) {
        fprintf(stderr, "Error creating socket\n");
        return;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(atoi(ASport));
    serverAddr.sin_addr.s_addr = inet_addr(AS_ip);

    char requestMessage[256];
    snprintf(requestMessage, sizeof(requestMessage), "LMA %s", userID);

    sendto(clientSocket, requestMessage, strlen(requestMessage), 0,
           (struct sockaddr *)&serverAddr, sizeof(serverAddr));

    char buffer[128];
    memset(buffer, 0, sizeof(buffer));

    int bytesRead = recvfrom(clientSocket, buffer, sizeof(buffer), 0,
                             (struct sockaddr *)&serverAddr, &addrSize);

    if (bytesRead > 0) {
        printf("Received response: %s\n", buffer);
        // Process the received data (list of auctions or information message)
    } else {
        printf("No response received from the server.\n");
    }

    close(clientSocket);
}

int main() {
    int check = 1;
    char command[10], keywords[5][256], userID[256], password[256];

    while (check) {
        scanf("%s", command);
        getchar(); // To consume the newline character after reading command
        fgets(keywords[0], sizeof(keywords[0]), stdin);

        int i = 0;
        char *token = strtok(keywords[0], " \n");
        while (token != NULL && i < 5) {
            strcpy(keywords[i + 1], token);
            i++;
            token = strtok(NULL, " \n");
        }

        if (strcmp(command, "login") == 0) {
            strcpy(userID, keywords[1]);
            strcpy(password, keywords[2]);
            client_login(userID, password, AS_ip, AS_port);
            //TODO: verificar se funciona a 100%;
        } 
        // Other command handling here...

        else if (strcmp(command, "myauctions") == 0 || strcmp(command, "ma") == 0) {
            strcpy(userID, keywords[1]);
            strcpy(password, keywords[2]);
            myauctions(userID, AS_ip, AS_port);
            //TODO: ver se está a funcionar bem
        }

        else if (strcmp(command, "exit") == 0) {
            check = 0;
        }
    }
    return 0;
}
