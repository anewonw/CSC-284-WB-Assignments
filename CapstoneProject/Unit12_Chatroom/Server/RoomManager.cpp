#include "RoomManager.h"
#include "Room.h"
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <mutex>

RoomManager::RoomManager()
{
	roomList.emplace_back(std::make_shared<Room>("Lobby"));

}

// Create room from user string
std::shared_ptr<Room> RoomManager::createRoom(const std::string& roomName)
{
	auto room = std::make_shared<Room>(roomName);
	std::lock_guard<std::mutex> lock(roomListMutex);
	roomList.push_back(room);
	return room;
}

std::vector<std::shared_ptr<Room>> RoomManager::getRoomList()
{
	std::lock_guard<std::mutex> lock(roomListMutex);
	return roomList;
}

// Broadcast to each room
void RoomManager::broadcastAllRooms()
{
	std::lock_guard<std::mutex> lock(roomListMutex);
	for (std::shared_ptr<Room> room : roomList)
		room->broadcastToRoom();
}

// Find room from string
std::shared_ptr<Room> RoomManager::findRoom(const std::string& target)
{
	std::lock_guard<std::mutex> lock(roomListMutex);
	auto it = std::find_if(roomList.begin(), roomList.end(),
		[&](auto room)
		{ return room->getRoomName() == target; });

	if (it != roomList.end())
		return *it;
	else
		return nullptr;
}