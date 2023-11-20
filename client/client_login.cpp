#include "sockets.h"

void client_login(string userID, string password, char* AS_ip, char* AS_port){
    
    using namespace std;
    int sockfd, errcode;
    ssize_t n;
    struct addrinfo hints, *res;
    struct sockaddr_in serv_addr;
    socklen_t addrlen;


    string buffer = "LIN " + userID + " " + password +"\n";
    size_t len = strlen(buffer.c_str());
    const void* msg = static_cast<const void*>(buffer.c_str());
 
    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("ERROR opening socket");
    }

    // Get server
    errcode = getaddrinfo(AS_ip, AS_port, NULL, NULL);
    if (errcode != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(errcode));
    }

    n = sendto(sockfd, msg , len, 0, res->ai_addr, res->ai_addrlen);  
    if (n < 0) {
        perror("ERROR writing to socket");
    }

    char buffer2[20];
    n = recvfrom(sockfd, buffer2, 255, 0, res->ai_addr, &res->ai_addrlen);
    if (n < 0) {
        perror("ERROR reading from socket");
    }
    
    cout << buffer2 << endl;
    close(sockfd);
}