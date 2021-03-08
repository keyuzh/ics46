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
    cal.readRoadMap();
    // now read and calculate trips
    cal.readTrips();
    cal.displayTrips();
   

    return 0;
}

