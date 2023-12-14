#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>

int check_login(char* userID, char* login_f){
    struct stat st;



}




int logout(char* userID, char* password){
    
    struct stat st;
    char* path;
    char pass_f[35];
    char login_f[35];

    if (strlen(userID) !=6) return(0);

    path = (char*)malloc(strlen("/USERS/") + strlen(userID) + 1);
    strcpy(path, "/../USERS/");
        sprintf(login_f, "%s/%s_login.txt", path, userID);



    return(1);
}