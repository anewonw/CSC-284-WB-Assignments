// CSC 284
// Capstone Project: Chatroom Client
// Andrew Dasch

// 12.15.25
// Now I see why programs never stop getting updated... no end of features/bugs to add!

// 12.8.25
// I'm sure I could get rid of all the window classes,
// When I started, I thought they might be useful...
// Maybe for final version.

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
// I had to manually add x64 location of ws2_32.lib to additional dependencies to compile
// (C:\Program Files (x86)\Windows Kits\10\Lib...)
#pragma comment(lib, "Ws2_32.lib")
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#define closesocket close
#endif
#include <iostream>
#include <string>
#include <thread>
#include <cstring>
#include <exception>
#include <curses.h>
#include "TextHandler.h"
#include "Menu.h"

constexpr const char* VERSION = "0.6";
void colorSwitcher(int& colorPair);
WINDOW* drawWindow(int height, int width, int startY, int startX, bool border);

int main(int argc, char* argv[])
{
	if (argc > 4)
	{
		std::cout << "Usage: Chatroom <ip> <port> <username\n";
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
	WINDOW* chatFrame{ drawWindow(LINES - 4, COLS - 30, 1, 0, true) };
	WINDOW* menuFrame{ drawWindow (LINES - 1, 30, 1, COLS - 30, true) };
	WINDOW* inputFrame{ drawWindow (3, COLS - 30, LINES - 3, 0, true) };
	mvwprintw(inputFrame, 1, 1, "> ");
	wrefresh(inputFrame);

	// Create windows and text handler
	WINDOW* chatWindow{ drawWindow(LINES - 6, COLS - 33, 2, 2, false) };
	scrollok(chatWindow, TRUE);
	WINDOW* menuWindow{ drawWindow(LINES - 3, 27, 2, COLS - 28, false) };
	WINDOW* inputWindow{ drawWindow(1, COLS - 34, LINES - 2, 3, false) };
	keypad(inputWindow, TRUE);
	scrollok(inputWindow, TRUE);
	TextHandler chatHandler{ chatWindow, inputWindow };

	// Initialize color pairs
	start_color();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_RED, COLOR_BLACK);
	init_pair(5, COLOR_BLUE, COLOR_BLACK);
	init_pair(6, COLOR_YELLOW, COLOR_BLACK);
	init_pair(7, COLOR_MAGENTA, COLOR_BLACK);

	// Print title with version number
	attron(COLOR_PAIR(1));
	printw(" Advanced Chat Client v%s", VERSION);
	attroff(COLOR_PAIR(1));
	refresh();

	// Add menu and options
	Menu menu(menuWindow, inputWindow);
	menu.addOption("Lobby");
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

		if (argc >= 3) {
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

	// Send desired username and get verified by server or get default
	std::string desiredName;
	if (argc == 4)
		desiredName = argv[3];
	else
		desiredName = "NO_NAME_SPECIFIED";

	send(sock, desiredName.c_str(), desiredName.size(), 0);

	/******************************************************************************/
	/*                                                                            */
	/* Main input Loop															  */
	/*                                                                            */
	/******************************************************************************/

	int menuSelection{};
	int menuSize{ menu.getNumItems() };

	// Receiving thread
	std::jthread ([&]() {
		int color{ 1 };
		char buffer[4096];
		while (true) {
			memset(buffer, 0, 4096);
			int bytesReceived = recv(sock, buffer, 4096, 0);
			if (bytesReceived > 0) {

				std::string msgToPrint(buffer, bytesReceived);

				// Clear screen if joining new room
				if (msgToPrint.starts_with("Server: Joined")) {
					werase(chatWindow);
					colorSwitcher(color);
				}
					chatHandler.printText(msgToPrint, color);
			}
		} }).detach();

		// Get user input

		while (true) {
			char input[512];
			wgetnstr(inputWindow, input, 512);
			std::string inputStr = input;

			send(sock, inputStr.c_str(), inputStr.size(), 0);
			wclear(inputWindow);
			wrefresh(inputWindow);

			// Quit if .EXIT is entered
			if (inputStr == ".EXIT") {
				break;
			}
		}

		closesocket(sock);
		endwin();
		std::cout << "Exiting program...\n";
		return 0;
}

void colorSwitcher(int& colorPair) {
	if (colorPair == 7)
		colorPair = 2;
	else
		colorPair++;
}

WINDOW* drawWindow(int height, int width, int startY, int startX, bool border)
{
	WINDOW* newWindow{ newwin(height, width, startY, startX) };

	if (border)
		box(newWindow, 0, 0);
	wrefresh(newWindow);

	return newWindow;
}
