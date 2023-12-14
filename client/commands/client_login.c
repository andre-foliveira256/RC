#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void client_login(char* message, char *userid, char *pass){
    //validar argumentos
    if (strlen(userid) != 6){
        printf("Invalid userid\n");
        userid = NULL;
        pass = NULL;
    }
    if (strlen(pass) != 9){
        printf("Invalid pass\n");
        userid = NULL;
        pass = NULL;
    }

    sprintf(message, "LIN %s %s\n", userid, pass);
}



