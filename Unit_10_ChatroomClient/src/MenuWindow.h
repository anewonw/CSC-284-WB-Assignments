#pragma once
#include <curses.h>
#include "UIWindow.h"

// Class for room selection window
class MenuWindow : public UIWindow
{
public:
	MenuWindow();
	virtual ~MenuWindow() override;

};