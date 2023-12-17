#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>


int myauctions_udp(char* userID, char *message){
    struct stat st;
    char* path;
    char pass_f[35];
    char login_f[35];
    char auctions_f[35];

    if (strlen(userID) !=6){
        sprintf(message, "RMA ERR\n");
        return(0);
    }

    path = (char*)malloc(strlen("USERS/") + strlen(userID) + 1);
    sprintf(path, "USERS/%s", userID);
    sprintf(pass_f, "%s/%s_pass.txt", path, userID);
    sprintf(login_f, "%s/%s_login.txt", path, userID);
    sprintf(auctions_f, "%s/HOSTED", path);

    int c = check_login(userID, path, pass_f, login_f);
    
    if (c == 1){
        struct stat dir_stat;

        if (stat(path, &dir_stat) != 0) {
            sprintf(message, "RMA ERR\n"); 
        }

        if ((dir_stat.st_size == 4096) == 1){
            sprintf(message, "RMA NOK\n");
        }
        else{sprintf(message, "RMA OK\n");}
        
    }
    else if (c == 2){
        sprintf(message, "RMA NLG\n");
    }
    else{
        sprintf(message, "RMA ERR\n");
    }
    return(1);
}