#pragma once
#include <vector>

template <typename T>
class Statistics {
private:
	std::vector<T> data;

public:
	void addValue(const T& value);
	T getMin() const;
	T getMax() const;
	double getAverage() const;
};

// Global template functions
// Traverse vector to find minimum, maximum, and average values
namespace Global {
	template<typename T>
	T getMin(const std::vector<T>& values)
	{
		T min{ values[0] };
		for (auto& value : values) {
			if (value < min)
				min = value;
		}

		return min;
	}

	template<typename T>
	T getMax(const std::vector<T>& values)
	{
		T max{ values[0] };
		for (auto& value : values) {
			if (value > max)
				max = value;
		}

		return max;
	}

	template<typename T>
	double getAverage(const std::vector<T>& values)
	{
		T sum{};
		for (auto& value : values) {
			sum += value;
		}

		return static_cast<double>(sum / values.size());
	}
}

// Add new value to data vector
template<typename T>
void Statistics<T>::addValue(const T& value)
{
	data.push_back(value);
}

// Class template functions call global
template<typename T>
T Statistics<T>::getMin() const
{
	return Global::getMin(data);
}

template<typename T>
T Statistics<T>::getMax() const
{
	return Global::getMax(data);
}

template<typename T>
double Statistics<T>::getAverage() const
{
	return Global::getAverage(data);
}