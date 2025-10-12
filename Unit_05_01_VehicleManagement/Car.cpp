#include "Car.h"
#include "Vehicle.h"
#include <print>

Car::Car(std::string_view make, std::string_view model, int year, double mileage, int numDoors,
	bool isElectric)
	: Vehicle(make, model, year, mileage)
	, m_numDoors{ numDoors }
	, m_isElectric{ isElectric }
{
}

Car::~Car()
{
	std::println("Car destructed.");
}

// Return 0 if electric
double Car::getFuelEfficiency() const
{
	if (m_isElectric)
		return 0.0;
	else
		return 15.0;
}

void Car::displayInfo() const
{
	Vehicle::displayInfo();
	std::println("Type: Car | Doors: {} | Electric: {}", m_numDoors, m_isElectric ? "Yes" : "No");
	std::println("Fuel Efficiency: {} km/l", getFuelEfficiency());
}
