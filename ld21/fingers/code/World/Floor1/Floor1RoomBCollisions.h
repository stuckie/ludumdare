#ifndef _FLOOR1_ROOMB_COLLISIONS_H_
#define _FLOOR1_ROOMB_COLLISIONS_H_

#include "../../Entities/CollisionCallback.h"

class Floor1RoomBCollisions : public CollisionCallback
{
	public:
		void collide(const GLESGAE::Resource<Entity>& entityA, const GLESGAE::Resource<Entity>& entityB);
};

#endif

