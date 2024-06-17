/***
 * @file main.cpp
 * @author Kaitlyn Griffin
 * @date 2024-06-16
 * 
 * @brief Main function for the load balancer program.
 */

#include <iostream>
using std::cout, std::endl, std::cin, std::string;
#include "RequestQueue.h"
#include "LoadBalancer.h"

/**
 * @brief Main function for the load balancer program.
 * 
 * @return int 0 if successful, 1 if error.
 */
int main() {
    int serverCount = -1, balancerTime = -1; 
    string serverInput, balancerInput;
    
    cout << "Howdy! Welcome to Kaitlyn Griffin's Load Balancer Program for CSCE 412 Project 3" << endl;
    cout << "Enter the number of servers you wish to use as a whole number: ";
    cin >> serverInput;
    cout << "Enter the amount of clock cycles you wish to run the load balancer for as a whole number: ";
    cin >> balancerInput;

    //!< input validation, ensure both inputs are integers.
    try {
        serverCount = std::stoi(serverInput);
    } catch (const std::invalid_argument& e) {
        cout << "Please enter a whole number for the maximum number of servers!" << endl;
        return 1;
    }
    try {
        balancerTime = std::stoi(balancerInput);
    } catch (const std::invalid_argument& e) {
        cout << "Please enter a whole number for the amount of clock cycles!" << endl;
        return 1;
    }

    //!< input validation, ensure both inputs are positive.
    if (serverCount <= 0 || balancerTime <= 0) {
        cout << "Please enter positive numbers for both inputs!" << endl;
        return 1;
    }

    //!< inputs are good.
    cout << "The load balancer is running with a maximum of " << serverCount 
        << " servers with the load balancer running for " << balancerTime << " clock cycles." << endl;

    RequestQueue queue; 
    //!< generate full queue (servers * 100). 
    for (int i = 0; i < serverCount * 100; i++) {
        queue.addRequest(new Request());
    }

    //!< record starting queue size.
    int startingQueueSize = queue.size();

    //!< create load balancer.
    LoadBalancer* balancer = new LoadBalancer(queue);

    //!< call load balancer with queue and time.
    balancer->runBalancer(balancerTime, serverCount);

    //!< record ending queue size.
    int endingQueueSize = queue.size();

    cout << endl << "The load balancer started with " << startingQueueSize << " requests and ended with " << endingQueueSize << " requests." << endl << endl;

    delete balancer;

    return 0;
}
