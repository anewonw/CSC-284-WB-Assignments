#pragma once
#include <string>
#include <vector>
#include <memory>
#include <mutex>

class User;

class Room
{
public:
	Room(const std::string& name);
	void addUserToRoom(std::shared_ptr<User> user);
	void removeUserFromRoom(std::shared_ptr<User> user);
	const std::string& getRoomName();
	std::vector<std::shared_ptr<User>> getRoomUsers();
	void broadcastToRoom();
	void roomQueueMsg(const std::string& msg);

private:
	std::mutex rmUserMutex;
	std::mutex rmMsgMutex;
	std::string rmName;
	std::vector<std::shared_ptr<User>> rmUsers;
	std::vector<std::string> rmMsgQueue;
};