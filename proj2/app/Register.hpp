// Register.hpp
// ICS46 Winter 2021 Project 2
// Name: Keyu Zhang
// ID: 19898090
// UCINetID: keyuz4

// Handles actions related to a specific register

#ifndef REGISTER_HPP
#define REGISTER_HPP

#include "Queue.hpp"
#include "Customer.hpp"

class Register
{
private:
    // time needed to process one customer
    unsigned int processTime;
    // pointer to its line
    Queue<Customer>* line;
    // remaining time that the register need to process the current customer
    unsigned int remainingTime;

public:
    Register(unsigned int processTime, Queue<Customer>* line, unsigned int remainingTime);

    // whether a register is empty (avaliable for customers to come)
    bool registerEmpty();

    // pulls one customer from queue(if any), and start processing it
    // if the queue is empty, throws EmptyException
    // returns: the time when the customer entered the queue
    unsigned int processCustomer();

    // one second passes
    void decrementRemainingTime();

    // returns the remaining time that the register need to process this customer
    unsigned int getRemainingTime();
};

#endif