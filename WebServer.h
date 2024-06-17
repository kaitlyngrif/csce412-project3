/**
 * @file WebServer.h
 * @author Kaitlyn Griffin
 * @date 2024-06-16
 * 
 * @brief WebServer header file implementation.
 */

#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <queue>
#include "Request.h"

class WebServer {
private:
    std::queue<Request*> webQueue; //!< queue of requests allocated to the Web Server.
    int time; //!< time of the process currently running on the web server.

public:
    WebServer(); //!< constructor.
    ~WebServer(); //!< destructor.
    void addRequest(Request* request); //!< add a request to the web server.
    bool isEmpty(); //!< check if the web server's queue of requests is empty.
    int size(); //!< get the size of the web server's queue of requests.
    int getTime(); //!< get the time required to process the current request.
    void processRequest(); //!< process the request
    std::queue<Request*> getRequests(); //!< get the entire queue of requests.
};

#endif