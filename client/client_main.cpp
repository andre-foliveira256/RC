#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string>
#include <iostream>
#include <sstream>
#include "client_login.cpp"



using namespace std;




int main(int argc, char* argv[]) {
    char *AS_ip, *AS_port;
    int check = 1;
    string command, keywords[5];
    AS_ip = argv[2];
    AS_port =argv[4];

    while(check){
        cin >> command;
        getline(cin, keywords[0]);
        istringstream iss(keywords[0]);
        int i = 0;
        while (iss >> keywords[i+1] && i < 5) {
            i++;
        }

        if (command == "login"){
            string userID = keywords[1], password = keywords[2];
            client_login(userID, password, AS_ip, AS_port);
            //TODO: verificar se funciona a 100%;
        }
        else if (command == "logout"){
            //TODO: logout();
        }
        

        else if (command == "unregister"){
            //TODO: unregister();
        }
        
        else if (command == "open"){
            //TODO: open();
        }
            
        
        else if (command == "close"){
            //TODO: close();
        }
            

        else if (command == "myauctions"|| command == "ma"){
            //TODO: myauctions();
        }
            
        
        else if (command == "list" || command == "l"){
            //TODO: list();
        }
            

        else if (command == "show_asset"|| command == "sa"){
            //TODO: show_asset();
        }
            

        else if (command == "bid"|| command == "b"){
            //TODO: bid();
        }
            

        else if (command == "show_record" ||command == "sr"){
            //TODO: show_record();
        }
            

        else if (command == "exit"){
            check = 0;
        }
            
    }        
    return 0;
}

