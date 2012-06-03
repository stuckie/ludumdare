#ifndef _FLOOR1_ROOMG_COLLISIONS_H_
#define _FLOOR1_ROOMG_COLLISIONS_H_

#include "../../Entities/CollisionCallback.h"

class Floor1RoomGCollisions : public CollisionCallback
{
	public:
		void collide(const GLESGAE::Resource<Entity>& entityA, const GLESGAE::Resource<Entity>& entityB);
};

#endif

