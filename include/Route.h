#ifndef ROUTE_H
#define ROUTE_H

#include <vector>

struct Route
{
    std::vector<long long> path;
    double totalDistance;
    double totalTravelTime;

    Route()
    {
        totalDistance = 0.0;
        totalTravelTime = 0.0;
    }
};

#endif