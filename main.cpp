#include <iostream>

#include "Graph.h"
#include "OSMParser.h"

int main()
{
    Graph graph;

    OSMParser parser;

    bool loaded =
        parser.parse(
            "data/raw/test.osm",
            graph
        );

    if(!loaded)
    {
        std::cout
            << "Failed to load OSM file\n";

        return 0;
    }

    std::cout
        << "OSM file loaded successfully\n";

    std::cout
        << "Graph Nodes: "
        << graph.getNodes().size()
        << "\n";

    std::cout
        << "Graph Vertices With Edges: "
        << graph.getAdjList().size()
        << "\n";

    for(const auto& nodePair : graph.getNodes())
    {
        const Node& node = nodePair.second;

        std::cout
            << "Node ID: "
            << node.id
            << " ("
            << node.latitude
            << ", "
            << node.longitude
            << ")\n";
    }

    return 0;
}