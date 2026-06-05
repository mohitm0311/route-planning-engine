#include <iostream>

#include "Utils.h"

int main()
{
    double distance =
        haversineDistance(
            28.5458,
            77.1926,
            28.6315,
            77.2167
        );

    std::cout << distance << "\n";

    return 0;
}