#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>

int unregister_udp(char* userID, char* password, char *message){
    struct stat st;
    char* path;
    char pass_f[35];
    char login_f[35];

    if (strlen(userID) !=6){
        sprintf(message, "RUR ERR\n");
        return(0);
    }
    path = (char*)malloc(strlen("USERS/") + strlen(userID) + 1);
    sprintf(path, "USERS/%s", userID);
    sprintf(pass_f, "%s/%s_pass.txt", path, userID);
    sprintf(login_f, "%s/%s_login.txt", path, userID);

    int c = check_login(userID, path, pass_f, login_f);
    if (c == 0){
        sprintf(message, "RUR UNR\n");
    }
    else if (c == 1){
        sprintf(message, "RUR OK\n");
        unlink(pass_f);
        unlink(login_f);
    }
    else if (c == 2){
        sprintf(message, "RUR NOK\n");
    }
    else{
        sprintf(message, "RUR ERR\n");
    }
    return(1);
}