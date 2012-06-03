#ifndef _SDL_GRAPHIC_OBJECT_H_
#define _SDL_GRAPHIC_OBJECT_H_

#include "GraphicObject.h"
#include <SDL/SDL.h>
#include <string>

class SDLGraphicObject : public GraphicObject
{
	public:
		SDLGraphicObject();
		~SDLGraphicObject();
		
		void load(const std::string& fileName);
		SDL_Surface* const readSurface() const { return graphicSurface_; }
		SDL_Surface* const writeSurface() { return graphicSurface_; }
		
	private:
		SDL_Surface* graphicSurface_;
};

#endif
