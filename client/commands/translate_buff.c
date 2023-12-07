#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void translate_buff(char* message){    
    char* code = strtok(message, " ");
    char* status = strtok(NULL, "\n");

    //login
    if (!strcmp(code, "RLI")){
        if (!strcmp(status, "OK"))  printf("successful login\n");
        if (!strcmp(status, "NOK")) printf("incorrect login attempt\n");
        if (!strcmp(status, "REG")) printf("new user registered\n");
    }
    //logout
    if (!strcmp(code, "RLO")){
        if (!strcmp(status, "OK"))  printf("successful logout\n");
        if (!strcmp(status, "NOK")) printf("user not logged in\n");
        if (!strcmp(status, "UNR")) printf("unkown user\n");
    }
    //unregister
    if (!strcmp(code, "RUR")){
        if (!strcmp(status, "OK"))  printf("successful unregister\n");
        if (!strcmp(status, "NOK")) printf("incorrect unregister attempt\n");
        if (!strcmp(status, "UNR")) printf("unkown user\n");

    }
    //TODO case switch para tratar as mensagens e mandar mensagem certa

    code = NULL;
    status = NULL;
}



