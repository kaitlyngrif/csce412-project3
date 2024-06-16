

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

int WebServer::size(){
    return webQueue.size();
}

void WebServer::processRequest(){
    if(webQueue.empty()){
        cout << "No requests to process" << endl;
        return;
    }
    Request* request = webQueue.front();
    // decrement the time it takes to process the request
    request->process();
    if(request->isComplete()) {
        cout << "Request from " << request->getIPin() << " to " << request->getIPout() << " has been processed" << endl;
        webQueue.pop();
        delete request;
    } else {
        cout << "Request from " << request->getIPin() << " to " << request->getIPout() << " is still processing" << endl;
    }
}