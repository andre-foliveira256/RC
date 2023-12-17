#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>

int check_login(char* userID, char* path, char* pass_f, char* login_f){
    struct stat st;

    //If user is not registered
    if (stat(path, &st) != 0 || stat(pass_f, &st) != 0){
        return(0);
    }
    //If user is registered
    else{
        //If user is logged in
        if (stat(login_f, &st) == 0){
            return(1);
        }
        //If user is not logged in
        else{
            return(2);
        }
    }
    return(-1);
}




int logout_udp(char* userID, char* password, char *message){
    
    struct stat st;
    char* path;
    char pass_f[35];
    char login_f[35];

    if (strlen(userID) !=6) return(0);

    path = (char*)malloc(strlen("USERS/") + strlen(userID) + 1);
    sprintf(path, "USERS/%s", userID);
    sprintf(pass_f, "%s/%s_pass.txt", path, userID);
    sprintf(login_f, "%s/%s_login.txt", path, userID);

    int c = check_login(userID, path, pass_f, login_f);
    if (c == 0){
        sprintf(message, "RLO UNR\n");
    }
    else if (c == 1){
        sprintf(message, "RLO OK\n");
        unlink(login_f);
    }
    else if (c == 2){
        sprintf(message, "RLO NOK\n");
    }
    else{
        sprintf(message, "RLO ERR\n");
    }


    return(1);
}