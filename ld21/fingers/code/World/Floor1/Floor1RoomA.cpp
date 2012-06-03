#include "Floor1RoomA.h"

#include "../WorldRooms.h"

#include <Maths/Vector3.h>
#include <Maths/Matrix4.h>
#include "../../Entities/Entity.h"
#include "../../Resources/Meshes.h"
#include "../../Resources/Entities.h"
#include <Resources/ResourceManager.h>
#include <Platform/Application.h>

using namespace GLESGAE;

Floor1RoomA::Floor1RoomA()
: Room(Fingers::Rooms::Floor1Id, new Floor1RoomACollisions)
{
	mOffset = Vector2(2.4F, 4.8F);
	
	createFloor();
	
	createWall(Vector2(0.0F, -1.2F), Vector2(25.0F, 1.0F));
	createWall(Vector2(0.0F, 1.2F), Vector2(25.0F, 1.0F));
	createWall(Vector2(1.2F, 0.0F), Vector2(1.0F, 25.0F));
	createWall(Vector2(-1.2F, 0.0F), Vector2(1.0F, 25.0F));
	
	createDoor(Vector2(-1.2F, 0.0F), Fingers::Entities::DoorEast);
	createDoor(Vector2(0.0F, -1.2F), Fingers::Entities::DoorSouth);
}

Floor1RoomA::~Floor1RoomA()
{
}
		
void Floor1RoomA::update(const float delta)
{
	mEntityManager.update(delta);
}

void Floor1RoomA::render()
{
	if (true == mVisible)
		mEntityManager.render();
}

void Floor1RoomA::addEntity(const Resource<Entity>& entity)
{
	mEntityManager.add(entity);
}

void Floor1RoomA::removeEntity(const Resource<Entity>& entity)
{
	mEntityManager.remove(entity);
}

