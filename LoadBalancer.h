/**
 * @file LoadBalancer.h
 * @author Kaitlyn Griffin
 * @date 2024-06-16
 * 
 * @brief LoadBalancer header file.
 */

#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <iostream>
#include <queue>
#include <vector>
#include <memory>
#include "RequestQueue.h"
#include "WebServer.h"

/**
 * @brief LoadBalancer class header.
 */
class LoadBalancer {
private:
    RequestQueue& requestQueue; //!< reference to the request queue.
    std::vector<std::unique_ptr<WebServer>> webServers; //!< vector of web servers.
    int time; //!< time of the process currently running load balancer.
    int serverCount; //!< number of servers.
    int maxServers; //!< maximum number of servers.
    void balanceLoad(); //!< function used to balance the load between servers.

public:
    LoadBalancer(RequestQueue& requestQueue); //!< constructor.
    ~LoadBalancer(); //!< destructor.
    void runBalancer(int time, int serverCount); //!< run the load balancer for a given amount of time with a given number of servers.
    void addRequest(); //!< add a request to the request queue.
    void addWebServer(); //!< add a web server.
    void removeWebServer(); //!< remove a web server.
    int getLeastLoadedServer(); //!< get the least loaded server.
    void processRequest(); //!< process requests on each server.
    void print(); //!< print the status of all web servers the load balancer is responsible for.
    bool isEmpty(); //!< check if the request queue is empty.
};

#endif
