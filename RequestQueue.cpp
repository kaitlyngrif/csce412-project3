#include "RequestQueue.h"

// constructor
RequestQueue::RequestQueue() {}

// destructor
RequestQueue::~RequestQueue() {
    while (!queue.empty()) {
        delete queue.front();
        queue.pop();
    }
}

// add request to queue
void RequestQueue::addRequest(Request* request) {
    queue.push(request);
}

// get request from queue
Request* RequestQueue::getNext() {
    if(queue.empty()) {
        return nullptr;
    }

    Request* request = queue.front();
    queue.pop();
    return request;
}

// check if queue is empty
bool RequestQueue::isEmpty() {
    return queue.empty();
}

// get size of queue
int RequestQueue::size() {
    return queue.size();
}

// print queue
void RequestQueue::print() {
    std::queue<Request*> tempQueue = queue;
    while (!tempQueue.empty()) {
        tempQueue.front()->print();
        cout << endl;
        tempQueue.pop();
    }
    delete &tempQueue; //might cause memory issues, will need to test this
}

