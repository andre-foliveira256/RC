#include <iostream>
#include <string>
#include <vector>

using namespace std;
string AS_ip, AS_port;
char command;
int check = 1;


int main(int argc, char* argv[]) {
    AS_ip = string(argv[2]);
    AS_port = string(argv[4]);

    while(check){
        cin >> command;
        cout << command << endl;
        switch(command){
            case 'login':
                //TODO: login();
                break;

            case 'logout':
                //TODO: logout();
                break;

            case 'unregister':
                //TODO: unregister();
                break;
            
            case 'open':
                //TODO: open();
                break;
            
            case 'close':
                //TODO: close();
                break;

            case 'myauctions':  
            case 'ma':
                //TODO: myauctions();
                break;
            
            case 'list':
            case 'l':
                //TODO: list();
                break;

            case 'show_asset':
            case 'sa':
                //TODO: show_asset();
                break;

            case 'bid':
            case 'b':
                //TODO: bid();
                break;

            case 'show_record':
            case 'sr':
                //TODO: show_record();
                break;

            case 'exit':
                check = 0;
                break;
       }        
    }
    return 0;
}
