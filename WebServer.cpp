

#include "Request.h"
#include "WebServer.h"
#include <iostream>
using std::cout, std::endl;
#include <queue>

/*
Webserver(s)
o Takes requests from the Load Balancer
o Process the requests
o Asks for another
*/

WebServer::WebServer(){}

WebServer::~WebServer(){
    while(!webQueue.empty()){
        Request* request = webQueue.front();
        webQueue.pop();
        delete request;
    }
}

void WebServer::addRequest(Request* request){
    webQueue.push(request);
}

bool WebServer::isEmpty(){
    return webQueue.empty();
}

void WebServer::processRequest(){
    if(webQueue.empty()){
        cout << "No requests to process" << endl;
        return;
    }
    Request* request = webQueue.front();
    webQueue.pop();
    time += request->getTime();
    cout << "Processing request from " << request->getIPin() << " to " << request->getIPout() << " in " << request->getTime() << " seconds" << endl;
    delete request;
}