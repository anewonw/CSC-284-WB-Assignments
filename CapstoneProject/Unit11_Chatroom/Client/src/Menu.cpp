#include "Menu.h"
#include <utility>
#include <curses.h>
#include "UIWindow.h"
#include <string>
#include <vector>
#include <iostream>

Menu::Menu(UIWindow* targetWindow, UIWindow* srcWindow)
	: targetWindow{ targetWindow }
	, srcWindow{ srcWindow }
	, selected { 0 }
{
}

Menu::~Menu()
{
}

// Add menu items
void Menu::addOption(std::string&& item)
{
	menuItems.push_back(std::move(item));
}

// Print menu items and handle highlighting
void Menu::printMenu(int choice)
{
	WINDOW* target = targetWindow->getWindow();

	if (choice < 0 || choice >= menuItems.size())
	{
		choice = 0;
	}		

	for (int i{ 0 }; i < menuItems.size(); ++i)
	{
		if (i == choice)
		{
			wattron(target, A_REVERSE);
		}

		mvwprintw(target, i, 0, menuItems[i].c_str());
		wattroff(target, A_REVERSE);
	}

	wrefresh(target);
}

int Menu::getNumItems() const
{
	return static_cast<int>(menuItems.size());
}

int Menu::getSelection() const
{
	return selected;
}
