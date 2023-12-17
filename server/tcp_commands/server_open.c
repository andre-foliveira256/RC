#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>


int generat_aID() {
    
    char *filename = "aID_status.txt";
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        file = fopen(filename, "w"); 
        if (file != NULL) {
            fprintf(file, "%d", 1); 
            fclose(file);
            return 1;
        } else {
            return -1; 
    } 
    }
    else {
        int aid;
        fscanf(file, "%d", &aid);

        if (aid == 999) {
            fclose(file);
            return 0;
        } else {
            aid++;
            fseek(file, 0, SEEK_SET);
            fprintf(file, "%d", aid);
            fclose(file); 
            return aid;
        }
    }

    return -1;
}

int register_auction(char *userID, char *name, char *start_value, char *timeactive, char *asset_fname, char *fsize, int aid){
    char *path;
    char status[] = "1";
    char name_f[50];
    char timeactive_f[50];
    char asset_fname_f[50];
    char fsize_f[50];
    char status_f[50];
    char aid_f[50];

    path = (char*)malloc(strlen("USERS/") + strlen(userID) + 1);
    sprintf(path, "USERS/%s/%03d_name.txt", userID, aid);
    sprintf(name_f, "%s/%03d_name.txt", path, aid);
    create_file(name_f, 0, name);
    //sprintf(timeactive_f, "%s/%03d_timeactive.txt", path, aid);
    //create_file(timeactive_f, 0, timeactive);
    //sprintf(asset_fname_f, "%s/%03d_asset_fname.txt", path, aid);
    //create_file(asset_fname_f, 0, asset_fname);
    //sprintf(fsize_f, "%s/%03d_fsize.txt", path, aid);
    //create_file(fsize_f, 0, fsize);
    //sprintf(status_f, "%s/%03d_status.txt", path, aid);
    //create_file(status_f, 0, status);
    //sprintf(path, "AUCTIONS/%03d", aid);
    //create_file(aid_f, 1, NULL); 

    free(path);

}



int open_tcp(char *userID, char *password, char *name, char *start_value, char *timeactive, char *asset_fname, char *fsize, char *message) {
    int aid;
    char *path;
    char name_f[50];
    char pass_f[50];
    char login_f[50];
    


    if (strlen(userID) !=6) return(0);

    path = (char*)malloc(strlen("USERS/") + strlen(userID) + 1);
    sprintf(path, "USERS/%s", userID);
    sprintf(pass_f, "%s/%s_pass.txt", path, userID);
    sprintf(login_f, "%s/%s_login.txt", path, userID);


    int c = check_login(userID, path, pass_f, login_f);

    if (c == 1) {
        aid = 1;
        sprintf(message, "RLO NOK\n");

        if (aid == 0) {
            sprintf(message, "RLO NOK\n");
        } 
        else {
            sprintf(path, "USERS/%s/%03d_name.txt", userID, aid);
            sprintf(name_f, "%s/%03d_name.txt", path, aid);
            create_file(name_f, 0, name);
            sprintf(message, "RLO OK %03d\n", aid);
        }
    } 
    else  {
        sprintf(message, "RLO NLG\n");
    }

    free(path);
    return 0;
}