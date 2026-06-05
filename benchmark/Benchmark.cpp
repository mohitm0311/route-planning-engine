#include "Benchmark.h"

#include "../include/Dijkstra.h"
#include "../include/AStar.h"
#include "../include/RouteMode.h"

#include <chrono>
#include <random>
#include <fstream>

std::vector<BenchmarkResult>
Benchmark::runRandomBenchmarks(
    const Graph& graph,
    int benchmarkCount
)
{
    std::vector<BenchmarkResult> results;

    std::vector<long long> nodes;

    for(const auto& pair :graph.getNodes()){
        nodes.push_back(
            pair.first
        );
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<>
    distribution(0,static_cast<int>(nodes.size() - 1));

    Dijkstra dijkstra(graph);

    AStar astar(graph);
    while(
        static_cast<int>(
            results.size()
        ) < benchmarkCount
    )
    {
        long long source =
            nodes[
                distribution(gen)
            ];
        long long destination =
            nodes[
                distribution(gen)
            ];
        if(source == destination)
        {
            continue;
        }
        auto dijkstraStart =
            std::chrono::
            high_resolution_clock::now();
        Route dijkstraRoute =
            dijkstra.shortestPath(
                source,
                destination,
                DISTANCE
            );
        auto dijkstraEnd =
            std::chrono::
            high_resolution_clock::now();

        if(
            dijkstraRoute.path.size()
            < 50
        )
        {
            continue;
        }
        auto astarStart =
            std::chrono::
            high_resolution_clock::now();
        Route astarRoute =
            astar.shortestPath(
                source,
                destination,
                DISTANCE
            );
        auto astarEnd =
            std::chrono::
            high_resolution_clock::now();
        BenchmarkResult result;
        result.dijkstraRuntime =
            std::chrono::duration<
                double,
                std::milli
            >(
                dijkstraEnd -
                dijkstraStart
            ).count();

        result.astarRuntime =
            std::chrono::duration<
                double,
                std::milli
            >(
                astarEnd -
                astarStart
            ).count();

        result.dijkstraNodesExplored =
            dijkstraRoute
            .nodesExplored;

        result.astarNodesExplored =
            astarRoute
            .nodesExplored;

        result.routeDistance =
            dijkstraRoute
            .totalDistance;

        results.push_back(
            result
        );
    }

    return results;
}

void Benchmark::exportToCSV(
    const std::vector<BenchmarkResult>& results,
    const std::string& fileName
)
{
    std::ofstream file(fileName);

    if(!file.is_open())
    {
        return;
    }

    file
        << "Route,"
        << "Distance,"
        << "DijkstraRuntime,"
        << "AStarRuntime,"
        << "DijkstraNodes,"
        << "AStarNodes\n";

    for(size_t i = 0;
        i < results.size();
        i++)
    {
        file
            << i + 1
            << ","
            << results[i].routeDistance
            << ","
            << results[i].dijkstraRuntime
            << ","
            << results[i].astarRuntime
            << ","
            << results[i].dijkstraNodesExplored
            << ","
            << results[i].astarNodesExplored
            << "\n";
    }

    file.close();
}