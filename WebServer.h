#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <queue>
#include "Request.h"

class WebServer {

private:
    // variables here
    // have a queue of requests, assigned by load balancer, that it should be responsible for
    std::queue<Request*> webQueue = std::queue<Request*>();
    int time = 0;

public:
    // functions here
    WebServer();
    ~WebServer();
    void addRequest(Request* request);
    bool isEmpty();
    void processRequest();
    int size();
};

#endif