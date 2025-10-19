// CSC 284
// Unit 6 Assignment 1: Generic Statistics Calculator
// Andrew Dasch

#include "Statistics.h"
#include <iostream>
#include <vector>

int main() {
	//Create objects using template arguments and add values
	Statistics<int> intStats;
	intStats.addValue(10);
	intStats.addValue(20);
	intStats.addValue(30);

	Statistics<double> doubleStats;
	doubleStats.addValue(3.14);
	doubleStats.addValue(2.71);
	doubleStats.addValue(4.5);

	std::vector<long> longVector{ 6345878, 8753456, 13453 };

	// Show results with class template functions
	std::cout << "Int Stats: Min = " << intStats.getMin()
		<< ", Max = " << intStats.getMax()
		<< ", Avg = " << intStats.getAverage() << "\n";

	std::cout << "Double Stats: Min = " << doubleStats.getMin()
		<< ", Max = " << doubleStats.getMax()
		<< ", Avg = " << doubleStats.getAverage() << "\n";

	// Show results with global function templates
	std::cout << "Long Stats: Min = " << Global::getMin(longVector)
		<< ", Max = " << Global::getMax(longVector)
		<< ", Avg = " << Global::getAverage(longVector) << "\n";

	return 0;
}