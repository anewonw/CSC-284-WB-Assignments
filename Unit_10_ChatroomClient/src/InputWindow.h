#pragma once
#include <curses.h>
#include "UIWindow.h"

// Class for  text input window
class InputWindow : public UIWindow
{
public:
	InputWindow();
	virtual ~InputWindow() override;

};