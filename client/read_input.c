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


    }
    else if(!strcmp(command, "close")){

    }
    else if (!strcmp(command, "myauctions") || !strcmp(command, "ma")) {
        /* myauctions(userID, AS_ip, AS_port);
            *///TODO ver se está a funcionar bem
    }

    else if(!strcmp(command, "mybids") || !strcmp(command, "mb")){

    }

    else if(!strcmp(command, "list") || !strcmp(command, "l")){

    }

    else if(!strcmp(command, "show_asset") || !strcmp(command, "sa")){

    }

    else if(!strcmp(command, "show_record") || !strcmp(command, "sr")){

    }

    else if (!strcmp(command, "exit\n")) {
        return EXIT;
    }
}



