#ifndef OSM_PARSER_H
#define OSM_PARSER_H

#include <string>

#include "Graph.h"

class OSMParser
{
public:

    bool parse(
        const std::string& filePath,
        Graph& graph
    );
};

#endif