// CSC 284
// Unit 10: Assignment 1: Chatroom Client
// Andrew Dasch

#include <curses.h>
#include "TextHandler.h"
#include "ChatWindow.h"
#include "UIWindow.h"
#include "MenuWindow.h"
#include "InputWindow.h"
#include <string>
#include "Menu.h"
#include <utility>	

constexpr const char* VERSION = "0.3";

int main(int argc, char* argv[])
{
	// Initialize ncurses
	initscr();
	refresh();

	// Create border frames
	UIWindow chatFrame{ LINES - 4, COLS - 30, 1, 0 };
	UIWindow menuFrame{ LINES - 1, 30, 1, COLS - 30 };
	UIWindow inputFrame{ 3, COLS - 30, LINES - 3, 0 };

	// Create windows and text handler
	ChatWindow chatWindow;
	mvwprintw(inputFrame.getWindow(), 1, 1, "> ");
	wrefresh(inputFrame.getWindow());
	MenuWindow menuWindow;
	InputWindow inputWindow;
	TextHandler chatHandler{ &chatWindow, &inputWindow };

	// Initialize color pairs
	start_color();
	init_pair(1, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(2, COLOR_CYAN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);

	// Print title with version number
	attron(COLOR_PAIR(2));
	printw(" Advanced Chat Client v%s", VERSION);
	attroff(COLOR_PAIR(2));
	refresh();

	// Placeholder messages
	std::string placeholderMsg = "Chat messages will appear here.";
	std::string user1 = "Penguin234234: Greetings PsychoBacon420!";
	std::string user2 = "PsychoBacon420: Well met, comrade Penguin";
	chatHandler.printText(placeholderMsg, 1);
	chatHandler.printText(user1, 3);
	chatHandler.printText(user2, 1);

	// Add menu and options
	Menu menu(&menuWindow, &inputWindow);
	menu.addOption("Jazz Club");
	menu.addOption("Sports Trivia");
	menu.addOption("Politics");
	menu.addOption("Just Hanging Out");
	menu.printMenu(0);

	// Handle user input
	std::string inputStr;
	int menuSelection{};
	int menuSize{ menu.getNumItems() };

	while (true) {
		int ch{ wgetch(inputWindow.getWindow()) };

		// Quit if 'q' is pressed
		if (ch == 'q' || ch == 'Q') {
			break;
		}
		// Handle directional input
		else if (ch == KEY_DOWN && menuSelection < menuSize - 1) {
			menu.printMenu(++menuSelection);
			continue;
		}
		else if (ch == KEY_UP && menuSelection > 0) {
			menu.printMenu (--menuSelection);
			continue;
		}
		// Handle printable characters
		else if (ch >= 32 && ch <= 126)	{
			inputStr += ch;
		}
		// Handle newline
		else if (ch == '\n') {
			chatHandler.printText("You: " + inputStr, 2);
			wclear(inputWindow.getWindow());
			wrefresh(inputWindow.getWindow());
			inputStr.clear();
		}
	}

	endwin();
	return 0;
}
