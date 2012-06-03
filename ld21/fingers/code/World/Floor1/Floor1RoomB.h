#ifndef _FLOOR1_ROOMB_H_
#define _FLOOR1_ROOMB_H_

#include "../Room.h"
#include "Floor1RoomBCollisions.h"

class Floor1RoomB : public Room
{
	public:
		Floor1RoomB();
		~Floor1RoomB();
		
		void update(const float delta);
		void render();
		void addEntity(const GLESGAE::Resource<Entity>& entity);
		void removeEntity(const GLESGAE::Resource<Entity>& entity);
};

#endif

