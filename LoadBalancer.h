#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <iostream>
#include <queue>
#include <vector>
#include <memory>
#include "RequestQueue.h"
#include "WebServer.h"

class LoadBalancer {
private:
    RequestQueue& requestQueue;
    std::vector<std::unique_ptr<WebServer>> webServers;
    int time;
    int serverCount;
    int maxServers;
    void balanceLoad();

public:
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
