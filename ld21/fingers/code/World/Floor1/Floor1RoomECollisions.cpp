#include "Floor1RoomECollisions.h"
#include "Floor1RoomE.h"

#include "../../Entities/Player.h"
#include "../../Entities/Entity.h"
#include "../../Entities/Crusher.h"
#include "../../Entities/TrapDoor.h"
#include "../../Entities/Spikes.h"
#include "../../Resources/Entities.h"
#include "../../Entities/PressurePad.h"
#include "../../Resources/Rooms.h"

#include <Platform/Application.h>
#include <Resources/ResourceManager.h>

using namespace GLESGAE;

void Floor1RoomECollisions::collide(const Resource<Entity>& entityA, const Resource<Entity>& entityB)
{
	// Player Collisions First
	if (entityA->getTag() == Fingers::Entities::Player) {
		if (entityB->getTag() == Fingers::Entities::Wall) {
			entityA->moveBack();
		}
	
		if (entityB->getTag() == Fingers::Entities::Gem) {
			Resource<Room> room(Application::getInstance()->getResourceManager()->getBank<Room>(Fingers::Rooms::Bank, Fingers::Rooms::Type).get(Fingers::Rooms::Floor1::Group, Fingers::Rooms::Floor1::RoomE));
			room->removeEntity(entityB);
			Player* player(const_cast<Player*>(reinterpret_cast<const Player*>(&(*entityA))));
			player->addGem();
		}
		
		if (entityB->getTag() == Fingers::Entities::Spikes) {
			const Spikes* spikes(reinterpret_cast<const Spikes*>(&(*entityB)));
			if (Spikes::UP == spikes->getState()) {
				Player* player(const_cast<Player*>(reinterpret_cast<const Player*>(&(*entityA))));
				player->modifyHealth(-10U);
			}
		}
		
		if (entityB->getTag() == Fingers::Entities::Camera) {
			Player* player(const_cast<Player*>(reinterpret_cast<const Player*>(&(*entityA))));
			player->modifyHealth(-10U);
		}
		
		if (entityB->getTag() == Fingers::Entities::StarDiamond) {
			Vector2 objectPosition(entityB->getPosition());
			Vector2 difference(objectPosition);
			difference -= entityA->getPosition();
			objectPosition += difference * 0.5F;
			entityB->setPosition(objectPosition);
		}
		
		if (entityB->getTag() == Fingers::Entities::Weight) {
			Vector2 objectPosition(entityB->getPosition());
			Vector2 difference(objectPosition);
			difference -= entityA->getPosition();
			objectPosition += difference * 0.5F;
			entityB->setPosition(objectPosition);
		}
		
		// Room specific
		if (entityB->getTag() == Fingers::Entities::DoorSouth) {
			moveToRoom(entityA, Fingers::Rooms::Floor1::Group, Fingers::Rooms::Floor1::RoomE, Fingers::Rooms::Floor1::Group, Fingers::Rooms::Floor1::RoomG, true);
			entityA->translate(MOVE_SOUTH);
		}
	}
	
	// Crusher
	if (entityA->getTag() == Fingers::Entities::Crusher) {
		Crusher* crusher(const_cast<Crusher*>(reinterpret_cast<const Crusher*>(&(*entityA))));
		if ((entityB->getTag() == Fingers::Entities::Player)
		||	(entityB->getTag() == Fingers::Entities::Gem)
		||	(entityB->getTag() == Fingers::Entities::StarDiamond)
		||	(entityB->getTag() == Fingers::Entities::Weight)) {
			Vector2 objectPosition(entityB->getPosition());
			Vector2 difference(objectPosition);
			difference -= entityA->getPosition();
			objectPosition += difference * crusher->getSpeed();
			entityB->setPosition(objectPosition);

			if (entityB->getTag() == Fingers::Entities::Player) {			
				Player* player(const_cast<Player*>(reinterpret_cast<const Player*>(&(*entityB))));
				player->modifyHealth(-10U);
			}
		}
		
		if (entityB->getTag() == Fingers::Entities::Wall)
			crusher->swapDirection();
	}
	
		// Star Diamond Collisions
	if (entityA->getTag() == Fingers::Entities::StarDiamond) {
		if (entityB->getTag() == Fingers::Entities::Wall) {
			entityA->moveBack();
		}
		
		if (entityB->getTag() == Fingers::Entities::DoorSouth) {
			moveToRoom(entityA, Fingers::Rooms::Floor1::Group, Fingers::Rooms::Floor1::RoomE, Fingers::Rooms::Floor1::Group, Fingers::Rooms::Floor1::RoomG);
			entityA->translate(Vector2(0.0F, -0.5F));
		}
	}
	
	
	// Weight collisions
	if (entityA->getTag() == Fingers::Entities::Weight) {
		if (entityB->getTag() == Fingers::Entities::Wall) {
			entityA->moveBack();
		}
		
		if (entityB->getTag() == Fingers::Entities::DoorSouth) {
			moveToRoom(entityA, Fingers::Rooms::Floor1::Group, Fingers::Rooms::Floor1::RoomE, Fingers::Rooms::Floor1::Group, Fingers::Rooms::Floor1::RoomG);
			entityA->translate(MOVE_SOUTH);
		}
	}
}

