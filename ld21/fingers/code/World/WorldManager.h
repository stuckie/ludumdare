#ifndef _WORLD_MANAGER_H_
#define _WORLD_MANAGER_H_

#include <Resources/Resource.h>
#include "Room.h"

#include <vector>

/// The World Manager's job is to load and connect all the rooms together.
/// It is also responsible for rendering the room tiles and updating each room's Entity Manager
class WorldManager
{
	public:
		WorldManager(const unsigned int floors);
		
		/// Add a room
		void addRoom(const GLESGAE::Resource<Room>& room);
		
		/// Render the world
		void render();
		
		/// Update the world
		void update(const float delta);
		
		/// Set Floor
		void setFloor(const unsigned int floor) { mFloor = floor; }
		
	private:
		/// 2D array sorted by Floor and Room
		std::vector<std::vector<GLESGAE::Resource<Room> > > mRooms;
		unsigned int mFloor;
};

#endif

