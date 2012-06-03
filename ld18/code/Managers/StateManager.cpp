#include "StateManager.h"

#include <cassert>
#include <map>
#include <string>

#include "../States/State.h"

StateManager* StateManager::instance_ = 0;

StateManager& StateManager::instance()
{
	if (0 == instance_)
		instance_ = new StateManager;
		
	return *instance_;		
}

StateManager::StateManager()
: stateMap_()
, currentState_(0)
{
	
}

StateManager::~StateManager()
{
	delete instance_;
	instance_ = 0;
	
	currentState_ = 0;
}

void StateManager::launch(const std::string& name)
{
	std::map<std::string, State*>::iterator state(stateMap_.find(name));
	
	assert(state != stateMap_.end());
	currentState_ = state->second;
}

void StateManager::update(const float deltaTime)
{
	assert(currentState_);
	currentState_->update(deltaTime);
}

void StateManager::remove(const std::string& name)
{
	std::map<std::string, State*>::iterator state(stateMap_.find(name));
	
	assert(state != stateMap_.end());
	
	if (currentState_ == state->second)
		currentState_ = 0;
		
	stateMap_.erase(state);
}

const bool StateManager::hasStates() const
{
	return (!stateMap_.empty());
}
