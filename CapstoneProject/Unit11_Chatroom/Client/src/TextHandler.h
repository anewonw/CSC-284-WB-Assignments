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
	virtual void printText(std::string message, short color) const;

protected:
	UIWindow* targetWindow;
	UIWindow* srcWindow;
};