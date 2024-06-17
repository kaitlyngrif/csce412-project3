/**
 * @file RequestQueue.h
 * @author Kaitlyn Griffin
 * @date 2024-06-16
 * 
 * @brief RequestQueue header file.
 */

#ifndef REQUESTQUEUE_H
#define REQUESTQUEUE_H

#include "Request.h"
#include <queue>
#include <vector>

class RequestQueue {
private:
    std::queue<Request*> queue; //!< queue of requests.
    
public:
    RequestQueue(); //!< constructor.
    ~RequestQueue(); //!< destructor.
    void addRequest(Request* request); //!< add a request to the queue.
    Request* getNext(); //!< get the next request.
    bool isEmpty(); //!< check if the queue is empty.
    int size(); //!< get the size of the queue.
    void print(); //!< print the queue.
    std::vector<int> requestTimes; //!< the times of the requests.
};

#endif
