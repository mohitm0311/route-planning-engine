#include "../include/Dijkstra.h"

#include <unordered_map>
#include <queue>
#include <limits>
#include <algorithm>

Dijkstra::Dijkstra(const Graph& g)
    : graph(g)
{
}

Route Dijkstra::shortestPath(
    long long source,
    long long destination,
    RouteMode mode
)
{
    Route route;
    std::unordered_map<long long, double> dist;
    std::unordered_map<long long, long long> parent;
    for(const auto& nodePair : graph.getNodes())
    {
        dist[nodePair.first] =
            std::numeric_limits<double>::max();
    }
    dist[source] = 0.0;
    using State = std::pair<double, long long>;
    std::priority_queue<
        State,
        std::vector<State>,
        std::greater<State>
    > pq;
    pq.push({0.0, source});
    const auto& adjList = graph.getAdjList();
    while(!pq.empty())
    {
        State current = pq.top();
        pq.pop();
        double currentDistance = current.first;
        long long currentNode = current.second;
        if(currentDistance > dist[currentNode])
        {
            continue;
        }
        auto it = adjList.find(currentNode);
        if(it == adjList.end())
        {
            continue;
        }
        for(const Edge& edge : it->second)
        {
            double weight;
            if(mode == DISTANCE)
            {
                weight = edge.distance;
            }
            else
            {
                weight = edge.travelTime;
            }
            double newDistance =
                currentDistance + weight;

            if(newDistance < dist[edge.to])
            {
                dist[edge.to] = newDistance;

                parent[edge.to] = currentNode;
                pq.push({newDistance,edge.to});
            }
        }
    }
    if(dist[destination] ==
       std::numeric_limits<double>::max())
    {
        return route;
    }
    std::vector<long long> path;
    long long current = destination;
    while(current != source){
        path.push_back(current);
        auto it = parent.find(current);
        if(it == parent.end())
        {
            return Route();
        }
        current = it->second;
    }
    path.push_back(source);
    std::reverse(
        path.begin(),
        path.end()
    );
    route.path = path;
    if(mode == DISTANCE)
    {
        route.totalDistance =
            dist[destination];
    }
    else
    {
        route.totalTravelTime =
            dist[destination];
    }
    return route;
}