// Simulation.hpp
// ICS46 Winter 2021 Project 2
// Name: Keyu Zhang
// ID: 19898090
// UCINetID: keyuz4

// handles the mechanics of simulation

#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <vector>

#include "Customer.hpp"
#include "Log.hpp"
#include "Queue.hpp"
#include "Register.hpp"
#include "Statistics.hpp"

class Simulation
{
private:
    // length of simulation
    unsigned int length;
    // maximum line length
    unsigned int maxLineLength;

    // current time in the simulation
    unsigned int currentTime;

    // next time that some customer will come
    unsigned int nextArrivalTime;
    // number of customers coming in the next time
    unsigned int nextArrivalCount;

    // vector storing the registers
    std::vector<Register> registers;
    // vector for the lines 
    std::vector<Queue<Customer>> lines;

    // pointers to the log and stats objects
    Log* log;
    Statistics* stats;

public:
    Simulation(Log* log, Statistics* stats);

    // get the first parts of user input
    void setup();
    // starts the simulation
    void startSimulation();

private:
    // all simulation for the entire second
    void simulateOneSecond();

    // do one round of simulation for registers
    void simlulateRegisters();

    // if register has a customer, decrement the remaining time
    // and see if its finished
    void simulateNonEmptyRegister(Register* reg, unsigned int regNumber);

    // try getting a customer from queue into register, if not (queue is empty)
    // do nothing for this round of simulation
    void simulateEmptyRegister(
        Register* reg, unsigned int regNumber, unsigned int lineNumber);

    // the input after initial setup, next arrival time and count
    void getCustomerInput();

    // lost a customer, record it
    void lostCustomer();

    // returns the number of the shortest queue
    unsigned int findShortestLine();
    // add a customer
    void addCustomerToLine(unsigned int customerCount);
    // try to add a customer to a queue, raise EmptyException if failed
    bool addToLine(unsigned int queueNumber);

    // returns the current time in simulation
    unsigned int getCurrentTime();
    // returns a reference of a given line
    Queue<Customer>& getLine(unsigned int lineNumber);
    // returns the length of a given line
    unsigned int getLineLength(unsigned int lineNumber);
    // given a register number, returns the corresponding line number
    unsigned int getLineNumber(unsigned int regNumber);
};

#endif