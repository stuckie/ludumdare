#include "EntityList.h"

#include "../../Entities/Entity.h"

EntityList::EntityList()
{
	
}

EntityList::~EntityList()
{
	for (std::list<Entity*>::iterator itr(entityList_.begin()); itr != entityList_.end(); ++itr)
		if (0 != (*itr)) {
			delete (*itr);
			(*itr) = 0;
		}
}

void EntityList::remove(Entity* entity)
{
	for (std::list<Entity*>::iterator itr(entityList_.begin()); itr != entityList_.end(); ++itr) {
		if ((*itr) == entity) {
			entityList_.erase(itr);
			return;
		}
	}
}
