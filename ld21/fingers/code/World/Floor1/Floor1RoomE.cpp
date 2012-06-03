#include "Floor1RoomE.h"

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

#include <cstdlib>

using namespace GLESGAE;

Floor1RoomE::Floor1RoomE()
: Room(Fingers::Rooms::Floor1Id, new Floor1RoomECollisions)
{
	mOffset = Vector2(-2.4F, 2.4F);
	
	createFloor();
	
	createWall(Vector2(0.0F, -1.2F), Vector2(25.0F, 1.0F));
	createWall(Vector2(0.0F, 1.2F), Vector2(25.0F, 1.0F));
	createWall(Vector2(1.2F, 0.0F), Vector2(1.0F, 25.0F));
	createWall(Vector2(-1.2F, 0.0F), Vector2(1.0F, 25.0F));
	
	createDoor(Vector2(-1.0F, -1.2F), Fingers::Entities::DoorSouth);

	createWall(Vector2(0.0F, 0.5F), Vector2(15.0F, 1.0F));
	{
		Resource<Entity>& camera(createTrap<CameraTrap>(Vector2(0.8F, 0.5F), Vector2(1.0F, 1.0F), Fingers::TrapMeshes::Group, Fingers::TrapMeshes::CameraSight));
		CameraTrap* cameraTrap(const_cast<CameraTrap*>(reinterpret_cast<const CameraTrap*>(&(*camera))));
		std::vector<CameraTrap::Command> path;
		path.push_back(CameraTrap::Command(CameraTrap::TURN_CW, 2.5F, 0.2F, 5.0F));
		cameraTrap->setPath(path);
		cameraTrap->setSphereSize(2.0F);
		cameraTrap->setBoxSize(Vector2(0.2F, 0.2F));
	}
	
	{
		Resource<Entity>& camera(createTrap<CameraTrap>(Vector2(-0.8F, 0.5F), Vector2(1.0F, 1.0F), Fingers::TrapMeshes::Group, Fingers::TrapMeshes::CameraSight));
		CameraTrap* cameraTrap(const_cast<CameraTrap*>(reinterpret_cast<const CameraTrap*>(&(*camera))));
		std::vector<CameraTrap::Command> path;
		path.push_back(CameraTrap::Command(CameraTrap::TURN_CW, 2.5F, 0.2F, 5.0F));
		cameraTrap->setPath(path);
		cameraTrap->setSphereSize(2.0F);
		cameraTrap->setBoxSize(Vector2(0.2F, 0.2F));
	}
	
	createWall(Vector2(-0.25F, -0.5F), Vector2(20.0F, 1.0F));
	{	
		Resource<Entity>& camera(createTrap<CameraTrap>(Vector2(0.8F, -0.5F), Vector2(1.0F, 1.0F), Fingers::TrapMeshes::Group, Fingers::TrapMeshes::CameraSight));
		CameraTrap* cameraTrap(const_cast<CameraTrap*>(reinterpret_cast<const CameraTrap*>(&(*camera))));
		std::vector<CameraTrap::Command> path;
		path.push_back(CameraTrap::Command(CameraTrap::TURN_CCW, 2.5F, 0.2F, 5.0F));
		cameraTrap->setPath(path);
		cameraTrap->setSphereSize(2.0F);
		cameraTrap->setBoxSize(Vector2(0.2F, 0.2F));
	}
	
	createWall(Vector2(0.8F, 0.0F), Vector2(1.0F, 12.0F));
	{ // Bottom Crushers
		{
			Resource<Entity> crusherEntity(createTrap<Crusher>(Vector2(-0.8F, -0.6F), Vector2(1.0F, 1.0F), Fingers::TrapMeshes::Group, Fingers::TrapMeshes::CrusherHead));
			Crusher* crusher(const_cast<Crusher*>(reinterpret_cast<const Crusher*>(&(*crusherEntity))));
			crusher->setSpeed(0.2F + ((rand() % 100) * 0.01F));
		}
		{
			Resource<Entity> crusherEntity(createTrap<Crusher>(Vector2(-0.4F, -0.6F), Vector2(1.0F, 1.0F), Fingers::TrapMeshes::Group, Fingers::TrapMeshes::CrusherHead));
			Crusher* crusher(const_cast<Crusher*>(reinterpret_cast<const Crusher*>(&(*crusherEntity))));
			crusher->setSpeed(0.2F + ((rand() % 100) * 0.01F));
		}
		{
			Resource<Entity> crusherEntity(createTrap<Crusher>(Vector2(-0.0F, -0.6F), Vector2(1.0F, 1.0F), Fingers::TrapMeshes::Group, Fingers::TrapMeshes::CrusherHead));
			Crusher* crusher(const_cast<Crusher*>(reinterpret_cast<const Crusher*>(&(*crusherEntity))));
			crusher->setSpeed(0.2F + ((rand() % 100) * 0.01F));
		}
		{
			Resource<Entity> crusherEntity(createTrap<Crusher>(Vector2(0.4F, -0.6F), Vector2(1.0F, 1.0F), Fingers::TrapMeshes::Group, Fingers::TrapMeshes::CrusherHead));
			Crusher* crusher(const_cast<Crusher*>(reinterpret_cast<const Crusher*>(&(*crusherEntity))));
			crusher->setSpeed(0.2F + ((rand() % 100) * 0.01F));
		}
		{
			Resource<Entity> crusherEntity(createTrap<Crusher>(Vector2(0.8F, -0.8F), Vector2(1.0F, 1.0F), Fingers::TrapMeshes::Group, Fingers::TrapMeshes::CrusherHead));
			Crusher* crusher(const_cast<Crusher*>(reinterpret_cast<const Crusher*>(&(*crusherEntity))));
			crusher->setSpeed(0.2F + ((rand() % 100) * 0.01F));
		}
	}
	
	{ // Top Crushers
		{
			Resource<Entity> crusherEntity(createTrap<Crusher>(Vector2(-0.75F, 0.8F), Vector2(1.0F, 1.0F), Fingers::TrapMeshes::Group, Fingers::TrapMeshes::CrusherHead));
			Crusher* crusher(const_cast<Crusher*>(reinterpret_cast<const Crusher*>(&(*crusherEntity))));
			crusher->setSpeed(0.2F + ((rand() % 100) * 0.01F));
		}
		{
			Resource<Entity> crusherEntity(createTrap<Crusher>(Vector2(-0.35F, 0.8F), Vector2(1.0F, 1.0F), Fingers::TrapMeshes::Group, Fingers::TrapMeshes::CrusherHead));
			Crusher* crusher(const_cast<Crusher*>(reinterpret_cast<const Crusher*>(&(*crusherEntity))));
			crusher->setSpeed(0.2F + ((rand() % 100) * 0.01F));
		}
		{
			Resource<Entity> crusherEntity(createTrap<Crusher>(Vector2(0.05F, 0.8F), Vector2(1.0F, 1.0F), Fingers::TrapMeshes::Group, Fingers::TrapMeshes::CrusherHead));
			Crusher* crusher(const_cast<Crusher*>(reinterpret_cast<const Crusher*>(&(*crusherEntity))));
			crusher->setSpeed(0.2F + ((rand() % 100) * 0.01F));
		}
		{
			Resource<Entity> crusherEntity(createTrap<Crusher>(Vector2(0.45F, 0.8F), Vector2(1.0F, 1.0F), Fingers::TrapMeshes::Group, Fingers::TrapMeshes::CrusherHead));
			Crusher* crusher(const_cast<Crusher*>(reinterpret_cast<const Crusher*>(&(*crusherEntity))));
			crusher->setSpeed(0.2F + ((rand() % 100) * 0.01F));
		}
		{
			Resource<Entity> crusherEntity(createTrap<Crusher>(Vector2(0.8F, 0.8F), Vector2(1.0F, 1.0F), Fingers::TrapMeshes::Group, Fingers::TrapMeshes::CrusherHead));
			Crusher* crusher(const_cast<Crusher*>(reinterpret_cast<const Crusher*>(&(*crusherEntity))));
			crusher->setSpeed(0.2F + ((rand() % 100) * 0.01F));
		}
	}

	createItem(Vector2(0.0F, 0.0F), Vector2(1.0F, 1.0F), Fingers::CollectableMeshes::Group, Fingers::CollectableMeshes::Gems, Fingers::Entities::Gem);
	{ // Spike Traps in the centre
		createTrap<Spikes>(Vector2(-0.2F, 0.25F), Vector2(1.0F, 1.0F), Fingers::TrapMeshes::Group, Fingers::TrapMeshes::SpikesUp);
		createTrap<Spikes>(Vector2(-0.2F, 0.0F), Vector2(1.0F, 1.0F), Fingers::TrapMeshes::Group, Fingers::TrapMeshes::SpikesUp);
		createTrap<Spikes>(Vector2(-0.2F, -0.25F), Vector2(1.0F, 1.0F), Fingers::TrapMeshes::Group, Fingers::TrapMeshes::SpikesUp);
		
		createTrap<Spikes>(Vector2(-0.4F, 0.25F), Vector2(1.0F, 1.0F), Fingers::TrapMeshes::Group, Fingers::TrapMeshes::SpikesUp);
		createTrap<Spikes>(Vector2(-0.4F, 0.0F), Vector2(1.0F, 1.0F), Fingers::TrapMeshes::Group, Fingers::TrapMeshes::SpikesUp);
		createTrap<Spikes>(Vector2(-0.4F, -0.25F), Vector2(1.0F, 1.0F), Fingers::TrapMeshes::Group, Fingers::TrapMeshes::SpikesUp);

		createTrap<Spikes>(Vector2(-0.6F, 0.25F), Vector2(1.0F, 1.0F), Fingers::TrapMeshes::Group, Fingers::TrapMeshes::SpikesUp);
		createTrap<Spikes>(Vector2(-0.6F, 0.0F), Vector2(1.0F, 1.0F), Fingers::TrapMeshes::Group, Fingers::TrapMeshes::SpikesUp);
		createTrap<Spikes>(Vector2(-0.6F, -0.25F), Vector2(1.0F, 1.0F), Fingers::TrapMeshes::Group, Fingers::TrapMeshes::SpikesUp);
	}
}

Floor1RoomE::~Floor1RoomE()
{
}
		
void Floor1RoomE::update(const float delta)
{
	mEntityManager.update(delta);
}

void Floor1RoomE::render()
{
	if (true == mVisible)
		mEntityManager.render();
}

void Floor1RoomE::addEntity(const Resource<Entity>& entity)
{
	mEntityManager.add(entity);
}

void Floor1RoomE::removeEntity(const Resource<Entity>& entity)
{
	mEntityManager.remove(entity);
}

