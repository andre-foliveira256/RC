#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#define AS_ip "tejo.tecnico.ulisboa.pt"
#define AS_port "58011"


void client_login(char *userID,char *password, const char *ASip, const char *ASport) {

    // Create message
    




}
/* 
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
 */
int main(int argc, char *argv[]){
    int check = 1;
    char command[128], keywords[5][256],  userID[6], password[256];
    
    //define udp or tcp variables
    int fd, errcode;
    ssize_t n;
    socklen_t addrlen;
    struct addrinfo hints, *res;
    struct sockaddr_in addr;
    char buffer[128];
    
    
    if (argc != 1) {
        const char *as_ip = argv[2];
        const char *as_port = argv[4];
    }


    while (check) {
        fgets(command, sizeof(command), stdin);        
        char *token = strtok(command, " ");
        int i = 0;
        while (token != NULL) {
            strcpy(keywords[i], token);
            token = strtok(NULL, " ");
            i++;
        }

        //create socket        
        fd = socket(AF_INET, SOCK_DGRAM, 0);
        if (fd == -1) exit(1);
        memset(&hints, 0, sizeof hints);
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_DGRAM;
        hints.ai_flags = AI_NUMERICSERV;
        errcode = getaddrinfo(AS_ip, AS_port, &hints, &res);
        if (errcode != 0) exit(1);


        //check commands

        if (strcmp(keywords[0], "login") == 0) {
            strcpy(userID, keywords[1]);
            strcpy(password, keywords[2]);
            printf("userID: %s Password: %s\n", userID, password);
            client_login(userID, password, AS_ip, AS_port);
            //TODO: verificar se funciona a 100%;
        } 
        // Other command handling here...

        else if (strcmp(keywords[0], "myauctions") == 0 || strcmp(keywords[0], "ma") == 0) {
            strcpy(userID, keywords[1]);
            strcpy(password, keywords[2]);
            /* myauctions(userID, AS_ip, AS_port);
             *///TODO: ver se está a funcionar bem
        }

        else if (strcmp(keywords[0], "exit") == 0) {
            check = 0;
        }
    }
    return 0;
}
