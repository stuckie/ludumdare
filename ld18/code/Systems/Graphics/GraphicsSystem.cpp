#include "GraphicsSystem.h"

#include <SDL/SDL.h>
#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL_framerate.h>

#include "../Entity/EntitySystem.h"
#include "../Entity/EntityList.h"

#include "../../Entities/Entity.h"
#include "../../Objects/SDLGraphicObject.h"

GraphicsSystem* GraphicsSystem::instance_ = 0;

GraphicsSystem& GraphicsSystem::instance()
{
	if (0 == instance_)
		instance_ = new GraphicsSystem;
		
	return *instance_;		
}

GraphicsSystem::GraphicsSystem()
: width_(640)
, height_(480)
, bpp_(32)
, screen_(0)
, fpsManager_()
{
	
}

GraphicsSystem::~GraphicsSystem()
{
	if (screen_) {
		SDL_FreeSurface(screen_);
		screen_ = 0;
	}
	
	delete instance_;
	instance_ = 0;
}

void GraphicsSystem::initialise(const Uint32 width, const Uint32 height, const Uint32 bpp)
{
	width_ = width;
	height_ = height;
	bpp_ = bpp;
	
	SDL_Init(SDL_INIT_EVERYTHING);
	
	screen_ = SDL_SetVideoMode(width, height, bpp, SDL_SWSURFACE | SDL_DOUBLEBUF);
	
	SDL_WM_SetCaption("T.I.T.A.N", "T.I.T.A.N");
	
	SDL_initFramerate(&fpsManager_);
	SDL_setFramerate(&fpsManager_, 60);
}

void GraphicsSystem::render(GraphicsCamera* const graphicsCamera)
{
	SDL_framerateDelay(&fpsManager_);
	
	EntitySystem& entitySystem(EntitySystem::instance());
	EntityList* entityList(entitySystem.getList("Renderable"));
	
	SDL_FillRect( SDL_GetVideoSurface(), NULL, 0 );
	
	const std::list<Entity*> renderableList(entityList->readList());
	for (std::list<Entity*>::const_iterator entity(renderableList.begin()); entity != renderableList.end(); ++entity) {
		const SDLGraphicObject& graphicObject((*entity)->readGraphicObject<SDLGraphicObject>());
		SDL_Surface* const entityGraphic(graphicObject.readSurface());
		
		SDL_Rect position;
		position.x = static_cast<int>((*entity)->readPosition().x_);
		position.y = static_cast<int>((*entity)->readPosition().y_);
		position.w = static_cast<int>(graphicObject.readSize().x_);
		position.h = static_cast<int>(graphicObject.readSize().y_);
		
		SDL_Surface* roto(SDL_DisplayFormat(entityGraphic));
		SDL_BlitSurface(entityGraphic, NULL, roto, NULL);
		SDL_Surface* roto2(rotozoomSurface(roto, (*entity)->getAngle(), 1.0F, SMOOTHING_OFF));
		SDL_SetColorKey(roto2, SDL_SRCCOLORKEY, SDL_MapRGB(roto2->format, 255U, 0U, 255U));
		SDL_Rect clip;
		clip.x = 0;
		clip.y = 0;
		clip.w = roto2->w;
		clip.h = roto2->h;
		SDL_BlitSurface(roto2, &clip, screen_, &position);
		
		SDL_FreeSurface(roto);
		SDL_FreeSurface(roto2);
	}
	
	SDL_Flip(screen_);
}
