// main.cpp
// ICS46 Winter 2021 Project 2
// Name: Keyu Zhang
// ID: 19898090
// UCINetID: keyuz4

// log the events during the simulation and print to standard output

#ifndef LOG_HPP
#define LOG_HPP

class Log
{
public:
    // prints the current simulation time
    void printCurrentTime(unsigned int currentTime, bool newline);

    // beginning of the log
    void logStart();

    // last output of the log
    void logEnd(unsigned int time);

    // a customer entered a line
    void enterLine(unsigned int time, unsigned int lineNumber, unsigned int length);

    // a customer exited a line
    void exitLine(unsigned int time, unsigned int lineNumber, unsigned int length, unsigned int waittime);

    // customer entered a register
    void enterRegister(unsigned int time, unsigned int regNumber);

    // customer exited a register
    void exitRegister(unsigned int time, unsigned int regNumber);

    // customer is lost
    void lost(unsigned int time);
};

#endif