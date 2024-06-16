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
        if (rand() % 7 == 0) {
            addRequest();
        }

        // increment load balancer's time
        this->time++;
        std::cout << "Time: " << this->time << std::endl;

        // process requests on each server
        processRequest();

        // TODO: redo server allocation and deallocation

        // if any servers are empty, deallocate them
        for (int j = 0; j < serverCount; ++j) {
            if (webServers[j] && webServers[j]->isEmpty()) {
                webServers.erase(webServers.begin() + j);
                serverCount--;
                j--;
            }
        }

        // add new web server if necessary
        if (requestQueue.size() > (serverCount * 10) && this->serverCount < maxServers) {
            addWebServer();
        }
    }
}

void LoadBalancer::balanceLoad() {
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
            webServers[i]->processRequest();
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

void LoadBalancer::processRequest() {
    for (int i = 0; i < serverCount; i++) {
        if (webServers[i]) {
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
