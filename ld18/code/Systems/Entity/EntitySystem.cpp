#include "EntitySystem.h"

#include <cassert>

EntitySystem* EntitySystem::instance_ = 0;

EntitySystem& EntitySystem::instance()
{
	if (0 == instance_)
		instance_ = new EntitySystem;
		
	return *instance_;		
}

EntitySystem::EntitySystem()
{
	
}

EntitySystem::~EntitySystem()
{
	for (std::map<std::string, EntityList*>::iterator itr(entityList_.begin()); itr != entityList_.end(); ++itr)
		delete itr->second;
	
	delete instance_;
	instance_ = 0;
}


void EntitySystem::remove(Entity* entity, const std::string& listName)
{
	std::map<std::string, EntityList*>::iterator entityList(entityList_.find(listName));
	
	assert(entityList != entityList_.end());
	entityList->second->remove(entity);
}

void EntitySystem::createList(const std::string& listName)
{
	std::map<std::string, EntityList*>::iterator entityList(entityList_.find(listName));
	
	assert(entityList == entityList_.end());
	entityList_[listName] = new EntityList;
}
		
EntityList* const EntitySystem::getList(const std::string& listName)
{
	std::map<std::string, EntityList*>::iterator entityList(entityList_.find(listName));
	
	assert(entityList != entityList_.end());
	return entityList->second;
}
		
void EntitySystem::addToList(Entity* const entity, const std::string& listName)
{
	std::map<std::string, EntityList*>::iterator entityList(entityList_.find(listName));
	
	assert(entityList != entityList_.end());
	entityList->second->addToList(entity);
}
