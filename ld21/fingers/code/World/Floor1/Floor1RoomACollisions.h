#ifndef _FLOOR1_ROOMA_COLLISIONS_H_
#define _FLOOR1_ROOMA_COLLISIONS_H_

#include "../../Entities/CollisionCallback.h"

class Floor1RoomACollisions : public CollisionCallback
{
	public:
		void collide(const GLESGAE::Resource<Entity>& entityA, const GLESGAE::Resource<Entity>& entityB);
};

#endif

