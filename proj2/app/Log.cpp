// Log.cpp  
// ICS46 Winter 2021 Project 2
// Name: Keyu Zhang
// ID: 19898090
// UCINetID: keyuz4

// log the events during the simulation and print to standard output

#include <iostream>
#include <string>

#include "Log.hpp"

namespace
{
    // a template print function to make output easier
    template <typename T>
    void print(const T& toPrint, bool newline=true)
    {
        std::cout << toPrint;
        if (newline)
        {
            std::cout << std::endl;
        }
    }
}

// prints the current simulation time
void Log::printCurrentTime(unsigned int currentTime, bool newline=false)
{
    print(currentTime, newline);
}


// beginning of the log
void Log::logStart()
{
    print("LOG");
    print("0 start");
}

// last output of the log
void Log::logEnd(unsigned int time)
{
    print(time, false);
    print(" end");
}

// a customer entered a line
void Log::enterLine(unsigned int time, unsigned int lineNumber, unsigned int length)
{
    printCurrentTime(time);
    print(" entered line ", false);
    print(lineNumber, false);
    print(" length ", false);
    print(length);
}

// a customer exited a line
void Log::exitLine(unsigned int time, unsigned int lineNumber, unsigned int length, unsigned int waittime)
{
    printCurrentTime(time);
    print(" exited line ", false);
    print(lineNumber, false);
    print(" length ", false);
    print(length, false);
    print(" wait time ", false);
    print(waittime);
}

// customer entered a register
void Log::enterRegister(unsigned int time, unsigned int regNumber)
{
    printCurrentTime(time);
    print(" entered register ", false);
    print(regNumber);
}

// customer exited a register
void Log::exitRegister(unsigned int time, unsigned int regNumber)
{
    printCurrentTime(time);
    print(" exited register ", false);
    print(regNumber);
}

// customer is lost
void Log::lost(unsigned int time)
{
    printCurrentTime(time);
    print(" lost");
}
