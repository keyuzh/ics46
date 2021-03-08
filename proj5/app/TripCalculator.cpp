
#include "TripCalculator.hpp"
#include <iomanip>
#include <string>
#include <cmath>
#include <sstream>

namespace
{
    double weightByDist(const RoadSegment& segment)
    {
        return segment.miles;
    }

    double weightByTime(const RoadSegment& segment)
    {
        return (double(segment.miles) / double(segment.milesPerHour)) * 3600;
    }

    std::string convertTime(double t)
    {
        std::stringstream result;
        result << std::fixed << std::setprecision(1);
        // hr, min, sec
        double second = fmod(t, 60.0);
        int minute = t / 60.0;
        int hour = minute / 60;
        minute = minute % 60;
        if (hour != 0)
        {
            result << hour << " hrs ";
            result << minute << " mins ";
            result << second << " secs";
        }
        else if (minute != 0)
        {
            result << minute << " mins ";
            result << second << " secs";
        }
        else
        {
            result << second << " secs";
        }
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
    DEBUG = true;
    if (DEBUG)
    {
        writer.writeRoadMap(std::cout, roadMap);
        std::cout << std::endl << std::endl;
    }
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


std::list<int> TripCalculator::shortestTrip(int start, int end, const TripMetric& type) const
{
    std::cout << start<< std::endl;
    std::map<int, int> paths;
    switch (type)
    {
    case TripMetric::Distance:
        // shortest distance
        std::cout << "Distance" << std::endl;
        paths = roadMap.findShortestPaths(start, weightByDist);
        break;
    case TripMetric::Time:
        std::cout << "time" << std::endl;
        // shortest time
        // paths = roadMap.findShortestPaths(start, [](RoadSegment seg){return seg.miles / seg.milesPerHour;});
        paths = roadMap.findShortestPaths(start, weightByTime);
        break;
    }
    
    for (auto& i : paths)
    {
        std::cout << i.second << "->" << i.first << std::endl;
    }
    
    
    // backtrace from end
    std::list<int> route;
    int current = end;
    // push the final vertex
    route.push_front(current);
    while (current != start)
    {
        std::cout << current << " ";
        current = paths[current];
        route.push_front(current);
    }
    std::cout << std::endl;
    return route;
}

void TripCalculator::displayRoute(const std::list<int>& route, const TripMetric& type) const
{
    std::setprecision(1);
    displayFirstLine(route, type);
    double total{0};
    int prev;
    for (auto i = route.begin(); i != route.end(); i++)
    {
        int current = *i;
        const std::string& info = roadMap.vertexInfo(current);
        if (i == route.begin())
        {
            std::cout << "  Begin at " << info << std::endl;
        }
        else
        {
            std::cout << "  Continue to " << info << displayContinueLine(prev, current, total, type) << std::endl;
        }
        prev = *i;
    }
    displayFinalLine(total, type);
}

void TripCalculator::displayFirstLine(const std::list<int>& route, const TripMetric& type) const
{
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
    std::stringstream result;
    result << std::fixed << std::setprecision(1);
    RoadSegment segment = roadMap.edgeInfo(prev, current);
    double distance = segment.miles;
    result << " (" << distance << " miles";
    if (type == TripMetric::Time)
    {
        double speed = segment.milesPerHour;
        double travelTime = (distance / speed) * 3600.0;
        result << " @ " << segment.milesPerHour << "mph = " << convertTime(travelTime);
        total += travelTime;
    }
    else
    {
        total += distance;
    }
    result << ")";
    return result.str();
}
