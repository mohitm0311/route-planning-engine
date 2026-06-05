#include <iostream>

#include "Graph.h"
#include "Dijkstra.h"
#include "RouteMode.h"

int main()
{
    Graph graph;

    graph.addNode(1, 0, 0);
    graph.addNode(2, 0, 0);
    graph.addNode(3, 0, 0);
    graph.addNode(4, 0, 0);

    graph.addEdge(1, 2, 4, 4);

    graph.addEdge(1, 3, 1, 1);

    graph.addEdge(3, 2, 2, 2);

    graph.addEdge(2, 4, 1, 1);

    graph.addEdge(3, 4, 5, 5);

    Dijkstra dijkstra(graph);

    Route route =
        dijkstra.shortestPath(
            1,
            4,
            DISTANCE
        );

    std::cout << "Shortest Path: ";

    for(long long node : route.path)
    {
        std::cout << node << " ";
    }

    std::cout << "\n";

    std::cout << "Total Distance: "
              << route.totalDistance
              << "\n";

    return 0;
}