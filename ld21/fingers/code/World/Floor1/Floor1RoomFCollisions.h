#ifndef _FLOOR1_ROOMF_COLLISIONS_H_
#define _FLOOR1_ROOMF_COLLISIONS_H_

#include "../../Entities/CollisionCallback.h"

class Floor1RoomFCollisions : public CollisionCallback
{
	public:
		void collide(const GLESGAE::Resource<Entity>& entityA, const GLESGAE::Resource<Entity>& entityB);
};

#endif

