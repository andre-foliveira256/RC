#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void client_open(char* message, char *userid, char *pass, char *name, int start_value, int timeactive,char *fname, int fsize, char *fdata){
    //validar argumentos
    if (strlen(userid) != 6){
        printf("User not logged in\n");
    }

    if (strlen(pass) != 8){
        printf("Invalid password\n");  
    }

    if (strlen(fname) > 24){
        printf("File name exceeded the characters limit\n");
    }

    if (fsize > 8){
        printf("File size exceeded the limit\n");
    }

    sprintf(message, "OPA %s %s %s %i %i %s %i %s", userid, pass, name, timeactive, fname, fsize, fdata);
}