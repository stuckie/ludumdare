#ifndef _STARTING_ROOM_COLLISIONS_H_
#define _STARTING_ROOM_COLLISIONS_H_

#include "../../Entities/CollisionCallback.h"

class StartingRoomCollisions : public CollisionCallback
{
	public:
		void collide(const GLESGAE::Resource<Entity>& entityA, const GLESGAE::Resource<Entity>& entityB);
};

#endif

