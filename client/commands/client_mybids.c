#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void  mybids(char* message, char *userid){
    //validar argumentos
    if (strlen(userid) != 6){
        printf("user not logged in\n");
    }

    sprintf(message, "LMB %s\n", userid);

}