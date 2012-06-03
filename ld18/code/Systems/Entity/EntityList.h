#ifndef _ENTITY_LIST_H_
#define _ENTITY_LIST_H_

#include <list>

class Entity;
class EntityList
{
	public:
		EntityList();
		~EntityList();
		
		//! Adds a new Entity to this List.
		template <typename T_Entity>
		T_Entity* const add();
		
		//! Removes an Entity from this List.
		void remove(Entity* entity);
		
		//! Adds an existing Entity to this List.
		void addToList(Entity* const entity) { entityList_.push_back(entity); }
		
		//! Returns const access to the Entity List.
		const std::list<Entity*>& readList() const { return entityList_; }
		
		//! Returns write access to the Entity List.
		std::list<Entity*>& writeList() { return entityList_; }

	private:
		std::list<Entity*> entityList_;
};

template <typename T_Entity>
T_Entity* const EntityList::add()
{
	entityList_.push_back(new T_Entity);
	return static_cast<T_Entity*>(*(entityList_.rbegin())); // we've just pushed back, so it'll be the one in the last slot we want - the reverse begin.
}

#endif
