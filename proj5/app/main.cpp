// main.cpp
//
// ICS 46 Winter 2021
// Project #5: Rock and Roll Stops the Traffic
//
// This is the program's main() function, which is the entry point for your
// console user interface.

#include "TripCalculator.hpp"
#include <iostream>

int main()
{
    TripCalculator cal{std::cin};
    cal.readRoadMap();  // read input

    if (cal.isConnected())
    {
        cal.readTrips();     // read trip input
        cal.displayTrips();  // display output
    }
    else
    {
        // disconnected, just display the message
        std::cout << "Disconnected Map" << std::endl;
    }

    return 0;
}

