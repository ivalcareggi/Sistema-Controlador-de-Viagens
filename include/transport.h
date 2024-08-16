#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <string>
#include <vector>
#include "passenger.h"
#include "city.h"

class Transport {
private:
    std::string name;
    bool type;                    // Tipo do transporte (terrestre = True ou aquático = False)
    int capacity;
    int occupancy;
    int speed;
    int distRest;
    int timeRest;
    bool available = true;
    bool inTransit = false;
    int id;
    std::vector<Passenger> passengers; // Passageiros no transporte
    City* currentLocation;
public:
    Transport(); 
    Transport(int id, const std::string& name, bool type, int capacity);
    Transport(const std::string& name, bool type, int capacity, int speed, int distRest, int timeRest);
    Transport(const std::string& name, bool type, int capacity);

    const std::string& getName() const;
    bool getType() const;
    int getCapacity() const;
    int getSpeed() const;
    int getDistRest() const;
    int getTimerest() const;
    int getCurrentOccupancy() const;
    bool isAvailable() const;
    bool isInTransit()const;
    City* getCurrentLocation() const;
    void setName(const std::string& name);
    void setType(bool type);
    void setCapacity(int capacity);
    void setSpeed(int speed);
    void setDistRest(int distRest);
    void setTimerest(int timeRest);
    void setAvailable(bool available);
    void setInTransit(bool inTransit);
    void setCurrentLocation(City* location);
    void addPassenger(const Passenger& passenger);
    void removePassenger(const Passenger& passenger);
};

#endif // TRANSPORT_H
