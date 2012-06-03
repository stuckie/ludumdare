#ifndef _FLOOR1_ROOMC_H_
#define _FLOOR1_ROOMC_H_

#include "../Room.h"
#include "Floor1RoomCCollisions.h"

class Floor1RoomC : public Room
{
	public:
		Floor1RoomC();
		~Floor1RoomC();
		
		void update(const float delta);
		void render();
		void addEntity(const GLESGAE::Resource<Entity>& entity);
		void removeEntity(const GLESGAE::Resource<Entity>& entity);
};

#endif

