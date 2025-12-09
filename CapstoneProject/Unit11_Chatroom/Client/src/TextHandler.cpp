#include "TextHandler.h"
#include <curses.h>
#include "UIWindow.h"
#include <string>

TextHandler::TextHandler(UIWindow* targetWindow, UIWindow* srcWindow)
	: targetWindow{ targetWindow }
	, srcWindow{ srcWindow }
{
}

TextHandler::~TextHandler()
{
}

// Print message to target window
void TextHandler::printText(std::string message, short color) const
{
	WINDOW* target{ targetWindow->getWindow() };

	// Get the current and max Y values
	int curY{ getcury(target) };
	int maxY{ getmaxy(target) };

	// Scroll if bottom is reached
	wsetscrreg(target, 0, maxY);

	// Set color
	wattron(target, COLOR_PAIR(color));

	// Print message
	wprintw(target, message.c_str());
	wattroff(target, COLOR_PAIR(color));

	// Move the cursor to the next line in chat window
	// Reset cursor in input window
	wmove(target, curY + 1, 0);
	wmove(srcWindow->getWindow(), 0, 0);

	// Refresh windows
	wrefresh(target);
	wrefresh(srcWindow->getWindow());
}