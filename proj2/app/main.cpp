#include <string>
#include <iostream>
#include <vector>
#include "Queue.hpp"
#include "EmptyException.hpp"

#include "Customer.hpp"
#include "Register.hpp"
#include "Simulation.hpp"
#include "Statistics.hpp"

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

