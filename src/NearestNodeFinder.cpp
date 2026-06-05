#include "../include/NearestNodeFinder.h"

#include "../include/Utils.h"

#include <limits>

long long NearestNodeFinder::findNearestNode(
    const Graph& graph,
    double latitude,
    double longitude
) const
{
    double bestDistance =
        std::numeric_limits<double>::max();

    long long nearestNode = -1;

    for(const auto& pair : graph.getNodes())
    {
        const Node& node =
            pair.second;

        double distance =
            haversineDistance(
                latitude,
                longitude,
                node.latitude,
                node.longitude
            );

        if(distance < bestDistance)
        {
            bestDistance = distance;
            nearestNode = node.id;
        }
    }

    return nearestNode;
}