#include <iostream>

#include "Graph.h"
#include "Dijkstra.h"
#include "AStar.h"
#include "RouteMode.h"

void printRoute(const Route& route)
{
    std::cout << "Path: ";

    for(long long node : route.path)
    {
        std::cout << node << " ";
    }

    std::cout << "\n";

    std::cout << "Total Distance: "
              << route.totalDistance
              << "\n";

    std::cout << "Total Travel Time: "
              << route.totalTravelTime
              << "\n";
}

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

    AStar astar(graph);

    std::cout << "===== Dijkstra =====\n";

    Route dijkstraRoute =
        dijkstra.shortestPath(
            1,
            4,
            DISTANCE
        );

    printRoute(dijkstraRoute);

    std::cout << "\n";

    std::cout << "===== A* =====\n";

    Route astarRoute =
        astar.shortestPath(
            1,
            4,
            DISTANCE
        );

    printRoute(astarRoute);

    return 0;
}