#include <iostream>
using std::cout, std::endl, std::cin, std::string;
#include "RequestQueue.h"

int main() {
    int serverCount = -1, balancerTime = -1; 
    string serverInput, balancerInput;
    
    cout << "Howdy! Welcome to Kaitlyn Griffin's Load Balancer Program for CSCE 412 Project 3" << endl;
    cout << "Enter the number of servers you wish to use as a whole number: ";
    cin >> serverInput;
    cout << endl << "Enter the amount of clock cycles you wish to run the load balancer for as a whole number: ";
    cin >> balancerInput;

    // input validation, ensuring both inputs are integers
    try {
        serverCount = std::stoi(serverInput);
    } catch (std::invalid_argument) {
        cout << "Please enter a whole number for the number of servers!" << endl;
        return 1;
    }
    try {
        balancerTime = std::stoi(balancerInput);
    } catch (std::invalid_argument) {
        cout << "Please enter a whole number for the amount of clock cycles!" << endl;
        return 1;
    }

    // input validation, ensuring both inputs are positive
    if (serverCount <= 0 || balancerTime <= 0) {
        cout << "Please enter positive numbers for both inputs!" << endl;
        return 1;
    }

    // input validation was successful
    cout << "The load balancer is running with " << serverCount << " servers with each load balancer running for " << balancerTime << " clock cycles." << endl;

    RequestQueue queue = RequestQueue(); 
    // generate a full queue (servers * 100) 
    for(int i = 0; i < serverCount * 100; i++){
        // generate a request and push it to the queue
        queue.addRequest(new Request());
    }
}