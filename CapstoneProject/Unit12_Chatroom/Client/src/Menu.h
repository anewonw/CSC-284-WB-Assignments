#pragma once
#include <curses.h>
#include <vector>
#include <string>

// Class for menu
class Menu {
public:
	Menu(WINDOW* targetWindow, WINDOW* srcWindow);
	virtual ~Menu();

	void addOption(const std::string& item);
	void printMenu(int choice);
	int getNumItems() const;
	int getSelection() const;

protected:
	std::vector<std::string> menuItems;
	int selected;
	WINDOW* targetWindow;
	WINDOW* srcWindow;
};