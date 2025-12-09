#include "UIWindow.h"
#include <curses.h>


UIWindow::UIWindow(int height, int width, int startY, int startX, bool border)
	: height{ height }
	, width{ width }
	, startY{ startY }
	, startX{ startX }
	, windowObj{ nullptr }
	, cursorX{ 1 }
	, cursorY{ 1 }
{
	windowObj  = drawWindow(height, width, startY, startX);
	if (border)
	{
		box(windowObj, 0, 0);
		wrefresh(windowObj);
	}
}

// Draw new window
WINDOW* UIWindow::drawWindow(int height, int width, int startY, int startX) const
{
	WINDOW* newWindow{ newwin(height, width, startY, startX) };
	wrefresh(newWindow);
	return newWindow;
}

WINDOW* UIWindow::getWindow() const
{
	return windowObj;
}

int UIWindow::getCursorX() const
{
	return cursorX;
}

void UIWindow::setCursorX(int x)
{
	cursorX = x;
}

int UIWindow::getCursorY() const
{
	return cursorY;
}

void UIWindow::setCursorY(int y)
{
	cursorY = y;
}

