#include "../include/TravelArithmetic.h"
#include <iostream>
#include <stdexcept>
#include <limits>
#include <algorithm>
#include <vector>
#include <map>
#include <set>


TravelArithmetic::TravelArithmetic() {
    // Se necessário, adicione código de inicialização aqui
}

// Calcula o tempo total de viagem, considerando pausas
double TravelArithmetic::totalTravelTime(double distance, int speed, int distRest, int timeRest) const {
    if (speed <= 0) {
        throw std::invalid_argument("Velocidade deve ser positiva.");
    }
    double travelTime = distance / speed;
    double restTime = (distance / distRest) * timeRest;
    return travelTime + restTime;
}

// Calcula o caminho mais curto usando o algoritmo de Dijkstra
std::vector<City*> TravelArithmetic::calculateShortestPath(const City& origin, const City& destination, const std::vector<City>& cities) {
    std::map<const City*, double> distances;  // Mapa de distâncias do nó inicial
    std::map<const City*, const City*> previous;  // Mapa de predecessores
    std::set<const City*> unvisited;  // Conjunto de cidades não visitadas

    // Inicializa distâncias
    for (const auto& city : cities) {
        distances[&city] = std::numeric_limits<double>::infinity();
        unvisited.insert(&city);
    }
    distances[&origin] = 0;

    while (!unvisited.empty()) {
        // Encontra a cidade com a menor distância
        const City* currentCity = nullptr;
        double minDistance = std::numeric_limits<double>::infinity();
        for (const auto& city : unvisited) {
            if (distances[city] < minDistance) {
                minDistance = distances[city];
                currentCity = city;
            }
        }

        if (currentCity == nullptr) {
            break; // Se não houver cidade válida, saia do loop
        }

        // Remove a cidade atual dos não visitados
        unvisited.erase(currentCity);

        // Atualiza distâncias para os vizinhos
        for (const auto& path : currentCity->getPaths()) {
            const City* neighbor = path.getDestination();
            if (unvisited.find(neighbor) != unvisited.end()) {
                double newDistance = distances[currentCity] + path.getDistance();
                if (newDistance < distances[neighbor]) {
                    distances[neighbor] = newDistance;
                    previous[neighbor] = currentCity;
                }
            }
        }
    }

    // Reconstroi o caminho
    std::vector<City*> path;
    for (const City* at = &destination; at != nullptr; at = previous[at]) {
        path.push_back(const_cast<City*>(at));  // Adiciona ponteiro ao vetor
        if (at == &origin) {
            break; // Não continue além da cidade de origem
        }
    }
    std::reverse(path.begin(), path.end());
    return path;
}
