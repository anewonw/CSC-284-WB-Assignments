#pragma once
#include "Vehicle.h"
#include <string_view>

class Motorcycle : public Vehicle
{
public:
	Motorcycle(std::string_view make, std::string_view model, int year, double mileage, bool
		hasSideCar);
	virtual ~Motorcycle() override;

	double getFuelEfficiency() const override;
	void displayInfo() const override;

private:
	bool m_hasSideCar;
};