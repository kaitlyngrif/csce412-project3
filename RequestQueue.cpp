#include "RequestQueue.h"
#include <iostream>

RequestQueue::RequestQueue() {}

RequestQueue::~RequestQueue() {
    while (!queue.empty()) {
        delete queue.front();
        queue.pop();
    }
}

void RequestQueue::addRequest(Request* request) {
    if (request != nullptr) {
        queue.push(request);
        std::cout << "Added request to queue. Queue size is now: " << queue.size() << std::endl;
    } else {
        std::cerr << "Error: Attempted to add a null request to the queue." << std::endl;
    }
}

Request* RequestQueue::getNext() {
    if (queue.empty()) {
        std::cerr << "Error: Attempted to get a request from an empty queue." << std::endl;
        return nullptr;
    }

    Request* request = queue.front();
    queue.pop();
    return request;
}

bool RequestQueue::isEmpty() {
    return queue.empty();
}

int RequestQueue::size() {
    return queue.size();
}

void RequestQueue::print() {
    std::queue<Request*> tempQueue = queue;
    while (!tempQueue.empty()) {
        tempQueue.front()->print();
        std::cout << std::endl;
        tempQueue.pop();
    }
}
