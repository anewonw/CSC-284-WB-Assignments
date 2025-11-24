#include "ChatWindow.h"
#include <curses.h>
#include "UIWindow.h"

ChatWindow::ChatWindow()
	: UIWindow(LINES - 6, COLS - 33, 2, 2, false)
{
	scrollok(windowObj, TRUE);
	//idlok(windowObj, TRUE);
}

ChatWindow::~ChatWindow()
{
}