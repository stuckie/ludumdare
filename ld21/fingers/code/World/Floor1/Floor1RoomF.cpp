#include "Floor1RoomF.h"

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

Resources::Id Floor1RoomF::LeftSpikes = Resources::INVALID;
Resources::Id Floor1RoomF::RightSpikes = Resources::INVALID;

Floor1RoomF::Floor1RoomF()
: Room(Fingers::Rooms::Floor1Id, new Floor1RoomFCollisions)
{
	mOffset = Vector2(2.4F, 0.0F);
	
	createFloor();
	
	createWall(Vector2(0.0F, -1.2F), Vector2(25.0F, 1.0F));
	createWall(Vector2(0.0F, 1.2F), Vector2(25.0F, 1.0F));
	createWall(Vector2(1.2F, 0.0F), Vector2(1.0F, 25.0F));
	createWall(Vector2(-1.2F, 0.0F), Vector2(1.0F, 25.0F));
	
	createDoor(Vector2(-1.2F, 0.0F), Fingers::Entities::DoorEast);;
	createDoor(Vector2(0.0F, 1.2F), Fingers::Entities::DoorNorth);
	
	createItem(Vector2(0.0F, 1.1F), Vector2(1.0F, 1.0F), Fingers::CollectableMeshes::Group, Fingers::CollectableMeshes::Gems, Fingers::Entities::Gem);
	
	{
		{
			Resource<Entity>& trapEntity(createTrap<Spikes>(Vector2(-0.1F, 1.0F), Vector2(1.0F, 1.0F), Fingers::TrapMeshes::Group, Fingers::TrapMeshes::SpikesDown));
			Spikes* spikes(const_cast<Spikes*>(reinterpret_cast<const Spikes*>(&(*trapEntity))));
			spikes->setManual(true);
			spikes->setState(Spikes::UP);
			RightSpikes = trapEntity.getId();
		}
		{
			Resource<Entity>& trapEntity(createTrap<Spikes>(Vector2(0.1F, 1.0F), Vector2(1.0F, 1.0F), Fingers::TrapMeshes::Group, Fingers::TrapMeshes::SpikesDown));
			Spikes* spikes(const_cast<Spikes*>(reinterpret_cast<const Spikes*>(&(*trapEntity))));
			spikes->setManual(true);
			spikes->setState(Spikes::UP);
			LeftSpikes = trapEntity.getId();
		}
	}
	
	createWall(Vector2(-0.7F, 0.2F), Vector2(1.0F, 20.0F));
	
	createItem(Vector2(0.8F, 0.8F), Vector2(1.0F, 1.0F), Fingers::PushableMeshes::Group, Fingers::PushableMeshes::Weight, Fingers::Entities::Weight);
	
	createTrap<PressurePad>(Vector2(-1.0F, 0.8F), Vector2(1.0F, 1.0F), Fingers::TrapMeshes::Group, Fingers::TrapMeshes::PressurePadUp);
	
	{
		Resource<Entity>& camera(createTrap<CameraTrap>(Vector2(0.75F, 0.25F), Vector2(1.5F, 1.5F), Fingers::TrapMeshes::Group, Fingers::TrapMeshes::CameraSight));
		CameraTrap* cameraTrap(const_cast<CameraTrap*>(reinterpret_cast<const CameraTrap*>(&(*camera))));
		std::vector<CameraTrap::Command> path;
		path.push_back(CameraTrap::Command(CameraTrap::TURN_CW, 2.0F, 0.2F, 5.0F));
		cameraTrap->setPath(path);
	}
	{
		Resource<Entity>& camera(createTrap<CameraTrap>(Vector2(0.0F, 0.5F), Vector2(1.5F, 1.5F), Fingers::TrapMeshes::Group, Fingers::TrapMeshes::CameraSight));
		CameraTrap* cameraTrap(const_cast<CameraTrap*>(reinterpret_cast<const CameraTrap*>(&(*camera))));
		std::vector<CameraTrap::Command> path;
		path.push_back(CameraTrap::Command(CameraTrap::TURN_CW, 2.5F, 0.2F, 5.0F));
		cameraTrap->setPath(path);
	}
	{
		Resource<Entity>& camera(createTrap<CameraTrap>(Vector2(0.5F, -0.5F), Vector2(1.5F, 1.5F), Fingers::TrapMeshes::Group, Fingers::TrapMeshes::CameraSight));
		CameraTrap* cameraTrap(const_cast<CameraTrap*>(reinterpret_cast<const CameraTrap*>(&(*camera))));
		std::vector<CameraTrap::Command> path;
		path.push_back(CameraTrap::Command(CameraTrap::TURN_CCW, 2.5F, 0.2F, 5.0F));
		cameraTrap->setPath(path);
	}
	{
		Resource<Entity>& camera(createTrap<CameraTrap>(Vector2(-0.25F, -0.75F), Vector2(1.5F, 1.5F), Fingers::TrapMeshes::Group, Fingers::TrapMeshes::CameraSight));
		CameraTrap* cameraTrap(const_cast<CameraTrap*>(reinterpret_cast<const CameraTrap*>(&(*camera))));
		std::vector<CameraTrap::Command> path;
		path.push_back(CameraTrap::Command(CameraTrap::TURN_CCW, 2.0F, 0.2F, 5.0F));
		cameraTrap->setPath(path);
	}
	
}

Floor1RoomF::~Floor1RoomF()
{
}
		
void Floor1RoomF::update(const float delta)
{
	mEntityManager.update(delta);
}

void Floor1RoomF::render()
{
	if (true == mVisible)
		mEntityManager.render();
}

void Floor1RoomF::addEntity(const Resource<Entity>& entity)
{
	mEntityManager.add(entity);
}

void Floor1RoomF::removeEntity(const Resource<Entity>& entity)
{
	mEntityManager.remove(entity);
}

