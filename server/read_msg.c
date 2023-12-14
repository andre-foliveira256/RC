#include <stdio.h>
#include <stdlib.h>

char userID[6];


void read_msg(char* message, int mode, char* ip, char* port){
    char* user;
    char* pass;
    char* type;
    
    char* code = strtok(message, " ");

    if (!strcmp(code, "LIN")){
        type = "login";
        user = strtok(NULL, " ");
        memcpy(userID, user, sizeof(userID));
        pass = strtok(NULL, "\n");
        login(user, pass, message);
    }
    if (!strcmp(code, "LOU")){
        char* type = "logout";
        char* user = strtok(NULL, " ");
        memcpy(userID, user, sizeof(userID));
        char* pass = strtok(NULL, "\n");
        logout(user, pass);
    }
    /*  
    if (!strcmp(code, "UNR")){
        char* type = "unregister";
        char* user = strtok(NULL, " ");
        char* pass = strtok(NULL, "\n");
        unregister(user, pass);
    } 
    if (!strcmp(code, "LMA")){
        char* type = "myauctions";
        char* user = strtok(NULL, " ");
    }
    if (!strcmp(code, "LMB")){
        char* type = "mybids";
        char* user = strtok(NULL, " ");
    }
    if (!strcmp(code, "LIS")){
        char* type = "list";
    }
    if (!strcmp(code, "SRC")){
        char* type = "show_record";
    }
    if (!strcmp(code, "SRA")){
        char* type = "show_auction";
    }
    if(!strcmp(code, "OPA")){
        char* type = "open";
        char* user = strtok(NULL, " ");
    }
    if(!strcmp(code, "CLS")){
        char* type = "close";
        char* user = strtok(NULL, " ");
    } */


    if(mode) printf("New request:\nUser: %s\nType: %s\nIPaddress: %s\nPort: %s\n", userID, type, ip, port);
}