// CSC 284
// Capstone Project: Chatroom Client
// Andrew Dasch

// - 12.8.25 -
// I'm sure I could get rid of all the window classes,
// When I started, I thought they might be useful...
// Maybe for final version.

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
// I had to manually add x64 location of ws2_32.lib to additional dependencies
#pragma comment(lib, "Ws2_32.lib")
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#define closesocket close
#endif
#include <utility>
#include <iostream>
#include <string>
#include <thread>
#include <cstring>
#include <exception>
#include <curses.h>
#include "TextHandler.h"
#include "ChatWindow.h"
#include "UIWindow.h"
#include "MenuWindow.h"
#include "InputWindow.h"
#include "Menu.h"

constexpr const char* VERSION = "0.4";
void colorSwitcher(int& colorPair);

int main(int argc, char* argv[])
{
	if (argc > 3)
	{
		std::cout << "Usage: Chatroom ip port \n";
		return 1;
	}

	/******************************************************************************/
	/*                                                                            */
	/* NCurses Setup															  */
	/*                                                                            */
	/******************************************************************************/

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
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);

	// Print title with version number
	attron(COLOR_PAIR(1));
	printw(" Advanced Chat Client v%s", VERSION);
	attroff(COLOR_PAIR(1));
	refresh();

	// Add menu and options
	Menu menu(&menuWindow, &inputWindow);
	menu.addOption("Jazz Club");
	menu.addOption("Sports Trivia");
	menu.addOption("Politics");
	menu.addOption("Just Hanging Out");
	menu.printMenu(0);

	/******************************************************************************/
	/*                                                                            */
	/* Winsock Setup															  */
	/*                                                                            */
	/******************************************************************************/

	// Initialize winsock and check for errors
#ifdef _WIN32
	WSADATA data;
	int WSCheck = WSAStartup(MAKEWORD(2, 2), &data);
	if (WSCheck != 0) {
		std::cerr << "WSAStartup failed: " << WSCheck;
	};
#endif

	// Set up socket
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
	{
		std::cerr << "Cannot create socket";
		return 1;
	}

	sockaddr_in serverHint{};
	serverHint.sin_family = AF_INET;

	// Use arguments to set ip/port if provided
	try {
		if (argc >= 2) {
			inet_pton(AF_INET, argv[1], &serverHint.sin_addr);
		}
		else
			inet_pton(AF_INET, "127.0.0.1", &serverHint.sin_addr);

		if (argc == 3) {
			serverHint.sin_port = htons(static_cast<u_short>(std::stoi(argv[2])));
		}
		else
			serverHint.sin_port = htons(54000);
	}

	catch (const std::exception&) {
		std::cout << "Error: Could not start client with specified ip/port\n";
		return 2;
	}

	// Connect to server
	int conn = connect(sock, (sockaddr*)&serverHint, sizeof(serverHint));
	if (conn < 0)
	{
		std::cerr << "Could not connect to server.\n";
		return 1;
	}
	chatHandler.printText("Connected to server.", 1);

	/******************************************************************************/
	/*                                                                            */
	/* Main input Loop															  */
	/*                                                                            */
	/******************************************************************************/

	int menuSelection{};
	int menuSize{ menu.getNumItems() };

	// Receiving thread
	std::thread([&]() {
		int color{2};
		char buffer[4096];
		while (true) {
			memset(buffer, 0, 4096);
			int bytesReceived = recv(sock, buffer, 4096, 0);
			if (bytesReceived > 0) {
				colorSwitcher(color);
				std::string msgToPrint("Server: " + std::string(buffer, bytesReceived) + "\n");
				chatHandler.printText(msgToPrint, color);
			}
		}}).detach();

		// Get user input
		std::string inputStr;
		while (true) {
			int ch{ wgetch(inputWindow.getWindow()) };

			// Quit if 'quit' is entered
			if (inputStr == "Quit" || inputStr == "quit") {
				break;
			}
			// Handle directional input
			else if (ch == KEY_DOWN && menuSelection < menuSize - 1) {
				menu.printMenu(++menuSelection);
				continue;
			}
			else if (ch == KEY_UP && menuSelection > 0) {
				menu.printMenu(--menuSelection);
				continue;
			}
			// Handle printable characters
			else if (ch >= 32 && ch <= 126) {
				inputStr += ch;
			}
			// Handle newline
			else if (ch == '\n') {
				send(sock, inputStr.c_str(), inputStr.size(), 0);
				wclear(inputWindow.getWindow());
				wrefresh(inputWindow.getWindow());
				inputStr.clear();
			}
		}
		closesocket(sock);
		endwin();
		std::cout << "Disconnected...\n";
		return 0;
}

void colorSwitcher(int& colorPair) {
	if (colorPair == 2)
		colorPair = 3;
	else
		colorPair = 2;
}