#ifndef ROUTE_H
#define ROUTE_H

#include <vector>

struct Route
{
    std::vector<long long> path;
    double totalDistance;
    double totalTravelTime;
    long long nodesExplored;
    Route()
    {
        totalDistance = 0.0;
        totalTravelTime = 0.0;
        nodesExplored = 0;
    }
};

#endif