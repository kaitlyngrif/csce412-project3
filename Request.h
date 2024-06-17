/**
 * @file Request.h
 * @author Kaitlyn Griffin
 * @date 2024-06-16
 * 
 * @brief Request header file.
 */

#ifndef REQUEST_H
#define REQUEST_H

#include <iostream>
using std::cout, std::endl, std::string;

/**
 * @brief The header file for the Request class.
 */
struct Request {
private:
    string IPin = ""; //!< IP address in.
    string IPout = ""; //!< IP address out.
    int time = 0; //!< time to process request.

public:
    /**
     * @brief Construct a new Request object.
     * 
     * @param IPin the IP address in for the Request.
     * @param IPout the IP address out for the Request.
     * @param time the time required to process the Request.
     */
    Request(string IPin, string IPout, int time) {
        this->IPin = IPin;
        this->IPout = IPout;
        this->time = time;
    } //!< constructor.
    Request(); //!< default constructor.
    void print(); //!< print the request.
    /**
     * @brief Get the time required to process the request.
     * 
     * @return int the time required to process the request.
     */
    int getTime() { return time; } //!< get the time.
    /**
     * @brief Get the IP address in.
     * 
     * @return string the IP address in for the Request.
     */
    string getIPin() { return IPin; } //!< get the IP in.
    /**
     * @brief The IP address out.
     *  
     * @return string the IP address out for the Request.
     */
    string getIPout() { return IPout; } //!< get the IP out.
    /**
     * @brief Check if the Request is done being processed.
     * 
     * @return true if the Request is done being processed.
     * @return false if the Request is not done being processed.
     */
    bool isComplete() { return time <= 0; } //!< check if the request is complete.
    /**
     * @brief Decrease the time required to process the request by one clock cycle.
     */
    void process() { time--; } //!< process the request.
};

#endif