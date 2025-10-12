#include "Motorcycle.h"
#include "Vehicle.h"
#include <string_view>
#include <print>

Motorcycle::Motorcycle(std::string_view make, std::string_view model, int year, double mileage,
	bool hasSideCar)
	: Vehicle(make, model, year, mileage)
	, m_hasSideCar{ hasSideCar }
{
}

Motorcycle::~Motorcycle()
{
	std::println("Motorcycle destructed.");
}

double Motorcycle::getFuelEfficiency() const
{
	return 30.0;
}

void Motorcycle::displayInfo() const
{
	Vehicle::displayInfo();
	std::println("Type: Motorcycle | Sidecar: {}", m_hasSideCar ? "Yes" : "No");
	std::println("Fuel Efficiency: {} km/l", getFuelEfficiency());
}
