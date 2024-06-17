#include "LoadBalancer.h"
#include <iostream>
using std::endl, std::cerr, std::cout;

LoadBalancer::LoadBalancer(RequestQueue& requestQueue)
    : requestQueue(requestQueue), time(0), serverCount(0), maxServers(0) {
}

LoadBalancer::~LoadBalancer() {
}

void LoadBalancer::runBalancer(int time, int serverCount) {
    maxServers = serverCount;
    
    webServers.clear();
    webServers.reserve(serverCount);


    for (int i = 0; i < serverCount; ++i) {
        webServers.push_back(std::make_unique<WebServer>());
    }

    for (int i = 0; i < time; ++i) {
        balanceLoad();

        // add new request to the queue randomly
        if (rand() % 4 == 0) { // 25% chance of adding a request
            cout << "Adding a request randomly" << endl;
            addRequest();
        }

        // increment load balancer's time
        this->time++;
        std::cout << endl << "Time: " << this->time << std::endl;

        // process requests on each server
        processRequest();
    }
}

void LoadBalancer::balanceLoad() {

    // check if a server needs to be allocated or deallocated
    if (requestQueue.size() > (serverCount * 10) && serverCount < maxServers) {
        addWebServer();
    } else if (requestQueue.size() < (serverCount * 10) && serverCount > 1) {
        // get the requests from the last server
        std::queue<Request*> q = webServers[serverCount - 1]->getRequests();
        // redistribute requests from deallocated server across existing webservers
        while(!q.empty()) {
            for(int i = 0; i < serverCount - 1; i++) {
                if(q.empty()) {
                    break;
                } else {
                    webServers[i]->addRequest(q.front());
                    q.pop();
                }
            }
        }

        // deallocate the server
        removeWebServer();
    }

    // balance load - TODO: implement a better load balancing algorithm
    for (int i = 0; i < serverCount; i++) {
        if (webServers[i]) {
            if (!requestQueue.isEmpty()) {
                Request* nextRequest = requestQueue.getNext();
                if (nextRequest != nullptr) {
                    webServers[i]->addRequest(nextRequest);
                } else {
                    cerr << "Error: Attempted to get a null request from the queue." << endl;
                }
            }
        } else {
            cerr << "Error: webServers[" << i << "] is null." << endl;
        }
    }
}

void LoadBalancer::addRequest() {
    requestQueue.addRequest(new Request());
}

void LoadBalancer::addWebServer() {
    webServers.push_back(std::make_unique<WebServer>());
    serverCount++;
}

void LoadBalancer::removeWebServer() {
    if (serverCount > 1) {
        webServers.pop_back();
        serverCount--;
    }
}

void LoadBalancer::processRequest() {
    for (int i = 0; i < serverCount; i++) {
        if (webServers[i]) {
            cout << "Server " << i << " processing request for " << webServers[i]->getTime() << " clock cycles." << endl;
            webServers[i]->processRequest();
        } else {
            cerr << "Error: Attempted to process request on a null web server." << endl;
        }
    }
}

void LoadBalancer::print() {
    for (int i = 0; i < serverCount; i++) {
        if (webServers[i]) {
            cout << "WebServer " << i << " has " << webServers[i]->size() << " requests" << endl;
        } else {
            cerr << "Error: webServers[" << i << "] is null." << endl;
        }
    }
}

bool LoadBalancer::isEmpty() {
    return requestQueue.isEmpty();
}
