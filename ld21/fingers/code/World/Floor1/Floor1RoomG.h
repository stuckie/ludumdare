#ifndef _FLOOR1_ROOMG_H_
#define _FLOOR1_ROOMG_H_

#include "../Room.h"
#include "Floor1RoomGCollisions.h"

class Floor1RoomG : public Room
{
	public:
		Floor1RoomG();
		~Floor1RoomG();
		
		void update(const float delta);
		void render();
		void addEntity(const GLESGAE::Resource<Entity>& entity);
		void removeEntity(const GLESGAE::Resource<Entity>& entity);
};

#endif

