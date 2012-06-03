#ifndef _SDL_INPUT_OBJECT_H_
#define _SDL_INPUT_OBJECT_H_

#include <SDL/SDL.h>
#include <map>
#include <string>

#include "InputObject.h"

class Entity;
class SDLInputObject : public InputObject
{
	public:
		SDLInputObject(Entity* const entity) : InputObject(entity) {}
		~SDLInputObject() {}
		
		//! Setup the Controls
		void setup();
		
		//! Update the Controls
		void update();
		
	private:
		std::map<std::string, SDLKey> controls_;
};

#endif
