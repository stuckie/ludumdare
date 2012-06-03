#ifndef _FLOOR1_ROOMA_H_
#define _FLOOR1_ROOMA_H_

#include "../Room.h"
#include "Floor1RoomACollisions.h"

class Floor1RoomA : public Room
{
	public:
		Floor1RoomA();
		~Floor1RoomA();
		
		void update(const float delta);
		void render();
		void addEntity(const GLESGAE::Resource<Entity>& entity);
		void removeEntity(const GLESGAE::Resource<Entity>& entity);
};

#endif

