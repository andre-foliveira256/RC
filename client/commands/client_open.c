#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>

void client_open(char* message, char *userid, char *pass, char *name,char *asset_fname, int start_value, int timeactive,char* path){

    if (strlen(asset_fname) > 24){
        printf("File name exceeded the characters limit\n");
    }
    struct stat filestat;
    int ret_stat;

    path = (char*) malloc(sizeof("ASSETS/") + sizeof(asset_fname)+1);
    sprintf(path, "ASSETS/%s", asset_fname);

    ret_stat = stat(path , &filestat);
    int fsize = filestat.st_size;
    
    sprintf(message, "OPA %s %s %s %i %i %s %i", userid, pass, name, start_value, timeactive, asset_fname, fsize);
}