#include "PhysicsSystem.h"

#include <cmath>

#include "../Entity/EntitySystem.h"
#include "../Entity/EntityList.h"
#include "../../Entities/Entity.h"
#include "../../Entities/GrappleHook.h"
#include "../../Objects/Math.h"

PhysicsSystem* PhysicsSystem::instance_ = 0;

PhysicsSystem& PhysicsSystem::instance()
{
	if (0 == instance_)
		instance_ = new PhysicsSystem;
		
	return *instance_;		
}

PhysicsSystem::PhysicsSystem()
{
	
}

PhysicsSystem::~PhysicsSystem()
{
	delete instance_;
	instance_ = 0;
}

void PhysicsSystem::update(const float deltaTime)
{	
	EntitySystem& entitySystem(EntitySystem::instance());
	EntityList* entityList(entitySystem.getList("Movable"));
	
	std::list<Entity*> movableList(entityList->writeList());
	for (std::list<Entity*>::iterator entity(movableList.begin()); entity != movableList.end(); ++entity) {
		(*entity)->writePosition() = Vector2D((*entity)->readPosition().x_ + ((*entity)->readVelocity().x_ * deltaTime)
											, (*entity)->readPosition().y_ - ((*entity)->readVelocity().y_ * deltaTime));
		
		if ((*entity)->readPosition().x_ < 0.0F)
			(*entity)->writeVelocity().x_ = - (*entity)->readVelocity().x_;
			
		if ((*entity)->readPosition().y_ < 0.0F)
			(*entity)->writeVelocity().y_ = - (*entity)->readVelocity().y_;
			
		if ((*entity)->readPosition().x_ > 640.0F)
			(*entity)->writeVelocity().x_ = - (*entity)->readVelocity().x_;
			
		if ((*entity)->readPosition().y_ > 480.0F)
			(*entity)->writeVelocity().y_ = - (*entity)->readVelocity().y_;
	}
											
	entityList = entitySystem.getList("Collidable");
	std::list<Entity*> collidableList(entityList->writeList());
	for (std::list<Entity*>::iterator entity(collidableList.begin()); entity != collidableList.end(); ++entity) {
		for (std::list<Entity*>::iterator collidable(collidableList.begin()); collidable != collidableList.end(); ++collidable) {
			if ((*entity) == (*collidable))
				continue;
				
			if (true == (*entity)->checkCollision(*collidable)) {
				(*entity)->writeVelocity() = Vector2D(-((*entity)->readVelocity().x_ * 0.98F), -((*entity)->readVelocity().y_ * 0.98F));
				(*entity)->setHealth((*entity)->getHealth() - 10U);
			}
		}
	}
	
	entityList = entitySystem.getList("Ship");
	std::list<Entity*> playerList(entityList->writeList());
	for (std::list<Entity*>::iterator entity(playerList.begin()); entity != playerList.end(); ++entity) {
		(*entity)->writeVelocity().x_ = (*entity)->readVelocity().x_ * 0.98F;
		(*entity)->writeVelocity().y_ = (*entity)->readVelocity().y_ * 0.98F;
	}
	
	entityList = entitySystem.getList("Grapple");
	std::list<Entity*> grappleList(entityList->writeList());
	for (std::list<Entity*>::iterator entity(grappleList.begin()); entity != grappleList.end(); ++entity) {
		static_cast<GrappleHook*>((*entity))->update(deltaTime);
	}
}
