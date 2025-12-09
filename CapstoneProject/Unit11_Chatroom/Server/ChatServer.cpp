// CSC 284
// Chatroom Server
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

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <thread>
#include <mutex>
#include <memory>
#include <chrono>
#include <exception>
#include <cstdlib>

struct ServerManager {
	std::mutex sockMutex{};
	std::mutex msgMutex{};
	std::vector<int> clientSockets{};
	std::vector<std::string> messageQueue{};
};

void queueMsg(ServerManager& manager, const std::string& msg);
void broadcastAll(ServerManager& manager);
void recvMsgs(ServerManager& manager, int clientSocket);
void disconnectClient(ServerManager& manager, int clientSocket);

int main(int argc, char* argv[])
{
	 // Check argument count
	if (argc > 3) {
		std::cout << "Usage: ChatServer ip port";
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

	// Create socket
	int listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening < 0)
	{
		std::cerr << "Cannot create socket";
		return 1;
	}
	sockaddr_in hint{};
	hint.sin_family = AF_INET;

	// Use arguments to set ip/port if provided
	try {
		if (argc >= 2) {
			inet_pton(AF_INET, argv[1], &hint.sin_addr);
		}
		else
			inet_pton(AF_INET, "127.0.0.1", &hint.sin_addr);

		if (argc == 3) {
			hint.sin_port = htons(static_cast<u_short>(std::stoi(argv[2])));
		}
		else
			hint.sin_port = htons(54000);

		char serverIP[NI_MAXHOST];
		inet_ntop(AF_INET, &hint.sin_addr, serverIP, NI_MAXHOST);
		int serverPort = ntohs(hint.sin_port);

		std::cout << "Server running on " << serverIP << ": " << serverPort << "\n";

	}

	catch (const std::exception&) {
		std::cout << "Error: Could not start server with specified ip/port\n";
		return 2;
	}

	// Bind the socket to IP/port and listen
	std::cout << "Listening...\n";
	bind(listening, (sockaddr*)&hint, sizeof(hint));
	listen(listening, SOMAXCONN);

	ServerManager manager;

	// Broadcast messages to all clients
	std::jthread broadcastThread([&]() {
		while (true) {
			if (!manager.messageQueue.empty()) {
				broadcastAll(manager);
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}});

		// Handle commands
		std::jthread cmdThread([&]() {
			std::string cmd;
			while (std::getline(std::cin, cmd)) {
				if (cmd == "quit" || cmd == "Quit") {
					std::cout << "Shutting down server...\n";
					closesocket(listening);
					exit (0);
				}
			}});

		// Accept clients and handle messages
		while (true) {

			sockaddr_in client{};
			socklen_t clientSize = sizeof(client);
			int clientSocket = accept(listening, (sockaddr*)&client, &clientSize);

			{
				std::lock_guard<std::mutex> lock(manager.sockMutex);
				manager.clientSockets.emplace_back(clientSocket);
				std::cout << "Client " << clientSocket << " connected.\n";
			}

			// Launch client thread
			std::thread([clientSocket, &manager]() {
				recvMsgs(manager, clientSocket);
				}).detach();
		}
		closesocket(listening);

#ifdef _WIN32
		WSACleanup();
#endif

		return 0;
}

// Add incoming messages to queue for broadcasting
void queueMsg(ServerManager& manager, const std::string& msg)
{
	std::lock_guard<std::mutex> lock(manager.msgMutex);
	manager.messageQueue.push_back(msg);
	for (const auto& msg : manager.messageQueue) {
		std::cout << "Queued message for broadcasting: " << msg << std::endl;
	}
}

// Broadcast 
void broadcastAll(ServerManager& manager)
{
	std::lock_guard<std::mutex> lock(manager.sockMutex);
	for (auto& client : manager.clientSockets) {
		for (const auto& msg : manager.messageQueue) {
			send(client, msg.c_str(), static_cast<int>(msg.size()), 0);
			std::cout << "Sent to client socket " << client << ": " << msg << std::endl;
		}
	}
	manager.messageQueue.clear();
}

// Receive client messages
void recvMsgs(ServerManager& manager, int clientSocket)
{
	char buffer[4096];
	while (true) {
		memset(buffer, 0, 4096);
		int bytesReceived = recv(clientSocket, buffer, 4096, 0);
		if (bytesReceived <= 0)
			break;
		std::string msg(buffer, bytesReceived);

		if (msg == "quit" || msg == "Quit") {
			disconnectClient(manager, clientSocket);
			return;
		}

		// Add message to shared queue
		std::cout << "Client " << clientSocket << ": " << msg << std::endl;
		queueMsg(manager, msg);
	}
	disconnectClient(manager, clientSocket);
}

// Disconnect and remove client from socket list
void disconnectClient(ServerManager& manager, int clientSocket) {
	closesocket(clientSocket);

	// Erase and remove
	std::lock_guard<std::mutex> lock(manager.sockMutex);
	manager.clientSockets.erase(std::remove(manager.clientSockets.begin(),
		manager.clientSockets.end(), clientSocket), manager.clientSockets.end());
	std::cout << "Disconnected Client " << clientSocket << "\n";
}

