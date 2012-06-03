#include "Floor1RoomD.h"

#include "../WorldRooms.h"

#include <Maths/Vector3.h>
#include <Maths/Matrix4.h>
#include "../../Entities/Entity.h"
#include "../../Resources/Meshes.h"
#include "../../Resources/Entities.h"
#include <Resources/ResourceManager.h>
#include <Platform/Application.h>

using namespace GLESGAE;

Floor1RoomD::Floor1RoomD()
: Room(Fingers::Rooms::Floor1Id, new Floor1RoomDCollisions)
{
	mOffset = Vector2(2.4F, 2.4F);
	
	createFloor();
	
	createWall(Vector2(0.0F, -1.2F), Vector2(25.0F, 1.0F));
	createWall(Vector2(0.0F, 1.2F), Vector2(25.0F, 1.0F));
	createWall(Vector2(1.2F, 0.0F), Vector2(1.0F, 25.0F));
	createWall(Vector2(-1.2F, 0.0F), Vector2(1.0F, 25.0F));
	
	createDoor(Vector2(0.0F, -1.2F), Fingers::Entities::DoorSouth);
	
	createItem(Vector2(0.0F, 0.0F), Vector2(1.0F, 1.0F), Fingers::CollectableMeshes::Group, Fingers::CollectableMeshes::Health, Fingers::Entities::Health);
	createItem(Vector2(-0.8F, 1.0F), Vector2(1.0F, 1.0F), Fingers::PushableMeshes::Group, Fingers::PushableMeshes::StarDiamond, Fingers::Entities::StarDiamond);
}

Floor1RoomD::~Floor1RoomD()
{
}
		
void Floor1RoomD::update(const float delta)
{
	mEntityManager.update(delta);
}

void Floor1RoomD::render()
{
	if (true == mVisible)
		mEntityManager.render();
}

void Floor1RoomD::addEntity(const Resource<Entity>& entity)
{
	mEntityManager.add(entity);
}

void Floor1RoomD::removeEntity(const Resource<Entity>& entity)
{
	mEntityManager.remove(entity);
}

