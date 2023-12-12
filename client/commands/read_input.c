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
        char* name = strtok(NULL, " ");
        char* asset_fname = strtok(NULL, " ");
        int   start_value = atoi(strtok(NULL, " "));
        int   timeactive = atoi(strtok(NULL, " "));
        open_a(buffer, userID, password, name, asset_fname, start_value, timeactive);
        return TCP;
    }
    else if(!strcmp(command, "close")){

        return TCP;
    }
    else if (!strcmp(command, "myauctions") || !strcmp(command, "ma")) {
        myauctions(buffer, userID);
        return UDP;

    }

    else if(!strcmp(command, "mybids") || !strcmp(command, "mb")){
        mybids(buffer, userID);
        return UDP;
    }

    else if(!strcmp(command, "list") || !strcmp(command, "l")){
        list(buffer);
        return UDP;
    }

    else if(!strcmp(command, "show_asset") || !strcmp(command, "sa")){

    }

    else if(!strcmp(command, "show_record") || !strcmp(command, "sr")){
        showrecord(buffer, userID);
        return UDP;
    }

    else if (!strcmp(command, "exit\n")) {
        return EXIT;
    }
}