#include "StartingRoomCollisions.h"
#include "StartingRoom.h"

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

#include <cstdio>
#include <Maths/Vector2.h>

using namespace GLESGAE;

extern bool gameComplete;

void StartingRoomCollisions::collide(const Resource<Entity>& entityA, const Resource<Entity>& entityB)
{
	// Player Collisions First
	if (entityA->getTag() == Fingers::Entities::Player) {
		// General Ones
		if (entityB->getTag() == Fingers::Entities::Wall) {
			entityA->moveBack();
		}
		
		if (entityB->getTag() == Fingers::Entities::Health) {
			removeFromRoom(entityB, Fingers::Rooms::Floor1::Group, Fingers::Rooms::Floor1::StartingRoom);
			Player* player(const_cast<Player*>(reinterpret_cast<const Player*>(&(*entityA))));
			player->modifyHealth(+10U);
		}
		
		if (entityB->getTag() == Fingers::Entities::Gem) {
			removeFromRoom(entityB, Fingers::Rooms::Floor1::Group, Fingers::Rooms::Floor1::StartingRoom);
			Player* player(const_cast<Player*>(reinterpret_cast<const Player*>(&(*entityA))));
			player->addGem();
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
		
		if (entityB->getTag() == Fingers::Entities::TrapDoor) {
			const TrapDoor* trapDoor(reinterpret_cast<const TrapDoor*>(&(*entityB)));
			if (TrapDoor::OPEN == trapDoor->getState()) {
				Player* player(const_cast<Player*>(reinterpret_cast<const Player*>(&(*entityA))));
				player->modifyHealth(-10U);
				// should also fall down a level, so trap doors should only be used on 2nd and 3rd floors
			}
		}
		
		if (entityB->getTag() == Fingers::Entities::PressurePad) {
			PressurePad* pressurePad(const_cast<PressurePad*>(reinterpret_cast<const PressurePad*>(&(*entityB))));
			pressurePad->setDown();
		}
		
		if (entityB->getTag() == Fingers::Entities::Spikes) {
			const Spikes* spikes(reinterpret_cast<const Spikes*>(&(*entityB)));
			if (Spikes::UP == spikes->getState()) {
				Player* player(const_cast<Player*>(reinterpret_cast<const Player*>(&(*entityA))));
				player->modifyHealth(-10U);
			}
		}
		
		if (entityB->getTag() == Fingers::Entities::Crusher) {
			const Crusher* crusher(reinterpret_cast<const Crusher*>(&(*entityB)));
			Player* player(const_cast<Player*>(reinterpret_cast<const Player*>(&(*entityA))));
			player->modifyHealth(-10U);
			Vector2 objectPosition(entityA->getPosition());
			Vector2 difference(objectPosition);
			difference -= entityB->getPosition();
			objectPosition += difference * crusher->getSpeed();
			entityA->setPosition(objectPosition);
		}
		
		if (entityB->getTag() == Fingers::Entities::Camera) {
			Player* player(const_cast<Player*>(reinterpret_cast<const Player*>(&(*entityA))));
			player->modifyHealth(-10U);
		}
		
		
		// Room specific
		if (entityB->getTag() == Fingers::Entities::DoorWest) {
			moveToRoom(entityA, Fingers::Rooms::Floor1::Group, Fingers::Rooms::Floor1::StartingRoom, Fingers::Rooms::Floor1::Group, Fingers::Rooms::Floor1::RoomF, true);

			entityA->translate(MOVE_WEST);
		}
	
		if (entityB->getTag() == Fingers::Entities::DoorEast) {
			moveToRoom(entityA, Fingers::Rooms::Floor1::Group, Fingers::Rooms::Floor1::StartingRoom, Fingers::Rooms::Floor1::Group, Fingers::Rooms::Floor1::RoomG, true);

			entityA->translate(MOVE_EAST);
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
	
	if (entityA->getTag() == Fingers::Entities::PressurePad) {
		if ((entityB->getTag() == Fingers::Entities::Player)
		|| (entityB->getTag() == Fingers::Entities::Weight)) {
			// Room specific, really
		}
	}
	
	// Star Diamond Collisions
	if (entityA->getTag() == Fingers::Entities::StarDiamond) {
		if (entityB->getTag() == Fingers::Entities::Wall) {
			entityA->moveBack();
		}
		
		if (entityB->getTag() == Fingers::Entities::DoorWest) {
			moveToRoom(entityA, Fingers::Rooms::Floor1::Group, Fingers::Rooms::Floor1::StartingRoom, Fingers::Rooms::Floor1::Group, Fingers::Rooms::Floor1::RoomF);

			entityA->translate(Vector2(0.5F, 0.0F));
		}
	
		if (entityB->getTag() == Fingers::Entities::DoorEast) {
			moveToRoom(entityA, Fingers::Rooms::Floor1::Group, Fingers::Rooms::Floor1::StartingRoom, Fingers::Rooms::Floor1::Group, Fingers::Rooms::Floor1::RoomG);

			entityA->translate(Vector2(-0.5F, 0.0F));
		}
		
		if (entityB->getTag() == Fingers::Entities::ExitDoor) {
			gameComplete = true;
		}
	}
	
	// Weight collisions
	if (entityA->getTag() == Fingers::Entities::Weight) {
		if (entityB->getTag() == Fingers::Entities::Wall) {
			entityA->moveBack();
		}
		
		if (entityB->getTag() == Fingers::Entities::DoorWest) {
			moveToRoom(entityA, Fingers::Rooms::Floor1::Group, Fingers::Rooms::Floor1::StartingRoom, Fingers::Rooms::Floor1::Group, Fingers::Rooms::Floor1::RoomF);

			entityA->translate(MOVE_WEST);
		}
	
		if (entityB->getTag() == Fingers::Entities::DoorEast) {
			moveToRoom(entityA, Fingers::Rooms::Floor1::Group, Fingers::Rooms::Floor1::StartingRoom, Fingers::Rooms::Floor1::Group, Fingers::Rooms::Floor1::RoomG);

			entityA->translate(MOVE_EAST);
		}
	}
}

