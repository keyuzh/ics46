// Register.cpp
// ICS46 Winter 2021 Project 2
// Name: Keyu Zhang
// ID: 19898090
// UCINetID: keyuz4

// Handles actions related to a specific register

#include "Customer.hpp"
#include "Register.hpp"

Register::Register(
    unsigned int processTime, Queue<Customer>* line, unsigned int remaining)
    : processTime{processTime}, line{line}, remainingTime{remaining}
{
}

// whether a register is empty (avaliable for customers to come)
bool Register::registerEmpty()
{
    return (remainingTime == 0);
}

// pulls one customer from queue(if any), and start processing it
// if the queue is empty, throws EmptyException
// returns: the time when the customer entered the queue
unsigned int Register::processCustomer()
{
    Customer firstCustomer = line->front();
    unsigned int enterTime = firstCustomer.enterQueueTime;
    // dequeue this customer
    line->dequeue();
    // start processing this customer, reset this counter
    remainingTime = processTime;
    return enterTime;
}

// one second passes
void Register::decrementRemainingTime()
{
    --remainingTime;
}

// returns the remaining time that the register need to process this customer
unsigned int Register::getRemainingTime()
{
    return remainingTime;
}
