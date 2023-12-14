#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void  showrecord(char* message, char *aid){
    //validar argumentos
    if (strlen(aid) != 3){
        printf("invalid auction id\n");
    }

    sprintf(message, "SRC %s\n", aid);

}