#include "Request.h"

// generates random IP addresses, both in and out
// random times for each request to be processed

Request::Request(){
    // initialize random IP addresses
    IPin = "";
    IPout = "";
    // generate random IP addresses, ranging from 0 to 255
    for(int i = 0; i < 4; i++){
        IPin += rand() % 256;
        IPout += rand() % 256;
        if(i < 3){
            IPin += ".";
            IPout += ".";
        }
    }
    time = rand() % 100;
};

void Request::print() {
    cout << "IP in: " << IPin << endl;
    cout << "IP out: " << IPout << endl;
    cout << "Time: " << time << endl;
};
