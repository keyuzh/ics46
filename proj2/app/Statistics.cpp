// Statistics.cpp
// ICS46 Winter 2021 Project 2
// Name: Keyu Zhang
// ID: 19898090
// UCINetID: keyuz4

// records the events happened during the simulation

#include <iomanip>
#include <iostream>
#include <string>

#include "Statistics.hpp"

Statistics::Statistics()
    : enteredLine{0}, exitedLine{0}, exitedRegister{0}, lost{0}, totalWaittime{0}
{
}

// one customer entered the line
void Statistics::enterLine()
{
    enteredLine++;
}

// one customer exited the line
void Statistics::exitLine()
{
    exitedLine++;
}

// one customer exited the Register
void Statistics::exitRegister()
{
    exitedRegister++;
}

// lost one customer
void Statistics::lostCustomer()
{
    lost++;
}

// add a customer's wait time to total wait time
void Statistics::addWaittime(unsigned long waittime)
{
    totalWaittime += waittime;
}

// returns the average wait time of all customers that exited the queue
double Statistics::getAvgWaittime()
{
    return double(totalWaittime) / double(exitedLine);
}

// get the count of ... data
unsigned int Statistics::getEnterLineCount()
{
    return enteredLine;
}

// get the count of ... data
unsigned int Statistics::getExitLineCount()
{
    return exitedLine;
}

// get the count of ... data
unsigned int Statistics::getExitRegisterCount()
{
    return exitedRegister;
}

// get the count of ... data
unsigned int Statistics::getLostCount()
{
    return lost;
}

// get the count of ... data
unsigned int Statistics::leftInLine()
{
    return enteredLine - exitedLine;
}

// get the count of ... data
unsigned int Statistics::leftInRegister()
{
    // exit line implies enter register
    return exitedLine - exitedRegister;
}


// print the report to standard output
void Statistics::writeStatistics()
{
    std::cout << std::endl << "STATS" << std::endl;

    std::cout << "Entered Line    : " << enteredLine << std::endl;
    std::cout << "Exited Line     : " << exitedLine << std::endl;
    std::cout << "Exited Register : " << exitedRegister << std::endl;
    std::cout << "Avg Wait Time   : " << std::fixed << std::setprecision(2);
    std::cout << getAvgWaittime() << std::endl;
    std::cout << "Left In Line    : " << leftInLine() << std::endl;
    std::cout << "Left In Register: " << leftInRegister() << std::endl;
    std::cout << "Lost            : " << lost << std::endl;
}