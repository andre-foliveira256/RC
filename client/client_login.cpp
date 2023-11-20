#include "sockets.h"
using namespace std;


void client_login(string userID, string password,const char* AS_ip,const  char* AS_port){
    
    using namespace std;
    int sockfd, errcode;
    ssize_t n;
    struct addrinfo hints, *res;
    struct sockaddr_in serv_addr;
    socklen_t addrlen;


    // Create message
    string msg = "LIN " + userID + " " + password;
    char *msg_c = new char[msg.length() + 1];
    strcpy(msg_c, msg.c_str());
    int len = strlen(msg_c);
    cout << msg_c << endl;
 
    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd==-1) /*error*/ {
        cout << "Error creating socket" << endl;
        exit(1);}

    memset(&hints,0,sizeof hints);
    hints.ai_family=AF_INET; //IPv4
    hints.ai_socktype=SOCK_DGRAM; //UDP socket


    // Get server
    errcode = getaddrinfo(AS_ip, AS_port, &hints, &res);
    if(n==-1) /*error*/ {
        cout << "Error getting address info" << endl;
        exit(1);}

    n = sendto(sockfd, msg_c , len, 0, res->ai_addr, res->ai_addrlen);  
    if(n==-1) /*error*/{ 
        cout << "Error sending message" << endl;
        exit(1);}
    


    char buffer2[128];
    n=recvfrom(sockfd,buffer2,128,0, (struct sockaddr*)&serv_addr,&addrlen);
    if(n==-1) /*error*/ {
        cout << "Error receiving message" << endl;
        exit(1);}


    cout << buffer2 << endl;
    freeaddrinfo(res);
    close(sockfd);
}