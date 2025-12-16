#pragma once
#include <string>
#include <memory>

class Room;

class User 
{
public:
	User(int clientSocket);
	int getSocket() const;
	void setRoom(std::shared_ptr<Room> newRoom);
	std::shared_ptr<Room> getRoom() const;
	const std::string& getUsername() const;
	void setUsername(const std::string& name);
	bool operator==(const User&) const = default;

private:
	std::string username;
	int socket;
	std::shared_ptr<Room> currentRoom;
};