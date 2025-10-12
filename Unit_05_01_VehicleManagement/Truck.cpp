#include "Truck.h"
#include "Vehicle.h"
#include <print>
#include <string_view>
#include "Vehicle.h"

Truck::Truck(std::string_view make, std::string_view model, int year, double mileage, 
    double loadCap)
    : Vehicle(make, model, year, mileage)
    , m_loadCapacity{loadCap}
{
}

Truck::~Truck()
{
    std::println("Truck destructed.");
}

double Truck::getFuelEfficiency() const
{
    return 8.0;
}

void Truck::displayInfo() const
{
    Vehicle::displayInfo();
    std::println("Type: Truck | Load Capacity: {} tons", m_loadCapacity);
    std::println("Fuel Efficiency: {} km/l", getFuelEfficiency());
}
