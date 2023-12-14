#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define UDP 1
#define TCP 0
#define EXIT -1


char* userid, *pass;

int read_input(char* buffer, char* input, char* userID, char* password){
    char* command = strtok(input, " ");

    if (!strcmp(command, "login")) {
        userid = strtok(NULL, " ");
        pass = strtok(NULL, " ");
        client_login(buffer, userid, pass);
        memcpy(userID, userid, sizeof(userID));
        memcpy(password, pass, sizeof(password));
        return UDP;
    } 
    
    else if (!strcmp(command, "logout\n")){
        client_logout(buffer, userID, password);
        return UDP;  
    }

    else if (!strcmp(command, "unregister\n")){
        client_unregister(buffer, userID, password);
        return UDP;
    }

    else if (!strcmp(command, "open")){
        userid = strtok(NULL, " ");
        pass = strtok(NULL, " ");
        char* name = strtok(NULL, " ");
        int   start_value = atoi(strtok(NULL, " "));
        int   timeactive = atoi(strtok(NULL, " "));
        char* fname = strtok(NULL, " ");
        int fsize = atoi(strtok(NULL, " "));
        char* fdata = strtok(NULL, "\n");
        client_open(buffer, userid, pass, name, start_value, timeactive, fname, fsize, fdata);
        return TCP;
    }
    else if(!strcmp(command, "close")){
        userid = strtok(NULL, " ");
        pass = strtok(NULL, " ");
        char* aid = strtok(NULL, " ");
        client_close(buffer, userid, pass, aid);
        return TCP;
    }
    else if (!strcmp(command, "myauctions\n") || !strcmp(command, "ma\n")) {
        myauctions(buffer, userID);
        return UDP;

    }

    else if(!strcmp(command, "mybids\n") || !strcmp(command, "mb\n")){
        mybids(buffer, userID);
        return UDP;
    }

    else if(!strcmp(command, "list\n") || !strcmp(command, "l\n")){
        list(buffer);
        return UDP;
    }

    else if(!strcmp(command, "show_asset") || !strcmp(command, "sa")){
        char* aid = strtok(NULL, " ");
        client_showasset(buffer, aid);
    }

    else if(!strcmp(command, "bid") || !strcmp(command, "b")){
        userid = strtok(NULL, " ");
        pass = strtok(NULL, " ");
        char* aid = strtok(NULL, " "); 
        int value = atoi(strtok(NULL, " ")); 
        client_bids(buffer, userid, pass, aid, value);        
    }

    else if(!strcmp(command, "show_record") || !strcmp(command, "sr")){
        char * aid = strtok(NULL, " ");
        showrecord(buffer, aid);
        return UDP;
    }

    else if (!strcmp(command, "exit\n")) {
        return EXIT;
    }
}