#include "SDLGraphicObject.h"

#include <cassert>

SDLGraphicObject::SDLGraphicObject()
: graphicSurface_(0)
{
	
}

SDLGraphicObject::~SDLGraphicObject()
{
	if (graphicSurface_) {
		SDL_FreeSurface(graphicSurface_);
		graphicSurface_ = 0;
	}
}

void SDLGraphicObject::load(const std::string& fileName)
{
	assert(!graphicSurface_);
	SDL_Surface* convertSurface(SDL_LoadBMP(fileName.c_str()));
	graphicSurface_ = SDL_ConvertSurface(convertSurface, SDL_GetVideoSurface()->format, SDL_SWSURFACE);
	SDL_FreeSurface(convertSurface);
	
	SDL_SetColorKey(graphicSurface_, SDL_SRCCOLORKEY, SDL_MapRGB(graphicSurface_->format, 255U, 0U, 255U));
}

