#pragma once
#include "Vehicle.h"
#include <vector>

class Fleet
{
public:
	~Fleet();

	void addVehicle(Vehicle* vehicle);
	void displayAllVehicles() const;
	double getAverageEfficiency() const;

private:
	// Vector of pointers to Vehicle objects
	std::vector<Vehicle*> m_vehicles;
};