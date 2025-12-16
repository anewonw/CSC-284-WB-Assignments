#pragma once

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

#include <memory>
#include <string>
#include <vector>
#include <mutex>
#include "User.h"
#include "RoomManager.h"
#include <thread>
#include <condition_variable>
#include <atomic>

class ChatServer
{
public:
	void run();
	int startServer(const std::string& ip = "127.0.0.1", const std::string& port = "54000");
	void quitServer();

private:
	void queueMsg(const std::string& msg, std::shared_ptr<User> user);
	void notifyUser(std::shared_ptr<User> user, const std::string& msg);
	void recvMsgs(std::shared_ptr<User> user);
	std::shared_ptr<User> newUser(int socket);
	void disconnectUser(std::shared_ptr<User> user);
	std::shared_ptr<User> acceptClient();
	int parseUserCommands(std::shared_ptr<User> user, const std::string& msg);
	void showAllUsers();
	std::string recvUsername(std::shared_ptr<User> user);
	std::string getDefaultUsername();
	bool userExists(const std::string& target);
	void removeUserThread(std::shared_ptr<User> user);
	void removeUserFromList(std::shared_ptr<User> user);


	sockaddr_in hint{};
	int serverSocket{};
	std::mutex threadMutex;
	std::mutex userMutex;
	std::mutex broadcastMutex;
	std::condition_variable broadcastCV;
	bool hasOutgoingMsgs = false;
	std::vector<std::shared_ptr<User>> userList;
	std::vector<std::jthread> userThreads;
	RoomManager roomManager{};
	int lastDefaultNum{ 0 };
	std::atomic<bool> quit{};
};