#include "Register.hpp"

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
