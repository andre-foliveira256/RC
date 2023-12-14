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
        if (!strcmp(status, "NLG\n"))  printf("user is not logged in\n");
        if (!strcmp(status, "NOK\n")) printf("user has no ongoing bids\n");

        status = NULL;
        ma_list = NULL;

    }
    // mybids
    if (!strcmp(code, "RMB")){
        char* status = strtok(NULL, " ");
        char* mb_list = strtok(NULL, "\n");

        if (!strcmp(status, "OK"))  printf("%s\n", mb_list);
        if (!strcmp(status, "NLG\n"))  printf("user is not logged in\n");
        if (!strcmp(status, "NOK\n")) printf("user has no ongoing auctions\n");

        status = NULL;
        mb_list = NULL;
    }
    // list
    if (!strcmp(code, "RLS")){
        char* status = strtok(NULL, " ");
        char* list = strtok(NULL, "\n");

        if (!strcmp(status, "OK"))  printf("%s\n", list);
        if (!strcmp(status, "NOK\n")) printf("no auctions was yet started\n");

        status = NULL;
        list = NULL;
    }
    // showrecord
    if (!strcmp(code, "RRC")){
        char* status = strtok(NULL, " ");
        char* info = strtok(NULL, "\n");

        if (!strcmp(status, "NOK\n")) printf("auction does not exist\n"); 
        if (!strcmp(status, "OK")){
            while (info != NULL){
                printf ("%s\n", info);
                info = strtok (NULL, "\n");
            }
        };
        //TODO:não sei se este if está a funcionar

        status = NULL;
        info = NULL;
    }

    //open
    if (!strcmp(code, "ROA")){
        char* status = strtok(NULL, " ");
        char* aid = strtok(NULL, "\n");

        if (!strcmp(status, "NOK\n")) printf("auction could not be strated\n"); 
        if (!strcmp(status, "OK")) printf("The auction id is: %s\n", aid); 
        //TODO: acabar a conecção com o TCP

        status = NULL;
        aid = NULL;
    }

    //close
    if (!strcmp(code, "RCL")){
        char* status = strtok(NULL, " ");

        if (!strcmp(status, "OK")) printf("auction closed successfully\n"); 
        if (!strcmp(status, "NGL\n")) printf("user is not logged in\n"); 
        if (!strcmp(status, "EAU\n")) printf("auction does not exist\n"); 
        if (!strcmp(status, "EOW\n")) printf("auction not owned by this user\n"); 
        if (!strcmp(status, "END\n")) printf("auction aalready finished\n"); 


        status = NULL;
    }

    //show_assets
    if (!strcmp(code, "RSA")){
        char* status = strtok(NULL, " ");
        char* fname = strtok(NULL, " "); //TODO: ver se tenho que separar isto
        int fsize = atoi(strtok(NULL, " "));
        char* fdata = strtok(NULL, "\n");

        if (!strcmp(status, "OK")) printf("asset for sale: %s\n", fdata); 
        if (!strcmp(status, "NOK\n")) printf("there was an error\n"); 

        status = NULL;
        fname = NULL;
        fsize = 0;
        fdata = NULL;
    }

    //bid
    if (!strcmp(code, "RBD")){
        char* status = strtok(NULL, " "); 

        if (!strcmp(status, "NOK\n")) printf("auction is not active\n");
        if (!strcmp(status, "NLG\n")) printf("user is not logged in\n"); 
        if (!strcmp(status, "ACC\n")) printf("bid was accepted\n");
        if (!strcmp(status, "REF\n")) printf("bid was not acceptes because a larger bid has already been placed\n");
        if (!strcmp(status, "ILG\n")) printf("user can not make a bid in a auction hosted by himself\n");

        status = NULL;
    } 

    //ERR
    if (!strcmp(code, "ERR\n")){
        printf("There was an erro!\n");
    }

    code = NULL;
    
}





