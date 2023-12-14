#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void client_close(char* message, char *userid, char *pass, char* aid){
    //validar argumentos
    if (strlen(userid) != 6){
        printf("User not logged in\n");
    }

    if (strlen(pass) != 8){
        printf("Invalid password\n");  
    }

    if (strlen(aid) != 3){
        printf("Invalid aution id\n");
    }

    sprintf(message, "CLS %s %s %s\n", userid, pass, aid);
}