#include "SDLInputObject.h"

#include "../Entities/PlayerShip.h"
#include "../Systems/Input/InputSystem.h"

void SDLInputObject::setup()
{
	// These should come from Config Manager...
	controls_["Accelerate"] = SDLK_UP;
	controls_["Decelerate"] = SDLK_DOWN;
	controls_["RotateLeft"] = SDLK_LEFT;
	controls_["RotateRight"] = SDLK_RIGHT;
	controls_["GrappleLeft"] = SDLK_q;
	controls_["GrappleRight"] = SDLK_e;
	controls_["Fire"] = SDLK_w;
}

void SDLInputObject::update()
{
	InputSystem& inputSystem(InputSystem::instance());
	
	if (inputSystem.keyDown(controls_["Accelerate"]))
		writeEntity<PlayerShip>()->accelerate();
	else if (inputSystem.keyDown(controls_["Decelerate"]))
		writeEntity<PlayerShip>()->decelerate();
		
	if (inputSystem.keyDown(controls_["RotateLeft"]))
		writeEntity<PlayerShip>()->rotateLeft();
	else if (inputSystem.keyDown(controls_["RotateRight"]))
		writeEntity<PlayerShip>()->rotateRight();
		
	if (inputSystem.keyDown(controls_["GrappleLeft"]))
		writeEntity<PlayerShip>()->grappleLeft();
	
	if (inputSystem.keyDown(controls_["GrappleRight"]))
		writeEntity<PlayerShip>()->grappleRight();
		
	if (inputSystem.keyDown(controls_["Fire"]))
		writeEntity<PlayerShip>()->fire();
}