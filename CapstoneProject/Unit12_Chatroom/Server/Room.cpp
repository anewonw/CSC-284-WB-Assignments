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

#include "Room.h"
#include <string>
#include "User.h"
#include <memory>
#include <mutex>
#include <iostream>
#include <vector>

Room::Room(const std::string& name)
	: rmName{ name }
{
}

// Add user to room
void Room::addUserToRoom(std::shared_ptr<User> user)
{
	std::lock_guard<std::mutex> lock(rmUserMutex);
	rmUsers.push_back(user);
}

// Remove user from room
void Room::removeUserFromRoom(std::shared_ptr<User> user)
{
	std::lock_guard<std::mutex> lock(rmUserMutex);
	rmUsers.erase(
		std::remove(rmUsers.begin(),
		rmUsers.end(), user), rmUsers.end());

	std::cout << "Removed " << user->getUsername() << " from room "
		<< rmName << "\n";
}

const std::string& Room::getRoomName()
{
	return rmName;
}

std::vector<std::shared_ptr<User>> Room::getRoomUsers()
{
	std::lock_guard<std::mutex> lock(rmUserMutex);
	return rmUsers;
}

// Broadcast only to users in room
void Room::broadcastToRoom()
{
	std::lock_guard<std::mutex> rmLock(rmUserMutex);
	std::lock_guard<std::mutex> msgLock(rmMsgMutex);
	if (!rmMsgQueue.empty() && !rmUsers.empty()) {

		for (const auto& msg : rmMsgQueue) {
			for (std::shared_ptr<User> user : rmUsers) {
				send(user->getSocket(), msg.c_str(), static_cast<int>(msg.size()), 0);
			}
			std::cout << "Sent to " << rmName << " : " << msg << std::endl;
		}
		rmMsgQueue.clear();
	}
}

// Queue string for room broadcast
void Room::roomQueueMsg(const std::string& msg)
{
	std::lock_guard<std::mutex> lock(rmMsgMutex);
	rmMsgQueue.push_back(msg);
}
