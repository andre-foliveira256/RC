#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include "client_login.c"
#include "client_logout.c"
#include "client_unregister.c"
#include "translate_buff.c"
#include "read_input.c"


#define AS_ip "tejo.tecnico.ulisboa.pt"
#define AS_port "58011"
#define UDP 1
#define TCP 0

char msg[128];
char userID[6];
char password[8];
char buffer[128];

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
    int check = 1, sock_mode;
    char input[128];
    
    //define socket variables
    int fd, errcode;
    ssize_t n;
    socklen_t addrlen;
    struct addrinfo hints, *res;
    struct sockaddr_in addr;
    
    if (argc != 1) {
        const char *as_ip = argv[2];
        const char *as_port = argv[4];
    }


    while (check) {        
        fgets(input, sizeof(input), stdin);
        sock_mode = read_input(buffer, input, userID, password);
        
        //open socket
       if (sock_mode == UDP){
            //create udp socket        
            fd = socket(AF_INET, SOCK_DGRAM, 0);
            if (fd == -1) exit(1);
            memset(&hints, 0, sizeof hints);
            hints.ai_family = AF_INET;
            hints.ai_socktype = SOCK_DGRAM;
            errcode = getaddrinfo(AS_ip, AS_port, &hints, &res);
            if (errcode != 0) exit(1);
            //send message
            n = sendto(fd, buffer, strlen(buffer), 0, res->ai_addr, res->ai_addrlen);
            if (n == -1) exit(1);

            //receive message
            addrlen = sizeof(addr);
            n = recvfrom(fd, msg, sizeof(buffer), 0, (struct sockaddr *)&addr, &addrlen);
            if (n == -1) exit(1);
            translate_buff(msg);
            memset(msg, '\0', sizeof(msg));
            memset(buffer, '\0', sizeof(buffer));
            close(fd);
            freeaddrinfo(res);
        }
        else if(sock_mode == TCP){
            //create tcp socket
            fd = socket(AF_INET, SOCK_STREAM, 0);
            if (fd == -1) exit(1);
            memset(&hints, 0, sizeof hints);
            hints.ai_family = AF_INET;
            hints.ai_socktype = SOCK_STREAM;

            errcode = getaddrinfo(AS_ip, AS_port, &hints, &res);
            if (errcode !=0) exit(1);

            //connect socket
            n = connect(fd, res->ai_addr, res->ai_addrlen);
            if (n!=0) exit(1);

            //send message
            n = write(fd, buffer, strlen(buffer));
            if (n!=0) exit(1);

            translate_buff(msg);
            memset(msg, '\0', sizeof(msg));
            memset(buffer, '\0', sizeof(buffer));

            close(fd);
            freeaddrinfo(res);

        }
        else if(sock_mode == EXIT) exit(1);

        //analyse message
        


        //close socket
        
    

    }
    return 0;
}
