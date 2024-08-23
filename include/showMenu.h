#ifndef SHOW_MENU_H
#define SHOW_MENU_H

#include <iostream>
#include <string>
#include <algorithm>
#include <limits> 
#include "TravelRegister.h"
#include "TravelAgency.h"

void showMenu(); 
int readOption(); 
std::string readString(const std::string& message); 
int readInt(const std::string& message); 
void clearScreen(); 
void pauseScreen();

void handleListOngoingTrips(DatabaseManager& dbManager);
void handleListMostVisitedCities(DatabaseManager& dbManager);
void handleAdvanceTime(TravelAgency& travelAgency);
void handleAddCity(TravelRegister& travelRegister);
void handleAddTransport(TravelRegister& travelRegister);
void handleAddPassenger(TravelRegister& travelRegister);
void handleAddPath(TravelRegister& travelRegister);
void handleListCities(const TravelRegister& travelRegister);
void handleListTransports(const DatabaseManager& dbManager);
void handleListPassengers(const DatabaseManager& dbManager);
void handleStartJourney(TravelRegister& travelRegister, TravelAgency& travelAgency);

#endif
