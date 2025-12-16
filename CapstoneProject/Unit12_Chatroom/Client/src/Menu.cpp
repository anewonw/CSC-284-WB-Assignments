#include "Menu.h"
#include <curses.h>
#include <string>
#include <vector>


Menu::Menu(WINDOW* targetWindow, WINDOW* srcWindow)
	: targetWindow{ targetWindow }
	, srcWindow{ srcWindow }
	, selected { 0 }
{
}

Menu::~Menu()
{
}

// Add menu items
void Menu::addOption(const std::string& item)
{
	menuItems.push_back(item);
}

// Print menu items and handle highlighting
void Menu::printMenu(int choice)
{
	if (choice < 0 || choice >= menuItems.size())
	{
		choice = 0;
	}		

	for (int i{ 0 }; i < menuItems.size(); ++i)
	{
		if (i == choice)
		{
			wattron(targetWindow, A_REVERSE);
		}

		mvwprintw(targetWindow, i, 0, menuItems[i].c_str());
		wattroff(targetWindow, A_REVERSE);
	}

	wrefresh(targetWindow);
}

int Menu::getNumItems() const
{
	return menuItems.size();
}

int Menu::getSelection() const
{
	return selected;
}
