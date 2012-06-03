#include "GameLoadingProcess.h"

#include <cassert>

#include "GameRenderProcess.h"
#include "GamePhysicsProcess.h"
#include "GameInputProcess.h"

#include "../GameState.h"
#include "../Process.h"
#include "../Processor.h"

#include "../../Entities/Bullet.h"
#include "../../Entities/PlayerShip.h"
#include "../../Entities/GrappleHook.h"
#include "../../Entities/HookSegment.h"
#include "../../Managers/StateManager.h"
#include "../../Objects/SDLGraphicObject.h"
#include "../../Objects/SDLInputObject.h"
#include "../../Systems/Entity/EntitySystem.h"

const Process::Return GameLoadingProcess::update(const float deltaTime)
{
	StateManager& stateManager(StateManager::instance());
	GameState* gameState(stateManager.getState<GameState>("GameState"));
	assert(gameState);
	
	EntitySystem& entitySystem(EntitySystem::instance());
	PlayerShip* playerShip(entitySystem.add<PlayerShip>("Player"));
	playerShip->setGraphicObject(new SDLGraphicObject);
	playerShip->writeGraphicObject<SDLGraphicObject>().load("data/playership.bmp");
	playerShip->setInputObject(new SDLInputObject(playerShip));
	playerShip->writeInputObject<SDLInputObject>().setup();
	playerShip->writePosition() = Vector2D(300.0F, 200.0F);
	playerShip->setMass(3.0F);
	//playerShip->writeVelocity() = Vector2D(100.0F, 300.0F);
	entitySystem.addToList(playerShip, "Renderable");
	entitySystem.addToList(playerShip, "Collidable");
	entitySystem.addToList(playerShip, "Movable");
	entitySystem.addToList(playerShip, "Ship");
	
	Bullet* enemyShip(entitySystem.add<Bullet>("Renderable"));
	enemyShip->setGraphicObject(new SDLGraphicObject);
	enemyShip->writeGraphicObject<SDLGraphicObject>().load("data/enemy.bmp");
	enemyShip->writePosition() = Vector2D(150.0F, 300.0F);
	enemyShip->setMass(3.0F);
	entitySystem.addToList(enemyShip, "Movable");
	//entitySystem.addToList(enemyShip, "Ship");
	
	GrappleHook* grapple(entitySystem.add<GrappleHook>("Renderable"));
	grapple->setGraphicObject(new SDLGraphicObject);
	grapple->writeGraphicObject<SDLGraphicObject>().load("data/hook.bmp");
	grapple->setSource(playerShip);
	grapple->setTarget(enemyShip);
	
	for (Uint segment(0U); segment < 10U; ++segment) {
		HookSegment* hookSegment(entitySystem.add<HookSegment>("Renderable"));
		hookSegment->setGraphicObject(new SDLGraphicObject);
		hookSegment->writeGraphicObject<SDLGraphicObject>().load("data/segment.bmp");
		grapple->addSegment(hookSegment);
	}

	entitySystem.addToList(grapple, "Grapple");
	grapple->setSpeed(100.0F);
	grapple->writePosition() = playerShip->readPosition();
	grapple->fire();
	
	std::vector<Process*> processList;
	processList.push_back(new GameInputProcess);
	processList.push_back(new GamePhysicsProcess);
	processList.push_back(new GameRenderProcess);
	gameState->setProcessor(new Processor(processList));
	
	return Process::STOP;
}