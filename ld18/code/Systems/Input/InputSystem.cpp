#include "InputSystem.h"

#include <SDL/SDL.h>
#include "../../Managers/StateManager.h"
#include "../Entity/EntitySystem.h"
#include "../Entity/EntityList.h"
#include "../../Objects/SDLInputObject.h"
#include "../../Entities/Entity.h"

InputSystem* InputSystem::instance_ = 0;

InputSystem& InputSystem::instance()
{
	if (0 == instance_)
		instance_ = new InputSystem;
		
	return *instance_;		
}

InputSystem::InputSystem()
: keyboardBuffer_(0)
{
	
}

InputSystem::~InputSystem()
{
	delete instance_;
	instance_ = 0;
}


void InputSystem::initialise()
{
	
}

void InputSystem::update()
{
	SDL_PumpEvents();
	keyboardBuffer_ = SDL_GetKeyState(NULL);
	
	EntitySystem& entitySystem(EntitySystem::instance());
	EntityList* entityList(entitySystem.getList("Player"));
	
	std::list<Entity*> playerList(entityList->writeList());
	for (std::list<Entity*>::iterator player(playerList.begin()); player != playerList.end(); ++player) {
		SDLInputObject& inputObject((*player)->writeInputObject<SDLInputObject>());
		inputObject.update();
	}
		
}

const bool InputSystem::hasQuit() const
{
	bool hasQuit(false);
	if (keyboardBuffer_[SDLK_ESCAPE])
		hasQuit = true;
		
	SDL_Event event;
    while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT)
			hasQuit = true;
	}
	
	return hasQuit;
}
