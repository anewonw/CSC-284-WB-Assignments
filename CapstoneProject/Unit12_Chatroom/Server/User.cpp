#include "User.h"
#include <string>
#include "Room.h"
#include <memory>

User::User(int clientSocket)
	: socket{ clientSocket }
	, currentRoom{ nullptr }
{
}

const std::string& User::getUsername() const
{
	return username;
}

int User::getSocket() const
{
	return socket;
}

void User::setRoom(std::shared_ptr<Room> newRoom)
{
	currentRoom = newRoom;
}

std::shared_ptr<Room> User::getRoom() const
{
	return currentRoom;
}

void User::setUsername(const std::string& name)
{
	username = name;
}