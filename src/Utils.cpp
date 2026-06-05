#include "../include/Utils.h"

#include <cmath>

double haversineDistance(
    double lat1,
    double lon1,
    double lat2,
    double lon2
)
{
    const double earthRadiusKm = 6371.0;
    const double pi = std::acos(-1.0);
    const double toRadians = pi / 180.0;

    lat1 *= toRadians;
    lon1 *= toRadians;
    lat2 *= toRadians;
    lon2 *= toRadians;

    const double deltaLat = lat2 - lat1;
    const double deltaLon = lon2 - lon1;

    const double a =
        std::sin(deltaLat / 2.0) * std::sin(deltaLat / 2.0) +
        std::cos(lat1) * std::cos(lat2) *
            std::sin(deltaLon / 2.0) * std::sin(deltaLon / 2.0);

    const double c = 2.0 * std::atan2(std::sqrt(a), std::sqrt(1.0 - a));

    return earthRadiusKm * c;
}
