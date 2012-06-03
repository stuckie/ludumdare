#ifndef _STARTING_ROOM_H_
#define _STARTING_ROOM_H_

#include "../Room.h"
#include "StartingRoomCollisions.h"

class StartingRoom : public Room
{
	public:
		StartingRoom();
		~StartingRoom();
		
		void update(const float delta);
		void render();
		void addEntity(const GLESGAE::Resource<Entity>& entity);
		void removeEntity(const GLESGAE::Resource<Entity>& entity);
};

#endif

