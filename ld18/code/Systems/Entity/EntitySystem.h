#ifndef _ENTITY_SYSTEM_H_
#define _ENTITY_SYSTEM_H_

#include <cassert>
#include <map>
#include <string>
#include "EntityList.h"

class Entity;
class EntitySystem
{
	public:
		~EntitySystem();
	
		//! Creates or returns the current active instance.
		static EntitySystem& instance();
		
		//! Add a new Entity of the specified type.
		template <typename T_Entity>
		T_Entity* const add(const std::string& listName);
		
		//! Creates a list of the given name
		void createList(const std::string& listName);
		
		//! Returns an entire list of Entities.
		EntityList* const getList(const std::string& listName);
		
		//! Adds an Entity to a List.
		void addToList(Entity* const entity, const std::string& listName);
		
		//! Removes an Entity
		void remove(Entity* entity, const std::string& listName);
		
	private:
		EntitySystem();
		
		static EntitySystem* instance_;	//!< Active instance
		
		std::map<std::string, EntityList*> entityList_;
		
};

template <typename T_Entity>
T_Entity* const EntitySystem::add(const std::string& listName)
{
	std::map<std::string, EntityList*>::iterator entityList(entityList_.find(listName));
	
	assert(entityList != entityList_.end());
	return entityList->second->add<T_Entity>();
}

#endif
