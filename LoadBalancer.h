
#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include "RequestQueue.h"
#include "WebServer.h"

class LoadBalancer {
private:
    RequestQueue requestQueue = RequestQueue();
    std::vector<WebServer*> webServers = std::vector<WebServer*>();
    int time = 0;
    int serverCount = 0;
    void balanceLoad();

public:
    LoadBalancer();
    LoadBalancer(RequestQueue& requestQueue);
    ~LoadBalancer();
    void runBalancer(int time, int serverCount);
    
    void addRequest();
    void addWebServer();
    void processRequest();
    void print();
    bool isEmpty();

};

#endif
