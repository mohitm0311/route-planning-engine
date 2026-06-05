#include <iostream>

#include "Graph.h"
#include "OSMParser.h"
#include "Dijkstra.h"
#include "NearestNodeFinder.h"
#include "RouteVisualizer.h"

int main()
{
    Graph graph;

    OSMParser parser;

    if(
        !parser.parse(
            "data/raw/hauz_khas.osm",
            graph
        )
    )
    {
        std::cout
            << "Failed to load OSM file\n";

        return 0;
    }

    std::cout
        << "\n========== ROUTE PLANNING ENGINE ==========\n";

    std::cout
        << "OSM file loaded successfully\n";

    std::cout
        << "Graph Nodes: "
        << graph.getNodes().size()
        << "\n";

    long long totalEdges = 0;

    for(const auto& pair :
        graph.getAdjList())
    {
        totalEdges += pair.second.size();
    }

    std::cout
        << "Graph Edges: "
        << totalEdges
        << "\n";

    std::cout
        << "\nMap Bounds:\n";

    std::cout
        << "Latitude  : 28.54095 -> 28.56707\n";

    std::cout
        << "Longitude : 77.19659 -> 77.22831\n";

    double sourceLatitude;
    double sourceLongitude;

    double destinationLatitude;
    double destinationLongitude;

    std::cout
        << "\nEnter Source Latitude: ";

    std::cin
        >> sourceLatitude;

    std::cout
        << "Enter Source Longitude: ";

    std::cin
        >> sourceLongitude;

    std::cout
        << "Enter Destination Latitude: ";

    std::cin
        >> destinationLatitude;

    std::cout
        << "Enter Destination Longitude: ";

    std::cin
        >> destinationLongitude;

    const double MIN_LAT = 28.54095;
    const double MAX_LAT = 28.56707;

    const double MIN_LON = 77.19659;
    const double MAX_LON = 77.22831;

    if(
        sourceLatitude < MIN_LAT ||
        sourceLatitude > MAX_LAT ||
        sourceLongitude < MIN_LON ||
        sourceLongitude > MAX_LON
    )
    {
        std::cout
            << "\nSource coordinates are outside map bounds.\n";

        return 0;
    }

    if(
        destinationLatitude < MIN_LAT ||
        destinationLatitude > MAX_LAT ||
        destinationLongitude < MIN_LON ||
        destinationLongitude > MAX_LON
    )
    {
        std::cout
            << "\nDestination coordinates are outside map bounds.\n";

        return 0;
    }

    NearestNodeFinder finder;

    long long source =
        finder.findNearestNode(
            graph,
            sourceLatitude,
            sourceLongitude
        );

    long long destination =
        finder.findNearestNode(
            graph,
            destinationLatitude,
            destinationLongitude
        );

    std::cout
        << "\nNearest Source Node: "
        << source
        << "\n";

    std::cout
        << "Nearest Destination Node: "
        << destination
        << "\n";

    Dijkstra dijkstra(graph);

    Route route =
        dijkstra.shortestPath(
            source,
            destination,
            DISTANCE
        );

    if(route.path.empty())
    {
        std::cout
            << "\nNo route found.\n";

        return 0;
    }

    std::cout
        << "\n========== ROUTE FOUND ==========\n";

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

    RouteVisualizer visualizer;

    bool exported =
        visualizer.exportGeoJSON(
            route,
            graph,
            "visualization/route.geojson"
        );

    if(!exported)
    {
        std::cout
            << "\nFailed to export route.\n";

        return 0;
    }

    std::cout
        << "\nRoute exported successfully.\n";

    std::cout
        << "Generated File:\n";

    std::cout
        << "visualization/route.geojson\n";

    std::cout
        << "\nNext Step:\n";

    std::cout
        << "python visualization/visualize.py\n";

    std::cout
        << "\nThen open:\n";

    std::cout
        << "visualization/route.html\n";

    return 0;
}