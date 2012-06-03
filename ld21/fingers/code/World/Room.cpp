#include "Room.h"

#include <Maths/Vector3.h>
#include <Maths/Matrix4.h>
#include "../Entities/Entity.h"
#include "../Resources/Meshes.h"
#include "../Resources/Entities.h"
#include <Resources/ResourceManager.h>
#include <Platform/Application.h>

using namespace GLESGAE;

Room::Room(const unsigned int floorId, CollisionCallback* const collisionCallback)
: mEntityManager(collisionCallback)
, mVisible(false)
, mOffset(0.0F, 0.0F)
, mFloorId(floorId)
{
}

Room::~Room()
{
}

Resource<Entity>& Room::createItem(const Vector2& centre, const Vector2& size, const Resources::Group group, const Resources::Id id, const Fingers::Entities::Tag tag)
{
	ResourceManager* resourceManager(Application::getInstance()->getResourceManager());
	ResourceBank<Entity>& entityBank(resourceManager->getBank<Entity>(Fingers::Entities::Bank, Fingers::Entities::Type));
	
	Resources::Locator locator;
	locator.bank = Fingers::Meshes::Bank;
	locator.group = group;
	locator.resource = id;
	
	Resource<Entity>& entity(entityBank.add(Fingers::Entities::Group, Fingers::Entities::Type, new Entity(locator, Entity::RENDER_BOX_COLLIDE, tag)));
	entity->getTransform()->setPosition(Vector3(centre.x() + mOffset.x(), centre.y() + mOffset.y(), 0.0F));
	entity->getTransform()->setScale(Vector3(size.x(), size.y(), 1.0F));
	entity->setBoxSize(Vector2(0.1F * size.x(), 0.1F * size.y()));
	if (size.x() > size.y())
		entity->setSphereSize(1.0F + (size.x() * 0.01F));
	else
		entity->setSphereSize(1.0F + (size.y() * 0.01F));
		
	mEntityManager.add(entity);
	
	return entity;
}

void Room::createFloor()
{
	ResourceManager* resourceManager(Application::getInstance()->getResourceManager());
	ResourceBank<Entity>& entityBank(resourceManager->getBank<Entity>(Fingers::Entities::Bank, Fingers::Entities::Type));
	
	Resources::Locator locator;
	locator.bank = Fingers::Meshes::Bank;
	locator.group = Fingers::RoomMeshes::Group;
	locator.resource = Fingers::RoomMeshes::Background::Floor;
	
	Resource<Entity>& floor(entityBank.add(Fingers::Entities::Group, Fingers::Entities::Type, new Entity(locator, Entity::RENDER_ONLY, Fingers::Entities::Background)));
	floor->getTransform()->setPosition(Vector3(0.0F + mOffset.x(), 0.0F + mOffset.y(), 0.0F));
	floor->getTransform()->setScale(Vector3(25.0F, 25.0F, 1.0F));
	mEntityManager.add(floor);
}

void Room::createWall(const Vector2& centre, const Vector2& size)
{
	createItem(centre, size, Fingers::RoomMeshes::Group, Fingers::RoomMeshes::Collidables::BlockWall, Fingers::Entities::Wall);
}

void Room::createDoor(const Vector2& position, const Fingers::Entities::Tag tag)
{
	Resource<Entity>& door(createItem(position, Vector2(1.0F, 1.0F), Fingers::RoomMeshes::Group, Fingers::RoomMeshes::Collidables::Door, tag));
	if ((tag == Fingers::Entities::DoorWest) || (tag == Fingers::Entities::DoorEast)) {
		door->rotate(3.14F * 0.5F);
		door->setBoxSize(Vector2(0.15F, 0.2F));
	}
	else if ((tag == Fingers::Entities::DoorNorth) || (tag == Fingers::Entities::DoorSouth))
		door->setBoxSize(Vector2(0.2F, 0.15F));
	
	door->setSphereSize(0.2F);
}

