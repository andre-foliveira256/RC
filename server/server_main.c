#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include "includes.h"

#define GROUPPORT "58041"

int v_mode = 1;
char* port;
char buf[1024];

int main(int argc, char *argv[]){
    int out_fds;
    
    if (argc > 1){
        if(!strcmp(argv[argc-1], "-v")){
            v_mode = 0;
        }
        if(!strcmp(argv[1], "-p")){
            port = argv[2];
        }
    }
    else{
        port = GROUPPORT;
    }



    int sock_udp, sock_tcp, errcode, out_sock;
    ssize_t n;
    socklen_t addrlen;
    struct addrinfo hints_udp, hints_tcp, *res_udp, *res_tcp;
    struct sockaddr_in addr;
    fd_set inputs, testfds;

    sock_udp = socket(AF_INET, SOCK_DGRAM, 0);
    sock_tcp = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_udp == -1 || sock_tcp == -1) exit(1);

    memset(&hints_udp, 0, sizeof(hints_udp));

    hints_udp.ai_family = AF_INET;
    hints_udp.ai_socktype = SOCK_DGRAM;
    hints_udp.ai_flags = AI_PASSIVE;

    errcode = getaddrinfo(NULL, port, &hints_udp, &res_udp);
    if(errcode !=0) exit(1);
    
    memset(&hints_tcp, 0, sizeof(hints_tcp));

    hints_tcp.ai_family = AF_INET;
    hints_tcp.ai_socktype = SOCK_STREAM;
    hints_tcp.ai_flags = AI_PASSIVE;

    errcode = getaddrinfo(NULL, port, &hints_tcp, &res_tcp);
    if (errcode != 0) exit(1);

    if(bind(sock_udp, res_udp->ai_addr, res_udp -> ai_addrlen) == -1) exit(1);
    if(bind(sock_tcp, res_tcp->ai_addr, res_tcp -> ai_addrlen) == -1) exit(1);

    if(res_udp != NULL)
        freeaddrinfo(res_udp);
    if(res_tcp != NULL)
        freeaddrinfo(res_tcp);

    printf("Server is running...\n");
    if(listen(sock_tcp, 5) == -1) exit(1);

    FD_ZERO(&inputs);
    FD_SET(sock_udp, &inputs);
    FD_SET(sock_tcp, &inputs);


    while(1){
        testfds = inputs;
        out_sock = select(FD_SETSIZE, &testfds, (fd_set *)NULL, (fd_set *)NULL, NULL);
        
        
        
        //udp
        if(FD_ISSET(sock_udp, &testfds)){
            addrlen=sizeof(addr);
            n= recvfrom(sock_udp, buf, sizeof(buf), 0, (struct sockaddr *)&addr, &addrlen);
            if(n==-1) exit(1);
            char client_ip[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &(addr.sin_addr), client_ip, INET_ADDRSTRLEN);
            
            read_msg(buf, v_mode, client_ip, port);

            n = sendto(sock_udp, buf, strlen(buf), 0, (struct sockaddr *)&addr, addrlen);
            if(n==-1) exit(1);
        }


        //tcp
        if(FD_ISSET(sock_tcp, &testfds)){
            int new_sock;
            addrlen=sizeof(addr);

            if((new_sock = accept(sock_tcp, (struct sockaddr *)&addr, &addrlen)) == -1) exit(1);
            n= read(new_sock, buf, sizeof(buf));
            if(n==-1) exit(1);
            char client_ip[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &(addr.sin_addr), client_ip, INET_ADDRSTRLEN);
            
            read_msg(buf, v_mode, client_ip, port);

            n = write(new_sock, buf, strlen(buf));
            if(n==-1) exit(1);
            close(new_sock);
        }


    }
    freeaddrinfo(res_udp);
    freeaddrinfo(res_tcp);
    close(sock_udp);
    close(sock_tcp);
    return 0;
}