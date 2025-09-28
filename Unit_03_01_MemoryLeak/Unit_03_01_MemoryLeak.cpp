// CSC 284
// Unit 3 Assignment 1: Fix that Leak!
// Andrew Dasch

#include <iostream>
#include <memory>

using namespace std;

int main() {
	int loopCounter{};

	while (true) {
		// With leak - allocates new arrays but does not release them
		// double* ptr{ new double[6000] {} };
		// cout << "Leaked " << loopCounter++ << " great big honkin' arrays!\n";

		// Without leak - uses smart pointers with make_unique
		auto ptr{ make_unique<double[]>(6000) };
		cout << "Allocated and freed " << loopCounter++ << " great big honkin' arrays with smart pointers!\n";
	}
}