// CSC 284
// Unit 5 Assignment 1: Vehicle Management System
// Andrew Dasch

#include "Fleet.h"
#include "Vehicle.h"
#include "Car.h"
#include "Truck.h"
#include "Motorcycle.h"
#include <print>
#include <memory>

using namespace std;

int main() {
	Fleet fleet{};
	println("Vehicle Management System\n");
	println("Adding vehicles to fleet...");

	// Add vehicles to fleet
	fleet.addVehicle(new Car("Toyota", "Corolla", 2020, 20'000, 4, 0));
	fleet.addVehicle(new Truck("Volvo", "FH16", 2018, 80'000, 18));
	fleet.addVehicle(new Motorcycle("Honda", "CBR600", 2021, 5'000, 0));
	fleet.addVehicle(new Car("Tesla", "Model 3", 2022, 15'000, 4, 1));

	// Print results
	fleet.displayAllVehicles();
	println("Total vehicles: {}", Vehicle::getVehicleCount());
	println("Average Fuel efficiency: {} km/l", fleet.getAverageEfficiency());

	println("\nProgram exiting...");
	return 0;
}
