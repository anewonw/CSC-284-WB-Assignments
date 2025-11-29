#pragma once
#include <curses.h>
#include <string>

class UIWindow
{
public:
	UIWindow(int height, int width, int startY, int startX, bool border = true);
	virtual ~UIWindow() = default;

	// Getters and setters
	WINDOW* getWindow() const;
	
	int getCursorX() const;
	void setCursorX (int x);
	
	int getCursorY() const;
	void setCursorY(int y);

protected:
	virtual WINDOW* drawWindow(int height, int width, int startY, int startX) const;
	int height;
	int width;
	int startY;
	int startX;
	int cursorX;
	int cursorY;
	WINDOW* windowObj;
};