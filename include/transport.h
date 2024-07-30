#ifndef TRANSPORT_H
#define TRANSPORT_H
#include <iostream>
#include <vector>
#include "path.h"

class Transport{
private:
    std::string name; 
    bool type; // True = Terrestre e False = aquatico
    int capacity;
    int speed;
    int rest; // distancia entre descansos 
    double timerest;
    bool available(); 
public:
    Transport(std::string name, bool type, int capacity, int speed, int rest, double timerest);
    std::string getName();
    bool getType();
    int getCapacity();
    int getSpeed();
    int getRest();
    double getTimerest();
    bool isAvailable();
    
    

};



#endif