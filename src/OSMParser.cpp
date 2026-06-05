#include "../include/OSMParser.h"

#include "../external/tinyxml2/tinyxml2.h"

#include "../include/Utils.h"

#include <iostream>
#include <vector>
#include <string>

using namespace tinyxml2;

bool OSMParser::parse(
    const std::string& filePath,
    Graph& graph
)
{
    XMLDocument document;

    if(document.LoadFile(filePath.c_str()) != XML_SUCCESS)
    {
        return false;
    }

    XMLElement* root =
        document.FirstChildElement("osm");

    if(root == nullptr)
    {
        return false;
    }

    long long nodeCount = 0;

    for(
        XMLElement* nodeElement =
            root->FirstChildElement("node");
        nodeElement != nullptr;
        nodeElement =
            nodeElement->NextSiblingElement("node")
    )
    {
        long long id =
            nodeElement->Int64Attribute("id");

        double latitude =
            nodeElement->DoubleAttribute("lat");

        double longitude =
            nodeElement->DoubleAttribute("lon");

        graph.addNode(
            id,
            latitude,
            longitude
        );

        nodeCount++;
    }

    long long edgeCount = 0;

    for(
        XMLElement* wayElement =
            root->FirstChildElement("way");
        wayElement != nullptr;
        wayElement =
            wayElement->NextSiblingElement("way")
    )
    {
        bool isRoad = false;

        for(
            XMLElement* tagElement =
                wayElement->FirstChildElement("tag");
            tagElement != nullptr;
            tagElement =
                tagElement->NextSiblingElement("tag")
        )
        {
            const char* key =
                tagElement->Attribute("k");

            if(
                key != nullptr &&
                std::string(key) == "highway"
            )
            {
                isRoad = true;
                break;
            }
        }

        if(!isRoad)
        {
            continue;
        }

        std::vector<long long> wayNodes;

        for(
            XMLElement* ndElement =
                wayElement->FirstChildElement("nd");
            ndElement != nullptr;
            ndElement =
                ndElement->NextSiblingElement("nd")
        )
        {
            long long nodeId =
                ndElement->Int64Attribute("ref");

            wayNodes.push_back(nodeId);
        }

        for(
            size_t i = 0;
            i + 1 < wayNodes.size();
            i++
        )
        {
            const Node* from =
                graph.getNode(
                    wayNodes[i]
                );

            const Node* to =
                graph.getNode(
                    wayNodes[i + 1]
                );

            if(
                from == nullptr ||
                to == nullptr
            )
            {
                continue;
            }

            double distance =
                haversineDistance(
                    from->latitude,
                    from->longitude,
                    to->latitude,
                    to->longitude
                );

            double travelTime =
                distance / 40.0;

            graph.addEdge(
                wayNodes[i],
                wayNodes[i + 1],
                distance,
                travelTime
            );

            edgeCount++;
        }
    }

    std::cout
        << "Nodes Loaded: "
        << nodeCount
        << "\n";

    std::cout
        << "Edges Loaded: "
        << edgeCount
        << "\n";

    return true;
}