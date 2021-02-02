#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
#include "Queue.hpp"
#include "EmptyException.hpp"

struct Customer
{
    unsigned int enterQueueTime;
};

struct Statistics
{
    unsigned int enteredLine;
    unsigned int exitedLine;
    unsigned int exitedRegister;
    unsigned int lost;
    unsigned long totalWaittime;
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

void setup(Simulation& sim)
{
    // length of simulation, converted to seconds
    unsigned int simulationMinute;
    std::cin >> simulationMinute;
    sim.length = simulationMinute * 60;

    // initiates current time to 0
    sim.currentTime = 0;

    // number of registers and max line length
    unsigned int registerCount;
    std::cin >> registerCount >> sim.maxLineLength;

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
    sim.lines = std::vector<Queue<Customer>>{lineCount, Queue<Customer>{}};

    // get each register's processing time
    for (unsigned int i = 0; i < registerCount; i++)
    {
        unsigned int processTime;
        std::cin >> processTime;
        sim.registers.push_back(Register{
            processTime, sim.maxLineLength, &sim.lines.at(i), 0
            });
    }
}

namespace
{
    template <typename T>
    void print(const T& s, bool newline=true)
    {
        std::cout << s;
        if (newline)
        {
        std::cout << std::endl;
        }
    }
} // namespace

void getCustomerInput(Simulation& sim)
{
    // time of next custommer arrival and the number of customers
    std::cin >> sim.nextArrivalCount >> sim.nextArrivalTime;
}

unsigned int findShortestQueue(const Simulation& sim)
{
    // returns the number of shortest queue (1-index), if there's a tie
    // returns the lowest queue number
    if (sim.lines.size() == 1)
    {
        // single line
        return 1;
    }

    // find the size of shortest queue
    unsigned int shortest = sim.lines.at(0).size();
    for (unsigned int i = 1; i < sim.lines.size(); i++)
    {
        unsigned int sz = sim.lines.at(i).size();
        shortest = std::min(shortest, sz);
    }
    // find which queue has that size
    unsigned int queueNumber = 0;
    for (unsigned int i = 0; i < sim.lines.size(); i++)
    {
        if (sim.lines.at(i).size() == shortest)
        {
            queueNumber = i + 1; // since 1-indexing
            break;
        }
    }
    return queueNumber;
}

bool addToQueue(Simulation& sim, unsigned int queueNumber)
{
    // add a customer to the queue at queueNumber if possible,
    // return false if the queue is full
    unsigned int queueIndex = queueNumber - 1;

    if (sim.lines.at(queueIndex).size() == sim.maxLineLength)
    {
        // queue is full
        return false;
    }

    Customer* customer = new Customer{};
    sim.lines.at(queueIndex).enqueue(*customer);
    // print("entered line", false);
    // print(queueNumber);
    std::cout << sim.currentTime << " entered line " << queueNumber;
    std::cout << " length " << sim.registers.at(queueIndex).line->size();
    std::cout << std::endl;
    return true;
}

bool registerEmpty(const Register& reg)
{
    return (reg.remainingTime == 0);
    // if (reg.remainingTime > 0)
    // {
    //     return false;
    // }
}

void processCustomer(Simulation& sim, unsigned int queueNum)
{
    // pulls one customer from queue(if any), and start processing it
    try
    {
        unsigned int queueIndex = queueNum - 1;
        sim.registers.at(queueIndex).line->dequeue();
        std::cout << sim.currentTime << " exited line " << queueNum << std::endl;
        sim.registers.at(queueIndex).remainingTime = sim.registers.at(queueIndex).processTime;
        std::cout << sim.currentTime << " entered register " << queueNum << std::endl;
    }
    catch(const EmptyException& e)
    {
    }
}

void incrementTime(Simulation& sim)
{
    sim.currentTime++;
    // for (unsigned int i = 0; i < sim.registers.size(); i++)
    // {
    //     // for any register that is not empty, decrement remaining time
    //     if (!registerEmpty(sim.registers.at(i)))
    //     {
    //         sim.registers.at(i).remainingTime--;
    //     }
        
    // }
    
}

void lostCustomer(Simulation& sim)
{
    std::cout << sim.currentTime << " lost" << std::endl;
    // TODO: increment lost count
}

void addCustomerToLine(Simulation& sim, unsigned int customerCount)
{
    // add some number of customers to shortest lines, if every line is full
    // the customer is lost
    for (unsigned int i = 0; i < customerCount; i++)
    {
        // first find the shortest queues
        unsigned int shortestQueue = findShortestQueue(sim);
        // add that customer into that queue
        if (!addToQueue(sim, shortestQueue))
        {
            lostCustomer(sim);
        }
    }
}

void simlulateRegisters(Simulation& sim)
{
    // for every registers, if its free, get one customer from the queue
    for (unsigned int i = 0; i < sim.registers.size(); i++)
    {
        unsigned int registerNum = i+1;
        if (!registerEmpty(sim.registers.at(i)))
        {
            // if register has a customer, decrement the remaining time and see
            // if its finished
            unsigned int remaining = --sim.registers.at(i).remainingTime;
            if (remaining == 0)
            {
                // one customer exited register
                std::cout << sim.currentTime << " exited register " << registerNum << std::endl;
                // TODO: increment exited customer count
            }
        }

        if (registerEmpty(sim.registers.at(i)))
        {
            processCustomer(sim, i+1);
        }
    }

}

void simulateOneSecond(Simulation& sim)
{
    // if customer arrives at this time, put them into queues
    if (sim.currentTime == sim.nextArrivalTime)
    {
        addCustomerToLine(sim, sim.nextArrivalCount);
    }
    simlulateRegisters(sim);

    incrementTime(sim);
}

int main()
{
    Simulation sim;
    setup(sim);

    print("length");
    print(sim.length);

    print("number of registers");
    print(sim.registers.size());

    print("max line length");
    print(sim.maxLineLength);

    print("line processing times");
    for (int i = 0; i < sim.registers.size(); i++)
    {
        print(sim.registers.at(i).processTime);
    }
    
    print("num of lines");
    print(sim.lines.size());

    // now that the setup is complete, start the simulation
    while (sim.currentTime < sim.length)
    {
        getCustomerInput(sim);

        while (sim.currentTime <= sim.nextArrivalTime)
        {
            print("current time:", false);
            print(sim.currentTime);
            simulateOneSecond(sim);

        }
    }
    
    
    return 0;
}

