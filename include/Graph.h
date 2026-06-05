#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <vector>

#include "Node.h"
#include "Edge.h"

class Graph
{
private:
    std::unordered_map<long long, Node> nodes;
    std::unordered_map<long long, std::vector<Edge>> adj;
public:
    void addNode(long long id, double latitude, double longitude);

    void addEdge(long long from, long long to, double distance, double travelTime);

    const std::unordered_map<long long, Node>& getNodes() const;

    const std::unordered_map<long long, std::vector<Edge>>& getAdjList() const;

    const Edge* getEdge(long long from,long long to) const;
};

#endif