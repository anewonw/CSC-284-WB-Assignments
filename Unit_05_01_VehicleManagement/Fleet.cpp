#include "Fleet.h"
#include "Vehicle.h"
#include <print>


// Deallocate each Vehicle pointer
Fleet::~Fleet()
{
    for (auto& vehicle : m_vehicles) {
        delete vehicle;
        vehicle = nullptr;
    }
}

// Add Vehicle pointer to vector
void Fleet::addVehicle(Vehicle* vehicle)
{
    m_vehicles.push_back(vehicle);
}

void Fleet::displayAllVehicles() const
{
    for (auto& vehicle : m_vehicles) {
        vehicle->displayInfo();
        std::println();
    }
}

// Return average fuel efficiency
double Fleet::getAverageEfficiency() const
{
    double sum{};
    for (auto& vehicle : m_vehicles) {
        sum+= vehicle->getFuelEfficiency();
    }
    return sum / Vehicle::getVehicleCount();
}
