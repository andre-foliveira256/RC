#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>

void client_open(char* message, char *userid, char *pass, char *name,char *asset_fname, int start_value, int timeactive){

    if (strlen(asset_fname) > 24){
        printf("File name exceeded the characters limit\n");
    }
    char* fname = asset_fname;

    struct stat filestat;
    int ret_stat;

    ret_stat = stat(fname , &filestat);
    int fsize = filestat.st_size; 

    FILE *file = fopen(fname, "rb");

   


    fclose(file);


    sprintf(message, "OPA %s %s %s %i %i %s %i \n", userid, pass, name, start_value, timeactive, fname, fsize);
}