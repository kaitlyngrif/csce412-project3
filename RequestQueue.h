#ifndef REQUESTQUEUE_H
#define REQUESTQUEUE_H

#include "Request.h"
#include <queue>

class RequestQueue {

private:
    std::queue<Request*> queue;

public:
    RequestQueue();
    ~RequestQueue();
    void addRequest(Request* request);
    Request* getNext();
    bool isEmpty();
    int size();
    void print();   
};

#endif