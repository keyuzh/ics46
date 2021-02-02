#include "Simulation.hpp"
#include <vector>
#include "Register.hpp"
#include <string>
#include <sstream>

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

void getCustomerInput(Simulation& sim)
{
    std::cout << "GETTING INPUT" << std::endl;
    std::string first;
    std::cin >> first;
    if (first == "END")
    {
        // end is equvalent to input: 0, length of simulation
        sim.nextArrivalCount = 0;
        sim.nextArrivalTime = sim.length;
        return;
    }

    sim.nextArrivalCount = std::stoi(first);
    // time of next customer arrival and the number of customers
    std::cin >> sim.nextArrivalTime;
    std::cout << "HERE" << std::endl;
    std::cout << sim.nextArrivalCount << sim.nextArrivalTime << std::endl;
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
    if (sim.currentTime == sim.length)
    {
        // end of simulation
        std::cout << sim.length << " end" << std::endl;
        sim.currentTime++;
        return;
    }
    
    // if customer arrives at this time, put them into queues
    if (sim.currentTime == sim.nextArrivalTime)
    {
        addCustomerToLine(sim, sim.nextArrivalCount);
    }
    simlulateRegisters(sim);
    sim.currentTime++;
}