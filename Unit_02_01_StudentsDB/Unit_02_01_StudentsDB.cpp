#include "Student.h"
#include "Database.h"
#include "Major.h"
#include <print>
#include <iostream>
#include <string>
#include <string_view>
#include <stdexcept>

using namespace std;
using namespace StudentRecords;

int displayMenu();
void add(Database& db);
void searchID(Database& db);
void searchName(Database& db);
bool isValidInt(const string& input);
int getValidInt();

int main()
{
	enum class Menu { ADD = 1, PRINT, SEARCH_ID, SEARCH_NAME, COUNT_MAJORS, QUIT };
	Database studentDB;

	bool done{ false };
	while (!done) {
		// Cast int choice to Menu
		Menu choice { static_cast<Menu>(displayMenu())};
		switch (choice) {
		case Menu::ADD:
			add(studentDB);
			break;
		case Menu::PRINT:
			studentDB.printAllRecords();
			break;
		case Menu::SEARCH_ID:
			searchID(studentDB);
			break;
		case Menu::SEARCH_NAME:
			searchName(studentDB);
			break;
		case Menu::COUNT_MAJORS:
			studentDB.printStudentsByMajor();
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

	return getValidInt() ;
}

// Add new student from user information
void add(Database& db)
{
	println("New Student");

	print("ID # ");
	int id{ getValidInt() };
	
	string name;
	print("Name: ");
	getline(cin, name);

	print("Age: ");
	int age{ getValidInt() };
	
	string major;
	print("Major: ");
	getline(cin, major);

	string email;
	print("Email: ");
	getline(cin, email);

	db.addStudent(id, name, age, major, email);
}

void searchID(Database& db)
{
	print("ID # ");
	int id{ getValidInt() };
	try {
		db.findID(id);
	}
	catch (logic_error ex)
	{
		println("{}", ex.what());
	}
}

void searchName(Database& db)
{
	string name;
	print("Name: ");
	getline(cin, name);

	try {
		db.findName(name);
	}
	catch (logic_error ex)
	{
		println("{}", ex.what());
	}
}

// Validate that input string is numeric
bool isValidInt(const string& input)
{
	try {
		if (int number{ stoi(input) })
			return true;
	}
	catch (exception ex ) {
		return false;
	}
}

// Return int from input string
int getValidInt()
{
	string input;
	getline(cin, input);
	while (!isValidInt(input)) {
		println("Error - Value must be numeric: ");
		getline(cin, input);
	}
	return stoi(input);
}
