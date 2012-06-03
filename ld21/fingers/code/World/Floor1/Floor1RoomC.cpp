#include "Floor1RoomC.h"

#include "../WorldRooms.h"

#include <Maths/Vector3.h>
#include <Maths/Matrix4.h>
#include "../../Entities/Entity.h"
#include "../../Resources/Meshes.h"
#include "../../Resources/Entities.h"
#include <Resources/ResourceManager.h>
#include <Platform/Application.h>

using namespace GLESGAE;

Floor1RoomC::Floor1RoomC()
: Room(Fingers::Rooms::Floor1Id, new Floor1RoomCCollisions)
{
	mOffset = Vector2(-2.4F, 4.8F);
	
	createFloor();
	
	createWall(Vector2(0.0F, -1.2F), Vector2(25.0F, 1.0F));
	createWall(Vector2(0.0F, 1.2F), Vector2(25.0F, 1.0F));
	createWall(Vector2(1.2F, 0.0F), Vector2(1.0F, 25.0F));
	createWall(Vector2(-1.2F, 0.0F), Vector2(1.0F, 25.0F));
	
	createDoor(Vector2(1.2F, 0.0F), Fingers::Entities::DoorWest);
/*
	{ // Stairwell
		locator.resource = Fingers::RoomMeshes::Collidables::StairWell;
		Resource<Entity>& stairs(entityBank.add(Fingers::Entities::Group, Fingers::Entities::Type, new Entity(locator, Entity::RENDER_BOX_COLLIDE, Fingers::Entities::Stairs)));
		stairs->getTransform()->setPosition(Vector3(-1.0F + offset.x(), 1.0F + offset.y(), 0.0F));
		stairs->setBoxSize(Vector2(0.1F, 0.1F));
		stairs->setSphereSize(0.1F);
		mEntityManager.add(stairs);
	}
*/
}

Floor1RoomC::~Floor1RoomC()
{
}
		
void Floor1RoomC::update(const float delta)
{
	mEntityManager.update(delta);
}

void Floor1RoomC::render()
{
	if (true == mVisible)
		mEntityManager.render();
}

void Floor1RoomC::addEntity(const Resource<Entity>& entity)
{
	mEntityManager.add(entity);
}

void Floor1RoomC::removeEntity(const Resource<Entity>& entity)
{
	mEntityManager.remove(entity);
}

