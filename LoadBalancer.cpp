#include "LoadBalancer.h"

// manages the webservers and the request queue
// should work for the creation of multiple load 
// balancers and not just be part of hte driver program
/*
Load Balancer
o Queue of requests
o Keeps track of time.
*/

// add new requests at different times
// dynamically allocate and deallocate webservers to maintain balance

// find out which webserver is best based on current state
// have a queue of requests in webserver, assigned by load balancer, that it should be responsible for

LoadBalancer::LoadBalancer(){};

LoadBalancer::LoadBalancer(RequestQueue& requestQueue){
    this->requestQueue = requestQueue;
}

LoadBalancer::~LoadBalancer(){
    while(!webServers.empty()){
        WebServer* webServer = webServers.back();
        webServers.pop_back();
        delete webServer;
    }
}

void LoadBalancer::runBalancer(int time, int serverCount){
    webServers.clear();
    webServers.reserve(serverCount);
    webServers.push_back(new WebServer());
    this->serverCount = 1;
    maxServers = serverCount;
    
    for(int i = 0; i < time; i++){
        balanceLoad();

        // add a new request to the queue randomly
        if(rand() % 11 == 0){
            addRequest();
        }

        // increment the load balancer's time
        this->time++;
        cout << "Time: " << this->time << endl;

        // add a new web server if necessary
        if(requestQueue.size() > (serverCount * 10) && this->serverCount < serverCount){
            addWebServer();
        }
        // deallocate a web server if necessary
        if(requestQueue.size() < (serverCount * 5) && this->serverCount > 1){
            WebServer* webServer = webServers.back();
            webServers.pop_back();
            delete webServer;
            this->serverCount--;
        }
    }
}

void LoadBalancer::balanceLoad() {
    for(int i = 0; i < serverCount; i++){
        if(webServers[i]->isEmpty()){
            webServers[i]->addRequest(requestQueue.getNext());
        }
        webServers[i]->processRequest();
    }
}

void LoadBalancer::addRequest(){
    requestQueue.addRequest(new Request());
}

void LoadBalancer::addWebServer(){
    webServers.push_back(new WebServer());
    serverCount++;
}

void LoadBalancer::processRequest(){
    for(int i = 0; i < serverCount; i++){
        webServers[i]->processRequest();
    }
}

void LoadBalancer::print(){
    for(int i = 0; i < serverCount; i++){
        cout << "WebServer " << i << " has " << webServers[i]->size() << " requests" << endl;
    }
}

bool LoadBalancer::isEmpty(){
    return requestQueue.isEmpty();
}

