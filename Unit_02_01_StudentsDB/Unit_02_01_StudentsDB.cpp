#include "Student.h"
#include "Database.h"
#include "Major.h"
#include <print>
#include <iostream>
#include <string>
#include <string_view>

using namespace std;
using namespace StudentRecords;

int displayMenu();
void add(Database& db);
void print(Database& db);
void searchID(Database& db);
void searchName(Database& db);
void countMajors(Database& db);
bool isValidInt(const string& input);

int main()
{
	enum class Menu { ADD, PRINT, SEARCH_ID, SEARCH_NAME, COUNT_MAJORS, QUIT };
	Database studentDB;

	bool done{ false };
	while (!done) {
		Menu{ displayMenu() };
		switch (Menu) {
		case Menu::ADD:
			add(studentDB);
			break;
		case Menu::PRINT:
			print(studentDB);
			break;
		case Menu::SEARCH_ID:
			searchID(studentDB);
			break;
		case Menu::SEARCH_NAME:
			searchName(studentDB);
			break;
		case Menu::COUNT_MAJORS:
			countMajors(studentDB);
			break;
		case Menu::QUIT:
			println("Exiting program...");
			done = true;
			break;
		default:
			println("Invalid command");
			break;
		}
	}
}

// Show menu and get user choice
int displayMenu()
{
	int choice;
	println("");
	println("Student Database");
	println("-----------------");
	println("1) Add student");
	println("2) Display all students");
	println("3) Search database by ID#");
	println("4) Search database by name");
	println("5) Count students by major");
	println("6) Quit");
	println("");
	print("Command: ");

	cin >> choice; cin.ignore(100, '\n');

	return choice;
}

// Add new student from user information
void add(Database& db)
{
	string id;
	string name;
	string age;
	string major;
	string email;

	println("New Student");

	print("ID # ");
	getline(cin, id);
	// Check id is numeric
	while (!isValidInt(id)) {
		println("Error - ID # must be numeric:");
		getline(cin, id);
	}
	print("Name: ");
	getline(cin, name);

	print("Age: ");
	getline(cin, age);
	// Check age is numeric
	while (!isValidInt(age)) {
		println("Error - Age must be numeric:");
		getline(cin, age);
	}
	print("Major: ");
	getline(cin, major);

	print("Email: ");
	getline(cin, email);

	db.addStudent(stoi(id), name, stoi(age), major, email);
}

void print()
{
}

void searchID()
{
}

void searchName()
{
}

void countMajorDBs()
{
}

// Validate that input string is numeric, return as int
bool isValidInt(const string& input)
{
	try {
		if (int number{ stoi(input) })
			return true;
	}
	catch (invalid_argument ex) {
		return false;
	}
}
