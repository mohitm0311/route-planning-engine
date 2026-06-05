#ifndef BENCHMARK_H
#define BENCHMARK_H

#include "../include/Graph.h"

#include "BenchmarkResult.h"

#include <vector>

class Benchmark
{
public:

    std::vector<BenchmarkResult>
    runRandomBenchmarks(
        const Graph& graph,
        int benchmarkCount
    );

    void exportToCSV(
    const std::vector<BenchmarkResult>& results,
    const std::string& fileName
);
};

#endif