// CSC 284
// Unit 8 - Multithreaded Log Analyzer
// Andrew Dasch

#include "LogAnalyzer.h"
#include <iostream>
#include <filesystem>
#include <thread>
#include <vector>
#include <string>
#include <exception>

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cerr << "Usage: " << argv[0] << " <log_directory>\n";
		return 1;
	}

	std::string folderPath = argv[1];
	LogAnalyzer analyzer;
	std::vector<std::string> keywords = { "[ERROR]", "[WARN]", "[INFO]", "[FATAL]", "[DEBUG]", "[TRACE]" };
	std::vector<std::thread> threads;

	// Check path exists and is directory
	while (!fs::exists(folderPath) || !fs::is_directory(folderPath)) {
		std::cout << "Error opening directory \"" << folderPath << "\"\nEnter log directory: ";
		std::cin >> folderPath;
	}

	std::cout << "Analyzing folder: " << folderPath << "\n\n";

	try {
		// Launch threads for each .log file
		for (auto& file : fs::directory_iterator(folderPath)) {
			if (file.path().extension() == ".log") {
				threads.emplace_back(&LogAnalyzer::analyzeFile, &analyzer, file.path().string(), keywords);
			}
		}
		// Join all threads
		for (auto& thread : threads)
			thread.join();

		// Show results
		analyzer.printSummary();
		std::cout << "Analysis complete. Processed " << threads.size() << " files.\n";
	}

	// Catch errors with accessing files
	catch (const std::exception& ex) {
		std::cerr << "Error occurred when attempting to access files:\n" << ex.what() << std::endl;
		return 2;
	}
	return 0;
}

