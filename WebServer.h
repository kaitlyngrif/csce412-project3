#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <queue>
#include "Request.h"

class WebServer {
private:
    std::queue<Request*> webQueue;
    int time;

public:
    WebServer();
    ~WebServer();
    void addRequest(Request* request);
    bool isEmpty();
    int size();
    void processRequest();
    std::queue<Request*> getRequests();
};

#endif