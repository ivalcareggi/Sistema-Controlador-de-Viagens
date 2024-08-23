#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <string>
#include <vector>
#include <sqlite3.h>
#include "city.h"
#include "transport.h"
#include "path.h"


class DatabaseManager {
public:
    DatabaseManager(const std::string& dbName);
    ~DatabaseManager();

    // Métodos de salvamento
    void saveCity(const std::string& cityName);
    void savePath(const std::string& origin, const std::string& destination, double distance);
    void saveTransport(const std::string& transportName, int capacity, bool type, int cityId);
    void savePassenger(const std::string& passengerName, const std::string& location); // continuar amanha
    int  saveTravel(int transportId, int originCityId, int destinationCityId, const std::string& timestamp);
    void updateTravelEndTime(int travelId, const std::string& endTime);
    void updatePassengerLocation(const std::string& name, int id);
    void updateTransportLocation(int transportId, int cityId);
    void updateTripStatus(int travelId, const std::string& status);

    // Métodos de listagem
    void listCities() const;
    void listTransports() const;
    void listPassengers() const;
    void listPaths() const;

    // Métodos de consulta
    City* findCityByName(const std::string& cityName);
    std::vector<std::string> getAllCityNames();
    std::vector<City> getAllCities(); 
    std::vector<Transport> getAllTransports(); 
    Transport getTransportByName(const std::string& name) const;
    Path getPath(const City& origin, const City& destination); 
   // double getPathDistance(int originCityId, int destinationCityId); 
    double getPathDistance(const std::string& originCityName, const std::string& destinationCityName);
    int getTransportId(const std::string& transportName); 
    int getCityId(const std::string& cityName) const;
    std::string getPassengerName(const std::string& passengerName);
    int getPassengerCityId(const std::string& passengerName) const; // verificar
    City* findCityById(int cityId) const; //verificar
    std::string getCityName(int cityId) const;
    int getTransportCityId(int transportId);
    void logTrip(int travelId, const std::string& originCity, const std::string& destinationCity, const std::string& passengers, const std::string& tripStatus); // verificar
    void listOngoingTrips(); // verificar
    void listMostVisitedCities(); // verificar

private:
    sqlite3* db;

    void executeSQL(const std::string& sql);
    void createTables();
    void createTable(const std::string& createTableSQL);
};

#endif // DATABASEMANAGER_H