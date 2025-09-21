// CSC 284
// Unit 2 Assignment 2: Fix this Code!
// Andrew Dasch

#include <iostream>
#include <vector>

using namespace std;

// Class to hold traffic light colors and runLights function
class TrafficLight
{
public:

	// Repeatedly cycle through light colors starting from red
	static void runLights(const int numTimes)
	{
		int color = Red;
		for (int i = 0; i < numTimes; i++) {
			cout << ms_lightColor[color] << endl;
			color++;
			if (color == Restart)
				color = Red;
		}
	}

private:
	const enum lightState { Red, Green, Yellow, Restart };
	static const vector<string> ms_lightColor;
};

const vector<string> TrafficLight::ms_lightColor{ "Red","Green","Yellow" };

int main()
{
	int numTimes;
	cout << "Number of traffic light changes: ";
	cin >> numTimes;

	TrafficLight::runLights(numTimes);
}