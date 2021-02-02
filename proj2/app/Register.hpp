
#ifndef REGISTER_HPP
#define REGISTER_HPP

#include "Queue.hpp"
#include "structs.hpp"

bool registerEmpty(const Register& reg);

void processCustomer(Simulation& sim, unsigned int queueNum);

#endif