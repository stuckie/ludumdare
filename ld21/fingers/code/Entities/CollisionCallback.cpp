#include "CollisionCallback.h"

#include "Entity.h"
#include "../Resources/Entities.h"
#include "../Resources/Rooms.h"
#include "../World/WorldRooms.h"

#include <Platform/Application.h>
#include <Resources/ResourceManager.h>

using namespace GLESGAE;

Vector2 CollisionCallback::MOVE_WEST = Vector2(0.3F, 0.0F);
Vector2 CollisionCallback::MOVE_EAST = Vector2(-0.3F, 0.0F);
Vector2 CollisionCallback::MOVE_NORTH = Vector2(0.0F, 0.3F);
Vector2 CollisionCallback::MOVE_SOUTH = Vector2(0.0F, -0.3F);

void CollisionCallback::collide(const Resource<Entity>& /*entityA*/, const Resource<Entity>& /*entityB*/)
{
}

void CollisionCallback::moveToRoom(const Resource<Entity>& entity, const Resources::Group fromGroup, const Resources::Id fromRoom, const Resources::Group toGroup, const Resources::Id toRoom, const bool isPlayer)
{
	Resource<Room> roomA(Application::getInstance()->getResourceManager()->getBank<Room>(Fingers::Rooms::Bank, Fingers::Rooms::Type).get(fromGroup, fromRoom));	
	roomA->removeEntity(entity);
	
Resource<Room> roomB(Application::getInstance()->getResourceManager()->getBank<Room>(Fingers::Rooms::Bank, Fingers::Rooms::Type).get(toGroup, toRoom));
	roomB->addEntity(entity);

	if (true == isPlayer) {		
		roomA->setVisible(false);
		roomB->setVisible(true);
	}
}
		
void CollisionCallback::removeFromRoom(const Resource<Entity>& entity, const Resources::Group fromGroup, const Resources::Id fromRoom)
{
	Resource<Room> room(Application::getInstance()->getResourceManager()->getBank<Room>(Fingers::Rooms::Bank, Fingers::Rooms::Type).get(fromGroup, fromRoom));
	room->removeEntity(entity);
}
