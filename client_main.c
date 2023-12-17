#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <sys/sendfile.h>
#include "client/includes.h"


#define AS_ip "localhost"
#define AS_port "58041"

char userID[16];
char password[16];
char* ip;
char* port;
char msg[128];
char buffer[6010];
char path[128];
char tcp_check[1];


int send_file(int fd, char *path){
    FILE *fp = fopen(path, "r");
    if (fp == NULL){
        printf("File does not exist.\n");
        return -1;
    }
    int n;
    struct stat filestat;
    int ret_stat;
    ret_stat = stat(path , &filestat);
    int fsize = filestat.st_size;
    int filefd = fileno(fp);
    n = sendfile(fd, filefd, NULL, fsize);
    if (n == -1) printf("ERR\n");
    fclose(fp);
}

int read_buffer(int fd, char* message,int n_words){
    int words_read = 0;
    int n;
    char c[1];
    memset(message, 0, sizeof(message));

    while(words_read < n_words){
        n = read(fd, c, 1);
        if (n == -1) exit(1);
        if (c[0] == ' ')
            words_read++;
        strcat(message, c);
    }

}



int receive_file(int fd, char * fname, int fsize){
    size_t bytesReceived = 0;
    size_t n, nr;

    char img[128];
    sprintf(path, "IMGS/%s", fname);
    memset(img, 0, 128);
    FILE *fp = fopen(path, "w");
    
    while(bytesReceived < fsize){
        nr = read(fd, img, sizeof(img));
        ssize_t n_received = 0;
        while (n_received < nr){
            n_received = fwrite(img, 1, nr, fp);
            nr += n_received;
        }
        bytesReceived += nr;
    }
    fclose(fp);
}


int main(int argc, char *argv[]){
    int check = 1, sock_mode;
    char input[128];
    //define socket variables
    int fd, errcode;
    ssize_t n;
    socklen_t addrlen;
    struct addrinfo hints, *res;
    struct sockaddr_in addr;
    


    //define port and ip
    if (argc != 1) {
        for (int i = 1; i < argc; i++){
            if (strcmp(argv[i], "-n") == 0){
                ip = argv[i+1];
            }
            else if (strcmp(argv[i], "-p") == 0){
                port = argv[i+1];
            }
        }
    }
    else{
        ip = AS_ip;
        port = AS_port;
    }

    //user app
    while (check) {
        printf("> ");    
        fgets(input, sizeof(input), stdin);
        sock_mode = read_input(buffer, input, userID, password, tcp_check, path);
        
        //open socket
       if (sock_mode == UDP){
            //create udp socket        
            fd = socket(AF_INET, SOCK_DGRAM, 0);
            if (fd == -1) exit(1);
            memset(&hints, 0, sizeof hints);
            hints.ai_family = AF_INET;
            hints.ai_socktype = SOCK_DGRAM;
            errcode = getaddrinfo(ip, port, &hints, &res);
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

            errcode = getaddrinfo(ip, port, &hints, &res);
            if (errcode !=0) exit(1);

            //connect socket
            n = connect(fd, res->ai_addr, res->ai_addrlen);
            if (n==-1) exit(1);

            //send message

            n = write(fd, buffer, sizeof(buffer));
            if (n==-1) exit(1);

            //receive message
            if (strcmp(tcp_check, "1") == 0){
                n = send_file(fd, path);}
           
            if (strcmp(tcp_check, "2") == 0){
                read_buffer(fd, msg, 2);
                translate_buff(msg);
                if (!strcmp(msg, "c")){
                    read_buffer(fd, msg, 2);
                    char* fname = strtok(msg, " ");
                    int fsize = atoi(strtok(NULL, " "));
                    receive_file(fd, fname, fsize);
                }
                
            }
            else{
                n = read(fd, msg, sizeof(msg));
                translate_buff(msg);
            }

            if (n==-1) exit(1);
            memset(msg, 0, sizeof(msg));
            memset(buffer, 0, sizeof(buffer));

            close(fd);
            freeaddrinfo(res);
        }
        else if(sock_mode == EXIT) exit(1);
    }
    return 0;
}
