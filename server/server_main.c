#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <signal.h>

#define GROUPPORT "5800041"
int v_mode = 1;

int main(int argc, char *argv[]){
    if(!strcmp(argv[argc-1], "-v")){
        v_mode = 0;
    }

    int sock_udp, sock_tcp, errcode, out_sock;
    ssize_t n;
    socklen_t addrlen;
    struct addrinfo hints_udp, hints_tcp, *res_udp, *res_tcp;
    struct sockaddr_in addr;
    char* port = GROUPPORT;
    fd_set inputs, testfds;

    sock_udp = socket(AF_INET, SOCK_DGRAM, 0);
    sock_tcp = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_udp == -1 || sock_tcp == -1) exit(1);

    memset(&hints_udp, 0, sizeof(hints_udp));

    hints_udp.ai_family = AF_INET;
    hints_udp.ai_socktype = SOCK_DGRAM;
    hints_udp.ai_flags = AI_PASSIVE;

    errcode = getaddrinfo(NULL, GROUPPORT, &hints_udp, res_udp);
    if(errcode !=0) exit(1);
    
    memset(&hints_tcp, 0, sizeof(hints_tcp));

    hints_tcp.ai_family = AF_INET;
    hints_tcp.ai_socktype = SOCK_STREAM;
    hints_tcp.ai_flags = AI_PASSIVE;

    errcode = getaddrinfo(NULL, GROUPPORT, &hints_tcp, &res_tcp);
    if (errcode != 0) exit(1);

    if(bind(sock_udp, res_udp->ai_addr, res_udp -> ai_addrlen) == -1) exit(1);
    if(bind(sock_tcp, res_tcp->ai_addr, res_tcp -> ai_addrlen) == -1)

    if(res_udp != NULL)
        freeaddrinfo(res_udp);
    if(res_tcp != NULL)
        freeaddrinfo(res_tcp);

    if(listen(sock_tcp, 5) == -1) exit(1);

    FD_ZERO(&inputs);
    FD_SET(sock_udp, &inputs);
    FD_SET(sock_tcp, &inputs);














    return 0;
}