#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string>
#include <iostream>
#include <cstring>
#include <sstream>

int sockfd, errcode;
ssize_t n;
struct addrinfo hints, *res;
struct sockaddr_in serv_addr;
socklen_t addrlen;