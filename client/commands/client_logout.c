#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void client_logout(char* message, char *userID, char *password){
    sprintf(message, "LOU %s %s\n", userID, password);
}



