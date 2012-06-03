#ifndef _STATE_MANAGER_H_
#define _STATE_MANAGER_H_

#include <map>
#include <string>

class State;
class StateManager
{
	public:
		~StateManager();
		
		//! Creates or returns the current active instance.
		static StateManager& instance();
		
		//! Adds a new State to manage.
		template <typename T_State>
		void add(const std::string& name);
		
		//! Launches a State - sets it as the current Active State.
		void launch(const std::string& name);
		
		//! Updates the current State with deltaTime.
		void update(const float deltaTime);
		
		//! Removes a State.
		void remove(const std::string& name);
		
		//! Does this State Manager have any States?
		const bool hasStates() const;
		
		//! Retrieves a state of this Type.. pointer check!
		template <typename T_State>
		T_State* const getState(const std::string& name);
		
	private:
		StateManager();
		
		std::map<std::string, State*> stateMap_;	//!< Map of all States.
		State* currentState_;						//!< Current Active State.
		static StateManager* instance_; 			//!< Active instance of this class.
};

template <typename T_State>
void StateManager::add(const std::string& name)
{
	stateMap_[name] = new T_State;
}

template <typename T_State>
T_State* const StateManager::getState(const std::string& name)
{
	return static_cast<T_State*>(stateMap_[name]);
}

#endif
