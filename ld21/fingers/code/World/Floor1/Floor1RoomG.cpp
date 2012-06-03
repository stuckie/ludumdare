#include "Floor1RoomG.h"

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

Floor1RoomG::Floor1RoomG()
: Room(Fingers::Rooms::Floor1Id, new Floor1RoomGCollisions)
{
	mOffset = Vector2(-2.4F, 0.0F);
		
	createFloor();
	
	createWall(Vector2(0.0F, -1.2F), Vector2(25.0F, 1.0F));
	createWall(Vector2(0.0F, 1.2F), Vector2(25.0F, 1.0F));
	createWall(Vector2(1.2F, 0.0F), Vector2(1.0F, 25.0F));
	createWall(Vector2(-1.2F, 0.0F), Vector2(1.0F, 25.0F));
	
	createDoor(Vector2(1.2F, 0.0F), Fingers::Entities::DoorWest);
	createDoor(Vector2(-1.0F, 1.2F), Fingers::Entities::DoorNorth);


	createTrap<Spikes>(Vector2(-0.6F, -0.4F), Vector2(1.0F, 1.0F), Fingers::TrapMeshes::Group, Fingers::TrapMeshes::SpikesUp);
	createTrap<Spikes>(Vector2(-0.6F, -0.6F), Vector2(1.0F, 1.0F), Fingers::TrapMeshes::Group, Fingers::TrapMeshes::SpikesUp);
	createTrap<Spikes>(Vector2(-0.6F, -0.8F), Vector2(1.0F, 1.0F), Fingers::TrapMeshes::Group, Fingers::TrapMeshes::SpikesUp);
	createTrap<Spikes>(Vector2(-0.8F, -0.4F), Vector2(1.0F, 1.0F), Fingers::TrapMeshes::Group, Fingers::TrapMeshes::SpikesUp);
	createTrap<Spikes>(Vector2(-0.8F, -0.6F), Vector2(1.0F, 1.0F), Fingers::TrapMeshes::Group, Fingers::TrapMeshes::SpikesUp);
	createTrap<Spikes>(Vector2(-0.8F, -0.8F), Vector2(1.0F, 1.0F), Fingers::TrapMeshes::Group, Fingers::TrapMeshes::SpikesUp);
	createTrap<Spikes>(Vector2(-1.0F, -0.4F), Vector2(1.0F, 1.0F), Fingers::TrapMeshes::Group, Fingers::TrapMeshes::SpikesUp);
	createTrap<Spikes>(Vector2(-1.0F, -0.6F), Vector2(1.0F, 1.0F), Fingers::TrapMeshes::Group, Fingers::TrapMeshes::SpikesUp);
	createTrap<Spikes>(Vector2(-1.0F, -0.8F), Vector2(1.0F, 1.0F), Fingers::TrapMeshes::Group, Fingers::TrapMeshes::SpikesUp);
	
	createItem(Vector2(-0.9F, -0.9F), Vector2(1.0F, 1.0F), Fingers::CollectableMeshes::Group, Fingers::CollectableMeshes::Gems, Fingers::Entities::Gem);

	{
		createWall(Vector2(0.5F, 0.3F), Vector2(1.0F, 18.75F));
		Resource<Entity>& camera(createTrap<CameraTrap>(Vector2(0.5F, -0.7F), Vector2(1.0F, 1.0F), Fingers::TrapMeshes::Group, Fingers::TrapMeshes::CameraSight));
		CameraTrap* cameraTrap(const_cast<CameraTrap*>(reinterpret_cast<const CameraTrap*>(&(*camera))));
		std::vector<CameraTrap::Command> path;
		path.push_back(CameraTrap::Command(CameraTrap::TURN_CW, 2.5F, 0.2F, 5.0F));
		cameraTrap->setPath(path);
		cameraTrap->setSphereSize(2.0F);
		cameraTrap->setBoxSize(Vector2(0.2F, 0.2F));
	}

	{	
		createWall(Vector2(-0.5F, -0.3F), Vector2(1.0F, 18.75F));
		Resource<Entity>& camera(createTrap<CameraTrap>(Vector2(-0.5F, 0.7F), Vector2(1.0F, 1.0F), Fingers::TrapMeshes::Group, Fingers::TrapMeshes::CameraSight));
		CameraTrap* cameraTrap(const_cast<CameraTrap*>(reinterpret_cast<const CameraTrap*>(&(*camera))));
		std::vector<CameraTrap::Command> path;
		path.push_back(CameraTrap::Command(CameraTrap::TURN_CCW, 2.5F, 0.2F, 5.0F));
		cameraTrap->setPath(path);
		cameraTrap->setSphereSize(2.0F);
		cameraTrap->setBoxSize(Vector2(0.2F, 0.2F));
	}
}

Floor1RoomG::~Floor1RoomG()
{
}
		
void Floor1RoomG::update(const float delta)
{
	mEntityManager.update(delta);
}

void Floor1RoomG::render()
{
	if (true == mVisible)
		mEntityManager.render();
}

void Floor1RoomG::addEntity(const Resource<Entity>& entity)
{
	mEntityManager.add(entity);
}

void Floor1RoomG::removeEntity(const Resource<Entity>& entity)
{
	mEntityManager.remove(entity);
}

