#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void  client_bids(char* message, char* userid, char* pass, char *aid, int value){
    if (strlen(userid) != 6){
        printf("Invalid userid\n");
        userid = NULL;
        pass = NULL;
        exit(1);
    }
    if (strlen(pass) != 8){
        printf("Invalid pass\n");
        userid = NULL;
        pass = NULL;
        exit(1);
    }
    sprintf(message, "BID %s %s %s %i\n", userid, pass, aid, value);
}