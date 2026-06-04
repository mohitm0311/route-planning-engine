#ifndef EDGE_H
#define EDGE_H

struct Edge
{
    long long to;

    double distance;

    double travelTime;

    Edge()
    {
        to = 0;
        distance = 0.0;
        travelTime = 0.0;
    }

    Edge(long long destination, double dist, double time)
    {
        to = destination;
        distance = dist;
        travelTime = time;
    }
};

#endif