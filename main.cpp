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

    if(loaded)
    {
        std::cout
            << "OSM file loaded successfully\n";
    }
    else
    {
        std::cout
            << "Failed to load OSM file\n";
    }

    return 0;
}