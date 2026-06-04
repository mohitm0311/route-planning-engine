#ifndef NODE_H
#define NODE_H

struct Node
{
    long long id;
    double latitude;
    double longitude;
    Node()
    {
        id = 0;
        latitude = 0.0;
        longitude = 0.0;
    }
    Node(long long nodeId, double lat, double lon)
    {
        id = nodeId;
        latitude = lat;
        longitude = lon;
    }
};

#endif