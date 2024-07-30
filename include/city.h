#ifndef CITY_H
#define CITY_H
#include <iostream>
#include <vector>
#include "path.h"




class City{
private:
    std::string name;
    std::vector<Path*> paths;

public:
    City(const std::string &name) : name(name) {}
    std::string getName();
    void cityRegister();
    void addPath();
    std::vector<Path*> getPaths();

};


#endif