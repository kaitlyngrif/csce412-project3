#include <queue>
#include "Request.h"

class WebServer {
private:
    // variables here
    // have a queue of requests, assigned by load balancer, that it should be responsible for
    std::queue<Request*> webQueue;
    int time;

public:
    // functions here
    WebServer();
    ~WebServer();
    void addRequest(Request* request);
    bool isEmpty();
    void processRequest();
};