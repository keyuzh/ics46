// TripCalculator.hpp
//
// ICS 46 Winter 2021
// Project #5: Rock and Roll Stops the Traffic
//
// A TripReader reads a sequence of trips from the given input, assuming
// they're written in the format described in the project write-up.

#ifndef TRIPCALCULATOR_HPP
#define TRIPCALCULATOR_HPP

#include <iostream>
#include <map>
#include <list>

#include "InputReader.hpp"
#include "RoadMap.hpp"
#include "RoadMapReader.hpp"
#include "RoadMapWriter.hpp"
#include "TripReader.hpp"


class TripCalculator
{
private:
    InputReader inputReader;
    RoadMapReader roadMapReader;
    RoadMap roadMap;
    RoadMapWriter writer;
    TripReader tripReader;

    std::vector<Trip> trips;

    bool DEBUG;

public:
    TripCalculator(std::istream& in);
    // ~TripCalculator();

    void readRoadMap();
    void readTrips();
    void displayTrips();

private:
    std::list<int> shortestTrip(int start, int end, const TripMetric& type) const;
    void displayRoute(const std::list<int>& route, const TripMetric& type) const;
    void displayFirstLine(const std::list<int>& route, const TripMetric& type) const;
    void displayFinalLine(double total, const TripMetric& type) const;
    std::string displayContinueLine(int prev, int current, double& total, const TripMetric& type) const;
};


#endif // TRIPREADER_HPP

