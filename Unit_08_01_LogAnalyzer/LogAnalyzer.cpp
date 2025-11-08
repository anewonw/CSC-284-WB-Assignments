#include "LogAnalyzer.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <mutex>
#include <vector>

void LogAnalyzer::analyzeFile(const std::string& filename, const std::vector<std::string>& keywords) {
	std::ifstream file(filename);
	if (!file) {
		std::cerr << "Error: Could not open file " << filename << "\n";
		return;
	}

	// Use lock_guard to synchronize cout statements
	{
		std::lock_guard<std::mutex> lock(countMutex);
		std::cout << "Processing: " << filename << std::endl;
	}

	std::string line;

	// Check file for keywords from vector
	while (std::getline(file, line)) {

		// Search line
		for (const auto& keyword : keywords) {
			size_t found{ line.find(keyword) };

			if (found != std::string::npos) {
				// Lock guard for thread
				std::lock_guard<std::mutex> lock(countMutex);
				// Store results in map
				++keywordCounts[keyword];
				break;
			}
		}
	}
}

// Print map with for_each and lambda expression
void LogAnalyzer::printSummary() const {
	std::cout << "\n--- Keyword Summary ---\n";

	std::for_each(keywordCounts.cbegin(), keywordCounts.cend(), [](const auto& keyword)
		{std::cout << keyword.first << "  " << keyword.second << std::endl; });

	std::cout << "-----------------------\n";
}
