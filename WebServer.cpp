/**
 * @file WebServer.cpp
 * @author Kaitlyn Griffin
 * @date 2024-06-16
 * 
 * @brief WebServer class implementation.
 */

#include "WebServer.h"
#include <iostream>
using std::cout, std::endl, std::cerr;

/**
 * @brief Construct a new Web Server:: Web Server object.
 */
WebServer::WebServer() : time(0) {}

/**
 * @brief Destroy the Web Server:: Web Server object.
 */
WebServer::~WebServer() {
    while (!webQueue.empty()) {
        Request* request = webQueue.front();
        webQueue.pop();
    }
}

/**
 * @brief Add a request to the web server.
 * 
 * @param request the request to add to the web server.
 */
void WebServer::addRequest(Request* request) {
    if (request != nullptr) {
        webQueue.push(request);
    } else {
        cerr << "Error: Attempted to add a null request to the web server." << endl;
    }
}

/**
 * @brief Get the entire queue of requests.
 * 
 * @return std::queue<Request*> the queue of requests allocated to the Web Server.
 */
std::queue<Request*> WebServer::getRequests() {
    return webQueue;
}

/**
 * @brief Determine if the web server's queue of requests is empty.
 * 
 * @return true if the queue is empty.
 * @return false if the queue is not empty.
 */
bool WebServer::isEmpty() {
    return webQueue.empty();
}

/**
 * @brief Determine the size of the web server's queue of requests.
 * 
 * @return int the size of the web server's queue of requests.
 */
int WebServer::size() {
    return webQueue.size();
}

/**
 * @brief Determine the time required to process the current request.
 * 
 * @return int the time required to process the current request.
 */
int WebServer::getTime() {
    if(webQueue.empty()) {
        time = 0;
        return 0;
    }
    time = webQueue.front()->getTime();
    return time;
}

/**
 * @brief Process the current request, decrementing its time by one clock cycle.
 */
void WebServer::processRequest() {
    if (webQueue.empty()) {
        cout << "No requests to process" << endl;
        return;
    }

    Request* request = webQueue.front();
    request->process();

    if (request->isComplete()) {
        cout << "Request from " << request->getIPin() << " to " << request->getIPout() << " has been processed" << endl;
        webQueue.pop();
        delete request;
    } else {
        cout << "Request from " << request->getIPin() << " to " << request->getIPout() << " is still processing" << endl;
    }
}
