#include <iostream>
#include "include/Graph.h"

int main()
{
    Graph graph;
    graph.addNode(1, 28.6139, 77.2090);
    graph.addNode(2, 28.6145, 77.2101);

    graph.addEdge(1, 2, 500, 60);

    std::cout << "Number of Nodes: "
              << graph.getNodes().size()
              << "\n";

    std::cout << "Number of Adjacency Entries: "
              << graph.getAdjList().size()
              << "\n";

    return 0;
}
