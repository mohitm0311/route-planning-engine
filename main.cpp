#include <iostream>
#include <chrono>

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

    std::cout << "Nodes Explored: "
              << route.nodesExplored
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

    std::cout << "========== Dijkstra ==========\n";

    auto dijkstraStart =
        std::chrono::high_resolution_clock::now();

    Route dijkstraRoute =
        dijkstra.shortestPath(
            1,
            4,
            DISTANCE
        );

    auto dijkstraEnd =
        std::chrono::high_resolution_clock::now();

    double dijkstraTime =
        std::chrono::duration<double, std::milli>(
            dijkstraEnd - dijkstraStart
        ).count();

    printRoute(dijkstraRoute);

    std::cout << "Runtime (ms): "
              << dijkstraTime
              << "\n\n";

    std::cout << "========== A* ==========\n";

    auto astarStart =
        std::chrono::high_resolution_clock::now();

    Route astarRoute =
        astar.shortestPath(
            1,
            4,
            DISTANCE
        );

    auto astarEnd =
        std::chrono::high_resolution_clock::now();

    double astarTime =
        std::chrono::duration<double, std::milli>(
            astarEnd - astarStart
        ).count();

    printRoute(astarRoute);

    std::cout << "Runtime (ms): "
              << astarTime
              << "\n";

    return 0;
}