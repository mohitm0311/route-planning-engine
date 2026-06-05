#ifndef ROUTE_VISUALIZER_H
#define ROUTE_VISUALIZER_H

#include <string>

#include "Graph.h"
#include "Route.h"

class RouteVisualizer
{
public:
    bool exportGeoJSON(
        const Route& route,
        const Graph& graph,
        const std::string& filePath
    );
};

#endif