#include "Request.h"
using std::to_string;

Request::Request(){
    // generate random IP addresses, ranging from 0 to 255
    for(int i = 0; i < 4; i++){
        IPin += to_string(rand() % 256);
        IPout += to_string(rand() % 256);
        if(i < 3){
            IPin += ".";
            IPout += ".";
        }
    }
    time = rand() % 10;
};

void Request::print() {
    cout << "IP in: " << IPin << endl;
    cout << "IP out: " << IPout << endl;
    cout << "Time: " << time << endl;
};
