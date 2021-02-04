// main.cpp
// ICS46 Winter 2021 Project 2
// Name: Keyu Zhang
// ID: 19898090
// UCINetID: keyuz4

#include "Simulation.hpp"
#include "Statistics.hpp"
#include "Log.hpp"

int main()
{
    // initiates the classes we need
    Log log;
    Statistics stats;
    Simulation sim{&log, &stats};
    // get first few lines of input
    sim.setup();
    // now that the setup is complete, start the simulation
    sim.startSimulation();

    return 0;
}
