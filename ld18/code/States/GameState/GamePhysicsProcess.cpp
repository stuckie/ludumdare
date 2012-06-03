#include "GamePhysicsProcess.h"

#include "../../Systems/Physics/PhysicsSystem.h"

const Process::Return GamePhysicsProcess::update(const float deltaTime)
{
	PhysicsSystem& physicsSystem(PhysicsSystem::instance());
	physicsSystem.update(deltaTime);
	
	return Process::SUCCESS;
}