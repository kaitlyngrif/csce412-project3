/**
 * @file Request.cpp
 * @author Kaitlyn Griffin
 * @date 2024-06-16
 * 
 * @brief Request class implementation.
 */

#include "Request.h"
using std::to_string;
#include <fstream>
extern std::ofstream logFile;

/**
 * @brief Constructs a new Request:: Request object.
 */
Request::Request(){
    //!< generate random IP addresses, ranging from 0 to 255.
    for(int i = 0; i < 4; i++){
        IPin += to_string(rand() % 256);
        IPout += to_string(rand() % 256);
        if(i < 3){
            IPin += ".";
            IPout += ".";
        }
    }
    time = (rand() % 250) + 100;
};

/**
 * @brief Prints out a Request object and its information to the terminal.
 */
void Request::print() {
    cout << "IP in: " << IPin << endl;
    cout << "IP out: " << IPout << endl;
    cout << "Time: " << time << endl;

    logFile << "IP in: " << IPin << endl;
    logFile << "IP out: " << IPout << endl;
    logFile << "Time: " << time << endl;
};
