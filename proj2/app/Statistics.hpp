// Statistics.hpp
// ICS46 Winter 2021 Project 2
// Name: Keyu Zhang
// ID: 19898090
// UCINetID: keyuz4

// records the events happened during the simulation

#ifndef STATISTICS_HPP
#define STATISTICS_HPP

class Statistics
{
private:
    // number of customers that entered the line
    unsigned int enteredLine;
    // number of customers that exited the line
    unsigned int exitedLine;
    // number of customers that exited the register
    unsigned int exitedRegister;
    // number of lost customers
    unsigned int lost;
    // total wait time of all customers
    unsigned long totalWaittime;

public:
    Statistics();
    // one customer entered the line
    void enterLine(); 
    // one customer exited the line
    void exitLine();
    // one customer exited the Register
    void exitRegister();
    // lost one customer
    void lostCustomer();

    // add a customer's wait time to total wait time
    void addWaittime(unsigned long waittime);

    // returns the average wait time of all customers that exited the queue
    double getAvgWaittime();

    // get the count of ... data
    unsigned int getEnterLineCount();
    unsigned int getExitLineCount();
    unsigned int getExitRegisterCount();
    unsigned int getLostCount();
    unsigned int leftInLine();
    unsigned int leftInRegister();

    // print the report to standard output
    void writeStatistics();
};

#endif