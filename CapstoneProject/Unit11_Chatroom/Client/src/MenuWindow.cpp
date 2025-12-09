#include "MenuWindow.h"
#include <curses.h>
#include "UIWindow.h"

MenuWindow::MenuWindow()
	: UIWindow(LINES - 3, 27, 2, COLS - 28, false)
{
}

MenuWindow::~MenuWindow()
{
}

