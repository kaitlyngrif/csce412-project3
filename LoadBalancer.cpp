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
