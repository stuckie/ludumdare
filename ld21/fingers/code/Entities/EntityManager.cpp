#include "EntityManager.h"

#include <Platform/Application.h>
#include <Graphics/GraphicsSystem.h>
#include <Time/Clock.h>

#include "Entity.h"

using namespace GLESGAE;

EntityManager::EntityManager(CollisionCallback* const callback)
: mDrawables()
, mCollidables()
, mDeletables()
, mCallback(callback)
{
}

void EntityManager::add(const Resource<Entity>& entity)
{
	switch (entity->getType()) {
		case Entity::RENDER_ONLY:
			mDrawables.push_back(entity);
			break;
		case Entity::RENDER_SPHERE_COLLIDE:
		case Entity::RENDER_BOX_COLLIDE:
			mDrawables.push_back(entity);
		case Entity::SPHERE_COLLIDE:
		case Entity::BOX_COLLIDE:
			mCollidables.push_back(entity);
		default:
			break;
	};
}

void EntityManager::remove(const Resource<Entity>& entity)
{
	mDeletables.push_back(entity);
}

void EntityManager::update(const float delta)
{
	for (std::list<Resource<Entity> >::const_iterator entity(mDrawables.begin()); entity != mDrawables.end(); ++entity)
		(*entity)->update(delta);
		
	processCollisions();
}

void EntityManager::processCollisions()
{
	for (std::list<Resource<Entity> >::iterator entityA(mCollidables.begin()); entityA != mCollidables.end(); ++entityA) {
		for (std::list<Resource<Entity> >::iterator entityB(mCollidables.begin()); entityB != mCollidables.end(); ++entityB) {
			if (true == (*entityA)->collide(*entityB))
				mCallback->collide((*entityA), (*entityB));
		}
	}
	
	for (std::list<Resource<Entity> >::iterator itr(mDeletables.begin()); itr != mDeletables.end(); ++itr) {
		Resource<Entity>& entity(*itr);
		switch (entity->getType()) {
			case Entity::RENDER_ONLY:
				removeFromList(entity, mDrawables);
				break;
			case Entity::RENDER_SPHERE_COLLIDE:
			case Entity::RENDER_BOX_COLLIDE:
				removeFromList(entity, mDrawables);
			case Entity::SPHERE_COLLIDE:
			case Entity::BOX_COLLIDE:
				removeFromList(entity, mCollidables);
			default:
				break;
		};
	}
	
	mDeletables.clear();
}

void EntityManager::render()
{
	for (std::list<Resource<Entity> >::const_iterator entity(mDrawables.begin()); entity != mDrawables.end(); ++entity) {
		(*entity)->render();
	}
}

void EntityManager::removeFromList(const Resource<Entity>& entity, std::list<Resource<Entity> >& list)
{
	for (std::list<Resource<Entity> >::iterator deletion(list.begin()); deletion != list.end(); ++deletion) {
		if ((*deletion) == entity) {
			list.erase(deletion);
			return;
		}
	}
}

