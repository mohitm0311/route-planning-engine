#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "Graph.h"
#include "Route.h"
#include "RouteMode.h"

class Dijkstra
{
private:
    const Graph& graph;

public:
    Dijkstra(const Graph& g);
    Route shortestPath(
        long long source,
        long long destination,
        RouteMode mode
    );
};

#endif