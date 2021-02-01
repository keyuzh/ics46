#include <string>
#include <iostream>
#include <vector>
#include "Queue.hpp"

struct Customer
{

};


struct Register
{
   unsigned int processTime;
   unsigned int maxLength;
};

struct Simulation
{
    // length of simulation in seconds
    unsigned int length;
    unsigned int maxLineLength;

    std::vector<Register> registers;
    std::vector<Queue<Customer>> lines;
};

void setup(Simulation& sim)
{
    // length of simulation, converted to seconds
    unsigned int simulationMinute;
    std::cin >> simulationMinute;
    sim.length = simulationMinute * 60;

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

    // get each register's processing time
    for (unsigned int i = 0; i < registerCount; i++)
    {
        unsigned int processTime;
        std::cin >> processTime;
        sim.registers.push_back(Register{processTime, sim.maxLineLength});
    }
    
    // initiates the queues
    for (unsigned int i = 0; i < lineCount; i++)
    {
        sim.lines.push_back(Queue<Customer>{});
    }
}

namespace
{
    template <typename T>
    void print(const T& s)
    {
        std::cout << s << std::endl;
    }
} // namespace


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
    
    
    return 0;
}

