#include "Floor1RoomBCollisions.h"
#include "Floor1RoomB.h"

#include "../../Entities/Entity.h"
#include "../../Resources/Entities.h"
#include "../../Resources/Rooms.h"

#include <Platform/Application.h>
#include <Resources/ResourceManager.h>

using namespace GLESGAE;

void Floor1RoomBCollisions::collide(const Resource<Entity>& entityA, const Resource<Entity>& entityB)
{
	// Player Collisions First
	if (entityA->getTag() == Fingers::Entities::Player) {
		if (entityB->getTag() == Fingers::Entities::Wall) {
			entityA->moveBack();
		}
	
		if (entityB->getTag() == Fingers::Entities::Gem) {
			Resource<Room> room(Application::getInstance()->getResourceManager()->getBank<Room>(Fingers::Rooms::Bank, Fingers::Rooms::Type).get(Fingers::Rooms::Floor1::Group, Fingers::Rooms::Floor1::RoomB));
			room->removeEntity(entityB);
		}
		
		if (entityB->getTag() == Fingers::Entities::DoorWest) {
			Resource<Room> roomB(Application::getInstance()->getResourceManager()->getBank<Room>(Fingers::Rooms::Bank, Fingers::Rooms::Type).get(Fingers::Rooms::Floor1::Group, Fingers::Rooms::Floor1::RoomB));
			roomB->removeEntity(entityA);
			Resource<Room> roomA(Application::getInstance()->getResourceManager()->getBank<Room>(Fingers::Rooms::Bank, Fingers::Rooms::Type).get(Fingers::Rooms::Floor1::Group, Fingers::Rooms::Floor1::RoomA));	
			roomA->addEntity(entityA);
			roomA->setVisible(true);
			entityA->translate(Vector2(0.2F, 0.0F));
		}
		
		if (entityB->getTag() == Fingers::Entities::DoorEast) {
			Resource<Room> roomB(Application::getInstance()->getResourceManager()->getBank<Room>(Fingers::Rooms::Bank, Fingers::Rooms::Type).get(Fingers::Rooms::Floor1::Group, Fingers::Rooms::Floor1::RoomB));
			roomB->removeEntity(entityA);
			Resource<Room> roomC(Application::getInstance()->getResourceManager()->getBank<Room>(Fingers::Rooms::Bank, Fingers::Rooms::Type).get(Fingers::Rooms::Floor1::Group, Fingers::Rooms::Floor1::RoomC));
			roomC->addEntity(entityA);
			roomC->setVisible(true);
			entityA->translate(Vector2(-0.2F, 0.0F));
		}
	}
}

