#include "Floor1RoomACollisions.h"
#include "Floor1RoomA.h"

#include "../../Entities/Entity.h"
#include "../../Resources/Entities.h"
#include "../../Resources/Rooms.h"

#include <Platform/Application.h>
#include <Resources/ResourceManager.h>

using namespace GLESGAE;

void Floor1RoomACollisions::collide(const Resource<Entity>& entityA, const Resource<Entity>& entityB)
{
	// Player Collisions First
	if (entityA->getTag() == Fingers::Entities::Player) {
		if (entityB->getTag() == Fingers::Entities::Wall) {
			entityA->moveBack();
		}
	
		if (entityB->getTag() == Fingers::Entities::Gem) {
			removeFromRoom(entityB, Fingers::Rooms::Floor1::Group, Fingers::Rooms::Floor1::RoomA);
		}
		
		if (entityB->getTag() == Fingers::Entities::DoorEast) {
			moveToRoom(entityA, Fingers::Rooms::Floor1::Group, Fingers::Rooms::Floor1::RoomA, Fingers::Rooms::Floor1::Group, Fingers::Rooms::Floor1::RoomB);

			entityA->translate(Vector2(-0.2F, 0.0F));
		}
	
		if (entityB->getTag() == Fingers::Entities::DoorSouth) {
			moveToRoom(entityA, Fingers::Rooms::Floor1::Group, Fingers::Rooms::Floor1::RoomA, Fingers::Rooms::Floor1::Group, Fingers::Rooms::Floor1::RoomD);

			entityA->translate(Vector2(0.0F, -0.2F));
		}
	}
	
	// Gem Collisions
	if (entityA->getTag() == Fingers::Entities::Gem) {
		if (entityB->getTag() == Fingers::Entities::DoorEast) {
			moveToRoom(entityA, Fingers::Rooms::Floor1::Group, Fingers::Rooms::Floor1::RoomA, Fingers::Rooms::Floor1::Group, Fingers::Rooms::Floor1::RoomB);

			entityA->translate(Vector2(-0.2F, 0.0F));
		}
	
		if (entityB->getTag() == Fingers::Entities::DoorSouth) {
			moveToRoom(entityA, Fingers::Rooms::Floor1::Group, Fingers::Rooms::Floor1::RoomA, Fingers::Rooms::Floor1::Group, Fingers::Rooms::Floor1::RoomD);

			entityA->translate(Vector2(0.0F, -0.2F));
		}
	}
}

