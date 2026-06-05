#ifndef ASTAR_H
#define ASTAR_H

#include "Graph.h"
#include "Route.h"
#include "RouteMode.h"

class AStar
{
private:

    const Graph& graph;

public:

    AStar(const Graph& g);

    Route shortestPath(
        long long source,
        long long destination,
        RouteMode mode
    );
};

#endif