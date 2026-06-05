#ifndef BENCHMARK_RESULT_H
#define BENCHMARK_RESULT_H

struct BenchmarkResult
{
    double dijkstraRuntime;
    double astarRuntime;

    long long dijkstraNodesExplored;
    long long astarNodesExplored;

    double routeDistance;
};

#endif