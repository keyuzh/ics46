// TripCalculator.cpp
// ICS46 Winter 2021 Project 5
// Name: Keyu Zhang
// ID: 19898090
// UCINetID: keyuz4

#include "TripCalculator.hpp"

#include <cmath>
#include <iomanip>
#include <map>
#include <sstream>
#include <string>

namespace
{
    double weightByDist(const RoadSegment& segment)
    {
        return segment.miles;
    }

    double weightByTime(const RoadSegment& segment)
    {
        return (segment.miles / segment.milesPerHour);
    }

    std::string convertTime(double t)
    {
        std::stringstream result;
        result << std::fixed << std::setprecision(1);
        // calculate hr, min, sec
        double second = std::fmod(t, 60.0);
        int minute = t / 60.0;
        int hour = minute / 60;
        // value over 60 is converted to hours
        minute = minute % 60;
        // feed into string stream
        if (hour != 0)
        {
            result << hour << " hrs " << minute << " mins " << second << " secs";
        }
        else if (minute != 0)
        {
            result << minute << " mins " << second << " secs";
        }
        else
        {
            result << second << " secs";
        }
        // convert back to string
        return result.str();
    }
}

TripCalculator::TripCalculator(std::istream& in)
    : inputReader{in}
{   
}

void TripCalculator::readRoadMap()
{
    roadMap = roadMapReader.readRoadMap(inputReader);
}

void TripCalculator::readTrips()
{
    trips = tripReader.readTrips(inputReader);
}

void TripCalculator::displayTrips()
{
    for (auto& trip : trips)
    {
        const std::list<int>& route = shortestTrip(trip.startVertex, trip.endVertex, trip.metric);
        displayRoute(route, trip.metric);
        std::cout << std::endl;
    }
}

bool TripCalculator::isConnected() const
{
    return roadMap.isStronglyConnected();
}


std::list<int> TripCalculator::shortestTrip(int start, int end, const TripMetric& type) const
{
    std::map<int, int> paths;
    switch (type)
    {
    case TripMetric::Distance:
        // shortest distance
        paths = roadMap.findShortestPaths(start, weightByDist);
        break;
    case TripMetric::Time:
        // shortest time
        paths = roadMap.findShortestPaths(start, weightByTime);
        break;
    }
    std::list<int> route;
    int current = end;
    // push the final vertex
    route.push_front(current);
    // backtrace from end, push to front of list
    while (current != start)
    {
        current = paths[current];
        route.push_front(current);
    }
    return route;
}

void TripCalculator::displayRoute(const std::list<int>& route, const TripMetric& type) const
{
    // print first line
    displayFirstLine(route, type);
    double total{0};
    int prev;
    // print each line of trip
    for (auto i = route.begin(); i != route.end(); i++)
    {
        int current = *i;
        const std::string& info = roadMap.vertexInfo(current);
        if (i == route.begin())
        {
            // starting location
            std::cout << "  Begin at " << info << std::endl;
        }
        else
        {
            std::cout << "  Continue to " << info << displayContinueLine(prev, current, total, type) << std::endl;
        }
        // save the previous vertex to calculate distance and time
        prev = *i;
    }
    // print total
    displayFinalLine(total, type);
}

void TripCalculator::displayFirstLine(const std::list<int>& route, const TripMetric& type) const
{
    // name of starting and ending vertex
    const std::string& startInfo = roadMap.vertexInfo(route.front());
    const std::string& endInfo = roadMap.vertexInfo(route.back());
    switch (type)
    {
    case TripMetric::Distance:
        // shortest distance
        std::cout << "Shortest distance from " << startInfo << " to " << endInfo << std::endl;
        break;
    case TripMetric::Time:
        // shortest time
        std::cout << "Shortest driving time from " << startInfo << " to " << endInfo << std::endl;
        break;
    }
}

void TripCalculator::displayFinalLine(double total, const TripMetric& type) const
{
    // set precision to one decimal place
    std::cout << std::fixed << std::setprecision(1);
    switch (type)
    {
    case TripMetric::Distance:
        // shortest distance
        std::cout << "Total distance: " << total << " miles" << std::endl;
        break;
    case TripMetric::Time:
        // shortest time
        std::cout << "Total time: " << convertTime(total) << std::endl;
        break;
    }
}

std::string TripCalculator::displayContinueLine(int prev, int current, double& total, const TripMetric& type) const
{
    // set precision to one decimal place
    std::stringstream result;
    result << std::fixed << std::setprecision(1);
    // get the edge
    RoadSegment segment = roadMap.edgeInfo(prev, current);
    double distance = segment.miles;
    result << " (" << distance << " miles";
    if (type == TripMetric::Time)
    {
        // calculate time
        double speed = segment.milesPerHour;
        double travelTime = (distance / speed) * 3600.0;  // time in seconds
        result << " @ " << segment.milesPerHour << "mph = " << convertTime(travelTime);
        // increment total
        total += travelTime;
    }
    else
    {
        // for distance, just add to total
        total += distance;
    }
    result << ")";  // add closing )
    return result.str();
}
