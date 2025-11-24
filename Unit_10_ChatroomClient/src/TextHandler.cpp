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
	scrollok(target, TRUE);

	// Get the current cursor position and max X, Y values
	int curY{ getcury(target) };
	int curX{ getcurx(target) };
	int maxY{ getmaxy(target) };
	int maxX{ getmaxx(target) };

	// Scroll if bottom is reached
	if (curY >= maxY - 1)
	{
		wscrl(target, 1);
		wmove(target, maxY - 1, 0);
	}

	// Set color
	wattron(target, COLOR_PAIR(color));

	// Print message
	wprintw(target, message.c_str());

	// Move the cursor to the next line
	wmove(target, curY + 1, 0);

	wattroff(target, COLOR_PAIR(color));

	// Refresh window
	wrefresh(target);
}

// Print last entered string
void TextHandler::printText(short color) const
{
	TextHandler::printText(lastMsg, color);
}

// Read characters into buffer and store as string
void TextHandler::getTextInput()
{
	WINDOW* source{ srcWindow->getWindow() };
	char buffer[256]{};
	wmove(source, 0, 0);
	mvwgetnstr(source, 0, 0, buffer, 255);
	lastMsg = buffer;
	wclear(source);
}

// Get last entered message
std::string TextHandler::getLastString() const
{
	return lastMsg;
}