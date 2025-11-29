#pragma once
#include <curses.h>
#include "UIWindow.h"
#include <vector>
#include <string>
#include "TextHandler.h"
#include <utility>

// Class for menu
class Menu {
public:
	Menu(UIWindow* targetWindow, UIWindow* srcWindow);
	virtual ~Menu();

	void addOption(std::string&& item);
	void printMenu(int choice);
	int getNumItems() const;
	int getSelection() const;

protected:
	std::vector<std::string> menuItems;
	int selected;
	UIWindow* targetWindow;
	UIWindow* srcWindow;
};