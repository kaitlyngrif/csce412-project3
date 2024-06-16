#include "WebServer.h"
#include <iostream>
using std::cout, std::endl, std::cerr;

WebServer::WebServer() : time(0) {}

WebServer::~WebServer() {
    while (!webQueue.empty()) {
        Request* request = webQueue.front();
        webQueue.pop();
        delete request;
    }
}

void WebServer::addRequest(Request* request) {
    if (request != nullptr) {
        webQueue.push(request);
    } else {
        cerr << "Error: Attempted to add a null request to the web server." << endl;
    }
}

bool WebServer::isEmpty() {
    return webQueue.empty();
}

int WebServer::size() {
    return webQueue.size();
}

void WebServer::processRequest() {
    if (webQueue.empty()) {
        cout << "No requests to process" << endl;
        return;
    }

    Request* request = webQueue.front();
    request->process();  // decrease request's time by one clock cycle

    if (request->isComplete()) {
        cout << "Request from " << request->getIPin() << " to " << request->getIPout() << " has been processed" << endl;
        webQueue.pop();
        delete request;
    } else {
        cout << "Request from " << request->getIPin() << " to " << request->getIPout() << " is still processing" << endl;
    }
}
