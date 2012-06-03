#include "MenuState.h"

#include <vector>

#include "MenuState/MenuLoadingProcess.h"
#include "../Logger/Logger.h"

MenuState::MenuState()
{
	std::vector<Process*> processList;
	
	processList.push_back(new MenuLoadingProcess);
	
	setProcessor(new Processor(processList));
	
	Logger& logger(Logger::instance());
	logger.log("Menu State Created\n");
}

void MenuState::update(const float deltaTime)
{
	updateProcessor(deltaTime);
}