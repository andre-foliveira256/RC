#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void  client_bids(char* message, char* userid, char* pass, char *aid, int value){
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

    sprintf(message, "BID %s %s %s %i", userid, pass, aid, value);

}