// CSC 284
// Capstone Project: Chatroom Server - Final
// Andrew Dasch

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#include <Windows.h>
#include <ws2def.h>
#pragma comment(lib, "Ws2_32.lib")
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#define closesocket close
#endif
#include "ChatServer.h"
#include <iostream>

int main(int argc, char* argv[])
{
	// Check argument count
	if (argc > 3) {
		std::cout << "Usage: ChatServer <ip> <port>";
		return 1;
	}

	// Initialize winsock and check for errors
#ifdef _WIN32
	WSADATA data;
	int WSCheck = WSAStartup(MAKEWORD(2, 2), &data);
	if (WSCheck != 0) {
		std::cerr << "WSAStartup failed: " << WSCheck;
		return 1;
	};
#endif

	// Start server with optional arguments

	ChatServer server;

	if (argc == 1)
		server.startServer();
	else if (argc == 2)
		server.startServer(argv[1]);
	else if (argc == 3)
		server.startServer(argv[1], argv[2]);
	
	// Run
	server.run();

	return 0;
}
