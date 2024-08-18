#ifndef TRAVELARITHMETIC_H
#define TRAVELARITHMETIC_H

#include <string>
#include <vector>
#include <map>
#include <set>
#include "../include/city.h"
#include "../include/transport.h"
#include "../include/passenger.h"
#include "../include/path.h"
#include "../include/DatabaseManager.h"

class TravelArithmetic {
public:
    TravelArithmetic();

    double totalTravelTime(double distance, int speed, int distRest, int timeRest) const;
    std::vector<City*> calculateShortestPath(const City& origin, const City& destination, const std::vector<City>& cities);
};

#endif // TRAVELARITHMETIC_H
