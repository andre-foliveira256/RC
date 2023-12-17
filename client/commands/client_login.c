#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int client_login(char* message, char *userid, char *pass){
    //validar argumentos
     if (strlen(userid) != 6){
        printf("Invalid userid\n");
        return -1;
    }
    if (strlen(pass) != 8 ){
        printf("Invalid password: wrong length\n");
        return -1;
    }
    for (int i = 0; i < 8; i++){
        if (!isalnum(pass[i])){
            printf("Invalid password: only alphanumeric characters allowed\n");
            return -1;
        }
    }
    sprintf(message, "LIN %s %s\n", userid, pass);
    return 0;
}



