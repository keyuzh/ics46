#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "Queue.hpp"
#include "structs.hpp"
#include <vector>


void setup(Simulation& sim);

void getCustomerInput(Simulation& sim);

unsigned int findShortestQueue(const Simulation& sim);

bool addToQueue(Simulation& sim, unsigned int queueNumber);

void lostCustomer(Simulation& sim);

void addCustomerToLine(Simulation& sim, unsigned int customerCount);

void simlulateRegisters(Simulation& sim);

void simulateOneSecond(Simulation& sim);

#endif