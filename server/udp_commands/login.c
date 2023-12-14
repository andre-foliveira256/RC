#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>

int create_file(char* name, int mode, char* password){
    FILE *fp;
    fp = fopen(name, "w");
    if (fp == NULL) return(0);
    if (mode == 0){
        fprintf(fp, "%s", password);
    }
    fclose(fp);
    return(1);
}

int check_user(char* password, char* pass_f, char* login_f){
    struct stat st;

    //If user is not registered
    if (stat(pass_f, &st) != 0) return(2);
    //If user is registered
    else{
        //Compare password
        FILE *fp;
        char pass[35];
        fp = fopen(pass_f, "r");
        if (fp == NULL) return(0);
        fscanf(fp, "%s", pass);
        fclose(fp);
        if (strcmp(pass, password) != 0) return(0);

        //Check if user is logged in
        if (stat(login_f, &st) != 0){
            return(1);
        }
    }
    return(-1);
}




int login(char* userID, char* password,char* message){
    
    struct stat st;
    char* path;
    char pass_f[35];
    char login_f[35];

    if (strlen(userID) !=6) return(0);

    path = (char*)malloc(strlen("USERS/") + strlen(userID) + 1);
    
    //file name creation
    sprintf(path, "USERS/%s", userID);
    sprintf(pass_f, "%s/%s_pass.txt", path, userID);
    sprintf(login_f, "%s/%s_login.txt", path, userID);

    


    //If user doesnt exist
    if (stat(path, &st) != 0) {
        if(mkdir(path, 0700)) return(0);
        create_file(pass_f, 0, password);
        create_file(login_f, 1, NULL);
        sprintf(message, "RLI REG\n");
    }
    //If user exists
    else{
        int c = check_user(password, pass_f, login_f);
        if(c == 1){
            create_file(login_f, 1, NULL);
            sprintf(message, "RLI OK\n");
        }
        else if(c == 2){
            create_file(pass_f, 0, password);
            create_file(login_f, 1, NULL);
            sprintf(message, "RLI REG\n");
        }
        else if(c == 0){
            sprintf(message, "RLI NOK\n");
        }
        else if(c == -1){
            sprintf(message, "ERR\n");
        }
    }
    free(path);
    return(1);
}
