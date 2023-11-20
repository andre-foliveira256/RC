#include "sockets.h"
#include "client_login.cpp"
#include <typeinfo>
//#include "client_logout.cpp"
#define AS_ip "tejo.tecnico.ulisboa.pt"
#define AS_port "580011"


using namespace std;


int main(int argc, char* argv[]) {
    int check = 1;
    string command, keywords[5], userID, password;


    while(check){
        cin >> command;
        getline(cin, keywords[0]);
        istringstream iss(keywords[0]);
        int i = 0;
        while (iss >> keywords[i+1] && i < 5) {
            i++;
        }  

        if (command == "login"){
            userID = keywords[1];
            password = keywords[2];
            client_login(userID, password, AS_ip, AS_port);
            //TODO: verificar se funciona a 100%;
        }
        else if (command == "logout"){
            userID = keywords[1];
            password = keywords[2];
            //client_logout(userID, password, AS_ip, AS_port);
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

