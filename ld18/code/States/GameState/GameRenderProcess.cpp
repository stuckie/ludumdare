#include "GameRenderProcess.h"

#include "../../Managers/StateManager.h"
#include "../../Systems/Graphics/GraphicsSystem.h"
#include "../GameState.h"

const Process::Return GameRenderProcess::update(const float deltaTime)
{
	StateManager& stateManager(StateManager::instance());
	GameState* gameState(stateManager.getState<GameState>("GameState"));
	
	GraphicsSystem& graphicsSystem(GraphicsSystem::instance());
	graphicsSystem.render(gameState->readGraphicsCamera());
	
	return Process::SUCCESS;
}