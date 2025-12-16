#pragma once
#include <vector>
#include <memory>
#include <string>
#include <mutex>

class Room;

class RoomManager
{
public:
	RoomManager();
	std::shared_ptr<Room> createRoom(const std::string& roomName);
	std::vector<std::shared_ptr<Room>> getRoomList();
	void broadcastAllRooms();
	std::shared_ptr<Room> findRoom(const std::string& target);

private:
	std::mutex roomListMutex;
	std::vector<std::shared_ptr<Room>> roomList;
};