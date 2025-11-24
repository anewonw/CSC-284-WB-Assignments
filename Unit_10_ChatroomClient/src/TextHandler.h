#pragma once
#include <curses.h>
#include "UIWindow.h"
#include <string>

// Class to handle text input/output
class TextHandler
{

public:
	TextHandler(UIWindow* targetWindow, UIWindow* srcWindow);
	virtual ~TextHandler();

	void getTextInput();
	virtual void printText(std::string message, short color) const;
	virtual void printText(short color) const;
	std::string getLastString() const;

protected:
	UIWindow* targetWindow;
	UIWindow* srcWindow;
	std::string lastMsg;
};