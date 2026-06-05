#include "../include/AStar.h"
#include "../include/Utils.h"

#include <unordered_map>
#include <queue>
#include <limits>
#include <algorithm>

double heuristic(
    const Graph& graph,
    long long current,
    long long destination
)
{
    const Node* currentNode =
        graph.getNode(current);

    const Node* destinationNode =
        graph.getNode(destination);

    if(currentNode == nullptr ||
       destinationNode == nullptr)
    {
        return 0.0;
    }
    return haversineDistance(
        currentNode->latitude,
        currentNode->longitude,
        destinationNode->latitude,
        destinationNode->longitude
    );
}

AStar::AStar(const Graph& g)
    : graph(g)
{
}
Route AStar::shortestPath(
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
    double startPriority =
        heuristic(
            graph,
            source,
            destination
        );

    pq.push({startPriority,source});
    const auto& adjList =graph.getAdjList();
    while(!pq.empty())
    {
        State current = pq.top();
        pq.pop();
        long long currentNode =current.second;
        if(currentNode == destination){
            break;
        }
        auto it = adjList.find(currentNode);
        if(it == adjList.end()){
            continue;
        }
        for(const Edge& edge : it->second){
            double weight;
            if(mode == DISTANCE)
            {
                weight = edge.distance;
            }
            else
            {
                weight = edge.travelTime;
            }
            double tentativeDistance =
                dist[currentNode] + weight;
            if(tentativeDistance < dist[edge.to])
            {
                dist[edge.to] =tentativeDistance;
                parent[edge.to] =currentNode;
                double priority =tentativeDistance +heuristic(graph,edge.to,destination);
                pq.push({priority,edge.to});
            }
        }
    }
    if(dist[destination] ==
       std::numeric_limits<double>::max())
    {
        return route;
    }
    std::vector<long long> path;
    long long current =
        destination;
    while(current != source)
    {
        path.push_back(current);
        auto it =parent.find(current);
        if(it == parent.end())
        {
            return Route();
        }
        current =it->second;
    }
    path.push_back(source);
    std::reverse(path.begin(),path.end());
    route.path = path;
    route.totalDistance = 0.0;
    route.totalTravelTime = 0.0;
    for(size_t i = 0;i + 1 < path.size();i++)
    {
        const Edge* edge =
            graph.getEdge(
                path[i],
                path[i + 1]
            );
        if(edge != nullptr)
        {
            route.totalDistance +=
                edge->distance;

            route.totalTravelTime +=
                edge->travelTime;
        }
    }
    return route;
}