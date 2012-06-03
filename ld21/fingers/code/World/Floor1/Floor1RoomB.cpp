#include "Floor1RoomB.h"

#include "../WorldRooms.h"

#include <Maths/Vector3.h>
#include <Maths/Matrix4.h>
#include "../../Entities/Entity.h"
#include "../../Resources/Meshes.h"
#include "../../Resources/Entities.h"
#include <Resources/ResourceManager.h>
#include <Platform/Application.h>

using namespace GLESGAE;

Floor1RoomB::Floor1RoomB()
: Room(Fingers::Rooms::Floor1Id, new Floor1RoomBCollisions)
{
	mOffset = Vector2(0.0F, 4.8F);
	
	createFloor();
	
	createWall(Vector2(0.0F, -1.2F), Vector2(25.0F, 1.0F));
	createWall(Vector2(0.0F, 1.2F), Vector2(25.0F, 1.0F));
	createWall(Vector2(1.2F, 0.0F), Vector2(1.0F, 25.0F));
	createWall(Vector2(-1.2F, 0.0F), Vector2(1.0F, 25.0F));
	
	createDoor(Vector2(-1.2F, 0.0F), Fingers::Entities::DoorEast);
	createDoor(Vector2(1.2F, 0.0F), Fingers::Entities::DoorWest);
}

Floor1RoomB::~Floor1RoomB()
{
}
		
void Floor1RoomB::update(const float delta)
{
	mEntityManager.update(delta);
}

void Floor1RoomB::render()
{
	if (true == mVisible)
		mEntityManager.render();
}

void Floor1RoomB::addEntity(const Resource<Entity>& entity)
{
	mEntityManager.add(entity);
}

void Floor1RoomB::removeEntity(const Resource<Entity>& entity)
{
	mEntityManager.remove(entity);
}

