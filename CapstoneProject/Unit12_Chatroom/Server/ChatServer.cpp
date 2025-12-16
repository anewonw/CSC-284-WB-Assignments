#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#include <ws2def.h>
#pragma comment(lib, "Ws2_32.lib")
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#define closesocket close
#endif

#include "ChatServer.h"
#include "RoomManager.h"
#include "User.h"
#include "Room.h"
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <thread>
#include <mutex>
#include <memory>
#include <exception>
#include <algorithm>
#include <cstdlib>

// Add incoming messages to room queues and notify broadcast thread
void ChatServer::queueMsg(const std::string& msg, std::shared_ptr<User> user)
{
	user->getRoom()->roomQueueMsg(user->getUsername() + ": " + msg);
	{
		std::lock_guard<std::mutex> lock(broadcastMutex);
		hasOutgoingMsgs = true;
	}
	broadcastCV.notify_one();
}

// Send message to individual user
void ChatServer::notifyUser(std::shared_ptr<User> user, const std::string& msg)
{
	std::string sendingMsg("Server: " + msg);
	send(user->getSocket(), sendingMsg.c_str(), sendingMsg.size(), 0);
}

// Receive client messages
void ChatServer::recvMsgs(std::shared_ptr<User> user)
{
	char buffer[4096];
	int userSocket{ user->getSocket() };
	while (!quit) {
		memset(buffer, 0, 4096);
		int bytesReceived = recv(userSocket, buffer, 4096, 0);
		if (bytesReceived <= 0) {
			disconnectUser(user);
			return;
		}

		std::string msg(buffer, bytesReceived);

		// Check for commands
		int cmd{ parseUserCommands(user, msg) };
		if (cmd == -1)
			return;
		else if (cmd == 1)
			continue;

		// Add message to shared queue
		std::cout << user->getUsername() << ": " << msg << std::endl;
		queueMsg(msg, user);
	}
	return;
}

// Close user socket and remove from master and room user lists
void ChatServer::disconnectUser(std::shared_ptr<User> user) {
	notifyUser(user, "Disconnected from server.");
	shutdown(user->getSocket(), SD_BOTH);
	closesocket(user->getSocket());

	std::cout << "Disconnected " << user->getUsername() << "\n";
	removeUserFromList(user);
	user->getRoom()->removeUserFromRoom(user);
	removeUserThread(user);
	broadcastCV.notify_all();
}

// Close sockets, exit program
void ChatServer::quitServer()
{
	// Copy userList to avoid deadlock
	std::vector<std::shared_ptr<User>> listCopy;
	{
		std::lock_guard < std::mutex> lock(userMutex);
		listCopy = userList;
		userList.clear();
	}

	for (auto& user : listCopy)
		disconnectUser(user);

	shutdown(serverSocket, SD_BOTH);
	closesocket(serverSocket);
#ifdef _WIN32
	WSACleanup();
#endif
	// Could find no good way to end all blocking processes after extended struggle
	exit(0);
}

// Accept client and create User
std::shared_ptr<User> ChatServer::acceptClient()
{
	sockaddr_in client{};
	socklen_t clientSize = sizeof(client);
	int clientSocket = accept(serverSocket, (sockaddr*)&client, &clientSize);

	if (clientSocket == INVALID_SOCKET)
		return nullptr;

	if (quit) {
		closesocket(clientSocket);
		return nullptr;
	}

	return newUser(clientSocket);

}

// Create new user from socket and add to lists
std::shared_ptr<User> ChatServer::newUser(int socket)
{
	if (!quit) {
		auto newUser = std::make_shared<User>(socket);
		std::shared_ptr<Room> lobby = roomManager.getRoomList()[0];
		newUser->setUsername(recvUsername(newUser));
		newUser->setRoom(lobby);
		lobby->addUserToRoom(newUser);
		{
			std::lock_guard<std::mutex> lock(userMutex);
			userList.push_back(newUser);
		}
		notifyUser(newUser, "Welcome " + newUser->getUsername() + "! Joined "
			+ newUser->getRoom()->getRoomName());

		std::cout << newUser->getUsername() << " connected.\n";
		return newUser;
	}
	return nullptr;
}

