#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void  client_showasset(char* message, char *aid){
    //validar argumentos
    if (strlen(aid) != 3){
        printf("invalid auction id\n");
    }

    sprintf(message, "SAS %s\n", aid);

}