#include "GameState.h"

#include <vector>

#include "GameState/GameLoadingProcess.h"
#include "../Logger/Logger.h"

GameState::GameState()
{
	std::vector<Process*> processList;
	
	processList.push_back(new GameLoadingProcess);
	
	setProcessor(new Processor(processList));
	
	Logger& logger(Logger::instance());
	logger.log("Game State Created\n");
}

void GameState::update(const float deltaTime)
{
	updateProcessor(deltaTime);
}