// Parse user message for commands and handle
int ChatServer::parseUserCommands(std::shared_ptr<User> user, const std::string& msg)
{
	if (msg == ".EXIT") {
		disconnectUser(user);

		return -1;
	}
	else if (msg.starts_with(".CREATE_ROOM ")) {
		auto room = roomManager.createRoom(msg.substr(13));
		notifyUser(user, "Created room " + room->getRoomName());
		std::cout << user->getUsername() << " created room " << room->getRoomName() << "\n";
		return 1;
	}
	else if (msg.starts_with(".JOIN_ROOM ")) {
		auto room = roomManager.findRoom(msg.substr(11));
		if (room != nullptr) {
			user->getRoom()->removeUserFromRoom(user);
			user->setRoom(room);
			room->addUserToRoom(user);
			notifyUser(user, "Joined room " + room->getRoomName());
			std::cout << user->getUsername() << " joined " << room->getRoomName() << "\n";
		}
		else
			notifyUser(user, "\"" + msg.substr(11) + "\" room not found on server.");
		return 1;
	}
	else if (msg.starts_with(".LIST_ROOMS")) {
		std::string roomsStr{ "\n" };
		for (auto& room : roomManager.getRoomList()) {
			roomsStr += room->getRoomName() + "\n";
		}
		notifyUser(user, roomsStr);
		return 1;
	}
	return 0;
}

// Main loops
void ChatServer::run()
{
	// Broadcast messages to all rooms when msg is queued
	std::jthread BroadcastThread([&]() {
		while (!quit) {
			std::unique_lock<std::mutex> lock(broadcastMutex);

			broadcastCV.wait(lock, [&]() {
				return hasOutgoingMsgs || quit;
				});

			if (quit)
				return;

			hasOutgoingMsgs = false;
			lock.unlock();
			roomManager.broadcastAllRooms();
			lock.lock();
		}
		});

	// Handle commands
	std::jthread cmdThread([&]() {
		std::string cmd;
		while (!quit) {
			if (!std::getline(std::cin, cmd))
				return;
			if (cmd == "quit") {
				std::cout << "Shutting down server...\n";
				quit = true;
				quitServer();
			}
			else if (cmd == "users") {
				showAllUsers();
			}
			else if (cmd == "threads") {
				for (auto& thread : userThreads)
					std::cout << thread.get_id() << "\n";
			}
		}});

		// Accept clients and handle messages in new thread
		while (!quit) {
			auto newUser{ acceptClient() };
			if (newUser == nullptr)
				break;

			// Launch client thread
			userThreads.emplace_back(std::jthread([newUser, this]() {
				recvMsgs(newUser);
				}));
		}
}

// Show all connected users in rooms
void ChatServer::showAllUsers()
{
	for (auto& room : roomManager.getRoomList()) {
		std::cout << "Room:" << room->getRoomName() << "\nUsers:\n";
		for (auto& user : room->getRoomUsers()) {
			std::cout << user->getUsername() << "\n";
		}
		std::cout << "\n";
	}
}

// Setup socket
int ChatServer::startServer(const std::string& ip, const std::string& port)
{
	// Create socket
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket < 0)
	{
		std::cerr << "Cannot create socket";
		return 1;
	}

	hint.sin_family = AF_INET;

	// Set ip and port
	try {
		inet_pton(AF_INET, ip.c_str(), &hint.sin_addr);
		hint.sin_port = htons(static_cast<u_short>(std::stoi(port)));

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
	bind(serverSocket, (sockaddr*)&hint, sizeof(hint));
	listen(serverSocket, SOMAXCONN);
	return 0;
}

// Get and verify username or assign default name
std::string ChatServer::recvUsername(std::shared_ptr<User> user)
{
	char buffer[4096];
	memset(buffer, 0, 4096);
	int bytesReceived = recv(user->getSocket(), buffer, 4096, 0);

	if (bytesReceived > 0) {
		std::string name(buffer, bytesReceived);
		if (name != "NO_NAME_SPECIFIED" && !userExists(name))
			return name;
		else if (userExists(name)) {
			notifyUser(user, name + " already in use. You have been assigned a default name.");
			return getDefaultUsername();

		}
	}
	return getDefaultUsername();
}

// Get unique default name
std::string ChatServer::getDefaultUsername()
{
	return "anon" + std::to_string(++lastDefaultNum);
}

// Check if username is already taken
bool ChatServer::userExists(const std::string& target)
{
	std::lock_guard<std::mutex> lock(userMutex);
	auto it = std::find_if(userList.begin(), userList.end(),
		[&](std::shared_ptr<User> user)
		{ return user->getUsername() == target; });

	if (it != userList.end())
		return true;
	else
		return false;
}

void ChatServer::removeUserFromList(std::shared_ptr<User> user)
{
	std::lock_guard<std::mutex> lock(userMutex);
	userList.erase(
		std::remove_if(userList.begin(),
			userList.end(), [&](std::shared_ptr<User> target) {
				return target->getUsername() == user->getUsername();})
		, userList.end());
}

// Trying to shrink threadList, not working as intended
void ChatServer::removeUserThread(std::shared_ptr<User> user)
{
	std::lock_guard<std::mutex> lock(threadMutex);
	userThreads.erase(
		std::remove_if(userThreads.begin(),
			userThreads.end(), [&](std::jthread& thread) {
				return !thread.joinable(); })
		, userThreads.end());
}
