#include <string>
#include <iostream>

#include "Logger/Logger.h"
#include "Managers/ConfigManager.h"
#include "Managers/StateManager.h"
#include "States/MenuState.h"
#include "States/GameState.h"
#include "Systems/Entity/EntitySystem.h"
#include "Systems/Graphics/GraphicsSystem.h"
#include "Timer/Timer.h"

int main(int argc, char* argv[])
{
	// Setup and initialise the Logger
	Logger& logger(Logger::instance());
	//logger.setFile(".html", Logger::LOG_FILE_HTML);
	//logger.setOutput(Logger::LOG_OUTPUT_FILE_AND_TERMINAL);
	logger.setOutput(Logger::LOG_OUTPUT_SILENT);
	//logger.setType(Logger::LOG_TYPE_INFO);
	
	// Check the Config Manager and get it to parse the configuration files.
	ConfigManager& configManager(ConfigManager::instance());
	configManager.loadConfig();
	
	// Start up the Graphics System.
	GraphicsSystem& graphicsSystem(GraphicsSystem::instance());
	graphicsSystem.initialise(640U, 480U, 32U);
	
	// Start and setup the Entity System with some lists.
	EntitySystem& entitySystem(EntitySystem::instance());
	entitySystem.createList("Player");
	entitySystem.createList("Enemy");
	entitySystem.createList("Renderable");
	entitySystem.createList("Movable");
	entitySystem.createList("Collidable");
	entitySystem.createList("Grapple");
	entitySystem.createList("Ship");
	
	// Start up the State Manager, and feed it the Main States.
	StateManager& stateManager(StateManager::instance());
	stateManager.add<MenuState>("MenuState");
	stateManager.add<GameState>("GameState");
	stateManager.launch("GameState");
	
	// Tick over the State Manager while we have any States.
	Timer mainTimer;
	while (true == stateManager.hasStates()) {
		stateManager.update(mainTimer.processDelta());
	}

	// Cleanup
	configManager.saveConfig();
	
	// Goodbye World
	return 0;
}
