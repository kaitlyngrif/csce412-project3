/**
 * @file LoadBalancer.cpp
 * @author Kaitlyn Griffin
 * @date 2024-06-16
 * 
 * @brief LoadBalancer class implementation
 */

#include "LoadBalancer.h"
#include <iostream>
#include <memory>
using std::endl, std::cerr, std::cout;
#include <fstream>
extern std::ofstream logFile;

/**
 * @brief Construct a new Load Balancer:: Load Balancer object.
 * 
 * @param requestQueue the request queue to use while giving requests to servers.
 */
LoadBalancer::LoadBalancer(RequestQueue& requestQueue)
    : requestQueue(requestQueue), time(0), serverCount(0), maxServers(0) {
}

/**
 * @brief Destroy the Load Balancer:: Load Balancer object.
 */
LoadBalancer::~LoadBalancer() {
    while (!requestQueue.isEmpty()) {
        Request* req = requestQueue.getNext();
        delete req;
    }
}


/**
 * @brief Run the load balancer for a given amount of time with a given number of servers.
 * 
 * @param time The amount of time to run the load balancer.
 * @param serverCount The number of servers to use.
 */
void LoadBalancer::runBalancer(int time, int serverCount) {
    maxServers = serverCount;

    webServers.clear();
    webServers.reserve(serverCount);

    for (int i = 0; i < serverCount; ++i) {
        webServers.push_back(std::make_unique<WebServer>());
    }

    for (int i = 0; i < time; ++i) {
        balanceLoad();

        //!< add new request to the queue randomly.
        if (rand() % 20 == 0) { //!< 5% chance of adding a request.
            cout << "Adding a request randomly" << endl;
            logFile << "Adding a request randomly" << endl;
            addRequest();
        }

        //!< increment load balancer's time.
        this->time++;
        cout << endl << "Time: " << this->time << endl;
        logFile << endl << "Time: " << this->time << endl;

        //!< process requests on each server.
        processRequest();
    }
}

/**
 * @brief A helper function to balance the load assigned to servers.
 */
void LoadBalancer::balanceLoad() {
    //!< check if a server needs to be allocated or deallocated.
    if (requestQueue.size() > (serverCount * 10) && serverCount < maxServers) {
        addWebServer();
    } else if (requestQueue.size() < (serverCount * 10) && serverCount > 1) {
        //!< get the requests from the last server.
        std::queue<Request*> q = webServers[serverCount - 1]->getRequests();
        //!< redistribute requests from deallocated server across existing web servers.
        while(!q.empty()) {
            for(int i = 0; i < serverCount - 1; i++) {
                if(q.empty()) {
                    break;
                } else {
                    webServers[i]->addRequest(q.front());
                    q.pop();
                }
            }
        }

        //!< deallocate the server.
        removeWebServer();
    }

    //!< balance load using least connections method.
    if (!requestQueue.isEmpty()) {
        Request* nextRequest = requestQueue.getNext();
        if (nextRequest != nullptr) {
            int leastLoadedServer = getLeastLoadedServer();
            if (webServers[leastLoadedServer]->size() < 10) {
                webServers[leastLoadedServer]->addRequest(nextRequest);
            } else {
                requestQueue.addRequest(nextRequest);  //!< if no server can take the request, put it back.
            }
        } else {
            cerr << "Error: Attempted to get a null request from the queue." << endl;
            logFile << "Error: Attempted to get a null request from the queue." << endl;
        }
    }
}

/**
 * @brief A helper function to get the index of the least loaded server.
 * 
 * @return int the index of the server with the least amount of requests.
 */
int LoadBalancer::getLeastLoadedServer() {
    int min = webServers[0]->size();
    int index = 0;
    for(int i = 1; i < serverCount; i++) {
        if(webServers[i]->size() < min) {
            min = webServers[i]->size();
            index = i;
        }
    }
    return index;
}

/**
 * @brief  Adds a request to the request queue.
 */
void LoadBalancer::addRequest() {
    Request* newRequest = new Request();
    requestQueue.addRequest(newRequest);
}


/**
 * @brief Adds a web server to the load balancer.
 * 
 */
void LoadBalancer::addWebServer() {
    webServers.push_back(std::make_unique<WebServer>());
    serverCount++;
    cout << "Allocated new web server. Total servers: " << serverCount << endl;
    logFile << "Allocated new web server. Total servers: " << serverCount << endl;
}

/**
 * @brief Removes a web server from the load balancer.
 */
void LoadBalancer::removeWebServer() {
    if (serverCount > 1) {
        webServers.pop_back();
        serverCount--;
        cout << "Deallocated a web server. Total servers: " << serverCount << endl;
        logFile << "Deallocated a web server. Total servers: " << serverCount << endl;
    }
}

/**
 * @brief Processes requests on each server.
 */
void LoadBalancer::processRequest() {
    for (int i = 0; i < serverCount; i++) {
        if (webServers[i]) {
            cout << "Server " << (i+1) << " processing request for " << webServers[i]->getTime() << " clock cycles." << endl;
            logFile << "Server " << (i+1) << " processing request for " << webServers[i]->getTime() << " clock cycles." << endl;
            webServers[i]->processRequest();
        } else {
            cerr << "Error: Attempted to process request on a null web server." << endl;
            logFile << "Error: Attempted to process request on a null web server." << endl;
        }
    }
}

/**
 * @brief Prints the number of requests on each server.
 */
void LoadBalancer::print() {
    for (int i = 0; i < serverCount; i++) {
        if (webServers[i]) {
            cout << "WebServer " << i << " has " << webServers[i]->size() << " requests" << endl;
            logFile << "WebServer " << i << " has " << webServers[i]->size() << " requests" << endl;
        } else {
            cerr << "Error: webServers[" << i << "] is null." << endl;
            logFile << "Error: webServers[" << i << "] is null." << endl;
        }
    }
}

/**
 * @brief Checks if the request queue is empty.
 * 
 * @return true if the request queue is empty.
 * @return false if the request queue is not empty.
 */
bool LoadBalancer::isEmpty() {
    return requestQueue.isEmpty();
}

/**
 * @brief Get the average run time of the requests.
 * 
 * @return double the average run time of the requests.
 */
double LoadBalancer::averageRunTime() {
    double total = 0;
    for(int i = 0; i < requestQueue.size(); i++) {
        Request* req = requestQueue.getNext();
        total += req->getTime();
    }
    
    return (total / requestQueue.size());
}
