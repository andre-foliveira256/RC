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
        login_udp(user, pass, message);
    }
    if (!strcmp(code, "LOU")){
        char* type = "logout";
        char* user = strtok(NULL, " ");
        memcpy(userID, user, sizeof(userID));
        char* pass = strtok(NULL, "\n");
        logout_udp(user, pass, message);
    }
    if (!strcmp(code, "UNR")){
        char* type = "unregister";
        char* user = strtok(NULL, " ");
        char* pass = strtok(NULL, "\n");
        unregister_udp(user, pass, message);
    } 
 
    if (!strcmp(code, "LMA")){
        char* type = "myauctions";
        char* user = strtok(NULL, "\n");
        myauctions_udp(user, message);
    }
    if (!strcmp(code, "LMB")){
        char* type = "mybids";
        char* user = strtok(NULL, " ");
        mybids_upd(user, message);
    }
    if (!strcmp(code, "LIS")){
        char* type = "list";
        list_udp(message);
    }
    if (!strcmp(code, "SRC")){
        char* type = "show_record";
        char* aid = strtok(NULL, " ");
        showrecord_udp(aid, message);
    }
    if(!strcmp(code, "OPA")){
        char* type = "open";
        char* user = strtok(NULL, " ");
        char* password = strtok(NULL, " ");
        char* name = strtok(NULL, " ");
        char* start_value = strtok(NULL, " ");
        char* timeactive = strtok(NULL, " ");
        char* asset_fname = strtok(NULL, " ");
        char* fsize = strtok(NULL, "\n");
        open_tcp(user, password, name, start_value, timeactive, asset_fname, fsize, message);
    }
    if(!strcmp(code, "CLS")){
        char* type = "close";
        char* user = strtok(NULL, " ");
        char* password = strtok(NULL, " ");
        char* aid = strtok(NULL, "\n");
        close_tcp(user, password, aid, message);
    } 
    if(!strcmp(code, "BID")){
        char* type = "bid";
        char* user = strtok(NULL, " ");
        char* password = strtok(NULL, " ");
        char* aid = strtok(NULL, " ");
        char* value = strtok(NULL, "\n");
        bids_tcp(user, password, aid, value, message);
    }
    if (!strcmp(code, "SAS")){
        char* type = "show_asset";
        char* aid = strtok(NULL, " ");
        showasset_tcp(aid , message);
    }


    if(mode) printf("New request:\nUser: %s\nType: %s\nIPaddress: %s\nPort: %s\n", userID, type, ip, port);
}