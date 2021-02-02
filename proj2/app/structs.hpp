#ifndef STRUCTS_HPP
#define STRUCTS_HPP

#include <vector>
#include "Queue.hpp"

struct Customer;
struct Register;
struct Simulation;
struct Statistics;

struct Customer
{
    // unsigned int enterQueueTime;
};

struct Register
{
    unsigned int processTime;
    unsigned int maxLength;
    Queue<Customer>* line;
    unsigned int remainingTime;
    
};

struct Simulation
{
    // length of simulation in seconds
    unsigned int length;
    unsigned int maxLineLength;

    unsigned int currentTime;

    unsigned int nextArrivalTime;
    unsigned int nextArrivalCount;

    std::vector<Register> registers;
    std::vector<Queue<Customer>> lines;
};

struct Statistics
{
    unsigned int enteredLine;
    unsigned int exitedLine;
    unsigned int exitedRegister;
    unsigned int lost;
    unsigned long totalWaittime;
};

#endif