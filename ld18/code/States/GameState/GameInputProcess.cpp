#include "GameInputProcess.h"

#include "../../Managers/StateManager.h"
#include "../../Systems/Input/InputSystem.h"
#include "../GameState.h"

const Process::Return GameInputProcess::update(const float deltaTime)
{	
	InputSystem& inputSystem(InputSystem::instance());
	inputSystem.update();
	
	if (inputSystem.hasQuit()) {
		StateManager& stateManager(StateManager::instance());
		stateManager.remove("GameState");
		stateManager.remove("MenuState");
		
		return Process::STOP;
	}
	
	return Process::SUCCESS;
}