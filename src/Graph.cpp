#include "../include/Graph.h"

void Graph::addNode(long long id,double latitude,double longitude){
    nodes[id] = Node(id, latitude, longitude);
}

void Graph::addEdge(long long from,long long to, double distance, double travelTime)
{
    Edge edge(to, distance, travelTime);
    adj[from].push_back(edge);
}

const std::unordered_map<long long, Node>& Graph::getNodes() const
{
    return nodes;
}

const std::unordered_map<long long, std::vector<Edge>>& Graph::getAdjList() const
{
    return adj;
}