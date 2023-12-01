#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void client_login(char* message, char *userID, char *password){

    //validar argumentos
    if (strlen(userID) != 6){
        printf("Invalid userID\n");
        exit(-1);
    }
    if (strlen(password) != 8){
        printf("Invalid password\n");
        exit(-1);   
    }

    sprintf(message, "LIN %s %s\n", userID, password);
}



