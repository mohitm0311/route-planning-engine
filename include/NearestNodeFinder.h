#ifndef NEAREST_NODE_FINDER_H
#define NEAREST_NODE_FINDER_H

#include "Graph.h"

class NearestNodeFinder
{
public:

    long long findNearestNode(
        const Graph& graph,
        double latitude,
        double longitude
    ) const;
};

#endif