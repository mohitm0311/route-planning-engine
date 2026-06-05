#include <iostream>
#include <chrono>

#include "Graph.h"
#include "OSMParser.h"
#include "Dijkstra.h"
#include "AStar.h"

void printRoute(
    const std::string& algorithm,
    const Route& route,
    double runtime
)
{
    std::cout
        << "\n===== "
        << algorithm
        << " =====\n";

    std::cout
        << "Path Nodes: "
        << route.path.size()
        << "\n";

    std::cout
        << "Distance: "
        << route.totalDistance
        << " km\n";

    std::cout
        << "Travel Time: "
        << route.totalTravelTime
        << " hours\n";

    std::cout
        << "Nodes Explored: "
        << route.nodesExplored
        << "\n";

    std::cout
        << "Runtime(ms): "
        << runtime
        << "\n";

    if(!route.path.empty())
    {
        std::cout
            << "Path:\n";

        for(long long node : route.path)
        {
            std::cout
                << node
                << " ";
        }

        std::cout
            << "\n";
    }
}

int main()
{
    Graph graph;

    OSMParser parser;

    if(
        !parser.parse(
            "data/raw/iit_delhi.osm",
            graph
        )
    )
    {
        std::cout
            << "Failed to load OSM file\n";

        return 0;
    }

    std::cout
        << "\nOSM file loaded successfully\n";

    std::cout
        << "Graph Nodes: "
        << graph.getNodes().size()
        << "\n";

    long long totalEdges = 0;

    for(const auto& pair :
        graph.getAdjList())
    {
        totalEdges +=
            pair.second.size();
    }

    std::cout
        << "Graph Edges: "
        << totalEdges
        << "\n";

    long long source =
        4233527048;

    long long destination =
        4233527054;

    std::cout
        << "\nSource: "
        << source
        << "\n";

    std::cout
        << "Destination: "
        << destination
        << "\n";

    Dijkstra dijkstra(graph);

    auto start1 =
        std::chrono::high_resolution_clock::now();

    Route dijkstraRoute =
        dijkstra.shortestPath(
            source,
            destination,
            DISTANCE
        );

    auto end1 =
        std::chrono::high_resolution_clock::now();

    double dijkstraTime =
        std::chrono::duration<double,
        std::milli>(
            end1 - start1
        ).count();

    printRoute(
        "Dijkstra",
        dijkstraRoute,
        dijkstraTime
    );

    AStar astar(graph);

    auto start2 =
        std::chrono::high_resolution_clock::now();

    Route astarRoute =
        astar.shortestPath(
            source,
            destination,
            DISTANCE
        );

    auto end2 =
        std::chrono::high_resolution_clock::now();

    double astarTime =
        std::chrono::duration<double,
        std::milli>(
            end2 - start2
        ).count();

    printRoute(
        "A*",
        astarRoute,
        astarTime
    );

    return 0;
}