#include "StartingRoom.h"

#include "../WorldRooms.h"

#include <Maths/Vector3.h>
#include <Maths/Matrix4.h>
#include "../../Entities/Entity.h"
#include "../../Entities/TrapDoor.h"
#include "../../Entities/Spikes.h"
#include "../../Entities/CameraTrap.h"
#include "../../Entities/PressurePad.h"
#include "../../Resources/Meshes.h"
#include "../../Resources/Entities.h"
#include "../../Entities/Crusher.h"
#include <Resources/ResourceManager.h>
#include <Platform/Application.h>

using namespace GLESGAE;

StartingRoom::StartingRoom()
: Room(Fingers::Rooms::Floor1Id, new StartingRoomCollisions)
{
	createFloor();
	
	createWall(Vector2(0.0F, -1.2F), Vector2(25.0F, 1.0F));
	createWall(Vector2(0.0F, 1.2F), Vector2(25.0F, 1.0F));
	createWall(Vector2(1.2F, 0.0F), Vector2(1.0F, 25.0F));
	createWall(Vector2(-1.2F, 0.0F), Vector2(1.0F, 25.0F));
	
	createDoor(Vector2(-1.2F, 0.0F), Fingers::Entities::DoorEast);
	createDoor(Vector2(1.2F, 0.0F), Fingers::Entities::DoorWest);
	
	createItem(Vector2(0.0F, -1.2F), Vector2(1.5F, 1.5F), Fingers::RoomMeshes::Group, Fingers::RoomMeshes::Collidables::ExitDoor, Fingers::Entities::ExitDoor);
	createItem(Vector2(0.9F, 0.9F), Vector2(1.0F, 1.0F), Fingers::CollectableMeshes::Group, Fingers::CollectableMeshes::Gems, Fingers::Entities::Gem);

	createTrap<Spikes>(Vector2(0.9F, 0.9F), Vector2(1.0F, 1.0F), Fingers::TrapMeshes::Group, Fingers::TrapMeshes::SpikesUp);
	Resource<Entity>& camera(createTrap<CameraTrap>(Vector2(0.9F, 0.9F), Vector2(1.0F, 1.0F), Fingers::TrapMeshes::Group, Fingers::TrapMeshes::CameraSight));
	CameraTrap* cameraTrap(const_cast<CameraTrap*>(reinterpret_cast<const CameraTrap*>(&(*camera))));
	std::vector<CameraTrap::Command> path;
	path.push_back(CameraTrap::Command(CameraTrap::TURN_CW, 5.0F, 0.2F, 5.0F));
	cameraTrap->setPath(path);
}

StartingRoom::~StartingRoom()
{
}
		
void StartingRoom::update(const float delta)
{
	mEntityManager.update(delta);
}

void StartingRoom::render()
{
	if (true == mVisible)
		mEntityManager.render();
}

void StartingRoom::addEntity(const Resource<Entity>& entity)
{
	mEntityManager.add(entity);
}

void StartingRoom::removeEntity(const Resource<Entity>& entity)
{
	mEntityManager.remove(entity);
}

