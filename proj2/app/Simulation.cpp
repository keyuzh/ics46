// Simulation.cpp
// ICS46 Winter 2021 Project 2
// Name: Keyu Zhang
// ID: 19898090
// UCINetID: keyuz4

// handles the mechanics of simulation

#include <iostream>
#include <string>
#include <vector>

#include "Simulation.hpp"


Simulation::Simulation(Log* log, Statistics* stats)
    : log{log}, stats{stats}
{
}


void Simulation::setup()
{
    // length of simulation, converted to seconds
    unsigned int simulationMinute;
    std::cin >> simulationMinute;
    length = simulationMinute * 60;

    // initiates current time to 0
    currentTime = 0;

    // number of registers and max line length
    unsigned int registerCount;
    std::cin >> registerCount >> maxLineLength;

    // single line or multi line
    std::string lineMode;
    std::cin >> lineMode;

    // default to single line, change the number for multi line
    unsigned int lineCount{1};
    if (lineMode == "M")
    {
        lineCount = registerCount;
    }
    // initiates the queues
    lines = std::vector<Queue<Customer>>{lineCount, Queue<Customer>{}};

    // get each register's processing time
    for (unsigned int i = 0; i < registerCount; i++)
    {
        unsigned int processTime;
        std::cin >> processTime;
        if (lineMode == "S")
        {
            // single line mode
            registers.push_back(Register{processTime, &lines.at(0), 0});
        }
        else
        {
            registers.push_back(Register{processTime, &lines.at(i), 0});
        }
    }
}


void Simulation::startSimulation()
{
    log->logStart();
    while (currentTime < length)
    {
        getCustomerInput();
        // if the input time is greater than simulation time, ignore that 
        // and only do simulation until the length
        while (currentTime <= length && currentTime <= nextArrivalTime)
        {
            // print("current time:", false);
            // print(sim.currentTime);
            simulateOneSecond();
        }
    }
    stats->writeStatistics();
}


void Simulation::simulateOneSecond()
{
    if (currentTime == length)
    {
        // end of simulation
        log->logEnd(currentTime);
        currentTime++;
        return;
    }
    
    // if customer arrives at this time, put them into queues
    if (currentTime == nextArrivalTime)
    {
        addCustomerToLine(nextArrivalCount);
    }
    simlulateRegisters();
    currentTime++;
}   


void Simulation::simlulateRegisters()
{
    // for every registers, if its free, get one customer from the queue
    for (unsigned int i = 0; i < registers.size(); i++)
    {
        Register* reg = &registers.at(i);
        unsigned int regNumber = i + 1;
        if (!reg->registerEmpty())
        {
            simulateNonEmptyRegister(reg, regNumber);
        }
        // now check if the register becomes empty
        if (reg->registerEmpty())
        {
            unsigned int lineNumber = getLineNumber(regNumber);
            simulateEmptyRegister(reg, regNumber, lineNumber);
        }
    }
}


// if register has a customer, decrement the remaining time and see if its finished
void Simulation::simulateNonEmptyRegister(Register* reg, unsigned int regNumber)
{
    reg->decrementRemainingTime();
    if (reg->getRemainingTime() == 0)
    {
        // one customer exited register
        log->exitRegister(currentTime, regNumber);
        stats->exitRegister();
    }
}


// try getting a customer from queue into register,
// if not (queue is empty), do nothing for this round of simulation
void Simulation::simulateEmptyRegister(
    Register* reg, unsigned int regNumber, unsigned int lineNumber)
{
    try
    {
        unsigned int enterQueueTime = reg->processCustomer();
        unsigned int waitTime = currentTime - enterQueueTime;
        // log the customer exiting the line and add to statistics data
        log->exitLine(currentTime, lineNumber, getLineLength(lineNumber), waitTime);
        stats->exitLine();
        stats->addWaittime(waitTime);
        // now the customer entered the register, log that as well
        log->enterRegister(currentTime, regNumber);
    }
    catch(const EmptyException& e)
    {
        // empty queue, just wait
    }
}


// the input after initial setup, next arrival time and count
void Simulation::getCustomerInput()
{
    std::string first;
    std::cin >> first;
    if (first == "END")
    {
        // end is equvalent to input: 0, length of simulation
        nextArrivalCount = 0;
        nextArrivalTime = length;
        return;
    }

    // convert that string to int
    nextArrivalCount = std::stoi(first);
    // time of next customer arrival and the number of customers
    std::cin >> nextArrivalTime;
}


// lost a customer, record it
void Simulation::lostCustomer()
{
    log->lost(currentTime);
    stats->lostCustomer();
}


// returns the number of the shortest line
unsigned int Simulation::findShortestLine()
{
    // returns the number of shortest line (1-index), if there's a tie
    // returns the lowest line number
    if (lines.size() == 1)
    {
        // single line
        return 1;
    }

    // find the size of shortest queue
    unsigned int shortest = lines.at(0).size();
    for (unsigned int i = 1; i < lines.size(); i++)
    {
        unsigned int sz = lines.at(i).size();
        shortest = std::min(shortest, sz);
    }
    // find which queue has that size
    unsigned int queueNumber = 0;
    for (unsigned int i = 0; i < lines.size(); i++)
    {
        if (lines.at(i).size() == shortest)
        {
            queueNumber = i + 1; // since 1-indexing
            break;
        }
    }
    return queueNumber;
}


// add a customer
void Simulation::addCustomerToLine(unsigned int customerCount)
{
    // add some number of customers to shortest lines, if every line is full
    // the customer is lost
    for (unsigned int i = 0; i < customerCount; i++)
    {
        // first find the shortest queues
        unsigned int shortestQueue = findShortestLine();
        // add that customer into that queue
        if (!addToLine(shortestQueue))
        {
            // cant add that customer to queue
            lostCustomer();
        }
    }
}


// try to add a customer to a line, raise EmptyException if failed
bool Simulation::addToLine(unsigned int queueNumber)
{
    // add a customer to the queue at queueNumber if possible,
    // return false if the queue is full
    unsigned int queueIndex = queueNumber - 1;

    if (lines.at(queueIndex).size() == maxLineLength)
    {
        // queue is full
        return false;
    }

    Customer customer = Customer{currentTime};
    lines.at(queueIndex).enqueue(customer);
    log->enterLine(currentTime, queueNumber, getLineLength(queueNumber));
    stats->enterLine();
    return true;
}


// returns the current time in simulation
unsigned int Simulation::getCurrentTime()
{
    return currentTime;
}


// returns a reference of a given line
Queue<Customer>& Simulation::getLine(unsigned int lineNumber)
{
    return lines.at(lineNumber-1);
}


// returns the length of a given line
unsigned int Simulation::getLineLength(unsigned int lineNumber)
{
    return getLine(lineNumber).size();
}


// given a register number, returns the corresponding line number
unsigned int Simulation::getLineNumber(unsigned int regNumber)
{
    if (lines.size() == 1)
    {
        // single-line -> always line 1
        return 1;
    }
    // multi-line -> same number
    return regNumber;
}
