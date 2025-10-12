#pragma once
#include "Vehicle.h"
#include <string_view>

class Truck : public Vehicle
{
public:
	Truck(std::string_view make, std::string_view model, int year, double mileage, double loadCap);
	virtual ~Truck() override;

	double getFuelEfficiency() const override;
	void displayInfo() const override;

private:
	double m_loadCapacity;
};