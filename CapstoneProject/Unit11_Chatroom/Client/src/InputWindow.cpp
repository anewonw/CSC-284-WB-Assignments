#include "InputWindow.h"
#include <curses.h>
#include "UIWindow.h"

InputWindow::InputWindow()
	: UIWindow(1, COLS - 34, LINES - 2, 3, false)
{
	keypad(windowObj, TRUE);
	scrollok(windowObj, TRUE);	
}

InputWindow::~InputWindow()
{
}
