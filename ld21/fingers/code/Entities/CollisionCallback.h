#ifndef _COLLISION_CALLBACK_H_
#define _COLLISION_CALLBACK_H_

#include <Resources/Resource.h>
#include <Maths/Vector2.h>

/// Collision Callbacks will change per room
/// Horribly hardcoded, but means there's less entities to check and so on, and can hopefully come up with some neat effects.
/// Really need to get some scripted action going on here as that would be perfect for this.. maybe next time..

class Entity;
class CollisionCallback
{
	public:
		static GLESGAE::Vector2 MOVE_NORTH;
		static GLESGAE::Vector2 MOVE_SOUTH;
		static GLESGAE::Vector2 MOVE_EAST;
		static GLESGAE::Vector2 MOVE_WEST;
		
		virtual ~CollisionCallback() {}
		
		virtual void collide(const GLESGAE::Resource<Entity>& entityA, const GLESGAE::Resource<Entity>& entityB);
		
		virtual void moveToRoom(const GLESGAE::Resource<Entity>& entity
							,	const GLESGAE::Resources::Group fromGroup, const GLESGAE::Resources::Id fromRoom
							,	const GLESGAE::Resources::Group toGroup, const GLESGAE::Resources::Id toRoom
							,	const bool isPlayer = false);
		
		virtual void removeFromRoom(const GLESGAE::Resource<Entity>& entity
								,	const GLESGAE::Resources::Group fromGroup, const GLESGAE::Resources::Id fromRoom);
};

#endif
