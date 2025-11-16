// CSC 284
// Unit 9 Assignment 1: Batch Update User Profiles
// Andrew Dasch

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include "json.hpp"
#include <chrono>
#include <format>
#include <exception>
#include <map>

using namespace std;
using nlohmann::json;
namespace fs = std::filesystem;

const string getTimestampString();
void updateEmail(json& record);
void replaceFields(json& record, const map<string, json>& replacements);

int main(int argc, char* argv[]) {
	if (argc < 2) {
		cerr << "Usage: " << argv[0] << " <user_profiles directory>\n";
		return 1;
	}

	// Replacement map
	map<string, json> replacementFields = {
		{"enabled", { {"status", "enabled"}, {"since", "2024-10-01"}}},
		{"disabled", { {"status", "disabled"}, {"since", "2024-10-01"} } },
		{"manage_users", { {"permission", "manage_users"}, {"granted_at", "2024-10-05"},
		{"level", "full"} } },
		{"edit_content", { {"permission", "edit_content"}, {"granted_at", "2024-9-25"},
		{"level", "full"}}},
		{"access_reports", { {"permission", "access_reports"}, {"granted_at", "2024-11-05"},
		{"level", "read-only"} } } };

	// Check user_profiles directory
	fs::path inputFolder{ argv[1] };
	if (!fs::exists(inputFolder)) {
		cout << "Error: Directory does not exist.";
		return 1;
	}

	// Create new directory with timestamp
	fs::path updateFolder{ getTimestampString() };
	try {
		fs::create_directory(updateFolder);
	}
	catch (const exception&) {
		cout << "Error creating new directory";
		return 1;
	}

	// Read original directory with recursive iterator
	for (auto& file : fs::recursive_directory_iterator(inputFolder)) {
		// New file path relative to input folder
		fs::path workingPath = updateFolder / fs::relative(file.path(), inputFolder);

		// Read json data, apply updates, and write to new file
		if (file.is_regular_file() && file.path().extension() == ".json") {

			// Try to perform operations on files
			try {
				ifstream inFile(file.path());
				json record{ json::parse(inFile) };

				updateEmail(record);
				replaceFields(record, replacementFields);

				// Create folders
				fs::create_directories(workingPath.parent_path());

				// Write to new file
				ofstream outFile(workingPath);

				outFile << record.dump(4);
				cout << "Updated record: " << file.path().filename() << "\n";
				continue;
			}
			// Copy file as-is if error or not json
			catch (const exception& ex) {
				cout << "\nERROR reading " << file << "\n" << ex.what() << "\n\n";
				fs::copy_file(file.path(), workingPath);
				cout << "Copied file without changes: " << file.path().filename() << "\n";
			}
		}
		else
		{
			try
			{
				fs::create_directories(workingPath.parent_path());
				if (!file.is_directory()) {
					fs::copy_file(file.path(), workingPath);
					cout << "Copied file without changes: " << file.path().filename() << "\n";
				}
			}
			catch (const std::exception&)
			{
				cout << "Error copying file: " << file.path().filename() << "\n";
			}
		}
	}
	return 0;
}

// Get formatted string for new directory with current time
const string getTimestampString() {
	auto time{ (chrono::system_clock::now()) };
	return format(".\\user_profiles_updated_{:%Y%m%d_%H%M%S}", time);
}

// Insert "new" into company email address
void updateEmail(json& record) {
	string email{ record["email"] };
	auto addressPos{ email.find("@company.com") };
	record["email"] = email.insert(addressPos + 1, "new");
}

// Gave up on making this more general after much struggle
void replaceFields(json& record, const map<string, json>& map) {
	for (auto& [key, value] : map) {
		if (record.contains("preferences") && record["preferences"].contains("notifications")
			&& record["preferences"]["notifications"] == key) {
			record["preferences"]["notifications"] = value;
		}

		if (record.contains("permissions") && record["permissions"].is_array())
		{
			for (auto& field : record["permissions"]) {
				if (field == key)
					field = value;
			}
		}
	}
}
