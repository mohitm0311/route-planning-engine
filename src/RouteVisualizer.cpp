#include "../include/RouteVisualizer.h"

#include <fstream>

bool RouteVisualizer::exportGeoJSON(
    const Route& route,
    const Graph& graph,
    const std::string& filePath
)
{
    std::ofstream file(filePath);

    if(!file.is_open())
    {
        return false;
    }

    file
        << "{\n"
        << "\"type\": \"FeatureCollection\",\n"
        << "\"features\": [\n"
        << "{\n"
        << "\"type\": \"Feature\",\n"
        << "\"geometry\": {\n"
        << "\"type\": \"LineString\",\n"
        << "\"coordinates\": [\n";

    for(
        size_t i = 0;
        i < route.path.size();
        i++
    )
    {
        const Node* node =
            graph.getNode(
                route.path[i]
            );

        if(node == nullptr)
        {
            continue;
        }

        file
            << "["
            << node->longitude
            << ", "
            << node->latitude
            << "]";

        if(i + 1 < route.path.size())
        {
            file << ",";
        }

        file << "\n";
    }

    file
        << "]\n"
        << "}\n"
        << "}\n"
        << "]\n"
        << "}\n";

    file.close();

    return true;
}