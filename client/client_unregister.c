#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void client_unregister(char* message, char *userID, char *password){

    //validar argumentos
    if (strlen(userID) != 6){
        printf("user not logged in\n");
    }
    if (strlen(password) != 8){
        printf("Invalid password\n");  
    }

    sprintf(message, "UNR %s %s\n", userID, password);
}



