#include "Vehicle.h"
#include <print>
#include <string_view>

// Initialize static member
int Vehicle::s_vehicleCount{};

Vehicle::Vehicle()
	: Vehicle("", "", 0, 0.0)
{
}

Vehicle::Vehicle(std::string_view make, std::string_view model, int year, double mileage)
	: m_make{ make }
	, m_model{ model }
	, m_year{ year }
	, m_mileage{ mileage }
{
	s_vehicleCount++;
}

Vehicle::~Vehicle()
{
	std::println("Vehicle destructed.");
	s_vehicleCount--;
}

void Vehicle::setMake(std::string_view make)
{
	m_make = make;
}

const std::string& Vehicle::getMake() const
{
	return m_make;
}

void Vehicle::setModel(std::string_view model)
{
	m_model = model;
}

const std::string& Vehicle::getModel() const
{
	return m_model;
}

// Check year is valid
void Vehicle::setYear(int year)
{
	if (year > 1885)
		m_year = year;
	else
		std::println("Error: invalid year.");
}

int Vehicle::getYear() const
{
	return m_year;
}

// Check mileage is positive
void Vehicle::setMileage(double miles)
{
	if (miles >= 0)
		m_mileage = miles;
	else
		std::println("Error: mileage must be positive.");
}

double Vehicle::getMileage() const
{
	return m_mileage;
}

void Vehicle::displayInfo() const
{
	std::println("{} | Mileage: {} km", m_make, m_mileage);
}

int Vehicle::getVehicleCount()
{
	return s_vehicleCount;
}