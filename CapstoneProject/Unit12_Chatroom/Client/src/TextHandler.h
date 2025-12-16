#pragma once
#include <curses.h>
#include <string>

// Class to handle text input/output
class TextHandler
{

public:
	TextHandler(WINDOW* targetWindow, WINDOW* srcWindow);
	virtual ~TextHandler();
	virtual void printText(std::string message, short color) const;

protected:
	WINDOW* targetWindow;
	WINDOW* srcWindow;
};