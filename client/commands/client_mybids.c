#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void  myauctions(char* message, char *userid){
    //validar argumentos
    if (strlen(userid) != 6){
        printf("user not logged in\n");
    }

    snprintf(message, "LMB %s", userid);

}