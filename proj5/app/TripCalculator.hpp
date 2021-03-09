// TripCalculator.hpp
// ICS46 Winter 2021 Project 5
// Name: Keyu Zhang
// ID: 19898090
// UCINetID: keyuz4

#ifndef TRIPCALCULATOR_HPP
#define TRIPCALCULATOR_HPP

#include <istream>
#include <list>
#include <string>
#include <vector>

#include "InputReader.hpp"
#include "RoadMap.hpp"
#include "RoadMapReader.hpp"
#include "RoadMapWriter.hpp"
#include "TripReader.hpp"


class TripCalculator
{
public:
    // constructor, need a input source
    TripCalculator(std::istream& in);
    // public function to read input
    void readRoadMap();
    void readTrips();
    // public function to display output
    void displayTrips();
    // check if the roadmap is strongly connected
    bool isConnected() const;

private:
    // provided input reader classes
    InputReader inputReader;
    RoadMapReader roadMapReader;
    TripReader tripReader;
    // roadmap (digraph) class
    RoadMap roadMap;
    // vector to store the trips read from input
    std::vector<Trip> trips;

private:
    // call findShortestPaths() in digraph class to find the shortest trip
    // between the given vertices, return a list of vertices along the route
    std::list<int> shortestTrip(int start, int end, const TripMetric& type) const;
    // write one route to std::cout
    void displayRoute(const std::list<int>& route, const TripMetric& type) const;
    // helper functions for displayRoute()
    void displayFirstLine(const std::list<int>& route, const TripMetric& type) const;
    void displayFinalLine(double total, const TripMetric& type) const;
    std::string displayContinueLine(
        int prev, int current, double& total, const TripMetric& type) const;
};


#endif // TRIPCALCULATOR_HPP
