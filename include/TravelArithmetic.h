#ifndef TRAVELARITHMETIC_H
#define TRAVELARITHMETIC_H

#include <string>
#include <vector>
#include <map>
#include <set>
#include "city.h"
#include "transport.h"
#include "passenger.h"
#include "path.h"
#include "DatabaseManager.h"

class TravelArithmetic {
public:
    TravelArithmetic();

    double totalTravelTime(double distance, int speed, int distRest, int timeRest) const;
    std::vector<City*> calculateShortestPath(const City& origin, const City& destination, const std::vector<City>& cities);
};

#endif // TRAVELARITHMETIC_H
