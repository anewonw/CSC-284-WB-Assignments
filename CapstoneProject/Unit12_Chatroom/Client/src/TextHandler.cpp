#include "TextHandler.h"
#include <curses.h>
#include <string>

TextHandler::TextHandler(WINDOW* targetWindow, WINDOW* srcWindow)
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
	scrollok(targetWindow, TRUE);

	// Set color
	wattron(targetWindow, COLOR_PAIR(color));

	// Print message
	wprintw(targetWindow, "% s\n", message.c_str());
	wattroff(targetWindow, COLOR_PAIR(color));

	// Refresh windows
	wrefresh(targetWindow);
	wrefresh(srcWindow);
}