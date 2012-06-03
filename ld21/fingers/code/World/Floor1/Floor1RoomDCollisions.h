#ifndef _FLOOR1_ROOMD_COLLISIONS_H_
#define _FLOOR1_ROOMD_COLLISIONS_H_

#include "../../Entities/CollisionCallback.h"

class Floor1RoomDCollisions : public CollisionCallback
{
	public:
		void collide(const GLESGAE::Resource<Entity>& entityA, const GLESGAE::Resource<Entity>& entityB);
};

#endif

