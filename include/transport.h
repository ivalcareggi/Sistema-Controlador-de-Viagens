#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <string>
#include <vector>
#include "passenger.h"

class Transport {
private:
    std::string name;
    bool type;                    // Tipo do transporte (terrestre = True ou aquático = False)
    int capacity;
    int speed;
    int distRest;
    int timeRest;
    bool available = true;
    std::vector<Passenger> passengers; // Passageiros no transporte
    City* currentLocation;
public:
    Transport();  // Construtor padrão
    Transport(const std::string& name, bool type, int capacity, int speed, int distRest, int timeRest);

    const std::string& getName() const;
    bool getType() const;
    int getCapacity() const;
    int getSpeed() const;
    int getDistRest() const;
    int getTimerest() const;
    bool isAvailable() const;
    City* getCurrentLocation()const;
    void setName(const std::string& name);
    void setType(bool type);
    void setCapacity(int capacity);
    void setSpeed(int speed);
    void setDistRest(int distRest);
    void setTimerest(int timeRest);
    void setAvailable(bool available);
    void setCurrentLocation(City* location);
    void addPassenger(const Passenger& passenger);
    void removePassenger(const Passenger& passenger);
};

#endif // TRANSPORT_H
