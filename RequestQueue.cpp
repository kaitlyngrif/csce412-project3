/**
 * @file RequestQueue.cpp
 * @author Kaitlyn Griffin
 * @date 2024-06-16
 * 
 * @brief RequestQueue class file.
 */

#include "RequestQueue.h"
#include <iostream>

/**
 * @brief Construct a new Request Queue:: Request Queue object.
 */
RequestQueue::RequestQueue() {}

/**
 * @brief Destroy the Request Queue:: Request Queue object.
 */
RequestQueue::~RequestQueue() {
    while (!queue.empty()) {
        delete queue.front();
        queue.pop();
    }
}

/**
 * @brief Adds a request to the queue.
 *  
 * @param request the request to add to the queue.
 */
void RequestQueue::addRequest(Request* request) {
    if (request != nullptr) {
        queue.push(request);
    } else {
        std::cerr << "Error: Attempted to add a null request to the queue." << std::endl;
    }
}

/**
 * @brief Get the next request from the queue.
 * 
 * @return Request* the next request in the queue.
 */
Request* RequestQueue::getNext() {
    if (queue.empty()) {
        std::cerr << "Error: Attempted to get a request from an empty queue." << std::endl;
        return nullptr;
    }

    Request* request = queue.front();
    queue.pop();
    return request;
}

/**
 * @brief Determine if the queue is empty.
 * 
 * @return true if the queue is empty.
 * @return false if the queue is not empty.
 */
bool RequestQueue::isEmpty() {
    return queue.empty();
}

/**
 * @brief Determine the size of the queue.
 * 
 * @return int the size of the queue.
 */
int RequestQueue::size() {
    return queue.size();
}

/**
 * @brief Print out the queue and its contents.
 */
void RequestQueue::print() {
    std::queue<Request*> tempQueue = queue;
    while (!tempQueue.empty()) {
        tempQueue.front()->print();
        std::cout << std::endl;
        tempQueue.pop();
    }
}
