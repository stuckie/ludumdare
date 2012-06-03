#ifndef _ENTITY_MANAGER_H_
#define _ENTITY_MANAGER_H_

#include <Resources/Resource.h>
#include <list>

#include "CollisionCallback.h"
#include "Entity.h"

class EntityManager
{
	public:
		EntityManager(CollisionCallback* const callback);
	
		/// Add an entity to the manager
		void add(const GLESGAE::Resource<Entity>& entity);
		
		/// Remove an entity
		void remove(const GLESGAE::Resource<Entity>& entity);
		
		/// Update everything
		void update(const float delta);
		
		/// process collisions
		void processCollisions();
		
		/// Render everything
		void render();
		
	protected:
		/// Helper function to remove an Entity from a list
		void removeFromList(const GLESGAE::Resource<Entity>& entity, std::list<GLESGAE::Resource<Entity> >& list);
		
	private:
		EntityManager(const EntityManager&);
		EntityManager& operator=(const EntityManager&);
		
		std::list<GLESGAE::Resource<Entity> > mDrawables;
		std::list<GLESGAE::Resource<Entity> > mCollidables;
		std::list<GLESGAE::Resource<Entity> > mDeletables;
		CollisionCallback* mCallback;
};

#endif

