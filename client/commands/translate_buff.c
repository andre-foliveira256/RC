#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void translate_buff(char* message){    
    char* code = strtok(message, " ");

    //login
    if (!strcmp(code, "RLI")){
        char* status = strtok(NULL, "\n");
        if (!strcmp(status, "OK"))  printf("successful login\n");
        if (!strcmp(status, "NOK")) printf("incorrect login attempt\n");
        if (!strcmp(status, "REG")) printf("new user registered\n");
        status = NULL;
    }
    //logout
    if (!strcmp(code, "RLO")){
        char* status = strtok(NULL, "\n");
        if (!strcmp(status, "OK"))  printf("successful logout\n");
        if (!strcmp(status, "NOK")) printf("user not logged in\n");
        if (!strcmp(status, "UNR")) printf("unkown user\n");
        status = NULL;
    }
    //unregister
    if (!strcmp(code, "RUR")){
        char* status = strtok(NULL, "\n");
        if (!strcmp(status, "OK"))  printf("successful unregister\n");
        if (!strcmp(status, "NOK")) printf("incorrect unregister attempt\n");
        if (!strcmp(status, "UNR")) printf("unkown user\n");
        status = NULL;

    }
    // myauctions
    if (!strcmp(code, "RMA")){
        char* status = strtok(NULL, " ");
        char* ma_list = strtok(NULL, "\n");

        if (!strcmp(status, "OK"))  printf("%s\n", ma_list);
        if (!strcmp(status, "NLG"))  printf("user is not logged in\n");
        if (!strcmp(status, "NOK")) printf("user has no ongoing bids\n");

        status = NULL;
        ma_list = NULL;

    }
    // mybids
    if (!strcmp(code, "RMB")){
        char* status = strtok(NULL, " ");
        char* mb_list = strtok(NULL, "\n");

        if (!strcmp(status, "OK"))  printf("%s\n", mb_list);
        if (!strcmp(status, "NLG"))  printf("user is not logged in\n");
        if (!strcmp(status, "NOK")) printf("user has no ongoing auctions\n");

        status = NULL;
        mb_list = NULL;
    }
    // list
    if (!strcmp(code, "RLS")){
        char* status = strtok(NULL, " ");
        char* state = strtok(NULL, "\n");

        if (!strcmp(status, "OK"))  printf("\n");
        if (!strcmp(status, "NOK")) printf("no auctions was yet started\n");

        status = NULL;
        state = NULL;
    }
    // showrecord
    if (!strcmp(code, "RRC")){
        char* status = strtok(NULL, " ");
        char* state = strtok(NULL, "\n");

        if (!strcmp(status, "OK"))  printf("\n");
        status = NULL;
    }

    //TODO case switch para tratar as mensagens e mandar mensagem certa

    code = NULL;
    
}



