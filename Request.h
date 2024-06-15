// holds request

#ifndef REQUEST_H
#define REQUEST_H

#include <iostream>
using std::cout, std::endl, std::string;

struct Request {
    // IP addresses for in and out + time to process
private:
    string IPin;
    string IPout;
    int time;

public:
    Request(string IPin, string IPout, int time) {
        this->IPin = IPin;
        this->IPout = IPout;
        this->time = time;
    }
    Request();
    void print();
    int getTime() { return time; }
    string getIPin() { return IPin; }
    string getIPout() { return IPout; }
};

#endif