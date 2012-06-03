#ifndef _FLOOR1_ROOME_H_
#define _FLOOR1_ROOME_H_

#include "../Room.h"
#include "Floor1RoomECollisions.h"

class Floor1RoomE : public Room
{
	public:
		Floor1RoomE();
		~Floor1RoomE();
		
		void update(const float delta);
		void render();
		void addEntity(const GLESGAE::Resource<Entity>& entity);
		void removeEntity(const GLESGAE::Resource<Entity>& entity);
};

#endif

