#pragma once
#include "Vehicle.h"
#include <string_view>

class Car : public Vehicle
{
public:
	Car(std::string_view make, std::string_view model, int year, double mileage, int numDoors,
		bool isElectric);
	virtual ~Car() override;

	double getFuelEfficiency() const override;
	void displayInfo() const override;

private:
	int m_numDoors;
	bool m_isElectric;
};