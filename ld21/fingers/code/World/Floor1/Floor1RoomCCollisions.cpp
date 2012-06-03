#include "Floor1RoomCCollisions.h"
#include "Floor1RoomC.h"

#include "../../Entities/Entity.h"
#include "../../Resources/Entities.h"
#include "../../Resources/Rooms.h"

#include <Platform/Application.h>
#include <Resources/ResourceManager.h>
#include <States/StateStack.h>
#include "../../States/Game/GameState.h"
#include "../WorldManager.h"

using namespace GLESGAE;

void Floor1RoomCCollisions::collide(const Resource<Entity>& entityA, const Resource<Entity>& entityB)
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
			Resource<Room> roomC(Application::getInstance()->getResourceManager()->getBank<Room>(Fingers::Rooms::Bank, Fingers::Rooms::Type).get(Fingers::Rooms::Floor1::Group, Fingers::Rooms::Floor1::RoomC));
			roomC->removeEntity(entityA);
			Resource<Room> roomB(Application::getInstance()->getResourceManager()->getBank<Room>(Fingers::Rooms::Bank, Fingers::Rooms::Type).get(Fingers::Rooms::Floor1::Group, Fingers::Rooms::Floor1::RoomB));	
			roomB->addEntity(entityA);
			roomB->setVisible(true);
			entityA->translate(Vector2(0.2F, 0.0F));
		}
		
		if (entityB->getTag() == Fingers::Entities::Stairs) {
			Resource<Room> floor1RoomC(Application::getInstance()->getResourceManager()->getBank<Room>(Fingers::Rooms::Bank, Fingers::Rooms::Type).get(Fingers::Rooms::Floor1::Group, Fingers::Rooms::Floor1::RoomC));
			floor1RoomC->removeEntity(entityA);
			Resource<Room> floor2RoomC(Application::getInstance()->getResourceManager()->getBank<Room>(Fingers::Rooms::Bank, Fingers::Rooms::Type).get(Fingers::Rooms::Floor2::Group, Fingers::Rooms::Floor2::RoomC));
			floor2RoomC->addEntity(entityA);
			floor2RoomC->setVisible(true);
			entityA->translate(Vector2(0.0F, -0.2F));
			
			GameState* gameState(reinterpret_cast<GameState*>(Application::getInstance()->getStateStack()->get()));
			gameState->getWorldManager()->setFloor(1U);
		}
	}
}

