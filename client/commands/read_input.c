#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define UDP 1
#define TCP 0
#define EXIT -1
#define NONE 2


int read_input(char* buffer, char* input, char* userID, char* password,char* tcp_check, char* fpath){
    char* userid, *pass;
    char* command = strtok(input, " ");

    if (!strcmp(command, "login")) {
        userid = strtok(NULL, " ");
        pass = strtok(NULL, "\n");
        if(!client_login(buffer, userid, pass)){
            memcpy(userID, userid, sizeof(userID));
            memcpy(password, pass, sizeof(password));
            return UDP;
        }
        else return NONE;
    } 
    
    else if (!strcmp(command, "logout\n")){
        client_logout(buffer, userID, password);
        memcpy(userID, "", sizeof(userID));
        memcpy(password, "", sizeof(password));
        return UDP;  
    }

    else if (!strcmp(command, "unregister\n")){
        client_unregister(buffer, userID, password);
        return UDP;
    }

    else if (!strcmp(command, "open")){
        char* name = strtok(NULL, " ");
        char* asset_fname = strtok(NULL, " ");
        char* start_value = strtok(NULL, " ");
        char* timeactive = strtok(NULL, "\n");
        client_open(buffer, userID, password, name, asset_fname, start_value, timeactive, fpath);
        memcpy(tcp_check, "1", sizeof(tcp_check));
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
        char* aid = strtok(NULL, "\n");
        client_showasset(buffer, aid);
        memcpy(tcp_check, "2", sizeof(tcp_check));
        return TCP;
    }

    else if(!strcmp(command, "bid") || !strcmp(command, "b")){
        char* aid = strtok(NULL, " "); 
        int value = atoi(strtok(NULL, " ")); 
        client_bids(buffer, userID, password, aid, value);
        return TCP;      
    }

    else if(!strcmp(command, "show_record") || !strcmp(command, "sr")){
        char * aid = strtok(NULL, "\n");
        showrecord(buffer, aid);
        return UDP;
    }

    else if (!strcmp(command, "exit\n")) {
        if (strlen(userID) != 0) printf("You must logout before exiting\n");
        else return EXIT;
    }
}