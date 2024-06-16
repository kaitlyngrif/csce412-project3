
#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include "RequestQueue.h"
#include "WebServer.h"

class LoadBalancer {
    // variables here
private:
    RequestQueue requestQueue;
    std::vector<WebServer*> webServers;
    int time;
    int serverCount;

    // functions here
public:
    LoadBalancer();
    //LoadBalancer(int serverCount);
    LoadBalancer(RequestQueue& requestQueue);
    //LoadBalancer(RequestQueue requestQueue, std::vector<WebServer*> webServers);
    ~LoadBalancer();
    void runBalancer(int time, int serverCount);
    void balanceLoad();
    void addRequest(Request* request);
    void addWebServer(WebServer* webServer);
    void processRequest();
    void print();
    bool isEmpty();

};

#endif
