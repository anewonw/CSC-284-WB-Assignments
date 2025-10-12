#pragma once
#include <string>
#include <string_view>

class Vehicle
{
public:
	// Constructors
	Vehicle();
	Vehicle(std::string_view make, std::string_view model, int year, double mileage);

	// Virtual destructor
	virtual ~Vehicle();

	// Accessors/Mutators
	void setMake(std::string_view make);
	const std::string& getMake() const;

	void setModel(std::string_view model);
	const std::string& getModel() const;

	void setYear(int year);
	int getYear() const;

	void setMileage(double miles);
	double getMileage() const;

	// Virtual functions
	virtual void displayInfo() const;
	virtual double getFuelEfficiency() const = 0;

	// Static function
	static int getVehicleCount();

private:
	// Data members
	std::string m_make;
	std::string m_model;
	int m_year;
	double m_mileage;
	// Static member
	static int s_vehicleCount;
};